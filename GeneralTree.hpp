#ifndef GeneralTree_h
#define GeneralTree_h

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include <string>

using namespace std ;

typedef string Elem;        // base element type

// General Tree class
class GeneralTree
{
public:
    // a node of the General Tree
    class GTNode
    {
    private:
        Elem      elt;        // element value
        GTNode*   par;        // parent
        std::list<GTNode*>* children ;
    public:
        // constructor
        GTNode() : elt(), par(NULL), children(NULL) { };
        GTNode(const Elem& ee, GTNode* _par=NULL) : elt(ee), par(_par), children(NULL){ };
        Elem getElt() {return elt ;}
        std::list<GTNode*>* getChildren() { return children ;}
        GTNode* getNparent() const { return par; }  // get parent
        void setNparent(GTNode* x)
        {
            par = x;
        }  // set parent
        // update
        void addChild(const Elem& ee) {
            if(children==NULL) children = new list<GTNode*> ;
            children->push_back(new GTNode(ee,this)) ;
        }
        
        bool hasSibling() {
            return this!=par->children->back() ;
        }
        
        // Friend declarations
        friend class GeneralTree;
        friend class Position ;
};
    
public:
    typedef std::list<GTNode*> GTNList ;
    class Position
    {
    private:
        GTNode* v ;
        
    public:
        Position(GTNode* p=NULL): v(p) {} // Constructor
        Elem& operator*() { return v->elt; } // Get element
        GTNode* parent() const { return v->par; }  // get parent
        GTNList* children() const { return v->children ; } // get node’s children
        GTNode* firstChild() const { return (v->children==NULL)?NULL:v->children->front();}
        
        // Test methods
        bool isRoot() const { return v->par == NULL; }     // root node?
        bool isExternal() const { return v->children == NULL ;}  // external node?
        bool hasSibling() const { return v!=v->par->children->back() ;}
        GTNode* getSibling() const ;
         
        // Friend declarations
        friend class GeneralTree;
    };

 
public:
    GeneralTree(): _root(NULL), n(0) { } // Constructor
    int size() const;         // number of nodes
    bool empty() const;       // is tree empty?
    Position root() const;    // get the root
    GTNode* getRoot() {return _root ;}
    void preorder(GTNList& gtnods) ;
    void postorder(GTNList& gtnods) ;
    void addRoot(const Elem& ee);   // add root to empty tree
    void addChild(const Elem& ee, const Position& p) ;
    void addChild(const Elem& ee, GTNode* p) ;
    //New Function
    Position GoToFirstChild(GTNode*x) const;

private:
    void preorderHelper(GTNode* r, GTNList& gtnods) ;
    void postorderHelper(GTNode* r, GTNList& gtnods) ;
    
private:
    GTNode* _root;                // pointer to the root
    int n;                        // number of nodes
};
#endif

