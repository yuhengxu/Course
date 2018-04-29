#ifndef Semaphore_H
#define Semaphore_H

#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Semaphore
{
private:
	string name;
	int value;
	HANDLE hSem;
public:
	Semaphore(string sName = "Semaphore_null", int iLow = 1, int iHigh = 1);
	void setName(string sName);
	void setValue(int iValue);
	string getName();
	int getValue();
	void p();
	void v();
};

#endif // !Semaphore_H
