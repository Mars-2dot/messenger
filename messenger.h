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
    core* tox;
    QThread* thread = new QThread;

public:
    messenger( QWidget* parent = nullptr );
    ~messenger();
public slots:
    void slotUpdateUserList( const QString& name, const QString& password, const QString& ip, const int port );
private slots:
    void slotOperationSuccessful( const int code );
    void slotError( const int code );
    void slotConnectSuccessful( const QString&, const QString& );
    void slotNewMessage( const QString& sender, const QString& message );
    void on_login_signup_clicked();
    void on_signup_button_clicked();
    void on_login_button_clicked();
    void on_signup_login_clicked();
    void on_input_textEdited( const QString& arg1 );
    void on_send_clicked();
    void on_listUser_currentTextChanged( const QString& currentText );

signals:
    void signalSetUserData( const QString&, const QString& );
    void signalCheckUser( const QString&, const QString );
    void signalAddRegUser( const QString&, const QString&, const QString&, const int );
    void signalSend( const QString& message );
    void signalGetPort( const QString& nameUser );
};
#endif // MESSENGER_H
