#include "tinyxml2.h"
#include<stdio.h>
#include<stdlib.h>
#include<iostream>

#define LEN 5000

using namespace tinyxml2;
using namespace std;

char str1[LEN];
int i = 0, counts = 1;

void XML(int state, char* str2)
{
	char type_v[20], valid_v[20], number_v[20];
	strcpy(valid_v, "true");
	itoa(counts++, number_v, 10);

	int b = strcmp(str2, "char") && strcmp(str2, "double") && strcmp(str2, "enum") && strcmp(str2, "float") && strcmp(str2, "int") && strcmp(str2, "long") && strcmp(str2, "short") && strcmp(str2, "signed") && strcmp(str2, "struct") && strcmp(str2, "union") && strcmp(str2, "unsigned") && strcmp(str2, "void") && strcmp(str2, "for") && strcmp(str2, "do") && strcmp(str2, "while") && strcmp(str2, "break") && strcmp(str2, "continue") && strcmp(str2, "if") && strcmp(str2, "else") && strcmp(str2, "goto") && strcmp(str2, "switch") && strcmp(str2, "case") && strcmp(str2, "default") && strcmp(str2, "return") && strcmp(str2, "auto") && strcmp(str2, "extern") && strcmp(str2, "register") && strcmp(str2, "static") && strcmp(str2, "const") && strcmp(str2, "sizeof") && strcmp(str2, "typeof") && strcmp(str2, "voliatile");

	int c = (-1) && (-1) && (-1) && (-1) && (-1);
	switch (state)
			{
			case 1:
				if(b == 0)
				//if (strcmp(str2, "char") && strcmp(str2, "double") && strcmp(str2, "enum") && strcmp(str2, "float") && strcmp(str2, "int") && strcmp(str2, "long") && strcmp(str2, "short") && strcmp(str2, "signed") && strcmp(str2, "struct") && strcmp(str2, "union") && strcmp(str2, "unsigned") && strcmp(str2, "void") && strcmp(str2, "for") && strcmp(str2, "do") && strcmp(str2, "while") && strcmp(str2, "break") && strcmp(str2, "continue") && strcmp(str2, "if") && strcmp(str2, "else") && strcmp(str2, "goto") && strcmp(str2, "switch") && strcmp(str2, "case") && strcmp(str2, "default") && strcmp(str2, "return") && strcmp(str2, "auto") && strcmp(str2, "extern") && strcmp(str2, "register") && strcmp(str2, "static") && strcmp(str2, "const") && strcmp(str2, "sizeof") && strcmp(str2, "typeof") && strcmp(str2, "voliatile"))
					strcpy(type_v, "keyword");
				else strcpy(type_v, "identifier");
				break;
			case 2:
				strcpy(type_v, "separator");
				break;
			case 5:
				strcpy(type_v, "letter");
				break;
			case 8:
				strcpy(type_v, "ESCAPE_CHAR");
				break;
			case 11:
				strcpy(type_v, "string");
				break;
			case 12:case 14:case 18:
				strcpy(type_v, "int");
				break;
			case 15:case 45:
				strcpy(type_v, "int_8");
				break;
			case 17:
				strcpy(type_v, "int_16");
				break;
			case 20:case 21:case 22:case 23:case 24:case 25:case 26:case 27:case 28:case 29:case 30:case 31:case 32:case 33:case 36:case 37:case 38:case 39:case 40:case 41:case 42:case 43:case 44:
				strcpy(type_v, "operator");
				break;
			case 52:
				strcpy(type_v, "scientfic count");
				break;
			case 255:
				strcpy(type_v, "unknow");
				strcpy(valid_v, "false");
				break;
			default:
				strcpy(type_v, "Forget");
				strcpy(valid_v, "false");
				printf("%d", state);
			}

	XMLDocument doc;
	int res = doc.LoadFile("C:\\Users\\yuheng\\Desktop\\bit-minic-compiler\\run\\input\\test.xml");
	if (res != 0)
	{
		printf("load xml file failed\n");
	}
	XMLElement* root1 = doc.RootElement();
	XMLElement* root = root1->FirstChildElement();

	XMLElement* token = doc.NewElement("token");
	root->InsertEndChild(token);

	XMLElement* number = doc.NewElement("number");
	XMLText* texNumber = doc.NewText(number_v);
	number->InsertEndChild(texNumber);
	token->InsertEndChild(number);

	XMLElement* value = doc.NewElement("value");
	XMLText *texValue = doc.NewText(str2);
	value->InsertEndChild(texValue);
	token->InsertEndChild(value);

	XMLElement* type = doc.NewElement("type");
	XMLText *texType = doc.NewText(type_v);
	type->InsertEndChild(texType);
	token->InsertEndChild(type);

	XMLElement* line = doc.NewElement("line");
	XMLText *texLine = doc.NewText("1");
	line->InsertEndChild(texLine);
	token->InsertEndChild(line);

	XMLElement* valid = doc.NewElement("valid");
	XMLText *texValid = doc.NewText(valid_v);
	valid->InsertEndChild(texValid);
	token->InsertEndChild(valid);

	doc.SaveFile("C:\\Users\\yuheng\\Desktop\\bit-minic-compiler\\run\\input\\test.xml");
	//doc.SaveFile("./test.xml");

	return;
}


//读入文件函数
FILE* input()
{
	printf("请输入读取文件路径：");

	char file_path[LEN];
	//scanf("%s", file_path);

	//FILE *fp = fopen(file_path, "r");
	FILE *fp = fopen("C:\\Users\\yuheng\\Desktop\\bit-minic-compiler\\run\\input\\test.pp.c", "r");
	//FILE *fp = fopen("./test.c", "r");

	if (fp == NULL) printf("打开文件失败\n");

	return fp;
}

char nextchar(char* &flag)
{
	//读出下一个字符，并且将指针向后移动一位，并将该字符写到string字符串中
	char str = flag[0];
	flag++;
	str1[i++] = str;
	return str;
}

void undo(char* &flag)
{
	//回退一位指针，并将string中的最后一个字符删除
	flag--;
	i--;
}



void output(int state)
{
	//输出type，再将string数组清空初始化，重新记录
	char str2[LEN];
	int j;
	for (j = 0; j < i; j++)str2[j] = str1[j];
	str2[j] = '\0';
	//XML(state, str2, doc, tokens);
	XML(state, str2);
	i = 0;
}

void AcceptingStates(char* &flag, int &state)
{
	undo(flag);
	output(state);		//传递state是为了再输出是进行标签分类，确定是哪一种数据
	state = 0;
}

void Scanner(char* buff)
{
	int state = 0;
	char* flag = buff;
	char str;

	while ((str = nextchar(flag)) != '\0')
	{
		//char str = nextchar(flag);

		switch (state)
		{
		case 0:
			switch (str)
			{
			case 'a':case 'b':case 'c':case 'd':case 'e':case 'f':case 'g':case 'h':case 'i':case 'j':case 'k':case 'l':case 'm':case 'n':case 'o':case 'p':case 'q':case 'r':case 's':case 't':case 'u':case 'v':case 'w':case 'x':case 'y':case 'z':
			case 'A':case 'B':case 'C':case 'D':case 'E':case 'F':case 'G':case 'H':case 'I':case 'J':case 'K':case 'L':case 'M':case 'N':case 'O':case 'P':case 'Q':case 'R':case 'S':case 'T':case 'U':case 'V':case 'W':case 'X':case 'Y':case 'Z':
				state = 1; break;
			case '{':case '}':case '[':case ']':case '(':case ')':case ',':case ';':case '.':case ':':case '?':
				state = 2; break;
			case '\'':
				state = 3; break;
			case '"':
				state = 9; break;
			case '1':case '2':case '3':case '4':case '5':case '6':case '7':case '8':case '9':
				state = 18; break;
			case '0':
				state = 12; break;
			case '+':case '-':
				state = 20; break;
			case '*':case '/':case '%':case '^':case '=':case '!':
				state = 23; break;
			case '&':
				state = 26; break;
			case '|':
				state = 28; break;
			case '<':
				state = 31; break;
			case '>':
				state = 36; break;
			case '~':
				state = 40; break;
			case '#':
				state = 45; break;
			default:
				state = 47;
			}break;
		case 1:
			if ((str >= 'A'&&str <= 'Z') || (str >= 'a'&&str <= 'z') || (str >= '0'&&str <= '9'))state = 1;
			else AcceptingStates(flag, state);
			break;
		case 2:
			AcceptingStates(flag, state);
			break;
		case 3:
			if (str != '\\' && str != '\'')state = 4;
			else if (str == '\\')state = 6;
			else if (str == '\'')state = 34;
			else state = 255;
			break;
		case 4:
			if (str == '\'')state = 5;
			break;
		case 5:
			AcceptingStates(flag, state);
			break;
		case 6:
			if (str == 'a' || str == 'b' || str == 'f' || str == 'n' || str == 'r' || str == 't' || str == 'v' || str == '\\' || str == '\'' || str == '"' || str == '0')state = 7;
			else state = 255;
			break;
		case 7:
			if (str == '\'')state = 8;
			else state = 255;
			break;
		case 8:
			AcceptingStates(flag, state);
			break;
		case 9:
			if (str == '"')state = 11;
			else if (str == '\\')state = 10;
			else state = 9;
			break;
		case 10:
			state = 9;
			break;
		case 11:
			AcceptingStates(flag, state);
			break;
		case 12:
			if (str == '.')state = 13;
			else if (str >= '0'&&str <= '7')state = 15;
			else if (str == 'X' || str == 'x')state = 16;
			else AcceptingStates(flag, state);
			break;
		case 13:
			if (str >= '0'&&str <= '9')state = 14;
			else state = 255;
			break;
		case 14:
			if (str >= '0'&& str <= '9')state = 14;
			else if (str == 'e' || str == 'E')state = 50;
			else AcceptingStates(flag, state);
			break;
		case 15:
			if (str >= '0'&&str <= '7')state = 15;
			else if (str == '.')state = 45;
			else AcceptingStates(flag, state);
			break;
		case 16:
			if ((str >= 'A'&&str <= 'F') || (str >= 'a'&&str <= 'f') || (str >= '0'&&str <= '9'))state = 17;
			else state = 255;
			break;
		case 17:
			if (str == '.')state = 46;
			else if ((str >= 'A'&&str <= 'F') || (str >= 'a'&&str <= 'f') || (str >= '0'&&str <= '9'))state = 17;
			else AcceptingStates(flag, state);
			break;
		case 18:
			if (str >= '0'&&str <= '9')state = 18;
			else if (str == '.')state = 19;
			else if (str == 'e' || str == 'E')state = 50;
			else AcceptingStates(flag, state);
			break;
		case 19:
			if (str >= '0'&& str <= '9')state = 14;
			else state = 255;
			break;
		case 20:
			if (str == '+')state = 21;
			else if (str == '=')state = 22;
			else AcceptingStates(flag, state);
			break;
		case 21:
			AcceptingStates(flag, state);
			break;
		case 22:
			AcceptingStates(flag, state);
			break;
		case 23:
			if (str == '=')state = 25;
			else if (str == '-')state = 24;
			else AcceptingStates(flag, state);
			break;
		case 24:
			AcceptingStates(flag, state);
			break;
		case 25:
			AcceptingStates(flag, state);
			break;
		case 26:
			if (str == '=')state = 27;
			else AcceptingStates(flag, state);
			break;
		case 27:
			AcceptingStates(flag, state);
			break;
		case 28:
			if (str == '=')state = 30;
			else if (str == '&')state = 29;
			else AcceptingStates(flag, state);
			break;
		case 29:
			AcceptingStates(flag, state);
			break;
		case 30:
			AcceptingStates(flag, state);
			break;
		case 31:
			if (str == '=')state = 33;
			else if (str == '|')state = 32;
			else AcceptingStates(flag, state);
			break;
		case 32:
			AcceptingStates(flag, state);
			break;
		case 33:
			AcceptingStates(flag, state);
			break;
		case 36:
			if (str == '<')state = 38;
			else if (str == '=')state = 37;
			else AcceptingStates(flag, state);
			break;;
		case 37:
			AcceptingStates(flag, state);
			break;
		case 38:
			if (str == '=')state = 39;
			else AcceptingStates(flag, state);
			break;
		case 39:
			AcceptingStates(flag, state);
			break;
		case 40:
			if (str == '=')state = 43;
			else if (str == '>')state = 41;
			else AcceptingStates(flag, state);
			break;
		case 41:
			if (str == '=')state = 42;
			else AcceptingStates(flag, state);
			break;
		case 42:
			AcceptingStates(flag, state);
			break;
		case 43:
			AcceptingStates(flag, state);
			break;
		case 44:
			AcceptingStates(flag, state);
			break;
		case 45:
			if (str >= '0'&&str <= '7')state = 45;
			else AcceptingStates(flag, state);
			break;
		case 46:
			if ((str >= 'A'&&str <= 'F') || (str >= 'a'&&str <= 'f') || (str >= '0'&&str <= '9'))state = 46;
			else AcceptingStates(flag, state);
			break;
		case 47:
			state = 0;
			flag--;
			i = 0;
			break;
		case 50:
			if (str == '-')state = 51;
			else if (str >= '0'&&str <= '9')state = 52;
			else state = 255;
			break;
		case 51:
			if (str >= '0'&&str <= '9')state = 52;
			else state = 255;
			break;
		case 52:
			if (str >= '0'&&str <= '9')state = 52;
			else AcceptingStates(flag, state);
			break;
		default:
			state = 255;
		}
	}
}

int createXML(const char* xmlPath)
{
	XMLDocument doc;
	const char* declaration = "<xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\">";
	doc.Parse(declaration);

	XMLElement* root = doc.NewElement("project");
	root->SetAttribute("name ", "test.c");
	doc.InsertEndChild(root);

	XMLElement* tokens = doc.NewElement("tokens");
	root->InsertEndChild(tokens);

	return doc.SaveFile(xmlPath);
}

int main()
{
	FILE* fp = input();
	char buff[LEN];

	int xml = createXML("C:\\Users\\yuheng\\Desktop\\bit-minic-compiler\\run\\input\\test.xml");

	while (fgets(buff, LEN, fp) != NULL)
	{
		i = 0;
		Scanner(buff);
	}

	printf("2. Scanning Finished!");
	fclose(fp);

	return 0;
}