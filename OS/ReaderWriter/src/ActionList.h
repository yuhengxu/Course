#ifndef ActionList_H
#define ActionList_H

#include "Action.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class ActionList
{
private:
	vector<Action> list;
public:
	ActionList();
	void append(Action aAction);
	void insertAt(int iIndex, Action aAction);
	void removeAt(int iIndex);
	void clear();
	int getListSize();
	void runAction(int iIndex);		// give this signal to action to run it
	Action getAction(int iIndex);
	void updateActionScope(int iIndex, int iScope);
};

#endif // !ActionList_H
