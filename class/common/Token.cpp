
#include "Token.h"

QString Token::ToString()
{
  /*
      Devuelve una cadena del token en el formato
      <lexeme: , kind: , line: >
  */
  QString _toString = "";
  if (kind == tk_Id)
    _toString = "< "+Token::TokenKindString(kind)+ ", "+
          "\""+ lexeme  + "\"" + ", " + QString::number(tableEntry) +  ">";
  else
    _toString = "< " + Token::TokenKindString(kind)
          + ", "+ "\"" + lexeme + "\""+ ">";

  return _toString;
}
