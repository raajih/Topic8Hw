#include "BinaryNodeTree.h"

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(): rootPtr(nullptr) {}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem);
}

template<class ItemType>
inline BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
	BinaryNode<ItemType>* newTreePtr;

	if (treePtr != nullptr)
	{
		//Preorder traversal to preserve structure of old tree
		newTreePtr = new BinaryNode<ItemType>(treePtr->getItem());
		newTreePtr->setLeftChildPtr(copyTree(treePtr->getLeftChildPtr()));
		newTreePtr->setRightChildPtr(copyTree(treePtr->getRightChildPtr()));
	}
	return newTreePtr;
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem, const BinaryNodeTree<ItemType>* leftTreePtr, const BinaryNodeTree<ItemType>* rightTreePtr)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr));
}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& tree)
{
	rootPtr = copyTree(tree.rootPtr);
}

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
}

template<class ItemType>
inline int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr) //Base case
		return 0;
	else
	{	
		return 1 + max(
			getHeightHelper(subTreePtr->getLeftChildPtr()),
			getHeightHelper(subTreePtr->getRightChildPtr())
		);
	}
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr) //Base case
		return 0;

	else
	{
		int leftNumNodes = getNumberOfNodesHelper(subTreePtr->getLeftChildPtr());
		int rightNumNodes = getNumberOfNodesHelper(subTreePtr->getRightChildPtr());

		return leftNumNodes + rightNumNodes + 1;
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
	if (subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->getLeftChildPtr());
		destroyTree(subTreePtr->getRightChildPtr());
		delete subTreePtr;
	}
}

//TODO: don't forget for the add method to account for the case that the tree is empty and rootptr == nullptr
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
{
	//Base case
	if (subTreePtr == nullptr)
		return newNodePtr;

	int leftHeight = (subTreePtr->getLeftChildPtr() != nullptr) ? getHeightHelper(subTreePtr->getLeftChildPtr()) : 0;
	int rightHeight = (subTreePtr->getRightChildPtr() != nullptr) ? getHeightHelper(subTreePtr->getRightChildPtr()) : 0;

	//If the left subtree has a smaller height or is the same height as right subtree, add node to left subtree. Otherwise add to right
	if (leftHeight <= rightHeight) 
		subTreePtr->setLeftChildPtr(balancedAdd(subTreePtr->getLeftChildPtr(), newNodePtr));
	else 
		subTreePtr->setRightChildPtr(balancedAdd(subTreePtr->getRightChildPtr(), newNodePtr));

	return subTreePtr;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getNumberOfNodes() const
{
	return getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNode = new BinaryNode<ItemType>(newData);

	if (rootPtr == nullptr)
		rootPtr = newNode;
	else
		balancedAdd(rootPtr, newNode);

	return true;
}
//TODO: For the removal in a binary search tree, if the node has two child nodes that is the complicated one. Look at powerpoint for instructions on how to do that. Find another node easier to remove...