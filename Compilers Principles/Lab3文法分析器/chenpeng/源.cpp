#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstdlib>
#include<vector>
#include<string>
#include<set>
#include<fstream>
#include<stack>
#include"InputXml.h"
#include"OutputXml.h"

using namespace std;

#define DEBUG1

const int MAXN = 100;
const int MAXN1 = 20;

string str[MAXN] = { "CU","FUNC_LIST","FUNC_DEF","TYPE","ARGU_LIST","A","ARGU",
"CODE_BLOCK","STAT_LIST","STAT","RET_STAT","ASS_STAT","EXP",
"EXP2","TERM","TERM2","FACTOR","DEF_STAT","IF_STAT","QUA_STAT",
"B","CMP","WHILE_STAT","int","char","float",",","id","{","}",
";","return","=","+","-","*","/","const","(",")","if","else",
"<",">","<=",">=","while","_none","#" };
string tag[MAXN] = { "typeSpecifier","typeSpecifier","typeSpecifier","separator","identifier",
"separator","separator","separator","keywordReturn","operator","operator",
"operator","operator","operator","keywordConst","separator","separator",
"keywordIf","keywordElse","operator","operator","operator","operator",
"keywordWhile","ε","end" };

//非终结符
const int CU = 0;	//编译单元
const int FUNC_LIST = 1;	//函数列表
const int FUNC_DEF = 2;		//函数定义	
const int TYPE = 3;		//类型
const int ARGU_LIST = 4;	//参数列表
const int A = 5;	//中间非终结符
const int ARGU = 6;		//参数
const int CODE_BLOCK = 7;	//代码块
const int STAT_LIST = 8;	//语句列表
const int STAT = 9;		//语句
const int RET_STAT = 10;	//返回语句
const int ASS_STAT = 11;	//赋值语句
const int EXP = 12;		//表达式
const int EXP2 = 13;	//表达式2
const int TERM = 14;
const int TERM2 = 15;
const int FACTOR = 16;
const int DEF_STAT = 17;	//声明语句
const int IF_STAT = 18;		//if语句
const int QUA_STAT = 19;	//条件语句
const int B = 20;	//中间非终结符
const int CMP = 21;		//比较符号
const int WHILE_STAT = 22;	//while语句

							//终结符
const int _int = 23;
const int _char = 24;
const int _float = 25;
const int _com = 26;
const int _id = 27;
const int _left_cur = 28;
const int _right_cur = 29;
const int _semi = 30;
const int _ret = 31;
const int _equ = 32;
const int _add = 33;
const int _sub = 34;
const int _mul = 35;
const int _div = 36;
const int _const = 37;
const int _left_brack = 38;
const int _right_brack = 39;
const int _if = 40;
const int _else = 41;
const int _smaller = 42;
const int _bigger = 43;
const int _smaller_equ = 44;
const int _bigger_equ = 45;
const int _while = 46;
const int _none = 47;
const int _end = 48;

struct Node
{
	int flag, v;
	Node(int _flag, int _v) :flag(_flag), v(_v)
	{};
};

vector<vector<int> > vec[MAXN];		//保存文法
vector<int> ll1Table[MAXN][MAXN];	//保存ll1表
set<int> first[MAXN], follow[MAXN], se;
int cnt, tabCnt;
bool vis[MAXN];
stack<Node> sta1, sta2;

void init();	//初始化文法
void insertG(int a[], int len, int now);
bool calFirst(vector<int> &v, int root);	//求first集
void calFollow(int vn);		//求非终结符vn的follow集

int main()
{
#ifdef DEBUG
	ofstream debug;
	debug.open("debug.txt");
#endif

	init();

	for (int i = CU; i <= WHILE_STAT; i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
			calFirst(vec[i][j], vec[i][j][0]);
	}

#ifdef DEBUG //输出first集
	for (int i = CU; i <= WHILE_STAT; i++)
	{
		for (int j = 0; j < vec[i].size(); j++)
		{
			for (int k = 1; k < vec[i][j].size(); k++)
				cout << str[vec[i][j][k]] << " ";
			cout << " first:\n";
			for (auto it = first[vec[i][j][0]].begin(); it != first[vec[i][j][0]].end(); it++)
				cout << str[*it] << " ";
			cout << endl;
		}
	}
	cout << "-------------------------------\n";
#endif

	follow[CU].insert(_end);
	for (int i = CU; i <= WHILE_STAT; i++)
		calFollow(i);

#ifdef DEBUG	//输出follow集
	for (int i = CU; i <= WHILE_STAT; i++)
	{
		cout << str[i] << " follow:\n";
		for (auto it = follow[i].begin(); it != follow[i].end(); it++)
			cout << str[*it] << " ";
		cout << endl;
	}
	cout << "-------------------------------\n";
#endif

#ifdef DEBUG	//测试满不满足ll(1)
	for (int i = CU; i <= WHILE_STAT; i++)
	{
		memset(vis, false, sizeof(vis));
		int flag(true);
		for (auto j : vec[i])
		{
			if (first[j[0]].find(_none) == first[j[0]].end())
			{
				for (auto it = first[j[0]].begin(); it != first[j[0]].end(); it++)
				{
					if (vis[*it])
					{
						flag = false;
						break;
					}
					else vis[*it] = true;
				}
			}
			else
			{
				bool vis1[MAXN];
				memset(vis1, false, sizeof(vis1));
				for (auto it = first[j[0]].begin(); it != first[j[0]].end(); it++)
					vis1[*it] = true;
				for (auto it = follow[i].begin(); it != follow[i].end(); it++)
					vis1[*it] = true;
				for (int k = 0; k < MAXN; k++)
				{
					if (vis1[k])
					{
						if (vis[k])
						{
							flag = false;
							break;
						}
						else vis[k] = true;
					}
				}
			}
			if (!flag) break;
		}
		cout << str[i] << endl;
		cout << flag << endl;
	}
	cout << "-------------------------------\n";
#endif

	for (int i = CU; i <= WHILE_STAT; i++)
	{
		for (int j = _int; j <= _end; j++)
		{
			if (j == _none) continue;
			bool flag(false);
			for (auto k : vec[i])
			{
				if (first[k[0]].find(j) != first[k[0]].end())
				{
					flag = true;
					for (int l = 1; l < k.size(); l++)
						ll1Table[i][j].push_back(k[l]);
					break;
				}
			}

			if (!flag)
			{
				for (auto k : vec[i])
				{
					if (first[k[0]].find(_none) != first[k[0]].end())
					{
						if (follow[i].find(j) != follow[i].end())
						{
							for (int l = 1; l < k.size(); l++)
								ll1Table[i][j].push_back(k[l]);
						}
						break;
					}
				}
			}
		}
	}

#ifdef DEBUG
	ofstream outTest;
	outTest.open("myll1.txt");

	int none(0);
	for (int i = CU; i <= WHILE_STAT; i++)
	{
		for (int j = _int; j <= _end; j++)
		{
			if (j == _none) continue;
			int len(0);
			for (auto k : ll1Table[i][j])
			{
				cout << str[k];
				outTest << str[k];
				len += str[k].size();
			}
			if (ll1Table[i][j].size() == 1 && ll1Table[i][j][0] == _none)
				none++;
			for (int k = len + 1; k <= 40; k++)
				cout << " ", outTest << " ";
		}
		cout << endl;
		outTest << endl;
	}
	outTest.close();
	cout << "-------------------------------\n";
	cout << none << endl;
	cout << "-------------------------------\n";
#endif

	vector<pair<string, string> > vTmp;
	vTmp.clear();
	InputXml in(".\\input\\test.token.xml");
	OutputXml out(".\\input\\test.tree.xml", 0, "1.0", "UTF-8");
	vTmp.push_back(make_pair<string, string>("name", "test.tree.xml"));
	out.output(0, "ParserTree", false, INF, vTmp);
	char value[MAXN1], type[MAXN1];
	int line;
	bool valid;
	sta1.push(Node(0, _end));
	sta1.push(Node(1, CU));

	bool error(false), sign(true);
	while (true)
	{
		if (sign) in.getToken(value, type, &line, &valid);
		if (strcmp(value, "&gt;") == 0) strcpy(value, ">");
		if (strcmp(value, "&lt;") == 0) strcpy(value, "<");
		if (strcmp(value, "&gt;=") == 0) strcpy(value, ">=");
		if (strcmp(value, "&lt;=") == 0) strcpy(value, "<=");

#ifdef DEBUG
		stack<Node> temp;
		while (!temp.empty()) temp.pop();
		cout << "------------\n";
		cout << "value:" << value << endl;
		cout << "stack1:\n";
		debug << "--------------\n";
		debug << "value:" << value << endl;
		debug << "stack1:\n";
		while (!sta1.empty())
		{
			Node p(sta1.top());
			sta1.pop();
			cout << p.flag << " " << str[p.v] << endl;
			debug << p.flag << " " << str[p.v] << endl;
			temp.push(p);
		}
		while (!temp.empty())
			sta1.push(temp.top()), temp.pop();
		cout << "stack2:\n";
		debug << "stack2:\n";
		while (!sta2.empty())
		{
			Node p(sta2.top());
			sta2.pop();
			cout << p.flag << " " << str[p.v] << endl;
			debug << p.flag << " " << str[p.v] << endl;
			temp.push(p);
		}
		while (!temp.empty())
			sta2.push(temp.top()), temp.pop();
#endif

		while (true)
		{
			Node t(sta1.top());
			if (t.flag == -1)
			{
				sta1.pop();
				t = sta2.top();
				sta2.pop();
				out.outputEnd(t.flag, str[t.v].c_str());
			}
			else break;
		}

		if (strcmp(value, "#") == 0)
		{
			int top(sta1.top().v);

#ifdef DEBUG
			debug << "ll1Table:\n";
			for (auto i : ll1Table[top][_end])
				debug << str[i] << " ";
			debug << endl;
#endif

			if (top == _end) break;
			else
			{
				if (ll1Table[top][_end].size() == 1 && ll1Table[top][_end][0] == _none)
					sta1.pop(), sign = false;
				else
				{
					error = true;
					break;
				}
			}
		}
		else
		{
			int index;
			if (strcmp(type, "GiG") == 0) index = _id;
			else if (strcmp(type, "GjG") == 0) index = _const;
			else
			{
				for (int i = _int; i <= _end; i++)
				{
					if (str[i] == value)
					{
						index = i;
						break;
					}
				}
			}

			Node t(sta1.top());
			int tab(t.flag);

			if (t.v >= CU && t.v <= WHILE_STAT)
			{
				if (ll1Table[t.v][index].size() == 0)
				{
					error = true;
					break;
				}

				if (ll1Table[t.v][index].size() == 1 && ll1Table[t.v][index][0] == _none)
					sta1.pop();
				else
				{
					sta2.push(t);
					t.flag = -1;
					sta1.pop();
					sta1.push(t);
					out.output(tab, str[t.v].c_str(), false, INF, vTmp);

					for (int i = ll1Table[t.v][index].size() - 1; i >= 0; i--)
						sta1.push(Node(tab + 1, ll1Table[t.v][index][i]));
				}

#ifdef DEBUG
				cout << "ll1Table:\n";
				debug << "ll1Table:\n";
				for (auto i : ll1Table[t.v][index])
					cout << str[i] << " ", debug << str[i] << " ";
				cout << endl;
				debug << endl;
#endif

				sign = false;
			}
			else
			{
				Node t(sta1.top());
				if (t.v == index)
				{
					out.output(t.flag, tag[index - 23].c_str(), true, value, vTmp);
					sta1.pop();
				}
				else
				{
					error = true;
					break;
				}
				sign = true;
			}
		}

		if (error) break;
	}

	if (error) cout << "Gramma Analysis error!\n";
	else cout << "Gramma Analysis success!\n";
	out.outputEnd(0, "ParserTree");

	return 0;
}

void init()
{
	cnt = tabCnt = 0;
	for (int i = 0; i < MAXN; i++)
	{
		first[i].clear();
		follow[i].clear();
		vis[i] = false;
		for (int j = 0; j < MAXN; j++)
			ll1Table[i][j].clear();
	}
	while (!sta1.empty()) sta1.pop();
	while (!sta2.empty()) sta2.pop();

	vec[CU].clear();
	int cu1[MAXN1] = { cnt++,FUNC_LIST };
	insertG(cu1, 2, CU);

	vec[FUNC_LIST].clear();
	int func_list1[MAXN1] = { cnt++,FUNC_DEF,FUNC_LIST };
	insertG(func_list1, 3, FUNC_LIST);
	int func_list2[MAXN1] = { cnt++,_none };
	insertG(func_list2, 2, FUNC_LIST);

	vec[FUNC_DEF].clear();
	int func_def1[MAXN1] = { cnt++,TYPE,_id,_left_brack,ARGU_LIST,_right_brack,CODE_BLOCK };
	insertG(func_def1, 7, FUNC_DEF);

	vec[TYPE].clear();
	int type1[MAXN1] = { cnt++,_int };
	insertG(type1, 2, TYPE);
	int type2[MAXN1] = { cnt++,_char };
	insertG(type2, 2, TYPE);
	int type3[MAXN1] = { cnt++,_float };
	insertG(type3, 2, TYPE);

	vec[ARGU_LIST].clear();
	int argu_list1[MAXN1] = { cnt++,ARGU,A };
	insertG(argu_list1, 3, ARGU_LIST);
	int argu_list2[MAXN1] = { cnt++,_none };
	insertG(argu_list2, 2, ARGU_LIST);

	vec[A].clear();
	int a1[MAXN1] = { cnt++,_none };
	insertG(a1, 2, A);
	int a2[MAXN1] = { cnt++,_com,ARGU,A };
	insertG(a2, 4, A);

	vec[ARGU].clear();
	int argu1[MAXN1] = { cnt++,TYPE,_id };
	insertG(argu1, 3, ARGU);

	vec[CODE_BLOCK].clear();
	int code_block1[MAXN1] = { cnt++,_left_cur,STAT_LIST,_right_cur };
	insertG(code_block1, 4, CODE_BLOCK);

	vec[STAT_LIST].clear();
	int stat_list1[MAXN1] = { cnt++,STAT,STAT_LIST };
	insertG(stat_list1, 3, STAT_LIST);
	int stat_list2[MAXN1] = { cnt++,_none };
	insertG(stat_list2, 2, STAT_LIST);

	vec[STAT].clear();
	int stat1[MAXN1] = { cnt++,RET_STAT };
	insertG(stat1, 2, STAT);
	int stat2[MAXN1] = { cnt++,ASS_STAT };
	insertG(stat2, 2, STAT);
	int stat3[MAXN1] = { cnt++,DEF_STAT };
	insertG(stat3, 2, STAT);
	int stat4[MAXN1] = { cnt++,IF_STAT };
	insertG(stat4, 2, STAT);
	int stat5[MAXN1] = { cnt++,WHILE_STAT };
	insertG(stat5, 2, STAT);
	int stat6[MAXN1] = { cnt++,_semi };
	insertG(stat6, 2, STAT);

	vec[RET_STAT].clear();
	int ret_stat1[MAXN1] = { cnt++,_ret,EXP,_semi };
	insertG(ret_stat1, 4, RET_STAT);

	vec[ASS_STAT].clear();
	int ass_stat1[MAXN1] = { cnt++,_id,_equ,EXP,_semi };
	insertG(ass_stat1, 5, ASS_STAT);

	vec[EXP].clear();
	int exp1[MAXN1] = { cnt++,TERM,EXP2 };
	insertG(exp1, 3, EXP);

	vec[EXP2].clear();
	int exp21[MAXN1] = { cnt++,_add,TERM,EXP2 };
	insertG(exp21, 4, EXP2);
	int exp22[MAXN1] = { cnt++,_sub,TERM,EXP2 };
	insertG(exp22, 4, EXP2);
	int exp23[MAXN1] = { cnt++,_none };
	insertG(exp23, 2, EXP2);

	vec[TERM].clear();
	int term1[MAXN1] = { cnt++,FACTOR,TERM2 };
	insertG(term1, 3, TERM);

	vec[TERM2].clear();
	int term21[MAXN1] = { cnt++,_mul,FACTOR,TERM2 };
	insertG(term21, 4, TERM2);
	int term22[MAXN1] = { cnt++,_div,FACTOR,TERM2 };
	insertG(term22, 4, TERM2);
	int term23[MAXN1] = { cnt++,_none };
	insertG(term23, 2, TERM2);

	vec[FACTOR].clear();
	int factor1[MAXN1] = { cnt++,_id };
	insertG(factor1, 2, FACTOR);
	int factor2[MAXN1] = { cnt++,_const };
	insertG(factor2, 2, FACTOR);
	int factor3[MAXN1] = { cnt++,_left_brack,EXP,_right_brack };
	insertG(factor3, 4, FACTOR);

	vec[DEF_STAT].clear();
	int def_stat1[MAXN1] = { cnt++,TYPE,_id,_semi };
	insertG(def_stat1, 4, DEF_STAT);

	vec[IF_STAT].clear();
	int if_stat1[MAXN1] = { cnt++,_if,_left_brack,QUA_STAT,_right_brack,CODE_BLOCK,_else,CODE_BLOCK };
	insertG(if_stat1, 8, IF_STAT);

	vec[QUA_STAT].clear();
	int qua_stat1[MAXN1] = { cnt++,EXP,B };
	insertG(qua_stat1, 3, QUA_STAT);

	vec[B].clear();
	int b1[MAXN1] = { cnt++,_none };
	insertG(b1, 2, B);
	int b2[MAXN1] = { cnt++,CMP,EXP };
	insertG(b2, 3, B);

	vec[CMP].clear();
	int cmp1[MAXN1] = { cnt++,_smaller };
	insertG(cmp1, 2, CMP);
	int cmp2[MAXN1] = { cnt++,_bigger };
	insertG(cmp2, 2, CMP);
	int cmp3[MAXN1] = { cnt++,_smaller_equ };
	insertG(cmp3, 2, CMP);
	int cmp4[MAXN1] = { cnt++,_bigger_equ };
	insertG(cmp4, 2, CMP);

	vec[WHILE_STAT].clear();
	int while_stat1[MAXN1] = { cnt++,_while,_left_brack,QUA_STAT,_right_brack,CODE_BLOCK };
	insertG(while_stat1, 6, WHILE_STAT);
}

void insertG(int a[], int len, int now)
{
	vector<int> v;
	v.clear();
	v.insert(v.begin(), a, a + len);
	vec[now].push_back(v);
}

//calFirst返回值位true代表该产生式能推出空
bool calFirst(vector<int> &v, int root)		//v里面放的是产生式的一个右部，root代表该产生式在集合数组中的索引
{											//v的first集元素放在first[root]中
	if (v[1] >= CU && v[1] <= WHILE_STAT)	//如果产生式第一个字符是非终结符的话
	{
		bool flag(false);
		for (auto i : vec[v[1]])			//求该终结符的产生式所有右部的first，并入first[root]中
			flag |= calFirst(i, root);

		if (flag)	//如果第一个非终结符能推出空，循环搜索后面的字符
		{
			int i;
			for (i = 2; i < v.size(); i++)
			{
				if (v[i] >= CU && v[i] <= WHILE_STAT)	//如果是非终结符
				{
					flag = false;
					for (auto j : vec[v[i]])
						flag |= calFirst(j, root);	//该终结符产生式的所有右部只要有一个能推出空，flag就为true
					if (!flag) break;	//flag为false说明都不能推出空，就退出循环，不用继续递归了
				}
				else	//如果是终结符，直接并入first[root]并退出循环
				{
					first[root].insert(v[i]);
					break;
				}
			}
			if (i == v.size()) first[root].insert(_none);	//没有提前退出循环的话，说明v产生式的所有右部都能推出空，所以v能推出空
			return true;
		}
		else return false;
	}
	else
	{
		first[root].insert(v[1]);
		return v[1] == _none;
	}
}

void calFollow(int vn)
{
	if (vis[vn]) return;

	for (int i = CU; i <= WHILE_STAT; i++)
	{
		if (i == vn) continue;
		for (auto j : vec[i])
		{
			for (int k = 1; k < j.size(); k++)
			{
				if (j[k] == vn)
				{
					if (k != j.size() - 1)
					{
						for (int l = k + 1; l < j.size(); l++)
						{
							if (j[l] >= CU && j[l] <= WHILE_STAT)
							{
								se.clear();
								for (auto q : vec[j[l]])
									se.insert(first[q[0]].begin(), first[q[0]].end());
								if (se.find(_none) == se.end())
								{
									follow[vn].insert(se.begin(), se.end());
									break;
								}
								else
								{
									se.erase(_none);
									follow[vn].insert(se.begin(), se.end());
									if (i != vn)
									{
										calFollow(i);
										follow[vn].insert(follow[i].begin(), follow[i].end());
									}
								}
							}
							else
							{
								follow[vn].insert(j[l]);
								break;
							}
						}
					}
					else
					{
						if (i != vn)
						{
							calFollow(i);
							follow[vn].insert(follow[i].begin(), follow[i].end());
						}
					}
				}
			}
		}
	}
	vis[vn] = true;
}
