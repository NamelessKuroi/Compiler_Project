#include "tree.h"
#include "../ast/AbstractSyntaxTree.h"



Tree::Tree(QTreeWidget * a , SymbolsTable * TS)
{
    arbol = a;
    ts = TS;
}

void * Tree::visit(ASTProgram * o )
{

    o->setParent(arbol->invisibleRootItem());
    QList < ASTInstruction * > I;
    I.append( o->GetList());

    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTProgram");

    o->getParent()->addChild(item);

    for(int i = 0 ; i < I.size() ; i++ )
    {
        I.value(i)->setParent(item);
        I.value(i)->visit(this);
    }

    return 0;

}

void * Tree::visit ( ASTDeclaration * o )
{
    QList < ASTIdentifierDeclaration * > D;
    D.append( o->GetList());


    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTDeclaration");

    o->getParent()->addChild(item);

    for(int i = 0 ; i < D.size() ; i++ )
    {
        D.value(i)->setParent(item);
        D.value(i)->visit(this);
    }

    return 0 ;
}

void * Tree::visit ( ASTIdentifierDeclaration * o )
{


    QTreeWidgetItem * item  = new QTreeWidgetItem();

    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTIdentifierDeclaration");
    o->getParent()->addChild(item);

    SymbolInfo * info = ts->Entry(o->GetEntry());
    QTreeWidgetItem * child  = new QTreeWidgetItem();

    child->setIcon(0 , QIcon(":/images/docs.png"));
    child->setText(0,info->getLexeme());
    item->addChild(child);

    return 0 ;
}

void * Tree:: visit ( ASTIdentifierReference * o  )
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTIdentifierReference");
    o->getParent()->addChild(item);

    SymbolInfo * info = ts->Entry(o->GetEntry());
    QTreeWidgetItem * child  = new QTreeWidgetItem();

    child->setIcon(0 , QIcon(":/images/docs.png"));
    child->setText(0,info->getLexeme());
    item->addChild(child);


    return 0 ;
}

void * Tree::visit ( ASTIdentifierValue *  o )
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTIdentifierValue");
    o->getParent()->addChild(item);

    SymbolInfo * info = ts->Entry(o->GetEntry());
    QTreeWidgetItem * child  = new QTreeWidgetItem();

    child->setIcon(0 , QIcon(":/images/docs.png"));
    child->setText(0,info->getLexeme());
    item->addChild(child);


    return 0 ;
}

void * Tree::visit ( ASTUnion *  o)
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTUnion");
    o->getParent()->addChild(item);

    o->GetOp1()->setParent(item);
    o->GetOp2()->setParent(item);
    o->GetOp1()->visit(this);
    o->GetOp2()->visit(this);

    return 0 ;
}

void * Tree::visit ( ASTInterception * o )
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTInterception");
    o->getParent()->addChild(item);

    o->GetOp1()->setParent(item);
    o->GetOp2()->setParent(item);
    o->GetOp1()->visit(this);
    o->GetOp2()->visit(this);

    return 0 ;
}

void * Tree::visit ( ASTDifference * o )
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTDifference");
    o->getParent()->addChild(item);

    o->GetOp1()->setParent(item);
    o->GetOp2()->setParent(item);
    o->GetOp1()->visit(this);
    o->GetOp2()->visit(this);
    return 0 ;
}

void * Tree::visit ( ASTInitInt * o )
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTInitInt");
    o->getParent()->addChild(item);

    o->GetID()->setParent(item);
    o->GetP1()->setParent(item);

    o->GetID()->visit(this);
    o->GetP1()->visit(this);


    return 0 ;
}

void * Tree::visit ( ASTInitRank * o )
{

    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTInitRank");
    o->getParent()->addChild(item);

    o->GetID()->setParent(item);
    o->GetP1()->setParent(item);
    o->GetP2()->setParent(item);

    o->GetID()->visit(this);
    o->GetP1()->visit(this);
    o->GetP2()->visit(this);


    return 0 ;
}

void * Tree::visit ( ASTInitRankExp * o )
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTInitRankExp");
    o->getParent()->addChild(item);

    o->GetID()->setParent(item);
    o->GetP1()->setParent(item);

    o->GetID()->visit(this);
    o->GetP1()->visit(this);

    return 0 ;
}

void * Tree:: visit ( ASTPrint * o)
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTPrint");
    o->getParent()->addChild(item);

    o->GetID()->setParent(item);
    o->GetID()->visit(this);

    return 0 ;
}

void * Tree:: visit ( ASTIntValue * o)
{
    QTreeWidgetItem * item  = new QTreeWidgetItem();
    item->setIcon(0 , QIcon(":/images/open.png"));
    item->setText(0,"ASTIntValue");
    o->getParent()->addChild(item);

    SymbolInfo * info = ts->Entry(o->GetEntry());
    QTreeWidgetItem * child  = new QTreeWidgetItem();

    child->setIcon(0 , QIcon(":/images/docs.png"));
    child->setText(0,info->getLexeme());
    item->addChild(child);


    return 0 ;
}
