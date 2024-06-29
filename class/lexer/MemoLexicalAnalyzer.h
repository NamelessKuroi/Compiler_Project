#ifndef MEMOLEXICALANALYZER_H_
#define MEMOLEXICALANALYZER_H_

#include "LexicalAnalyzer.h"
#include "Dictionary.h"
#include "ErrorReporter.h"
#include "SourceStream.h"
#include "../common/SymbolTable.h"

#include <QString>

class MemoLexicalAnalyzer: public LexicalAnalyzer
{

private :
    SymbolsTable * table;
    ErrorReporter * errorList;

    Dictionary<QString, TokenKind> * keywordsTable;
    void FillKeywordsTable();
public:
    MemoLexicalAnalyzer(SourceStream *source,SymbolsTable * table,ErrorReporter * errorList);
    Token *NextToken();
    TokenKind DefineTokenKind(QString lexeme);
    Token * scanIdentifier();
    Token * scanNumber();
    virtual ~MemoLexicalAnalyzer();
};


#endif /* MEMOLEXICALANALYZER_H_ */
