#include "server.h"

Server::Server( QObject* parent ) : QObject( parent )
{
    TcpServer = new QTcpServer( this );
    connect( TcpServer,  &QTcpServer::newConnection, this, &Server::slotNewConnection );
    connect( this, &Server::signalAuthenticateUsers, &Server::slotLoginInUsers );
    connect( this, &Server::signalSendOnline, this, &Server::slotSendOnline );
    connect( this, &Server::signalUpdateOnline, this, &Server::slotUpdateOnline );
    connect( this, &Server::signalSendMessage, this, &Server::slotSendMessage );
    connect( this, &Server::signalUpdateContactList, this, &Server::slotUpdateContactList );
    connect ( this, &Server::signalAddContactList, this, &Server::slotAddContactList );

    spdlog::info( "Server start" );

    int Port = 2323;

    if ( !TcpServer->listen( QHostAddress::Any, Port ) ) {
        TcpServer->close();
        spdlog::critical( "Error of socket" );
        return;
    }

    spdlog::info( "Waiting connects..." );
}


void Server::sendToClient( QTcpSocket* Socket, const QString& command, const QString& message )
{
    QByteArray  arrBlock;
    QDataStream out( &arrBlock, QIODevice::WriteOnly );
    out << QTime::currentTime() << command + "|" + message;
    Socket->write( arrBlock );
}

Server::UserData Server::FindUser( QTcpSocket* Socket )
{
    for ( int i = 0; i < UsersInOnline.length(); i++ ) {
        if ( UsersInOnline[i].Socket == Socket ) {
            return UsersInOnline[i];
        }
    }

    UserData ReturnErrorName;
    ReturnErrorName.Name = "Error";
    return ReturnErrorName;
}

Server::UserData Server::FindUser( QString UserName )
{
    for ( int i = 0; i < UsersInOnline.length(); i++ ) {
        if ( UsersInOnline[i].Name == UserName ) {
            return UsersInOnline[i];
        }
    }

    UserData ReturnErrorName;
    ReturnErrorName.Name = "Error";
    return ReturnErrorName;
}

void Server::slotNewConnection()
{
    QTcpSocket* ClientSocket = TcpServer->nextPendingConnection();
    connect( ClientSocket, &QAbstractSocket::disconnected, this, &Server::slotDeleteUserInOnline );
    connect( ClientSocket, &QAbstractSocket::disconnected, ClientSocket, &QAbstractSocket::deleteLater );
    connect( ClientSocket, &QIODevice::readyRead, this,  &Server::slotReadClient );
}

void Server::slotReadClient()
{
    QTcpSocket* ClientSocket = ( QTcpSocket* )sender();
    QDataStream in( ClientSocket );
    QTime time;
    QString data;
    in >> time >> data;
    QStringList UserMessage = data.split( "|" );

    if ( UserMessage[0] == "Login" ) {
        slotLoginInUsers( ClientSocket, UserMessage[1] );
    } else if ( UserMessage[0] == netCommand[getOnline] ) {
        emit signalSendOnline( ClientSocket );
    } else if ( UserMessage[0] == "FindContact" ) {
        emit signalUserFindInDataBase( UserMessage[1], ClientSocket );
    } else if ( UserMessage[0] == netCommand[recoverContactList] ) {
        sendToClient( ClientSocket, netCommand[recoverContactList], dataBase.getContactList( FindUser( ClientSocket ).Name ) );
    } else if ( UserMessage[0] == netCommand[updateContactList] ) {
        emit signalUpdateContactList( ClientSocket, FindUser( ClientSocket ).Name );
    } else if ( UserMessage[0] == netCommand[addInContactList] ) {
        emit signalAddContactList( ClientSocket, UserMessage[1] );
    } else if ( UserMessage[0] == netCommand[message] ) {
        const QString& message = UserMessage[2];
        const QString& recipient = UserMessage[1];
        const QString& sender = FindUser( ClientSocket ).Name;
        emit signalSendMessage( &sender, &recipient, &message );
    } else if ( UserMessage[0] == "sendUnreadMessage" ) {
        sendToClient( ClientSocket, "unreadMessage", dataBase.getUnreadMessage( UserMessage[1],
                                                                                FindUser( UserMessage[2] ).Name ) );
    } else if ( UserMessage[0] == "disconnect" ) {
        emit slotDeleteUserInOnline();

    } else if ( UserMessage[0] == "Connect" ) {
        sendToClient( ClientSocket, "ConnectSuccessful", "" );
    } else {
        emit signalWriteHistoryToDataBase( data, FindUser( ClientSocket ) );
    }
}

void Server::slotUpdateOnline( QString* const newConnectName )
{
    for ( int i = 0; i < UsersInOnline.size(); i++ ) {
        if ( UsersInOnline.at( i ).Name != *newConnectName ) {
            emit signalSendOnline( UsersInOnline.at( i ).Socket );
        }
    }
}

void Server::slotLoginInUsers( QTcpSocket* Socket, const QString& name )
{
    spdlog::info( "New connect" );
    UserData userData;
    userData.Socket = Socket;
    userData.Name = name;

    if ( FindUser( name ).Name != "Error" ) {
        sendToClient( Socket, netCommand[errorLogin], "" );
        spdlog::error( "The user is already logged in" );
        return;
    }

    if ( dataBase.checkUser( userData.Name ) ) {
        UsersInOnline << userData;
    } else {
        UsersInOnline << userData;
        dataBase.addUser( userData.Name );
    }

    emit signalUpdateOnline( &userData.Name );

    sendToClient( Socket, netCommand[loginSuccessful], dataBase.getContactList( FindUser( Socket ).Name ) );
}

void Server::slotDeleteUserInOnline()
{
    QTcpSocket* SenderPoint = ( QTcpSocket* ) sender();

    for ( int i = 0; i < UsersInOnline.length(); i++ ) {
        if ( UsersInOnline[i].Socket == SenderPoint ) {
            UsersInOnline.removeAt( i );
            break;
        }
    }
}

void Server::slotUpdateContactList( QTcpSocket* socket )
{
    QString listContacts = dataBase.getPersonalContactList( FindUser( socket ).Name  );

    if ( !listContacts.isNull() ) {
        sendToClient( socket, netCommand[successfulAddContact], listContacts );
        spdlog::info( "Send contact list" );
    } else {
        spdlog::info( "Contact list is empty" );
    }

}

void Server::slotSendOnline( QTcpSocket* socket )
{
    QString inOnline;

    for ( int i = 0; i < UsersInOnline.size(); i++ ) {
        inOnline += UsersInOnline.at( i ).Name + "%";
    }

    sendToClient( socket, netCommand[getOnline], inOnline );
    spdlog::info( "Send users in online for " + FindUser( socket ).Name.toLocal8Bit() );
}

void Server::slotSendMessage( const QString* sender, const QString* recipient, const QString* messageForUser )
{
    if ( FindUser( *recipient ).Name != "Error" ) {
        sendToClient( FindUser( *recipient ).Socket, netCommand[message],  *sender + "|" + *messageForUser );
    } else {
        dataBase.saveUserMessage( recipient, messageForUser, sender );
    }

    spdlog::info( "Send message from " + QString( *sender ).toLocal8Bit() + " for " + QString( *recipient ).toLocal8Bit() );
}

void Server::slotAddContactList( QTcpSocket* socket, const QString& nameUser )
{
    spdlog::info( FindUser( socket ).Name.toLocal8Bit() + ":" + nameUser.toLocal8Bit() );

    if ( dataBase.addInContactList( FindUser( socket ).Name, nameUser ) ) {
        sendToClient( socket, netCommand[successfulAddContact], "Сontact added successfully" );
        spdlog::info( "Add user to contact list" );
    }
}
