#include "messenger.h"

messenger::messenger( QWidget* parent )
    : QMainWindow( parent )
{
    setupUi( this );

    connect( thread, &QThread::started, tox, &core::start );
    connect( thread, &QThread::finished, thread, &QThread::deleteLater );
    connect( tox, &core::signalSetId, this, &messenger::slotSetId, Qt::DirectConnection );
    connect( tox, &core::signalSendMessage, this, &messenger::slotNewMessage, Qt::DirectConnection );
    connect( tox, &core::signalFriendRequest, this, &messenger::slotFriendRequest, Qt::DirectConnection );
    connect( tox, &core::signalSendFriendList, this, &messenger::slotFriendListUpdate, Qt::DirectConnection );
    connect( tox, &core::signalError, this, &messenger::slotError, Qt::DirectConnection );
    connect( tox, &core::signalCheckSuccessful, this, &messenger::slotCheckSuccessful, Qt::DirectConnection );
    connect( tox, &core::signalSetStatus, this, &messenger::slotSetStatus, Qt::DirectConnection );
    connect( this, &messenger::signalAcceptFriendRequest, tox, &core::slotAddFriend, Qt::DirectConnection );
    connect( this, &messenger::signalToxStart, &messenger::slotToxStart );
    connect( this, &messenger::signalAcceptFriendRequest, tox, &core::slotAcceptFriendRequest, Qt::DirectConnection );
    connect( this, &messenger::signalSend, tox, &core::slotSendMessage, Qt::DirectConnection );
    connect( this, &messenger::signalCheckUser, tox, &core::slotCheckUser, Qt::DirectConnection );
    connect( this, &messenger::signalUpdateFriendList, tox, &core::slotGetListFriends, Qt::DirectConnection );
    connect( this, &messenger::signalFriendAdd, tox, &core::slotFriendAdd, Qt::DirectConnection );
}

messenger::~messenger()
{

}

void messenger::slotUpdateUserList( const QString& name )
{
    listUser->addItem( name );
}

void messenger::slotOperationSuccessful( const int code )
{
    switch ( code ) {
        case 0: {
            stackedWidget->setCurrentIndex( 2 );
        }
        break;
    }
}

void messenger::slotSetId( const QString& id )
{
    statusBar()->addWidget( status );
    status->setStyleSheet( "QLabel { font: 13pt \"Open Sans Light\"; color:rgb(215, 213, 217);}" );
    status->setText( "Connecting, please wait" );
    copyToxId->setText( copyToxId->text() + id );
}

void messenger::slotError( int code )
{
    switch ( code ) {
        case 0: {
            QMessageBox::warning( 0, "Warning", "User with this name already exists", "Ok" );
        }
        break;

        case 1: {
            QMessageBox::warning( 0, "Warning", "The password and its confirmation do not match", "Ok" );
        }
        break;

        case 2: {
            QMessageBox::warning( 0, "Warning", "A user with this username and password was not found", "Ok" );
        }
        break;

        case 3: {
            QMessageBox::warning( 0, "Warning", "Error of socket", "Ok" );
        }
        break;

        case 4: {
            QMessageBox::warning( 0, "Warning", "Error of read socket", "Ok" );
        }
        break;

        case 5: {
            QMessageBox::critical( 0, "Critical", "Error of read ID from database", "Ok" );
        }
        break;
    }
}

void messenger::slotSetStatus( const int code )
{
    switch ( code ) {
        case 1: {
            status->setStyleSheet( "QLabel { font: 13pt \"Open Sans Light\"; color:red;}" );
            status->setText( "Offline" );
        }
        break;

        case 2: {
            status->setStyleSheet( "QLabel { font: 13pt \"Open Sans Light\"; color:rgb(215, 213, 217);}" );
            status->setText( "Online, using UDP" );
        }
        break;

        case 3: {
            status->setStyleSheet( "QLabel { font: 13pt \"Open Sans Light\"; color:rgb(215, 213, 217);}" );
            status->setText( "Online, using TCP" );
        }
        break;
    }
}

void messenger::slotConnectSuccessful( const QString&, const QString& )
{

}

void messenger::slotNewMessage( const QString& name, const QString& message, uint32_t number )
{
    chat->setText( chat->text()  + name + "->" + message + "\n" );
}

void messenger::slotFriendRequest( const QString& message )
{
    listRequests->addItem( message );
}

void messenger::slotFriendListUpdate( QStringList& list )
{
    if ( !list.isEmpty() ) {
        for ( int i = 0; i < list.size(); i++ ) {
            if ( listUser->findItems( list.at( i ), Qt::MatchFixedString ).isEmpty() ) {
                listUser->addItem( list.at( i ) );
            }
        }
    }
}

void messenger::slotToxStart( const QString& name, const QString& password, const bool loginType )
{
    tox->login( name, password, loginType );
    tox->moveToThread( thread );
    thread->start();
}

void messenger::slotCheckSuccessful( const QString& name, const QString& password, const bool loginType )
{
    emit signalToxStart( name, password, loginType );
    stackedWidget->setCurrentIndex( 2 );
}

void messenger::on_login_signup_clicked()
{
    stackedWidget->setCurrentIndex( 1 );
}

void messenger::on_signup_button_clicked()
{
    if ( signup_password->text() == signup_confirm->text() ) {
        emit signalCheckUser( signup_username->text(), signup_password->text(), false );
        toxUser.Name = signup_username->text();
        toxUser.Password = signup_password->text();
    } else {
        slotError( 1 );
    }
}

void messenger::on_login_button_clicked()
{
    emit signalCheckUser( login_username->text(), login_password->text(), true );
    toxUser.Name = login_username->text();
    toxUser.Password = login_password->text();
}

void messenger::on_signup_login_clicked()
{
    stackedWidget->setCurrentIndex( 0 );
}

void messenger::on_send_clicked()
{
    emit signalSend(  input->text(), 0 );
    chat->setText( chat->text() + toxUser.Name + "->" + listUser->currentItem()->text() + ": " + input->text() + "\n" );
    input->clear();
    send->setDisabled( true );
}

void messenger::on_copyToxId_clicked()
{
    if ( QClipboard* c = QApplication::clipboard() ) {
        c->disconnect( this );
        c->setText( copyToxId->text().split( ":" )[1] );
    }
}

void messenger::on_listRequests_itemClicked( QListWidgetItem* item )
{
    requestAccept->setDisabled( false );
    requestReject->setDisabled( false );
}

void messenger::on_add_button_clicked()
{
    chatStackWidget->setCurrentIndex( 1 );
}

void messenger::on_contact_button_clicked()
{
    chatStackWidget->setCurrentIndex( 0 );

    if ( tox != nullptr ) {
        emit signalUpdateFriendList( tox );
    }
}

void messenger::on_requestAccept_clicked()
{
    if ( listRequests->count() > 0 ) {
        emit signalAcceptFriendRequest( listRequests->currentItem()->text().split( " " )[0] );
        QListWidgetItem* item = listRequests->takeItem( listRequests->currentRow() );
        delete item;
        requestAccept->setDisabled( true );
        requestReject->setDisabled( true );
    }
}

void messenger::on_buttonFriendAdd_clicked()
{
    emit signalFriendAdd( friendToxId->text(), messageForFriend->text() );
    friendToxId->clear();
}

void messenger::on_input_textChanged( const QString& arg1 )
{
    if ( listUser->count() > 0 ) {
        if ( !arg1.isEmpty() ) {
            send->setDisabled( false );
        } else {
            send->setDisabled( true );
        }
    }
}

void messenger::on_requestReject_clicked()
{
    if ( listRequests->count() > 0 ) {
        QListWidgetItem* item = listRequests->takeItem( listRequests->currentRow() );
        delete item;
        requestAccept->setDisabled( true );
        requestReject->setDisabled( true );
    }
}

void messenger::on_friendToxId_textChanged( const QString& arg1 )
{
    if ( arg1.size() == 76 ) {
        buttonFriendAdd->setDisabled( false );
    } else {
        buttonFriendAdd->setDisabled( true );
    }
}

void messenger::on_listUser_itemClicked( QListWidgetItem* item )
{
//    if ( !item->text().isEmpty() && !input->text().isEmpty() ) {
//        send->setDisabled( false );
//    } else {
//        send->setDisabled( true );
//    }
}

