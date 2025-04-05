#include <iostream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
using namespace std;

int main()
{
	BinaryNodeTree<int> tree;

	cout << tree.getHeight() << endl;
	tree.add(5);
	cout << tree.getHeight() << endl;
	tree.add(7);
	cout << tree.getHeight() << endl;
	tree.add(1);
	cout << tree.getHeight() << endl;
	tree.add(2);
	cout << tree.getHeight() << endl;

	
	
	return 0;
}