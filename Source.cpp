//Raajih Roland
//Final Project
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "BinarySearchTree.h"
using namespace std;

int main()
{
	BinarySearchTree<string> tree1;
	BinarySearchTree<string> tree2;

	tree1.add("abc");
	tree1.add("def");
	tree1.add("ghi");

	tree2.add("def");
	tree2.add("abc");
	tree2.add("ghi");

	cout << (tree1.isSameTreeStructure(tree2) ? "The trees structure and contents are the same." : "The trees structure and contents are not the same.") << endl;
	cout << (tree1.isSameTreeContents(tree2) ? "The trees contents are the same." : "The trees contents are not the same.") << endl;

	tree1.clear();
	tree2.clear();

	tree1.add("abc");
	tree1.add("ghi");
	tree2.add("abc");
	tree2.add("def");
	tree2.add("ghi");

	cout << endl << (tree1.isSameTreeStructure(tree2) ? "The trees structure and contents are the same." : "The trees structure and contents are not the same.") << endl;
	cout << (tree1.isSameTreeContents(tree2) ? "The trees contents are the same." : "The trees contents are not the same.") << endl;

	return 0;
}