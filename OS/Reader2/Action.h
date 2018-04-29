#ifndef Action_H
#define Action_H

#include "ACTION_TYPE.h"
#include "ACTION_OPERATION.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Action
{
private:
	ACTION_TYPE type;
	ACTION_OPERATION operation;
	int semaphore;	// index of extern vector
	int counter;
	int value;
	int scope;
	bool valid;
public:
	Action();

	void setType(ACTION_TYPE aType);
	void setOperation(ACTION_OPERATION aOperation);
	void setSemaphore(int iSemaphore);
	void setCounter(int iCounter);
	void setValue(int iValue);
	void setScope(int iScope);
	void setValid(bool bValid);

	ACTION_TYPE getType();
	ACTION_OPERATION getOperation();
	int getSemaphore();
	int getCounter();
	int getValue();
	int getScope();
	bool getValid();

	void runAction();	// if call this function, run this action
						// according to index to run extern vector

};

#endif // !Action_H
