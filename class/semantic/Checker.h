#ifndef CHECKER_H_
#define CHECKER_H_

#include "../common/visitor.h"
#include "../common/SymbolTable.h"
#include "../lexer/ErrorReporter.h"

class Checker :public Visitor
{
public:
    Checker(SymbolsTable *table, ErrorReporter *errorReporter);

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

         QString tipoS(MemoTypes i)
         {
             if( (i) == Int )
                 return "Int";
             else if ( (i) == Rank )
                     return "Rank";
             else
                 return "Undefined";
         }

          int tipoE(MemoTypes i)
         {
             if( i == Int )
                 return 1;
             else if ( i == Rank )
                     return 2;
             else
                 return 3;
         }


protected:
    SymbolsTable *table;
    ErrorReporter *errorReporter;
};

#endif // CHECKER_H_
