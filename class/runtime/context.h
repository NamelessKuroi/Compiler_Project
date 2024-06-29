#ifndef CONTEXT_H
#define CONTEXT_H

#include <QStack>
#include <QObject>
#include <QList>

#include "memory.h"

class RuntimeEntity;
class Context
{
public:
    Context(QList<RuntimeEntity*> c)
    {
        code = c;
        stack = new QStack<QObject*>();
        memory = new Memory();
        current = 0;
    }

    QStack<QObject*> * getStack()    {  return stack;      }
    Memory* getMemory()            {  return memory;     }
    int getCurrent()               {  return current;    }
    void setCurrent(int ncurrent)  {  current = ncurrent;}

    QList<RuntimeEntity*> getCode(){  return code;       }

protected:
    QStack<QObject*> *stack;
    Memory *memory;
    int current;
    QList<RuntimeEntity*> code;
};

#endif // CONTEXT_H
