// ============================================================================
// File: CBST.h
// ============================================================================
// Header file for the class CBST (Binary Search Tree)
// ============================================================================

#ifndef CBST_HEADER
#define CBST_HEADER

#include "CBinaryTreeInterface.h"
#include "CBinaryNode.h"
#include "CBinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcept.h"

template<class ItemType>
class CBST : public CBinaryNodeTree<ItemType>
{
public:
   // =========================================================================
   //      Constructors and Destructor
   // =========================================================================
   
   /** Sets m_rootPtr to nullptr*/
   CBST();

   /** Allocates space for a CBinaryNode and sets it equal to m_rootPtr.  The
        allocated node initializes the item and sets nullptr to its left and
        right childs. */
   CBST(const ItemType &rootItem);

    /** Copy constructor.  It copies the tree that was given as an argument.
        Uses a deep copy by calling the inherited method CopyTree. */
   CBST(const CBST<ItemType> &tree);

   /** Destructor.  Releases the memory of the tree appropriately. Calls the
                    inherited method DestroyTree. */
   virtual ~CBST();
   
   // =========================================================================
   //      Member Functions
   // =========================================================================

   /** Checks if m_rootPtr is nullptr
    @param Nothing.
    @return  True if it is empty, or false if it is not. */
   bool IsEmpty() const override;

   /** Counts the height of the tree by calling the inherited method 
       GetHeightHelper.
    @param Nothing.
    @return  An int value representing the height of the tree. */
   int GetHeight() const override;

   /** Counts the number of nodes the tree has by calling the inherited
       function GetNumberOfNodesHelper.
    @param Nothing.
    @return  An int value representing the number of nodes the tree has. */
   int GetNumberOfNodes() const override;

   /** Gets the item at root location.
    @param Nothing.
    @return  An ItemType that is located at the root.
    @throw  PrecondViolatedExcept if the tree is empty. */
   ItemType GetRootData() const throw(PrecondViolatedExcept) override;

   /** Throws an error that you "Cannot change root value in a CBST".
    @param newData: An ItemType that will be assigned/initialzed at the root
                    location.
    @return  Nothing.
    @throw  PrecondViolatedExcept if you call this function. */
   void SetRootData(const ItemType &newData) const throw(PrecondViolatedExcept);

   /** Adds a new node to the tree.  Allocate the new node first and then call
       the function PlaceNode to add the new node to the tree.
    @param newEntry: An ItemType that will be used to initialzed the new node.
    @return  True if add was successful, or false if it is not. */
   bool Add(const ItemType &newEntry) override;

   /** Removes a node from the tree.  This function calls the function 
       RemoveValue.
    @param target: An ItemType that will be used to find the node to delete.
    @return  True if remove was successful, or false if it is not. */
   bool Remove(const ItemType &anEntry) override;

   /** Clears all nodes of the tree.  The function calls DestroyTree.
    @param Nothing.
    @return  Nothing. */
   void Clear() override;

   /** Retrieves an entry from the tree.  This function calls FindNode.
    @param anEntry: An ItemType that will be used to retrieve an item.
    @return  Returns an ItemType (the entry if it exists.
    @throw   NotFoundException if the entry does not exists. */
   ItemType GetEntry(const ItemType &anEntry) const throw(NotFoundException) override;

   /** Checks if an item exists in the tree.  This function calls FindNode.
    @param anEntry: An ItemType that will be used to check if it exists.
    @return  True if found, or false if it is not. */
   bool Contains(const ItemType &anEntry) const override;
   
   /** A function used to transverse the tree in preorder.  Calls the inherited
       function Preorder.
    @param Visit: A function that is a void return type and takes an argument
                  of ItemType. This function is the processing step of each
                  node.  It is as simple as displaying the ItemType object.
    @return  Nothing. */
   void PreorderTraverse(void Visit(ItemType &item)) const override;

   /** A function used to transverse the tree in inorder.  Calls the inherited
       function Inorder.
    @param Visit: A function that is a void return type and takes an argument
                  of ItemType. This function is the processing step of each
                  node.  It is as simple as displaying the ItemType object.
    @return  Nothing. */
   void InorderTraverse(void Visit(ItemType &item)) const override;

   /** A function used to transverse the tree in postorder.  Calls the
       inherited function Postorder.
    @param Visit: A function that is a void return type and takes an argument
                  of ItemType. This function is the processing step of each
                  node.  It is as simple as displaying the ItemType object.
    @return  Nothing. */
   void PostorderTraverse(void Visit(ItemType &item)) const override;

   /** This function recursively creates a array from a tree
    @param treePtr: A pointer of CBinaryNode type for the root of the tree.
    @param arr: An array whose size is the same as the number of nodes in
    			a tree
    @param arrLocation: pointer to an int which shows the location of where
    					to add the current node. Gets updated every recursion
    @return  nothing */
   void TreeToArray(CBinaryNode<ItemType> *treePtr, ItemType arr[],
   					int *arrLocation);

   /** This creates a balanced BST by calling TreeToArray to create an
   	   array representing the tree then call ArrayToTreeHelper to convert that
   	   array back to a tree but balanced.
    @return  nothing */
   void ArrayToTree();

   /** This function recursively creates a balanced tree from an array
    @param arr: A sorted array from least to greatest
    @param start: int of where to start in the array
    @param end: int of where to end in the array
    @return  A CBST pointer. */
   CBinaryNode<ItemType>* ArrayToTreeHelper(ItemType arr[], int start, int end);

   /** Overloaded assignment operator.  Used to check if two CBST's are the
      same.
    @param rhs: A const CBST reference object.
    @return  CBST reference object. */
   CBST<ItemType>& operator=(const CBST<ItemType> &rhs); 

 
protected:
   // =========================================================================
   //      Protected Member Functions
   // =========================================================================

   /** This function recursively finds where the given node should be placed
       and inserts it in a leaf at that point.
    @param subTreePtr: A pointer of CBinaryNode type for the root of the tree.
    @param newNode: A pointer of CBinaryNode type for the new node to add/place.
    @return  A CBST pointer. */
  CBinaryNode<ItemType>* PlaceNode(CBinaryNode<ItemType> *subTreePtr,
                  CBinaryNode<ItemType> *newNode);
   
   /** This function removes the given target value from the tree while 
       maintaining a binary search tree.
    @param subTreePtr: A pointer of CBinaryNode type for the root of the tree.
    @param target: An ItemType to remove.
    @param success: A bool reference to report success or failture of the
                    removal.
    @return  A CBinaryNode pointer. */
   CBinaryNode<ItemType>* RemoveValue(CBinaryNode<ItemType> *subTreePtr,
                                      const ItemType &target,
                                      bool &success);
   
   /** This function removes a given node from a tree while maintaining a
       binary search tree.
    @param nodePtr: A pointer of CBinaryNode type for the root of the tree.
    @return  A CBinaryNode pointer. */
   CBinaryNode<ItemType>* RemoveNode(CBinaryNode<ItemType> *nodePtr);
   
   /** This function removes the leftmost node in the left subtree of the node
       pointed to by nodePtr. Sets inorderSuccessor to the value in this node.
    @param subTreePtr: A pointer of CBinaryNode type for the root of the tree.
    @param inorderSuccessor: A reference of ItemType type for its successor.
    @return  Returns a CBinaryNode pointer to the revised subtree. */

   CBinaryNode<ItemType>* RemoveLeftmostNode(CBinaryNode<ItemType> *subTreePtr,
                                             ItemType &inorderSuccessor);
   
   /** This function returns a pointer to the node containing the given value,
       or nullptr if not found.
    @param treePtr: A pointer of CBinaryNode type for the root of the tree.
    @param target: A reference of ItemType type to find the node corresponding.
    @return  Returns a CBinaryNode pointer to the revised subtree. */

   CBinaryNode<ItemType>* FindNode(CBinaryNode<ItemType> *treePtr,
                                  const ItemType& target) const;

   CBinaryNode<ItemType>* FindParent(CBinaryNode<ItemType> *treePtr,
                                  const ItemType& target);
   

private:
   // =========================================================================
   //      Data Member
   // =========================================================================

   CBinaryNode<ItemType> *m_rootPtr;  
   
}; // end CBST

#include "CBST.tpp"

#endif  // CBST_HEADER
