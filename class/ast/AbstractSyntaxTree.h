#ifndef ABSTRACTSTATICTREE_H_
#define ABSTRACTSTATICTREE_H_

#include "../common/visitor.h"
#include "../common/Enum.h"
#include <QList>
#include <QString>
#include <QTreeWidget>

class AST
{
public:
    AST(int line , bool null = false) : line(line) , null(null) {}
    virtual ~AST() {}

    inline int getLine() {  return line; }
    inline bool IsNull(){return null;}
    inline void setNull(bool n){ null = n;}
    inline QTreeWidgetItem * getParent(){return parent;}
    inline void setParent(QTreeWidgetItem * p ){parent = p;}
    int valor()
    {
        if ( null == false)
            return 0;
        else
            return 1 ;
    }
    virtual void* visit(Visitor * v)
    {
        return 0;
    }

protected:
    int line;
    bool null;
    QTreeWidgetItem * parent;
};

class ASTInstruction : public AST
{
public:
    ASTInstruction(int line)
        : AST(line) {}

protected:
};

class ASTExpRank : public AST
{
public:
    ASTExpRank(int line) : AST(line) {   m_type = Undefined;}

    MemoTypes getType() {  return m_type;  }
    void setType(MemoTypes type) {  m_type = type;  }
    void * visit (Visitor * v )
    {
        return 0;
    }

protected:
    MemoTypes m_type;

};

//aqui
class ASTOperatorBinary : public ASTExpRank
{
public:
    ASTOperatorBinary(int l , ASTExpRank * op1 , ASTExpRank * op2)
        :ASTExpRank(l) ,op1(op1) , op2(op2)  {
        m_type = Undefined;
    }

    ASTExpRank * GetOp1()
    {
        return op1;
    }

    ASTExpRank * GetOp2()
    {
        return op2;
    }
   virtual void * visit(Visitor * v)=0;


 protected:
    ASTExpRank * op1;
    ASTExpRank * op2;
};


class ASTUnion : public ASTOperatorBinary
{
public:
    ASTUnion( int s , ASTExpRank * op1 , ASTExpRank * op2)
        : ASTOperatorBinary( s , op1 , op2)
    {}
     void * visit(Visitor * v )
     {
         return v->visit(this);
     }
};


class ASTInterception : public ASTOperatorBinary
{
public:
    ASTInterception(int l , ASTExpRank * op1 , ASTExpRank * op2)
        : ASTOperatorBinary(l,op1,op2)
    {}
     void * visit(Visitor * v)
     {
        return v->visit(this);
     }
};

class ASTDifference : public ASTOperatorBinary
{
public:
    ASTDifference(int l , ASTExpRank * P1 , ASTExpRank * P2)
        : ASTOperatorBinary(l , P1,P2)
    {}

    void * visit(Visitor *v )
    {
      return v->visit(this);
    }
};


class ASTSymbol : public ASTExpRank
{
public:
    ASTSymbol(int l , int E):ASTExpRank(l)
    {
        entry = E;
    }
    int GetEntry()
    {
        return entry ;
    }
    virtual  void * visit(Visitor * v )
    {
        return 0;
    }

protected:
    int entry;
};

class ASTIntValue : public ASTSymbol
{
public:
    ASTIntValue(int l , int e)
        :ASTSymbol( l , e) {}
    void * visit(Visitor * v)
    {
        return v->visit(this);
    }
};

class ASTIdentifier : public ASTSymbol
{
public:
    ASTIdentifier(int l , int e)
        :ASTSymbol(l,e) {}
     void * visit(Visitor * v )
     {
         return 0;
     }
};

class ASTIdentifierDeclaration : public ASTIdentifier
{
public:
    ASTIdentifierDeclaration (int l , int e)
        :ASTIdentifier(l , e) {}

     void * visit(Visitor * v)
     {

         return v->visit(this);
     }
};

class ASTIdentifierReference : public ASTIdentifier
{
public:
    ASTIdentifierReference ( int l , int e)
        :ASTIdentifier(l , e) {}
    void * visit(Visitor * v)
    {

       return v->visit(this);
    }
};

class ASTIdentifierValue : public ASTIdentifier
{
public:
    ASTIdentifierValue ( int l , int e)
        :ASTIdentifier(l , e) {}
    void * visit(Visitor * v)
    {
       return v->visit(this);
    }
};



class ASTProgram: public AST
{
public:
    ASTProgram( int l , QList < ASTInstruction * >  i ):AST(l)
    {
        I.append(i);
    }
    QList < ASTInstruction * > GetList()
    {
        return I;
    }
    void * visit(Visitor * v)
    {
        return v->visit(this);
    }
private:
    QList < ASTInstruction * >  I;
};

class ASTDeclaration: public ASTInstruction
{
public:
    ASTDeclaration( int l ,  MemoTypes t , QList < ASTIdentifierDeclaration * >  d)
        : ASTInstruction(l),T(t){
        D.append(d);
    }
    QList <ASTIdentifierDeclaration * > GetList()
    {
        return D;
    }
    MemoTypes GetType()
    {
        return T;
    }
    void SetType( MemoTypes t)
    {
        T = t;
    }
    void * visit(Visitor * v)
    {
        return v->visit(this);
    }
private:
    QList < ASTIdentifierDeclaration * > D;
    MemoTypes T;
};

class ASTPrint: public ASTInstruction
{
public:
    ASTPrint( int l , ASTIdentifierValue * id)
    : ASTInstruction(l){
        Id = id;
    }
    ASTIdentifierValue * GetID()
    {
        return Id;
    }
    void * visit(Visitor * v)
    {
        return v->visit(this);
    }
private:
    ASTIdentifierValue * Id;
};

class ASTAssignation: public ASTInstruction
{
public:
    ASTAssignation(int l , ASTIdentifierReference * id)
    : ASTInstruction(l){
        Id = id;
    }
    ASTIdentifierReference * GetID()
    {
        return Id;
    }
    virtual  void * visit(Visitor * v )
    {
        return 0;
    }

protected:
    ASTIdentifierReference * Id;
};


class ASTInitInt: public ASTAssignation
{
public:
    ASTInitInt( int l , ASTIdentifierReference * id,  ASTSymbol * p)
        :ASTAssignation( l , id)
    {
        p1 = p;
    }
    ASTSymbol * GetP1()
    {
        return p1;
    }
    void * visit(Visitor * v)
    {
        return v->visit(this);
    }
private:
    ASTSymbol * p1;
};

class ASTInitRank: public ASTAssignation
{
public:
    ASTInitRank( int l, ASTIdentifierReference * id,  ASTSymbol * P1 , ASTSymbol * P2)
         :ASTAssignation( l , id)
    {
        p1 = P1 ;
        p2 = P2;
    }
    ASTSymbol * GetP1()
    {
        return p1;
    }
    ASTSymbol * GetP2()
    {
        return p2;
    }
    void SetP1(ASTSymbol * P1){p1 = P1;}
    void SetP2(ASTSymbol * P2){p2 = P2;}
    void * visit(Visitor * v )
    {
        return v->visit(this);
    }

private:
    ASTSymbol * p1;
    ASTSymbol * p2;
};

class ASTInitRankExp: public ASTAssignation
{
public:
    ASTInitRankExp(int l , ASTIdentifierReference * id,  ASTExpRank * P1)
        :ASTAssignation( l , id)
    {
        p1 = P1 ;
    }
    ASTExpRank * GetP1()
    {
        return p1 ;
    }
    void * visit(Visitor * v)
    {
        return v->visit(this);
    }
private:
    ASTExpRank * p1;

};

//aqui

#endif /* ABSTRACTSTATICTREE_H_ */
