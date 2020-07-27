//Copy right 涂经纬 林镕桢
/* LexicalScanner.h
 * 定义词法分析器
 * 版本 1.0, 作者 涂经纬 林镕桢, 完成时间2020-07-08
 */

#pragma once
#include "fstream"
#include "string"
using namespace std;
class LexicalScanner
{
private:
	string buffer;//读入的源程序缓冲区
	int pos;//缓冲区位置
	int syn;//token类别
	int state;//DFA状态
	string sourceName;//源文件名
	int filepos;
	ifstream infile;
	const int BUFFERLENGTH = 4096;
public:
	LexicalScanner(string s)
	{
		sourceName = s;
		infile.open(s);
		pos = 0;
		syn = -1;
		state = 0;
		filepos = 0;
	}

	void getToken();//分析词法
	bool isNum(char c);//判断c是否是数字
	bool isLetter(char c);//判断c是否是字母
	char getNext();//指针移到下一个
	void back() { pos--; };//指针回退
	~LexicalScanner() { infile.close(); }
};