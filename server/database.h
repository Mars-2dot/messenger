#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>

#include "qtincludes.h"

class DataBase: public QObject
{
    Q_OBJECT

private:
    QSqlDatabase dataBase = QSqlDatabase::addDatabase( "QSQLITE" );
    QString sqlCommand[8] = {
        "create table ",        //0
        "INSERT INTO ",         //1
        "SELECT * FROM ",       //2
        "VALUES ",              //3
        " WHERE ",              //4
        " AND ",                //5
        "UPDATE ",              //6
        " SET ",                //7
    };
    QString sqlNameTable[2] = {"users", "contacts"};
    QString sqlVariable[7] = {
        """id integer primary key",  //0
        """Name text(255)",          //1
        """Password text(255)",      //2
        """Token text(255)",         //3
        """User text(255)",          //4
        """Contact text(255)",       //5
        """SaveMessage text(255)",   //6
    };
    QString sqlNameAttributes[6] = {
        "Name",         //0
        "Password",     //1
        "Token",        //2
        "User",         //3
        "Contact",      //4
        "SaveMessage"   //5
    };
    QSqlQuery query, queryContacts;
    QSqlRecord record = query.record();
public:
    typedef enum SQLCommands {
        createNewTable  = 0,
        insertInto = 1,
        selectAllFrom = 2,
        values = 3,
        where = 4,
        AND = 5,
        update = 6,
        set = 7,
        idIntegerPrimaryKey = 0,
        nameText = 1,
        passwordText = 2,
        tokenText = 3,
        userText = 4,
        contactText = 5,
        saveMessageText = 6,
        name = 0,
        password = 1,
        token = 2,
        user = 3,
        contact = 4,
        saveMessage = 5,
        users = 0,
        contacts = 1
    } commands;
    const QString path = QDir::currentPath() + "/database.db";

public:
    DataBase( );

public:
    void addUser( QString nameUser );
    void saveUserMessage( const QString* nameUser, const QString* message, const QString* nameUserFrom );
    bool checkUser( QString nameUser );
    bool addInContactList( QString nameUser, QString contactUser );
    QString getContactList( QString nameUser );
    QString getPersonalContactList( QString nameUser );
    QString getUnreadMessage( QString nameUser, QString sender );

};

#endif // DATABASE_H
