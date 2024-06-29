#include "SyntacticAnalizer.h"

SyntacticAnalyzer::SyntacticAnalyzer(LexicalAnalyzer *scanner, ErrorReporter *errorReporter)
{
    this->scanner = scanner;
    this->errorReporter = errorReporter;
}

SyntacticAnalyzer:: ~SyntacticAnalyzer()
{
    delete scanner;
    delete errorReporter;
}

void SyntacticAnalyzer::SyntacticError( QString text )
{
    errorReporter->AddError(new CompilerError(text,currentToken->GetLine()));
}

void SyntacticAnalyzer::Match(TokenKind tokenExpected)
{
    if(currentToken->GetKind() == tokenExpected)
        consume();
    else
    {
        errorReporter->AddError(new CompilerError("Error Sintáctico: Se esperaba el token: " + Token::TokenKindString(tokenExpected) +
                                                  " y se encontró el token " + currentToken->GetLexeme(), currentToken->GetLine()));
    }
}

void SyntacticAnalyzer:: consume()
{
    currentToken = scanner->NextToken();
}
