//Copy right 涂经纬 林镕桢
/* GrammarParser.h
 * 定义语法分析器这个类，同时声明语法分析器的成员函数
 * 版本 1.0, 作者 涂经纬 林镕桢, 完成时间2020-07-09
 */

#pragma once

#include "string"
#include "list"
#include "vector"
#include "map"
#include "set"
#include "stack"
#include "fstream"
using namespace std;

struct node
{
	node* Parent;
	string type;
	string value;
	list<node*> sons;
};

class GrammarParser
{
public:
	GrammarParser(string gFile, string tFile);

	void get_LL1_grammar();						//得到LL（1）文法
	void Parse();								//解析，匹配文法与token，建树

	~GrammarParser()
	{
		tokenfile.close();
	}

private:
	list<list<string>> grammar;		//文法	
	vector<vector<vector<string>>> final_grammar;	//处理后的LL(1)文法
	map<string, bool> can_produce_empty;
	map<string, bool> is_Vn;
	map<string, set<string>> FIRST, FOLLOW;
	//预测分析表,结构为		predictive_table[非终结符号，终结符号] = 产生式
	map<pair<string, string>, vector<string>> predictive_table;
	string grammar_file;
	string token_file;
	FILE* f;
	int filepos;
	node root;										//语法树根
	ifstream tokenfile;


	void get_grammar();								//获取初始文法
	void Eliminate_left_recursion();				//消除左递归
	void get_FIRST();								//获取FIRST集合
	void get_FOLLOW();								//获取FOLLOW集合
	bool judge_LL1_grammar();						//判断是不是LL(1)文法
	bool cmp_set(const set<string> s1, const set<string> s2);	//判断两个set是否有交集
	void get_predict_table();						//计算预测分析表
	void get_left_common_factor();					//提取左公因子
	void get_all_Vn();								//找出所有非终结符
	void reconsitution();							//换个方便的数据结构。。。
	string get_next_token();						//不断获得下一个token
	void print_grammar0();							//打印初始文法
	void print_grammar1();							//打印去除左递归后的文法
	void print_grammar2();							//打印提取左公因子后的文法
	void print_final_grammar();						//打印重构后的文法，测试
	set<string> cal_first(string Vn);//用于递归计算FIRST集
	void print_FIRST();								//打印FIRST集合
	void print_FOLLOW();							//打印FOLLOW集合
	void print_predictive_table();					//打印预测分析表
	void print_tree();								//打印语法树
	void string_to_vector(string& s, vector<string>& v);		//将string表示的产生式转为vector
	void vector_to_string(string& s, vector<string>& v);		//将vector表示的产生式转为string
	bool has_common_prefix(vector<string>& gm1, vector<string>& gm2);	//判断两个产生式有无左公因子
	set<string> get_left(vector<string>& tmp);		//返回左端，即first集，用于查看是否有左公因子
	void get_token_value(string& token, string& value, string& type);		//获取token属性
	void deep_print(ofstream& out, int r, node* t);				//递归打印树

};

