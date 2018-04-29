#ifndef Thread_H
#define Thread_H

#include "Action.h"
#include "ActionList.h"
#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

class Thread
{
private:
	string name;
	int number;
	int period;
	bool random;
	ActionList actionList;

	int stopFlag;
	bool start;
	bool stop;
	bool next;
public:
	Thread(string sName = "Thread_null", int iNumber = 1, int iPeriod = 0, bool bRandom = false);
	
	void setName(string sName);
	void setNumber(int iNumber);
	void setPeriod(int iPeriod);
	void setRandom(bool bRandom);
	void setstopFlag(int iFlag);
	void setStart(bool bStart);
	void setStop(bool bStop);
	void setNext(bool bNext);

	string getName();
	int getNumber();
	int getPeriod();
	bool getRandom();
	int getstopFlag();
	bool getStart();
	bool getStop();
	bool getNext();

	void appendAction(Action aAction);
	void insertAction(int iIndex, Action aAction);
	void removeAction(int iIndex);
	void clearAction();
	int getActionListSize();
	Action getAction(int iIndex);
	void updateActionScope(int iIndex, int iScope);
	void runAction(int iIndex);		// give this signal to actionlist to run it
};


/*
 * function: server form thread, listen order from ReaderWriter, and then do them
 * input: address of vNowThreads[i]
 */
void run(LPVOID pParam);

#endif // !Thread_H
