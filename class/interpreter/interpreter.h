#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "../runtime/runtime-operator.h"

class Interpreter
{
public:
    Interpreter(QList<RuntimeEntity*> code);
    void Execute();

private:
    Context *context;
};

#endif // INTERPRETER_H
