#ifndef CONVERTSTRING_H
#define CONVERTSTRING_H

#include <QObject>
#include <limits>

#include "qtincludes.h"

class convertString : public QObject
{
    Q_OBJECT
private:
    QByteArray string;
    typedef enum textType {
        toxId = TOX_ADDRESS_SIZE,
        toxPublicKey = TOX_PUBLIC_KEY_SIZE,
        toxPrivetKey = TOX_SECRET_KEY_SIZE,
    } textType;

public:
    explicit convertString( const QString& text );
    explicit convertString( const QByteArray& text );

    convertString( const uint8_t* text, size_t length );
    convertString( const uint8_t* text, textType type );
    convertString( const uint8_t* data );

    const uint8_t* data() const;
    size_t size() const;
    QString getQString() const;
    QByteArray getBytes() const;
    uint8_t* getDataFromQString() const;
};

#endif // CONVERTSTRING_H
