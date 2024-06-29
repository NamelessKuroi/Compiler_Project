#ifndef VISITOR_H
#define VISITOR_H

class AST;
class ASTProgram;
class ASTExpRank;
class ASTOperatorBinary;
class ASTUnion;
class ASTInterception;
class ASTDifference;
class ASTSymbol;
class ASTIntValue;

class ASTIdentifier;
class ASTIdentifierDeclaration;
class ASTIdentifierReference;
class ASTIdentifierValue;

class ASTInstruction;
class ASTDeclaration;

class ASTPrint;

class ASTAssignation;
class ASTInitInt;
class ASTInitRank;
class ASTInitRankExp;


class Visitor
{
public:
    Visitor() {}

    virtual void * visit ( ASTProgram *  )= 0;
    virtual void * visit ( ASTUnion *  )= 0;
    virtual void * visit ( ASTInterception *  )= 0;
    virtual void * visit ( ASTDifference *  )= 0;
    virtual void * visit ( ASTInitInt *  )= 0;
    virtual void * visit ( ASTInitRank *  )= 0;
    virtual void * visit ( ASTInitRankExp *  )= 0;
    virtual void * visit ( ASTDeclaration * )=0;
    virtual void * visit ( ASTIdentifierDeclaration *  )= 0;
    virtual void * visit ( ASTIdentifierValue *  )= 0;
    virtual void * visit ( ASTIdentifierReference *  )= 0;
    virtual void * visit ( ASTPrint * )=0;
    virtual void * visit ( ASTIntValue * )=0;



};

#endif // VISITOR_H
