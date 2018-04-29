#ifndef Counter_H
#define Counter_H

#include <iostream>
#include <string>
using namespace std;

class Counter
{
private:
	string name;
	int value;
public:
	// default param
	Counter(string sName = "Counter_null", int iValue = 0);
	void decrease();
	void increase();
	void setName(string sName);
	string getName();
	void setValue(int iValue);
	int getValue();
};

#endif // !Counter_H
