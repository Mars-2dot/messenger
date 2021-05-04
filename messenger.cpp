#include "messenger.h"

messenger::messenger( QWidget* parent )
    : QMainWindow( parent )
{
    setupUi( this );
    connect( this, &messenger::signalSetUserData, netController, &NetController::slotSetUserData );
    connect( this, &messenger::signalCheckUser, netController, &NetController::slotCheckUser );
    connect( this, &messenger::signalAddRegUser, netController, &NetController::slotAddRegUser );
    connect( this, &messenger::signalGetPort, netController, &NetController::slotGetPort );
    connect( this, &messenger::signalSend, netController, &NetController::slotSendMessage );
    connect( netController, &NetController::signalOperationSuccessful, this, &messenger::slotOperationSuccessful );
    connect( netController, &NetController::signalUpdateUserList, this, &messenger::slotUpdateUserList );
    connect( netController, &NetController::signalError, this, &messenger::slotError );
//    connect( netController, &NetController::signalConnectSuccessful, this, &messenger::slotError );
    connect( netController, &NetController::signalNewMessage, this, &messenger::slotNewMessage );
}

messenger::~messenger()
{

}

void messenger::slotUpdateUserList( const QString& name, const QString& password, const QString& ip, const int port )
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

void messenger::slotError( const int code )
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

    }
}

void messenger::slotConnectSuccessful( const QString&, const QString& )
{

}

void messenger::slotNewMessage( const QString& sender, const QString& message )
{
    chat->setText( chat->text() + "\n" + sender + "->" + message );
}

void messenger::on_login_signup_clicked()
{
    stackedWidget->setCurrentIndex( 1 );
}

void messenger::on_signup_button_clicked()
{
    if ( signup_password->text() == signup_confirm->text() ) {
        QString name = signup_username->text(), password = signup_password->text();
//        emit signalSetUserData( name, password );
        stackedWidget->setCurrentIndex( 2 );
        emit signalAddRegUser( signup_username->text(), signup_password->text(), "", 0 );
    } else {
        slotError( 1 );
    }
}

void messenger::on_login_button_clicked()
{
    emit signalCheckUser( login_username->text(), login_password->text() );
}

void messenger::on_signup_login_clicked()
{
    stackedWidget->setCurrentIndex( 0 );
}

void messenger::on_input_textEdited( const QString& arg1 )
{
    if ( !arg1.isEmpty() && !listUser->currentItem()->text().isEmpty() ) {
        send->setDisabled( false );
    }
}

void messenger::on_send_clicked()
{
    emit signalSend( "User|" + input->text() );
}

void messenger::on_listUser_currentTextChanged( const QString& currentText )
{
    emit signalGetPort( currentText );
}
