#ifndef SYNTACTICANALIZER_H_
#define SYNTACTICANALIZER_H_

#include <QString>

#include "../lexer/MemoLexicalAnalyzer.h"
#include "../lexer/ErrorReporter.h"
#include "../common/Token.h"
#include "../ast/AbstractSyntaxTree.h"

class SyntacticAnalyzer
{
    /*
        Clase abstracta que define un subconjunto de parser, para definir alguno
        hay que heredar de ella y redefinir el método Parse
    */
    protected:
        LexicalAnalyzer *scanner;
        ErrorReporter * errorReporter;
        Token *currentToken;
        AST* memotree;

    public:
         SyntacticAnalyzer(LexicalAnalyzer *scanner, ErrorReporter *errorReporter);
         virtual ~SyntacticAnalyzer();

    protected:
        void SyntacticError( QString text );
        void Match(TokenKind tokenExpected);
        void consume();

    public:
        AST* GetMemoTree(){ return memotree; }
        virtual AST* Parse() = 0;
};

#endif /* SYNTACTICANALIZER_H_ */
