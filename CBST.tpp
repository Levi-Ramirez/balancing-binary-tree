// ============================================================================
// File: CBST.tpp
// ============================================================================
// This is the implementation file for the classCBST which impliments a binary
// search tree
// ============================================================================

#include <iostream>
#include "CBST.h"
using namespace std;

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
template<class ItemType>
CBST<ItemType>::CBST()
{
	m_rootPtr = nullptr;
}



// ==== Type Constructor ===================================================
//
// Allocates space for a CBinaryNode and sets it equal to m_rootPtr.  The
// allocated node initializes the item and sets nullptr to its left and
// right childs
//
// Input:
//		rootItem	[IN] - a const ItemType reference
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
CBST<ItemType>::CBST(const ItemType &rootItem)
{
	m_rootPtr = new CBinaryNode<ItemType>;

	m_rootPtr->SetItem(rootItem);
}



// ==== Copy Constructor ======================================================
//
// Copy constructor.  It copies the tree that was given as an argument.
// Uses a deep copy by calling the inherited method CopyTree.
//
// Input:
//		tree	[IN] - a const CBST with type ItemType
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
CBST<ItemType>::CBST(const CBST<ItemType> &tree) :
											CBinaryNodeTree<ItemType> (tree)
{
	Clear();
	m_rootPtr = CBinaryNodeTree<ItemType>::CopyTree(tree.m_rootPtr);
}



// ==== Destructor ============================================================
//
// Releases the memory of the tree appropriately. Calls the
// inherited method DestroyTree.
//
// Input:
//		nothing
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
CBST<ItemType>::~CBST()
{
	CBinaryNodeTree<ItemType>::DestroyTree(m_rootPtr);
}


   
// ============================================================================
//      Member Functions
// ============================================================================



// ==== IsEmpty ===============================================================
//
// Checks if m_rootPtr is nullptr
//
// Input:
//		nothing
//
// Output:
//		bool  -  True if it is empty, false if it is not
//
// ============================================================================
template<class ItemType>
bool CBST<ItemType>::IsEmpty() const
{
	if (m_rootPtr == nullptr)
	{
		return true;
	}

	return false;
}



// ==== IsHeight ==============================================================
//
// Counts the height of the tree by calling the inherited method 
// GetHeightHelper.
//
// Input:
//		nothing
//
// Output:
//		int  -  value representing the height of the tree
//
// ============================================================================
template<class ItemType>
int CBST<ItemType>::GetHeight() const
{
	return CBinaryNodeTree<ItemType>::GetHeightHelper(m_rootPtr);
}



// ==== GetNumberOfNodes ======================================================
//
// Counts the number of nodes the tree has by calling the inherited
// function GetNumberOfNodesHelper.
//
// Input:
//		nothing
//
// Output:
//		int  -  value representing the number of nodes the tree has
//
// ============================================================================
template<class ItemType>
int CBST<ItemType>::GetNumberOfNodes() const
{
	return CBinaryNodeTree<ItemType>::GetNumberOfNodesHelper(m_rootPtr);
}



// ==== GetRootData ===========================================================
//
// Gets the item at root location.
//
// Input:
//		nothing
//
// Output:
//		ItemType  -  m_rootPtr item when it exists
//		PrevondViolatedExcept  -  error thrown if tree is empty
//		
//
// ============================================================================
template<class ItemType>
ItemType CBST<ItemType>::GetRootData() const throw(PrecondViolatedExcept)
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
// An ItemType that will be assigned/initialzed at the root location.
//
// Input:
//		nothing
//
// Output:
//		PrevondViolatedExcept  -  error thrown if this function is called
//								  containing the message "Cannot change root
//							      value in a CBST"
//
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::SetRootData(const ItemType &newData)
									const throw(PrecondViolatedExcept)
{
	PrecondViolatedExcept exception("Cannot change root value in a CBST");
	throw exception;
}



// ==== Add ===================================================================
//
// Adds a new node to the tree.  Allocate the new node first and then call
// the function PlaceNode to add the new node to the tree.
//
// Input:
//		newEntry	[IN] - a const ItemType reference
//
// Output:
//		bool  -  True if add was successful, false if it is not
//
//
// ============================================================================
template<class ItemType>
bool CBST<ItemType>::Add(const ItemType &newEntry)
{
	//create new node and alocate the item
	CBinaryNode<ItemType> *newNode = new CBinaryNode<ItemType>;
	newNode->SetItem(newEntry);

	m_rootPtr = PlaceNode(m_rootPtr, newNode);

	//balance after addition
	ArrayToTree();

	return true; //will always be true??
}



// ==== Remove ================================================================
//
// Removes a node from the tree.  This function calls the function RemoveValue.
// Remove value will remove any node except a leaf node as it needs its parent
// It is much more convienent to take care of this case here.
//
// Input:
//		asEntry	[IN] - An ItemType that will be used to find the node to delete
//
// Output:
//		bool  -  True if removal was successful, false if it is not
//
//
// ============================================================================
template<class ItemType>
bool CBST<ItemType>::Remove(const ItemType &anEntry)
{
	if (!Contains(anEntry))
	{
		return false;
	}
	//success gets updated to true if removal was successful
	bool success;
	success = false;

	RemoveValue(m_rootPtr, anEntry, success);

	//if it still contains the entry then it is a leaf after running through
	//Remove Value so locate parent node and delete it we must use the
	//implimentation of FindNode from CBinarNode Tree here because if anEntry
	// passed through the RemoveLeftmostNode function then it will be out of
	//order, thus the CBST::Contains or CBST::FindNode won't find it
	
	bool searchSuccess;
	CBinaryNodeTree<ItemType>::FindNode(m_rootPtr, anEntry, searchSuccess);
	
	if (searchSuccess)
	{	
		if (m_rootPtr->GetItem() == anEntry && m_rootPtr->IsLeaf())
		{
			delete m_rootPtr;
			m_rootPtr = nullptr;
		
			success = true;
		}
		else
		{
			CBinaryNode<ItemType> *parentHolder;
			parentHolder = FindParent(m_rootPtr, anEntry);
			if (parentHolder->GetLeftChildPtr() != nullptr)
			{
				if (parentHolder->GetLeftChildPtr()->GetItem() == anEntry &&
			 	   parentHolder->GetLeftChildPtr()->IsLeaf())
				{
					delete (parentHolder->GetLeftChildPtr());
					parentHolder->SetLeftChildPtr(nullptr);

					success = true;
				}
			}
			
			if (parentHolder->GetRightChildPtr() != nullptr)
			{
				if (parentHolder->GetRightChildPtr()->GetItem() == anEntry &&
				   parentHolder->GetRightChildPtr()->IsLeaf())
				{
					delete (parentHolder->GetRightChildPtr());
					parentHolder->SetRightChildPtr(nullptr);

					success = true;
				}
			}
			
		}
	}

	//balance after removal
	if (m_rootPtr != nullptr)
	{
		ArrayToTree();
	}
	return success;
}



// ==== Clear =================================================================
//
// Clears all nodes of the tree. The function calls DestroyTree.
//
// Input:
//		nothing
//
// Output:
//		nothing
//
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::Clear()
{
	CBinaryNodeTree<ItemType>::DestroyTree(m_rootPtr);
	
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
//		asEntry	[IN] - An ItemType that will be used to retrieve an item
//
// Output:
//		ItemType  -  returns an ItemType if the entry exists
//
//		NotFoundException  -  thrown if the entry does not exist
//
//
// ============================================================================
template<class ItemType>
ItemType CBST<ItemType>::GetEntry(const ItemType &anEntry)
										const throw(NotFoundException)
{
	if (FindNode(m_rootPtr, anEntry) != nullptr)
	{
		//why do we want to return an ItemType if we already know the value
		//would be anEntry??
		return anEntry;
	}
	else
	{
		NotFoundException exception("Entry does not exhist");
		throw exception;
	}
}



// ==== Contains ==============================================================
//
// Checks if an item exists in the tree.  This function calls FindNode.
//
// Input:
//		asEntry	[IN] - An ItemType that will be used to retrieve an item
//
// Output:
//		bool  - True if found, false if not found.
//
//
// ============================================================================
template<class ItemType>
bool CBST<ItemType>::Contains(const ItemType &anEntry) const
{
	if (FindNode(m_rootPtr, anEntry) != nullptr)
	{
		return true;
	}
	return false;
}



// ==== PreorderTraverse ======================================================
//
// A function used to transverse the tree in preorder.  Calls the inherited
// function Preorder.
//
// Input:
//		Visit	[IN] - A function that is a void return type and takes an
//                  argument of ItemType. This function is the processing step
//                  of each node. It is as simple as displaying the ItemType
//					object.
//
// Output:
//		nothing
//
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::PreorderTraverse(void Visit(ItemType &item)) const
{
	CBinaryNodeTree<ItemType>::Preorder(Visit, m_rootPtr);
}



// ==== InorderTraverse =======================================================
//
// A function used to transverse the tree in inorder.  Calls the inherited
// function Inorder.
//
// Input:
//		Visit	[IN] - A function that is a void return type and takes an
//                  argument of ItemType. This function is the processing step
//                  of each node. It is as simple as displaying the ItemType
//					object.
//
// Output:
//		nothing
//
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::InorderTraverse(void Visit(ItemType &item)) const
{
	CBinaryNodeTree<ItemType>::Inorder(Visit, m_rootPtr);
}



// ==== PostorderTraverse =====================================================
//
// A function used to transverse the tree in postorder.  Calls the inherited
// function Postorder.
//
// Input:
//		Visit	[IN] - A function that is a void return type and takes an
//                  argument of ItemType. This function is the processing step
//                  of each node. It is as simple as displaying the ItemType
//					object.
//
// Output:
//		nothing
//
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::PostorderTraverse(void Visit(ItemType &item)) const
{
	CBinaryNodeTree<ItemType>::Postorder(Visit, m_rootPtr);
}



// ==== TreeToArray ===========================================================
//
// This function recursively creates a balanced tree from an array
//
// Input:
//		treePtr	[IN] - A pointer of CBinaryNode type for the root of the tree.
//		arr	[IN/OUT] - An array whose size is the same as the number of nodes
//    				   in a tree
//		arrLocation	[IN] - pointer to an int which shows the location of where
//    					   to add the current node. Gets updated every
//						   recursion
//
// Output:
//		nothing but updates whatever array was passed into the function
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::TreeToArray(CBinaryNode<ItemType> *treePtr,
								ItemType arr[], int *arrLocation)
{
	if (treePtr == nullptr)
	{
		return;
	}

	TreeToArray(treePtr->GetLeftChildPtr(), arr, arrLocation);

	arr[*arrLocation] = treePtr->GetItem();
	++ *arrLocation;
	
	TreeToArray(treePtr->GetRightChildPtr(), arr, arrLocation);
}



// ==== ArrayToTree ===========================================================
//
// This creates a balanced BST by calling TreeToArray to create an
// array representing the tree then call ArrayToTreeHelper to convert that
// array back to a tree but balanced.
//
// Input:
//		nothing
//
// Output:
//		nothing but updates m_rootPtr and thus the tree
//
// ============================================================================
template<class ItemType>
void CBST<ItemType>::ArrayToTree()
{
	int numberNodes;
	numberNodes = GetNumberOfNodes();
	ItemType arr[numberNodes];

	int arrayLocation;
	arrayLocation = 0;

	//create the array
	TreeToArray(m_rootPtr, arr, &arrayLocation);

	//clear the tree
	Clear();

	//create new tree
	int start;
	start = 0;
	int end;
	end = numberNodes - 1; //maybe not -1
	
	m_rootPtr = ArrayToTreeHelper(arr, start, end);
	
}



// ==== ArrayToTreeHelper =====================================================
//
// This function recursively creates a balanced tree from an array
//
// Input:
//		arr	[IN] - A sorted array from least to greatest
//		start	[IN] - int of where to start in the array
//		end	[IN] - int of where to end in the array
//
// Output:
//		CBST - a CBST pointer which points to the rot of the new tree
//
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::ArrayToTreeHelper(ItemType arr[],
							int start, int end)
{
	if (start > end)
	{
		return nullptr;
	}

	int mid = (start + end)/2;
	//create new node at middle
	CBinaryNode<ItemType>* tempRoot;
	tempRoot = new CBinaryNode<ItemType>;
	tempRoot->SetItem(arr[mid]);

	//recur down left side
	tempRoot->SetLeftChildPtr(ArrayToTreeHelper(arr, start, mid - 1));

	//recur down right side
	tempRoot->SetRightChildPtr(ArrayToTreeHelper(arr, mid + 1, end));

	return tempRoot;
	
}



// ==== Overloaded Assignment Operator ========================================
//
// Overloaded assignment operator.  Used to check if two CBST's are the
// same.
//
// Input:
//		rhs	[IN] - A const CBST reference object.
//
// Output:
//		CBST - a CBST reference object
//
//
// ============================================================================
template<class ItemType>
CBST<ItemType>& CBST<ItemType>::operator=(const CBST<ItemType> &rhs)
{
	if (this == &rhs)
	{
		return *this;
	}

	//clears old tree
	if (m_rootPtr != nullptr)
	{
		Clear();
	}

	//Creates a copy of rhs and has m_rootPtr point to it
	m_rootPtr = CBinaryNodeTree<ItemType>::CopyTree(rhs.m_rootPtr);

	return *this;
}



// =========================================================================
//      Protected Member Functions
// =========================================================================



// ==== PlaceNode =============================================================
//
// This function recursively finds where the given node should be placed
// and inserts it in a leaf at that point.
//
// Input:
//		subTreeptr	[IN] - A pointer of CBinaryNode type for the root of the
//						   tree.
//		newNode		[IN] - A pointer of CBinaryNode type for the new node to
//						   add/place.
//
// Output:
//		CBST - a CBST pointer
//
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::PlaceNode(
			CBinaryNode<ItemType> *subTreePtr, CBinaryNode<ItemType> *newNode)
{
	if (subTreePtr == nullptr)
	{
		return newNode;
	}
	else if (subTreePtr->GetItem() > newNode->GetItem())
	{
		CBinaryNode<ItemType> *tempPtr;
		tempPtr = PlaceNode(subTreePtr->GetLeftChildPtr(), newNode);
		subTreePtr->SetLeftChildPtr(tempPtr);
	}
	else
	{
		CBinaryNode<ItemType> *tempPtr;
		tempPtr = PlaceNode(subTreePtr->GetRightChildPtr(), newNode);
		subTreePtr->SetRightChildPtr(tempPtr);
	}

	return subTreePtr;
}



// ==== RemoveValue ===========================================================
//
// This function recursively finds where the given node should be placed
// and inserts it in a leaf at that point
//
// Input:
//		subTreeptr	[IN] - A pointer of CBinaryNode type for the root of the
//						   tree.
//		target		[IN] - An ItemType to remove.
//		success 	[IN/OUT] - A bool reference to report success or failture
//                             of the removal.
//
// Output:
//		CBinaryNode - a CBinaryNode pointer
//
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::RemoveValue(
      CBinaryNode<ItemType> *subTreePtr, const ItemType &target, bool &success)
{
	if (subTreePtr == nullptr)
	{
		success = false;
	}
	else if (subTreePtr->GetItem() == target)
	{
		subTreePtr = RemoveNode(subTreePtr); //remove item
		success = true;
	}
	else if (subTreePtr->GetItem() > target)
	{
		//create a temporoary ptr to a CBinaryNode and search the left subtree
		CBinaryNode<ItemType> *tempPtr;
		tempPtr = RemoveValue(subTreePtr->GetLeftChildPtr(), target, success);

		subTreePtr->SetLeftChildPtr(tempPtr);
	}
	else
	{
		//create a temporoary ptr to a CBinaryNode and search the left subtree
		CBinaryNode<ItemType> *tempPtr;
		tempPtr = RemoveValue(subTreePtr->GetRightChildPtr(), target, success);

		subTreePtr->SetRightChildPtr(tempPtr);
	}

	return subTreePtr;
}



// ==== RemoveNode ===========================================================
//
// This function removes a given node from a tree while maintaining a
// binary search tree.
//
// Input:
//		nodePtr	[IN] - A pointer of CBinaryNode type for the root of the tree.
//
// Output:
//		CBinaryNode - a CBinaryNode pointer
//
//
// ===========================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::RemoveNode(
											CBinaryNode<ItemType> *nodePtr)
{
	if (nodePtr->IsLeaf())
	{
		return nodePtr;
	}
	else if ((nodePtr->GetLeftChildPtr() == nullptr || 
			nodePtr->GetRightChildPtr() == nullptr) && !(nodePtr->IsLeaf()))
	{
		CBinaryNode<ItemType> *nodeToConnectPtr;
		if (nodePtr->GetRightChildPtr() == nullptr)
		{
			nodeToConnectPtr = nodePtr->GetLeftChildPtr();
		}
		else
		{
			nodeToConnectPtr = nodePtr->GetRightChildPtr();
		}

		//if the root is the one you delete here, make sure you relink the root back
		//to the tree, this if statment checks for this
		if (nodePtr->GetItem() == m_rootPtr->GetItem())
		{
			m_rootPtr = nodeToConnectPtr;
		}
		
		delete nodePtr;

		return nodeToConnectPtr;
	}
	else
	{
		CBinaryNode<ItemType> *tempPtr;
		ItemType tempItem;

		//pass item we want to remove to tempItem
		tempItem = nodePtr->GetItem();
		tempPtr = RemoveLeftmostNode(nodePtr->GetRightChildPtr(),
									 tempItem);

		nodePtr->SetRightChildPtr(tempPtr);
		nodePtr->SetItem(tempItem);
		return nodePtr;
	}
}



// ==== RemoveLeftmostNode ====================================================
//
// This function recursively finds where the given node should be placed
// and inserts it in a leaf at that point
//
// Input:
//		subtreePtr	[IN] - A pointer of CBinaryNode type for the root of the
//						   tree.
//		inorderSuccessor	[IN] - A reference of ItemType type for its
//									successor.
//
// Output:
//		CBinaryNode - a CBinaryNode pointer to the revised subtree
//
//
// ===========================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::RemoveLeftmostNode(
		  CBinaryNode<ItemType> *subTreePtr, ItemType &inorderSuccessor)
{
	if (subTreePtr->GetLeftChildPtr() == nullptr)
	{
		
		ItemType itemHolder;
		//have item holder hold the item that we want to remove which
		//was passed to inorder successor
		itemHolder = inorderSuccessor;

		//update inorderSuccessor to hold the inorderSuccessor
		inorderSuccessor = subTreePtr->GetItem();

		//now item is at the bottom of the subtree
		subTreePtr->SetItem(itemHolder);

		//in the special case where m_rootPtr is the node to remove,
		//update the value to the inorder successor now or it will interfere
		//with the special root case of RemoveNode
		if (m_rootPtr->GetItem() == itemHolder)
		{
			m_rootPtr->SetItem(inorderSuccessor);
		}
		
		return RemoveNode(subTreePtr);
	}
	else
	{
		CBinaryNode<ItemType> *tempPtr;
		tempPtr = RemoveLeftmostNode(
							subTreePtr->GetLeftChildPtr(), inorderSuccessor);

		subTreePtr->SetLeftChildPtr(tempPtr);
		return subTreePtr;
	}
}



// ==== FindNode ==============================================================
//
// This function returns a pointer to the node containing the given value, or
// nullptr if not found.
//
// Input:
//		treePtr	[IN] - A pointer of CBinaryNode type for the root of the tree.
//		target	[IN] - A reference of ItemType type to find the node
//					   corresponding.
//
// Output:
//		CBinaryNode - a CBinaryNode pointer to the revised subtree
//
//
// ===========================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::FindNode(
                CBinaryNode<ItemType> *treePtr, const ItemType& target) const
{
	if (treePtr == nullptr || treePtr->GetItem() == target)
	{
		return treePtr;
	}
	if (treePtr->GetItem() < target)
	{
		return FindNode(treePtr->GetRightChildPtr(), target);
	}
	
	return FindNode(treePtr->GetLeftChildPtr(), target);
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
//		ItemType -  Returns parent to the target's node
//
// ============================================================================
template <class ItemType>
CBinaryNode<ItemType>* CBST<ItemType>::FindParent(
								CBinaryNode<ItemType> *treePtr,
								const ItemType &target)
{
	return CBinaryNodeTree<ItemType>::FindParent(treePtr, target);
}
