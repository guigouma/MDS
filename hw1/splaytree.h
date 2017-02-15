#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include "node.h"

/*
This represents a SplayTree that encodes a dynamic sequence.
*/
class SplayTree {
	Node* root;										// The root node of the Splay Tree.
	unsigned int num_elements;						// The number of elements stored in the tree.
	
	public:
	SplayTree();									// Constructs a Splay Tree. Initializes the root to nullptr and num_elements to 0.
	~SplayTree();									// De-allocates all the nodes in the Tree.
	
	void insert(string k, unsigned int r);			// inserts string k at position r.
	string select(unsigned int r);					// Selects the element at position r (splays it to the root).
	void modify(unsigned int r, string k);			// Modifies the element at position r to string k.
	void split(unsigned int r, SplayTree* R);		// Splits the tree at position r. The left side of the split is stored in the calling object. The right side of the split is stored in R.
	void join(SplayTree*);							// Concatenates the sequences stored in the current tree (calling object) with R.
	
	void print();									// Prints the sequence by doing an inorder traversal of the tree.
	unsigned int size();							// Returns the number of elements currently stored in the tree.
	
	// Private recursive functions to implement the above.
//	private:
	// Fill in your own private methods, and other private data that suits your implementation.
	// TBD...
   	Node* insertNode(Node* t, string k,unsigned int r, Node* p);
   	void printNodes(Node* t);	
	void prettyPrintNodes(Node * t);
	Node* splay(Node* t);
	Node* find(unsigned int r);
	Node* findNode(Node * t,unsigned int r);
	void setLeftChild(Node* p, Node* c);
	void setRightChild(Node* p, Node* c);
	void rotateRL(Node* a, Node* b, Node* c);
    void rotateLR(Node* a, Node* b, Node* c);	
	void set_root(Node* r);
	void set_num_elements(unsigned int n);

	Node* splayPGP(Node* z, Node* p, Node* gp, Node* ggp);
	Node* inLineSplay(Node* z, Node* p, Node* gp, Node* ggp);
	Node* outOfLineSplay(Node* z, Node* p, Node* gp, Node* ggp);
	Node* get_root();
	unsigned int get_num_elements();
	void destroyNode(Node* n);
};

#endif
