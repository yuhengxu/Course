#ifndef ReaderWriter_H
#define ReaderWriter_H

#include <iostream>
#include <string>
#include <vector>
#include "Thread.h"
#include "Semaphore.h"
#include "Counter.h"
#include "Action.h"
#include "ActionList.h"
#include "ACTION_TYPE.h"
#include "ACTION_OPERATION.h"
// back informace class
#include "config.h"
#include "overlap.h"

using namespace std;

class ReaderWriter
{
public:
	// default value
	void addThread(string sName = "Thread_null", int iNumber = 1, int iPeriod = 0, bool bRandom = false);
	void addSemaphore(string sName = "Semaphore_null", int iLow = 1, int iHigh = 1);
	void addCounter(string sName = "Counter_null", int iValue = 0);

	void setThreadNumber(string sName, int iNumber);
	void setThreadPeriod(string sName, int iPeriod);
	void setCounterValue(string sName, int iValue);

	int getSemaphoreValue(string sName);
	int getCounterValue(string sName);

	// use name to confrom the thread
	void addAction(string sName, Action aAction);
	void insertAction(string sName, int iIndex, Action aAction);
	void removeAction(string sName, int iIndex);
	void clearAction(string sName);

	// run the extern vector Thread, and get order, wait it
	void runThread(string sName);

	// get index of extern vector, according to name
	int getThreadIndex(string sName);
	int getSemaphoreIndex(string sName);
	int getCounterIndex(string sName);

	// turn from string to action and add to Thread
	void addString(string sStr, string sThreadName);
	int getStringLen(string sStr[]);

	// now using interfaces
    void start();
    void stop();
	Overlap next(int index);
	void test();
	Config getReaderFirstConfig();
    Config getWriterFirstConfig();
    Config getFairnessConfig();
};

extern vector<Thread> vNowThreads;
extern vector<Semaphore> vNowSemaphores;
extern vector<Counter> vNowCounters;

#endif // !ReaderWriter_H

