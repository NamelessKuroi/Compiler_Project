#ifndef TOKEN_H_
#define TOKEN_H_

#include <QString>
#include "../lexer/SourcePosition.h"

enum TokenKind
{
/*
  Enumerativo que se usa para identificar el tipo de token
*/
    tk_Int,
    tk_Rank,
    tk_Id,
    tk_Literal_Entero,
    tk_AR,
    tk_Asig,
    tk_Pto_Coma,
    tk_Par_Izq,
    tk_Par_Der,
    tk_Llave_Izq,
    tk_Llave_Der,
    tk_Coma,
    tk_Print,
    tk_Main,
    tk_InitRank,
    tk_Union,
    tk_Inter,
    tk_Dif,
    tk_Error,
    tk_EOF
};

class Token
{
  protected:
     QString lexeme;
     TokenKind kind;
     int tableEntry;
     int line;

  public:

     Token( TokenKind kind, QString lexeme, int line, int tableEntry)
     {
         this->lexeme = lexeme;
         this->kind = kind;
         this->line = line;
         this->tableEntry = tableEntry;
     }

     Token( TokenKind kind, QString lexeme, int line)
     {
         this->lexeme = lexeme;
         this->kind = kind;
         this->line = line;
         this->tableEntry = -1;
     }

     QString GetLexeme()
     {
        return lexeme;
     }

     TokenKind GetKind()
     {
        return kind;
     }

     int GetLine()
     {
        return line;
     }

     QString ToString();


     int GetTableEntry()
     {
        return tableEntry;
     }

     static QString TokenKindString(TokenKind tk)
     {
        QString TokenKindStringArr[] =
        {
            "tk_Int",
            "tk_Rank",
            "tk_Id",
            "tk_Literal_Entero",
            "tk_AR",
            "tk_Asig",
            "tk_Pto_Coma",
            "tk_Par_Izq",
            "tk_Par_Der",
            "tk_Llave_Izq",
            "tk_Llave_Der",
            "tk_Coma",
            "tk_Print",
            "tk_Main",
            "tk_InitRank",
            "tk_Union",
            "tk_Inter",
            "tk_Dif",
            "tk_Error",
            "tk_EOF"
        };

        return TokenKindStringArr[tk];
     }
};

#endif /* TOKEN_H_ */
