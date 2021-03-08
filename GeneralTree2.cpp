#include <stdio.h>
#include "GeneralTree.hpp"

int GeneralTree::size() const            // number of nodes
{
    return n;
}

bool GeneralTree::empty() const          // is tree empty?
{
    return size() == 0;
}

GeneralTree::Position GeneralTree::root() const // get the root
{
    return Position(_root);
}

void GeneralTree::addRoot(const Elem& e)    // add root to empty tree
{
    _root = new GTNode(e);
    n = 1;
}


void GeneralTree::addChild(const Elem& ee, const Position& p)
{
    GTNode* par = p.v ;
    par->addChild(ee) ;
    n++ ;
}
void GeneralTree::addChild(const Elem& ee, GTNode* p)
{
    if(p) {
        p->addChild(ee) ;
        n++ ;
    }
}
void GeneralTree::preorderHelper(GTNode* r, GTNList& gtnods)
{
    gtnods.push_back(r) ; // add this node
    if(r->children!=NULL) {
        list<GTNode*>::iterator pp = r->children->begin() ;
        while(pp!=r->children->end()) {
            preorderHelper(*pp, gtnods) ;
            pp++;
        }
    }
}

void GeneralTree::preorder(GTNList& gtnods)
{
    preorderHelper(_root, gtnods) ;
}

void GeneralTree::postorderHelper(GTNode* r, GTNList& gtnods)
{
    if(r->children!=NULL) {
        list<GTNode*>::iterator pp = r->children->begin() ; //Iterator initialised at the beginning of the list
        while(pp!=r->children->end()) {
            postorderHelper(*pp, gtnods) ;
            pp++; //increments iterator
        }
        
    }
    gtnods.push_back(r) ; //Push into the list at the end for Postorder
}

void GeneralTree::postorder(GTNList& gtnods)
{
    postorderHelper(_root, gtnods) ; //Calls PostOrderHelper function that works recursively
}

GeneralTree::GTNode* GeneralTree::Position::getSibling() const
{
   if(this->hasSibling()) //Checks if there is a sibling
   {
       GTNode* parentnode = new GTNode(); //Makes a new node
       parentnode = this->parent(); //Gets the node at the parent of the current Position
       std::list<GTNode*>* ChildrenList;
       ChildrenList = parentnode->getChildren(); //List of the Siblings of the current Position

       list<GeneralTree::GTNode*>::iterator itCL = ChildrenList->begin() ;
        while (itCL!=ChildrenList->end())
        {
            if((*itCL)->getElt() == this->v->elt) //Checks if the Node that called is reached (or is the same in the Children List)
            {
                itCL++; //If condition is true, goes to the node on the right
                if(itCL==ChildrenList->end()) return NULL; //Returns NULL incase there is no sibling to the right
                return (*itCL); //Returns the Node to the Sibling
            }
            itCL++;
        }
       if(itCL==ChildrenList->end()) return NULL;

   }
    return NULL;
}

GeneralTree::Position GeneralTree::GoToFirstChild(GTNode* x) const // It changes the position to the first child of current Position
{
    if(x->children!=NULL) //Checks if there are any children of the node
    {
        return Position(x->children->front()); //Returns the node to the first child
    }
    return NULL; //Otherwise returns NULL
}

//Another Method Of getSibling()
//GeneralTree::GTNode* GeneralTree::Position::getSibling() const
//{
//    GTNode* parentnode = new GTNode;
//    parentnode = this->parent();
//    std::list<GTNode*>* ChildrenList;
//    ChildrenList= parentnode->getChildren();
//
//    list<GeneralTree::GTNode*>::iterator itCL;
//    for(itCL = ChildrenList->begin(); itCL!=ChildrenList->end(); itCL++) {
//        if((itCL)->getElt()==this->v->elt) {
//            if(itCL==ChildrenList->end()) { return NULL;}
//            else
//            }
//                itCL++;
//                return (*itCL);
//            }
//        }
//        else {itCL++;}
//    }
//    return NULL;
//}
