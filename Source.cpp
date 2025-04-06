#include <iostream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
using namespace std;

int main()
{
	BinaryNodeTree<int> tree;
	cout << (tree.isEmpty() ? "Tree is empty" : "Tree is not empty") << endl;
	tree.add(5);
	tree.add(7);
	tree.add(1);
	tree.add(2);
	
	cout << tree.getRootData() << endl;
	tree.remove(5);
	cout << tree.getRootData() << endl;

	
	return 0;
}