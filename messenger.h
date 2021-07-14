#ifndef MESSENGER_H
#define MESSENGER_H

#pragma once
#include "./ui_messenger.h"
#include "qtincludes.h"

#include "core.h"

class messenger : public QMainWindow, private Ui::messenger
{
    Q_OBJECT

private:
    core* tox = new core( );
    QThread* thread = new QThread;
    struct ToxUser {
        QString ToxUser;
        QString Name;
        QString Password;
        QString publicKey;
        QString privateKey;
        QString id;
    };
    ToxUser toxUser;

    QLabel* status = new QLabel;

public:
    messenger( QWidget* parent = nullptr );
    ~messenger();

public slots:
    void slotUpdateUserList( const QString& name );

private slots:
    void slotToxStart( const QString& name, const QString& password, const bool loginType );
    void slotOperationSuccessful( const int code );
    void slotSetId( const QString& id );
    void slotError( int code );
    void slotSetStatus( const int code );
    void slotConnectSuccessful( const QString&, const QString& );
    void slotNewMessage( const QString& name, const QString& message, uint32_t number );
    void slotFriendRequest( const QString& message );
    void slotFriendListUpdate( QStringList& list );
    void slotCheckSuccessful( const QString& name, const QString& password, const bool loginType );

private slots:
    void on_login_signup_clicked();
    void on_signup_button_clicked();
    void on_login_button_clicked();
    void on_signup_login_clicked();
    void on_input_textEdited( const QString& arg1 );
    void on_send_clicked();
    void on_listUser_currentTextChanged( const QString& currentText );
    void on_copyToxId_clicked();
    void on_listRequests_itemClicked( QListWidgetItem* item );
    void on_add_button_clicked();
    void on_contact_button_clicked();
    void on_requestAccept_clicked();
    void on_buttonFriendAdd_clicked();
    void on_input_textChanged( const QString& arg1 );
    void on_requestReject_clicked();
    void on_friendToxId_textChanged( const QString& arg1 );

signals:
    void signalToxStart( const QString& name, const QString& pasword, const bool loginType );
    void signalSetUserData( const QString&, const QString& );
    void signalCheckUser( const QString& name, const QString& password, const bool loginType );
    void signalAddRegUser( const QString&, const QString&, const QString&, const int );
    void signalSend( const QString& message, uint32_t number );
    void signalGetPort( const QString& nameUser );
    void signalGetFriendList();
    void signalAcceptFriendRequest( const QString& message );
    void signalUpdateFriendList( void* core );
    void signalSaveNewFriend( const QString& Name, const QString& friendUser, const QString& PublicKey );
    void signalFriendAdd( const QString& toxID, const QString& message );
};
#endif // MESSENGER_H
