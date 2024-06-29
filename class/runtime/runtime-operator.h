#ifndef RUNTIMEOPERATOR_H
#define RUNTIMEOPERATOR_H

#include "context.h"
#include "../../console.h"
#include "../common/Enum.h"

class RuntimeEntity
{
public:
    RuntimeEntity() {}
    virtual void Execute(Context *) {}
    QString toString();
};

class IntValue : public RuntimeEntity
{

public:
    IntValue(int value = 0) : RuntimeEntity(), value(value) {}
    int getValue()       {   return value; }
    void setValue(int v) {   value = v;    }

protected:
    int value;
};

 class RankValue : public RuntimeEntity
{
public:
    RankValue(int s = 0, int e = 0 )
        : RuntimeEntity()  {
        if(  s < e )
        {
            start = s;
            end = e;
            len = e - s + 1;
        }
        else
        {
            start = e;
            end = s;
            len = s - e + 1;
        }

    }

    bool operator == (RankValue  r1 )
    {
       if ( start ==  r1.start && end == r1.end )
           return  true;

           return  false;
    }
    friend RankValue * operator+(RankValue  r1 , RankValue  r2)
    {
        int min = r1.start < r2.start ?  r1.start : r2.start;
        int max = r1.end > r2.end ?  r1.end : r2.end;
        return new RankValue(min,max);
    }
    friend RankValue * operator&(RankValue  r1 , RankValue  r2)
    {    int min = 0, max = 0;
           if ( r1.start >= r2.start &&  r1.start <= r2.end )
            min =  r1.start;
          else if( r2.start >= r1.start &&  r2.start <= r1.end )
            min = r2.start;

           if ( r1.end >= r2.start &&  r1.end <= r2.end )
            max =  r1.end;
          else if( r2.end >= r1.start &&  r2.end <= r1.end )
            max = r2.end;

        return new RankValue(min,max);
    }
    friend RankValue * operator-(RankValue  r1 , RankValue  r2)
    {
        RankValue * e = new RankValue();
        RankValue  *t1;
        RankValue  *t2;

        RankValue * r = r1 & r2;

        if( *r == *e)
            e = new RankValue(r1.start,r1.end);
        else
            if(*r == r1)
             return e;
            else if(*r == r2)
            {
                t1 = new RankValue(r1.start , r2.start - 1);
                t2 = new RankValue(r2.end + 1 , r1.end);
                if(t1->getlen() < t2->getlen() )
                    return t1;
                else
                    return t2;
            }
        else
            {
                if ( r1.start < r2.start)
                    return new RankValue(r1.start,r2.start - 1);
                 else
                   return new RankValue(r2.end + 1 , r1.end);
            }

        return e;
    }

    inline void setStart(int s) {   start = s ;    }
    inline void setEnd( int e)  {   end = e ;    }
    inline int getStart() { return start;}
    inline int getEnd() { return end;}
    inline int getlen(){return len; }
 protected:
    int start;
    int end;
    int len;
};


 class RuntimeCarga : public RuntimeEntity
{
public:
    RuntimeCarga() : RuntimeEntity() {}

    void Execute(Context *context)
    {

       int address = ((IntValue *)context->getCode().value(context->getCurrent() + 1))->getValue();
       context->getStack()->push(context->getMemory()->getVal(address));
       context->setCurrent(context->getCurrent() + 2);

    }
};


 class RuntimeCargaDir : public RuntimeEntity
{
public:
    RuntimeCargaDir() : RuntimeEntity() {}

    void Execute(Context *context)
    {
        QObject *address = (QObject *)context->getCode().value(context->getCurrent() + 1);
        context->getStack()->push(address);
        context->setCurrent(context->getCurrent() + 2);

    }
};


 class RuntimeStore : public RuntimeEntity
{
public:
    RuntimeStore() : RuntimeEntity() { }

    void Execute(Context *context)
    {

        QObject *value = context->getStack()->pop();
        IntValue *address = (IntValue *)context->getStack()->pop();
        context->getMemory()->assign(address->getValue(), value);
        context->setCurrent(context->getCurrent() + 1);

    }

};

 class RuntimeUnion : public RuntimeEntity
{
public:


    RuntimeUnion ():RuntimeEntity() {}
    void Execute(Context * context )
    {
        RankValue * op2 = (RankValue *)context->getStack()->pop();
        RankValue * op1 = (RankValue *)context->getStack()->pop();
        RankValue * result = (*op1) + (*op2);
        context->getStack()->push( (QObject *) result );
        context->setCurrent(context->getCurrent() + 1 );
    }
};

 class RuntimeInterception :public RuntimeEntity
{
public:
    RuntimeInterception (): RuntimeEntity() {}
    void Execute(Context * context )
    {
        RankValue *op2 = (RankValue *)context->getStack()->pop();
        RankValue *op1 = (RankValue *)context->getStack()->pop();
        RankValue * result = (*op1) & (*op2) ;
        context->getStack()->push( (QObject *) result );
        context->setCurrent(context->getCurrent() + 1 );
    }
};

 class RuntimeDifference : public RuntimeEntity
{
public:
    RuntimeDifference  (): RuntimeEntity () {}

   void Execute(Context * context )
    {
        RankValue * op2 = (RankValue *)context->getStack()->pop();
        RankValue * op1 = (RankValue *)context->getStack()->pop();
        RankValue * result = (*op1) - (*op2) ;
        context->getStack()->push((QObject*) result );
        context->setCurrent(context->getCurrent() + 1 );
    }
};

 class RuntimePrint : public RuntimeEntity
{
public:
     RuntimePrint(MemoTypes a) : RuntimeEntity(),a(a) {}

    void Execute(Context *context)
    {   


        QObject * value = context->getStack()->pop();
        if( a == Int )
          {
           IntValue * e = (IntValue *) value;
           Console::instance()->println(e->getValue());
          }
        else
        {
          RankValue * r = (RankValue *) value;
         Console::instance()->print("[" + QString::number(r->getStart())+".."+ QString::number(r->getEnd())+"]");
        }

        context->setCurrent(context->getCurrent() + 1);
    }
 private :
    MemoTypes a;
};

 class RuntimeNewRank : public RuntimeEntity
{
public:
    RuntimeNewRank() : RuntimeEntity() {}
    void Execute(Context * context )
    {
        context->getMemory()->addVal((QObject*) new RankValue());
        context->setCurrent(context->getCurrent() + 1);
    }
};

 class RuntimeNewInt : public RuntimeEntity
{
public:
    RuntimeNewInt() : RuntimeEntity() {}

    void Execute(Context *context)
    {
        context->getMemory()->addVal((QObject*)new IntValue());
        context->setCurrent(context->getCurrent() + 1);

    }
};

 class RuntimePush : public RuntimeEntity
{
public:
    RuntimePush() : RuntimeEntity() {}
    void Execute(Context * context)
    {
        QObject * address = (QObject *)context->getCode().value(context->getCurrent() + 1);
        context->getStack()->push(address);
        context->setCurrent(context->getCurrent() + 2);
    }
};

class RuntimeInitRank : public RuntimeEntity
{
public :
    RuntimeInitRank() : RuntimeEntity() {}
    void Execute(Context * context)
    {
        IntValue * p2 = (IntValue *)context->getStack()->pop();
        IntValue * p1 = (IntValue *)context->getStack()->pop();
        RankValue * result = new RankValue( p1->getValue(),p2->getValue() );
        context->getStack()->push((QObject*) result );
        context->setCurrent(context->getCurrent() + 1);
    }
};

#endif // RUNTIMEOPERATOR_H
