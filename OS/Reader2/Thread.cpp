#include "Thread.h"
#include "Semaphore.h"
#include "Counter.h"
#include <iostream>
using namespace std;

extern vector<Thread> vNowThreads;
extern vector<Semaphore> vNowSemaphores;
extern vector<Counter> vNowCounters;

Thread::Thread(string sName, int iNumber, int iPeriod, bool bRandom)
{
	this->name = sName;
	this->number = iNumber;
	this->period = iPeriod;
	this->random = bRandom;

	this->start = false;
	this->stop = false;
	this->next = false;
	this->stopFlag = 0;
}

void Thread::setName(string sName)
{
	this->name = sName;
}

void Thread::setNumber(int iNumber)
{
	this->number = iNumber;
}

void Thread::setPeriod(int iPeriod)
{
	this->period = iPeriod;
}

void Thread::setRandom(bool bRandom)
{
	this->random = bRandom;
}

void Thread::setstopFlag(int iFlag)
{
	this->stopFlag = iFlag;
}

void Thread::setStart(bool bStart)
{
	this->start = bStart;
}

void Thread::setStop(bool bStop)
{
	this->stop = bStop;
}

void Thread::setNext(bool bNext)
{
	this->next = bNext;
}

string Thread::getName()
{
	return this->name;
}

int Thread::getNumber()
{
	return this->number;
}

int Thread::getPeriod()
{
	return this->period;
}

bool Thread::getRandom()
{
	return this->random;
}

int Thread::getstopFlag()
{
	return this->stopFlag;
}

bool Thread::getStart()
{
	return this->start;
}

bool Thread::getStop()
{
	return this->stop;
}

bool Thread::getNext()
{
	return this->next;
}

void Thread::appendAction(Action aAction)
{
	this->actionList.append(aAction);
}

void Thread::insertAction(int iIndex, Action aAction)
{
	this->actionList.insertAt(iIndex, aAction);
}

void Thread::removeAction(int iIndex)
{
	this->actionList.removeAt(iIndex);
}

void Thread::clearAction()
{
	this->actionList.clear();
}

int Thread::getActionListSize()
{
	return this->actionList.getListSize();
}

Action Thread::getAction(int iIndex)
{
	return this->actionList.getAction(iIndex);
}

void Thread::updateActionScope(int iIndex, int iScope)
{
	this->actionList.updateActionScope(iIndex, iScope);
}

void Thread::runAction(int iIndex)
{
	this->actionList.runAction(iIndex);
}

void run(LPVOID pParam)
{
	Thread * tThis = (Thread *)pParam;

	bool flag = true;
	// run and listen
//    cout << tThis->getNumber() << endl;
//    cout << tThis->getstopFlag() << endl;
	while (tThis->getNumber() > 0)
	{
		while (true)
		{
			if (tThis->getstopFlag() == tThis->getActionListSize())	// end of list
			{
				break;
			}
			else
			{
				while (tThis->getStop() == false && tThis->getStart() == false && tThis->getNext() == false)
				{
					// wait for order
//					cout << "brother I need order, you know ?" << endl;
				}
				if (tThis->getStop() == true)
				{
					flag = false;
					tThis->setStop(false);
					break;
				}
				else if (tThis->getNext() == true)
				{
					int iActionlistsize = 0;
					iActionlistsize = tThis->getActionListSize();
					for (int i = tThis->getstopFlag(); i < iActionlistsize; i++)
					{
						// run each action
                        bool bFlag = true;
						Action aAction;
						aAction = tThis->getAction(i);
						if (aAction.getType() == IF)
						{
							if (vNowCounters[aAction.getCounter()].getValue() == aAction.getValue())
							{
								// uadate the next action.scope = 1
								tThis->updateActionScope(i, 1);
							}
							else
							{
								// uadate the next action.scope = 0
								tThis->updateActionScope(i, 0);
                                bFlag = false;
							}
						}
						else if (aAction.getType() == DATA)
						{
//							cout << "DATA" << endl;
						}
						else
						{
							tThis->runAction(i);
						}
                        if(bFlag == false)
                        {
                            tThis->setstopFlag(i + 2);
                        }
                        else
                        {
                            tThis->setstopFlag(i + 1);
                        }
						break;
					}
					tThis->setNext(false);
				}
				else if (tThis->getStart() == true)
				{
					int iActionlistsize = 0;
					iActionlistsize = tThis->getActionListSize();
					for (int i = tThis->getstopFlag(); i < iActionlistsize; i++)
					{
						// run each action
						tThis->runAction(i);
						// wait some time to show
						Sleep(2000);	//???
					}
					tThis->setstopFlag(iActionlistsize);
					tThis->setStart(false);
				}
			}
		}
//		tThis->setNumber(tThis->getNumber() - 1);	// number --
//		if (flag == false)
//			break;
//		// time between run
//		int time = 0;
//		if (tThis->getRandom() == true)
//		{
//			time = (rand() % tThis->getPeriod()) * 1000;
//		}
//		else
//		{
//			time = tThis->getPeriod() * 1000;
//		}
//		cout << "Waiting..." << endl;
//		Sleep(time);
//		cout << "Starting" << endl;
	}
	tThis->setNext(false);
	tThis->setStart(false);
}
