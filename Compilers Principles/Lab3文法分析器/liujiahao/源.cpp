#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <string>
#include <cctype>
#include <stack>
#include <map>
#include <set>
#include <conio.h>
#include<fstream>
#define MAX 507
#ifndef MAKETREE_H
#define MAKETREE_H
#ifndef TRAVERSAL_H
#define TRAVERSAL_H
#ifndef TREENODE_H
#define TREENODE_H
#define STR_FILENAME "in.txt"
#define STR_ADD_NODE "node"
#define STR_ADD_LEAF "leaf"
#define STR_FATHER_CHILD "fc"
#define STR_DELETE "del"
#define STR_PREORDER "preorder"
#define STR_INORDER "inorder"
#define STR_POSTORDER "postorder"
#define STR_EXIT "exit"
using namespace std;
ofstream fout; 
class CTreeNode;	//前置申明，tNodeLink和CTreeNode互相含有彼此
struct tNodeLink
{
	CTreeNode *pChild;		//儿子节点的地址
	tNodeLink *pNext;
};
class Tree
{
public:
	Tree();
	~Tree();
	int getSum();									//获取节点总数
	void addTreeNode(float value);					//增加普通节点
	void addLeafNode(float value);					//增加叶子节点
	CTreeNode *pNode(int num);						//返回编号为num的节点地址
	bool fatherChild(int numFather, int numChild);	//绑定父子关系
	bool delNode(int num);							//删除节点
	
private:
	int m_sum;				//节点总数
	tNodeLink *m_pHead;		//节点链表头
};
void preorderTraversal(CTreeNode *pRoot);	//先序遍历
void inorderTraversal(CTreeNode *pRoot);	//中序遍历
void postorderTraversal(CTreeNode *pRoot);	//后序遍历



//节点链表结构体


//树节点类
class CTreeNode
{
public:
	friend class Tree;

	CTreeNode();
	~CTreeNode();
	int getNum();									//获取编号
	float getValue();								//获取节点的值
	void setValue(float value);						//获取节点的值
	tNodeLink *getChildHead();						//取出儿子节点链表头
	bool hasFatherNode();							//判断是否有父亲节点
	bool setFatherNode(CTreeNode *pFather);			//设置父亲节点
	virtual bool addChildNode(CTreeNode *pChild);	//增加儿子节点
	bool delChildNode(CTreeNode *pChild);			//删除儿子节点
	void setLeaf();									//设置成叶子节点

private:
	static int s_max;		//已分配的编号的数目
	int m_num;				//节点编号
	float m_value;			//节点的值
	CTreeNode *m_pFather;	//父亲节点
	tNodeLink *m_pChildHead;//儿子节点链表
	bool m_bLeaf;
};

//树叶子节点类（继承树节点类）
class CLeafNode : public CTreeNode
{
public:
	CLeafNode();
	bool addChildNode(CTreeNode *pChild);	//增加儿子节点
};

#endif
#endif
#endif




char tnode[MAX];
int nodenum;
FILE *fp;
//大写字母为非终止符(可以多一个'的标号做区分)，小写字母为终止符,用~代替epsilon
FILE *g_pFilePointer;

char g_cmd[256];
float g_value;
int g_num, g_child;
Tree g_tree;
Tree::Tree()
{
	m_sum = 0;
	m_pHead = NULL;
}

/*析构函数*/
Tree::~Tree()
{
	tNodeLink *pCurrent = m_pHead;
	tNodeLink *pNext;

	//释放所有的节点
	while (pCurrent != NULL)
	{
		pNext = pCurrent->pNext;

		delete pCurrent->pChild;
		delete pCurrent;

		pCurrent = pNext;
	}
}

/*获取节点总数*/
int Tree::getSum()
{
	return m_sum;
}

/*增加普通节点*/
void Tree::addTreeNode(float value)
{
	tNodeLink **ppLast = &this->m_pHead;
	tNodeLink *pCurrent = m_pHead;
	tNodeLink *pNewLink = new tNodeLink;
	CTreeNode *pNewTreeNode = new CTreeNode;	//申请一个普通节点

	pNewLink->pChild = pNewTreeNode;
	pNewTreeNode->setValue(value);

	//找到最后一个节点
	while (pCurrent != NULL)
	{
		ppLast = &pCurrent->pNext;
		pCurrent = pCurrent->pNext;
	}

	//插入新节点
	*ppLast = pNewLink;
	pNewLink->pNext = NULL;

}

/*增加叶子节点*/
void Tree::addLeafNode(float value)
{
	tNodeLink **ppLast = &this->m_pHead;
	tNodeLink *pCurrent = m_pHead;
	tNodeLink *pNewLink = new tNodeLink;
	CLeafNode *pNewLeafNode = new CLeafNode;	//申请一个叶子节点

	pNewLink->pChild = pNewLeafNode;
	pNewLeafNode->setValue(value);

	//找到最后一个节点
	while (pCurrent != NULL)
	{
		ppLast = &pCurrent->pNext;
		pCurrent = pCurrent->pNext;
	}

	//插入新节点
	*ppLast = pNewLink;
	pNewLink->pNext = NULL;
}

/*返回编号为num的节点地址*/
CTreeNode *Tree::pNode(int num)
{
	tNodeLink *pCurrent = m_pHead;

	while (pCurrent != NULL)
	{
		if (pCurrent->pChild->getNum() == num) return pCurrent->pChild;

		pCurrent = pCurrent->pNext;
	}

	return NULL;
}

/*绑定父子关系*/
bool Tree::fatherChild(int numFather, int numChild)
{
	char flag;
	CTreeNode *pAncestor;
	CTreeNode *pFather = pNode(numFather);
	CTreeNode *pChild = pNode(numChild);

	if (numFather == numChild)
	{
		printf("不能和自己建立父子关系\n");
		return false;
	}

	//父亲节点编号无效
	if (pFather == NULL)
	{
		printf("没有编号为%d的节点\n", numFather);
		return false;
	}

	//儿子节点编号无效
	if (pChild == NULL)
	{
		printf("没有编号为%d的节点\n", numChild);
		return false;
	}
	//检查是否形成环路
	pAncestor = pFather->m_pFather;
	while (pAncestor != NULL)
	{	
	
		if (pAncestor == pChild)
		{
			printf("形成环路\n");
			return false;
		}

		pAncestor = pAncestor->m_pFather;
	}
	if (pFather->addChildNode(pChild) == false) return false;
	if (pChild->hasFatherNode() == true)
	{
		printf("警告：已有父亲节点，按任意键继续，ESC取消");
		flag = getch();
		if (flag == '\033')
		{
			pFather->delChildNode(pChild);
			return false;
		}
	}

	pChild->setFatherNode(pFather);

	return true;
}

/*删除节点*/
bool Tree::delNode(int num)
{
	tNodeLink **ppLast = &this->m_pHead;
	tNodeLink *pCurrent = this->m_pHead;

	while (pCurrent != NULL)
	{
		if (pCurrent->pChild->getValue() == num)
		{
			*ppLast = pCurrent->pNext;

			delete pCurrent->pChild;
			delete pCurrent;

			return true;
		}

		ppLast = &pCurrent->pNext;
		pCurrent = pCurrent->pNext;
	}

	return false;
}




int i=0;
void preorderTraversal(CTreeNode *pRoot)
{
	for(int j=0;j<i;j++)
	{
		printf("    ");
		fout<<"  ";
	}
	tNodeLink *pCurrend;
	
	if (pRoot != NULL)
	{
		if((tnode[pRoot->getNum()-1]>='A')&&(tnode[pRoot->getNum()-1]<='Z'))
		{
			if(tnode[pRoot->getNum()-1]=='T')
				fout<<"<Type>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='A')
				fout<<"<ARGS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='G')
				fout<<"<FRAGS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='B')
				fout<<"<ALIST>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='U')
				fout<<"<UNION>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='E')
				fout<<"<PROGRAM>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='I')
				fout<<"<IDENT>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='S')
				fout<<"<STMTS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='P')
				fout<<"<PLUS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='O')
				fout<<"<OPER>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='Q')
				fout<<"<CLOS>"<<endl;
		//	fout<<"<"<<tnode[pRoot->getNum()-1]<<">"<<endl;
		printf("<%d>\n", pRoot->getNum());
		pCurrend = pRoot->getChildHead();
		}
		else 
		{
			if(tnode[pRoot->getNum()-1]=='i')
				fout<<"<keyword>int</keyword>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='r')
				fout<<"<keyword>return</keyword>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='m')
				fout<<"<identifier>main</identifier>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='a')
				fout<<"<identifier>a</identifier>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='b')
				fout<<"<identifier>b</identifier>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='(')
				fout<<"<separator>(</separator>"<<endl;
			else if(tnode[pRoot->getNum()-1]==')')
				fout<<"<separator>)</separator>"<<endl;
			else if(tnode[pRoot->getNum()-1]==',')
				fout<<"<separator>,</separator>"<<endl;
			else if(tnode[pRoot->getNum()-1]==';')
				fout<<"<separator>;</separator>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='{')
				fout<<"<separator>{</separator>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='}')
				fout<<"<separator>}</separator>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='+')
				fout<<"<operarator>+</operarator>"<<endl;
		//	fout<<tnode[pRoot->getNum()-1]<<endl;
		printf("<%d>\n", pRoot->getNum());
		pCurrend = pRoot->getChildHead();
		}
		//先遍历根
		for(int j=0;j<i;j++)
	{
		printf("    ");
	}
		printf("节点编号%5d: %f\n", pRoot->getNum(), pRoot->getValue());
		
		//再遍历儿子
		
		while (pCurrend != NULL)
		{
			i++;
			preorderTraversal(pCurrend->pChild);
			i--;
			pCurrend = pCurrend->pNext;
		}

		if((tnode[pRoot->getNum()-1]>='A')&&(tnode[pRoot->getNum()-1]<='Z'))
		{
			for(int j=0;j<i;j++)
			{
				printf("    ");
				fout<<"  ";
			}
			if(tnode[pRoot->getNum()-1]=='T')
				fout<<"</Type>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='A')
				fout<<"</ARGS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='G')
				fout<<"</FRAGS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='B')
				fout<<"</ALIST>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='U')
				fout<<"</UNION>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='E')
				fout<<"</PROGRAM>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='I')
				fout<<"</IDENT>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='S')
				fout<<"</STMTS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='P')
				fout<<"</PLUS>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='O')
				fout<<"</OPER>"<<endl;
			else if(tnode[pRoot->getNum()-1]=='Q')
				fout<<"</CLOS>"<<endl;
		//	fout<<"</"<<tnode[pRoot->getNum()-1]<<">"<<endl;
		}
		printf("</%d>\n",pRoot->getNum());

	}
}

int CTreeNode::s_max = 0;	//已分配节点数目初始化为0

CTreeNode::CTreeNode()
{
	m_num = ++s_max;	//为节点分配一个独立的编号
	m_value = 0;		//初始化节点的值
	m_pFather = NULL;	//初始化父亲节点为空
	m_pChildHead = NULL;//初始化儿子链表头为空
	m_bLeaf = false;	//不是叶子节点
}

CTreeNode::~CTreeNode()
{
	tNodeLink *pCurrent = this->m_pChildHead;
	tNodeLink *pNext;

	//如果有父亲，则将自己从父亲的儿子链表中删除
	if (m_pFather != NULL) m_pFather->delChildNode(this);

	//删除儿子们的父亲
	while (pCurrent != NULL)
	{
		pNext = pCurrent->pNext;
		
		//释放儿子链表的空间
		(pCurrent->pChild)->setFatherNode(NULL);
		pCurrent = pNext;
	}
}

/*获取编号*/
int CTreeNode::getNum()
{
	return m_num;
}

/*获取节点的值*/
float CTreeNode::getValue()
{
	return m_value;
}

/*设置节点的值*/
void CTreeNode::setValue(float value)
{
	m_value = value;
}

/*获取儿子节点链表头的指针*/
tNodeLink *CTreeNode::getChildHead()
{
	return m_pChildHead;
}

/*判断是否有父亲节点*/
bool CTreeNode::hasFatherNode()
{
	if (m_pFather == NULL) return false;

	return true;
}


//设置父亲节点

bool CTreeNode::setFatherNode(CTreeNode *pFather)
{
	//已有父亲节点
	if (m_pFather != NULL) m_pFather->delChildNode(this);
	
	//设置
	m_pFather = pFather;

	return true;
}

//增加儿子节点

bool CTreeNode::addChildNode(CTreeNode *pChild)
{
	tNodeLink **ppLast = &this->m_pChildHead;
	tNodeLink *pCurrent = this->m_pChildHead;
	tNodeLink *pNewChild;

	//儿子指针为空
	if (pChild == NULL)
	{
		printf("错误：儿子指针为空\n");
		return false;
	}

	if (this->m_bLeaf == true)
		return (CLeafNode *)(this)->addChildNode(pChild);
	
	//指向链表最后一个儿子
	while (pCurrent != NULL)
	{
		ppLast = &pCurrent->pNext;
		pCurrent = pCurrent->pNext;
	}
	
	//加入新儿子
	pNewChild = new tNodeLink;
	pNewChild->pChild = pChild;
	pNewChild->pNext = NULL;
	*ppLast = pNewChild;

	return true;
}

//删除儿子节点

bool CTreeNode::delChildNode(CTreeNode *pChild)
{
	tNodeLink **ppLast = &this->m_pChildHead;
	tNodeLink *pCurrent = this->m_pChildHead;

	//儿子指针为空
	if (pChild == NULL)
	{
		printf("错误：儿子指针为空\n");
		return false;
	}

	while (pCurrent != NULL)
	{
		//找到儿子节点
		if (pCurrent->pChild == pChild)
		{
			*ppLast = pCurrent->pNext;
			delete pCurrent;

			return true;
		}

		ppLast = &pCurrent->pNext;
		pCurrent = pCurrent->pNext;
	}

	//没找到儿子
	return false;
}

/*设置成叶子节点*/
void CTreeNode::setLeaf()
{
	m_bLeaf = true;
}

/*主构函数*/
CLeafNode::CLeafNode()
{
	setLeaf();
}

/*
增加儿子节点
1.不予许
*/
bool CLeafNode::addChildNode(CTreeNode *pChild)
{
	printf("叶子节点不能有儿子节点\n");

	return false;
}
class WF
{
    public:
    string left;
    set<string> right;
    WF ( char s[] )
    {
        left = s;
    }
    void print ( )
    {
        printf ( "%s->" , left.c_str() );
        set<string>::iterator it = right.begin();
        if ( right.begin()!= right.end() )
        {
            printf ( "%s" , it->c_str() );
            it++;
        }
        for(; it != right.end() ; it++ )
            printf ( "|%s" , it->c_str() );
        puts("");
    }
    void insert ( char s[] )
    {
        right.insert ( s );
    }
};

map<string,set<char> > first;
map<string,set<char> > follow;
map<string,int> VN_dic;
vector<WF> VN_set;
bool used[MAX];

void dfs ( int x )
{
    if ( used[x] ) return;
    used[x] = 1;
    string& left = VN_set[x].left;
    set<string>& right = VN_set[x].right;
    set<string>::iterator it = right.begin();
    for ( ; it!= right.end() ; it++ )
        for ( int i = 0 ; i < it->length() ; i++ )
        {
            if ( !isupper( it->at(i) ) && it->at(i) != '\'' )
            {
                first[left].insert ( it->at(i) );
                break;
            }
            if ( isupper( it->at(i) ) )
            {
                int y;
                if ( i != it->length()-1 && it->at(i+1) == '\'' )
                    y = VN_dic[it->substr(i,2)]-1;
                else y = VN_dic[it->substr(i,1)]-1;
                string& tleft = VN_set[y].left;
                dfs ( y );
                set<char>& temp = first[tleft];
                set<char>::iterator it1 = temp.begin();
                bool flag = true;
                for ( ; it1 != temp.end() ; it1++ )
                {
                    if ( *it1 == '~' ) flag = false;
                    first[left].insert( *it1 );
                }
                if ( flag ) break;
            }
            else continue;
        }
}

void make_first ( )
{
    memset ( used , 0 , sizeof ( used ) );
    for ( int i = 0 ; i < VN_set.size() ; i++ )
        dfs ( i );
#define DEBUG
#ifdef DEBUG
        puts ("***************FIRST集***********************");
        map<string,set<char> >::iterator it = first.begin();
        for ( ; it != first.end() ; it++ )
        {
            printf ( "FIRST(%s)={" , it->first.c_str() );
            set<char> & temp = it->second;
            set<char>::iterator it1 = temp.begin();
            bool flag = false;
            for ( ; it1 != temp.end() ; it1++ )
            {
                if ( flag ) printf ( "," );
                printf ( "%c" , *it1 );
                flag = true;
            }
            puts ("}");
        }
#endif
}

void append ( const string& str1 , const string& str2 )
{
    set<char>& from = follow[str1];
    set<char>& to = follow[str2];
    set<char>::iterator it = from.begin();
    for ( ; it != from.end() ; it++ )
        to.insert ( *it );
}

void make_follow ( )
{
    while ( true )
    {
        bool goon = false;
        for ( int i = 0 ; i < VN_set.size() ; i++ )
        {
            string& left = VN_set[i].left;
            set<string>& right = VN_set[i].right;
            set<string>::iterator it = right.begin();
            for ( ; it!= right.end() ; it++ )
            {
                bool flag = true;
                const string& str = *it;
                for ( int j = it->length()-1 ; j >= 0 ; j-- )
                {
                    if ( str[j] == '\'' )
                    {
                        int x = VN_dic[it->substr(j-1,2)]-1;
                        if ( flag ) 
                        {
                            int tt = follow[it->substr(j-1,2)].size();
                            append ( left , it->substr(j-1,2) );
                            int tt1 = follow[it->substr(j-1,2)].size();
                            if ( tt1 > tt ) goon = true;
                            if ( !VN_set[x].right.count("~" ) ) 
                                flag = false;
                        }
                        for ( int k = j+1 ; k < it->length() ; k++ )
                        {
                            if ( isupper(str[k]) )
                            {
                                string id;
                                if ( k != it->length()-1 && str[k+1] == '\'' )
                                    id = it->substr(k,2);
                                else id = it->substr(k,1);
                                set<char>& from = first[id];
                                set<char>& to = follow[it->substr(j-1,2)];
                                int tt = to.size();
                                set<char>::iterator it1 = from.begin();
                                for ( ; it1 != from.end() ; it1++ )
                                    if ( *it1 != '~' )
                                        to.insert ( *it1 );
                                int tt1 = follow[it->substr(j-1,2)].size();
                                if ( tt1 > tt ) goon = true;
                                if ( !VN_set[VN_dic[id]-1].right.count("~") )
                                    break;
                            }
                            else if ( str[k] != '\'' )
                            {
                                int tt = follow[it->substr(j-1,2)].size();
                                follow[it->substr(j-1,2)].insert ( str[k] );
                                int tt1 = follow[it->substr(j-1,2)].size();
                                if ( tt1 > tt )
                                    goon = true;
                                break;
                            }
                            else continue;
                        }
                        j--;
                    }
                    else if ( isupper(str[j] ) )
                    {
                        int x = VN_dic[it->substr(j,1)]-1;
                        if ( flag )
                        {
                            int tt = follow[it->substr(j,1)].size();
                            append ( left , it->substr(j,1) );
                            if ( !VN_set[x].right.count("~") )
                                flag = false;
                            int tt1 = follow[it->substr(j,1)].size();
                            if ( tt1 > tt ) goon = true;
                        }
                        for ( int k = j+1 ; k < it->length() ; k++ )
                        {
                            if ( isupper( str[k] ) )
                            {
                                string id;
                                if ( k != it->length()-1 && str[k+1] == '\'' )
                                    id = it->substr(k,2);
                                else id = it->substr(k,1);
                                set<char>& from = first[id];
                                set<char>& to = follow[it->substr(j,1)];
                                set<char>::iterator it1 = from.begin();
                                int tt = follow[it->substr(j,1)].size();
                                for ( ; it1 != from.end() ; it1++ )
                                    if ( *it1 != '~' )
                                        to.insert( *it1 );
                                int tt1 = follow[it->substr(j,1)].size();
                                if ( tt1 > tt ) goon = true;
                                if ( !VN_set[VN_dic[id]-1].right.count("~") )
                                    break;
                            }
                            else if ( str[k] != '\'' )
                            {
                                int tt = follow[it->substr(j,1)].size();
                                follow[it->substr(j,1)].insert ( str[k] );
                                int tt1 = follow[it->substr(j,1)].size();
                                if ( tt1 > tt ) goon = true;
                                break;
                            }
                            else continue;
                        }
                    }
                    else flag = false;
                }
            }
        }
        if ( !goon ) break;
    }
#define DEBUG
#ifdef DEBUG
    puts ("****************FOLLOW集**********************" );
    map<string,set<char> >::iterator it = follow.begin();
    for ( ; it != follow.end() ; it++ )
    {
        printf ( "FOLLOW(%s)={" , it->first.c_str() );
        set<char> & temp = it->second;
        temp.insert('#');
        set<char>::iterator it1 = temp.begin();
        bool flag = false;
        for ( ; it1 != temp.end() ; it1++ )
        {
            if ( flag ) printf ( "," );
            printf ( "%c" , *it1 );
            flag = true;
        }
        puts ("}");
    }
#endif
}

vector<map<char,string> > predict_table;

//检查一个字符是否属于一个字符串的FIRST集合
bool check_first ( const string& text , char ch )
{
    for ( int i = 0 ; i < text.length() ; i++ )
    {
        bool hasEmpty = false;
        if ( !isupper(text[i]) && text[i] != '\'' )
        {
            if ( text[i] != ch ) return false;
            else return true;
        }
        else if ( isupper(text[i] ) )
        {
            string temp;
            if ( i != text.length()-1 && text[i+1] == '\'' )
                temp = text.substr(i,2);
            else
                temp = text.substr(i,1);
            set<char>& dic = first[temp];
            set<char>::iterator it = dic.begin();
            for ( ; it != dic.end() ; it++ )
            {
                if ( *it == '~' ) hasEmpty = true;
                if ( *it == ch ) return true;
            }
            if ( !hasEmpty) break;
        }
        else continue;
    }
    return false;
}

//检查一个字符是否属于一个字符串的FOLLOW集合
bool check_follow ( const string& text , char ch )
{
    set<char>& dic = follow[text];
    set<char>::iterator it = dic.begin();
    for ( ; it != dic.end() ; it++ )
        if ( *it == ch ) return true;
    return false;
}

void make_table ()
{
    map<char,string> temp;
    vector<char> letter;
    bool vis[500];
    memset ( vis , 0 , sizeof ( vis ) );
    for ( int i = 0 ; i < VN_set.size() ; i++ )
    {
        set<string>& right = VN_set[i].right;
        set<string>::iterator it = right.begin();
        for ( ; it != right.end() ; it++ )
            for ( int j = 0 ; j < it->length() ; j++ )
                if ( !isupper(it->at(j)) && it->at(j) != '\'' ) 
                {
                    if ( vis[it->at(j)] ) continue;
                    vis[it->at(j)] = true;
                    letter.push_back ( it->at(j) );
                }
    }
    for ( int i = 0 ; i < VN_set.size() ; i++ )
    {
        temp.clear();
        string& left = VN_set[i].left;
        set<string>& right = VN_set[i].right;
        set<string>::iterator it = right.begin();
        for ( ; it != right.end() ; it++ )
            for ( int j = 0 ; j < letter.size() ; j++ )
            {
                //cout << *it << " " <<  letter[j] << endl;
                if ( check_first ( *it , letter[j] ) )
                {
                    //cout << "YES" << endl;
                    temp[letter[j]] = *it;
                }
                if ( it->at(0) == '~' && check_follow ( left, letter[j] ))
                    temp[letter[j]] = *it;
            }
        predict_table.push_back ( temp );
    }
#define DEBUG
#ifdef DEBUG
    for ( int i = 0 ; i <= (letter.size()+1)*10 ; i++ )
        printf ( "-" );
    puts ("");
    printf ( "|%9s" , "|" );
    for ( int i = 0 ; i < letter.size() ; i++ )
        printf ( "%5c%5s" , letter[i] , "|" );
    puts("");
    for ( int i = 0 ; i <= (letter.size()+1)*10 ; i++ )
        printf ( "-" );
    puts("");
    for ( int i = 0 ; i < VN_set.size() ; i++ )
    {
        printf ( "|%5s%4s" , VN_set[i].left.c_str() , "|" );
        for ( int j = 0 ; j < letter.size() ; j ++ )
            if ( predict_table[i].count(letter[j] ) )
                printf ( "%7s%3s" , predict_table[i][letter[j]].c_str() , "|" );
            else printf ( "%10s" , "|" );
        puts("");
        for ( int i = 0 ; i <= (letter.size()+1)*10 ; i++ )
            printf ( "-" );
        puts ("");
    }
#endif
}
string stackin[MAX];
int tempnum;
void print ( int steps , stack<string> stk , string src , string wf , int x )
{
    printf ( "%-10d?" , steps );
    string out = "";
    while ( !stk.empty() )
    {
        out = stk.top()+out;
        stk.pop();
    }
    printf ( "#%-9s!" , out.c_str() );
    out ="";
    for ( int i = x ; i < src.length() ; i++ )
        out += src[i];
    printf ( "%-10s@" , (out+"#").c_str() );
	stackin[tempnum]+=wf.c_str();

    printf ( "%-10s&\n" , wf.c_str() );
}

void analyse ( const string& src )
{
    stack<string> stk;
    stk.push ( "E" );
	tnode[nodenum]='E';
	nodenum++;
	fputs("node 1\n",fp);
    int steps = 0;
    int idx = 0;
    printf ( "%-10s%-10s%-10s%-10s\n" , "步骤","符号栈","输入串","所用产生式" );
    while ( !stk.empty() )
    {
        string u = stk.top();
        string tmp="";
        stk.pop();
        if ( !isupper(u[0]) ) 
        {
            if ( idx == src.length() && u[0] == '~' );
            else if ( src[idx] == u[0] ) 
			{
				
                idx++;
				cout<<"part of tail"<<src[idx]<<endl;
			}
        }
        else 
        {
            int x = VN_dic[u]-1;
            tmp = predict_table[x][src[idx]];
			cout<<"tail"<<tmp<<endl;
            for ( int i = tmp.length()-1 ; i >= 0 ; i-- )
            {
                if ( tmp[i] == '\'' )
                {
                    string v = tmp.substr(i-1,2);
                    stk.push ( v );
                    i--;
                }
                else
                {
                    string v = tmp.substr(i,1);
                    stk.push( v );
                }
            }
			const char *temp1=u.c_str();
			int head=0;
			for(int tempi=nodenum-1;tempi>=0;tempi--)
			{
				if(temp1[0]==tnode[tempi])
				{
					head=tempi+1;
					break;
				}
			}
			int length=tmp.length();
			const char *temp2=tmp.c_str();
			for(int tempi=0;tempi<length;tempi++)
			{
				if(temp2[tempi]>='A'&&temp2[tempi]<='Z')
				{
					tnode[nodenum]=temp2[tempi];
					nodenum++;
					fprintf(fp,"node %d\n",nodenum);
					fprintf(fp,"fc %d %d\n",head,nodenum);
				}
				else 
				{
					tnode[nodenum]=temp2[tempi];
					nodenum++;
					fprintf(fp,"leaf %d\n",nodenum);
					fprintf(fp,"fc %d %d\n",head,nodenum);
				}
			}
            tmp = u+"->"+tmp;
			cout<<"head"<<u<<endl;
        }
		cout<<tmp<<"!!!!!!!!!!!"<<endl;
        print ( steps++ , stk , src , tmp  , idx );
		tempnum++;
    }
}

int main ( )
{
    int n=16;
    char s[MAX];
	fp=fopen("in.txt","w");
	char input[17][MAX]={"E->TI(A){S}","T->i","I->m","I->a","I->b","A->GB","G->TI","B->UG","U->,","S->RP","R->r","P->IQ;","Q->OI","O->+","O->-","O->*","O->/"};
        for ( int i = 0 ; i < n ; i++ )
        {
            strcpy(s,input[i]);
            int len = strlen ( s ),j;
            for ( j = 0 ; j < len ; j++ )
                if ( s[j] == '-' ) break;
            s[j] = 0;
            if ( !VN_dic[s] )
            {
                VN_set.push_back ( s );
                VN_dic[s] = VN_set.size();
            }
            int x = VN_dic[s]-1;
            VN_set[x].insert ( s+j+2 );
        }
        make_first();
        make_follow();
        make_table();
		string in = "im(ia,ib){ra+b;}";
        analyse( in );
		fputs("preorder 1\n",fp);
		fputs("exit\n",fp);
		for(int i=0;i<nodenum;i++)
		{
			printf("%c %d\n",tnode[i],i+1);
		}
    fclose(fp);
	char key;

	//以只读方式打开文件，返回文件指针

	g_pFilePointer = fopen(STR_FILENAME, "r");
	fout.open("test.tree.xml");
	//fout<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<endl<<"<ParserTree name=\"test.tree.xml\">"<<endl;
	//判断文件指针是否正确
	if(!g_pFilePointer)
	{
		//如果文件指针不正确，则显示错误信息
		printf("Unable to find or open the file: %s\n", STR_FILENAME);
	}

	do
	{
		memset(g_cmd, 0, sizeof(g_cmd));
		fscanf(g_pFilePointer, "%s", g_cmd);

		if (strcmp(g_cmd, STR_ADD_NODE) == 0)
		{
			fscanf(g_pFilePointer, "%f", &g_value);
			g_tree.addTreeNode(g_value);
			continue;
		}

		if (strcmp(g_cmd, STR_ADD_LEAF) == 0)
		{
			fscanf(g_pFilePointer, "%f", &g_value);
			g_tree.addLeafNode(g_value);
			continue;
		}

		if (strcmp(g_cmd, STR_FATHER_CHILD) == 0)
		{
			fscanf(g_pFilePointer, "%d %d", &g_num, &g_child);
			if (g_tree.fatherChild(g_num, g_child) == true)

			continue;
		}

		if (strcmp(g_cmd, STR_DELETE) == 0)
		{
			fscanf(g_pFilePointer, "%d", &g_num);
			if (g_tree.delNode(g_num) == true) 
			continue;
		}

		if (strcmp(g_cmd, STR_PREORDER) == 0)
		{
			fscanf(g_pFilePointer, "%d", &g_num);
			preorderTraversal(g_tree.pNode(g_num));
			fout.close();
			continue;
		}

	}
	while (strcmp(g_cmd, STR_EXIT) != 0);

//	printf("任意键退出程序\n");

	key = getch();
}




