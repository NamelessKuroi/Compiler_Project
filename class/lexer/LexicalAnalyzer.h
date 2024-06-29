
#ifndef LEXICALANALYZER_H_
#define LEXICALANALYZER_H_

#include"SourceStream.h"
#include "../common/Token.h"

class LexicalAnalyzer
/*
    Clase abstracta que agrupa a todos
    los analizadores léxicos
*/
{
    protected:
        SourceStream *source;
        char currentChar;

    protected:

        bool IsLetter(char c)
        {
            return (c >= 'A' && c <= 'Z') || ( c >= 'a' && c <= 'z');
        }

        bool IsDigit(char c)
        {
            return c >= '0' && c <= '9';
        }
        bool IsSeparator(char c)
        {
            switch (c)
            {
                case '\n':
                case ' ':
                case '\r':
                case '\t':
                    return true;
                default:
                    return false;
            }
        }
        char NextChar()
        {
            return source->Read();
        }

        void Consume()
        {
            currentChar = source->Read();
        }

    public:
        LexicalAnalyzer(SourceStream *source)
        {
            this->source = source;
        }

        virtual ~LexicalAnalyzer()
        {
            if (source)
                delete source;
        }
         /*
            Token NextToken();
            Define la función princial del analizador léxico
            Devuelve en cada llamada el siguiente token
            reconocido en el Stream de entrada
        */
        virtual Token * NextToken() = 0;
};

#endif /* LEXICALANALYZER_H_ */
