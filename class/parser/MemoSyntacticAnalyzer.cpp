#include "MemoSyntacticAnalyzer.h"
#include "console.h"

MemoSyntacticAnalyzer::MemoSyntacticAnalyzer(LexicalAnalyzer *scanner, ErrorReporter *errorReporter)
    : SyntacticAnalyzer(scanner, errorReporter)
{
    currentToken = scanner->NextToken();

}

void MemoSyntacticAnalyzer::recuperate(TokenKind tk_expected)
{
    while (currentToken->GetKind() != tk_expected && currentToken->GetKind() != tk_EOF)
        consume();
}

void MemoSyntacticAnalyzer::recuperate(QList<TokenKind> tokens)
{
    while (!tokens.contains(currentToken->GetKind()) && currentToken->GetKind() != tk_EOF)
        consume();
}

AST * MemoSyntacticAnalyzer::Parse()
{
    // Simbolo inicial de la gramatica
    memotree = Program();
    if (currentToken->GetKind() != tk_EOF)
    {
        errorReporter->AddError(new CompilerError("Error Sintactico: Se esperaba el token fin de fichero "
                                                  "y se encontraba el token " + currentToken->GetLexeme(),
                                                  currentToken->GetLine()));

        recuperate(tk_EOF);
    }

    return memotree;
}


ASTInstruction * MemoSyntacticAnalyzer::Instruction()
{
    ASTInstruction * temp = new ASTInstruction(0);
    temp->setNull(true);

    if ( currentToken->GetKind() == tk_Print)
    {
        return Print();
    }

    if( currentToken->GetKind() == tk_Int || currentToken->GetKind() == tk_Rank  )
    {
        return Declaration();
    }

    if( currentToken->GetKind() == tk_Id || currentToken->GetKind() == tk_InitRank  )
    {
        return Assignation();
    }

    return temp;
}

QList<  ASTInstruction * >  MemoSyntacticAnalyzer::Instructions ()
{
    QList<  ASTInstruction * > I;

    ASTInstruction * temp = Instruction();
    I.append(temp);
    return MoreInstructions(I);
}

QList<  ASTInstruction * >  MemoSyntacticAnalyzer::MoreInstructions (QList<  ASTInstruction *>  I)
{
    ;
    ASTInstruction * temp = Instruction();


    if ( !temp->IsNull())
    {
        I.append(temp );
        return MoreInstructions(I);
    }
    return I;
}

ASTProgram * MemoSyntacticAnalyzer::Program()
{   QList < ASTInstruction *>  I;

    Match(tk_Main);
    Match(tk_Par_Izq);
    Match(tk_Par_Der);
    Match(tk_Llave_Izq);
    I.append( Instructions());
    Match(tk_Llave_Der);

    return new ASTProgram(0 , I);
}

ASTPrint * MemoSyntacticAnalyzer::Print()
{
    ASTPrint * t = new ASTPrint(0 , new ASTIdentifierValue(0,0));
    t->setNull(true);
    Match(tk_Print);

    if ( currentToken->GetKind() == tk_Id )
    {
        ASTIdentifierValue * temp = new ASTIdentifierValue(currentToken->GetLine(), currentToken->GetTableEntry());
        Match(tk_Id);
        Match(tk_Pto_Coma);
        return new ASTPrint(0 , temp);
    }
    else
        errorReporter->AddError(new CompilerError("Error Sintáctico: Se esperaba el token: " + Token::TokenKindString(tk_Id) +
                                                  " y se encontró el token " + currentToken->GetLexeme(), currentToken->GetLine()));
    Match(tk_Pto_Coma);
    return t;
}

ASTDeclaration * MemoSyntacticAnalyzer::Declaration()
{
    QList <ASTIdentifierDeclaration * >  I;
    MemoTypes T = Tipo();

    if( currentToken->GetKind() == tk_Id)
    {
        ASTIdentifierDeclaration * temp = new ASTIdentifierDeclaration(currentToken->GetLine(), currentToken->GetTableEntry());
        I.append(temp);
        Match(tk_Id);
    }

    if( currentToken->GetKind() == tk_Coma)
    {

        return new ASTDeclaration( 0 , T, MoreIdentifier(I));
    }
    else
        Match(tk_Pto_Coma);

    return new ASTDeclaration( 0 , T, I);
}

QList <ASTIdentifierDeclaration*>  MemoSyntacticAnalyzer::MoreIdentifier(QList <ASTIdentifierDeclaration*> I)
{

    Match(tk_Coma);
    if( currentToken->GetKind() == tk_Id)
    {
        ASTIdentifierDeclaration * temp = new ASTIdentifierDeclaration(currentToken->GetLine(), currentToken->GetTableEntry());
        I.append(temp);
        Match(tk_Id);
        if(currentToken->GetKind() == tk_Coma)
            return MoreIdentifier(I);
        else
            Match(tk_Pto_Coma);
    }
    else
        errorReporter->AddError(new CompilerError("Error Sintactico:Falta tk_Id",currentToken->GetLine()));


    return I ;
}


ASTAssignation * MemoSyntacticAnalyzer::Assignation()
{ ASTAssignation * t = new ASTAssignation(0 , new ASTIdentifierReference(0,0));
    t->setNull(true);
    if( currentToken->GetKind() == tk_InitRank )
    {
        Match(tk_InitRank);
        if(currentToken->GetKind() == tk_Id)
        {
            ASTIdentifierReference * temp = new  ASTIdentifierReference(currentToken->GetLine(), currentToken->GetTableEntry());
            Match(tk_Id);
            ASTSymbol * a = new ASTSymbol(0,0);
            a->setNull(true);
            ASTSymbol * b = new ASTSymbol(0,0);
            b->setNull(true);
            Match(tk_Coma);
            return ParametrodeRango( new ASTInitRank(0 , temp , a , b) );
        }
        else
            errorReporter->AddError(new CompilerError("Error Sintactico:Falta tk_Id",currentToken->GetLine()));

    }

    if( currentToken->GetKind() == tk_Id )
    {
        ASTIdentifierReference * t1 = new ASTIdentifierReference(currentToken->GetLine(), currentToken->GetTableEntry());
        Match(tk_Id);
        if(currentToken->GetKind() == tk_Asig )
        {
            Match(tk_Asig);
            ASTSymbol* t2 = Parametro();
            Match(tk_Pto_Coma);
            return new ASTInitInt(0,t1,t2);
        }
        else
            if(currentToken->GetKind() == tk_AR)
            {
                Match(tk_AR);
                ASTExpRank * t2 = ExpRank();
                Match(tk_Pto_Coma);
                return new ASTInitRankExp( 0,t1 ,t2);

            }
            else
                errorReporter->AddError(new CompilerError("Error Sintactico:Falta Operador de Asignacion",currentToken->GetLine() ) );
    }

    return t;
}

ASTExpRank * MemoSyntacticAnalyzer::ExpRank()
{
    return MasT2(T2());
}

ASTExpRank * MemoSyntacticAnalyzer::T2()
{
    return MasT1(T1());
}

ASTExpRank * MemoSyntacticAnalyzer::MasT2(ASTExpRank * ER)
{
    if(currentToken->GetKind() == tk_Dif )
    {
        Match( tk_Dif);
        return new ASTDifference(0 , ER , MasT2(T2()));
    }
    return ER;
}

ASTExpRank * MemoSyntacticAnalyzer::T1()
{
    return MasFactor( Factor());
}

ASTExpRank * MemoSyntacticAnalyzer::MasT1(ASTExpRank * ER )
{
    if(currentToken->GetKind() == tk_Inter )
    {
        Match(tk_Inter);
        return new ASTInterception(0, ER , MasT1( T1() ));
    }
    return ER;
}

ASTExpRank * MemoSyntacticAnalyzer::Factor()
{    ASTExpRank * t = new ASTExpRank(0);
     t->setNull(true);

      if( currentToken->GetKind() == tk_Id )
      {

          ASTIdentifierValue * temp = new ASTIdentifierValue(currentToken->GetLine(), currentToken->GetTableEntry());
          Match(tk_Id);
          return temp;
      }
      else

          if( currentToken->GetKind() == tk_Par_Izq )
          {
              Match(tk_Par_Izq);
              ASTExpRank * temp = ExpRank();
              Match(tk_Par_Der);
              return temp;
          }
          else
              errorReporter->AddError(new CompilerError("Error Sintáctico: Se esperaba el token: " + Token::TokenKindString(tk_Id) +
                                                        " y se encontró el token " + currentToken->GetLexeme(), currentToken->GetLine()));

       return t;
}

ASTExpRank * MemoSyntacticAnalyzer::MasFactor( ASTExpRank * ER)
{
    if(currentToken->GetKind() == tk_Union )
    {
        Match(tk_Union);
        return new ASTUnion(0 , ER , MasFactor( Factor() ));
    }

    return ER;
}


MemoTypes MemoSyntacticAnalyzer::Tipo ()
{
    if ( currentToken->GetKind() == tk_Int)
    {
        Match(tk_Int);
        return Int;
    }
    if  ( currentToken->GetKind() == tk_Rank)
    {
        Match(tk_Rank);
        return Rank;
    }
    errorReporter->AddError(new CompilerError("Error Sintactico: Falta el Tipo en la Declaracion",currentToken->GetLine()));
    return Undefined;
}

ASTSymbol * MemoSyntacticAnalyzer::Parametro()
{   ASTSymbol * t = new ASTSymbol(0,0);
    t->setNull(true);
    if ( currentToken->GetKind() == tk_Id)
    {
        ASTIdentifierValue * temp = new ASTIdentifierValue(currentToken->GetLine(),currentToken->GetTableEntry());
        Match(tk_Id);
        return  temp;
    }
    else
        if ( currentToken->GetKind() == tk_Literal_Entero)
        {

            ASTIntValue * temp = new ASTIntValue( currentToken->GetLine(), currentToken->GetTableEntry() );
            Match(tk_Literal_Entero);
            return  temp;
        } else
            errorReporter->AddError(new CompilerError("Error Sintactico: Falta el Parametro",currentToken->GetLine()));

    return t;
}

ASTInitRank * MemoSyntacticAnalyzer::ParametrodeRango( ASTInitRank * IR)
{
    Match( tk_Par_Izq);
    ASTSymbol * p1 = Parametro();
    Match(tk_Coma);
    ASTSymbol * p2 = Parametro();
    Match( tk_Par_Der);
    IR->SetP1(p1);
    IR->SetP2(p2);
    Match(tk_Pto_Coma);
    return IR;
}


