#ifndef NODE_H
#define NODE_H

#include <string>
using std::string;

/*
This class represents a single node in the binary search tree.
*/
class Node {
	string key;						// The data field. 
	Node *left;						// Pointer to the left subtree.
	Node *right;					// Pointer to the right subtree.
	unsigned int size;		        // The node is augmented with subtree sizes. This allows us to do the select operation.
	Node *parent;

	public:
	Node (string k);			    // Constructor to construct a single node. The left and right subtrees are initalized to nullptr, and the size to 1.

	// The appropriate get and set functions.
	string get_key();
	unsigned int get_size();
	Node* get_left();
	Node* get_right();
	Node* get_parent();
	void set_key(string);
	void set_left(Node* );
	void set_right(Node* );
	void set_parent(Node* );
	
	// This function updates the size of the subtree rooted at this node.
	void update_size();
};

#endif
