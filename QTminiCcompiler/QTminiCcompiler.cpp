//Copy right 涂经纬 林镕桢
/* QTminiCcompiler.cpp
 * QTminiCcompiler.h中普通函数与槽函数的实现
 * 版本 1.0, 作者 涂经纬, 完成时间2020-07-10
 */
#include "QTminiCcompiler.h"

#include "qfiledialog.h"
#include "qtextstream.h"

QTminiCcompiler::QTminiCcompiler(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

//打开代码文件
void QTminiCcompiler::openCodeFile()
{
    ui.CodePathEdit->setText(
        QFileDialog::getOpenFileName(this, 
            "openCode", 
            "", 
            "Code File(*.c *.cpp *.txt)"
        )
    );
    //读取代码到文本框
    QFile file(ui.CodePathEdit->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    in.setCodec("utf-8");
    QString line = file.readLine(), codeText;
    codeText.append(line);
    while (!line.isNull())
    {
        line = in.readLine();
        codeText.append(line);
        codeText.append("\n");
    }
    ui.CodeText->setPlainText(codeText);
}

//打开文法文件
void QTminiCcompiler::openGrammarFile()
{
    ui.GrammarPathEdit->setText(
        QFileDialog::getOpenFileName(this,
            "openGrammar",
            "",
            "Code File(*.txt)"
        )
    );

    //读取文法到文本框
    QFile file(ui.GrammarPathEdit->text());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;
    QTextStream in(&file);
    in.setCodec("utf-8");
    QString line = file.readLine(), grammarText;
    grammarText.append(line);
    while (!line.isNull())
    {
        line = in.readLine();
        grammarText.append(line);
        grammarText.append("\n");
    }
    ui.plainTextEdit->setPlainText(grammarText);
}
//扫描代码
void QTminiCcompiler::LexicalScan()
{
    LexicalScanner *lexScanner= new LexicalScanner(ui.CodePathEdit->text().toStdString());
    lexScanner->getToken();
}
//语法分析
void QTminiCcompiler::syntacticAna()
{
    GrammarParser* gp = new GrammarParser("grammar.txt", "token.txt");
    gp->get_LL1_grammar();
    gp->Parse();
}
