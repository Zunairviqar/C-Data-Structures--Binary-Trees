
#include <iostream>
#include <string>
#include "GeneralTree.hpp"
#include "LinkedBinaryTree.hpp"

using namespace std ;

void EqualNewTree(LinkedBinaryTree& bx);
void NotEqualNewTree(LinkedBinaryTree& by);
void TestSibling(GeneralTree& gt);

int main(int argc, const char * argv[])
{
    // ----------------------------------
    // Create GeneralTree
    //-----------------------------------
    GeneralTree gt ;
    gt.addRoot("A") ;
    GeneralTree::GTNode* pr= gt.getRoot() ;
    gt.addChild("B", pr) ;
    gt.addChild("C", pr) ;
    gt.addChild("D", pr) ;

    // Add grand children of the root
    list<GeneralTree::GTNode*>::iterator p = pr->getChildren()->begin() ;
    gt.addChild("E", *p) ; // added under child 1 of root
    gt.addChild("F", *p) ; // added under child 1 of root
    p++;                   // No child for child 2 of root
    p++;
    gt.addChild("G", *p) ; // added under child 3 of root

    //Get all the nodes in a list, the display the content of the list
    GeneralTree::GTNList gtn ;
    gt.postorder(gtn) ;
    cout<<"----------------------GeneralTree bt Display---------------------"<<endl;
    list<GeneralTree::GTNode*>::iterator pp = gtn.begin() ;
    while(pp!=gtn.end()) {
        cout<<(*pp)->getElt()<<endl ;
        pp++ ;
    }
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<endl ;
    
    cout<<"----------------------Start of TestSibling-----------------------"<<endl;
    TestSibling(gt);
    cout<<"----------------------End of TestSibling-------------------------"<<endl;
    cout<<endl;
    // ----------------------------------
    // Create LinkedBinaryTree
    //-----------------------------------
    LinkedBinaryTree bt;
    bt.addRoot("A");

    // Children of root
    LinkedBinaryTree::Position pA = bt.root() ;  // get root's position, so pos of A
    bt.expandExternal(pA,"B") ;                  // Add left= B" and empty right children to root

    // Children and descendents of B, the left child of root
    LinkedBinaryTree::Position pB = pA.left() ;  // get position of root's left child, so pos of B
    bt.expandExternal(pB, "E", "C") ;            // Add left="E" and right="C" children to B

    // Children and descendants of E, the left child of B
    LinkedBinaryTree::Position pE = pB.left() ;  // get position of B's left child, so pos of E
    bt.expandExternal(pE, "F", 1) ;              // Add empty left and right ="F" children to E

    LinkedBinaryTree::Position pF = pE.right() ; // get position of E's right child, so pos of F
    bt.expandExternal(pF) ;                      // Add empty left and empty right children to F

    // Children and descendents of C, the right child of B
    LinkedBinaryTree::Position pC = pB.right() ; // get position of B's rightt child, so pos of C
    bt.expandExternal(pC, "D", 1) ;              // Add empty left and right="D" children to C

    LinkedBinaryTree::Position pdd = pC.right() ; // get position of C's right child, so pos of D
    bt.expandExternal(pdd, "G") ;                 // Add left="G" and empty right children to D

    LinkedBinaryTree::Position pgg = pdd.left() ; // get position of D's left child, so pos of G
    bt.expandExternal(pgg) ;                      // Add empty left and empty right children to G

    // display with preorder traversale
    cout<<"----------------------LinkedBinaryTree bt Display----------------"<<endl;
    bt.displayTree() ;
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<endl;
    
    LinkedBinaryTree bx;
    EqualNewTree(bx); //Function fills the Tree bx equal to bt

    LinkedBinaryTree by;
    NotEqualNewTree(by); //Function fills the Tree by not equal to bt
    
    cout<<"----------------------Test LinkedBinary Tree bx Display----------"<<endl;
    bx.displayTree();
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"----------------------Test LinkedBinary Tree by Display----------"<<endl;
    by.displayTree();
    cout<<"-----------------------------------------------------------------"<<endl;
    cout<<endl;
    
    cout<<"----------------------Start of Test of Equal Function------------"<<endl;
    if(bt.equal(bx)==1) {cout<<"bt is equal to bx"<<endl;}
    else { cout<<"bt is not equal to bx"<<endl; }
    if(bt.equal(by)==1){cout<<"bt is equal to by"<<endl;}
    else{cout<<"bt is not equal to by"<<endl;}
    cout<<"----------------------End of Test of Equal Function--------------"<<endl;
    cout<<endl;
    
    
    cout<<"-----------------Start of Test generalTree2BinaryTree()----------"<<endl;
    LinkedBinaryTree bt1;
    bt1 = bt1.generalTree2BinaryTree(gt);
    cout<<"------Newly Converted Tree bt1: ------"<<endl;
    bt1.displayTree();
    cout<<"-----------------End of Test generalTree2BinaryTree()------------"<<endl;
    cout<<endl;
    
    if(bt.equal(bt1)==1) {cout<<"bt1 is equal to bt"<<endl;}
    else { cout<<"bt1 is not equal to bt"<<endl; }
    cout<<endl;
    
    //Complex Case Tree
    GeneralTree g1 ;
    g1.addRoot("A") ;
    GeneralTree::GTNode* qr= g1.getRoot() ;
    g1.addChild("B", qr) ;
    g1.addChild("F", qr) ;
    g1.addChild("J", qr) ;

    // Add grand children of the root
    list<GeneralTree::GTNode*>::iterator q = qr->getChildren()->begin() ;
    g1.addChild("C", *q) ; // added under child 1 of root
    g1.addChild("D", *q) ; // added under child 1 of root
    g1.addChild("E", *q) ; // added under child 1 of root
    q++;
    g1.addChild("G", *q) ; // added under child 2 of root
    g1.addChild("H", *q) ; // added under child 2 of root
    q++;
    g1.addChild("K", *q) ; // added under child 3 of root
    g1.addChild("L", *q) ; // added under child 3 of root
    g1.addChild("M", *q) ; // added under child 3 of root
    g1.addChild("N", *q) ; // added under child 3 of root
    
    // Add great grand children of the root
    list<GeneralTree::GTNode*>::iterator t = (*q)->getChildren()->begin();
    t++;
    t++;
    //cout<<"AT  "<<(*t)->getElt()<<endl;
    g1.addChild("P", *t);
    g1.addChild("Q", *t);
//    cout<<(*q)->getElt()<<endl;
//    while(t!=(*q)->getChildren()->end())
//    {
//        cout<<(*t)->getElt()<<endl;
//        t++;
//    }
    
    cout<<"-----------------Complex Test of generalTree2BinaryTree()--------"<<endl;
    LinkedBinaryTree bt2;
    bt2 = bt2.generalTree2BinaryTree(g1);
    bt2.displayTree();
    cout<<"-----------------End of ComplexTest generalTree2BinaryTree()-----"<<endl;

    cout<<endl;
    return 0;
    }

//Function to replicate the Tree 'bt' for test function of being equal
void EqualNewTree(LinkedBinaryTree& bx)
{
    bx.addRoot("A");

    // Children of root
    LinkedBinaryTree::Position pA = bx.root() ;  // get root's position, so pos of A
    bx.expandExternal(pA,"B") ;                  // Add left= B" and empty right children to root

    // Children and descendents of B, the left child of root
    LinkedBinaryTree::Position pB = pA.left() ;  // get position of root's left child, so pos of B
    bx.expandExternal(pB, "E", "C") ;            // Add left="E" and right="C" children to B

    // Children and descendants of E, the left child of B
    LinkedBinaryTree::Position pE = pB.left() ;  // get position of B's left child, so pos of E
    bx.expandExternal(pE, "F", 1) ;              // Add empty left and right ="F" children to E

    LinkedBinaryTree::Position pF = pE.right() ; // get position of E's right child, so pos of F
    bx.expandExternal(pF) ;                      // Add empty left and empty right children to F

    // Children and descendents of C, the right child of B
    LinkedBinaryTree::Position pC = pB.right() ; // get position of B's rightt child, so pos of C
    bx.expandExternal(pC, "D", 1) ;              // Add empty left and right="D" children to C

    LinkedBinaryTree::Position pD = pC.right() ; // get position of C's right child, so pos of D
    bx.expandExternal(pD, "G") ;                 // Add left="G" and empty right children to D

    LinkedBinaryTree::Position pG = pD.left() ; // get position of D's left child, so pos of G
    bx.expandExternal(pG) ;

}

//Function to replicate the Tree 'bt' for test function of not being equal
void NotEqualNewTree(LinkedBinaryTree& by)
{
    by.addRoot("A");

    // Children of root
    LinkedBinaryTree::Position pA = by.root() ;  // get root's position, so pos of A
    by.expandExternal(pA,"B") ;                  // Add left= B" and empty right children to root

    // Children and descendents of B, the left child of root
    LinkedBinaryTree::Position pB = pA.left() ;  // get position of root's left child, so pos of B
    by.expandExternal(pB, "E", "C") ;            // Add left="E" and right="C" children to B

    // Children and descendants of E, the left child of B
    LinkedBinaryTree::Position pE = pB.left() ;  // get position of B's left child, so pos of E
    by.expandExternal(pE, "F", 1) ;              // Add empty left and right ="F" children to E

    LinkedBinaryTree::Position pF = pE.right() ; // get position of E's right child, so pos of F
    by.expandExternal(pF) ;                      // Add empty left and empty right children to F

    // Children and descendents of C, the right child of B
    LinkedBinaryTree::Position pC = pB.right() ; // get position of B's rightt child, so pos of C
    by.expandExternal(pC, "D", 1) ;              // Add empty left and right="D" children to C

    LinkedBinaryTree::Position pD = pC.right() ; // get position of C's right child, so pos of D
    by.expandExternal(pD, "N") ;                 // Add left="G" and empty right children to D

    LinkedBinaryTree::Position pG = pD.left() ; // get position of D's left child, so pos of G
    by.expandExternal(pG) ;

}

//Function to Test the Function getSibling()
void TestSibling(GeneralTree& gt)
{
    GeneralTree::Position pD;
    pD = gt.root(); //Positions to the root of the tree
   // cout<<*pD<<endl;
    GeneralTree::GTNode* x= new GeneralTree::GTNode;
    
    // To get sibling of B (i.e C)
    x = gt.getRoot(); //Stores the root of the tree in x
    pD = gt.GoToFirstChild(x); //Goes to the first child of the root (i.e B)
    //cout<<*pD<<endl;
    cout<<"Sibling of "<< *pD<<" is "<<pD.getSibling()->getElt()<<endl;
    //cout<<x->getElt()<<endl;
    
    // To get sibling of E (i.e F)
    pD = gt.root(); //Gets the position of the root of the tree
    x = pD.firstChild(); //Stores B in x
    //cout<<x->getElt()<<endl;
    pD = gt.GoToFirstChild(x); // Stores E in pD
    //cout<<*pD<<endl;
    cout<< "Sibling of "<<*pD<<" is "<<pD.getSibling()->getElt()<<endl;

}
