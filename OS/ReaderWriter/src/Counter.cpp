#include "Counter.h"
using namespace std;

Counter::Counter(string sName, int iValue)
{
	this->name = sName;
	this->value = iValue;
}

void Counter::decrease()
{
	this->value--;
}

void Counter::increase()
{
	this->value++;
}

void Counter::setName(string sName)
{
	this->name = sName;
}

string Counter::getName()
{
	return this->name;
}

void Counter::setValue(int iValue)
{
	this->value = iValue;
}

int Counter::getValue()
{
	return this->value;
}
