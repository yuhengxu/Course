#include "Semaphore.h"
using namespace std;

Semaphore::Semaphore(string sName, int iLow, int iHigh)
{
	this->name = sName;
	this->hSem = CreateSemaphore(NULL, iLow, iHigh, NULL);
	this->value = iLow;
}

void Semaphore::setName(string sName)
{
	this->name = sName;
}

void Semaphore::setValue(int iValue)
{
	this->value = iValue;
}

string Semaphore::getName()
{
	return this->name;
}

int Semaphore::getValue()
{
	return this->value;
}

void Semaphore::p()
{
	WaitForSingleObject(this->hSem, INFINITE);
    this->value--;
}

void Semaphore::v()
{
	ReleaseSemaphore(this->hSem, 1, NULL);
    this->value++;
}
