#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <string>

using namespace std;


class Config
{
public:
    Config();
    vector<string> readerActions;
    vector<string> writerActions;

    class Object
    {
    public:
        Object(int id, string name, int value) :
            id(id), name(name), value(value) {}
        int id;
        string name;
        int value;
    };

    vector<Object> semaphores;
    vector<Object> counters;
};

#endif // CONFIG_H
