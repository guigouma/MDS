#include "splaytree.h"

#include <string>
using std::string;
using std::to_string;

#include <iostream>
using std::endl;
using std::cout;
using std::cin;

#include <cstdlib>


int main() {
	string k;
	SplayTree T;

	cout << "Inserting 1...100 ...." << endl;
	int size;
	for (size = 0; size < 100; size++) {
		k = to_string(size+1);
		T.insert(k, size+1);
	}
	T.print();
	cout << endl;

	cout << "Inserting 200 at random indices ...." << endl;
	k = "200";
	for (int i = 0; i < 10; i++) {
		int pos = (rand() % (size++)) + 1;
		T.insert(k, pos);

	}
	T.print();
	cout << endl;
	
	cout << "Inserting 300 at the beginning ...." << endl;
	k = "300";
	for (int i = 0; i < 10; i++) {
		T.insert(k, 1);
		size++;
	}
	T.print();
	cout << endl;

	cout << "Inserting 400 at the end ...." << endl;
	k = "400";
	for (int i = 0; i < 10; i++) {
		T.insert(k, ++size);

	}
	T.print();
	cout << endl;
	
	
	cout << "Printing the sequence using select ..." << endl;
	cout << "size is " << T.size() << endl;
	for (unsigned int i = 1; i <= T.size(); i++) {
		cout << T.select(i) << " ";
	}
	cout << endl << endl;

	cout << "modifying at middle (neither beginning nor end) indices to 500 ..." << endl;
	for (unsigned int i = 1; i <= 10; i++) {
		cout << "modifying index " << (i * 10) << endl;
		T.modify(i * 10, "500");
	}
	T.print();
	cout << endl;
	
	cout << "modifying index 1 and T->size() to 600 ..." << endl;
	T.modify(1, "600");
	T.modify(T.size(), "600");
	T.print();
	cout << endl;
	
	cout << "Splitting at index 50 ..." << endl;
	SplayTree* R = new SplayTree();
	T.split(50, R);
	cout << "Printing the left side of the split ..." << endl;
	T.print();
	cout << "Printing the right side (Tree R) of the split ..." << endl;
	R->print();
	cout << endl;
	
	cout << "splitting the left side at index 25 ..." << endl;
	SplayTree* S = new SplayTree();
	T.split(25, S);
	cout << "Printing the left side (Tree T) of the split ..." << endl;
	T.print();
	cout << "Printing the right side (Tree S) of the split ..." << endl;
	S->print();
	cout << endl;

	cout << "splitting Tree R at index 25 ..." << endl;
	SplayTree* P = new SplayTree();
	R->split(25, P);
	cout << "Printing the left side (still Tree R) of the split ..." << endl;
	R->print();
	cout << "Printing the right side (Tree P) of the split ..." << endl;
	P->print();
	cout << endl;

	cout << "splitting Tree R at index R->size()-1 ..." << endl;
	SplayTree* Q = new SplayTree();
	R->split(R->size()-1, Q);
	cout << "Printing the left side (still Tree R) of the split ..." << endl;
	R->print();
	cout << "Printing the right side (Tree Q) of the split ..." << endl;
	Q->print();
	cout << endl;

	cout << "splitting Tree R at index 1 ..." << endl;
	SplayTree* O = new SplayTree();
	R->split(1, O);
	cout << "Printing the left side (still Tree R) of the split ..." << endl;
	R->print();
	cout << "Printing the right side (Tree O) of the split ..." << endl;
	O->print();
	cout << endl;

	cout << "splitting Tree R at index 0 ..." << endl;
	SplayTree* Y = new SplayTree();
	R->split(0, Y);
	cout << "Printing the left side (still Tree R) of the split ..." << endl;
	R->print();
	cout << "Printing the right side (Tree Y) of the split ..." << endl;
	Y->print();
	cout << endl;

	cout << "splitting Tree R at index R->size() ..." << endl;
	SplayTree* Z = new SplayTree();
	R->split(R->size(), Z);
	cout << "Printing the left side (still Tree R) of the split ..." << endl;
	R->print();
	cout << "Printing the right side (Tree Z) of the split ..." << endl;
	Z->print();
	cout << endl;

	cout << "joining R with Z ..." << endl;
	R->join(Z);
	R->print();
	cout << endl;

	cout << "joining R with Y ..." << endl;
	R->join(Y);
	R->print();
	cout << endl;

	cout << "joining R with O ..." << endl;
	R->join(O);
	R->print();
	cout << endl;

	cout << "joining R with Q ..." << endl;
	R->join(Q);
	R->print();
	cout << endl;

	cout << "joining R with P ..." << endl;
	R->join(P);
	R->print();
	cout << endl;

	cout << "joining R with S ..." << endl;
	R->join(S);
	R->print();
	cout << endl;

	cout << "joining R with T ..." << endl;
	R->join(&T);
	R->print();
	cout << endl;

	cout << "de-allocating memory for all trees ..." << endl;
	delete Z;
	delete Y;
	delete O;
	delete Q;
	delete P;
	delete S;
	delete R;
		
	return 0;
}
