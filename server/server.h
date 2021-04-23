#ifndef SERVER2_H
#define SERVER2_H

#include "qtincludes.h"
#include "database.h"

class Server : public QObject
{
    Q_OBJECT

private:
    struct UserData {
        QTcpSocket* Socket;
        QString    Name;
        QString    Password;
        QString    Token;
        int        id;
    };

    typedef enum netCommands {
        getOnline = 0,
        loginSuccessful = 1,
        recoverContactList = 2,
        message = 3,
        errorLogin = 4,
        addInContactList = 5,
        successfulAddContact = 6,
        errorAddContact = 7,
        updateContactList = 8
    } netCommands ;

    QString netCommand[10] = {
        "getOnline",
        "loginSuccessful",
        "recoverContactList",
        "message",
        "errorLogin",
        "addInContactList",
        "successfulAddContact",
        "errorAddContact",
        "updateContactList"
    };

    QTcpServer* TcpServer;
    DataBase dataBase;
    QList<UserData> UsersInOnline;
    QString bufferMessage = "";

private:
    void sendToClient( QTcpSocket* Socket, const QString& command, const QString& message );
    UserData FindUser( QTcpSocket* Socket );
    UserData FindUser( QString UserName );

public:
    explicit Server( QObject* parent = nullptr );

private slots:
    virtual void slotNewConnection();
    void slotReadClient();
    void slotUpdateOnline( QString* const newConnectName );
    void slotLoginInUsers( QTcpSocket* Socket, const QString& str );
    void slotDeleteUserInOnline();
    void slotUpdateContactList( QTcpSocket* socket );
    void slotSendOnline( QTcpSocket* socket );
    void slotSendMessage( const QString* sender, const QString* recipient, const QString* messageForUser );
    void slotAddContactList( QTcpSocket* socket, const QString& nameUser );

signals:
    void signalAuthenticateUsers( QTcpSocket* Socket, const QString& str );
    void signalAddUserToDataBase( UserData UsersData );
    void signalUpdateOnline( QString* );
    void signalWriteHistoryToDataBase( QString Messages, UserData dataUser );
    void signalUserFindInDataBase( QString nameUser, QTcpSocket* requestersSocket );
    void signalSendUnreadMessage( Server::UserData userData, QString command, QString sender  );
    void signalSendOnline( QTcpSocket* );
    void signalSendMessage( const QString*, const QString*, const QString* );
    void signalUpdateContactList( QTcpSocket*, const QString& );
    void signalAddContactList( QTcpSocket*, const QString& );
};

#endif // SERVER2_H
