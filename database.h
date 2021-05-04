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
        " WHERE ",              //4
        " AND ",                //5
        " UPDATE ",              //6
        " SET ",                //7
    };
    QString sqlNameTable[3] = {"users", "contacts", "registationList"};
    QString sqlVariable[10] = {
        """id integer primary key",  //0
        """Name text(255)",          //1
        """Password text(255)",      //2
        """Token text(255)",         //3
        """User text(255)",          //4
        """Contact text(255)",       //5
        """SaveMessage text(255)",   //6
        """IP text(255)",   		 //7
        """PORT text(255)",   		 //8
        """Status text(255)",   		 //9
    };
    QString sqlNameAttributes[9] = {
        "Name",          //0
        "Password",      //1
        "Token",         //2
        "User",          //3
        "Contact",       //4
        "SaveMessage",   //5
        "IP",			 //6
        "PORT",          //7
        "Status",          //8
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
        nameText = 1,
        passwordText = 2,
        tokenText = 3,
        userText = 4,
        contactText = 5,
        saveMessageText = 6,
        ipVar = 7,
        PortVar = 8,
        StatusVar = 9,
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
        //sql name tables
        users = 0,
        contacts = 1,
        registationList = 2
    } commands;
    const QString path = QDir::currentPath() + "/database.db";

public:
    DataBase( );

public:
    void addUser( QString nameUser );
    void saveUserMessage( const QString* nameUser, const QString* message, const QString* nameUserFrom );
    bool registrationUser( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                           const int portUser );
    bool checkUser( const QString& nameUser, const QString& passwordUser );
    bool addInContactList( QString nameUser, QString contactUser );
    QString getContactList( QString nameUser );
    QString getPersonalContactList( QString nameUser );
    QString getUnreadMessage( QString nameUser, QString sender );

public slots:
    void slotUpdateRegistationData( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                                    const int portUser );
    void slotUpdateStatus( const QString& nameUser, const QString& status );
    void slotGetPort( const QString& nameUser );
signals:
    void signalSetPort( const QString&, const QString&, const QString&, const int );
    void signalSetConnect( const QString& name, const QString& password, const QString& ip, const int port );
};

#endif // DATABASE_H
