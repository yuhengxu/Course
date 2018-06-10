//
// Created by DamJoker on 2018/5/9.
//

#include "InputXml.h"

InputXml::InputXml(const char *fileName)
{
	in.open(fileName);
	char str[100];
	for (int i = 1; i <= 3; i++)
		in.getline(str, 99);
}

int InputXml::getToken(char *value, char *type, int *line, bool *valid)
{
	char str1[100], str2[100];
	in.getline(str1, 99);

	int number;
	for (int i = 1; i <= 5; i++)
	{
		in.getline(str1, 99);
		int len(strlen(str1));
		for (int j = 0; j<len; j++)
		{
			if (str1[j] == '>')
			{
				strcpy(str2, &str1[j + 1]);
				break;
			}
		}
		len = strlen(str2);
		for (int j = 1; j<len; j++)
		{
			if (str2[j] == '<')
			{
				str2[j] = 0;
				break;
			}
		}

		if (i == 1) number = atoi(str2);
		else if (i == 2) strcpy(value, str2);
		else if (i == 3) strcpy(type, str2);
		else if (i == 4) *line = atoi(str2);
		else if (i == 5)
		{
			if (strcmp(str2, "true") == 0) *valid = true;
			else *valid = false;
		}
	}
	in.getline(str1, 99);

	return number;
}

InputXml::~InputXml()
{
	in.close();
}