//Copy right Ϳ��γ ���F��
/* QTminiCcompiler.cpp
 * QTminiCcompiler.h����ͨ������ۺ�����ʵ��
 * �汾 1.0, ���� Ϳ��γ, ���ʱ��2020-07-10
 */
#include "QTminiCcompiler.h"

#include "qfiledialog.h"
#include "qtextstream.h"

QTminiCcompiler::QTminiCcompiler(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

//�򿪴����ļ�
void QTminiCcompiler::openCodeFile()
{
    ui.CodePathEdit->setText(
        QFileDialog::getOpenFileName(this, 
            "openCode", 
            "", 
            "Code File(*.c *.cpp *.txt)"
        )
    );
    //��ȡ���뵽�ı���
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

//���ķ��ļ�
void QTminiCcompiler::openGrammarFile()
{
    ui.GrammarPathEdit->setText(
        QFileDialog::getOpenFileName(this,
            "openGrammar",
            "",
            "Code File(*.txt)"
        )
    );

    //��ȡ�ķ����ı���
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
//ɨ�����
void QTminiCcompiler::LexicalScan()
{
    LexicalScanner *lexScanner= new LexicalScanner(ui.CodePathEdit->text().toStdString());
    lexScanner->getToken();
}
//�﷨����
void QTminiCcompiler::syntacticAna()
{
    GrammarParser* gp = new GrammarParser("grammar.txt", "token.txt");
    gp->get_LL1_grammar();
    gp->Parse();
}
