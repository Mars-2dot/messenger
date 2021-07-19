#ifndef CORE_H
#define CORE_H

#pragma once
#include "qtincludes.h"
#include "convertstring.h"
#include "database.h"

class core;

using corePtr = std::unique_ptr<core>;

class core : public QObject
{
    Q_OBJECT

private:
    Tox* tox ;
    DataBase* db = new DataBase;
    QFile toxSave;
    Tox_Options* options = tox_options_new( NULL );

    typedef struct DHT_node {
        const char* ip;
        uint16_t port;
        const char key_hex[TOX_PUBLIC_KEY_SIZE * 2 + 1];
    } DHT_node;

    struct ToxUser {
        QString ToxUser;
        QString Name;
        QString Password;
        QString publicKey;
        QString privateKey;
        QString id;
    };
    ToxUser toxUser;

    QByteArray data;

public:
    static corePtr makeCore( const QByteArray& savedata );

public:
    core( );
    ~core();
    void start( );
    void login( const QString& name, const QString& password, const bool loginType );
private:
    static void friendRequestCb( Tox* tox, const uint8_t* public_key, const uint8_t* message, size_t length,
                                 void* Core );
    static void friendMessageCb( Tox* tox, uint32_t friend_number, TOX_MESSAGE_TYPE type, const uint8_t* message,
                                 size_t length, void* Core );
    static void selfConnectionStatusCb( Tox* tox, TOX_CONNECTION connection_status, void* Core );
    static void toxFriendConnectionStatusCb( Tox* tox, uint32_t friend_number, TOX_CONNECTION connection_status,
                                             void* Core );
    static void toxLogCb( Tox* tox, TOX_LOG_LEVEL level, const char* file, uint32_t line, const char* func,
                          const char* message, void* Core );
    static void toxFriendNameCb( Tox* tox, uint32_t friend_number, const uint8_t* name, size_t length,
                                 void* Core );
    static void toxFriendStatusMessageCb( Tox* tox, uint32_t friend_number, const uint8_t* message, size_t length,
                                          void* Core );
    static void toxFriendStatusCb( Tox* tox, uint32_t friend_number, TOX_USER_STATUS status, void* Core );
    static void toxFriendTypingCb( Tox* tox, uint32_t friend_number, bool is_typing, void* Core );
    static void toxFriendReadReceiptCb( Tox* tox, uint32_t friend_number, uint32_t message_id, void* Core );
    static void toxFileRecvControlCb( Tox* tox, uint32_t friend_number, uint32_t file_number,
                                      TOX_FILE_CONTROL control,
                                      void* Core );
    static void toxFileChunkRequestCb( Tox* tox, uint32_t friend_number, uint32_t file_number, uint64_t position,
                                       size_t length, void* Core );
    static void toxFileRecvCb( Tox* tox, uint32_t friend_number, uint32_t file_number, uint32_t kind,
                               uint64_t file_size,
                               const uint8_t* filename, size_t filename_length, void* Core );
    static void toxFileRecvChunkCb( Tox* tox, uint32_t friend_number, uint32_t file_number, uint64_t position,
                                    const uint8_t* data, size_t length, void* Core );
    static void toxConferenceInviteCb( Tox* tox, uint32_t friend_number, TOX_CONFERENCE_TYPE type,
                                       const uint8_t* cookie,
                                       size_t length, void* Core );
    static void toxConferenceConnectedCb( Tox* tox, uint32_t conference_number, void* Core );
    static void toxConferenceMessageCb( Tox* tox, uint32_t conference_number, uint32_t peer_number,
                                        TOX_MESSAGE_TYPE type, const uint8_t* message, size_t length, void* Core );
    static void toxConferenceTitleCb( Tox* tox, uint32_t conference_number, uint32_t peer_number, const uint8_t* title,
                                      size_t length, void* Core );
    static void toxConferencePeerNameCb( Tox* tox, uint32_t conference_number, uint32_t peer_number,
                                         const uint8_t* name, size_t length, void* Core );
    static void toxConferencePeerListChangedCb( Tox* tox, uint32_t conference_number, void* Core );
    static void toxFriendLossyPacketCb( Tox* tox, uint32_t friend_number, const uint8_t* data, size_t length,
                                        void* Core );
    static void toxFriendLosslessPacketCb( Tox* tox, uint32_t friend_number, const uint8_t* data, size_t length,
                                           void* Core );
    static const QString toxGetFriendName( Tox* tox, uint32_t friendNumber, void* core, TOX_ERR_FRIEND_QUERY* error );

private:
    static bool parseError( Tox_Err_Conference_Title error, int line );
    static bool parseError( Tox_Err_Friend_Send_Message error, int line );
    static bool parseError( Tox_Err_Conference_Send_Message error, int line );
    static bool parseError( Tox_Err_Conference_Peer_Query error, int line );
    static bool parseError( Tox_Err_Conference_Get_Type error, int line );
    static bool parseError( Tox_Err_Conference_Invite error, int line );
    static bool parseError( Tox_Err_Conference_New error, int line );
    static bool parseError( Tox_Err_Friend_By_Public_Key error, int line );
    static bool parseError( Tox_Err_Bootstrap error, int line );
    static bool parseError( Tox_Err_Friend_Add error, int line );
    static bool parseError( Tox_Err_Set_Info error, int line );
    static bool parseError( Tox_Err_Friend_Query error, int line );
    static bool parseError( Tox_Err_Friend_Get_Public_Key error, int line );
    static bool parseError( Tox_Err_Friend_Get_Last_Online error, int line );
    static bool parseError( Tox_Err_Set_Typing error, int line );
    static bool parseError( Tox_Err_Conference_Delete error, int line );

private:
    void toxCallbacks();
    void toxBootstrap( );
    void signUp( const QString& Name, const QString& Password );
    void signIn( const QString& Name, const QString& Password );
    void saveData( const QString& Name, const QString& Password );
    const QString& getToxId( Tox* tox );

public slots:
    void slotAcceptFriendRequest( const QString& message );
    void slotSendMessage( const QString& message, const QString& name );
    void slotAddFriend( const QString& Name );
    void slotCheckUser( const QString& name, const QString& password, const bool loginType );
    void slotGetListFriends( void* core );
    void slotSetStatus( TOX_USER_STATUS  status );
    void slotFriendAdd( const QString& friendID, const QString& message );
    void slotUpdateUserData();

signals:
    void signalToxData( const QString&, const QString&, const QString& );
    void signalSetId( const QString& );
    void signalAddFriend( const QString& Name, const QString& friendUser, const QString& PublicKey,
                          const QString& UserData, const QString& numberFriend );
    void signalClientInfo( uint32_t, TOX_MESSAGE_TYPE, const uint8_t*, size_t );
    void signalSaveData( QByteArray& );
    void signalSetStatus( int );
    void signalSendMessage( const QString& name, const QString& message, uint32_t number );
    void signalFriendRequest(  const QString& message );
    void signalSendFriendList( QStringList& friendList );
    void signalDataBaseAddRequst( const QString& Name, const QString& PublicKey, const QString& Message );
    void signalCheckUser( const QString& nameUser, const QString& passwordUser, const bool loginType );
    void signalCheckSuccessful( const QString& name, const QString& password, const bool loginType );
    void signalUpdateUserData();
    void signalSaveUserData( const QString& Name, const QString& userData );
    void signalError( int errorNumber );
};

#endif // CORE_H
