//Copy right Ϳ��γ ���F��
/* GrammarParser.h
 * �����﷨����������࣬ͬʱ�����﷨�������ĳ�Ա����
 * �汾 1.0, ���� Ϳ��γ ���F��, ���ʱ��2020-07-09
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

	void get_LL1_grammar();						//�õ�LL��1���ķ�
	void Parse();								//������ƥ���ķ���token������

	~GrammarParser()
	{
		tokenfile.close();
	}

private:
	list<list<string>> grammar;		//�ķ�	
	vector<vector<vector<string>>> final_grammar;	//������LL(1)�ķ�
	map<string, bool> can_produce_empty;
	map<string, bool> is_Vn;
	map<string, set<string>> FIRST, FOLLOW;
	//Ԥ�������,�ṹΪ		predictive_table[���ս���ţ��ս����] = ����ʽ
	map<pair<string, string>, vector<string>> predictive_table;
	string grammar_file;
	string token_file;
	FILE* f;
	int filepos;
	node root;										//�﷨����
	ifstream tokenfile;


	void get_grammar();								//��ȡ��ʼ�ķ�
	void Eliminate_left_recursion();				//������ݹ�
	void get_FIRST();								//��ȡFIRST����
	void get_FOLLOW();								//��ȡFOLLOW����
	bool judge_LL1_grammar();						//�ж��ǲ���LL(1)�ķ�
	bool cmp_set(const set<string> s1, const set<string> s2);	//�ж�����set�Ƿ��н���
	void get_predict_table();						//����Ԥ�������
	void get_left_common_factor();					//��ȡ������
	void get_all_Vn();								//�ҳ����з��ս��
	void reconsitution();							//������������ݽṹ������
	string get_next_token();						//���ϻ����һ��token
	void print_grammar0();							//��ӡ��ʼ�ķ�
	void print_grammar1();							//��ӡȥ����ݹ����ķ�
	void print_grammar2();							//��ӡ��ȡ�����Ӻ���ķ�
	void print_final_grammar();						//��ӡ�ع�����ķ�������
	set<string> cal_first(string Vn);//���ڵݹ����FIRST��
	void print_FIRST();								//��ӡFIRST����
	void print_FOLLOW();							//��ӡFOLLOW����
	void print_predictive_table();					//��ӡԤ�������
	void print_tree();								//��ӡ�﷨��
	void string_to_vector(string& s, vector<string>& v);		//��string��ʾ�Ĳ���ʽתΪvector
	void vector_to_string(string& s, vector<string>& v);		//��vector��ʾ�Ĳ���ʽתΪstring
	bool has_common_prefix(vector<string>& gm1, vector<string>& gm2);	//�ж���������ʽ����������
	set<string> get_left(vector<string>& tmp);		//������ˣ���first�������ڲ鿴�Ƿ���������
	void get_token_value(string& token, string& value, string& type);		//��ȡtoken����
	void deep_print(ofstream& out, int r, node* t);				//�ݹ��ӡ��

};

