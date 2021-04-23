#ifndef MESSENGER_H
#define MESSENGER_H

#include "./ui_messenger.h"

#include "qtincludes.h"
#include "netcontroller.h"

class Messenger : public QMainWindow, private Ui::Messenger
{
    Q_OBJECT
private:
    NetController* netController = new NetController();
    QString userName;
public:
    Messenger( QWidget* parent = nullptr );
    ~Messenger();
private slots:
    void onSendClicked();
    void slotError( const int error );
    void slotLoginSuccessful();
    void slotContextMenu( const QPoint& pos );
    void slotAddContact( const QString& nameUser );
    void slotFromUser( QString message );
    void slotGetOnline( QString online );
    void slotUnreadMessage( QStringList messages );
    void slotSuccessfulAddContact();
    void slotCountUnreadMessage( QStringList messages );
    void slotConnected();
    void slotDisconnect();
    void slotNewMessage( const QString* sender, const QString* message );
    void slotUpdateContactList( const QString& contacts );
    void on_login_button_clicked();
    void on_login_username_textEdited( const QString& arg1 );
    void on_login_password_textEdited( const QString& arg1 );
    void on_send_clicked();
    void on_input_textEdited( const QString& arg1 );
    void on_listClients_currentTextChanged( const QString& currentText );
    void on_tabWidget_currentChanged( int index );
    void on_listFriends_currentTextChanged( const QString& currentText );
    void on_FindClientButton_clicked();
    void on_FindClient_textEdited( const QString& arg1 );

signals:
    void signalConnection();
    void signalGetOnline();
    void signalUpdateContactList(  );
    void signalAddContact( const QString& );
    void signalSendMessage( const QString* );
    void signalError( const int );
};
#endif // MESSENGER_H
