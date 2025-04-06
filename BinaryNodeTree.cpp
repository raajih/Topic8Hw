#include "BinaryNodeTree.h"

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(): rootPtr(nullptr) {}

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem);
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::moveValuesUpTree(BinaryNode<ItemType>* subTreePtr)
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
		subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), largestInLeftSubtree->getItem(), success));
		success = true;  // Node was successfully replaced
	}

	return subTreePtr; //SOOOO much trouble with this method.
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findLargestNode(BinaryNode<ItemType>* subTreePtr) const
{
	// Traverse to the rightmost leaf in the left subtree 
	while (subTreePtr->getRightChildPtr() != nullptr) 
	{
		subTreePtr = subTreePtr->getRightChildPtr();
	}
	return subTreePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::findNode(BinaryNode<ItemType>* treePtr, const ItemType& target, bool& success) const
{
	//Base case: value is not found
	if (treePtr == nullptr)
	{
		success = false;
		return treePtr;
	}
	//Base case: value is found
	else if (treePtr->getItem() == target)
	{
		success = true;
		return treePtr;
	}
	
	BinaryNode<ItemType>* leftResult = findNode(treePtr->getLeftChildPtr(), target, success);
	if (success)
		return leftResult;

	return findNode(treePtr->getRightChildPtr(), target, success);
}

template<class ItemType>
inline BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
	BinaryNode<ItemType>* newTreePtr = nullptr;

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
void BinaryNodeTree<ItemType>::preorder(void visit(ItemType), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		visit(treePtr->getItem());
		preorder(visit, treePtr->getLeftChildPtr());
		preorder(visit, treePtr->getRightChildPtr());
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		inorder(visit, treePtr->getLeftChildPtr());
		visit(treePtr->getItem());
		inorder(visit, treePtr->getRightChildPtr());
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::postorder(void visit(ItemType), BinaryNode<ItemType>* treePtr) const
{
	if (treePtr != nullptr)
	{
		postorder(visit, treePtr->getLeftChildPtr());
		postorder(visit, treePtr->getRightChildPtr());
		visit(treePtr->getItem());

	}
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
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target, bool& success)
{
	if (subTreePtr == nullptr)
	{
		success = false;  // Nothing to remove
		return nullptr;
	}

	if (target < subTreePtr->getItem())
	{
		subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), target, success));
	}

	else if (target > subTreePtr->getItem())
	{
		subTreePtr->setRightChildPtr(removeValue(subTreePtr->getRightChildPtr(), target, success));
	}
	
	else
	{
		success = true;
		subTreePtr = moveValuesUpTree(subTreePtr);  
	}

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
ItemType BinaryNodeTree<ItemType>::getRootData() const throw(PrecondViolatedExcep)
{
	if (rootPtr == nullptr)
		throw PrecondViolatedExcep("Tree is empty");
	else
		return rootPtr->getItem();
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData)
{
	if (rootPtr != nullptr)
		rootPtr->setItem(newData);
	else
		rootPtr = new BinaryNode<ItemType>(newData);
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

template<class ItemType>
bool BinaryNodeTree<ItemType>::remove(const ItemType& data)
{
	if (contains(data))
	{
		bool success = false;
		rootPtr = removeValue(rootPtr, data, success);  // Update rootPtr after removal
		return true;
	}
	else
		return false;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::clear()
{
	destroyTree(rootPtr);
	rootPtr = nullptr;
}

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const throw(NotFoundException)
{
	bool success = false;
	BinaryNode<ItemType>* node = findNode(rootPtr, anEntry, success);

	// If the node was found, return the item
	if (success && node != nullptr)
	{
		return node->getItem();
	}
	else
	{
		throw NotFoundException("Entry not found in the tree");
	}
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
{
	bool success = false;
	return findNode(rootPtr, anEntry, success) != nullptr;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType)) const
{
	preorder(visit, rootPtr);
}
template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType)) const
{
	inorder(visit, rootPtr);
}
template<class ItemType>
void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType)) const
{
	postorder(visit, rootPtr);
}

template<class ItemType>
BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator=(const BinaryNodeTree<ItemType>& rightHandSide)
{
	if (this != &rightHandSide)  // Avoid self-assignment
	{
		// Clear the current tree
		clear();

		// Copy the tree from the right-hand side using copyTree
		rootPtr = copyTree(rightHandSide.rootPtr);
	}
	return *this;
}
//TODO: For the removal in a binary search tree, if the node has two child nodes that is the complicated one. Look at powerpoint for instructions on how to do that. Find another node easier to remove...