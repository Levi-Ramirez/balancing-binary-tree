// ============================================================================
// File: main.cpp
// ============================================================================
// Programmer: Levi Ramirez
// Date: 12/13/2020
// Class: CSCI 133 ("Data Structures Using C++")
// Time: 7:00pm
// Instructor: Dr. Rodriguez
// Project: Project CBST
//
// Description:
//  This program works with the ADT CBST.  It allows the user to remove
//  and insert items (nodes) in the tree.
// ============================================================================

#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

#include "CBST.h"
#include "CPersonInfo.h"

// global constants
const int MAX_ITEMS = 30;

// function prototype
void Visit(CPersonInfo &item);

void VisitInt(int &item);

// ==== main ==================================================================
//
// ============================================================================

int main()
{
	CBST<int> treeExample;

	CBST<CPersonInfo> treeList;	   // create a tree list
	CPersonInfo people[MAX_ITEMS]; // allocate an array of CPersonInfo
	ifstream inFile("PersonBankInfo.txt");
	char header[256];
	int index;

	treeExample.Add(1);
	treeExample.Add(8);
	treeExample.Add(3);
	treeExample.Add(4);
	treeExample.Add(5);
	treeExample.Add(6);
	treeExample.Add(7);
	treeExample.Add(9);
	treeExample.Add(2);

	cout << "InorderTraverse before balance" << endl;
	treeExample.InorderTraverse(VisitInt);
	cout << endl;
	cout << "end of traverse";
	cout << endl;

	cout << "Height " << treeExample.GetHeight();
	cout << endl;

	cout << "Check if treeExample contains 3" << endl;
	cout << treeExample.Contains(3) << endl;

	cout << "Check if treeExample contains 9" << endl;
	cout << treeExample.Contains(9) << endl;

	cout << endl;

	treeExample.Remove(1);
	treeExample.Remove(4);
	treeExample.Remove(2);
	treeExample.Remove(3);
	treeExample.Remove(5);
	treeExample.Remove(9);

	cout << endl;
	cout << "Inorder:" << endl;
	treeExample.InorderTraverse(VisitInt);
	cout << endl;
	cout << "Preorder:" << endl;
	treeExample.PreorderTraverse(VisitInt);
	cout << endl;
	cout << "Postorder:" << endl;
	treeExample.PostorderTraverse(VisitInt);
	cout << endl;

	cout << "Check if it contians 4: ";
	cout << treeExample.Contains(4) << endl;

	if (inFile.fail())
	{
		cerr << "Error opening \"PersonBankInfo.txt\"...\n\n";
		exit(EXIT_FAILURE);
	}

	// Get rid of the header in the file ("First", "Last", ... , "Savings")
	inFile.getline(header, 256);

	// Read all the items in the file and store in a CPersonInfo array
	for (index = 0; index < MAX_ITEMS; ++index)
	{
		inFile >> people[index]; // usage of overloaded stream operator
	}

	// Add 20 items (CPersonInfo) to the treeList and remove them to test it.
	for (index = 0; index < 20; ++index)
	{
		treeList.Add(people[index]);
	}

	// Display the tree in order
	cout << "\n\nDisplaying in in-order\n\n";
	treeList.InorderTraverse(Visit);
	cout << endl;

	// Remove the first 10 items
	for (index = 0; index < 10; ++index)
	{
		treeList.Remove(people[index]);
	}

	cout << "\n\nDisplaying in in-order\n\n";
	treeList.InorderTraverse(Visit);
	cout << endl;
	// Display the tree Preorder
	cout << "Displaying in Pre-order\n\n";
	treeList.PreorderTraverse(Visit);
	cout << endl;

	// Display the tree Postorder
	cout << "Displaying in Post-order\n\n";
	treeList.PostorderTraverse(Visit);
	cout << endl;

	cout << "Test Overloaded Assignment operator\n\n";
	CBST<CPersonInfo> treeCopy;
	treeCopy = treeList;
	treeCopy.PostorderTraverse(Visit);

	try
	{
		treeList.GetRootData();
	}
	catch (PrecondViolatedExcept e)
	{
		cout << e.GetMsg();
	}
	// You may add more lines to test various other functions to your choosing.
	// Though this should get you started.

	return 0;

} // end of "main"

// ==== Visit =================================================================
//
// This function displays a CPersonInfo.
//
// Input:
//      item [in]   -- A pass by reference CPersonInfo object.
//
// Output:
//      void
//
// ============================================================================
void Visit(CPersonInfo &item)
{
	cout << item << endl; // usage of overloaded stream operator
}

// ==== VisitInt ==============================================================
//
// This function displays a int.
//
// Input:
//      item [in]   -- A pass by reference CPersonInfo object.
//
// Output:
//      void
//
// ============================================================================
void VisitInt(int &item)
{
	cout << item << endl; // usage of overloaded stream operator
}
