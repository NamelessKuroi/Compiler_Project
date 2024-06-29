#include "Checker.h"
#include "../ast/AbstractSyntaxTree.h"
#include "../lexer/ErrorReporter.h"
#include "console.h"

Checker::Checker(SymbolsTable * table, ErrorReporter *errorReporter)
    : Visitor(), table(table), errorReporter(errorReporter)
{}

void * Checker::visit(ASTProgram * o )
{
    QList < ASTInstruction * > I;
    I.append( o->GetList());


    for(int i = 0 ; i < I.size() ; i++ )
    {
        I.value(i)->visit(this);
    }
    return 0;
}

void * Checker::visit(ASTDeclaration * o )
{
    QList < ASTIdentifierDeclaration * > D;
    D.append( o->GetList());
    SymbolInfo * info;
    for(int i = 0 ; i < D.size() ; i++ )
    {
        info = table->Entry(D.value(i)->GetEntry());
        info->setType(o->GetType());
        D.value(i)->visit(this);
    }
    return 0;
}

void * Checker::visit(ASTIdentifierDeclaration * o)
{

    SymbolInfo *info = table->Entry(o->GetEntry());
    if ( info -> isDeclared() )

        errorReporter->AddError(new CompilerError("Error Semántico: identificador "+info->getLexeme()+
                                                  " ya fue declarado previamente.",o->getLine()));
    else
        info->setDeclared( true );
    return 0;
}

void * Checker::visit(ASTIdentifierReference * o )
{
    SymbolInfo * info = table->Entry(o->GetEntry());
    if  ( info->isDeclared() )
    {
        info->setInitialized( true );

        return ( void *)(info->getType());
    }
    else
    {
        errorReporter->AddError(new CompilerError(" Error  semántico:  identificador" +
                                                  info->getLexeme()+ " no ha sido declarado" , o->getLine()));
        return (void*)Undefined;
    }
}

void * Checker::visit(ASTIdentifierValue * o )
{
    SymbolInfo * info = table->Entry(o->GetEntry());

    if ( info->isInitialized() && info->isDeclared() )
    {

        return (void*)(info->getType());
    }

    else
    {
        if ( info->isDeclared()!= true )

            errorReporter->AddError(new CompilerError(" Error Semántico:  identificador "
                                                      + info->getLexeme()+ " no ha sido declarado", o->getLine() ));



        if ( info->isInitialized()  != true )

            errorReporter->AddError(new CompilerError(" Error Semántico:  identificador "
                                                      + info->getLexeme() + " no ha sido inicializado " , o->getLine() ));

        return (void*)Undefined;
    }

}

void * Checker::visit(ASTUnion * o )
{

    MemoTypes  t1 =*((MemoTypes *) o->GetOp1()->visit(this));
    MemoTypes  t2 =*((MemoTypes *) o->GetOp2()->visit(this));

    if( t1 != t2 )
    {
        errorReporter->AddError(new CompilerError(" Error  semántico: Operación de union de  tipos  incompatibles" , o->getLine()));
        return (void*)Undefined;
    }
    else
    {
        o->setType( Rank );
        return  &(t1) ;
    }
}

void * Checker::visit(ASTInterception * o )
{

    MemoTypes * t1 = (MemoTypes *) o->GetOp1()->visit(this);
    MemoTypes * t2 = (MemoTypes *) o->GetOp2()->visit(this);

    if( t1 != t2 )
    {
        errorReporter->AddError(new CompilerError(" Error  semántico: Operación de intercepcion de  tipos  incompatibles" , o->getLine()));
        return (void*)Undefined;
    }
    else
    {
        o->setType( Rank );
        return (void*)t1 ;
    }
    return 0;
}

void * Checker::visit(ASTDifference * o )
{


    MemoTypes * t1 = (MemoTypes *) o->GetOp1()->visit(this);
    MemoTypes * t2 = (MemoTypes *) o->GetOp2()->visit(this);

    if( t1 != t2)
    {
        errorReporter->AddError(new CompilerError(" Error  semántico: Operación de diferencia de  tipos  incompatibles" , o->getLine()));
        return (void*) Undefined;
    }
    else
    {

        o->setType(Rank);
        return (void*)t1 ;
    }
    return 0;
}

void * Checker::visit ( ASTInitRankExp * o)
{


    MemoTypes * t1 = (MemoTypes *) o->GetID()->visit(this);
    MemoTypes * t2 = (MemoTypes *) o->GetP1()->visit(this);


    if( t1 != t2)
    {
        errorReporter->AddError(new CompilerError(" Error  semántico:  Operación asignación de  tipos   incompatibles" , o->getLine()));
        return (void*) Undefined;
    }
    return 0;
}

void * Checker::visit ( ASTInitInt * o)
{
    MemoTypes * t1 = (MemoTypes *) o->GetID()->visit(this);
    MemoTypes * t2 = (MemoTypes *) o->GetP1()->visit(this);
    //qDebug("t1: %d - t2: %d", *t1, *t2);

    if( t1 != t2)
    {
        errorReporter->AddError(new CompilerError(" Error  semántico:  Operación asignación con son incompatible"  , o->getLine()));
        return (void*)Undefined;
    }

    return 0;
}

void * Checker::visit ( ASTInitRank * o)
{

    MemoTypes * t1 =(MemoTypes *) o->GetID()->visit(this);
    MemoTypes * t2 =(MemoTypes *) o->GetP1()->visit(this);
    MemoTypes * t3 =(MemoTypes *) o->GetP2()->visit(this);

    if (t1 == (void *)Rank && t2 == (void *)Int && t3 == (void *)Int)
        return 0;
    else
    {
        //qDebug("t2: %d - t3: %d", *t2, *t3);
        if( t2 != (void*)Int || t3 != (void*)Int)
            errorReporter->AddError(new CompilerError("Error Semántico:  Operación parametro de  tipos   incompatibles" , o->getLine()));
        if( t1 != (void*)Rank )
            errorReporter->AddError(new CompilerError("Error Semántico:  Operación asignación de  tipos   incompatibles" , o->getLine()));
        return (void*) Undefined;
    }

}

void * Checker::visit ( ASTPrint * o)
{
    o->GetID()->visit(this);
    return 0;
}

void * Checker::visit(ASTIntValue *o )
{
    return (void *)Int;
}



