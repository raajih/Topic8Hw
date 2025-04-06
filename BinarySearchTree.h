/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
	private:
	BinaryNode<ItemType>* rootPtr;

	protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNode);
	void inorder(void visit(ItemType), BinaryNode<ItemType>* treePtr) const;
	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType target);
	BinaryNode<ItemType>* moveValuesUpTree(BinaryNode<ItemType>* subTreePtr);
	BinaryNode<ItemType>* findLargestNode(BinaryNode<ItemType>* subTreePtr) const;
	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType& target) const;
	bool isSameTreeHelper(BinaryNode<ItemType>* tree1, BinaryNode<ItemType>* tree2) const;

	public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& tree);
	//virtual ~BinarySearchTree();
	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const throw(PrecondViolatedExcep);
	void setRootData(const ItemType& newData) const throw(PrecondViolatedExcep);
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const throw(NotFoundException);
	bool contains(const ItemType& anEntry) const;
	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType)) const;
	void inorderTraverse(void visit(ItemType)) const;
	void postorderTraverse(void visit(ItemType)) const;
	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	BinarySearchTree<ItemType>& operator=(const BinarySearchTree<ItemType>& rightHandSide);
	
}; 
//Other


// end BinarySearchTree
#include "BinarySearchTree.cpp"
#endif


