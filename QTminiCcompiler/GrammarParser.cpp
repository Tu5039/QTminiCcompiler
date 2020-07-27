//Copy right Ϳ��γ ���F��
/* GrammarParser.cpp
 * ʵ��GrammarParser�ĳ�Ա������ʹ֮�ܹ������﷨
 * �汾 1.0, ���� Ϳ��γ ���F��, ���ʱ��2020-07-09
 */

#include "GrammarParser.h"
#include "iostream"
#include "iomanip"

//����������
const int BUFFERLENGTH = 4096;

//���캯��ָ���ķ��ļ���token�ļ�
GrammarParser::GrammarParser(string gFile, string tFile)
{
	grammar_file = gFile;
	token_file = tFile;
	tokenfile.open(token_file);
	filepos = 0;
	//�﷨����
	root.Parent = NULL;
	root.type = "non-terminal";
	root.value = "program";
}

void GrammarParser::get_LL1_grammar()
{
	get_grammar();						//���ķ�
	print_grammar0();
	Eliminate_left_recursion();			//ȥ��ݹ�
	print_grammar1();
	get_all_Vn();						//������з��ս��
	get_left_common_factor();			//����������
	print_grammar2();
	reconsitution();					//�ع��洢�ķ������ݽṹ
	print_final_grammar();
	get_FIRST();						//����FIRST����
	print_FIRST();
	get_FOLLOW();						//����FOLLOW����
	print_FOLLOW();
	if (!judge_LL1_grammar())
	{
		cout << "����LL(1)�ķ�" << endl;
		//system("pause");
	}
	else
	{
		cout << "��LL(1)�ķ�" << endl;
		//system("pause");
	}
	get_predict_table();				//����Ԥ�������
	print_predictive_table();
}

//����token�������﷨��
void GrammarParser::Parse()
{
	ofstream outfile("matching_process.txt");
	outfile << setiosflags(ios::left);
	outfile << setw(30) << "Stack" << setw(20) << "Input" << "Action" << endl;
	stack<node*> match;
	//stack<string> match;

	node end;
	end.Parent = NULL;
	end.type = "";
	end.value = "$";

	match.push(&end);
	match.push(&root);

	string type;
	string value;
	string out;
	string token = get_next_token();
	get_token_value(token, value, type);

	while (!match.empty())
	{
		node& top = *match.top();
		match.pop();
		//token��ȡ����
		if (token == "$")
		{
			//ƥ��ɹ�
			if (match.size() == 1)
			{
				outfile << setw(30) << "$" << setw(20) << "$" << "accept" << endl;
				match.pop();
				break;
			}
			else
			{
				//ջ���Ƿ��ս�������Ż����֣�ƥ��ֵ����value��
				bool choose = true;
				if (top.type == "RESERVED WORD" || top.type == "SYMBOL" || top.type == "non-terminal")
				{
					out = top.value + " ... " + "$";
					outfile << setw(30) << out << setw(20) << "$" << "output" << top.value;
				}
				//ջ���Ǳ�ʶ�����������ƥ��ֵ����type��
				else
				{
					out = top.type + " ... " + "$";
					outfile << setw(30) << out << setw(20) << "$" << "output" << top.value;
					choose = false;
				}

				//����ȡ����
				vector<string>& pro = choose ? predictive_table[make_pair(top.value, value)] : predictive_table[make_pair(top.type, value)];
				out.clear();
				vector_to_string(out, pro);
				outfile << " -> " << out << endl;

				//�յ����
				if (out == "empty")
				{
					continue;
				}

				//��ջ��ѹ����ֵ,�����ӽڵ㽨��
				for (int i = pro.size() - 1; i >= 1; i--)
				{
					node* son;
					son = new node;
					//�½ڵ���ԭջ�����ӽڵ�
					top.sons.push_back(son);
					son->Parent = &top;

					//������ѹ����Ų�ͬ����ڵ�
					if (is_Vn[pro[i]])
					{
						son->type = "non-terminal";
						son->value = pro[i];
					}
					else
					{
						if (pro[i] == "ID" || pro[i] == "NUM")
						{
							son->type = pro[i];
							son->value = "";
						}
						else
						{
							if (pro[i][0] >= 'a' && pro[i][0] <= 'z')
							{
								son->type = "RESERVED WORD";
								son->value = pro[i];
							}
							else
							{
								son->type = "SYMBOL";
								son->value = pro[i];
							}
						}
					}
					match.push(son);
				}
			}
		}
		else
		{
			bool choose = true;
			if (top.type == "RESERVED WORD" || top.type == "SYMBOL" || top.type == "non-terminal")
			{
				out = top.value + " ... " + "$";
				outfile << setw(30) << out;
			}
			//ջ���Ǳ�ʶ�����������ƥ��ֵ����type��
			else
			{
				out = top.type + " ... " + "$";
				outfile << setw(30) << out;
				choose = false;
			}

			//token�ǹؼ��ֻ����
			if (type == "RESERVED WORD" || type == "SYMBOL")
			{
				out = value + " ... " + "$";
				outfile << setw(20) << out;
				//ƥ�䣬��ȡ��һ��token
				if (top.value == value)
				{
					outfile << "match" << endl;
					token.clear();
					token = get_next_token();
					get_token_value(token, value, type);
					continue;
				}
				//��ƥ�䣬���
				else
				{
					vector<string>& pro = choose ? predictive_table[make_pair(top.value, value)] : predictive_table[make_pair(top.type, value)];
					if (choose)
					{
						outfile << "output: " << top.value << " -> ";
					}
					else
					{
						outfile << "output: " << top.type << " -> ";
					}
					out.clear();
					vector_to_string(out, pro);
					outfile << out << endl;

					//�յ����
					if (out == "empty")
					{
						continue;
					}

					//��ջ��ѹ����ֵ,�����ӽڵ㽨��
					for (int i = pro.size() - 1; i >= 0; i--)
					{
						node* son;
						son = new node;
						//�½ڵ���ԭջ�����ӽڵ�
						top.sons.push_back(son);
						son->Parent = &top;

						//������ѹ����Ų�ͬ����ڵ�
						if (is_Vn[pro[i]])
						{
							son->type = "non-terminal";
							son->value = pro[i];
						}
						else
						{
							if (pro[i] == "ID" || pro[i] == "NUM")
							{
								son->type = pro[i];
								son->value = "";
							}
							else
							{
								//������
								if (pro[i][0] >= 'a' && pro[i][0] <= 'z')
								{
									son->type = "RESERVED WORD";
									son->value = pro[i];
								}
								//�����
								else
								{
									son->type = "SYMBOL";
									son->value = pro[i];
								}
							}
						}
						match.push(son);
					}
				}
			}
			//token�Ǳ�ʶ��������
			else
			{
				out = type + " ... " + "$";
				outfile << setw(20) << out;
				//ƥ�䣬�ڵ����ֵ����ȡ��һ��token
				if (top.type == type)
				{
					outfile << "match" << endl;
					top.value = value;
					token.clear();
					token = get_next_token();
					get_token_value(token, value, type);
					continue;
				}
				else
				{
					vector<string>& pro = choose ? predictive_table[make_pair(top.value, type)] : predictive_table[make_pair(top.type, type)];

					if (choose)
					{
						outfile << "output: " << top.value << " -> ";
					}
					else
					{
						outfile << "output: " << top.type << " -> ";
					}

					out.clear();
					vector_to_string(out, pro);
					outfile << out << endl;

					//�յ����
					if (out == "empty")
					{
						continue;
					}

					//��ջ��ѹ����ֵ,�����ӽڵ㽨��
					for (int i = pro.size() - 1; i >= 0; i--)
					{
						node* son;
						son = new node;
						//�½ڵ���ԭջ�����ӽڵ�
						top.sons.push_back(son);
						son->Parent = &top;

						//������ѹ����Ų�ͬ����ڵ�
						if (is_Vn[pro[i]])
						{
							son->type = "non-terminal";
							son->value = pro[i];
						}
						//�ս�����ж��Ƿ�ƥ��
						else
						{
							if (pro[i] == "ID" || pro[i] == "NUM")
							{
								son->type = pro[i];
								son->value = "";
							}
							else
							{
								//������
								if (pro[i][0] >= 'a' && pro[i][0] <= 'z')
								{
									son->type = "RESERVED WORD";
									son->value = pro[i];
								}
								//�����
								else
								{
									son->type = "SYMBOL";
									son->value = pro[i];
								}
							}
						}
						match.push(son);
					}
				}
			}
		}
	}
	outfile.close();
	print_tree();
}

//��ӡ�﷨��
void GrammarParser::print_tree()
{
	ofstream outfile("syntax_tree.txt");
	outfile << setiosflags(ios::left);
	deep_print(outfile, 0, &root);
	outfile.close();
}

//��ӡ���ļ��ж�ȡ���ķ�
void GrammarParser::print_grammar0()
{
	ofstream outfile("grammar0.txt");
	for (const auto& l : grammar)
	{
		bool first = true;
		for (const auto& t : l)
		{
			if (first)
			{
				outfile << t << " -> ";
				first = false;
			}
			else outfile << t << " | ";
		}
		outfile << endl << endl;
	}
	outfile.close();
}

//��ӡȥ����ݹ����ķ�
void GrammarParser::print_grammar1()
{
	ofstream outfile("grammar1.txt");
	for (const auto& l : grammar)
	{
		bool first = true;
		for (const auto& t : l)
		{
			if (first)
			{
				outfile << t << " -> ";
				first = false;
			}
			else outfile << t << " | ";
		}
		outfile << endl << endl;
	}
	outfile.close();
}

//��ӡ��ȡ�����Ӻ���ķ�
void GrammarParser::print_grammar2()
{
	ofstream outfile("grammar2.txt");

	for (const auto& l : grammar)
	{
		bool first = true;
		for (const auto& t : l)
		{
			if (first)
			{
				outfile << t << " -> ";
				first = false;
			}
			else outfile << t << " | ";
		}
		outfile << endl << endl;
	}
	outfile.close();
}

//��ӡ�޸ĺ��LL(1)�ķ�
void GrammarParser::print_final_grammar()
{
	ofstream outfile("ll(1)grammar.txt");
	for (auto& gm : final_grammar)
	{
		outfile << gm[0][0] << " -> ";
		for (int i = 1; i < gm.size(); i++)
		{
			for (int j = 0; j < gm[i].size(); j++)
			{
				outfile << gm[i][j] << " ";
			}
			outfile << "| ";
		}
		outfile << endl << endl;
	}
	outfile.close();
}

//��ӡ�����ķ���FIRST����
void GrammarParser::print_FIRST()
{
	ofstream outfile("FIRST.txt");
	for (const auto& gm : final_grammar)
	{
		outfile << gm[0][0] << " : { ";
		for (const auto& str : FIRST[gm[0][0]])
		{
			outfile << str << "| ";
		}
		outfile << "}" << endl << endl;
	}
	outfile.close();
}

//��ӡ�����ķ���FOLLOW����
void GrammarParser::print_FOLLOW()
{
	ofstream outfile("FOLLOW.txt");
	for (const auto& gm : final_grammar)
	{
		const auto& Vn = gm[0][0];
		outfile << Vn << " :{ ";
		for (auto& str : FOLLOW[Vn])
		{
			outfile << str << " | ";
		}
		outfile << "}" << endl << endl;
	}
	outfile.close();
}

//��ӡԤ�������
void GrammarParser::print_predictive_table()
{
	ofstream outfile("predictive_table.txt");
	for (auto& p : predictive_table)
	{
		outfile << p.first.first << "\t" << p.first.second << "\t";
		string pro;
		vector_to_string(pro, p.second);
		outfile << pro << endl << endl;
	}
	outfile.close();
}

void GrammarParser::string_to_vector(string& s, vector<string>& v)
{
	string tmp;
	for (auto& c : s)
	{
		if (c == ' ')
		{
			v.push_back(tmp);
			tmp.clear();
		}
		else
		{
			tmp.push_back(c);
		}
	}
	if (tmp.length()) v.push_back(tmp);
}

void GrammarParser::vector_to_string(string& s, vector<string>& v)
{
	for (int i = 0; i < v.size(); i++)
	{
		if (v[i] == "") continue;
		s += v[i];
		if (i != v.size() - 1)
		{
			s.push_back(' ');
		}
	}
}

//�ж���������ʽ��û��������
bool GrammarParser::has_common_prefix(vector<string>& gm1, vector<string>& gm2)
{
	set<string> S, s1, s2;
	s1 = get_left(gm1);
	s2 = get_left(gm2);
	S.insert(s1.begin(), s1.end());
	S.insert(s2.begin(), s2.end());
	return s1.size() + s2.size() != S.size();
}

//���ز���ʽ��first����������������
set<string> GrammarParser::get_left(vector<string>& tmp)
{
	set<string> res;
	if (tmp.size() == 0)
	{
		return res;
	}
	int i = 0;
	do
	{
		if (is_Vn[tmp[i]])
		{
			for (auto& gm : grammar)
			{
				auto p = gm.begin();
				if (tmp[i] == *p)
				{
					for (p++; p != gm.end(); p++)
					{
						vector<string> vs;
						string_to_vector(*p, vs);
						auto s = get_left(vs);
						res.insert(s.begin(), s.end());
					}
					break;
				}
			}
		}
		else
		{
			res.insert(tmp[i]);
		}
		if (i == tmp.size() - 1 && can_produce_empty[tmp[i]])
		{
			res.insert("empty");
			break;
		}
	} while (can_produce_empty[tmp[i++]]);
	return res;
}

//��token�е�������ȡ����
void GrammarParser::get_token_value(string& token, string& value, string& type)
{
	type.clear();
	value.clear();
	node* res;
	res = new node;
	for (int i = 0; i < token.length(); i++)
	{
		auto c = token[i];
		if (c == '<' && i == 0) continue;
		else if (c == ',')
		{
			type = value;
			value.clear();
			continue;
		}
		else if (c == '>' && i == token.length() - 1)
		{
			break;
		}
		else
		{
			value.push_back(c);
		}
	}
}

//�ݹ��ӡ�﷨����������ʾ�β�
void GrammarParser::deep_print(ofstream& out, int r, node* t)
{
	for (int i = 0; i < r; i++)
	{
		out << "-";
	}
	string tmp;
	tmp = "type: " + t->type;
	out << setw(30) << tmp;
	tmp = "value: " + t->value;
	out << setw(30) << tmp;
	out << endl;
	for (auto& p : t->sons)
	{
		deep_print(out, r + 1, p);
	}
}

//��ȡԭʼ�ķ������浽�ڴ���
void GrammarParser::get_grammar()
{
	fopen_s(&f, grammar_file.c_str(), "r");

	char input_buffer[BUFFERLENGTH];
	while (fgets(input_buffer, BUFFERLENGTH, f))
	{
		list<string> tmp;
		int len = strlen(input_buffer);
		string str;
		int pos = 0;
		for (int i = 0; i < len; i++)
		{
			if (input_buffer[i] == ' ' && str.length() == 0) continue;
			else if (input_buffer[i] == '|')
			{
				while (str.back() == ' ') str.pop_back();
				tmp.push_back(str);
				str.clear();
				pos = 0;
			}
			else if (input_buffer[i] == -95)
			{
				while (str.back() == ' ') str.pop_back();
				tmp.push_back(str);
				str.clear();
				pos = 0;
				i++;
			}
			else str.push_back(input_buffer[i]);
		}
		while (str.back() == ' ' || str.back() == '\n') str.pop_back();
		tmp.push_back(str);
		grammar.push_back(tmp);
	}
}

//������ݹ�
void GrammarParser::Eliminate_left_recursion()
{
	//TO DO:����grammar�����ݹ�  
	for (auto p = grammar.begin(); p != grammar.end(); p++)
	{
		list<string>& A = *p;			//�ķ�A
		//չ����ǰ�ķ�
		for (auto j = grammar.begin(); j != p; j++)
		{
			//�滻A����ʽ�е�Vn			
			list<string>& B = *j;			//�ķ�B
			string& Vn = B.front();			//�ķ�B�Ŀ�ͷ
			auto pA = A.begin(); pA++;
			//auto pB = B.begin(); pB++;
			for (; pA != A.end(); pA++)
			{
				string& production = *pA;		//�ķ�A�еĲ���ʽ
				string item(production);
				string tmp;					//��ȡproduction�еķ��ս��
				for (char c : production)
				{
					if (c != ' ')
					{
						tmp.push_back(c);
					}
					else							//��ȡ����һ�������ķ��ս��
					{
						if (Vn == tmp)				//�÷��ս����ǰ��Ŀ�ʼ����
						{
							//string prefix = production.substr(0,subbg);
							//string suffix = production.substr(subend);						
							pA = A.erase(pA);		//ɾ��ԭ����ʽ
							auto pB = B.begin(); pB++;
							for (; pB != B.end(); pB++)		//��production�滻ΪB�еĲ���ʽ
							{
								string newprd(item);
								newprd.replace(0, Vn.length(), *pB);
								A.insert(pA, newprd);		//�����滻��Ĳ���ʽ
							}
							pA = A.begin();
							break;
						}
						//cout << tmp << endl;
						break;
					}
				}
			}
		}
		//ȥ��ֱ����ݹ�
		do
		{
			list<string>::iterator pA = A.begin();
			auto Vn = *pA;
			pA++;
			/*
			A -> A��| ��
			vs1�����vs2���
			*/
			vector<string> vs1, vs2;
			for (; pA != A.end(); pA++)
			{
				string& production = *pA;
				string first;				//ÿ������ʽ�ĵ�һ����ĸ�жϷָ������Ǧ�
				bool flag = true;
				for (char c : production)
				{
					if (c == ' ')
					{
						if (first == Vn)		//��A��
						{
							vs1.push_back(production.substr(Vn.length() + 1));
						}
						else					//�Ǧ�
						{
							vs2.push_back(production);
						}
						flag = false;			//�Ѿ��������ǰ����ʽ
						break;
					}
					else
					{
						first.push_back(c);
					}
				}
				if (flag) vs2.push_back(production);
			}
			if (vs1.empty()) continue;			//���ǿյģ�������ݹ�
			pA = A.begin(); pA++;
			/*
			��A -> A��| �¸�Ϊ
			A -> ��A1
			A1 -> ��A1
			*/
			while (pA != A.end()) pA = A.erase(pA);		//���A�Ĳ���ʽ
			//�����ֻ��empty��ֱ�Ӹ�Ϊ A -> ��A | empty
			if (vs2[0] == "empty")
			{
				for (string s : vs1)
				{
					A.push_back(s + ' ' + Vn);
				}
				A.push_back("empty");
				continue;
			}
			string newprdt(Vn + "_1");				//���Ӳ���ʽ
			//��A1
			for (string s : vs2)
			{
				A.push_back(s + ' ' + newprdt);
			}
			//A1 -> ��A1
			list<string> newgrammar;
			newgrammar.push_back(newprdt);				//����A1
			for (string s : vs1)
			{
				newgrammar.push_back(s + ' ' + newprdt);
			}
			newgrammar.push_back("empty");
			p++;
			p = grammar.insert(p, newgrammar);
		} while (false);

	}
}

//��ȡFIRST����
void GrammarParser::get_FIRST()
{
	FIRST.clear();
	for (auto& gm : final_grammar)
	{
		string& Vn = gm[0][0];
		if (FIRST[Vn].empty())
		{
			FIRST[Vn] = cal_first(Vn);
		}
	}
}

//�ݹ���㵱ǰ���ս����fist����
set<string> GrammarParser::cal_first(string Vn)
{
	set<string> res;
	for (auto& gm : final_grammar)
	{
		if (gm[0][0] == Vn)
		{
			//ÿ������ʽ��FIRST����
			for (int j = 1; j < gm.size(); j++)
			{
				auto& pro = gm[j];
				//��ÿ������ʽ�ĵ�һ�����ս����ʼ����FISRST�����������empty���ټ�����һ���������һ��Ҳ��empty����empty����FIRST����
				for (int i = 0; i < pro.size(); i++)
				{
					//�ж��ǲ��Ƿ��ս��
					if (is_Vn[pro[i]])
					{
						FIRST[pro[i]] = cal_first(pro[i]);
						res.insert(FIRST[pro[i]].begin(), FIRST[pro[i]].end());
						if (FIRST[pro[i]].find("empty") != FIRST[pro[i]].end())
						{
							if (i == pro.size() - 1)
							{
								res.insert("empty");
								break;
							}
							else continue;
						}
						else break;
					}
					else
					{
						if (pro[i] != "empty")
						{
							res.insert(pro[i]);
						}
						//����ʽֻ��һ��empty�����
						else if (i == 0)
						{
							res.insert("empty");
						}
						break;
					}
				}
			}
			break;
		}
	}
	return res;
}

//��ȡFOLLOW����
void GrammarParser::get_FOLLOW()
{
	FOLLOW[final_grammar[0][0][0]].insert("$");
	int t = final_grammar.size();
	while (t--)
	{
		for (auto& gm : final_grammar)
		{
			/*
			����ÿ���ķ����򣬲���Ѱ��A -> ��B�½ṹ��
			��FIRST(��)�г�empty������з��ż���FOLLOW(B)
			*/
			auto p = gm.begin();
			for (p++; p != gm.end(); p++)
			{
				auto& pro = *p;
				/*
				��Ǹ÷��ź���Ĳ����ܷ����empty
				�Ӷ��ж��Ƿ�Ӧ�ù��򣺶���A -> ��B��
				��FOLLOW(A)�еķ��ż���FOLLOW(B)��
				flagΪtrueʱ��Ӧ�ã�falseʱ�ǲ�Ӧ��
				*/
				bool flag = true;
				//�Ӻ���ǰ�ж�ÿ���ķ������ܲ���emptyʱ��flag��Ϊfalse
				for (int i = pro.size() - 1; i >= 0; i--)
				{
					//�ж��Ƿ��Ƿ��ս��
					if (is_Vn[pro[i]])
					{

						if (flag)
						{
							//��Ϊgm[0][0]��follow���Ͽ��ܲ�ȫ������Ҫ�������øú�����ȫ��������
							FOLLOW[pro[i]].insert(FOLLOW[gm[0][0]].begin(), FOLLOW[gm[0][0]].end());
							if (FIRST[pro[i]].find("empty") == FIRST[pro[i]].end()) flag = false;
						}
						//����벿��first����follow
						for (int j = i + 1; j < pro.size(); j++)
						{
							if (is_Vn[pro[j]])
							{
								FOLLOW[pro[i]].insert(FIRST[pro[j]].begin(), FIRST[pro[j]].end());
								if (FIRST[pro[j]].find("empty") == FIRST[pro[j]].end())
								{
									flag = false;
									break;
								}
							}
							else
							{
								FOLLOW[pro[i]].insert(pro[j]);
								break;
							}
						}
					}
					else
					{
						flag = false;
					}
				}
			}
		}
	}
	//FOLLOW����û��empty
	for (auto& gm : final_grammar)
	{
		auto& Vn = gm[0][0];
		auto p = FOLLOW[Vn].find("empty");
		if (p != FOLLOW[Vn].end()) FOLLOW[Vn].erase(p);
	}
}

//�ж��ǲ���LL(1)�ķ�
bool GrammarParser::judge_LL1_grammar()
{
	bool res = true;
	for (auto& gm : final_grammar)
	{
		auto& Vn = gm[0][0];
		bool flag = false;
		//first(Vn)����empty����Ҫ�Ƚ�follow(Vn)��first(A)��A��first����û��empty�Ĳ���ʽ
		if (FIRST[Vn].find("empty") != FIRST[Vn].end())
		{
			flag = true;
		}
		for (int i = 1; i < gm.size(); i++)
		{
			//��������ʽ��FIRST����
			set<string> s1;
			for (auto& v : gm[i])
			{
				//�Ƿ��ս��
				if (is_Vn[v])
				{
					s1.insert(FIRST[v].begin(), FIRST[v].end());
					//���治��empty
					if (FIRST[v].find("empty") == FIRST[v].end()) break;
				}
				else
				{
					s1.insert(v);
					break;
				}
			}
			if (flag && s1.find("empty") == s1.end()) res &= cmp_set(s1, FOLLOW[Vn]);
			for (int j = i + 1; j < gm.size(); j++)
			{
				set<string> s2;
				for (auto& v : gm[j])
				{
					if (is_Vn[v])
					{
						s2.insert(FIRST[v].begin(), FIRST[v].end());
						if (FIRST[v].find("empty") == FIRST[v].end()) break;
					}
					else
					{
						s2.insert(v);
						break;
					}
				}
				res &= cmp_set(s1, s2);
			}
		}
	}
	return res;
}

//�Ƚ�����������û�н���
bool GrammarParser::cmp_set(const set<string> s1, const set<string> s2)
{
	int l1 = s1.size();
	int l2 = s2.size();
	set<string> s;
	s.insert(s1.begin(), s1.end());
	s.insert(s2.begin(), s2.end());
	int l = s.size();
	if (l1 + l2 != l) {
		cout << "error" << endl;
	}
	return (l1 + l2) == l;
}

//����Ԥ�������
void GrammarParser::get_predict_table()
{
	/*
	����A -> ��,������ʽ����pair(A, a��FIRST(��))��
	���empty��FIRST(��)�У�������ʽ����pair(A, b��FOLLOW(A))��
	*/
	for (auto& gm : final_grammar)
	{
		auto& Vn = gm[0][0];
		for (int i = 1; i < gm.size(); i++)
		{
			//gm[i]��Ϊ��
			auto& pro = gm[i];
			set<string> s;		//����FIRST����
			bool flag = false;				//FIRST����û��empty
			for (auto& v : pro)
			{
				//�Ƿ��ս��
				if (is_Vn[v])
				{
					s.insert(FIRST[v].begin(), FIRST[v].end());
					//���治��empty
					if (FIRST[v].find("empty") == FIRST[v].end()) break;
				}
				else
				{
					s.insert(v);
					break;
				}
			}
			if (s.find("empty") != s.end())
			{
				flag = true;
			}
			for (auto& Vt : s)
			{
				predictive_table[make_pair(Vn, Vt)] = pro;
			}
			if (flag)
			{
				for (auto& Vt : FOLLOW[Vn])
				{
					predictive_table[make_pair(Vn, Vt)] = pro;
				}
			}
		}

	}
}

//��ȡ������
void GrammarParser::get_left_common_factor()
{
	for (auto& gm : grammar)
	{
		int sign = 2;
		//reconsitution();
		//get_FIRST();		
	loop:
		auto p = gm.begin();
		p++;
		//����ѭ���Ƚϸ÷��ս�����еĲ���ʽ
		for (; p != gm.end(); p++)
		{

			auto p2 = p;
			for (p2++; p2 != gm.end(); p2++)
			{

				//�Ѳ���ʽ��ÿ����ʶ���浽vector�﷽�����
				vector<string> pro1, pro2;
				string_to_vector(*p, pro1);
				string_to_vector(*p2, pro2);
				//�ж���������ʽ��û������ʽ
				if (!has_common_prefix(pro1, pro2)) continue;
				else
				{
					//����ʽ��ͬ����ȡ����
					if (pro1[0] == pro2[0])
					{
						vector<string> common;
						int i = 0;
						while (i < pro1.size() && i < pro2.size() && pro1[i] == pro2[i])
						{
							common.push_back(pro1[i]);
							pro1[i] = "";
							pro2[i] = "";
							i++;
						}
						string common_fact;
						vector_to_string(common_fact, common);
						string npro1, npro2;
						vector_to_string(npro1, pro1);
						vector_to_string(npro2, pro2);
						string nVn(gm.front());
						nVn = nVn + '_' + (char)(sign + 48);
						sign++;
						//���й����ӵĲ���ʽɾ��
						gm.erase(p);
						gm.erase(p2);
						//�滻
						gm.push_back(common_fact + ' ' + nVn);
						//�µ��ķ�����
						list<string> tmp;
						tmp.push_back(nVn);
						if (npro1 != "")
						{
							tmp.push_back(npro1);
						}
						else
						{
							tmp.push_back("empty");
						}
						if (npro2 != "")
						{
							tmp.push_back(npro2);
						}
						else
						{
							tmp.push_back("empty");
						}
						grammar.push_back(tmp);
						is_Vn[nVn] = true;
					}
					//˵���Ǹò���ʽ�Ĳ���ʽ�й�����,��չ��
					else
					{
						//չ��pָ��Ĳ���ʽ
						if (is_Vn[pro1[0]])
						{
							for (auto& g : grammar)
							{
								if (g.front() == pro1[0])
								{
									string npro;
									pro1[0] = "";
									vector_to_string(npro, pro1);
									gm.erase(p);
									auto it = g.begin(); it++;
									for (; it != g.end(); it++)
									{
										if (npro != "")
										{
											gm.push_back(*it + ' ' + npro);
										}
										else
										{
											gm.push_back(*it);
										}
									}
									break;
								}
							}
						}
						//չ��p2ָ��Ĳ���ʽ
						if (is_Vn[pro2[0]])
						{
							for (auto& g : grammar)
							{
								if (g.front() == pro2[0])
								{
									string npro;
									pro2[0] = "";
									vector_to_string(npro, pro2);
									gm.erase(p2);
									auto it = g.begin(); it++;
									for (; it != g.end(); it++)
									{
										if (npro != "")
										{
											gm.push_back(*it + ' ' + npro);
										}
										else
										{
											gm.push_back(*it);
										}
									}
									break;
								}
							}
						}
					}
					goto loop;
				}
			}
		}
	}
}

//������з��ս�����ս��
void GrammarParser::get_all_Vn()
{
	//��map�м��������ս������ս��
	for (auto gm : grammar)
	{
		for (auto V : gm)
		{
			is_Vn[V] = false;
		}
	}
	//�����ս�����Ϊtrue
	for (auto gm : grammar)
	{
		is_Vn[*gm.begin()] = true;
	}
}

//�ķ����ٸı䣬�������ݽṹ���������ʹ��
void GrammarParser::reconsitution()
{
	final_grammar.clear();
	vector<vector<string>> tmp;
	for (auto& gm : grammar)
	{
		tmp.clear();
		vector<string> vs;
		for (auto& pro : gm)
		{
			vs.clear();
			string sub;
			for (auto& c : pro)
			{
				if (c == ' ')
				{
					vs.push_back(sub);
					sub.clear();
				}
				else
				{
					sub.push_back(c);
				}
			}
			vs.push_back(sub);
			tmp.push_back(vs);
		}
		final_grammar.push_back(tmp);
	}
	//grammar.clear();
}


//���ϻ�ȡ��һ��token�����﷨��
string GrammarParser::get_next_token()
{
	string str;
	if (getline(tokenfile, str))
	{
		return str;
	}
	else
	{
		return string("$");
	}
}
