#include "BinarySearchTree.h"

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode)
{
	if (subTreePtr == nullptr)
	{
		subTreePtr = newNode;
		return newNode;
	}

	else
	{
		if (newNode->getItem() < subTreePtr->getItem())
			subTreePtr->setLeftChildPtr(insertInorder(subTreePtr->getLeftChildPtr(), newNode));
		else
			subTreePtr->setRightChildPtr(insertInorder(subTreePtr->getRightChildPtr(), newNode));

		return subTreePtr;
	}
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(ItemType), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		visit(treePtr->getItem());
		inorder(visit, treePtr->getRightChildPtr());
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target)
{
	if (subTreePtr == nullptr)
	{
		return nullptr;
	}

	if (target < subTreePtr->getItem())
	{
		subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target));
	}

	else if (target > subTreePtr->getItem())
	{
		subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target));
	}

	else
	{
		subTreePtr = moveValuesUpTree(subTreePtr);
	}

	return subTreePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType>* subTreePtr)
{
	bool success = false;

	if (subTreePtr == nullptr)
	{
		success = false;  // Nothing to remove
		return nullptr;
	}

	if (subTreePtr->isLeaf())  // Case 1: Leaf node
	{
		delete subTreePtr;
		success = true;  // Node was successfully removed
		return nullptr;
	}

	BinaryNode<ItemType>* childPtr = nullptr;

	// Case 2: Node with one child
	if (subTreePtr->getLeftChildPtr() != nullptr)
	{
		childPtr = subTreePtr->getLeftChildPtr();
	}
	else if (subTreePtr->getRightChildPtr() != nullptr)
	{
		childPtr = subTreePtr->getRightChildPtr();
	}

	// Move up the child and delete the current node
	if (childPtr != nullptr)
	{
		BinaryNode<ItemType>* temp = subTreePtr;
		subTreePtr = childPtr;
		temp->setLeftChildPtr(nullptr);
		temp->setRightChildPtr(nullptr);
		delete temp;
		success = true;  // Node was successfully removed
	}
	// Case 3: Node with two children
	else if (subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() != nullptr)
	{
		BinaryNode<ItemType>* largestInLeftSubtree = findLargestNode(subTreePtr->getLeftChildPtr());
		subTreePtr->setItem(largestInLeftSubtree->getItem());
		subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), largestInLeftSubtree->getItem()));
		success = true;  // Node was successfully replaced
	}

	return subTreePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findLargestNode(BinaryNode<ItemType>* subTreePtr) const
{
	// Traverse to the rightmost leaf in the left subtree 
	while (subTreePtr->getRightChildPtr() != nullptr)
	{
		subTreePtr = subTreePtr->getRightChildPtr();
	}
	return subTreePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const
{
	//Base case: value is not found
	if (treePtr == nullptr)
	{
		return treePtr;
	}
	//Base case: value is found
	else if (treePtr->getItem() == target)
	{
		return treePtr;
	}

	if (target < treePtr->getItem())
		return findNode(treePtr->getLeftChildPtr(), target);
	else
		return findNode(treePtr->getRightChildPtr(), target);
	

}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree()
{
	rootPtr = nullptr;
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem);
}

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& tree)
{
	rootPtr = BinaryNodeTree<ItemType>::copyTree(tree.rootPtr);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return rootPtr == nullptr;
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
	return BinaryNodeTree<ItemType>::getHeightHelper(rootPtr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const
{
	return BinaryNodeTree<ItemType>::getNumberOfNodesHelper(rootPtr);
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const throw(PrecondViolatedExcep)
{
	if (rootPtr == nullptr)
		throw PrecondViolatedExcep("Tree is empty");
	else
		return rootPtr->getItem();
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType& newData) const throw(PrecondViolatedExcep)
{
	if (rootPtr != nullptr)
		rootPtr->setItem(newData);
	else
		rootPtr = new BinaryNode<ItemType>(newData);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& newEntry)
{
	if (!BinaryNodeTree<ItemType>::contains(newEntry))
	{
		rootPtr = insertInorder(rootPtr, new BinaryNode<ItemType>(newEntry));
		return true;
	}

	return false;//If the tree already has newEntry
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& anEntry)
{
	if (contains(anEntry))
	{
		rootPtr = removeValue(rootPtr, anEntry);  // Update rootPtr after removal
		return true;
	}
	else
		return false;
}

template<class ItemType>
void BinarySearchTree<ItemType>::clear()
{
	BinaryNodeTree<ItemType>::destroyTree(rootPtr);
	rootPtr = nullptr;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	if (contains(anEntry))
	{
		BinaryNode<ItemType>* entryPtr = findNode(rootPtr, anEntry);
		return entryPtr->getItem();
	}
	else
		throw NotFoundException("Entry not found in the tree");
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
{
	return findNode(rootPtr, anEntry) != nullptr;
}

template<class ItemType>
void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType)) const
{
	BinaryNodeTree<ItemType>::preorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType)) const
{
	inorder(visit, rootPtr);
}

template<class ItemType>
void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType)) const
{
	BinaryNodeTree<ItemType>::postorder(visit, rootPtr);
}

template<class ItemType>
BinarySearchTree<ItemType>& BinarySearchTree<ItemType>::operator=(const BinarySearchTree<ItemType>& rightHandSide)
{
	if (this != &rightHandSide)  // Avoid self-assignment
	{
		// Clear the current tree
		clear();

		// Copy the tree from the right-hand side using copyTree
		rootPtr = BinaryNodeTree<ItemType>::copyTree(rightHandSide.rootPtr);
	}
	return *this;
}


