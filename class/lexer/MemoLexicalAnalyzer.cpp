
#include "MemoLexicalAnalyzer.h"

MemoLexicalAnalyzer::MemoLexicalAnalyzer(SourceStream *source,SymbolsTable * table, ErrorReporter * errorList)
    :LexicalAnalyzer(source)
{
    this->table = table;
    this->errorList = errorList;
    currentChar = NextChar();
    keywordsTable = new Dictionary<QString,TokenKind>;
    FillKeywordsTable();
}

void MemoLexicalAnalyzer::FillKeywordsTable()
/*
    Se define que cadenas van a ser palabras claves
    para el lenguaje que reconoce este Analizador Léxico (Easy).
*/
{
    keywordsTable->AddEntry("main", tk_Main);
    keywordsTable->AddEntry("int", tk_Int);
    keywordsTable->AddEntry("rank", tk_Rank);
    keywordsTable->AddEntry("initrank", tk_InitRank);
    keywordsTable->AddEntry("print", tk_Print);
}

MemoLexicalAnalyzer::~MemoLexicalAnalyzer()
{
    delete keywordsTable;
}

Token * MemoLexicalAnalyzer::NextToken()
{
    /*
    {...}
    Define la función principal del analizador léxico
    Devuelve en cada llamada el siguiente token
    reconocido en el Stream de entrada
    {...}
    */
    if(IsSeparator(currentChar))
    {
        Consume();
        return  NextToken();
    }

    switch(currentChar)
    {

      //Operators
       case '?': Consume();
       return new Token(tk_Union, "?", source->CurrentLine());

       case '$': Consume();
       return new Token(tk_Inter, "$", source->CurrentLine());

       case '&': Consume();
       return new Token(tk_Dif, "&", source->CurrentLine());

       case':':
          {
            Consume();
            if (currentChar == '=')
              {
               Consume();
               return new Token(tk_AR, ":=", source->CurrentLine());
            }
            return NextToken();
          }
        break;
        case '=': Consume();
              return new Token(tk_Asig, "=", source->CurrentLine());

       //Signs

      case '{': Consume();
      return new Token(tk_Llave_Izq, "{", source->CurrentLine());

      case '}': Consume();
      return new Token(tk_Llave_Der, "}", source->CurrentLine());

      case '(': Consume();
      return new Token(tk_Par_Izq, "(", source->CurrentLine());

      case ')': Consume();
      return new Token(tk_Par_Der, ")", source->CurrentLine());

      case ';': Consume();
      return new Token(tk_Pto_Coma, ";", source->CurrentLine());

      case ',': Consume();
      return new Token(tk_Coma, ",", source->CurrentLine());





     case '\0': Consume();
        return new Token(tk_EOF, "EOF", source->CurrentLine());

    default:
    {
        if (IsLetter(currentChar) || currentChar == '_')
        {
            Token *token = scanIdentifier(); // matching identifier
            return (token != 0) ? token : NextToken();
        }
        else
        {
            if (IsDigit(currentChar))
            {
                Token *token = scanNumber(); // matching Literal
                return (token != 0) ? token : NextToken();
            }
            else
            {
                errorList->AddError(new CompilerError(QString("Caracter %1 no esperado.").arg(currentChar),
                                                      source->CurrentLine()));
                Consume();
                return NextToken();
            }
        }
    }
  }
}

Token * MemoLexicalAnalyzer::scanIdentifier()
{
    QString lexeme = "";
    do
    {
        lexeme += currentChar;
        Consume();
    } while(IsLetter(currentChar)||IsDigit(currentChar)||currentChar=='_' );

    TokenKind kind = DefineTokenKind(lexeme);

    if (kind == tk_Id)
    {
        int entry = table->Add(lexeme, kind);
        return new Token(tk_Id,lexeme,source->CurrentLine(),entry);
    }

    return new Token(kind, lexeme, source->CurrentLine());
}

TokenKind MemoLexicalAnalyzer::DefineTokenKind(QString lexeme)
{
    TokenKind kind = tk_Id ;
    if (keywordsTable->TryGetValue(lexeme, kind))
        return kind;
    return kind;
}

Token * MemoLexicalAnalyzer::scanNumber()
{
    QString lexeme = "";
    TokenKind kind = tk_Literal_Entero;

    do
    {
        lexeme += currentChar;
        Consume();
    }
    while(IsDigit(currentChar));

    int entry = table->Add(lexeme, kind);
    return new Token(kind, lexeme, source->CurrentLine(), entry);
}
