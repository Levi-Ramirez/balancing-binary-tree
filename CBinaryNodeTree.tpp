// ============================================================================
// File: CBinaryNodeTree.tpp
// ============================================================================
// This is the implementation file for CBinaryNodeTree class which impliments a
// binary tree
// ============================================================================

#include <iostream>
using namespace std;

#include "CBinaryNodeTree.h"



// ==== Default Constructor ===================================================
//
// Sets m_rootPtr to nullptr
//
// Input:
//		nothing
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree()
{
	m_rootPtr = nullptr;
}



// ==== Type Constructor ======================================================
//
// Allocates space for a CBinaryNode and sets it equal to m_rootPtr.  The
// allocated node initializes the item and sets nullptr to its left and right
// childs. 
//
// Input:
//		rootItem	[IN] - a const ItemType reference
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree(const ItemType &rootItem)
{
	m_rootPtr = new CBinaryNode<ItemType>;

	m_rootPtr->SetItem(rootItem);
}



// ==== Type Constructor ======================================================
//
// Allocates space for a CBinaryNode and sets it equal to m_rootPtr. The
// allocated node initializes the item and sets the left and right child
// pointers appropriately.
//
// Input:
//		rootItem	[IN] - a const ItemType reference
//		leftTreePtr [IN] - a ?const? pointer to a CBinaryNodeTree<ItemType>
//		rightTreePtr [IN] - a ?const? pointer to a CBinaryNodeTree<ItemType>
//
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree(const ItemType &rootItem,
                   const CBinaryNodeTree<ItemType> *leftTreePtr,
                   const CBinaryNodeTree<ItemType> *rightTreePtr)
{
	Clear();
	m_rootPtr = new CBinaryNode<ItemType>;
	m_rootPtr->SetItem(rootItem);

	m_rootPtr->SetLeftChildPtr(CopyTree(leftTreePtr->m_rootPtr));

	m_rootPtr->SetRightChildPtr(CopyTree(rightTreePtr->m_rootPtr));
}



// ==== Copy Constructor ======================================================
//
// It copies the tree that was given as an argument. Uses a deep copy.
//
//
// Input:
//		tree	[IN] - a const BinaryNodeTree with type ItemType
//
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
CBinaryNodeTree<ItemType>::CBinaryNodeTree(const CBinaryNodeTree<ItemType> &tree)
{
	Clear();
	m_rootPtr = CopyTree(tree.m_rootPtr);
}



// ==== Destructor ============================================================
//
// Releases the memory of the tree appropriately
//
//
// Input:
//		nothing
//
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
CBinaryNodeTree<ItemType>::~CBinaryNodeTree()
{
	DestroyTree(m_rootPtr);
	m_rootPtr = nullptr;
}



// =========================================================================
//      Member Functions
// =========================================================================



// ==== IsEmpty ===============================================================
//
// Checks if m_rootPtr is nullptr
//
// Input:
//		nothing
//
// Output:
//		bool  - true if empty
//
// ============================================================================
template <class ItemType>
bool CBinaryNodeTree<ItemType>::IsEmpty() const
{
	if (m_rootPtr == nullptr)
	{
		return true;
	}

	return false;
}



// ==== GetHeight =============================================================
//
// Counts the height of the tree by calling the function GetHeightHelper.
//
// Input:
//		nothing
//
// Output:
//		int  -  value represeting the height of the tree
//
// ============================================================================
template <class ItemType>
int CBinaryNodeTree<ItemType>::GetHeight() const
{
	return GetHeightHelper(m_rootPtr);
}



// ==== GetNumberOfNodes ======================================================
//
// Counts the number of nodes the tree has by calling the function
// GetNumberOfNodesHelper.
//
// Input:
//		nothing
//
// Output:
//		int  -  value representing the number of nodes the tree has. */
//
// ============================================================================
template <class ItemType>
int CBinaryNodeTree<ItemType>::GetNumberOfNodes() const
{
	return GetNumberOfNodesHelper(m_rootPtr);
}



// ==== GetRootData ===========================================================
//
// Gets the item at root location.
//
// Input:
//		rootItem	[IN] - a const ItemType reference
//
// Output:
//		ItemType  -  An ItemType that is located at the root.
//		PrevondViolatedExcept  -  error thrown if tree is empty
//
//
// ============================================================================
template <class ItemType>
ItemType CBinaryNodeTree<ItemType>::GetRootData()
									const throw(PrecondViolatedExcept)
{
	if (m_rootPtr != nullptr)
	{
		return (m_rootPtr->GetItem());
	}
	else
	{
		PrecondViolatedExcept exception("Tree is empty");
		throw exception;
	}
}



// ==== SetRootData ===========================================================
//
// Assigns an item at root location. If the root is empty, a new
// CBinaryNode is created and item is initialzed.
//
// Input:
//		ItemType newData - An ItemType that will be assigned/initialzed at the
//                         root location.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::SetRootData(const ItemType &newData)
{
	if (m_rootPtr == nullptr)
	{
		m_rootPtr = new CBinaryNode<ItemType>;
		m_rootPtr->SetItem(newData);
	}
}



// ==== Add ===================================================================
//
// Adds a new node to the tree. Allocate the new node first and then call
// the function BalanceAdd to add the new node to the tree.
//
// Input:
//		ItemType newData	[IN] - An ItemType that will be used to initialzed
//                                 the new node.
//
// Output:
//		bool  -  True if add was successful, or false if it is not.
//
// ============================================================================
template <class ItemType>
bool CBinaryNodeTree<ItemType>::Add(const ItemType &newData)
{
	CBinaryNode<ItemType> *newNode = new CBinaryNode<ItemType>;
	newNode->SetItem(newData);
	
	m_rootPtr = BalancedAdd(m_rootPtr, newNode);

	return true;
	//When will it be false?
}



// ==== Remove ================================================================
//
// Removes a node from the tree.  This function calls the function RemoveValue.
//
// Input:
//		rootItem data	[IN] - An ItemType that will be used to find the node
//                             to delete.
//
// Output:
//		bool  -  True if remove was successful, or false if it is not.
//
// ============================================================================
template <class ItemType>
bool CBinaryNodeTree<ItemType>::Remove(const ItemType &data)
{
	//success gets updated to true if removal was successful
	bool success;
	success = false;

	//if tree is empty
	if (m_rootPtr == nullptr)
	{
		success = false;
		return success;
	}
	
	else if (!Contains(data))
	{
		success = false;
		return success;
	}

	//if m_rootPtr is the only node
	if (m_rootPtr->GetRightChildPtr() == nullptr &&
		m_rootPtr->GetLeftChildPtr() == nullptr &&
		m_rootPtr->GetItem() == data)
	{
		delete m_rootPtr;
		m_rootPtr = nullptr;
		return true;
	}

	CBinaryNode<ItemType>* nodeLocation;
	nodeLocation = FindNode(m_rootPtr, data, success);
	
	CBinaryNode<ItemType>* nodeParent;
	nodeParent = FindParent(m_rootPtr, data);
	if ((m_rootPtr->GetItem() == data)	&&
	    (m_rootPtr->GetRightChildPtr() != nullptr ||
		 m_rootPtr->GetLeftChildPtr() != nullptr))
	{
		m_rootPtr = RemoveValue(m_rootPtr, data, success);
	
		success = true;
		return success;
	}
	
	if (nodeLocation->IsLeaf())
	{
		if (nodeParent->GetRightChildPtr() != nullptr)
		{
			if (nodeParent->GetRightChildPtr()->GetItem() == data)
			{
				delete (nodeParent->GetRightChildPtr());
				nodeParent->SetRightChildPtr(nullptr);

				success = true;
				return success;
			}
		}

		if (nodeParent->GetLeftChildPtr() != nullptr)
		{	
			if (nodeParent->GetLeftChildPtr()->GetItem() == data)
			{
				delete (nodeParent->GetLeftChildPtr());
				nodeParent->SetLeftChildPtr(nullptr);

				success = true;
				return success;
			}
		}
	}
	//remove value takes care of the case where it is not a leaf,
	//it is not by itself as the root, and the tree is not empty
	else
	{
		if (nodeParent->GetRightChildPtr() != nullptr)
		{
			if (nodeParent->GetRightChildPtr()->GetItem() == data)
			{
				nodeParent->SetRightChildPtr(
					RemoveValue(nodeLocation, data, success));
				

				success = true;
				return success;
			}
		}

		if (nodeParent->GetLeftChildPtr() != nullptr)
		{	
			if (nodeParent->GetLeftChildPtr()->GetItem() == data)
			{
				nodeParent->SetLeftChildPtr(
					RemoveValue(nodeLocation, data, success));
				

				success = true;
				return success;
			}
		}
		//would I have to first find which child of the parent
		//I am updating so I can go back and update the tree??
		
		return success;
	}

	//if none of the above are true and it doesn't remove any value
	success = false;
	return success;

}



// ==== Clear =================================================================
//
// Clears all nodes of the tree.  The function calls DestroyTree.
//
// Input:
//		nothing
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::Clear()
{
	DestroyTree(m_rootPtr);
	if (m_rootPtr != nullptr)
	{
		m_rootPtr->SetLeftChildPtr(nullptr);
		m_rootPtr->SetRightChildPtr(nullptr);
		m_rootPtr = nullptr;
	}
}



// ==== GetEntry ==============================================================
//
// Retrieves an entry from the tree.  This function calls FindNode. 
//
// Input:
//		ItemType anEntry	[IN] -  An ItemType that will be used to retrieve
//                                  an item.
//
// Output:
//		ItemType  -  if the entry exhists, return an Itemtype
//		NotFoundException  -  if entry doesn't exhist throw this error
//
// ============================================================================
template <class ItemType>
ItemType CBinaryNodeTree<ItemType>::GetEntry(const ItemType &anEntry) const
                             						throw(NotFoundException)
{
	bool success;
	success = false;
	FindNode(m_rootPtr, anEntry, success);
	if (success == true)
	{
		//why do we want to return an ItemType if we already know the value
		//would be anEntry??
		return anEntry;
	}
	else
	{
		NotFoundException exception("Entry does not exist");
		throw exception;
	}
}



// ==== Contains ==============================================================
//
// Checks if an item exists in the tree. This function calls FindNode. 
//
// Input:
//		ItemType anEntry	[IN] - An ItemType that will be used to check if it
//								   exists.
//
// Output:
//		bool  -  True if found, or false if it is not.
//
// ============================================================================
template <class ItemType>
bool CBinaryNodeTree<ItemType>::Contains(const ItemType &anEntry) const
{
	//success gets updates to true if found
	bool success;
	success = false;
	FindNode(m_rootPtr, anEntry, success);

	return success;
}



// ==== PreorderTraverse ======================================================
//
// A function used to transverse the tree in preorder.  Calls the function
// Preorder.
//
// Input:
//		Visit	[IN] - A function that is a void return type and takes an
//					   argument of ItemType. This function is the processing
//                     step of each  node.  It is as simple as displaying the
//                     ItemType object.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::PreorderTraverse(
											void Visit(ItemType &item)) const
{
	Preorder(Visit, m_rootPtr);
}



// ==== InorderTraverse =======================================================
//
// A function used to transverse the tree in inorder.  Calls the function
// Inorder. This function is the processing step of each node.  It is as
// simple as displaying the ItemType object.
//
// Input:
//		Visit	[IN] - A function that is a void return type and takes an
//					   argument of ItemType.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::InorderTraverse(
											void Visit(ItemType &item)) const
{
	Inorder(Visit, m_rootPtr);
}



// ==== PostorderTraverse ======================================================
//
// A function used to transverse the tree in postorder.  Calls the function
// Postorder. This function is the processing step of each node.  It is as
// simple as displaying the ItemType object.
//
// Input:
//		Visit	[IN] - A function that is a void return type and takes an
//					   argument of ItemType.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::PostorderTraverse(
											void Visit(ItemType &item)) const
{
	Postorder(Visit, m_rootPtr);
}



// ==== Overloaded Assignment Operator ========================================
//
// Used to check if two CBinaryNodeTree are the same.
//
// Input:
//		rhs	[IN] - A const CBinaryNodeTree reference object.
//
// Output:
//		CBinaryNodeTree reference object
//
// ============================================================================
template <class ItemType>
CBinaryNodeTree<ItemType>& CBinaryNodeTree<ItemType>::operator=(
										const CBinaryNodeTree<ItemType> &rhs)
{
	if(this == &rhs)
	{
		return *this;
	}

	//clears old tree
	Clear();
	
	//Creates a copy of rhs and has m_rootPtr point to it
	m_rootPtr = CopyTree(rhs.m_rootPtr);

	return *this;
}



// ==== GetHeightHelper =======================================================
//
// This function calculates the height of the tree by providing the root
// subtree root pointer.
//
// Input:
//		subTreePtr	[IN] - A pointer of CBinaryNodeTree type for the root of
// 						   the tree.
//
// Output:
//		int  -  represents the height of the tree
//
// ============================================================================
template <class ItemType>
int CBinaryNodeTree<ItemType>::GetHeightHelper
								(CBinaryNode<ItemType> *subTreePtr) const
{
	if(subTreePtr == nullptr)
	{
		return 0;
	}
	else
	{
		int leftHeight = GetHeightHelper(subTreePtr->GetLeftChildPtr());
		int rightHeight = GetHeightHelper(subTreePtr->GetRightChildPtr());

		if (leftHeight > rightHeight)
		{
			return (leftHeight + 1);
		}
		
		else
		{
			return (rightHeight + 1);
		}
	}
}



// ==== GetNumberOfNodesHelper ================================================
//
// This function calculates the number of nodes of the tree by providing
// the root/subtree root pointer.
//
// Input:
//		subTreePtr	[IN] - A pointer of CBinaryNodeTree type for the root of
//                         the tree.
//
// Output:
//		int - represents the number of nodes
//
// ============================================================================
template <class ItemType>
int CBinaryNodeTree<ItemType>::GetNumberOfNodesHelper(
									CBinaryNode<ItemType> *subTreePtr) const
{
	int total = 1;
	
	if (subTreePtr == nullptr)
	{
		return 0;
	}

	else
	{
		total = total + GetNumberOfNodesHelper(subTreePtr->GetLeftChildPtr());
		total = total + GetNumberOfNodesHelper(subTreePtr->GetRightChildPtr());
		return total;
	}
}



// ==== BalancedAdd ===========================================================
//
// Recursively adds a new node to the tree in a left/right fashion to keep the
// tree balanced.
//
// Input:
//		subTreePtr	[IN] - A pointer of CBinaryNodeTree type for the root of
//						   the tree.
//		newNodePtr	[IN] - A new node pointer of CBinaryNodeTree type to add to
//						   the tree.
//
// Output:
//		CBinaryNode - Returns the updated subTreePtr after adding the new node.
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBinaryNodeTree<ItemType>::BalancedAdd(
		CBinaryNode<ItemType> *subTreePtr, CBinaryNode<ItemType> *newNodePtr)
{
	if (subTreePtr == nullptr)
	{
		return newNodePtr;
	}
	
	else
	{
		//if left side is bigger then right side, add new node to right side
		if (GetHeightHelper(subTreePtr->GetLeftChildPtr()) >
			GetHeightHelper(subTreePtr->GetRightChildPtr()))
		{
			subTreePtr->SetRightChildPtr(BalancedAdd(subTreePtr->GetRightChildPtr()
										,newNodePtr));
		}
		else
		{
			subTreePtr->SetLeftChildPtr(BalancedAdd(subTreePtr->GetLeftChildPtr(),
										newNodePtr));
		}

		return subTreePtr;
	}
}



// ==== MoveValuesUpTree ======================================================
//
// Copies values up the tree to overwrite value in current node until
// a leaf is reached; the leaf is then removed in Remove, since its value is
// stored in the parent.
//
// Input:
//		subTreePtr	[IN] - A pointer of CBinaryNodeTree type for the root of
//                         the tree.
//
// Output:
//		CBinaryNode - Returns the updated subTreePtr after placing the node in
//					  a leaf
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBinaryNodeTree<ItemType>::MoveValuesUpTree(
										CBinaryNode<ItemType> *subTreePtr)
{
	//if height is greater in right side traverse down right side
	if (GetHeightHelper(subTreePtr->GetRightChildPtr()) >
		GetHeightHelper(subTreePtr->GetLeftChildPtr()))
	{
		//if right pointer is a leaf, swap items and return subTreePtr
		if (subTreePtr->GetRightChildPtr()->IsLeaf())
		{
			ItemType itemHolder = subTreePtr->GetItem();
				
			//swap item and return pointer
			subTreePtr->SetItem(subTreePtr->GetRightChildPtr()->GetItem());
			subTreePtr->GetRightChildPtr()->SetItem(itemHolder);
				
			return subTreePtr;
		}
		//if not a leaf, swap items then use recursion to go down
		//right side
		else
		{
			ItemType itemHolder = subTreePtr->GetItem();
				
			//swap item and return pointer
			subTreePtr->SetItem(subTreePtr->GetRightChildPtr()->GetItem());
			subTreePtr->GetRightChildPtr()->SetItem(itemHolder);

			return MoveValuesUpTree(subTreePtr->GetRightChildPtr());
		}
	}
	//if height is NOT greater in right side traverse down left side
	else
	{
		//if right pointer is a leaf, swap items and return subTreePtr
		if (subTreePtr->GetLeftChildPtr()->IsLeaf())
		{
			ItemType itemHolder = subTreePtr->GetItem();
				
			//swap item and return pointer
			subTreePtr->SetItem(subTreePtr->GetLeftChildPtr()->GetItem());
			subTreePtr->GetLeftChildPtr()->SetItem(itemHolder);
				
			return subTreePtr;
		}
		//if not a leaf, swap items then use recursion to go down
		//left  side
		else
		{
			ItemType itemHolder = subTreePtr->GetItem();
				
			//swap item and return pointer
			subTreePtr->SetItem(subTreePtr->GetLeftChildPtr()->GetItem());
			subTreePtr->GetLeftChildPtr()->SetItem(itemHolder);

			//recur down the left side of the tree
			return MoveValuesUpTree(subTreePtr->GetLeftChildPtr());
		}
	}
}



// ==== RemoveValue ===========================================================
//
// Removes the target value from the tree by calling MoveValuesUpTree to
// overwrite value with value from child.
//
// Input:
//		subTreePtr	[IN] - A pointer of CBinaryNodeTree type for the root of
//                         the tree.
//		target		[IN] - A const ItemType reference to remove.
//		success 	[IN] - A bool reference to report success or failture of
//						   the removal.
//
// Output:
//		CBinaryNode - Returns the updated subTreePtr after removing the
//                    node.
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBinaryNodeTree<ItemType>::RemoveValue(
					CBinaryNode<ItemType> *subTreePtr, const ItemType &target,
					bool &success)
{
	CBinaryNode<ItemType>* nodeParent;
	nodeParent = MoveValuesUpTree(subTreePtr);

	if (nodeParent->GetRightChildPtr() != nullptr)
	{
		if (nodeParent->GetRightChildPtr()->GetItem() == target)
		{
			delete (nodeParent->GetRightChildPtr());
			nodeParent->SetRightChildPtr(nullptr);

			success = true;
			return subTreePtr;
		}
	}
	
	if (nodeParent->GetLeftChildPtr() != nullptr)
	{
		if (nodeParent->GetLeftChildPtr()->GetItem() == target)
		{
			delete (nodeParent->GetLeftChildPtr());
			nodeParent->SetLeftChildPtr(nullptr);
			
			success = true;
			return subTreePtr;
		}
	}

	success = false;
	return subTreePtr;
}



// ==== FindParent ============================================================
//
// Recursively searches for target value's parent in the tree by using a
// preorder traversal.
//
// Input:
//		treePtr	[IN] - A pointer of CBinaryNodeTree type for the root of the
//                     tree.
//		target	[IN] - A const ItemType reference to find.
//		parentHolder	[IN/OUT] - An ItemType that will represent the parent
//									of the target
//
// Output:
//		ItemType -  Returns parent to the item's node
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBinaryNodeTree<ItemType>::FindParent(
								CBinaryNode<ItemType> *treePtr,
								const ItemType &target)
{
	if (treePtr == nullptr)
	{
		return nullptr;
	}
	else
	{
		if ((treePtr->GetLeftChildPtr() != nullptr &&
			treePtr->GetLeftChildPtr()->GetItem() == target) ||
			(treePtr->GetRightChildPtr() != nullptr &&
			treePtr->GetRightChildPtr()->GetItem() == target))
			{
				return treePtr;
			}
		else
		{
			CBinaryNode<ItemType>* search;
			search = FindParent(treePtr->GetLeftChildPtr(), target);
			//searches using FindParent then returns result
			if (search != nullptr)
			{
				return search;
			}
			else
			{
				return FindParent(treePtr->GetRightChildPtr(), target);
			}
		}
	}
}



// ==== FindNode ==============================================================
//
// Recursively searches for target value in the tree by using a
// preorder traversal.
//
// Input:
//		treePtr	[IN] - A pointer of CBinaryNodeTree type for the root of the
//                     tree.
//		target	[IN] - A const ItemType reference to find.
//		success	[IN] - A bool reference to report success or failure of the
//					   search
//
// Output:
//		CBinaryNode -  Returns target node pointer.
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBinaryNodeTree<ItemType>::FindNode(
			CBinaryNode<ItemType> *treePtr, const ItemType &target,
			bool &success) const
{
	if (treePtr == nullptr)
	{
		success = false;
		return nullptr;
	}
	if (treePtr->GetItem() == target)
	{
		success = true;
		return treePtr;
	}
	
	//check if we can find target in the left subtree
	CBinaryNode<ItemType>* search;
	search = FindNode(treePtr->GetLeftChildPtr(), target, success);
	if (search != nullptr)
	{
		success = true;
		return search;
	}

	//if not found in the left subtree, try the right one
	return FindNode(treePtr->GetRightChildPtr(), target, success);
}



// ==== CopyTree ==============================================================
//
// Copies the tree rooted at treePtr and returns a pointer to
// the copy.
//
// Input:
//		oldTreeRootPtr	[IN] - A pointer of CBinaryNodeTree type for the root of
//                       	   the tree.
//
// Output:
//		CBinaryNode - Returns the new tree pointer.
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBinaryNodeTree<ItemType>::CopyTree(
							const CBinaryNode<ItemType> *oldTreeRootPtr) const
{
	CBinaryNode<ItemType>* newTreePtr;
	
	if (oldTreeRootPtr != nullptr)
	{
		newTreePtr = new CBinaryNode<ItemType>();
		newTreePtr->SetItem(oldTreeRootPtr->GetItem());

		newTreePtr->SetLeftChildPtr(CopyTree(oldTreeRootPtr->GetLeftChildPtr()));
		newTreePtr->SetRightChildPtr(CopyTree(oldTreeRootPtr->GetRightChildPtr()));
	}
	else
	{
		return nullptr;
	}

	return newTreePtr;
}



// ==== DestroyTree ===========================================================
//
// Recursively deletes all nodes from the tree.
//
// Input:
//		subTreePtr	[IN] - A pointer of CBinaryNodeTree type for the root of
//                         the tree.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::DestroyTree(CBinaryNode<ItemType> *subTreePtr)
{
	if (subTreePtr == nullptr)
	{
		return;
	}

	DestroyTree(subTreePtr->GetLeftChildPtr());
	DestroyTree(subTreePtr->GetRightChildPtr());

	delete subTreePtr;
}



// ==== Preorder ==============================================================
//
// Recursive traversal helper methods for Preorder
//
// Input:
//		Visit	[IN] - A function that processes an ItemType object. This
//	                   function is as simple as displaying the ItemType object.
//		treePtr	[IN] - A pointer of CBinaryNodeTree type for the root of the
//                     tree.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::Preorder(void Visit(ItemType &item),
                 CBinaryNode<ItemType> *treePtr) const
{
	if (treePtr != nullptr)
	{
		ItemType itemContents = treePtr->GetItem();
		Visit(itemContents);
		
		Inorder(Visit, treePtr->GetLeftChildPtr());
		
		Inorder(Visit, treePtr->GetRightChildPtr());
	}
}



// ==== Inorder ===============================================================
//
// Recursive traversal helper methods for Inorder
//
// Input:
//		Visit	[IN] - A function that processes an ItemType object. This
//	                   function is as simple as displaying the ItemType object.
//		treePtr	[IN] - A pointer of CBinaryNodeTree type for the root of the
//                     tree.
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::Inorder(void Visit(ItemType &item),
                CBinaryNode<ItemType> *treePtr) const
{
	if (treePtr != nullptr)
	{
		Inorder(Visit, treePtr->GetLeftChildPtr());

		ItemType itemContents = treePtr->GetItem();
		Visit(itemContents);
		Inorder(Visit, treePtr->GetRightChildPtr());
	}
}



// ==== Postorder =============================================================
//
// Recursive traversal helper methods for Postorder
//
// Input:
//		Visit	[IN] - A function that processes an ItemType object. This
//	                   function is as simple as displaying the ItemType object.
//		treePtr [IN] - A pointer of CBinaryNodeTree type for the root of the
//                     tree.
//
//
// Output:
//		nothing
//
// ============================================================================
template <class ItemType>
void CBinaryNodeTree<ItemType>::Postorder(void Visit(ItemType &item),
                  CBinaryNode<ItemType> *treePtr) const
{
	if (treePtr != nullptr)
	{
		Inorder(Visit, treePtr->GetLeftChildPtr());
		Inorder(Visit, treePtr->GetRightChildPtr());
		
		ItemType itemContents = treePtr->GetItem();
		Visit(itemContents);
	}
}
