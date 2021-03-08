//
//  LinkedBinaryTree.c
//  homeWk3
//
//  Created by Sebti Foufou on 12/04/2020.
//  Copyright © 2020 Sebti Foufou. All rights reserved.
//


#include <cstdlib>
#include <iostream>
#include "LinkedBinaryTree.hpp"

using namespace std;

LinkedBinaryTree::LinkedBinaryTree()            // constructor
    : _root(NULL), n(0) { }

int LinkedBinaryTree::size() const            // number of nodes
    { return n; }

bool LinkedBinaryTree::empty() const            // is tree empty?
    { return size() == 0; }

LinkedBinaryTree::Position LinkedBinaryTree::root() const // get the root
    { return Position(_root); }

void LinkedBinaryTree::addRoot()    // add root to empty tree
    { _root = new Node; n = 1; }

void LinkedBinaryTree::addRoot(const Elem& e)    // add root to empty tree
{ _root = new Node(e); n = 1; }

void LinkedBinaryTree::expandExternal(const Position& p) {
    Node* v = p.v;                    // p's node
    v->left = new Node;                    // add a new left child
    v->left->par = v;                    // v is its parent
    v->right = new Node;                // and a new right child
    v->right->par = v;                    // v is its parent
    n += 2;                        // two more nodes
}

// To be able to create sample tree
void LinkedBinaryTree::expandExternal(const Position& p, const Elem& _le, const Elem& _re)
{
    Node* v = p.v;                    // p's node
    v->left = new Node(_le, v);       // add a new left child
    v->right= new Node(_re, v);      // and a new right child
    n += 2;                        // two more nodes
}

// 0 expand left,  otherwise exapns right
void LinkedBinaryTree::expandExternal(const Position& p, const Elem& ee, int child)
{
    Node* v = p.v;                    // p's node
    if(child==0) {
        v->left = new Node(ee, v);         // dd non empty left child
        v->right = new Node;                // and a empty right child
        v->right->par = v;                  // v is its parent
    }
    else {
        v->right= new Node(ee, v);      // and a non empty right child
        v->left = new Node;             // add a empty left child
        v->left->par = v;               // v is its parent
    }
    n += 2;                        // two more nodes
}


LinkedBinaryTree::Position                // remove p and parent
LinkedBinaryTree::removeAboveExternal(const Position& p) {
    Node* w = p.v;  Node* v = w->par;        // get p's node and parent
    Node* sib = (w == v->left ?  v->right : v->left);
    if (v == _root) {                    // child of root?
      _root = sib;                    // ...make sibling root
      sib->par = NULL;
    }
    else {
      Node* gpar = v->par;                // w's grandparent
      if (v == gpar->left) gpar->left = sib;         // replace parent by sib
      else gpar->right = sib;
      sib->par = gpar;
    }
    delete w; delete v;                    // delete removed nodes
    n -= 2;                        // two fewer nodes
    return Position(sib);
}

LinkedBinaryTree::PositionList LinkedBinaryTree::positions() const {
  PositionList pl;
  preorder(_root, pl);                    // preorder traversal
  return PositionList(pl);                // return resulting list
}

// preorder traversal
void LinkedBinaryTree::preorder(Node* v, PositionList& pl) const
{
    pl.push_back(Position(v));                // add this node
    
    // traverse left, then right subtrees
    if (v->left != NULL) preorder(v->left, pl);
    if (v->right != NULL) preorder(v->right, pl);
}

// postorder traversal
void LinkedBinaryTree::postorder(Node* v, PositionList& pl) const
{
    // traverse left, then right subtrees
    if(v->left != NULL) postorder(v->left, pl);
    if(v->right!= NULL) postorder(v->right, pl);
    
    // add this node
    pl.push_back(Position(v));
}

// inorder traversal
void LinkedBinaryTree::inorder(Node* v, PositionList& pl) const
{
//

    LinkedBinaryTree::Position a(v);
    if(!a.isExternal())
    {
        inorder(v->left,pl); //Recursive Call till it reaches the left
    }
    pl.push_back(Position(v)); //Add element into the list
    
    if(!a.isExternal())
    {
        inorder(v->right,pl); //Recursive Call till it reaches the right
    }
// ANOTHER METHOD
    
//    if(v->left!=NULL)
//    {
//        inorder(v->left,pl);
//    }
//    pl.push_back(Position(v));
//    if(v->right!=NULL)
//    {
//        inorder(v->right,pl);
//    }
    
// (ADAPTED FROM SLIDE 38 OF TREES AS BELOW)
//    1: function binaryInorder(T, p)
//    2: if (!p.isExternal()) then
//    3: binaryInorder(T,p.left());
//    4: end if
//    5: perform visit-action for node p
//    6: if (!p.isExternal()) then
//    7: binaryInorder(T,p.right());
//    8: end if
//    9: end function
}

//Adapted from Lab 9 to Display Tree Properly
int LinkedBinaryTree::maxDepth(Node* ptr)
{
    if(ptr==NULL) return -1;
    else             return max(maxDepth(ptr->left),maxDepth(ptr->right))+1;
}

// Display the tree
void LinkedBinaryTree::displayTree()
{
    PositionList p1;
    inorder(_root,p1); //Calls the inorder function to get a list of the elements in 'inorder' form
    std::list<Position>::iterator it; //Declaration of iterator it
    cout<<"Inorder Traversal"<<endl;
    // Make iterate point to begining and incerement it one by one till it reaches the end of list.
    
    //p1.pop_front(); //To remove empty space at the beginning
    for (it = p1.begin() ; it != p1.end() ; it++)
    {
        cout<<*p1.front()<<" "; //Displays the element at the front of the list
        p1.pop_front(); //Pops the element to allow the next element to be printed
    }
    cout<<endl;

//Code below is adapted from slides to Display a representation of the tree

    int d = maxDepth(_root);
    int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

    Elem *A = new Elem[n];
    bool *B = new bool[n];
    for(int i=0; i<n; ++i) B[i]=false;

    printTreeHelper(A,B,_root,n);

    for(int t=(n+1)/2; t>0; t=t/2){
         for(int j=0; j<n; j++){
             if( ((j+1)%t == 0) && B[j]){
                 cout<<A[j];
                 B[j] = false;
             }
             else{
                 cout<<"  ";
             }
         }
         cout<<endl;
    }
    cout<<endl;
    delete [] A;
    delete [] B;
    
}

//Adapted from Lab 9 to Display Tree Properly
void LinkedBinaryTree::printTreeHelper(Elem *X, bool *Y,Node *ptr, int n){
    if(ptr!=NULL){
        int mid = (n-1)/2;
        X[mid] = ptr->elt;
        Y[mid] = true;
        printTreeHelper(X,Y,ptr->left,mid);
        printTreeHelper(X+(mid+1), Y+(mid+1), ptr->right, mid);
    }
}

bool LinkedBinaryTree::equal(LinkedBinaryTree& TreeB)
{
    LinkedBinaryTree::Position RootTreeA = this->root(); //Gets the position of root of the first tree
    LinkedBinaryTree::Position RootTreeB = TreeB.root(); //Gets the position of root of the second tree
    if(*RootTreeA == *RootTreeB) //Compares the element at both roots
    {
        //COMPARE PREORDER TRAVERSAL
        PositionList pTreeA;
        this->preorder(this->_root,pTreeA); //Gets the 'preorder' list for the first tree
        PositionList pTreeB;
        TreeB.preorder(TreeB._root,pTreeB); //Gets the 'preorder' list for the second tree
        std::list<Position>::iterator it1;
        
        if(pTreeA.size()!=pTreeB.size()) return 0; //Compares the size of both lists
//        cout<<p1a.size()<<endl;
//        cout<<p1b.size()<<endl;
//        cout<<"Size Equal"<<endl;
        for(it1 = pTreeB.begin() ; it1 != pTreeB.end() ; it1++) //Loop through the entire list
        {
            if (*pTreeA.front() != *pTreeB.front()) return 0; //Displays the element at the front of the list
            pTreeA.pop_front(); //Pops the element to allow the next element to be compared
            pTreeB.pop_front(); //Pops the element to allow the next element to be compared
        }
        pTreeA.clear(); //Clears all elements from the list as a precaution
        pTreeB.clear(); //Clears all elements from the list as a precaution

        //COMPARE POSTORDER TRAVERSAL
        this->postorder(this->_root,pTreeA); //Gets the 'postorder' list for the first tree
        TreeB.postorder(TreeB._root,pTreeB); //Gets the 'postorder' list for the second tree

        if(pTreeA.size()!=pTreeB.size()) return 0; //Compares the size of both lists

        for(it1 = pTreeB.begin() ; it1 != pTreeB.end() ; it1++) //Loop through the entire list
        {
            if (*pTreeA.front() != *pTreeB.front()) return 0; //Displays the element at the front of the list
            pTreeA.pop_front(); //Pops the element to allow the next element to be compared
            pTreeB.pop_front(); //Pops the element to allow the next element to be compared
        }
        pTreeA.clear(); //Clears all elements from the list as a precaution
        pTreeB.clear(); //Clears all elements from the list as a precaution
        
        //COMPARE INORDER TRAVERSAL
        this->inorder(this->_root,pTreeA); //Gets the 'inorder' list for the first tree
        TreeB.inorder(TreeB._root,pTreeB); //Gets the 'inorder' list for the second tree
        
        if(pTreeA.size()!=pTreeB.size()) return 0; //Compares the size of both lists
//        cout<<p1a.size()<<endl;
//        cout<<p1b.size()<<endl;
//        cout<<"Size Equal"<<endl;
        for (it1 = pTreeB.begin() ; it1 != pTreeB.end() ; it1++) //Loop through the entire list
        {
            if (*pTreeA.front() != *pTreeB.front()) return 0; //Displays the element at the front of the list
            pTreeA.pop_front(); //Pops the element to allow the next element to be compared
            pTreeB.pop_front(); //Pops the element to allow the next element to be compared
        }
        pTreeA.clear(); //Clears all elements from the list as a precaution
        pTreeB.clear(); //Clears all elements from the list as a precaution
        
        return 1; //If all elements in all orders are exactly the same, then the function returns 1 (True)
    }

    return 0; //If root elements are not equal, it returns 0
}



LinkedBinaryTree LinkedBinaryTree::generalTree2BinaryTree(GeneralTree TreeB)
{
    LinkedBinaryTree* NewTreeA = new LinkedBinaryTree;
    GeneralTree::GTNode* Root = new GeneralTree::GTNode();
    Root = TreeB.getRoot();
    Elem AtRoot = Root->getElt();
//    cout<<"AtRoot "<<AtRoot<<endl;
    NewTreeA->addRoot(AtRoot);
//    cout<<"NEWTREE ROOT "<<*NewTreeA->root()<<endl;
    GeneralTree::Position pr = TreeB.root();
    Position PosX = NewTreeA->root();
    NewTreeA->expandExternal(PosX, pr.firstChild()->getElt());

//    newTree->displayTree();
//    cout<<"CALL TO FUNCTION"<<endl;
    Position CurrentPos = PosX.left(); //Position 'B'
//    cout<<"POS "<<*pos<<endl;
//    cout<<endl;
    generalTree2BinaryTreeHelper(*NewTreeA, Root, CurrentPos);
    //passing r = root AND pos = B
    return *NewTreeA;

}

void LinkedBinaryTree::generalTree2BinaryTreeHelper(LinkedBinaryTree& NewTreeB, GeneralTree::GTNode* Xnode, Position PosX)
{
    std::list<GeneralTree::GTNode*>* ChildrenList = Xnode->getChildren();
//    if(ch!=NULL)
//    {
//        list<GeneralTree::GTNode*>::iterator it = ch->begin();
//        while(it!=ch->end())
//        {
//            cout<<(*it)->getElt();
//            ++it;
//        }
//        cout<<" XX "<<endl;
//    }
    if(ChildrenList!=NULL) {
        list<GeneralTree::GTNode*>::iterator IterarorCL = ChildrenList->begin();
        //for(itc=ch->begin(); itc!=ch->end(); itc++)
        do
        {
//            cout<<"ITC IS "<<(*itc)->getElt()<<endl;
            //Checks if it has children and Siblings
            if((*IterarorCL)->getChildren()!=NULL && (*IterarorCL)->hasSibling()) {
                GeneralTree::Position x(*IterarorCL);
                NewTreeB.expandExternal(PosX, (*IterarorCL)->getChildren()->front()->getElt(), x.getSibling()->getElt());
//                cout<<"Test 100"<<endl;
//                cout<<(*itc)->getChildren()->front()->getElt()<<endl;
//                cout<<sib->getElt()<<endl;
//                cout<<"End Test 100 "<<endl;
//                newTree.displayTree();
                Position PosLeft = PosX.left();
                generalTree2BinaryTreeHelper(NewTreeB, (*IterarorCL), PosLeft); //1st call for Recursion happens here
                //Position posr = pos.right();
                //generalTree2BinaryTreeHelper(newTree, (*itc), posr);
//                cout<<"DoneTestDone"<<endl;
//                newTree.displayTree();
            }
            //Checks if it only has children then only adds the right child to the new tree
            else if((*IterarorCL)->getChildren()!=NULL) {
                NewTreeB.expandExternal(PosX, (*IterarorCL)->getChildren()->front()->getElt());
                Position PosLeft = PosX.left();
                generalTree2BinaryTreeHelper(NewTreeB, (*IterarorCL), PosLeft); //recursive call
            }
            //Checks if it only has siblings then adds the sibling as itd child
            else if((*IterarorCL)->hasSibling()) {
                GeneralTree::Position x(*IterarorCL);
//                cout<<"DoneTestDone 3"<<endl;
//                cout<<*pos<<endl;
                NewTreeB.expandExternal(PosX,  x.getSibling()->getElt(), 1);
//                cout<<"Test 101"<<endl;
//                cout<<sib->getElt()<<endl;
//                cout<<"End Test 101"<<endl;
//                newTree.displayTree();
                Position PosRight = PosX.right();
//                cout<<"Test 102"<<endl;
//                cout<<(*itc)->getElt()<<endl;
//                cout<<*posr<<endl;
//                cout<<"End Test 102"<<endl;
                generalTree2BinaryTreeHelper(NewTreeB, (*IterarorCL), PosRight); //2nd Call for Recursion with E and F
//                cout<<"DoneTestDone 2"<<endl;
            }
            else {
//                cout<<"DoneTestDone 3"<<endl;
//                cout<<*pos<<endl;
//                Position PosRight = pos.right();
//                cout<<*posr<<endl;
                NewTreeB.expandExternal(PosX);
//                newTree.displayTree();
//                cout<<"DoneTestDone 4"<<endl;
            }
            PosX = PosX.right();
            IterarorCL++;
        }while(IterarorCL!=ChildrenList->end());
    }
}

//LinkedBinaryTree LinkedBinaryTree::generalTree2BinaryTree(GeneralTree T2)
//{
//    LinkedBinaryTree NewTree;
//
//    GeneralTree::GTNode* xnode = new GeneralTree::GTNode();
//    xnode = T2.getRoot();
//
//    std::list<GeneralTree::GTNode*>* CList;
//    CList = xnode->getChildren();
//    list<GeneralTree::GTNode*>::iterator it = CList->begin();
//    cout<<"HEREE"<<endl;
//
//    GeneralTree::GTNode* endchild = new GeneralTree::GTNode();
//
//    while(it!=CList->end())
//    {
//        cout<<(*it)->getElt()<<endl;
//        if((*it)==CList->back())
//        {
//            cout<<"MILGAYA"<<(*it)->getElt()<<endl;
//
//        }
//        ++it;
//    }
//    endchild = CList->back();
//    cout<<"endchild 1 "<<endchild->getElt()<<endl;
//
//    while(endchild->getChildren()->size()!=1)
//    {
//        CList = endchild->getChildren();
//        endchild = CList->back();
//    }
//    cout<<"endchild 2 "<<endchild->getElt()<<endl;
//
//    list<GeneralTree::GTNode*>::iterator pp;
//    pp = endchild->getNparent()->getChildren()->end();
//
//    while(pp!=endchild->getNparent()->getChildren()->begin())
//    {
//        GeneralTree::GTNode* temp = new GeneralTree::GTNode();
//        temp = *pp;
//        pp--;
//        temp -> setNparent(*pp);
//    }
//
//    return NewTree;
//}
