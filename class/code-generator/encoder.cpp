#include "encoder.h"

Encoder::Encoder(SymbolsTable *st) : Visitor()
{
    symbolTable = st;
    currentMemDir = 0;
}

//aqui

void * Encoder::visit(ASTProgram * o )
{
    QList < ASTInstruction * >  I;
         I.append(o->GetList());
    for(int i = 0 ; i < I.size() ; i++ )
    {
        I.value(i)->visit(this);
    }
 return 0;
}

void * Encoder::visit(ASTDeclaration * o )
{
    QList < ASTIdentifierDeclaration * > I;
    I.append(o->GetList());
    for(int i = 0 ; i < I.size() ; i++ )
    {
        I.value(i)->visit(this);
    }
 return 0;
}

void * Encoder::visit(ASTIdentifierDeclaration * o )
{
    SymbolInfo * info = symbolTable->Entry( o->GetEntry());

    if( info->getType() == Int )
    {
        code.append(new RuntimeNewInt());
        info->setAddress(currentMemDir++);
    }
    else
    {
        code.append(new RuntimeNewRank());
        info->setAddress(currentMemDir++);
    }

    return 0;
}

void * Encoder::visit(ASTIdentifierReference * o )
{
    SymbolInfo * info = symbolTable->Entry(o->GetEntry());
    code.append( new RuntimeCargaDir());
    code.append( new IntValue( info->getAddress()));

  return 0;
}

void * Encoder::visit(ASTIdentifierValue * o )
{
    MemoTypes t;
    MemoTypes * a = &t;
    SymbolInfo * info = symbolTable->Entry(o->GetEntry());
    t = info->getType();
    code.append( new RuntimeCarga());
    code.append( new IntValue( info->getAddress()));
    return a;
}

void * Encoder::visit(ASTUnion * o )
{
   o->GetOp1()-> visit( this );
   o->GetOp2()-> visit( this );
   code.append( new RuntimeUnion());
   return 0;
}

void * Encoder::visit(ASTInterception * o )
{
   o->GetOp1()-> visit( this );
   o->GetOp2()-> visit( this );
   code.append( new RuntimeInterception());
   return 0;

}

void * Encoder::visit(ASTDifference * o )
{
   o->GetOp1()-> visit( this );
   o->GetOp2()-> visit( this );
   code.append( new RuntimeDifference());
   return 0;
}

void * Encoder::visit ( ASTInitRankExp * o)
{
    o->GetID()->visit(this);
    o->GetP1()->visit(this);
    code.append(new RuntimeStore());
    return 0;
}

void * Encoder::visit ( ASTInitInt * o)
{
    o->GetID()->visit(this);
    o->GetP1()->visit(this);
    code.append(new RuntimeStore());
 return 0;
}

void * Encoder::visit ( ASTInitRank * o)
{
    o->GetID()->visit(this);
    o->GetP1()->visit(this);
    o->GetP2()->visit(this);
    code.append(new RuntimeInitRank());
    code.append(new RuntimeStore());
    return 0;
}

void * Encoder::visit ( ASTPrint * o)
{

    MemoTypes * t =  (MemoTypes*)o->GetID()->visit(this);
    if(*t == Int)
     code.append(new RuntimePrint(Int));
    else if(*t== Rank)
     code.append(new RuntimePrint(Rank));
    else
     code.append(new RuntimePrint(Undefined));

    return 0;
}

void * Encoder::visit( ASTIntValue * o )
{
    SymbolInfo * info = symbolTable->Entry( o->GetEntry());

    if ( info->getAddress() == -1 )
    {

        code.append( new RuntimeNewInt ());
        info->setAddress( currentMemDir++);

        code.append( new RuntimeCargaDir());
        IntValue * address = new IntValue(info->getAddress());
        code.append( address);

        code.append( new RuntimePush());
        IntValue * value = new IntValue(info->getLexeme().toInt());
        code.append( value );
        code.append( new RuntimeStore());

    }

    IntValue * address = new IntValue( info->getAddress());
    code.append( new RuntimeCarga());
    code.append( address);

    return 0;
}





