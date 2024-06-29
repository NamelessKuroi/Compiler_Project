#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "../common/visitor.h"
#include "../common/SymbolTable.h"
#include "../ast/AbstractSyntaxTree.h"
#include "../lexer/ErrorReporter.h"

class Evaluador : public Visitor
{
public:
    Evaluador(SymbolsTable *st, ErrorReporter *errors);
    void *visit(ASTProgram *) { return 0; }
    void *visit(ASTSuma *e);
    void *visit(ASTRestaBinaria *e);
    void *visit(ASTMultiplicacion *e);
    void *visit(ASTDivision *e);
    void *visit(ASTPotencia *e);

protected:
    SymbolsTable *symbolTable;
    ErrorReporter *errorReporter;
};

#endif // EVALUADOR_H
