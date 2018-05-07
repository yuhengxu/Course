#include "Action.h"
#include "Thread.h"
#include "Semaphore.h"
#include "Counter.h"
#include <Windows.h>
using namespace std;

extern vector<Thread> vNowThreads;
extern vector<Semaphore> vNowSemaphores;
extern vector<Counter> vNowCounters;

Action::Action()
{
	this->scope = 1;
}

void Action::setType(ACTION_TYPE aType)
{
	this->type = aType;
}

void Action::setOperation(ACTION_OPERATION aOperation)
{
	this->operation = aOperation;
}

void Action::setSemaphore(int iSemaphore)
{
	this->semaphore = iSemaphore;
}

void Action::setCounter(int iCounter)
{
	this->counter = iCounter;
}

void Action::setValue(int iValue)
{
	this->value = iValue;
}

void Action::setScope(int iScope)
{
	this->scope = iScope;
}

void Action::setValid(bool bValid)
{
	this->valid = bValid;
}

ACTION_TYPE Action::getType()
{
	return this->type;
}

ACTION_OPERATION Action::getOperation()
{
	return this->operation;
}

int Action::getSemaphore()
{
	return this->semaphore;
}

int Action::getCounter()
{
	return this->counter;
}

int Action::getValue()
{
	return this->value;
}

int Action::getScope()
{
	return this->scope;
}

bool Action::getValid()
{
	return this->valid;
}

void Action::runAction()
{
	if (this->type == SEMAPHORE && this->scope == 1)
	{
		if (this->operation == P)
		{
			vNowSemaphores[this->semaphore].p();
		}
		else
		{
			vNowSemaphores[this->semaphore].v();
		}
	}
	else if (this->type == COUNTER && this->scope == 1)
	{
		if (this->operation == INCREASE)
		{
			vNowCounters[this->counter].increase();
		}
		else
			vNowCounters[this->counter].decrease();
	}
	else
		cout << "I am not finished it ahhhh!" << endl;
}
