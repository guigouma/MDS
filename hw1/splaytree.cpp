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
	if(n->get_left() == nullptr && n->get_right() == nullptr)
	{
		delete n;
	}
	else if (n->get_left() == nullptr) {
		destroyNode(n->get_right());
		delete n;
	}
	else if (n->get_right() == nullptr) {
		destroyNode(n->get_left());
		delete n;
	}
	else {
        destroyNode(n->get_left());
        destroyNode(n->get_right());
		delete n;
	}
}

void SplayTree::insert(string k, unsigned int r) {
	assert(r > 0 && r <= num_elements + 1);

	num_elements++;
	root = insertNode(root, k, r, nullptr);
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
		if (root->get_right() != nullptr) num_elements = num_elements - size;//root->get_right()->get_size();
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
		return;
	}
	root = splay(findNode(root,num_elements));
	root->set_right(R->get_root());
	if ( R->get_root() != nullptr ) R->get_root()->set_parent(root);
	num_elements = num_elements + R->get_root()->get_size();
	root->update_size();	
	R->set_root(nullptr);
	R->set_num_elements(0);
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

Node* SplayTree::insertNode(Node* t, string k, unsigned int r, Node* p) {
   	if (t == nullptr) {
		Node* n = new Node(k); 
		n->set_parent(p);
		return n;
	}
    if (r < t->get_size()) {
	    t->set_left(insertNode(t->get_left(),k,r,t));
		t->update_size();
    }
	else {
       	t->set_right(insertNode(t->get_right(), k,r,t));
		t->update_size();
    }
    return t;
}

Node* SplayTree::splay(Node* z) {
	while (z->get_parent() != nullptr) {
		Node* p = z->get_parent();
		// If p and gp
		if (p->get_parent() != nullptr) {
			Node* gp = p->get_parent();
		 	Node* ggp = gp->get_parent();	
			
			z = splayPGP(z,p,gp,ggp);	
			/*	
			if (gp->get_left() == p && p->get_left() == z) { // If inline
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
			}*/
/*			if (p->get_left() == z) { // If not inline
				setRightChild(gp,z);
				Node* b = z->get_right();
				rotateRL(z,p,b);
				Node * c = z->get_left();
				setRightChild(gp,c);
				setLeftChild(z,gp);
			}
			else {
				setLeftChild(gp,z);
				Node* b = z->get_left();
				rotateLR(z,p,b);
				Node* c = z->get_right();
				setLeftChild(gp,c);
				setRightChild(z,gp);
			}*/
/*
			z->set_parent(ggp);
			if (ggp != nullptr && ggp->get_left() == gp) ggp->set_left(z);
            if (ggp != nullptr && ggp->get_right() == gp) ggp->set_right(z);
			gp->update_size();
            p->update_size();
			z->update_size();*/
		}
		else { // If no gp
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
	
	return z; // maybe could change so root is set here instead of on return
}

Node* SplayTree::splayPGP(Node* z, Node* p, Node* gp, Node* ggp) {
	z = inLineSplay(z,p,gp,ggp);
	z = outOfLineSplay(z,p,gp,ggp);
    z->set_parent(ggp);
    if (ggp != nullptr && ggp->get_left() == gp) ggp->set_left(z);
    if (ggp != nullptr && ggp->get_right() == gp) ggp->set_right(z);
    gp->update_size();
    p->update_size();
    z->update_size();
	return z;
}

Node* SplayTree::inLineSplay(Node* z, Node* p, Node* gp, Node* ggp){
    if (gp->get_left() == p && p->get_left() == z) { // If inline
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
	if (p->get_left() == z) { // If not inline
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
	//cout << "------" << r->get_key() << "|" << endl;
	if (r->get_key().compare("\n")) cout << r->get_key() << " ";
	else cout << r->get_key();
	printNodes(r->get_right());
}

void SplayTree::prettyPrintNodes(Node* r) {
	if (r == nullptr) return; 
	prettyPrintNodes(r->get_left());
	if (r->get_parent() == nullptr) 
 	 	cout << "(K:" <<  r->get_key() << " S:" << r->get_size() << " P=" << r->get_parent() << ")";
	else
		cout << "(K:" <<  r->get_key() << " S:" << r->get_size() << " P=" << r->get_parent()->get_key() << ")";
    	prettyPrintNodes(r->get_right());
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
