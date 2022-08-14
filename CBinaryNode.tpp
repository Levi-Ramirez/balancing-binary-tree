// ============================================================================
// File: CBinaryNode.tpp
// ============================================================================
// This is the implementation file for the CBinaryNode class which impliments a
// binary node
// ============================================================================

#include <iostream>
using namespace std;

#include "CBinaryNode.h"



// ==== Default Constructor ===================================================
//
// Initializes left and right child ptr to nullptr and leaves m_item as garbage
//
// Input:
//		nothing
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>::CBinaryNode()
{
	m_leftChildPtr = nullptr;
	m_rightChildPtr = nullptr;
}


   
// ==== Type Constructor ======================================================
//
// Initializes m_item and sets left and right child ptr to nullptr.
//
// Input:
//		item	[IN] - a const ItemType reference
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>::CBinaryNode(const ItemType &item) : m_item(item),
					m_leftChildPtr(nullptr), m_rightChildPtr(nullptr)
{
	
}


   
// ==== Type Constructor ======================================================
//
// Initializes all the private data members with the supplied arguments.
//
// Input:
//		item			[IN] - a const ItemType reference
//		leftChildPtr	[IN] - a pointer to a CBinaryNode
//		rightChildPtr	[IN] - a pointer to a CBinaryNode
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>::CBinaryNode(const ItemType &item,
           CBinaryNode<ItemType> *leftChildPtr,
           CBinaryNode<ItemType> *rightChildPtr) : m_item(item),
           m_leftChildPtr(leftChildPtr), m_rightChildPtr(rightChildPtr)
{
	
}



// ==== SetItem  ==============================================================
//
// Assigns an Item to m_item
//
// Input:
//		item			[IN] - a const ItemType reference
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
 void CBinaryNode<ItemType>::SetItem(const ItemType &item)
 {
 	m_item = item;
 }



// ==== GetItem ===============================================================
//
// Retrieves m_item
//
// Input:
//		nothing
//
// Output:
//		ItemType data type (template)
//
// ============================================================================
template<class ItemType>
ItemType CBinaryNode<ItemType>::GetItem() const
{
	return m_item;
}



// ==== IsLeaf ================================================================
//
// Checks if a node is a leaf.
//
// Input:
//		nothing
//
// Output:
//		bool - true if node is a leaf, false if its not
//
// ============================================================================
template<class ItemType>
bool CBinaryNode<ItemType>::IsLeaf() const
{
	if (m_leftChildPtr == nullptr && m_rightChildPtr == nullptr)
	{
		return true;
	}

	return false;
}



// ==== GetLeftChildPtr =======================================================
//
// Retrieves the pointer to the left node (left child).
//
// Input:
//		nothing
//
// Output:
//		CBinaryNode<ItemType>*. A templated pointer to the left node.
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBinaryNode<ItemType>::GetLeftChildPtr() const
{
	return m_leftChildPtr;
}



// ==== GetRightChildPtr ======================================================
//
// Retrieves the pointer to the right node (right child).
//
// Input:
//		nothing
//
// Output:
//		CBinaryNode<ItemType>*. A templated pointer to the left node.
//
// ============================================================================
template<class ItemType>
CBinaryNode<ItemType>* CBinaryNode<ItemType>::GetRightChildPtr() const
{
	return m_rightChildPtr;
}



// ==== SetLeftChildPtr =======================================================
//
// Retrieves the pointer to the right node (right child).
//
// Input:
//		*leftChildPtr - [IN] A templated pointer to the left node
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
void   CBinaryNode<ItemType>::SetLeftChildPtr(CBinaryNode<ItemType> *leftChildPtr)
{
	m_leftChildPtr = leftChildPtr;
}



// ==== SetRightChildPtr =======================================================
//
// Retrieves the pointer to the right node (right child).
//
// Input:
//		*rightChildPtr - [IN] A templated pointer to the left node
//
// Output:
//		nothing
//
// ============================================================================
template<class ItemType>
void   CBinaryNode<ItemType>::SetRightChildPtr(CBinaryNode<ItemType> *rightChildPtr)
{
	m_rightChildPtr = rightChildPtr;
}
