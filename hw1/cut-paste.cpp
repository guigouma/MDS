
#include <iostream>
using std::endl;
using std::cout;
using std::cin;

#include <string>
using std::string;

#include <sstream>

#include "splaytree.h"

/*
  This function does a cut-paste operation on the sequence represented by T.
  The cut portion is the subsequence from indices i to j (j is always >= i),
  and this subsequence is pasted at index k. The resulting sequence is stored
  in T.
*/
void cut_paste(SplayTree *T, int i, int j, int k) {
	// TBD:
	SplayTree* a = new SplayTree();
	SplayTree* b = new SplayTree();
	SplayTree* c = new SplayTree();
	if (i > 0) i = i-1;
	T->split(i,a);
	
	a->split(j-i,b);
	if (k < i) T->split(k,c);
	
	else if (k > i) b->split(k-j,c);
	

	if (k < i) {
		T->join(a);
		T->join(c);
		T->join(b);
	}

	else if (k > i) {
		T->join(b);
		T->join(a);
		T->join(c);	
	}
	else
	{
		T->join(a);
		T->join(b);
        
	}
    delete a;
    delete b;
    delete c;
}

int main() {
	
	string line;
	string word;
	SplayTree *T = new SplayTree();
	int num_words = 1;
	string newline = "\n";
	
	int n;			// Number of lines.
	cin >> n;
	getline(cin, line);
	
	for (int i = 0; i < n; i++) {
		
		getline(cin, line);
		std::istringstream iss(line);
		
		// while there are words in the line...
		while (iss >> word) {
			T->insert(word, num_words++);
		}
		T->insert("\n", num_words++);
		iss.clear();
	}

	int m;			// Number of queries.
	int i, j, k;	// Variables to hold each query.
	
	cin >> m;
	for (int x = 0; x < m; x++) {
		cin >> i >> j >> k;		
		cut_paste(T, i, j, k);
	}
	T->print();
	delete T;
	return 0;
}
