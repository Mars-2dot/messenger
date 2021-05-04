#include "node.h"

Node::Node( QObject* parent ) : QObject( parent )
{
    connect( node, &QTcpServer::newConnection, this, &Node::slotNewConnection, Qt::DirectConnection );
}

void Node::slotNewConnection()
{
    QTcpSocket* ClientSocket = node->nextPendingConnection();
    connect( ClientSocket, &QAbstractSocket::disconnected, ClientSocket, &QAbstractSocket::deleteLater );
    connect( ClientSocket, &QIODevice::readyRead, this,  &Node::slotReadyRead );
}

void Node::slotReadyRead()
{
    QTcpSocket* ClientSocket = ( QTcpSocket* )sender();
    QDataStream in( ClientSocket );
    QTime time;
    QString data;
    in >> time >> data;
    QStringList UserMessage = data.split( "|" );

    if ( UserMessage[0] == "Login" ) {
//        slotLoginInUsers( ClientSocket, UserMessage[1] );
    } else if ( UserMessage[0] == netCommand[getOnline] ) {
//        emit signalSendOnline( ClientSocket );
    } else if ( UserMessage[0] == "FindContact" ) {
//        emit signalUserFindInDataBase( UserMessage[1], ClientSocket );
    } else if ( UserMessage[0] == netCommand[recoverContactList] ) {
//        sendToClient( ClientSocket, netCommand[recoverContactList], dataBase.getContactList( FindUser( ClientSocket ).Name ) );
    } else if ( UserMessage[0] == netCommand[updateContactList] ) {
//        emit signalUpdateContactList( ClientSocket, FindUser( ClientSocket ).Name );
    } else if ( UserMessage[0] == netCommand[addInContactList] ) {
//        emit signalAddContactList( ClientSocket, UserMessage[1] );
    } else if ( UserMessage[0] == netCommand[message] ) {
        emit signalNewMessage( UserMessage[1], UserMessage[2] );
    } else if ( UserMessage[0] == "sendUnreadMessage" ) {
//        sendToClient( ClientSocket, "unreadMessage", dataBase.getUnreadMessage( UserMessage[1],
    } else if ( UserMessage[0] == "disconnect" ) {
//        emit slotDeleteUserInOnline();
    } else if ( UserMessage[0] == "Connect" ) {
//        sendToClient( ClientSocket, "ConnectSuccessful", "" );
    } else {
//        emit signalWriteHistoryToDataBase( data, FindUser( ClientSocket ) );
    }

}

void Node::slotStartPort( const QString& name, const QString& password, const QString& ip, const int port )
{
    if ( port == 0 ) {
        for ( int port = 2323; port < 4343; port++ ) {
            if ( node->listen( QHostAddress::Any, port ) ) {
                break;
            } else {
                node->close();
            }
        }
    } else {
        node->listen( QHostAddress::Any, port );
    }
}


