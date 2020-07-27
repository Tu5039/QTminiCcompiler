/********************************************************************************
** Form generated from reading UI file 'QTminiCcompiler.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTMINICCOMPILER_H
#define UI_QTMINICCOMPILER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QTminiCcompilerClass
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *CodePathEdit;
    QPushButton *openCodeBtn;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *GrammarPathEdit;
    QPushButton *openGrammarBtn;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *lexicalAnaBtn;
    QPushButton *syntacticAnaBtn;
    QPushButton *semanticAnaBtn;
    QPushButton *genCodeBtn;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QPlainTextEdit *CodeText;
    QVBoxLayout *verticalLayout;
    QLabel *label_4;
    QPlainTextEdit *plainTextEdit;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QTminiCcompilerClass)
    {
        if (QTminiCcompilerClass->objectName().isEmpty())
            QTminiCcompilerClass->setObjectName(QString::fromUtf8("QTminiCcompilerClass"));
        QTminiCcompilerClass->resize(673, 630);
        QTminiCcompilerClass->setMinimumSize(QSize(540, 630));
        actionOpen = new QAction(QTminiCcompilerClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionExit = new QAction(QTminiCcompilerClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        centralWidget = new QWidget(QTminiCcompilerClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMinimumSize(QSize(540, 600));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(35, 0));
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        CodePathEdit = new QLineEdit(centralWidget);
        CodePathEdit->setObjectName(QString::fromUtf8("CodePathEdit"));

        horizontalLayout->addWidget(CodePathEdit);

        openCodeBtn = new QPushButton(centralWidget);
        openCodeBtn->setObjectName(QString::fromUtf8("openCodeBtn"));

        horizontalLayout->addWidget(openCodeBtn);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_3->addWidget(label_2);

        GrammarPathEdit = new QLineEdit(centralWidget);
        GrammarPathEdit->setObjectName(QString::fromUtf8("GrammarPathEdit"));

        horizontalLayout_3->addWidget(GrammarPathEdit);

        openGrammarBtn = new QPushButton(centralWidget);
        openGrammarBtn->setObjectName(QString::fromUtf8("openGrammarBtn"));

        horizontalLayout_3->addWidget(openGrammarBtn);


        gridLayout->addLayout(horizontalLayout_3, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lexicalAnaBtn = new QPushButton(centralWidget);
        lexicalAnaBtn->setObjectName(QString::fromUtf8("lexicalAnaBtn"));

        horizontalLayout_2->addWidget(lexicalAnaBtn);

        syntacticAnaBtn = new QPushButton(centralWidget);
        syntacticAnaBtn->setObjectName(QString::fromUtf8("syntacticAnaBtn"));

        horizontalLayout_2->addWidget(syntacticAnaBtn);

        semanticAnaBtn = new QPushButton(centralWidget);
        semanticAnaBtn->setObjectName(QString::fromUtf8("semanticAnaBtn"));

        horizontalLayout_2->addWidget(semanticAnaBtn);

        genCodeBtn = new QPushButton(centralWidget);
        genCodeBtn->setObjectName(QString::fromUtf8("genCodeBtn"));

        horizontalLayout_2->addWidget(genCodeBtn);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_3);

        CodeText = new QPlainTextEdit(centralWidget);
        CodeText->setObjectName(QString::fromUtf8("CodeText"));

        verticalLayout_2->addWidget(CodeText);


        gridLayout->addLayout(verticalLayout_2, 2, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_4);

        plainTextEdit = new QPlainTextEdit(centralWidget);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));

        verticalLayout->addWidget(plainTextEdit);


        gridLayout->addLayout(verticalLayout, 2, 1, 1, 1);

        QTminiCcompilerClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QTminiCcompilerClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 673, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        QTminiCcompilerClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QTminiCcompilerClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QTminiCcompilerClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QTminiCcompilerClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QTminiCcompilerClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actionOpen);
        menu->addAction(actionExit);

        retranslateUi(QTminiCcompilerClass);
        QObject::connect(actionExit, SIGNAL(triggered()), QTminiCcompilerClass, SLOT(close()));
        QObject::connect(openCodeBtn, SIGNAL(clicked()), QTminiCcompilerClass, SLOT(openCodeFile()));
        QObject::connect(openGrammarBtn, SIGNAL(clicked()), QTminiCcompilerClass, SLOT(openGrammarFile()));
        QObject::connect(lexicalAnaBtn, SIGNAL(clicked()), QTminiCcompilerClass, SLOT(LexicalScan()));
        QObject::connect(syntacticAnaBtn, SIGNAL(clicked()), QTminiCcompilerClass, SLOT(syntacticAna()));

        QMetaObject::connectSlotsByName(QTminiCcompilerClass);
    } // setupUi

    void retranslateUi(QMainWindow *QTminiCcompilerClass)
    {
        QTminiCcompilerClass->setWindowTitle(QCoreApplication::translate("QTminiCcompilerClass", "QTminiCcompiler", nullptr));
        actionOpen->setText(QCoreApplication::translate("QTminiCcompilerClass", "Open", nullptr));
        actionExit->setText(QCoreApplication::translate("QTminiCcompilerClass", "Exit", nullptr));
        label->setText(QCoreApplication::translate("QTminiCcompilerClass", "\344\273\243\347\240\201\346\226\207\344\273\266", nullptr));
        openCodeBtn->setText(QCoreApplication::translate("QTminiCcompilerClass", "\346\211\223\345\274\200\344\273\243\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("QTminiCcompilerClass", "\346\226\207\346\263\225", nullptr));
        openGrammarBtn->setText(QCoreApplication::translate("QTminiCcompilerClass", "\346\211\223\345\274\200\346\226\207\346\263\225", nullptr));
        lexicalAnaBtn->setText(QCoreApplication::translate("QTminiCcompilerClass", "\350\257\215\346\263\225\345\210\206\346\236\220", nullptr));
        syntacticAnaBtn->setText(QCoreApplication::translate("QTminiCcompilerClass", "\350\257\255\346\263\225\345\210\206\346\236\220", nullptr));
        semanticAnaBtn->setText(QCoreApplication::translate("QTminiCcompilerClass", "\350\257\255\344\271\211\345\210\206\346\236\220", nullptr));
        genCodeBtn->setText(QCoreApplication::translate("QTminiCcompilerClass", "\347\224\237\346\210\220\344\273\243\347\240\201", nullptr));
        label_3->setText(QCoreApplication::translate("QTminiCcompilerClass", "\346\272\220\344\273\243\347\240\201", nullptr));
        label_4->setText(QCoreApplication::translate("QTminiCcompilerClass", "\346\226\207\346\263\225", nullptr));
        menu->setTitle(QCoreApplication::translate("QTminiCcompilerClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QTminiCcompilerClass: public Ui_QTminiCcompilerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTMINICCOMPILER_H
