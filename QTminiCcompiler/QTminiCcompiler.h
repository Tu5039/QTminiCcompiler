//Copy right Ϳ��γ ���F��
/* QTminiCcompiler.cpp
 * QTminiCcompiler.h����ͨ������ۺ�����ʵ��
 * �汾 1.0, ���� Ϳ��γ, ���ʱ��2020-07-10
 */

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QTminiCcompiler.h"

#include "LexicalScanner.h"
#include "GrammarParser.h"

class QTminiCcompiler : public QMainWindow
{
    Q_OBJECT

public:
    QTminiCcompiler(QWidget *parent = Q_NULLPTR);

private:
    Ui::QTminiCcompilerClass ui;

private slots:
    void openCodeFile();//�򿪴����ļ�
    void openGrammarFile();//���ķ��ļ�
    void LexicalScan();//�ʷ�����
    void syntacticAna();//�﷨����
    
    //δ���
    //void semanticAna();
    //void genCode();

};
