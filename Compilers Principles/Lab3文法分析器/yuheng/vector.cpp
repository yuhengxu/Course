#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<map>
#include<vector>
#include<set>

using namespace std;

#define path "C:\\Users\\yuheng\\Documents\\College\\Compilers Principles\\Lab3\\rule1"		//读取文法的路径
#define buff_MIXN 200						//一个产生式G的最大长度

map<string, bool>non_terminal;				//非终结符集

class Gx									//一个项目
{
public:
	int loop = 0;							//记录点的位置
	string left;							//产生式左部
	vector<string>right;					//产生式右部
	set<string>search;						//搜索符
											//vector<bool>right_type;					//右部成员属性，非终结符是true,终结符是false

public:

	Gx init_G(char* buff);					//从文本中读入一条产生式，对其进行初始化
}gx;

class Ix									//一个项目集I
{
private:
	vector<Gx>G;							//一个项目集I中有多个产生式G
public:

	Gx pop_G(int i);						//从该项目集中取出一条文法
	Gx init_FIRST(Gx &g1, Gx g2);			//求FRST集前先初始化，g2是项目集中的当前项，g1是求搜索符的待入项
	int size_I();							//返回项目集的大小
	void FIRST(Gx &g1, vector<string>Ba);	//求该项目的first(βa),进而求搜索符.
	void FIRST_empty(Gx &g1, vector<string>Ba);//判断"空"是否属于first(βa)
											   //void type_G();							//对项目集右部的字符做标记（终结符or非终结符）
	void closure(Gx g);						//求项目集的闭包
	void push_I(Gx g);						//把某一条文法放入项目集中
	void print_I();							//打印整个项目集
	void init_non_terminal();				//初始化非终结符集
	void init_search(string a);
}I_list;									//项目集I用来存放当前已有的全部产生式

class Cx
{
private:
	vector<Ix>I;							//一个项目集规范族C中有多个项目集I
public:

	int size();
	Ix pop_I(int i);						//从该项目集规范族中取出一个项目集		
	void push_I(Ix I1);
	void init_I(Gx g);						//初始化项目集Ii，向该项目集中添加第一条文法，并求闭包
	Ix closure(Ix I1);
	void Goto(Ix I1, set<string>next);		//对C中的每个项目集I和每个文法符号x，若goto[I, X]非空，且不再C中则把goto[I, X]加入到C
}C;

bool cmp_G(vector<Gx> g1, Gx g2, int G_num);
bool cmp_Gx(Gx g1, Gx g2);
bool same(Ix I1, Ix I3);

Gx Gx::init_G(char* buff)
{
	Gx G_demo;
	int i = 0, k = 0, l = 0;
	char buff_left[buff_MIXN], buff_right[buff_MIXN];
	while (buff[i] != ':')buff_left[i++] = buff[i];
	buff_left[i] = '\0';
	G_demo.left = buff_left;
	while (buff[i] != '\0' && buff[++i] != '\n')
	{
		buff_right[k++] = buff[i];
		if (buff[i] == ' ')
		{
			buff_right[k - 1] = '\0';
			G_demo.right.push_back(buff_right);
			k = 0;
		}
	}
	buff_right[k] = '\0';
	G_demo.right.push_back(buff_right);

	return G_demo;
}


Gx Ix::pop_G(int i)
{
	return G[i];
}

void Ix::print_I()
{
	for (int i = 0; i < G.size(); i++)
	{
		cout << "left:" << G[i].left << "\t\t";
		for (int j = 0; j < G[i].right.size(); j++)
			cout << "right" << j << ":" << G[i].right[j] << " ";
		cout << endl;
	}
}

void Ix::push_I(Gx g)
{
	G.push_back(g);
}

void Ix::init_non_terminal()
{
	for (int i = 0; i < G.size(); i++)
		non_terminal[G[i].left] = true;
}

void Ix::closure(Gx g)
{
	//判断该项是否已经存在于项目集中，若不存在将该项加入项目集
	if (cmp_G(G, g, G.size()) == false)
	{
		G.push_back(g);
		//判断该项是否为待约项目，如果是，则将其扩展出的项目也加入项目集中
		if (g.loop!=g.right.size() && non_terminal[g.right[g.loop]] == true)
		{
			//扫描文法中左部是该非终结符的项目，将其加入
			for (int i = 0; i < I_list.G.size(); i++)
			{
				if (I_list.G[i].left == g.right[g.loop])
				{
					//判断新的待扩展的项目是否已经存在于项目集中，若不存在则加入
					if (cmp_G(G, I_list.G[i], G.size()) == false)
					{
						Gx g1 = init_FIRST(I_list.G[i], g);
						if (non_terminal[I_list.G[i].right[I_list.G[i].loop]] == false)
						{
							G.push_back(g1);
						}
						//如果新扩展出的项目仍然是一个待约项目，则再求closure
						else if (non_terminal[I_list.G[i].right[I_list.G[i].loop]] == true)
						{
							closure(g1);
						}
					}
				}
			}
		}
	}
}

Gx Ix::init_FIRST(Gx &g1, Gx g2)
{
	//g1是求搜索符的待入项，g2是项目集中的当前项
	vector<vector<string>>Ba;
	vector<string>a;
	set<string>::iterator it;
	//遍历当前项中的所有搜索符，与g1的β部分拼接再一起
	for (it = g2.search.begin(); it != g2.search.end(); it++)
	{
		for (int i = g2.loop + 1; i < g2.right.size(); i++)
		{
			a.push_back(g2.right[i]);
		}
		a.push_back(*it);
		Ba.push_back(a);
	}

	/*debug
	Ba[0].clear();
	Ba[0].push_back("A");
	Ba[0].push_back("B");
	Ba[0].push_back("b");
	debug*/

	g1.search.clear();
	for (int i = 0; i < Ba.size(); i++)
	{
		FIRST(g1, Ba[i]);
		FIRST_empty(g1, Ba[i]);
	}

	return g1;
}

void Ix::FIRST(Gx &g1, vector<string>Ba)
{
	//首先再产生式的左侧找，找到以该非终结符开始的产生式，对他们进行分别查找

	//vector<string>::iterator it = Ba.begin();
	for (int i = 0; i < I_list.G.size(); i++)
	{
		if (I_list.G[i].left == Ba[0])
		{
			//如果右部推出空，就要向后传递
			//eg X->ABCD  A->empty  A->aAB,那此时我们就要将B的first集加入
			if (I_list.G[i].right[0] == "@")
			{
				vector<string>Ba1 = Ba;
				Ba1.erase(Ba1.begin());
				FIRST(g1, Ba1);
			}
			//若果右侧开始时终结符，就将之加入
			else if (non_terminal[I_list.G[i].right[0]] == false)
			{
				g1.search.insert(I_list.G[i].right[0]);
			}
			//如果右部开始时非终结符，就递归查找该终结符
			else
			{
				FIRST(g1, I_list.G[i].right);
			}
		}
		else if (I_list.G[i].left != Ba[0] && i == (I_list.G.size() - 1) && non_terminal[Ba[0]] == false)
		{
			g1.search.insert(Ba[0]);
		}
	}
}

void Ix::FIRST_empty(Gx &g1, vector<string>Ba)
{
	//for (int i = 0; i < Ba.size(); i++)
	//{
	//	//如果有一个是终结符就说明推不出空
	//	if (non_terminal[Ba[i]] = false)
	//		break;
	//	else
	//	{

	//	}
	//}
}

void Ix::init_search(string a)
{
	G[0].search.insert(a);
}

int Ix::size_I()
{
	return G.size();
}

Ix Cx::pop_I(int i)
{
	return I[i];
}

void Cx::push_I(Ix I1)
{
	I.push_back(I1);
}

void Cx::init_I(Gx g)
{
	Ix I1;
	I.push_back(I1);
	I.back().closure(g);			//把第一条文法放入项目集Ii，并求闭包
}

void Cx::Goto(Ix I1, set<string>next)
{
	bool flag = false;
	set<string>::iterator it;
	//当前项目集可以经过字符集next到达新的项目集，遍历可经过得字符
	for (it = next.begin(); it != next.end(); it++)
	{
		Ix I2;
		//遍历项目集经过字符next[i]到达新的项目集
		for (int i = 0; i < I1.size_I(); i++)
		{
			//判断该项目loop处得字符和next[i]是否相等
			Gx g1 = I1.pop_G(i);
			if (g1.loop<g1.right.size() && g1.right[g1.loop] == *it)
			{
				g1.loop++;						//点向后移动一位
				I2.push_I(g1);					//将新的项目加入项目集
			}
		}

		Ix I3 = C.closure(I2);					//对项目集I2求闭包得到新的项目集I3
		for (int i = 0; i < C.size(); i++)
		{
			if (same(C.pop_I(i), I3) == true)
			{
				flag = true;
				break;
			}
		}
		if (flag == true)						//判断该项目集规范族中的每一项Ii和项目集I1是否相等
		{
			flag = false;
			continue;
		}
		C.push_I(I3);							//项目集I3即为项目集规范族得一个新的项目集，将其加入C
		set<string>next1;						//求解新的项目集I3经过得字符集next1可以到达新的项目
		for (int i = 0; i < I3.size_I(); i++)
		{
			Gx g_demo = I3.pop_G(i);
			if (g_demo.loop < g_demo.right.size())
				next1.insert(g_demo.right[g_demo.loop]);
		}
		if (next1.size() != 0)
			Goto(I3, next1);
	}
}

Ix Cx::closure(Ix I1)
{
	vector<Ix>I_chongfu;
	for (int i = 0; i < I1.size_I(); i++)
	{
		Gx g1 = I1.pop_G(i);
		Ix I2;
		I2.closure(g1);
		I_chongfu.push_back(I2);
	}
	Ix I3 = I_chongfu[0];
	for (int i = 1; i < I_chongfu.size(); i++)
	{
		for (int j = 0; j < I_chongfu[i].size_I(); j++)
		{
			int k = 0;
			for (k = 0; k < I3.size_I(); k++)
			{
				if (cmp_Gx(I3.pop_G(k), I_chongfu[i].pop_G(j)) == true)
				{
					break;
				}
			}
			if (k == I3.size_I())
				I3.push_I(I_chongfu[i].pop_G(j));
		}
	}
	return I3;
}

int Cx::size()
{
	return I.size();
}


void init()
{
	FILE* fp = fopen(path, "r");
	char buff[buff_MIXN];
	int i = 0;
	while (fgets(buff, buff_MIXN, fp) != NULL)
	{
		if (buff[0] == '/' || buff[0] == '\n' || buff[0] == ' ')continue;
		I_list.push_I(gx.init_G(buff));
	}

	I_list.init_non_terminal();
	//I_list.type_G();

	fclose(fp);
}

bool cmp_G(vector<Gx> g1, Gx g2, int G_num)
{
	for (int i = 0; i < G_num; i++)
	{
		if (g1[i].left == g2.left && g1[i].right.size() == g2.right.size())
		{
			for (int j = 0; j < g2.right.size(); j++)
			{
				if (g1[i].right[j] != g2.right[j] || g1[i].loop != g2.loop)
				{
					return false;
				}
				else if (g1[i].right[j] == g2.right[j] && g1[i].loop == g2.loop && j == (g2.right.size() - 1))
				{
					set<string>::iterator it1 = g1[i].search.begin();
					set<string>::iterator it2 = g2.search.begin();
					for (it2 = g2.search.begin(), it1 = g1[i].search.begin(); it2 != g2.search.end(); it1++, it2++)
					{
						if (*it1 != *it2)return false;
					}
					return true;
				}
			}
		}
	}
	return false;
}

bool cmp_Gx(Gx g1, Gx g2)
{
	if (g1.left == g2.left && g1.right.size() == g2.right.size())
	{
		for (int j = 0; j < g2.right.size(); j++)
		{
			if (g1.right[j] != g2.right[j] || g1.loop != g2.loop)
			{
				return false;
			}
			else if (g1.right[j] == g2.right[j] && g1.loop == g2.loop && j == (g2.right.size() - 1))
			{
				set<string>::iterator it1 = g1.search.begin();
				set<string>::iterator it2 = g2.search.begin();
				for (it2 = g2.search.begin(), it1 = g1.search.begin(); it2 != g2.search.end(); it1++, it2++)
				{
					if (*it1 != *it2)return false;
				}
				return true;
			}
		}
	}
	return false;
}

bool same(Ix I1, Ix I3)
{
	for (int i = 0; i < I1.size_I(); i++)
	{
		for (int j = 0; j < I3.size_I(); j++)
		{
			if (cmp_Gx(I1.pop_G(i), I3.pop_G(j)) == true)
				break;
			else if (j == (I3.size_I() - 1) && cmp_Gx(I1.pop_G(i), I3.pop_G(j)) == false)
				return false;								//I3中得某一条与I1中得任意一条都不同，说明这是一个新的项目集
		}
	}
	return true;
}

int main()
{
	init();
	I_list.init_search("#");
	C.init_I(I_list.pop_G(0));

	Ix I_demo = C.pop_I(0);
	set<string>next;
	for (int i = 0; i < I_demo.size_I(); i++)
	{
		Gx g_demo = I_demo.pop_G(i);
		next.insert(g_demo.right[g_demo.loop]);
	}

	C.Goto(I_demo, next);

	printf("haha\n");
	return 0;
}