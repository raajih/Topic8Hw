#include <iostream>
#include "BinaryNode.h"
using namespace std;

int main()
{
	BinaryNode<float> bn;
	bn.setItem(3.14159f);
	cout << bn.getItem() << endl;
	cout << bn.isLeaf() << endl;
	
	
	return 0;
}