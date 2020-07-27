//Copy right 涂经纬 林镕桢
/* main.cpp
 * 程序运行的主函数，为自带模板，不需修改
 * 版本 1.0, 作者 涂经纬, 完成时间2020-07-5
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
