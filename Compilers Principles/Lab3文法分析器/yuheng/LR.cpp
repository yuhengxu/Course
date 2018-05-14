#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<map>

using namespace std;

#define path "C:\\Users\\yuheng\\Desktop\\rules"		//读取文法的路径
#define r_num 20							//产生式右部的字符个数
#define G_MIXN 200							//一个项目集I有多个产生式G
#define I_MIXN 500							//一个项目族集C有多个项目集I
#define buff_MIXN 200						//一个产生式G的最大长度

map<string, bool>non_terminal;				//非终结符集

class Gx									//一个产生式
{
public:
	string search = "#";					//搜索符
	string gleft;							//产生式左部的字符
	string gright[r_num];					//产生式右部的字符
	bool gright_type[r_num] = {false};		//右部成员属性，非终结符是true,终结符是false
	int gright_num = 0;						//产生式右部的字符个数
	int loop = 0;							//产生式中点的位置

public:
	Gx init_G(char* buff);					//从文本中读入一条产生式，对其进行初始化
	Gx type_G(int loop1, Gx g);				//对某一条文法中，当前loop处的字的类型做标记（终结符or非终结符）
}g1;

bool cmp_G(Gx* g1, Gx g2, int G_num);

class Ix									//一个项目集I
{
private:
	Gx G[G_MIXN];							//一个项目集I中有多个产生式G
	bool flag[G_MIXN] = { false };			//该项是否已经被加入到项目集中
	int G_num = 0;							//记录某个项目集中产生式的个数
public:
	Gx pop_I(int i);						//从该项目集中取出一条文法
	void closure(int flag1);				//求项目集的闭包
	void search_Char();						//对项目集中的每个项目求搜索符
	void push_I(Gx g);						//把某一条文法放入项目集中
	void print_I();							//打印整个项目集
	void init_non_terminal();				//初始化非终结符集
}I_list;									//项目集I用来存放当前已有的全部产生式

class Cx:public Ix
{
private:
	Ix I[I_MIXN];							//一个项目集规范族C有多个项目集I

public:
	void init_I(int i, Gx g);				//初始化项目集Ii，向该项目集中添加第一条文法，并求闭包
}C;

Gx Gx::init_G(char* buff)
{
	Gx G_demo;
	int i = 0, k = 0, l = 0;
	char buff_left[buff_MIXN], buff_right[buff_MIXN];
	
	while (buff[i] != ':')buff_left[i++] = buff[i];
	buff_left[i] = '\0';
	G_demo.gleft = buff_left;
	while (buff[i] != '\0' && buff[++i] != '\n')
	{
		buff_right[k++] = buff[i];
		if (buff[i] == ' ')
		{
			buff_right[k - 1] = '\0';
			G_demo.gright[l++] = buff_right;
			k = 0;
		}
	}
	buff_right[k] = '\0';
	G_demo.gright[l++] = buff_right;
	G_demo.gright_num = l;

	return G_demo;
}

Gx Gx::type_G(int loop1, Gx g)
{
	if (non_terminal[g.gright[loop1]] == true)
		g.gright_type[loop1] == true;
	return g;
}

Gx Ix::pop_I(int i)
{
	return G[i];
}

void Ix::print_I()
{
	for (int i = 0; i < G_num; i++)
	{
		cout << "left:" << G[i].gleft << "\t\t";
		for (int j = 0; j < G[i].gright_num; j++)
			cout << "right" << j << ":" << G[i].gright[j] << " ";
		cout << endl;
	}
}

void Ix::push_I(Gx g)
{
	G[G_num++] = g;
}

void Ix::init_non_terminal()
{
	for (int i = 0; i < G_num; i++)
		non_terminal[G[i].gleft] = true;
	/*for (int i = 0; i < G_num; i++)
		for (int j = 0; j < G[i].gright_num; j++)
			if (non_terminal[G[i].gright[j]] == true)
				G[i].gright_type[j] = true;*/
}

void Ix::closure(int flag1)
{
	//扫描项目集中已有的项，如果该项是待约项目则将其扩展出的项加入项目集
	for (int i = flag1; i < G_num; i++)			
	{
		//该项目是待约项目且未被加入到项目集中
		if (flag[i]==false && non_terminal[G[i].gright[G[i].loop]] == true)			
		{
			//扫描文法中左部是该非终结符的项目，将其加入
			for (int j = 0; j < I_list.G_num; j++)
			{
				if (I_list.G[j].gleft == G[i].gright[G[i].loop])
				{
					//对比项目集中已有的项目，若不同则加入
					if (cmp_G(G, I_list.G[j], G_num) == false)
					{
						push_I(I_list.G[j]);
						flag[i] = true;
						//如果新加入的项目仍然是一个待约项目，则再求closure
						if (non_terminal[I_list.G[j].gright[G[j].loop]] == true)
						{
							closure(i);
						}
					}
				}
			}
		}
	}
}

void Ix::search_Char()
{

}

void Cx::init_I(int i, Gx g)
{
	I[i].push_I(g);				//把Ii的第一条文法放入Ii中
	I[i].closure(0);			//求闭包
	I[i].search_Char();			//对Ii中的每条文法，求对应的搜索符
}

void init()
{
	FILE* fp = fopen(path, "r");
	char buff[buff_MIXN];
	int i = 0;
	while (fgets(buff, buff_MIXN, fp) != NULL)
	{
		if (buff[0] == '/' || buff[0] == '\n' || buff[0] == ' ')continue;
		I_list.push_I(g1.init_G(buff));
	}
	I_list.init_non_terminal();

	fclose(fp);
}

bool cmp_G(Gx* g1, Gx g2, int G_num)
{
	for (int i = 0; i < G_num; i++)
	{
		if (g1[i].gleft == g2.gleft)
		{
			if (g1[i].gright_num == g2.gright_num)
			{
				for (int j = 0; j < g2.gright_num; j++)
				{
					if (g1[i].gright[j] != g2.gright[j])
						break;
					else if (g1[i].gright_type[j] != g2.gright_type[j])
						break;
					else
					{
						if (g1[i].loop == g2.loop)
							if (g1[i].search == g2.search)
								return true;
					}
				}
			}
		}
	}
	return false;
}

int main()
{
	//初始化，将整个文法存入I_list中
	init();

	C.init_I(0, I_list.pop_I(0));


	////求整个项目集规范族
	//do
	//{

	//} while (1);

	return 0;
}