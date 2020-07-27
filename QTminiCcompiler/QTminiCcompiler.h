//Copy right 涂经纬 林镕桢
/* QTminiCcompiler.cpp
 * QTminiCcompiler.h中普通函数与槽函数的实现
 * 版本 1.0, 作者 涂经纬, 完成时间2020-07-10
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
    void openCodeFile();//打开代码文件
    void openGrammarFile();//打开文法文件
    void LexicalScan();//词法分析
    void syntacticAna();//语法分析
    
    //未完成
    //void semanticAna();
    //void genCode();

};
