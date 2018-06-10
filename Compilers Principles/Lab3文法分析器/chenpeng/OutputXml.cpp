#include"OutputXml.h"

OutputXml::OutputXml(const char *fileName, int tabCnt, const char *version, const char *encoding)
{
	out.open(fileName);
	while (tabCnt--) out << "  ";
	out << "<?xml version=\"" << version << "\" encoding=\"" << encoding << "\"?>\n";
}

void OutputXml::output(int tabCnt, const char *proName, bool flag, const char *value, vector<pair<string, string> > &vec)
{
	while (tabCnt--) out << "  ";
	out << "<" << proName;
	if (vec.size() != 0)
	{
		for (auto i : vec)
			out << " " << i.first << "=\"" << i.second << "\"";
	}
	out << ">";
	if (value != NULL) out << value;
	if (flag) out << "</" << proName << ">";
	out << endl;
	vec.clear();
}

void OutputXml::output(int tabCnt, const char *proName, bool flag, int value, vector<pair<string, string> > &vec)
{
	while (tabCnt--) out << "  ";
	out << "<" << proName;
	if (vec.size() != 0)
	{
		for (auto i : vec)
			out << " " << i.first << "=\"" << i.second << "\"";
	}
	out << ">";
	if (value != INF) out << value;
	if (flag) out << "</" << proName << ">";
	out << endl;
	vec.clear();
}

void OutputXml::outputEnd(int tabCnt, const char *proName)
{
	while (tabCnt--) out << "  ";
	out << "</" << proName << ">\n";
}

OutputXml::~OutputXml()
{
	out.close();
}