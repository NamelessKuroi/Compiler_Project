#ifndef MEMOCOMPILER_H
#define MEMOCOMPILER_H

#include "../lexer/MemoLexicalAnalyzer.h"
#include "../parser/MemoSyntacticAnalyzer.h"
#include "../runtime/context.h"

class MemoCompiler
{
public:
    MemoCompiler(SourceStream *source);
    ~MemoCompiler();
    QList<RuntimeEntity*> Compile();
    AST * getAST(){return tree; }
    SymbolsTable * getST(){return symbolsTable;}
    void ShowErrorOutput();

private:
    MemoLexicalAnalyzer *scanner;
    ErrorReporter *errorReporter;
    SymbolsTable *symbolsTable;
    MemoSyntacticAnalyzer *parser;
    AST *tree;
};

#endif // MEMOCOMPILER_H
