#include "database.h"

DataBase::DataBase( )
{
    QFileInfo checkDataBase( path );

    if ( !( checkDataBase.exists() && checkDataBase.isFile() ) ) {
        dataBase.setDatabaseName( path );
        dataBase.open();
        query.exec( sqlCommand[createNewTable] + sqlNameTable[users] + "(" + sqlVariable[idIntegerPrimaryKey] + "," +
                    sqlVariable[nameText] + "," + sqlVariable[passwordText] + "," +
                    sqlVariable[tokenText] + ")" );

        query.exec( sqlCommand[createNewTable] + sqlNameTable[contacts] + "(" + sqlVariable[idIntegerPrimaryKey] + "," +
                    sqlVariable[userText] + "," + sqlVariable[contactText] + "," +
                    sqlVariable[saveMessageText] + ")" );
        query.exec( sqlCommand[createNewTable] + sqlNameTable[registationList] + "(" + sqlVariable[idIntegerPrimaryKey] + "," +
                    sqlVariable[nameText] + "," + sqlVariable[passwordText] + "," + sqlVariable[ipVar] + "," +
                    sqlVariable[PortVar] + "," + sqlVariable[StatusVar] + ")" );
        spdlog::info( "Database created" );
    } else {
        dataBase.setDatabaseName( path );
        dataBase.open();
        spdlog::info( "Database is exists" );
    }

}

bool DataBase::checkUser( const QString& nameUser, const QString& passwordUser )
{
    query.exec( sqlCommand[selectAllFrom] + sqlNameTable[registationList] + sqlCommand[where] + sqlNameAttributes[name] +
                " = '" +
                nameUser + "' " + sqlCommand[AND] + sqlNameAttributes[password] + " = '" + passwordUser + "'" );
    bool inDataBase = false;
    record = query.record();
    int portInx = record.indexOf( sqlNameAttributes[port] );

    if ( query.next() ) {
        inDataBase = true;
        spdlog::info( "User in database" );
        emit signalSetPort( NULL, NULL, NULL, query.value( portInx ).toString().toInt() );
    }

    return inDataBase;
}

void DataBase::addUser( QString nameUser )
{
    query.prepare( sqlCommand[insertInto] + sqlNameTable[users] + "(" + sqlNameAttributes[name] + "," +
                   sqlNameAttributes[password] + ")" +
                   sqlCommand[values] + "(" + ":" + sqlNameAttributes[name] + "," + ":" + sqlNameAttributes[password] + ")" );
    query.bindValue( ":" + sqlNameAttributes[name], nameUser );
    QString test = "tests";
    query.bindValue( ":" + sqlNameAttributes[password], test ) ;

    if ( !query.exec() ) {
        spdlog::error( "Error of sql query" );
    } else {
        spdlog::info( "Add user in database" );
    }
}

QString DataBase::getContactList( QString nameUser )
{
    QSqlQuery query, queryContacts;
    QString usersInDataBase;
    int count = 0;
    query.exec( sqlCommand[insertInto] + sqlNameTable[users] );
    QSqlRecord record = query.record();
    int nameIndex = record.indexOf( sqlNameAttributes[contact]  );

    while ( query.next() ) {
        queryContacts.exec( sqlCommand[selectAllFrom] + sqlNameTable[contacts] + sqlCommand[where] + sqlNameAttributes[user]
                            +
                            "= '" + query.value( nameIndex ).toString()
                            + "'" + sqlCommand[AND] + sqlNameAttributes[contact] + " = '" + nameUser + "'" + sqlCommand[AND] +
                            sqlNameAttributes[saveMessage] + " != 'null'" );
        QSqlRecord recordContacts = queryContacts.record();
        int unreadMessageIndex = recordContacts.indexOf( sqlNameAttributes[AND] );

        if ( !queryContacts.exec() ) {
        }

        queryContacts.next();
        QStringList unreadMessage = queryContacts.value( unreadMessageIndex ).toString().split( "%" );

        for ( int i = 0 ; i < unreadMessage.size(); i++ ) {
            count++;
        }

        count--;

        if ( count > 0 ) {
            usersInDataBase += query.value( nameIndex ).toString() + " (" + QString::number( count ) + ")" + "|";
        } else {
            usersInDataBase += query.value( nameIndex ).toString() + "|";
        }

        count = 0;
    }

    return usersInDataBase;
}

QString DataBase::getPersonalContactList( QString nameUser )
{
    QString personalContactsList;
    queryContacts.exec( sqlCommand[selectAllFrom] + sqlNameTable[contacts] + sqlCommand[where] + sqlNameAttributes[user] +
                        " = '" + nameUser + "'" );
    QSqlRecord recordContacts = queryContacts.record();
    int contactIndexContacts = recordContacts.indexOf( sqlNameAttributes[contact]  );
    queryContacts.exec();

    while ( queryContacts.next() ) {
        personalContactsList += queryContacts.value( contactIndexContacts ).toString() + "%";
    }

    return personalContactsList;
}

bool DataBase::addInContactList( QString nameUser, QString contactUser )
{
    queryContacts.exec( sqlCommand[selectAllFrom] + sqlNameTable[contacts] + sqlCommand[where] + sqlNameAttributes[user] +
                        " = '" + nameUser + "' " + sqlCommand[AND] + sqlNameAttributes[contact] + "= '" +
                        contactUser + "'" );

    if ( !queryContacts.exec() ) {
        spdlog::error( "error chech contact" );
    }

    QSqlRecord recordContacts = queryContacts.record();
    int userIndexContacts = recordContacts.indexOf( sqlNameAttributes[contact] );
    queryContacts.next();

    if ( queryContacts.value( userIndexContacts ).isNull() ) {
        query.prepare( sqlCommand[insertInto] + sqlNameTable[contacts] + "(" + sqlNameAttributes[contact] + "," +
                       sqlNameAttributes[user]  +
                       ")"
                       + sqlCommand[values] + "(" + ":" + sqlNameAttributes[contact] + "," + ":" + sqlNameAttributes[user] + ")" );

        query.bindValue( ":" + sqlNameAttributes[contact],  contactUser );
        query.bindValue( ":" + sqlNameAttributes[user],  nameUser );

        if ( !query.exec() ) {
            spdlog::error( "error add contact" );
        } else {
            spdlog::info( "successful add contact" );
        }

        return true;
    } else {
        spdlog::info( "The user is already in the contact list" );
        return false;
    }
}

void DataBase::saveUserMessage( const QString* nameUser, const QString* message, const QString* nameUserFrom )
{
    QSqlQuery queryContacts( sqlCommand[selectAllFrom] + sqlNameTable[contacts] + sqlCommand[where] +
                             sqlNameAttributes[name] + " ='" + *nameUser + "'" +
                             sqlCommand[AND] + sqlNameAttributes[contact] + " ='" +
                             *nameUserFrom + "'" );
    QSqlRecord recordContacts = queryContacts.record();
    int userIndexContacts = recordContacts.indexOf( sqlNameAttributes[user]  );
    int pastMessagesIndexContacts = recordContacts.indexOf( sqlNameAttributes[saveMessage]  );

    if ( !queryContacts.exec() ) {
    }

    queryContacts.next();

    if (  !queryContacts.value( userIndexContacts ).isNull() ) {
        QString MessageforDataBase = queryContacts.value( pastMessagesIndexContacts ).toString() + *message + "%";
        queryContacts.prepare( sqlCommand[update] + sqlNameTable[contacts] + sqlCommand[set] + sqlNameAttributes[saveMessage] +
                               "=:" +
                               sqlNameAttributes[saveMessage] + sqlCommand[where] + sqlNameAttributes[user] + "=:" + sqlNameAttributes[user] +
                               sqlCommand[AND] + sqlNameAttributes[contact] + "=:" + sqlNameAttributes[contact] );
        queryContacts.bindValue( ":" + sqlNameAttributes[user],
                                 nameUser );
        queryContacts.bindValue( ":" + sqlNameAttributes[contact],
                                 nameUserFrom );
        queryContacts.bindValue( ":" + sqlNameAttributes[saveMessage],
                                 MessageforDataBase );

        if ( !queryContacts.exec() ) {
            spdlog::error( "Error of sql query in Contacts" );
        }
    }
}

bool DataBase::registrationUser( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                                 const int portUser )
{
    query.exec( sqlCommand[selectAllFrom] + sqlNameTable[registationList] + sqlCommand[where] + sqlNameAttributes[name] +
                " = '" + nameUser + "'" );
    record = query.record();
    int nameIndex = record.indexOf( sqlNameAttributes[name] );
    query.next();

    if ( !query.value( nameIndex ).isNull()  ) {
        return false;
    } else {
        query.prepare( sqlCommand[insertInto] + sqlNameTable[registationList] + "(" + sqlNameAttributes[name] + "," +
                       sqlNameAttributes[password] + "," + sqlNameAttributes[ip] + "," + sqlNameAttributes[port] + ")" + sqlCommand[values] +
                       "(" + ":" + sqlNameAttributes[name] + "," + ":" + sqlNameAttributes[password] + "," + ":" + sqlNameAttributes[ip] + ","
                       + ":" + sqlNameAttributes[port] + ")" );
        query.bindValue( ":" + sqlNameAttributes[name], nameUser );
        query.bindValue( ":" + sqlNameAttributes[password], passwordUser );
        query.bindValue( ":" + sqlNameAttributes[ip], ipUser );
        query.bindValue( ":" + sqlNameAttributes[port], portUser );

        if ( !query.exec() ) {
            spdlog::error( "Error of registation user" );
        } else {
            spdlog::info( "User registation successful" );
        }

        return true;
    }
}

QString DataBase::getUnreadMessage( QString nameUser, QString sender )
{
    QString unreadMessages;
    queryContacts.exec( sqlCommand[selectAllFrom] + sqlNameTable[contacts] + sqlCommand[where] + sqlNameAttributes[user] +
                        " = '" + sender + "'" + sqlCommand[AND] + sqlNameAttributes[contact] + " = '" +
                        nameUser + "'" );
    QSqlRecord recordContacts = queryContacts.record();
    int pastMessagesIndexContacts = recordContacts.indexOf( sqlNameAttributes[saveMessage]  );

    if ( !queryContacts.exec() ) {
    }

    queryContacts.next();
    unreadMessages = queryContacts.value( pastMessagesIndexContacts ).toString();

    queryContacts.prepare( sqlCommand[update] + sqlNameTable[contacts] + sqlCommand[set] +  sqlNameAttributes[saveMessage] +
                           "=:"
                           +  sqlNameAttributes[saveMessage] + sqlCommand[where] + sqlNameAttributes[user] + "=:" + sqlNameAttributes[user] +
                           sqlCommand[AND] +
                           sqlNameAttributes[contact] + "=:" +
                           sqlNameAttributes[contact]
                         );
    queryContacts.bindValue( ":" + sqlNameAttributes[saveMessage], "" );
    queryContacts.bindValue( ":" + sqlNameAttributes[contact],  nameUser );
    queryContacts.bindValue( ":" + sqlNameAttributes[user],  sender );

    if ( !queryContacts.exec() ) {
        spdlog::error( "Error of sql query in Contacts" );
    }

    return unreadMessages;
}

void DataBase::slotUpdateRegistationData( const QString& nameUser, const QString& passwordUser, const QString& ipUser,
                                          const int portUser )
{
    registrationUser( nameUser, passwordUser, ipUser, portUser );
}

void DataBase::slotUpdateStatus( const QString& nameUser, const QString& status )
{
    query.prepare( sqlCommand[update] + sqlNameTable[registationList] + sqlCommand[set] + sqlNameAttributes[StatusAtr] +
                   "=:" + sqlNameAttributes[StatusAtr]
                   + sqlCommand[where] + sqlNameAttributes[name] + "=:" + sqlNameAttributes[name]
                 );
    query.bindValue( ":" + sqlNameAttributes[StatusAtr],
                     status );
    query.bindValue( ":" + sqlNameAttributes[name],
                     nameUser );

    if ( !query.exec() ) {
        spdlog::error( "Error of sql query in update status" );
        spdlog::error(  query.lastError().text().toLocal8Bit() );
    }
}

void DataBase::slotGetPort( const QString& nameUser )
{
    query.exec( sqlCommand[selectAllFrom] + sqlNameTable[registationList] + sqlCommand[where] + sqlNameAttributes[name]
                + "= '" + nameUser + "'"
              );
    record = query.record();
    int portInx = record.indexOf( sqlNameAttributes[port] );
    query.next();
    emit signalSetConnect( nameUser, "", "", query.value( portInx ).toString().toInt() );
}
