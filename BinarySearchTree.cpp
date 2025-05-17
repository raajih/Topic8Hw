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
	

	if (subTreePtr == nullptr)
	{
		
		return nullptr;
	}

	//Case 3: Node with two children
	if (subTreePtr->getLeftChildPtr() != nullptr && subTreePtr->getRightChildPtr() != nullptr)
	{
		BinaryNode<ItemType>* largestInLeftSubtree = findLargestNode(subTreePtr->getLeftChildPtr());
		subTreePtr->setItem(largestInLeftSubtree->getItem());
		subTreePtr->setLeftChildPtr(removeValue(subTreePtr->getLeftChildPtr(), largestInLeftSubtree->getItem()));
	}
	//Case 1: Leaf node (no children)
	else if (subTreePtr->isLeaf())
	{
		delete subTreePtr;
		return nullptr;
	}
	//Case 2: Node with one child
	else
	{
		BinaryNode<ItemType>* childPtr = nullptr;

		//If the node has a left child, replace it with the left child.
		if (subTreePtr->getLeftChildPtr() != nullptr)
		{
			childPtr = subTreePtr->getLeftChildPtr();
		}
		//Otherwise, it has only a right child.
		else if (subTreePtr->getRightChildPtr() != nullptr)
		{
			childPtr = subTreePtr->getRightChildPtr();
		}

		//Move up the child and delete the current node
		if (childPtr != nullptr)
		{
			BinaryNode<ItemType>* temp = subTreePtr;
			subTreePtr = childPtr;
			temp->setLeftChildPtr(nullptr);
			temp->setRightChildPtr(nullptr);
			delete temp;
		}
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

// Helper function to recursively check if two trees are the same.
template<class ItemType>
bool BinarySearchTree<ItemType>::isSameTreeStructureHelper(BinaryNode<ItemType>* node1, BinaryNode<ItemType>* node2) const
{
	if (node1 == nullptr && node2 == nullptr)//Base case where both nodes are null.
		return true;

	if (node1 == nullptr || node2 == nullptr)//Base case where only one of the nodes is null. Therefore the trees are not the same.
		return false;

	return (node1->getItem() == node2->getItem()) && //Check if the data of the nodes are the same.
		isSameTreeStructureHelper(node1->getLeftChildPtr(), node2->getLeftChildPtr()) && //Check left children.
		isSameTreeStructureHelper(node1->getRightChildPtr(), node2->getRightChildPtr()); //Check right children.
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
void BinarySearchTree<ItemType>::inorderMonthQuery(void visit(ItemType, int), int month) const
{
	inorderMonthQueryHelper(visit, rootPtr, month);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isSameTreeStructure(BinarySearchTree<ItemType>& otherTree) const
{
	return isSameTreeStructureHelper(this->rootPtr, otherTree.rootPtr);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::isSameTreeContents(BinarySearchTree<ItemType>& otherTree) const
{
	vector<ItemType> tree1Values;
	vector<ItemType> tree2Values;
	bool same = true;

	collectTreeValues(this->rootPtr, tree1Values);//Collect values of this tree.
	collectTreeValues(otherTree.rootPtr, tree2Values);//Collect values of other tree.

	bubbleSort(tree1Values);//Sort the values of this tree.
	bubbleSort(tree2Values);//Sort the values of other tree.

	if (tree1Values.size() != tree2Values.size())//If the sizes of the vectors are not equal, the trees are not the same.
		same = false;

	for (int i = 0; i < tree1Values.size(); i++)//Loop through the vectors and compare the values.
	{
		if (tree1Values[i] != tree2Values[i])//If the values are not equal, the trees are not the same.
		{
			same = false;
			break;
		}
	}

	return same;
}

//Recursively go through tree and add items to vector.
template<class ItemType>
bool BinarySearchTree<ItemType>::collectTreeValues(BinaryNode<ItemType>* node, vector<ItemType>& values) const
{
	if (node == nullptr)//Base case.
		return true;

	collectTreeValues(node->getLeftChildPtr(), values);//Go through left subtree.
	values.push_back(node->getItem());//Add the current node's value to the vector.
	collectTreeValues(node->getRightChildPtr(), values);//Go through right subtree.

	return true;
}

//Use for isSameTreeContents to sort the vector of values.
template<class ItemType>
void BinarySearchTree<ItemType>::bubbleSort(vector<ItemType>& vec) const
{
	int n = vec.size();  //Get the number of elements in the vector.
	bool swapped;

	//Loop through all elements in the vector.
	for (int i = 0; i < n - 1; ++i) 
	{
		swapped = false;

		//Last i elements are already in place, so we avoid comparing them.
		for (int j = 0; j < n - 1 - i; ++j) {
			//Compare adjacent elements and swap if necessary.
			if (vec[j] > vec[j + 1]) {
				//Swap the elements.
				string temp = vec[j];
				vec[j] = vec[j + 1];
				vec[j + 1] = temp;

				swapped = true;
			}
		}

		//If no two elements were swapped, the vector is already sorted.
		if (!swapped) 
			break;
	}
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

template<class ItemType>
void BinarySearchTree<ItemType>::inorderMonthQueryHelper(void visit(ItemType, int), BinaryNode<ItemType>* treePtr, int queryMonth) const
{
	if (treePtr != nullptr)
	{
		inorderMonthQueryHelper(visit, treePtr->getLeftChildPtr(), queryMonth);
		visit(treePtr->getItem(), queryMonth);
		inorderMonthQueryHelper(visit, treePtr->getRightChildPtr(), queryMonth);
	}
}


