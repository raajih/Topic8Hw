#include <iostream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
using namespace std;

void printItem(int item)
{
	cout << item << " ";
}

int main()
{
	BinaryNodeTree<int> tree;
	cout << (tree.isEmpty() ? "Tree is empty" : "Tree is not empty") << endl;
	tree.add(5);
	tree.add(7);
	tree.add(1);
	tree.add(2);
	
	BinaryNodeTree<int> newTree;

	newTree = tree;
	tree.clear();

	newTree.inorderTraverse(printItem);

	
	return 0;
}