#ifndef CONVERTSTRING_H
#define CONVERTSTRING_H

#include <QObject>

class convertString : public QObject
{
    Q_OBJECT
public:
    explicit convertString( const QString& text );
    explicit convertString( const QByteArray& text );

    convertString( const uint8_t* text, size_t length );

    const uint8_t* data() const;
    size_t size() const;
    QString getQString() const;
    QByteArray getBytes() const;

private:
    QByteArray string;

};

#endif // CONVERTSTRING_H
