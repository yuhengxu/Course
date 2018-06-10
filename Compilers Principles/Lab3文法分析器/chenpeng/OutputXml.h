#ifndef OUTPUTXML_
#define OUTPUTXML_

#include<vector>
#include<utility>
#include<string>
#include<fstream>
using namespace std;
const int INF = 0x3f3f3f3f;

class OutputXml
{
private:
	ofstream out;
public:
	OutputXml(const char *fileName, int tabCnt, const char *version, const char *encoding);
	void output(int tabCnt, const char *proName, bool flag, const char *value, vector<pair<string, string> > &vec);
	void output(int tabCnt, const char *proName, bool flag, int value, vector<pair<string, string> > &vec);
	void outputEnd(int tabCnt, const char *proName);
	~OutputXml();
};

#endif