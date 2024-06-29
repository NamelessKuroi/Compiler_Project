#ifndef EVALUADOR_H
#define EVALUADOR_H

#include "../common/visitor.h"
#include "../common/SymbolTable.h"
#include "../ast/AbstractSyntaxTree.h"
#include "../runtime/runtime-operator.h"

class Encoder : public Visitor
{
public:
    Encoder(SymbolsTable *st);
    void * visit ( ASTProgram * );
    void * visit ( ASTExpRank * );
    void * visit ( ASTUnion *  ) ;
    void * visit ( ASTInterception *  );
    void * visit ( ASTDifference *  );
    void * visit ( ASTInitInt*  );
    void * visit ( ASTInitRank*  );
    void * visit ( ASTInitRankExp *  );
    void * visit ( ASTDeclaration *  );
    void * visit ( ASTIdentifierDeclaration *  );
    void * visit ( ASTIdentifierReference*  );
    void * visit ( ASTIdentifierValue *  );
    void * visit ( ASTPrint * );
    void * visit ( ASTIntValue *);
    QString tipo(MemoTypes i)
    {
        if( (i) == Int )
            return "Int";
        else if ( (i) == Rank )
                return "Rank";
        else
            return "Undefined";
    }


    QList<RuntimeEntity*> Code() {  return code; }

protected:
    QList<RuntimeEntity*> code;
    SymbolsTable *symbolTable;
    int currentMemDir;
};

#endif // EVALUADOR_H
