#include "interpreter.h"

Interpreter::Interpreter(QList<RuntimeEntity*> code)
{
    context = new Context(code);
}

void Interpreter::Execute()
{
    QList<RuntimeEntity*> code = context->getCode();
    for (int i = 0; i < code.size()&& context->getCurrent() < code.size(); i++)
    {
       // Console::instance()->println(context->getCurrent());
        RuntimeEntity *inst = code[context->getCurrent()];
        inst->Execute(context);
    }
}
