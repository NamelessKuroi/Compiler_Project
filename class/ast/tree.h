#ifndef TREE_H
#define TREE_H

#include "../common/visitor.h"
#include <QTreeWidget>
#include "class/common/SymbolTable.h"

class Tree : public Visitor
{
public:
    Tree(QTreeWidget * a,SymbolsTable * TS);

    void * visit ( ASTProgram * );
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
private:
QTreeWidget * arbol;
SymbolsTable * ts;


};

#endif // TREE_
