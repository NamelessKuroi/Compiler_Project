#ifndef MEMOSYNTACTICANALYZER_H_
#define MEMOSYNTACTICANALYZER_H_

#include <QList>

#include "../lexer/ErrorReporter.h"
#include "SyntacticAnalizer.h"
#include "../ast/AbstractSyntaxTree.h"

class MemoSyntacticAnalyzer : public SyntacticAnalyzer
{
protected:
    void recuperate(TokenKind tk_expected);
    void recuperate(QList<TokenKind> tokens);

public:
    MemoSyntacticAnalyzer(LexicalAnalyzer *scanner, ErrorReporter *errorReporter);
    AST *Parse();
    ASTProgram * Program();
    QList < ASTInstruction * >  Instructions ();
    QList < ASTInstruction * >  MoreInstructions( QList < ASTInstruction * >  );
    ASTInstruction * Instruction() ;
    ASTDeclaration * Declaration();
    QList <ASTIdentifierDeclaration * >  MoreIdentifier( QList <ASTIdentifierDeclaration*> );
    ASTAssignation * Assignation();
    ASTPrint * Print();

    ASTExpRank * ExpRank();
    ASTExpRank * Factor ();
    ASTExpRank * MasFactor (ASTExpRank *);
    ASTExpRank * T2();
    ASTExpRank * MasT2(ASTExpRank *);
    ASTExpRank * T1();
    ASTExpRank * MasT1(ASTExpRank *);

    MemoTypes Tipo ();
    ASTSymbol * Parametro();
    ASTInitRank *  ParametrodeRango(ASTInitRank * IR);


};

#endif /* MEMOSYNTACTICANALYZER_H_ */
