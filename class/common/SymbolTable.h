#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_

#include "Token.h"
#include "Enum.h"
#include <QList>
#include <QString>

class SymbolInfo
{
public:
    SymbolInfo(QString lexeme, TokenKind kind) :
        lexeme(lexeme), kind(kind), declared(false), initialized(false), type(Undefined)
    {
        this->lexeme  =  lexeme;
        this->kind = kind ;
        declared = false;
        initialized = false;
        type = Undefined;
        address = -1;
    }

    QString getLexeme() {   return lexeme;  }

    TokenKind getKind() {   return kind;    }
    void setKind(TokenKind nkind) {   kind = nkind;    }

    bool isDeclared()  {   return declared;  }
    void setDeclared(bool dec)  {  declared = dec;  }

    int getAddress()    {   return address;   }
    void setAddress(int newAddress)   {   address = newAddress; }

    bool isInitialized()  {  return initialized;  }
    void setInitialized(bool init)    {   initialized = init;   }

    MemoTypes getType() {   return type;      }
    void setType(MemoTypes newType)   {   type = newType;      }

    QString ToString()  {   return lexeme;  }

protected:
    QString lexeme;
    TokenKind kind;
    int address;
    bool declared;
    bool initialized;
    MemoTypes type;
};

class SymbolsTable
{
private:
    QList<SymbolInfo*> *items;
public:
    SymbolsTable()
    {
        items = new QList<SymbolInfo*>;
    }

    SymbolInfo* Entry(int index)
    {
        return items->value(index);
    }

    int IndexOf(QString lexeme)
    {
        for(int i = 0; i < items->size(); i++)
        {
            if(lexeme == Entry(i)->getLexeme())
                return i;
        }
        return -1;
    }

    int Add(QString lexeme, TokenKind kind)
    {
        SymbolInfo *item = new SymbolInfo(lexeme,kind);
        int index= IndexOf(item->getLexeme());
        if( index == -1)
        {
            items->append(item);
            index = Count() -1;
        }
        return index;
    }

    int Count()
    {
        return items->size();
    }
};

#endif /* SYMBOLTABLE_H_ */
