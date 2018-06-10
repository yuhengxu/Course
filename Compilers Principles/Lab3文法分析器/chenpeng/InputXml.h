//
// Created by DamJoker on 2018/5/9.
//

#ifndef INPUTXML_INPUTXML_H
#define INPUTXML_INPUTXML_H

#include<fstream>
#include<iostream>
#include<cstdio>
#include<cstring>

using namespace std;

class InputXml
{
private:
	ifstream in;

public:
	InputXml(const char *fileName);
	int getToken(char *value, char *type, int *line, bool *valid);
	~InputXml();
};

#endif //INPUTXML_INPUTXML_H
