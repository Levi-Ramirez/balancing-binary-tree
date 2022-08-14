// ============================================================================
// File: PrecondViolatedExcept.cpp
// ============================================================================
// Header file for the class PrecondViolatedExcept
// ============================================================================

#include <iostream>
using namespace std;
#include "PrecondViolatedExcept.h"


// ==== Default Constructor ===================================================
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
PrecondViolatedExcept::PrecondViolatedExcept(std::string errorMsg)
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
std::string PrecondViolatedExcept::GetMsg() const
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
void PrecondViolatedExcept::SetMsg(std::string	errorMsg)
{
	m_errorMsg = errorMsg;
}
