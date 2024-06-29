#include "evaluador.h"

Evaluador::Evaluador(SymbolsTable *st, ErrorReporter *errors)
    : Visitor()
{
    symbolTable = st;
    errorReporter = errors;
}

void* Evaluador::visit(ASTSuma *e)
{
    int izq = int(e->izquierdo()->visit(this));
    int der = int(e->derecho()->visit(this));

    return (void*)(izq + der);
}

void* Evaluador::visit(ASTRestaBinaria *e)
{
    int izq = int(e->izquierdo()->visit(this));
    int der = int(e->derecho()->visit(this));

    return (void*)(izq - der);
}

void* Evaluador::visit(ASTRestaUnaria *e)
{
    int op = int(e->operando()->visit(this));

    return (void*)(-op);
}

void* Evaluador::visit(ASTMultiplicacion *e)
{
    int izq = int(e->izquierdo()->visit(this));
    int der = int(e->derecho()->visit(this));

    return (void*)(izq * der);
}

void* Evaluador::visit(ASTDivision *e)
{
    int izq = int(e->izquierdo()->visit(this));
    int der = int(e->derecho()->visit(this));

    if (der != 0)
        return (void*)(izq / der);
    else
    {
        // Error semantico: Division por 0
        errorReporter->AddError(new CompilerError("Error Semántico: División por cero", 0));
    }

    return (void *)int(1);
}

void* Evaluador::visit(ASTPotencia *e)
{
    int base = int(e->izquierdo()->visit(this));
    int exp = int(e->derecho()->visit(this));

    return (void*)(int(pow(base, exp)));
}

void* Evaluador::visit(ASTLiteralEntero *e)
{
    SymbolInfo *info = symbolTable->Entry(e->getEntry());
    QString lexeme = info->getLexeme();

    return (void *)(lexeme.toInt());
}
