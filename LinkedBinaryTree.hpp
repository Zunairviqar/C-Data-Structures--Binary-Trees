//
//  LinkedBinaryTree.h
//  homeWk3
//
//  Created by Sebti Foufou on 12/04/2020.
//  Copyright © 2020 Sebti Foufou. All rights reserved.
//

#ifndef LinkedBinaryTree_h
#define LinkedBinaryTree_h

#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <list>
#include "GeneralTree.hpp"


using namespace std;

typedef string Elem;        // base element type

class LinkedBinaryTree
{
    friend class GeneralTree;
protected:
    struct Node {            // a node of the tree
        Elem    elt;        // element value
        Node*   par;        // parent
        Node*   left;        // left child
        Node*   right;        // right child
        
        // constructor
        Node() : elt(), par(NULL), left(NULL), right(NULL) { };
        Node(const Elem& ee, Node* _par=NULL, Node* _left=NULL, Node* _right=NULL) : elt(ee), par(_par), left(_left), right(_right) { };
    };
    
public:
    class Position {        // position in the tree
    private:
        Node* v;            // pointer to the node
    public:
        Position(Node* _v = NULL): v(_v) { }        // constructor
        Elem& operator*()                    // get element
        { return v->elt; }
        Position left() const                // get left child
        { return Position(v->left); }
        Position right() const                // get right child
        { return Position(v->right); }
        Position parent() const                // get parent
        { return Position(v->par); }
  
        bool isRoot() const                    // root of the tree?
        { return v->par == NULL; }
        bool isExternal() const                // an external node?
        { return v->left == NULL && v->right == NULL; }
        friend class LinkedBinaryTree;         // give tree access
    };
    typedef std::list<Position> PositionList;  // list of positions
    
public:
    LinkedBinaryTree();                    // constructor
    int size() const;                    // number of nodes
    bool empty() const;                    // is tree empty?
    Position root() const;                // get the root
    PositionList positions() const;              // list of nodes
    void addRoot();                    // add root to empty tree
    void addRoot(const Elem& ee);            // add root to empty tree
    void expandExternal(const Position& p);   // expand external node
    void expandExternal(const Position& p, const Elem& _left, const Elem& _right);
    void expandExternal(const Position& p, const Elem& _left, int child=0); // 0 expand left,  right
    Position removeAboveExternal(const Position& p);    // remove p and parent
    // Other housekeeping functions omitted...
    void displayTree() ;
    //New Functions
    int maxDepth(Node* ptr);
    void printTreeHelper(Elem *X, bool *Y,Node *ptr, int n);
    bool equal(LinkedBinaryTree& TreeB);
    LinkedBinaryTree generalTree2BinaryTree(GeneralTree TreeB);
    void generalTree2BinaryTreeHelper(LinkedBinaryTree& newTree, GeneralTree::GTNode* curnode, Position pos);
    
protected:                         // local utilities
    void preorder(Node* v, PositionList& pl) const;    // preorder utility
    void postorder(Node* v, PositionList& pl) const;// postorder utility
    void inorder(Node* v, PositionList& pl) const;// inorder utility

private:
    Node* _root;                // pointer to the root
    int n;                        // number of nodes
};
#endif /* LinkedBinaryTree_h */
