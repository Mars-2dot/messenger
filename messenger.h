#ifndef MESSENGER_H
#define MESSENGER_H

#include "./ui_messenger.h"

#include <QMainWindow>

class Messenger : public QMainWindow, private Ui::Messenger
{
    Q_OBJECT

public:
    Messenger(QWidget *parent = nullptr);
    ~Messenger();
};
#endif // MESSENGER_H
