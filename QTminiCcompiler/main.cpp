//Copy right Ϳ��γ ���F��
/* main.cpp
 * �������е���������Ϊ�Դ�ģ�壬�����޸�
 * �汾 1.0, ���� Ϳ��γ, ���ʱ��2020-07-5
 */

#include "QTminiCcompiler.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTminiCcompiler w;
    w.show();
    return a.exec();
}
