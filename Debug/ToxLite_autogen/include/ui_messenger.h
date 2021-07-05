/********************************************************************************
** Form generated from reading UI file 'messenger.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSENGER_H
#define UI_MESSENGER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCommandLinkButton>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_messenger
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *login;
    QVBoxLayout *verticalLayout;
    QWidget *widget_1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_7;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QLineEdit *login_username;
    QLabel *label_6;
    QLineEdit *login_password;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *login_button;
    QPushButton *login_signup;
    QLabel *login_error;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QWidget *signUp;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_9;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLineEdit *signup_username;
    QLabel *label_4;
    QLineEdit *signup_password;
    QLabel *label_5;
    QLineEdit *signup_confirm;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *signup_button;
    QPushButton *signup_login;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_4;
    QWidget *main;
    QVBoxLayout *verticalLayout_6;
    QSplitter *splitter;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *add_button;
    QPushButton *contact_button;
    QLineEdit *search;
    QListWidget *listUser;
    QWidget *layoutWidget_3;
    QFormLayout *formLayout_2;
    QLabel *chat;
    QLineEdit *input;
    QPushButton *send;
    QCommandLinkButton *copyToxId;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *messenger)
    {
        if (messenger->objectName().isEmpty())
            messenger->setObjectName(QString::fromUtf8("messenger"));
        messenger->resize(825, 620);
        messenger->setStyleSheet(QString::fromUtf8("background: rgb(25, 25, 25);\n"
"color:black;"));
        messenger->setToolButtonStyle(Qt::ToolButtonIconOnly);
        centralwidget = new QWidget(messenger);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8("background: rgb(38, 39, 40);"));
        login = new QWidget();
        login->setObjectName(QString::fromUtf8("login"));
        verticalLayout = new QVBoxLayout(login);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        widget_1 = new QWidget(login);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_1->sizePolicy().hasHeightForWidth());
        widget_1->setSizePolicy(sizePolicy);
        widget_1->setAutoFillBackground(false);
        widget_1->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_2 = new QHBoxLayout(widget_1);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(98, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(widget_1);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(551, 21));
        label_2->setMaximumSize(QSize(551, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("Open Sans Light"));
        font.setPointSize(13);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"        font: 13pt \"Open Sans Light\";\n"
"        color:rgb(215, 213, 217);\n"
"}"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_2->setMargin(0);
        label_2->setIndent(0);

        verticalLayout_5->addWidget(label_2);

        login_username = new QLineEdit(widget_1);
        login_username->setObjectName(QString::fromUtf8("login_username"));
        login_username->setMinimumSize(QSize(551, 35));
        login_username->setMaximumSize(QSize(551, 35));
        login_username->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"        font: 11pt \"Open Sans\";\n"
"        border:1px solid  grey ;\n"
"        min-height: 33px;\n"
"        background: white;\n"
"       color:black;\n"
"}\n"
"\n"
"QLineEdit:focus\n"
"{\n"
"        border:1px solid  #161626 ;\n"
"} "));
        login_username->setMaxLength(20);

        verticalLayout_5->addWidget(login_username);

        label_6 = new QLabel(widget_1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(551, 21));
        label_6->setMaximumSize(QSize(551, 21));
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"        font: 13pt \"Open Sans Light\";\n"
"color:rgb(215, 213, 217)\n"
";\n"
"}"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_6->setIndent(0);

        verticalLayout_5->addWidget(label_6);

        login_password = new QLineEdit(widget_1);
        login_password->setObjectName(QString::fromUtf8("login_password"));
        login_password->setMinimumSize(QSize(551, 35));
        login_password->setMaximumSize(QSize(551, 35));
        login_password->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"        font: 11pt \"Open Sans\";\n"
"        border:1px solid  grey ;\n"
"        min-height: 33px;\n"
"        background: white;\n"
"        color:black;\n"
"}\n"
"\n"
"QLineEdit:focus\n"
"{\n"
"        border:1px solid  #161626 ;\n"
"} "));
        login_password->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        login_password->setMaxLength(30);
        login_password->setEchoMode(QLineEdit::Password);

        verticalLayout_5->addWidget(login_password);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(-1, -1, -1, 5);
        login_button = new QPushButton(widget_1);
        login_button->setObjectName(QString::fromUtf8("login_button"));
        login_button->setStyleSheet(QString::fromUtf8("QPushButton:enabled\n"
"{\n"
"                font: 13pt \"Open Sans Semibold\";\n"
"                background:  #73739b;\n"
"                border-radius: 3px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"                outline: 0;\n"
"            color: white;\n"
"}\n"
"\n"
"QPushButton:disable\n"
"{\n"
"                font: 13pt \"Open Sans Semibold\";\n"
"                background:  gray;\n"
"                border-radius: 3px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"                outline: 0;\n"
"            color: white;\n"
"}\n"
"\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #7a7aa1;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
" {\n"
"        background: #8f8fb3;\n"
"}"));

        horizontalLayout_5->addWidget(login_button);

        login_signup = new QPushButton(widget_1);
        login_signup->setObjectName(QString::fromUtf8("login_signup"));
        login_signup->setEnabled(true);
        login_signup->setStyleSheet(QString::fromUtf8("QPushButton:enabled\n"
"{\n"
"                font: 13pt \"Open Sans Semibold\";\n"
"                background:  #73739b;\n"
"                border-radius: 3px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"                outline: 0;\n"
"                color: white;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #7a7aa1;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
" {\n"
"        background: #8f8fb3;\n"
"}"));

        horizontalLayout_5->addWidget(login_signup);


        verticalLayout_5->addLayout(horizontalLayout_5);

        login_error = new QLabel(widget_1);
        login_error->setObjectName(QString::fromUtf8("login_error"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(login_error->sizePolicy().hasHeightForWidth());
        login_error->setSizePolicy(sizePolicy1);
        login_error->setMinimumSize(QSize(551, 21));
        login_error->setMaximumSize(QSize(551, 21));
        login_error->setStyleSheet(QString::fromUtf8("font: 10pt \"Open Sans Light\";\n"
"color:rgb(215, 213, 217);"));
        login_error->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(login_error);


        verticalLayout_7->addLayout(verticalLayout_5);

        verticalSpacer_3 = new QSpacerItem(20, 45, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_3);


        horizontalLayout_2->addLayout(verticalLayout_7);

        horizontalSpacer_2 = new QSpacerItem(97, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(widget_1);

        stackedWidget->addWidget(login);
        signUp = new QWidget();
        signUp->setObjectName(QString::fromUtf8("signUp"));
        verticalLayout_2 = new QVBoxLayout(signUp);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(signUp);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(698, 21));
        label_3->setMaximumSize(QSize(698, 21));
        label_3->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"        font: 13pt \"Open Sans Light\";\n"
" color: rgb(215, 213, 217);\n"
"\n"
"}"));

        verticalLayout_4->addWidget(label_3);

        signup_username = new QLineEdit(signUp);
        signup_username->setObjectName(QString::fromUtf8("signup_username"));
        signup_username->setMinimumSize(QSize(698, 35));
        signup_username->setMaximumSize(QSize(698, 35));
        signup_username->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"        font: 11pt \"Open Sans\";\n"
"        border:1px solid  grey ;\n"
"        min-height: 33px;\n"
"        background: white;\n"
"}\n"
"\n"
"QLineEdit:focus\n"
"{\n"
"        border:1px solid  #161626 ;\n"
"} "));
        signup_username->setMaxLength(20);

        verticalLayout_4->addWidget(signup_username);

        label_4 = new QLabel(signUp);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(698, 21));
        label_4->setMaximumSize(QSize(698, 21));
        label_4->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"        font: 13pt \"Open Sans Light\";\n"
"		color:rgb(215, 213, 217)\n"
"}"));

        verticalLayout_4->addWidget(label_4);

        signup_password = new QLineEdit(signUp);
        signup_password->setObjectName(QString::fromUtf8("signup_password"));
        signup_password->setMinimumSize(QSize(698, 35));
        signup_password->setMaximumSize(QSize(698, 35));
        signup_password->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"        font: 11pt \"Open Sans\";\n"
"        border:1px solid  grey ;\n"
"        min-height: 33px;\n"
"        background: white;\n"
"}\n"
"\n"
"QLineEdit:focus\n"
"{\n"
"        border:1px solid  #161626 ;\n"
"} "));
        signup_password->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        signup_password->setMaxLength(30);
        signup_password->setEchoMode(QLineEdit::Password);

        verticalLayout_4->addWidget(signup_password);

        label_5 = new QLabel(signUp);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(698, 21));
        label_5->setMaximumSize(QSize(698, 21));
        label_5->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"        font: 13pt \"Open Sans Light\";\n"
"		color:rgb(215, 213, 217)\n"
"}"));

        verticalLayout_4->addWidget(label_5);

        signup_confirm = new QLineEdit(signUp);
        signup_confirm->setObjectName(QString::fromUtf8("signup_confirm"));
        signup_confirm->setMinimumSize(QSize(698, 35));
        signup_confirm->setMaximumSize(QSize(698, 35));
        signup_confirm->setStyleSheet(QString::fromUtf8("QLineEdit\n"
"{\n"
"        font: 11pt \"Open Sans\";\n"
"        border:1px solid  grey ;\n"
"        min-height: 33px;\n"
"        background: white;\n"
"}\n"
"\n"
"QLineEdit:focus\n"
"{\n"
"        border:1px solid  #161626 ;\n"
"} "));
        signup_confirm->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);
        signup_confirm->setMaxLength(30);
        signup_confirm->setEchoMode(QLineEdit::Password);

        verticalLayout_4->addWidget(signup_confirm);


        verticalLayout_8->addLayout(verticalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        signup_button = new QPushButton(signUp);
        signup_button->setObjectName(QString::fromUtf8("signup_button"));
        signup_button->setMinimumSize(QSize(345, 35));
        signup_button->setMaximumSize(QSize(345, 35));
        signup_button->setStyleSheet(QString::fromUtf8("QPushButton:enabled\n"
"{\n"
"                font: 13pt \"Open Sans Semibold\";\n"
"                background:  #73739b;\n"
"                border-radius: 3px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"            outline: 0;\n"
"                color: white;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #7a7aa1;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
" {\n"
"        background: #8f8fb3;\n"
"}"));

        horizontalLayout_6->addWidget(signup_button);

        signup_login = new QPushButton(signUp);
        signup_login->setObjectName(QString::fromUtf8("signup_login"));
        signup_login->setMinimumSize(QSize(345, 35));
        signup_login->setMaximumSize(QSize(345, 35));
        signup_login->setStyleSheet(QString::fromUtf8("QPushButton:enabled\n"
"{\n"
"                font: 13pt \"Open Sans Semibold\";\n"
"                background:  #73739b;\n"
"                border-radius: 3px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"                outline: 0;\n"
"                color: white;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #7a7aa1;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
" {\n"
"        background: #8f8fb3;\n"
"}"));

        horizontalLayout_6->addWidget(signup_login);


        verticalLayout_8->addLayout(horizontalLayout_6);


        horizontalLayout_7->addLayout(verticalLayout_8);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);


        verticalLayout_9->addLayout(horizontalLayout_7);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_4);


        verticalLayout_2->addLayout(verticalLayout_9);

        stackedWidget->addWidget(signUp);
        main = new QWidget();
        main->setObjectName(QString::fromUtf8("main"));
        verticalLayout_6 = new QVBoxLayout(main);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        splitter = new QSplitter(main);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        add_button = new QPushButton(layoutWidget);
        add_button->setObjectName(QString::fromUtf8("add_button"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(add_button->sizePolicy().hasHeightForWidth());
        add_button->setSizePolicy(sizePolicy2);
        add_button->setMinimumSize(QSize(50, 50));
        add_button->setMaximumSize(QSize(100, 50));
        add_button->setBaseSize(QSize(101, 51));
        add_button->setToolTipDuration(-1);
        add_button->setStyleSheet(QString::fromUtf8("QPushButton:enabled\n"
"{\n"
"                background: #1c1c37;\n"
"                min-width: 40px;\n"
"                min-height:40px;\n"
"                border-radius: 0px;\n"
"                padding: 5px;\n"
"                outline: 0px;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #3D3D5A;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"           background: #585879;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        add_button->setIcon(icon);
        add_button->setIconSize(QSize(130, 130));
        add_button->setFlat(false);

        horizontalLayout_8->addWidget(add_button);

        contact_button = new QPushButton(layoutWidget);
        contact_button->setObjectName(QString::fromUtf8("contact_button"));
        sizePolicy2.setHeightForWidth(contact_button->sizePolicy().hasHeightForWidth());
        contact_button->setSizePolicy(sizePolicy2);
        contact_button->setMinimumSize(QSize(50, 50));
        contact_button->setMaximumSize(QSize(100, 50));
        contact_button->setBaseSize(QSize(101, 51));
        contact_button->setStyleSheet(QString::fromUtf8(" QPushButton:enabled\n"
"{\n"
"                background: #1c1c37;\n"
"                min-width: 40px;\n"
"                min-height:40px;\n"
"                border-radius: 0px;\n"
"                padding: 5px;\n"
"                outline: 0px;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #3D3D5A;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"           background: #585879;\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/chat.png"), QSize(), QIcon::Normal, QIcon::Off);
        contact_button->setIcon(icon1);
        contact_button->setIconSize(QSize(130, 130));

        horizontalLayout_8->addWidget(contact_button);


        verticalLayout_3->addLayout(horizontalLayout_8);

        search = new QLineEdit(layoutWidget);
        search->setObjectName(QString::fromUtf8("search"));
        search->setStyleSheet(QString::fromUtf8("border: rgb(215, 213, 217);\n"
"background: rgb(54, 57, 63);\n"
"color:rgb(215, 213, 217);\n"
""));

        verticalLayout_3->addWidget(search);

        listUser = new QListWidget(layoutWidget);
        listUser->setObjectName(QString::fromUtf8("listUser"));
        listUser->setStyleSheet(QString::fromUtf8("border:rgb(38, 39, 40);\n"
"color:rgb(215, 213, 217)"));

        verticalLayout_3->addWidget(listUser);

        splitter->addWidget(layoutWidget);
        layoutWidget_3 = new QWidget(splitter);
        layoutWidget_3->setObjectName(QString::fromUtf8("layoutWidget_3"));
        formLayout_2 = new QFormLayout(layoutWidget_3);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 6, 6);
        chat = new QLabel(layoutWidget_3);
        chat->setObjectName(QString::fromUtf8("chat"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(chat->sizePolicy().hasHeightForWidth());
        chat->setSizePolicy(sizePolicy3);
        chat->setMinimumSize(QSize(491, 471));
        chat->setAutoFillBackground(false);
        chat->setStyleSheet(QString::fromUtf8(" background:rgb(54, 57, 63);\n"
"color:rgb(215, 213, 217)"));
        chat->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        chat->setWordWrap(true);

        formLayout_2->setWidget(1, QFormLayout::SpanningRole, chat);

        input = new QLineEdit(layoutWidget_3);
        input->setObjectName(QString::fromUtf8("input"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(input->sizePolicy().hasHeightForWidth());
        input->setSizePolicy(sizePolicy4);
        input->setMinimumSize(QSize(530, 35));
        input->setStyleSheet(QString::fromUtf8(" background:rgb(54, 57, 63);\n"
"color: rgb(215, 213, 217);\n"
"border: rgb(215, 213, 217);"));
        input->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, input);

        send = new QPushButton(layoutWidget_3);
        send->setObjectName(QString::fromUtf8("send"));
        send->setEnabled(false);
        sizePolicy4.setHeightForWidth(send->sizePolicy().hasHeightForWidth());
        send->setSizePolicy(sizePolicy4);
        send->setMaximumSize(QSize(50, 35));
        send->setStyleSheet(QString::fromUtf8(" QPushButton:enabled\n"
"{\n"
"                border-image: url(:/Resources/send.png);\n"
"                background:  #73739b;\n"
"                border-radius: 3px;\n"
"                min-width: 40px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"                outline: 0px;\n"
"}\n"
"\n"
" QPushButton:disabled\n"
"{\n"
"                border-image: url(:/Resources/send_disabled.png);\n"
"                background:  #73739b;\n"
"                border-radius: 3px;\n"
"                min-width: 40px;\n"
"                min-height:25px;\n"
"                padding: 5px;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"                background: #7a7aa1;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
" {\n"
"        background: #8f8fb3;\n"
"}"));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, send);

        copyToxId = new QCommandLinkButton(layoutWidget_3);
        copyToxId->setObjectName(QString::fromUtf8("copyToxId"));
        copyToxId->setStyleSheet(QString::fromUtf8("color: blue"));

        formLayout_2->setWidget(0, QFormLayout::SpanningRole, copyToxId);

        splitter->addWidget(layoutWidget_3);

        verticalLayout_6->addWidget(splitter);

        stackedWidget->addWidget(main);

        horizontalLayout->addWidget(stackedWidget);

        messenger->setCentralWidget(centralwidget);
        menubar = new QMenuBar(messenger);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 825, 20));
        messenger->setMenuBar(menubar);
        statusbar = new QStatusBar(messenger);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        messenger->setStatusBar(statusbar);

        retranslateUi(messenger);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(messenger);
    } // setupUi

    void retranslateUi(QMainWindow *messenger)
    {
        messenger->setWindowTitle(QCoreApplication::translate("messenger", "messenger", nullptr));
        label_2->setText(QCoreApplication::translate("messenger", "Username:", nullptr));
        login_username->setText(QCoreApplication::translate("messenger", "User", nullptr));
        label_6->setText(QCoreApplication::translate("messenger", "Password:", nullptr));
        login_password->setText(QCoreApplication::translate("messenger", "1111", nullptr));
        login_button->setText(QCoreApplication::translate("messenger", "Log in", nullptr));
        login_signup->setText(QCoreApplication::translate("messenger", "Sign up", nullptr));
        login_error->setText(QCoreApplication::translate("messenger", "Connection...", nullptr));
        label_3->setText(QCoreApplication::translate("messenger", "Username:", nullptr));
        signup_username->setText(QCoreApplication::translate("messenger", "User", nullptr));
        label_4->setText(QCoreApplication::translate("messenger", "Password:", nullptr));
        signup_password->setText(QCoreApplication::translate("messenger", "111", nullptr));
        label_5->setText(QCoreApplication::translate("messenger", "Confirm password:", nullptr));
        signup_confirm->setText(QCoreApplication::translate("messenger", "111", nullptr));
        signup_button->setText(QCoreApplication::translate("messenger", "Ok", nullptr));
        signup_login->setText(QCoreApplication::translate("messenger", "Cancel", nullptr));
        add_button->setText(QString());
        contact_button->setText(QString());
        chat->setText(QString());
        copyToxId->setText(QCoreApplication::translate("messenger", "Your tox ID(click to copy):", nullptr));
    } // retranslateUi

};

namespace Ui {
    class messenger: public Ui_messenger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSENGER_H
