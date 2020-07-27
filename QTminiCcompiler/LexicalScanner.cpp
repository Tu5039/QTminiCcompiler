//Copy right 涂经纬 林镕桢
/* LexicalScanner.cpp
 * 实现LexicalScanner的成员函数，使之能够分析词法，将代码转化为若干token
 * 版本 1.0, 作者 涂经纬 林镕桢, 完成时间2020-07-09
 */

#include "LexicalScanner.h"
#include "iostream"
using namespace std;

void LexicalScanner::getToken()
{
	char ch;
	constexpr int TOKENLENGTH = 256;
	char token[TOKENLENGTH];
	memset(token, 0, TOKENLENGTH);
	int tokenpos = 0;
	ofstream outfile("token.txt");
	while ((ch = getNext()) != EOF)
	{
		//todo: 标识符，关键字，整型，浮点数运算符，注释，界符，字符串的dfa
		while (state != 100)
			switch (state)
			{
			case 0:									//开始状态
				switch (ch)
				{
				case '+':state = 1; break;
				case '-':state = 2; break;
				case '*':state = 3; break;
				case '<':state = 4; break;
				case '>':state = 5; break;
				case '=':state = 6; break;
				case ';':state = 7; break;
				case '!':state = 8; break;
				case '[':state = 9; break;
				case ']':state = 10; break;
				case '(':state = 11; break;
				case ')':state = 12; break;
				case '{':state = 13; break;
				case '}':state = 14; break;
				case '"':state = 15; break;
				case ',':state = 16; break;
				case ' ':
				case '\t':
				case '\n':state = 100; break;
				default:
					if (isLetter(ch))state = 18;
					else if (isNum(ch))state = 19;
					else state = 99;//异常
					break;
				}
				break;
			case 1:									//匹配到 +
				token[tokenpos++] = ch;
				ch = getNext();
				if (isNum(ch)) state = 19;
				else
				{
					back();
					syn = 8;
					state = 100;
				}
				break;
			case 2:									//匹配到 -
				token[tokenpos++] = ch;
				syn = 9;
				state = 100;
				break;
			case 3:									//匹配到 *
				token[tokenpos++] = ch;
				syn = 10;
				state = 100;
				break;
			case 4:									//匹配到 /
				token[tokenpos++] = ch;
				ch = getNext();
				if (ch == '/') state = 20;
				else if (ch == '*') state = 21;
				else
				{
					back();
					state = 100;
					syn = 11;
				}
				break;
			case 20:								//匹配到 //
				while ((ch = getNext()) != '\n');
				syn = 31;
				state = 100;
				break;
			case 21:								// 匹配到 /*
				ch = getNext();
				if (ch == '*') state = 22;
				else state = 21;
				break;
			case 22:								//匹配到 /**
				ch = getNext();
				if (ch == '*') state = 22;
				else if (ch == '/')state = 23;
				else state = 21;
				break;
			case 23:								//匹配到 /**/
				state = 100;
				syn = 32;
				break;
			case 5:									//匹配到 <
				token[tokenpos++] = ch;
				ch = getNext();
				if (ch == '=') state = 24;
				else
				{
					back();;
					state = 100;
					syn = 12;
				}
				break;
			case 24:								//匹配到 <=
				token[tokenpos++] = ch;
				state = 100;
				syn = 23;
				break;
			case 6:									//匹配到 >
				token[tokenpos++] = ch;
				ch = getNext();
				if (ch == '=') state = 25;
				else
				{
					back();
					state = 100;
					syn = 13;
				}
				break;
			case 25:								//匹配到 >=
				token[tokenpos++] = ch;
				state = 100;
				syn = 24;
				break;
			case 7:									//匹配到 =
				token[tokenpos++] = ch;
				ch = getNext();
				if (ch == '=') state = 26;
				else
				{
					back();
					state = 100;
					syn = 14;
				}
				break;
			case 26:								//匹配到 ==
				token[tokenpos++] = ch;
				state = 100;
				syn = 25;
				break;
			case 8:									//匹配到 ；
				token[tokenpos++] = ch;
				state = 100;
				syn = 15;
				break;
			case 9:									//匹配到 !
				token[tokenpos++] = ch;
				ch = getNext();
				if (ch == '=') state = 27;
				else state = 99;
				break;
			case 27:								//匹配到 !=
				token[tokenpos++] = ch;
				state = 100;
				syn = 26;
				break;
			case 10:									//匹配到 [
				token[tokenpos++] = ch;
				state = 100;
				syn = 17;
				break;
			case 11:									//匹配到 ]
				token[tokenpos++] = ch;
				state = 100;
				syn = 18;
				break;
			case 12:									//匹配到 (
				token[tokenpos++] = ch;
				state = 100;
				syn = 19;
				break;
			case 13:									//匹配到 )
				token[tokenpos++] = ch;
				state = 100;
				syn = 20;
				break;
			case 14:									//匹配到 {
				token[tokenpos++] = ch;
				state = 100;
				syn = 21;
				break;
			case 15:									//匹配到 }
				token[tokenpos++] = ch;
				state = 100;
				syn = 22;
				break;
			case 16:									//匹配到 "……
				token[tokenpos++] = ch;
				ch = getNext();
				if (ch == '"') state = 28;
				else state = 16;
				break;
			case 28:									//匹配到 "……"
				token[tokenpos++] = ch;
				state = 100;
				syn = 30;
				break;
			case 17:									//匹配到 ,
				token[tokenpos++] = ch;
				state = 100;
				syn = 16;
				break;
			case 18:									//匹配到字母
				token[tokenpos++] = ch;
				ch = getNext();
				if (isLetter(ch) || isNum(ch)) state = 18;	//向前看一位还是数字或字母
				else
				{
					back();
					state = 29;							//向前看一位不属于标识符
				}
				break;
			case 29:									//判断匹配到的标识符是不是关键字
				if (strcmp(token, "if") == 0)
				{
					state = 100;
					syn = 0;
				}
				else if (strcmp(token, "else") == 0)
				{
					state = 100;
					syn = 1;
				}
				else if (strcmp(token, "int") == 0)
				{
					state = 100;
					syn = 2;
				}
				else if (strcmp(token, "double") == 0)
				{
					state = 100;
					syn = 3;
				}
				else if (strcmp(token, "return") == 0)
				{
					state = 100;
					syn = 4;
				}
				else if (strcmp(token, "void") == 0)
				{
					state = 100;
					syn = 5;
				}
				else if (strcmp(token, "while") == 0)
				{
					state = 100;
					syn = 6;
				}
				else if (strcmp(token, "char") == 0)
				{
					state = 100;
					syn = 7;
				}
				else
				{
					state = 100;
					syn = 27;
				}
				break;
			case 19:									//匹配到的是数字
				token[tokenpos++] = ch;
				ch = getNext();
				if (isNum(ch)) state = 19;				//下一位还是数字
				else if (ch == '.') state = 30;			//下一位是.
				else
				{
					back();
					state = 100;
					syn = 28;
				}
				break;
			case 30:									//匹配到 digit D* .
				token[tokenpos++] = ch;
				ch = getNext();
				if (isNum(ch)) state = 30;
				else if (ch == 'e') state = 31;
				else
				{
					back();
					state = 100;
					syn = 29;
				}
				break;
			case 31:									//匹配到 digit D* . D* e
				token[tokenpos++] = ch;
				ch = getNext();
				if (isNum(ch)) state = 32;
				else if (ch == '-')state = 33;
				else
				{
					back();
					state = 99;
				}
				break;
			case 32:									//匹配到 digit D* . D* e
				token[tokenpos++] = ch;
				ch = getNext();
				if (isNum(ch)) state = 32;
				else
				{
					back();
					state = 100;
					syn = 29;
				}
				break;
			case 33:									//匹配到 digit D* . D* e -
				token[tokenpos++] = ch;
				ch = getNext();
				if (isNum(ch)) state = 32;
				else
				{
					back();
					state = 99;
				}
				break;
			case 99:									//匹配中出错
				cout << endl;
				cout << "error" << endl;
				cout << (int)ch << " " << ch << endl;
				ch = getNext();
				while (ch != ' ' && ch != '\t' && ch != '\n' && ch != ';') ch = getNext();
				back();
				state = 100;
				syn = -1;
			}
		if (state == 100 && syn != -1)					//接受状态
		{
			switch (syn)
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
				outfile << "<" << "RESERVED WORD," << token << ">" << endl;
				//outfile << "<" << token << ">" << endl;
				break;
			case 27:
				outfile << "<" << "ID," << token << ">" << endl;
				break;
			case 28:
				outfile << "<" << "NUM," << token << ">" << endl;
				break;
			case 29:
				outfile << "<" << "DOUBLE," << token << ">" << endl;
				break;
			case 30:
				outfile << "<" << "STRING," << token << ">" << endl;
				break;
			case 31:
			case 32:
				break;
			default:
				outfile << "<" << "SYMBOL," << token << ">" << endl;
			}
			memset(token, 0, TOKENLENGTH);
			tokenpos = 0;
			state = 0;
			syn = -1;
		}
		if (state = 100) state = 0;
	}
	outfile.close();
}

bool LexicalScanner::isNum(const char c)
{
	return (c >= '0' && c <= '9');
}

bool LexicalScanner::isLetter(const char c)
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}

char LexicalScanner::getNext()
{

	if (pos < buffer.length())
	{
		return buffer[pos++];
	}
	else
	{
		if (getline(infile, buffer))
		{
			buffer.push_back('\n');
		}
		else
		{
			return EOF;
		}
		pos = 0;
		return buffer[pos++];
	}
}
