// ReaderWriter_v1.0.cpp : 定义控制台应用程序的入口点。
//

#include "ReaderWriter.h"
#include "Thread.h"
#include <fstream>
#include <iostream>
using namespace std;

vector<Thread> vNowThreads;
vector<Semaphore> vNowSemaphores;
vector<Counter> vNowCounters;

vector<string> vReader;
vector<string> vWriter;

//string sReader[] = { "P(s1);",
//                     "If(c1 == 0)",
//                     "    P(s2);",
//                     "c1++;",
//                     "V(s1);",
//                     "Read();",
//                     "P(s1);",
//                     "c1--;",
//                     "If(c1 == 0)",
//                     "    V(s2);",
//                     "V(s1);" ,
//                     "NULL"};
//string sWriter[] = { "P(s2);",
//                     "Write();",
//                     "V(s2);",
//                     "NULL"};

//int main()
//{
//	// test reader writer
//	ReaderWriter rw;
//	rw.getReaderFirstConfig();
//	rw.next(1);		// P s1
//	rw.next(1);		// if
//	rw.next(1);		// P s2
//	rw.next(1);		// c1++
//	rw.next(1);		// V s1
//	rw.next(1);		// Read

//	rw.next(4);		// Ps2	// ??是应当先p再-1，还是先-1再p
//	rw.next(4);		// write	// 此处你应当挂起next按钮，防止再按
//	rw.next(4);		// Vs2

//	rw.next(1);		// Ps1
//	rw.next(1);		// c1--
//	rw.next(1);		// if
//	rw.next(1);		// Vs2
//	rw.next(1);		// Vs1
//}

void ReaderWriter::addThread(string sName, int iNumber, int iPeriod, bool bRandom)
{
	// can use the default param
	Thread tThread(sName, iNumber, iPeriod, bRandom);
	vNowThreads.push_back(tThread);
}

void ReaderWriter::addSemaphore(string sName, int iLow, int iHigh)
{
	// can use the default param
	Semaphore sSemaphore = Semaphore(sName, iLow, iHigh);
	vNowSemaphores.push_back(sSemaphore);
	// you can rename it too, but I'am give you the interface ahhh
}

void ReaderWriter::addCounter(string sName, int iValue)
{
	// can use the default param
	Counter cCounter(sName, iValue);
	vNowCounters.push_back(cCounter);
}

void ReaderWriter::setThreadNumber(string sName, int iNumber)
{
	int index;
	index = getThreadIndex(sName);
	vNowThreads[index].setNumber(iNumber);
}

void ReaderWriter::setThreadPeriod(string sName, int iPeriod)
{
	int index;
	index = getThreadIndex(sName);
	vNowThreads[index].setPeriod(iPeriod);
}

void ReaderWriter::setCounterValue(string sName, int iValue)
{
	int index;
	index = getCounterIndex(sName);
	vNowCounters[index].setValue(iValue);
}

int ReaderWriter::getSemaphoreValue(string sName)
{
	int index;
	index = getSemaphoreIndex(sName);
	return vNowSemaphores[index].getValue();
}

int ReaderWriter::getCounterValue(string sName)
{
	int index;
	index = getCounterIndex(sName);
	return vNowCounters[index].getValue();
}

void ReaderWriter::addAction(string sName, Action aAction)
{
	int index;
	index = getThreadIndex(sName);
	vNowThreads[index].appendAction(aAction);
}

void ReaderWriter::insertAction(string sName, int iIndex, Action aAction)
{
	int index;
	index = getThreadIndex(sName);
	vNowThreads[index].insertAction(iIndex, aAction);
}

void ReaderWriter::removeAction(string sName, int iIndex)
{
	int index;
	index = getThreadIndex(sName);
	vNowThreads[index].removeAction(iIndex);
}

void ReaderWriter::clearAction(string sName)
{
	int index;
	index = getThreadIndex(sName);
	vNowThreads[index].clearAction();
}

void ReaderWriter::runThread(string sName)
{
	int index;
	index = getThreadIndex(sName);
	// create thread to run, and listen order
	HANDLE hRun = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run, &vNowThreads[index], 0, NULL);
	
	// wait the order
	vNowThreads[index].setStart(true);	// start to run

	// must wait the handle, to prevent destory the local param
	WaitForSingleObject(hRun, INFINITE);
}

int ReaderWriter::getThreadIndex(string sName)
{
	int i;
	int iNumber = vNowThreads.size();
	for (i = 0; i < iNumber; i++)
	{
		if ((sName.compare(vNowThreads[i].getName())) == 0)
		{
			break;
		}
	}
	return i;
}

int ReaderWriter::getSemaphoreIndex(string sName)
{
	int i;
	int iNumber = vNowSemaphores.size();
	for (i = 0; i < iNumber; i++)
	{
		if (sName.compare(vNowSemaphores[i].getName()) == 0)
		{
			break;
		}
	}
	return i;
}

int ReaderWriter::getCounterIndex(string sName)
{
	int i;
	int iNumber = vNowCounters.size();
	for (i = 0; i < iNumber; i++)
	{
		if (sName.compare(vNowCounters[i].getName()) == 0)
		{
			break;
		}
	}
	return i;
}

void ReaderWriter::addString(string sStr, string sThreadName)
{
	ReaderWriter rw;
	Action aAction;
	int iLen = sStr.length();
	for (int i = 0; i < iLen; i++)
	{
		if (sStr[i] != ' ')
		{
			if (sStr[i] == 'R' || sStr[i] == 'W')
			{
				aAction.setType(DATA);
				rw.addAction(sThreadName, aAction);

				break;
			}
			else if (sStr[i] == 'I')
			{
				string sName = sStr.substr(i+3, 2);
				int iNum = sStr[i+9] - '0';
				
				aAction.setType(IF);
				aAction.setOperation(EQUAL);
				aAction.setCounter(rw.getCounterIndex(sName));
				aAction.setValue(iNum);
				rw.addAction(sThreadName, aAction);

				break;
			}
			else if (sStr[i] == 'P')		// add action p(sName)
			{
				string sName = sStr.substr(i + 2, 2);
				
				aAction.setType(SEMAPHORE);
				aAction.setOperation(P);
				aAction.setSemaphore(rw.getSemaphoreIndex(sName));
				rw.addAction(sThreadName, aAction);

				break;
			}
			else if (sStr[i] == 'V')
			{
				string sName = sStr.substr(i + 2, 2);

				aAction.setType(SEMAPHORE);
				aAction.setOperation(V);
				aAction.setSemaphore(rw.getSemaphoreIndex(sName));
				rw.addAction(sThreadName, aAction);
			
				break;
			}
			else if (sStr[i] == 'c')
			{
				string sName = sStr.substr(i, 2);
				
				aAction.setType(COUNTER);
				if (sStr[i + 2] == '+')
				{
					aAction.setOperation(INCREASE);
				}
				else
				{
					aAction.setOperation(DECREASE);
				}
				aAction.setCounter(rw.getCounterIndex(sName));
				rw.addAction(sThreadName, aAction);
				
				break;
			}
			else
			{
				cout << "Order error:" << sStr[i] << endl;
				break;
			}
		}
	}
}

int ReaderWriter::getStringLen(string sStr[])
{
	for (int i = 0; ; i++)
	{
		if (sStr[i].compare("NULL") == 0)
		{
			return i;
		}
	}
	return -1;
}

void ReaderWriter::start()
{
    // create Thread
    ReaderWriter rw;
    rw.addThread("T1", 1, 0, false);
    rw.addThread("T2", 1, 0, false);
    rw.addThread("T3", 1, 0, false);
    rw.addThread("T4", 1, 0, false);
    rw.addThread("T5", 1, 0, false);
    rw.addThread("T6", 1, 0, false);
    // create Semaphore Counter
    rw.addSemaphore("s1", 1, 1);
    rw.addSemaphore("s2", 1, 1);
    rw.addSemaphore("s3", 1, 1);
    rw.addSemaphore("s4", 1, 1);
    rw.addSemaphore("s5", 1, 1);
    rw.addCounter("c1", 0);
    rw.addCounter("c2", 0);
    rw.addCounter("c3", 0);
    // read order string size
    int iRlen = vReader.size();
    int iWlen = vWriter.size();
    // from order to action and add to the appointed thread
    for (int i = 0; i < iRlen; i++)		// thread 1-3
    {
        rw.addString(vReader[i], "T1");
        rw.addString(vReader[i], "T2");
        rw.addString(vReader[i], "T3");
    }
    for (int i = 0; i < iWlen; i++)		// thread 4-6
    {
        rw.addString(vWriter[i], "T4");
        rw.addString(vWriter[i], "T5");
        rw.addString(vWriter[i], "T6");
    }
}

void ReaderWriter::stop()
{
    vNowCounters.clear();
    vNowSemaphores.clear();
    vNowThreads.clear();
    vReader.clear();
    vWriter.clear();
}


// now use the interfaces
Overlap ReaderWriter::next(int index)
{
	int iOriLine = vNowThreads[index - 1].getstopFlag();
    if(iOriLine == -1)
    {
        vNowThreads[index-1].setstopFlag(0);
//        cout << iOriLine << endl;
    }
    else
    {
        // create thread to run, and listen order
        HANDLE hRun = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)run, &vNowThreads[index-1], 0, NULL);

        // wait the order
        vNowThreads[index-1].setNext(true);

        // must wait the handle, to prevent destory the local param, but time?
        WaitForSingleObject(hRun, 100);
    //    Sleep(1000);
        TerminateThread(hRun, 0);
    }

	Overlap oOverlap;
	oOverlap.line = vNowThreads[index-1].getstopFlag();
    if(index > 0 && index < 4)  // reader
    {
        int iRlen = vReader.size();
        if(oOverlap.line >= iRlen)
        {
            oOverlap.line = -1;
            vNowThreads[index-1].setstopFlag(-1);
        }
    }
    else                        // writer
    {
        int iWlen = vWriter.size();
        if(oOverlap.line >= iWlen)
        {
            oOverlap.line = -1;
            vNowThreads[index-1].setstopFlag(-1);
        }
    }
	if (oOverlap.line == iOriLine)
	{
		oOverlap.blocked = true;
	}
	else
	{
		oOverlap.blocked = false;
	}
	
	Action aAction;
	int iNum;
	aAction = vNowThreads[index - 1].getAction(iOriLine);
	if (aAction.getType() == SEMAPHORE)
	{
		iNum = aAction.getSemaphore();
        oOverlap.id = iNum + 1;
		oOverlap.name = vNowSemaphores[iNum].getName();
		oOverlap.value = vNowSemaphores[iNum].getValue();
	}
	else if (aAction.getType() == COUNTER)
	{
		iNum = aAction.getCounter();
        oOverlap.id = iNum + 4;
        oOverlap.name = vNowCounters[iNum].getName();
		oOverlap.value = vNowCounters[iNum].getValue();
	}

	return oOverlap;
}

// may be interface
Config ReaderWriter::getReaderFirstConfig()
{
    vReader.clear();
    vWriter.clear();
    // reader context to order vector
    string sTemp;
    // reader
    ifstream iR("vReader1.txt");
    while( getline(iR,sTemp) )
    {
        vReader.push_back(sTemp);
    }
    iR.close();
    // writer
    ifstream iW("vWriter1.txt");
    while(getline(iW,sTemp))
    {
        vWriter.push_back(sTemp);
        cout << sTemp << endl;
    }
    iW.close();

    int iRlen = vReader.size();
    int iWlen = vWriter.size();
	////////////////////////////////////////
	// return
	Config config;
	for (int i = 0; i < iRlen; i++)
	{
        config.readerActions.push_back(vReader[i]);
	}
	for (int i = 0; i < iWlen; i++)
	{
        config.writerActions.push_back(vWriter[i]);
	}
	config.semaphores.push_back(Config::Object(1, "s1", 1));
	config.semaphores.push_back(Config::Object(2, "s2", 1));
    config.semaphores.push_back(Config::Object(3, "s3", 1));
	config.counters.push_back(Config::Object(1, "c1", 0));
    config.counters.push_back(Config::Object(1, "c2", 0));
    config.counters.push_back(Config::Object(1, "c3", 0));
	////////////////////////////////////////

	return config;
}

Config ReaderWriter::getWriterFirstConfig()
{
    vReader.clear();
    vWriter.clear();
    // reader context to order vector
    string sTemp;
    // reader
    ifstream iR("vReader2.txt");
    while( getline(iR,sTemp) )
    {
        vReader.push_back(sTemp);
    }
    iR.close();
    // writer
    ifstream iW("vWriter2.txt");
    while(getline(iW,sTemp))
    {
        vWriter.push_back(sTemp);
        cout << sTemp << endl;
    }
    iW.close();

    int iRlen = vReader.size();
    int iWlen = vWriter.size();
    ////////////////////////////////////////
    // return
    Config config;
    for (int i = 0; i < iRlen; i++)
    {
        config.readerActions.push_back(vReader[i]);
    }
    for (int i = 0; i < iWlen; i++)
    {
        config.writerActions.push_back(vWriter[i]);
    }
    config.semaphores.push_back(Config::Object(1, "s1", 1));
    config.semaphores.push_back(Config::Object(2, "s2", 1));
    config.semaphores.push_back(Config::Object(3, "s3", 1));
    config.counters.push_back(Config::Object(1, "c1", 0));
    config.counters.push_back(Config::Object(1, "c2", 0));
    config.counters.push_back(Config::Object(1, "c3", 0));
    ////////////////////////////////////////

    return config;
}

Config ReaderWriter::getFairnessConfig()
{
    vReader.clear();
    vWriter.clear();
    // reader context to order vector
    string sTemp;
    // reader
    ifstream iR("vReader3.txt");
    while( getline(iR,sTemp) )
    {
        vReader.push_back(sTemp);
    }
    iR.close();
    // writer
    ifstream iW("vWriter3.txt");
    while(getline(iW,sTemp))
    {
        vWriter.push_back(sTemp);
        cout << sTemp << endl;
    }
    iW.close();

    int iRlen = vReader.size();
    int iWlen = vWriter.size();
    ////////////////////////////////////////
    // return
    Config config;
    for (int i = 0; i < iRlen; i++)
    {
        config.readerActions.push_back(vReader[i]);
    }
    for (int i = 0; i < iWlen; i++)
    {
        config.writerActions.push_back(vWriter[i]);
    }
    config.semaphores.push_back(Config::Object(1, "s1", 1));
    config.semaphores.push_back(Config::Object(2, "s2", 1));
    config.semaphores.push_back(Config::Object(3, "s3", 1));
    config.counters.push_back(Config::Object(1, "c1", 0));
    config.counters.push_back(Config::Object(1, "c2", 0));
    config.counters.push_back(Config::Object(1, "c3", 0));
    ////////////////////////////////////////

    return config;
}

void ReaderWriter::test()
{
	cout << "Hello" << endl;
}
