#ifndef DATABASE_H
#define DATABASE_H

#pragma once
#include "qtincludes.h"

class DataBase: public QObject
{
    Q_OBJECT

private:
    QSqlDatabase dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
    QString sqlCommand[8] = {
        " create table ",        //0
        " INSERT INTO ",         //1
        " SELECT * FROM ",       //2
        " VALUES ",              //3
        " WHERE ",               //4
        " AND ",                 //5
        " UPDATE ",              //6
        " SET ",                 //7
    };

    QString sqlNameTable[4] = {"users",				//0
                               "contacts",			//1
                               "registationList",	//2
                               "requests"			//3
                              };

    QString sqlVariable[16] = {
        """id integer primary key",  //0
        """Name text(255)",          //1
        """Password text(255)",      //2
        """Token text(255)",         //3
        """User text(255)",          //4
        """Contact text(255)",       //5
        """SaveMessage text(255)",   //6
        """IP text(255)",   		 //7
        """PORT text(255)",   		 //8
        """Status text(255)",   	 //9
        """PublicKey text(255)",   	 //10
        """Message text(255)",   	 //11
        """Data text(255)",   	     //12
        """PrivetKey text(255)",   	 //13
        """toxID text(255)",   	     //14
        """Friend text(255)",   	 //15
    };

    QString sqlNameAttributes[15] = {
        "Name",          //0
        "Password",      //1
        "Token",         //2
        "User",          //3
        "Contact",       //4
        "SaveMessage",   //5
        "IP",			 //6
        "PORT",          //7
        "Status",        //8
        "PublicKey",	 //9
        "Message",		 //10
        "Data",			 //11
        "PrivetKey",     //12
        "toxID",         //13
        "Friend",         //14
    };
    QSqlQuery query, queryContacts;
    QSqlRecord record = query.record();

public:
    typedef enum SQLCommands {
        //sql commands
        createNewTable  = 0,
        insertInto = 1,
        selectAllFrom = 2,
        values = 3,
        where = 4,
        AND = 5,
        update = 6,
        set = 7,
        //sql variables
        idIntegerPrimaryKey = 0,
        nameVar = 1,
        passwordVar = 2,
        tokenVar = 3,
        userText = 4,
        contactVar = 5,
        saveMessageVar = 6,
        ipVar = 7,
        PortVar = 8,
        StatusVar = 9,
        publicKeyVar = 10,
        messageVar = 11,
        userDataVar = 12,
        privetKeyVar = 13,
        toxIDVar = 14,
        friendNameVar = 15,
        //sql name attributes
        name = 0,
        password = 1,
        token = 2,
        user = 3,
        contact = 4,
        saveMessage = 5,
        ip = 6,
        port = 7,
        StatusAtr = 8,
        publicKeyAtr = 9,
        messageAtr = 10,
        userDataAtr = 11,
        privetKeyAtr = 12,
        toxIDAtr = 13,
        friendNameAtr = 14,
        //sql name tables
        users = 0,
        contacts = 1,
        registationList = 2,
        requests = 3
    } commands;
    const QString path = QDir::currentPath() + "/database.db";

public:
    DataBase( );

public:
    void addUser( const QString& nameUser,
                  const QString& passwordUser,
                  const QString& userData,
                  const QString& publicKey,
                  const QString& privetKey,
                  const QString& toxID );
    void saveUserMessage( const QString* nameUser, const QString* message, const QString* nameUserFrom );
    bool registrationUser( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                           const int portUser );
    bool checkUser( const QString& nameUser, const QString& passwordUser, bool loginType );
    bool checkRegUser( const QString& nameUser, const QString& passwordUser, bool loginType );
    bool addInContactList( QString nameUser, QString contactUser );
    QString getPublicKey( const QString& nameUser );
    QString getUserPublicKey( const QString& nameUser );
    QString getContactList( QString nameUser );
    QString getPersonalContactList( QString nameUser );
    QString getUnreadMessage( QString nameUser, QString sender );
    QString getUserData( const QString& nameUser );
    QString getToxID( const QString& nameUser );

public slots:
    void slotUpdateRegistationData( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                                    const int portUser );
    void slotUpdateStatus( const QString& nameUser, const QString& status );
    void slotGetPort( const QString& nameUser );
    void slotAddRequest( const QString& Name, const QString& PublicKey, const QString& Message );
    void slotAddFriend( const QString& Name, const QString& friendUser, const QString& PublicKey );
    void slotSaveData( const QString& Name, const QString& userData );
signals:
    void signalSetPort( const QString&, const QString&, const QString&, const int );
    void signalSetConnect( const QString& name, const QString& password, const QString& ip, const int port );
};

#endif // DATABASE_H
