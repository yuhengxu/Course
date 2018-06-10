#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<map>
#include<vector>
#include<set>
#include<stack>
#include <iomanip>
#include"tinyxml2.h"

using namespace std;
using namespace tinyxml2;

#define path "C:\\Users\\yuheng\\Desktop\\LL(1)\\test.txt"
//#define path "C:\\Users\\yuheng\\Desktop\\LL(1)\\LL(1).txt"
#define buff_MIXN 200
#define table_MIXN 200

const char* xmlpath = "C:\\Users\\yuheng\\Desktop\\LL(1)\\test.xml";

class Gx									//一个项目
{
public:
	string left;							//产生式左部
	vector<string>right;					//产生式右部

public:
	Gx initG(char* buff);					//从文本中读入一条产生式，对其进行初始化(填入左部右部)
};

vector<Gx>I_list;
set<string>nonTerminal;						//非终结符集
set<string>Terminal;						//终结符集
map<string, bool>non_terminal;				//非终结符集
map<string, set<string>>first;				//first集
map<string, set<string>>follow;				//follow集
map<string, map<string, int>>tableMap;		//分析表

Gx Gx::initG(char* buff)					//这是初始化函数用来初始化文法的，不用管实现过程
{
	Gx G_temp;
	int i = 0, k = 0, l = 0;
	char buff_left[buff_MIXN], buff_right[buff_MIXN];
	while (buff[i] != ':')buff_left[i++] = buff[i];
	buff_left[i] = '\0';
	G_temp.left = buff_left;
	while (buff[i] != '\0' && buff[++i] != '\n')
	{
		buff_right[k++] = buff[i];
		if (buff[i] == ' ')
		{
			buff_right[k - 1] = '\0';
			G_temp.right.push_back(buff_right);
			k = 0;
		}
	}
	buff_right[k] = '\0';
	G_temp.right.push_back(buff_right);

	return G_temp;
}

void init()
{
	FILE* fp = fopen(path, "r");
	if (fp == NULL) printf("The path is not exist\n");
	else
	{
		char buff[buff_MIXN];
		int i = 0;
		Gx G_temp;
		while (fgets(buff, buff_MIXN, fp) != NULL)
		{
			if (buff[0] == '/' || buff[0] == '\n' || buff[0] == ' ')continue;
			I_list.push_back(G_temp.initG(buff));
		}
		for (int j = 0; j < I_list.size(); j++)
		{
			non_terminal[I_list[j].left] = true;
			nonTerminal.insert(I_list[j].left);
		}
		for (int j = 0; j < I_list.size(); j++)
		{
			for (int k = 0; k < I_list[j].right.size(); k++)
			{
				if (non_terminal[I_list[j].right[k]] == false)
					Terminal.insert(I_list[j].right[k]);
			}
		}
		Terminal.insert("#");
	}

	fclose(fp);

}

//计算first集
void calFirst(string g)
{
	int tag = 0;
	int flag = 0;
	for (int i = 0; i < I_list.size(); i++)
	{
		if (I_list[i].left == g)			//匹配产生式右部
		{
			if (non_terminal[I_list[i].right[0]] == false)		//对于终结符，直接加入first
			{
				first[g].insert(I_list[i].right[0]);
			}
			else
			{
				for (int j = 0; j < I_list[i].right.size(); j++)
				{
					if (non_terminal[I_list[i].right[j]] == false)//终结符结束
					{
						first[g].insert(I_list[i].right[j]);
						break;
					}
					calFirst(I_list[i].right[j]);				//递归

					set<string>::iterator it;
					for (it = first[I_list[i].right[j]].begin(); it != first[I_list[i].right[j]].end(); it++)
					{
						if (*it == "@") flag = 1;
						else
							first[g].insert(*it);				//将first(Y)中得非@加入first(g)
					}
					if (flag == 0)break;
					else
					{
						tag += flag;
						flag = 0;
					}
				}
				if (tag == I_list[i].right.size())				//所有得右部first(y)都有@，将@加入first(g)
				{
					first[g].insert("@");
				}
			}
		}
	}
}

//计算follow集
void calFollow(string g)
{
	for (int i = 0; i < I_list.size(); i++)
	{
		int index = -1;
		int len = I_list[i].right.size();
		for (int j = 0; j < len; j++)
		{
			if (I_list[i].right[j] == g)				//寻找含有该字符得产生式
			{
				index = j;
				break;
			}
		}
		if (index != -1 && index < len - 1)
		{
			string next = I_list[i].right[index + 1];
			if (non_terminal[next] == false)			//g后面得第一个字符如果是终结符就将其加入g得follow集中
				follow[g].insert(next);
			else
			{
				int isExt = 0;
				set<string>::iterator it;
				for (it = first[next].begin(); it != first[next].end(); it++)
				{
					//若A->aBb是一个产生式,则把FIRST(b)\{ε}加至FOLLOW(B)中;
					if (*it == "@")
						isExt = 1;
					else
						follow[g].insert(*it);
				}
				//若A->aBb是一个产生式而b=>ε(即ε∈FIRST(b))则把FOLLOW(A)加至FOLLOW(B)中
				if (isExt && I_list[i].left != g)
				{
					calFollow(I_list[i].left);
					set<string>::iterator it;
					string temp = I_list[i].left;
					for (it = follow[temp].begin(); it != follow[temp].end(); it++)
						follow[g].insert(*it);
				}

			}
		}

		//若A->aB是一个产生式,而b=>ε(即ε∈FIRST(b))则把FOLLOW(A)加至FOLLOW(B)中
		else if (index != -1 && index == len - 1 && g != I_list[i].left)
		{
			calFollow(I_list[i].left);
			set<string>::iterator it;
			string temp = I_list[i].left;
			for (it = follow[temp].begin(); it != follow[temp].end(); it++)
				follow[g].insert(*it);
		}
		
	}
}

//构造LL(1)分析表
void makeTable()
{
	for (int i = 0; i < I_list.size(); i++)
	{
		string temp = I_list[i].right[0];
		if (non_terminal[temp] == false)
		{
			if (temp != "@")
				tableMap[I_list[i].left][temp] = i;
			if (temp == "@")
			{
				set<string>::iterator it;
				for (it = follow[I_list[i].left].begin(); it != follow[I_list[i].left].end(); it++)
				{
					tableMap[I_list[i].left][*it] = i;
				}
			}
		}
		else
		{
			set<string>::iterator it1;
			for (it1 = first[temp].begin(); it1 != first[temp].end(); it1++)
			{
				tableMap[I_list[i].left][*it1] = i;
			}
			if (first[temp].count("@") != 0)
			{
				set<string>::iterator it;
				for (it = follow[I_list[i].left].begin(); it != follow[I_list[i].left].end(); it++)
				{
					tableMap[I_list[i].left][*it] = i;
				}
			}
		}
	}
}

void showAnalysis(stack<string>analyStr, vector<string>remainStr, vector<string>::iterator remainStrIt, int number)
{
	cout << "————————————————————————————————————————————————" << endl;
	cout << "分析栈：";
	while (!analyStr.empty())
	{
		cout << setw(5) << analyStr.top();
		analyStr.pop();
	}
	cout << endl;

	vector<string>::iterator tempIt;
	
	cout << "剩余输入串：";
	for (tempIt = remainStr.begin(); tempIt != remainStr.end(); tempIt++)
	{
		cout << setw(5) << *tempIt;
	}
	cout << endl;

	cout << "产生式标号：" << number << endl;
}

//总控程序
void analyExp(vector<string>remainStr)
{
	int number;
	stack<string>analyStr;						//分析栈
	vector<string>remainStrCopy;
	remainStrCopy = remainStr;

	//初始化
	analyStr.push("#");
	analyStr.push(I_list[0].left);
	vector<string>::iterator it;
	it = remainStr.begin();


	while (1)
	{
		number = 255;
		//若当前分析栈栈顶符号X和输入串剩余第一项ai都是文法得终结符号
		if (non_terminal[analyStr.top()] == false && non_terminal[remainStr[0]] == false)
		{
			//X=ai=# 表示分析成功，停止分析过程
			if (analyStr.top() == *it && *it == "#")
			{
				cout << "analysis succeed!" << endl;
				break;
			}
			//X=ai！=# 将X从分析栈顶退掉，剩余串向后移动
			else if (analyStr.top() == *it && *it != "#")
			{
				analyStr.pop();
				it++;
				remainStrCopy.erase(remainStrCopy.begin());
			}
			else
			{
				cout << "analysis failed!" << endl;
				break;
			}
		}
		//若X属于非终结符，查询分析表
		else if (non_terminal[analyStr.top()] == true)
		{
			//若tableMap[X,ai]中为空白，贼执行出错处理程序
			if (tableMap[analyStr.top()][*it] < 0 || tableMap[analyStr.top()][*it] >= I_list.size())
			{
				cout << "The table is NULL" << endl;
				break;
			}
			//若tableMap[X,ai]中为一个产生式规则，则将X从栈中弹出并将此规则右部得符号序列按倒叙推进栈，若产生式规则为x->@,则将x从栈中弹出
			else
			{
				string analyNonTerminal = analyStr.top();
				analyStr.pop();

				if (I_list[tableMap[analyNonTerminal][*it]].right[0] != "@")
				{
					number = tableMap[analyNonTerminal][*it];
					for (int i = I_list[tableMap[analyNonTerminal][*it]].right.size() - 1; i >= 0; i--)
					{
						analyStr.push(I_list[tableMap[analyNonTerminal][*it]].right[i]);
					}
				}
			}
		}
		showAnalysis(analyStr, remainStrCopy, it, number);
	}
}

void input()
{
	vector<string>remainStr;					//余留输入串
	string ss;
	cout << "Waiting input, end with #" << endl;
	do
	{
		cin >> ss;
		remainStr.push_back(ss);
	} while (ss != "#");

	//将输入得字符串输入分析栈
	analyExp(remainStr);
}

void showFirst()
{
	cout << "==========First集==========" << endl;
	map<string, set<string>>::iterator it;
	for (it = first.begin(); it != first.end(); it++)
	{
		cout << "first(" << it->first << ")" << "{";
		set<string>::iterator it1;
		int i = 0;
		for (it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (i != it->second.size() - 1)
			{
				cout << *it1 << ",";
				i++;
			}
			else cout << *it1;
		}

		cout << "}" << endl;
	}
	cout << "==========First集==========" << endl;
	cout << endl;
}

void showFollow()
{
	cout << "==========Follow集==========" << endl;
	map<string, set<string>>::iterator it;
	for (it = follow.begin(); it != follow.end(); it++)
	{
		cout << "follow(" << it->first << ")" << "{";
		set<string>::iterator it1;
		int i = 0;
		for (it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (i != it->second.size() - 1)
			{
				cout << *it1 << ",";
				i++;
			}
			else cout << *it1;
		}

		cout << "}" << endl;
	}
	cout << "==========Follow集==========" << endl;
	cout << endl;
}

void showTable()
{
	cout << "==========分析表==========" << endl;

	set<string>::iterator it;
	int i = 0;
	for (it = Terminal.begin(); it != Terminal.end(); it++)
		cout << setw(20) << *it;
	cout << endl;

	map<string, map<string, int>>::iterator it1;
	for (it1 = tableMap.begin(); it1 != tableMap.end(); it1++)
	{
		cout << it1->first;
		for (it = Terminal.begin(); it != Terminal.end(); it++)
		{
			int flag = 0;
			map<string, int>::iterator it2;
			for (it2 = it1->second.begin(); it2 != it1->second.end(); it2++)
			{
				if (*it == it2->first)
				{
					flag = 1;
					cout << setw(20) << tableMap[it1->first][*it];
				}
			}
			if(flag == 0)cout << setw(20) << "error";
		}
		cout << endl;
	}

	cout << "==========分析表==========" << endl;
}


int main()
{
	init();

	set<string>::iterator it;
	for (it = nonTerminal.begin();it!=nonTerminal.end();it++)
	{
		calFirst(*it);
	}

	follow[I_list[0].left].insert("#");
	for (it = nonTerminal.begin(); it != nonTerminal.end(); it++)
	{
		calFollow(*it);
	}

	makeTable();
	
	showFirst();
	showFollow();
	showTable();

	input();

	return 0;
}