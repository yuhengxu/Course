#include "ActionList.h"
#include "Thread.h"
#include "Semaphore.h"
#include "Counter.h"
#include <iostream>
using namespace std;

extern vector<Thread> vNowThreads;
extern vector<Semaphore> vNowSemaphores;
extern vector<Counter> vNowCounters;

ActionList::ActionList()
{
}

void ActionList::append(Action aAction)
{
	this->list.push_back(aAction);
}

void ActionList::insertAt(int iIndex, Action aAction)
{
	this->list.insert(this->list.begin() + iIndex, aAction);
}

void ActionList::removeAt(int iIndex)
{
	this->list.erase(this->list.begin() + iIndex);
}

void ActionList::clear()
{
	this->list.clear();
}

int ActionList::getListSize()
{
	return this->list.size();
}

void ActionList::runAction(int iIndex)
{
	this->list[iIndex].runAction();
}

Action ActionList::getAction(int iIndex)
{
	return list[iIndex];
}

void ActionList::updateActionScope(int iIndex, int iScope)
{
	this->list[iIndex].setScope(iScope);
}
