#include "splaytree.h"

#include <cassert>
#include <iostream>
using std::cout;
using std::endl;

SplayTree::SplayTree() {
	root = nullptr;
	num_elements = 0;
}

SplayTree::~SplayTree() {
	destroyNode(root);	
}

void SplayTree::destroyNode(Node* n) {
    if (n == nullptr) return;
	if (n->get_left() != nullptr) {
		destroyNode(n->get_left());
	}
	if (n->get_right() != nullptr) {
		destroyNode(n->get_right());
	}
	delete n;
}

void SplayTree::insert(string k, unsigned int r) {
	assert(r > 0 && r <= num_elements + 1);

	num_elements++;
	root = insertNode(root, k, r);
	root = splay(findNode(root, r));
}

string SplayTree::select(unsigned int r) {
	assert(r > 0 && r <= num_elements);	

	root = splay(findNode(root,r));
	return root->get_key();
}

void SplayTree::modify(unsigned int r, string k) {
	assert(r > 0 && r <= num_elements);

	root = splay(findNode(root, r));
	root->set_key(k);
}

void SplayTree::split(unsigned int r, SplayTree* R) {
	assert(R != nullptr);					// R should be allocated by the user.
	assert(R->root == nullptr);				// The pointer to the right subtree should be nullptr.
	assert(r >= 0 && r <= num_elements);
	
	int size = 0;
	if (r == 0) {
		R->set_root(root);
		R->set_num_elements(num_elements);
		root = nullptr;
		num_elements = 0;		
	}
	else {
		root = splay(findNode(root,r));
		R->set_root(root->get_right());
		if (R->get_root() != nullptr) {
			R->get_root()->set_parent(nullptr);
			R->set_num_elements(R->get_root()->get_size());
			size = R->get_num_elements();
			R->get_root()->update_size();
		}
		if (root->get_right() != nullptr) num_elements = num_elements - size;
		root->set_right(nullptr);
		root->update_size();
	}
}

void SplayTree::join(SplayTree* R) {
	assert(R != nullptr);					// R should be allocated by the user.

	if (root == nullptr) {
		root = R->get_root();
		num_elements = R->get_num_elements();
		R->set_root(nullptr);
		R->set_num_elements(0);
		
	}
	else {
		root = splay(findNode(root,num_elements));
		root->set_right(R->get_root());
		if ( R->get_root() != nullptr ) 
			R->get_root()->set_parent(root);
		num_elements = num_elements + R->get_root()->get_size();
		root->update_size();	
		R->set_root(nullptr);
		R->set_num_elements(0);
	}
}

void SplayTree::print() {
	printNodes(root);
	cout << "\n";
}

unsigned int SplayTree::size() {
	return num_elements;
}

Node* SplayTree::findNode(Node * t, unsigned int r) {
	unsigned int leftSize = 1;	
 	if (t->get_left() != nullptr) {
		leftSize = t->get_left()->get_size() + 1;
	}
   	
	if (leftSize == r) return t; 
	else if (r < leftSize) {
		return findNode(t->get_left(), r);
	}
	else if (t->get_right() != nullptr) {
		return findNode(t->get_right(), r - leftSize  );
	}
	return t;
}

Node* SplayTree::insertNode(Node* t, string k, unsigned int r) {
   	if (t == nullptr) {
		Node* n = new Node(k); 
		return n;
	}
    if (r < t->get_size()) {
		Node* n = insertNode(t->get_left(),k,r);
		n->set_parent(t);
	    t->set_left(n);
    }
	else {
		Node* n = insertNode(t->get_right(), k,r);
		n->set_parent(t);
       	t->set_right(n);
    }
    return t;
}

Node* SplayTree::splay(Node* z) {
	while (z->get_parent() != nullptr) {
		Node* p = z->get_parent();
		// If parent and grandparent are not null
		if (p->get_parent() != nullptr) {
			// Pass node, parent, grandparent, and great grandparent
			z = splayPGP(z,p,p->get_parent(),p->get_parent()->get_parent());	
		}
		else { // If grand parent null, meaning last rotation
			if (p->get_right() == z) { // If Right
				z->set_parent(nullptr);
				Node* b = z->get_left();
				rotateLR(z,p,b);
			
			}
			else { // If Left
				z->set_parent(nullptr);
				Node* b = z->get_right();
				rotateRL(z,p,b);
			}
			p->update_size();
			z->update_size();		
		}
	
	}
	
	return z; 
}

Node* SplayTree::splayPGP(Node* z, Node* p, Node* gp, Node* ggp) {
	// Splay to where grand parent was
	z = inLineSplay(z,p,gp,ggp);
	z = outOfLineSplay(z,p,gp,ggp);
	
	// Set great grandparent
    z->set_parent(ggp);
    if (ggp != nullptr && ggp->get_left() == gp) ggp->set_left(z);
    if (ggp != nullptr && ggp->get_right() == gp) ggp->set_right(z);
	
    gp->update_size();
    p->update_size();
    z->update_size();
	return z;
}

Node* SplayTree::inLineSplay(Node* z, Node* p, Node* gp, Node* ggp){
    if (gp->get_left() == p && p->get_left() == z) { 
        Node* c = p->get_right();
        rotateRL(p,gp,c);
        Node* b = z->get_right();
        rotateRL(z,p,b);
    }
    else if (gp->get_right() == p && p->get_right() == z) {
        Node* b = p->get_left();
        rotateLR(p,gp,b);
        Node* c = z->get_left();
    	rotateLR(z,p,c);
    }
	return z;
}

Node* SplayTree::outOfLineSplay(Node* z, Node* p, Node* gp, Node* ggp) {
	if (p->get_left() == z) { 
        setRightChild(gp,z);
        Node* b = z->get_right();
        rotateRL(z,p,b);
        Node * c = z->get_left();
        setRightChild(gp,c);
        setLeftChild(z,gp);
    }
	else if (p->get_right() == z) {
        setLeftChild(gp,z);
        Node* b = z->get_left();
        rotateLR(z,p,b);
        Node* c = z->get_right();
        setLeftChild(gp,c);
    	setRightChild(z,gp);
	}
	return z;
}

void SplayTree::rotateRL(Node* a, Node* b, Node* c) {
	setRightChild(a,b);
	setLeftChild(b,c);
}

void SplayTree::rotateLR(Node* a, Node* b, Node* c) {
	setLeftChild(a,b);
    setRightChild(b,c);
}

void SplayTree::setLeftChild(Node* parent, Node* child) {
	parent->set_left(child);
	if ( child != nullptr ) child->set_parent(parent);
}

void SplayTree::setRightChild(Node* parent, Node* child) {
	parent->set_right(child);
	if ( child != nullptr ) child->set_parent(parent);
}

void SplayTree::printNodes(Node* r) {
	if (r == nullptr) return;
	
	printNodes(r->get_left());
	
	if (r->get_key().compare("\n")) {
		cout << r->get_key() << " ";
	}
	else cout << r->get_key();
	
	printNodes(r->get_right());
}

void SplayTree::set_root(Node* r) {
	root = r;
}

void SplayTree::set_num_elements(unsigned int n) {
	num_elements = n;
}

Node* SplayTree::get_root() {
	return root;
}

unsigned int SplayTree::get_num_elements() {
	return num_elements;
}
