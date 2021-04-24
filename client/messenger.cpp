#include "messenger.h"

Messenger::Messenger( QWidget* parent )
    : QMainWindow( parent )
{
    setupUi( this );
    this->stackedWidget->setCurrentIndex( 1 );
    this->stackedWidget->setContextMenuPolicy( Qt::CustomContextMenu );

    if ( QFile::exists( ( "settings.ini" ) ) ) {
        QSettings settings( "settings.ini", QSettings::IniFormat );
        settings.beginGroup( "WidgetPosition" );
        int x = settings.value( "x", -1 ).toInt();
        int y = settings.value( "y", -1 ).toInt();
        int width = settings.value( "width", -1 ).toInt();
        int height = settings.value( "height", -1 ).toInt();
        settings.endGroup();
        this->setGeometry( x, y, width, height );
    }

    connect( this->stackedWidget, &QStackedWidget::customContextMenuRequested, this, &Messenger::slotContextMenu );
    connect( netController, &NetController::signalError, this, &Messenger::slotError );
    connect( netController, &NetController::signalLoginSuccessful, this, &Messenger::slotLoginSuccessful );
    connect( netController, &NetController::signalUnreadMessage, this, &Messenger::slotUnreadMessage );
    connect( netController, &NetController::signalCountUnreadMessage, this, &Messenger::slotCountUnreadMessage );
    connect( netController, &NetController::signalConnectSuccessful, this, &Messenger::slotConnected );
    connect( netController, &NetController::signalGetOnline, this, &Messenger::slotGetOnline );
    connect( netController, &NetController::signalNewMessage, this, &Messenger::slotNewMessage );
    connect( netController, &NetController::signalDisconnect, this, &Messenger::slotDisconnect );
    connect( netController, &NetController::signalUpdateContactList, this, &Messenger::slotUpdateContactList );
    connect( netController, &NetController::signalAddContact, this, &Messenger::slotAddContact );
    connect( this, &Messenger::signalConnection, netController, &NetController::slotConnect );
    connect( this, &Messenger::signalGetOnline, netController, &NetController::slotGetOnline );
    connect( this, &Messenger::signalSendMessage, netController, &NetController::slotSendMessage );
    connect( this, &Messenger::signalAddContact, netController, &NetController::slotAddContact );
    connect( this, &Messenger::signalUpdateContactList, netController, &NetController::slotUpdateContastList );
    connect( this, &Messenger::signalError, this, &Messenger::slotError );
    emit signalConnection();
}

Messenger::~Messenger()
{
    if ( saveSettings ) {
        QSettings settings( "settings.ini", QSettings::IniFormat );
        settings.beginGroup( "WidgetPosition" );
        settings.setValue( "x", this->x() );
        settings.setValue( "y", this->y() );
        settings.setValue( "width", this->width() );
        settings.setValue( "height", this->height() );
        settings.endGroup();
    }
}

void Messenger::slotError( int error )
{
    switch ( error ) {
        case 0: {
            this->chat->setText( "unknown server command" );
        }
        break;

        case 1: {
            this->login_error->setText( "Connection failed" );
        }
        break;

        case 2: {
            this->login_error->setText( "Error of login" );
        }
        break;

        case 3: {
            this->chat->setText( "Error add contact list" );
        }
        break;
    }
}

void Messenger::slotLoginSuccessful()
{
    this->stackedWidget->setCurrentIndex( 0 );
    emit signalGetOnline();
}

void Messenger::slotContextMenu( const QPoint& pos )
{
    QMenu menu( this );
    auto infoA = menu.addAction( tr( "Add to friend" ) );

    if ( ( this->listClients->hasFocus() && this->listClients->count() ) ) {
        connect( infoA, &QAction::triggered, this, [this]() {
            emit signalAddContact( this->listClients->currentItem()->text() );
            update();
        } );
        menu.exec( QCursor::pos() );
    }
}

void Messenger::slotAddContact( const QString& nameUser )
{
    this->listFriends->addItem( nameUser );
    emit signalAddContact( nameUser );
}

void Messenger::slotUpdateContactList( const QString& contacts )
{
    QStringList listUsers = contacts.split( "%" );
    listUsers.removeDuplicates();
    this->listFriends->clear();

    for ( int i = 0; i < listUsers.size(); i++ ) {
        this->listFriends->addItem( listUsers[i] );
    }
}

void Messenger::slotGetOnline( QString online )
{
    QStringList usersName = online.split( "%" );

    if ( !usersName.isEmpty() ) {
        usersName.removeDuplicates();
        this->listClients->clear();

        for ( int i = 0; i < usersName.size(); i++ ) {
            if ( ( usersName[i] != userName ) && ( usersName[i] != "" ) ) {
                this->listClients->addItem( usersName[i] );
            }
        }
    }
}

void Messenger::slotUnreadMessage( QStringList messages )
{

}

void Messenger::slotCountUnreadMessage( QStringList messages )
{

}

void Messenger::slotConnected()
{
    this->login_error->setText( "Connect successful" );
}

void Messenger::slotDisconnect()
{
    this->stackedWidget->setCurrentIndex( 1 );
    emit signalError( 1 );
}

void Messenger::slotNewMessage( const QString* sender, const QString* message )
{
    this->chat->setText( this->chat->text() + "\n" + *sender + "->You: " + *message );
}

void Messenger::on_login_button_clicked()
{
    netController->slotSend( "Login", this->login_username->text() + "|" + this->login_password->text() );
    userName = this->login_username->text();
}

void Messenger::on_login_username_textEdited( const QString& arg1 )
{
    if ( ( !arg1.isEmpty() ) && ( !this->login_password->text().isEmpty() ) ) {
        this->login_button->setDisabled( false );
    } else {
        this->login_button->setDisabled( true );
    }
}

void Messenger::on_login_password_textEdited( const QString& arg1 )
{
    if ( ( !this->login_username->text().isEmpty() ) && ( !arg1.isEmpty() ) ) {
        this->login_button->setDisabled( false );
    } else {
        this->login_button->setDisabled( true );
    }
}

void Messenger::on_send_clicked()
{
    const QString& message = this->listFriends->currentItem()->text() + "|" + this->input->text();
    this->chat->setText( this->chat->text() + "\n" + "You->" + this->listFriends->currentItem()->text() + ": " +
                         this->input->text() );
    this->input->clear();
    this->send->setEnabled( true );
    emit signalSendMessage( &message );
}

void Messenger::on_input_textEdited( const QString& arg1 )
{
    if ( !arg1.isEmpty()  && this->listFriends->currentIndex().isValid() ) {
        this->send->setDisabled( false );
    }
}

void Messenger::on_tabWidget_currentChanged( int index )
{
    switch ( index ) {
        case 0: {
            emit signalGetOnline();
        }
        break;

        case 1: {
            emit signalUpdateContactList();
        }
        break;
    }
}

void Messenger::on_listFriends_currentTextChanged( const QString& currentText )
{
    if ( !currentText.isEmpty() && !this->input->text().isEmpty() ) {
        this->send->setDisabled( false );
    }
}

void Messenger::on_FindClientButton_clicked()
{
    if ( !this->FindClient->text().isNull() ) {
        QString foundUser;
        auto result = this->listClients->findItems( this->FindClient->text(), Qt::MatchContains );

        for ( int i = 0; i < result.size(); i++ ) {

            if ( result[i]->text() == this->FindClient->text() ) {
                foundUser = result[i]->text();
            }
        }

        this->listClients->clear();
        slotGetOnline( foundUser );
    } else {
        emit signalGetOnline();
    }
}

void Messenger::on_FindClient_textEdited( const QString& arg1 )
{
    if ( arg1.isEmpty() ) {
        emit signalGetOnline();
    } else {
        this->FindClientButton->setDisabled( false );
    }
}

void Messenger::on_SaveSizeWindow_clicked( bool checked )
{
    if ( checked ) {
        saveSettings = true;
    } else {
        saveSettings = false;
    }
}
