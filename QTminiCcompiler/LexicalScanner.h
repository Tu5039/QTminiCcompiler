//Copy right Ϳ��γ ���F��
/* LexicalScanner.h
 * ����ʷ�������
 * �汾 1.0, ���� Ϳ��γ ���F��, ���ʱ��2020-07-08
 */

#pragma once
#include "fstream"
#include "string"
using namespace std;
class LexicalScanner
{
private:
	string buffer;//�����Դ���򻺳���
	int pos;//������λ��
	int syn;//token���
	int state;//DFA״̬
	string sourceName;//Դ�ļ���
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

	void getToken();//�����ʷ�
	bool isNum(char c);//�ж�c�Ƿ�������
	bool isLetter(char c);//�ж�c�Ƿ�����ĸ
	char getNext();//ָ���Ƶ���һ��
	void back() { pos--; };//ָ�����
	~LexicalScanner() { infile.close(); }
};