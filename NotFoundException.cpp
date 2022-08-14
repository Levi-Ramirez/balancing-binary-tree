// ============================================================================
// File: NotFoundException.cpp
// ============================================================================
// Implementation file for the class NotFoundException
// ============================================================================

#include <iostream>
using namespace std;
#include "NotFoundException.h"


// ==== Type Constructor ======================================================
//
// Initializes the error message from a string input
//
// Input:
//		errorMsg	[IN]  -  string representing the error mesage
//
// Output:
//		nothing
//
// ============================================================================
NotFoundException::NotFoundException(std::string errorMsg)
{
	m_errorMsg = errorMsg;
}



// ==== GetMsg ================================================================
//
// Returns the error message as a string
//
// Input:
//		nothing
//
// Output:
//		string  -  returns the error message
//
// ============================================================================
std::string	NotFoundException::GetMsg() const
{
	return m_errorMsg;
}



// ==== SetMsg ================================================================
//
// Initializes the error message from a string input
//
// Input:
//		errorMsg	[IN]  -  string representing the error mesage
//
// Output:
//		nothing
//
// ============================================================================
void NotFoundException::SetMsg(std::string errorMsg)
{
 	m_errorMsg = errorMsg;
}
