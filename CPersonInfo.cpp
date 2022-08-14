// ============================================================================
// File: CPersonInfo.cpp
// ============================================================================
// Implimentation file for the class CPersonInfo
// ============================================================================

#include <iostream>
using namespace std;
#include "CPersonInfo.h"

// =========================================================================
//      Constructors and Destructor
// =========================================================================

// ==== Default Constructor ===================================================
//
// Initializes the strings to an empty string and all ints to 0.
//
// Input:
//		nothing
//
// Output:
//		nothing
//
// ============================================================================
CPersonInfo::CPersonInfo() : m_fname(" "), m_lname(" "), m_age(0), m_checking(0),
							 m_savings(0)
{
	
}



// ==== Type Constructor ======================================================
//
// Initializes the strings with their first and last name and sets all ints
// to 0 as default arguments.
//
// Input:
//		nothing
//
// Output:
//		nothing
//
// ============================================================================
CPersonInfo::CPersonInfo(const string &fname, const string &lname,
            int age, double checking, double savings): m_fname(fname),
            m_lname(lname), m_age(age), m_checking(checking),
            m_savings(savings)
{
 	
}



// ==== SetFirstName ==========================================================
//
// Sets the first name of the class private data member
//
// Input:
//		fname	[IN]:  A string (passed by reference) to update m_fname.
//
// Output:
//		nothing
//
// ============================================================================
void CPersonInfo::SetFirstName(const string &fname)
{
   	m_fname = fname;
}



// ==== SetLastName ===========================================================
//
// Sets the last name of the class private data member
//
// Input:
//		lname	[IN]:  A string (passed by reference) to update m_lname.
//
// Output:
//		nothing
//
// ============================================================================
void CPersonInfo::SetLastName(const string &lname)
{
   	m_lname = lname;
}



// ==== SetAge ================================================================
//
// Sets the age of the class private data member
//
// Input:
//		age	[IN]:  An int to update m_age.
//
// Output:
//		nothing
//
// ============================================================================
void CPersonInfo::SetAge(int age)
{
   	m_age = age;
}



// ==== SetChecking ===========================================================
//
// Sets the age of the class private data member
//
// Input:
//		checking	[IN]:  A double to update m_checking.
//
// Output:
//		nothing
//
// ============================================================================
void CPersonInfo::SetChecking(double checking)
{
   	m_checking = checking;
}



// ==== SetSavings ============================================================
//
// Sets the savings of the class private data member
//
// Input:
//		savings	[IN]:  A double to update m_savings.
//
// Output:
//		nothing
//
// ============================================================================
void CPersonInfo::SetSavings(double savings)
{
   	m_savings = savings;
}



// ==== GetFirstName ==========================================================
//
// Sets the first of the class private data member
//
// Input:
//		nothing
//
// Output:
//		string  -  first name data member
//
// ============================================================================
string CPersonInfo::GetFirstName() const
{
   	return m_fname;
}



// ==== GetLastName ==========================================================
//
//  Returns the last name of the class private data member
//
// Input:
//		nothing
//
// Output:
//		string  -  last name data member
//
// ============================================================================/
string CPersonInfo::GetLastName() const
{
   	return m_lname;
}



// ==== GetAge ================================================================
//
//  Returns the last name of the class private data member
//
// Input:
//		nothing
//
// Output:
//		int  -  data member representing age
//
// ============================================================================
int CPersonInfo::GetAge() const
{
   	return m_age;
}



// ==== GetChecking ===========================================================
//
//  Returns the age of the class private data member
//
// Input:
//		nothing
//
// Output:
//		double  -  data member representing checking
//
// ============================================================================
double CPersonInfo::GetChecking() const
{
   	return m_checking;
}



// ==== GetSavings ============================================================
//
//  Returns the savings amount of the class private data member
//
// Input:
//		nothing
//
// Output:
//		double  -  data member representing saving
//
// ============================================================================
double CPersonInfo::GetSavings() const
{
   	return m_savings;
}



// ============================================================================
//      Overloaded operators
// ============================================================================


   
// ==== Overloaded Equality Operator ==========================================
//
//  Checks if two CPersonInfo classes are exactly the same.
//
// Input:
//		rhs	[IN]: const reference to a CPersonInfo object
//
// Output:
//		bool  -  True if they are the same, false otherwise.
//
// ============================================================================
bool CPersonInfo::operator==(const CPersonInfo &rhs)
{
	if (m_fname == rhs.GetFirstName() && m_lname == rhs.GetLastName() &&
        m_age == rhs.GetAge() && m_checking == rhs.GetChecking() &&
   		m_savings == rhs.GetSavings())
   	{
   		return true;
   	}
	else
	{
		return false;
	}
}



// ==== Overloaded Relational Operator ========================================
//
//  Checks which CPersonInfo class is greater. For our case, we will
//  distinguish what is greater by the m_age private data member.
//
// Input:
//		rhs	[IN]: const reference to a CPersonInfo object
//
// Output:
//		bool  -  True if it is greater, false otherwise.
//
// ============================================================================
bool CPersonInfo::operator>(const CPersonInfo &rhs)
{
   	if (m_age > rhs.GetAge())
   	{
   		return true;
   	}
	else
	{
		return false;
	}
}



// ==== Overloaded Relational Operator ========================================
//
//  Checks which CPersonInfo class is lesser. For our case, we will
//  distinguish what is lesser by the m_age private data member.
//
// Input:
//		rhs	[IN]: const reference to a CPersonInfo object
//
// Output:
//		bool  -  True if it is greater, false otherwise.
//
// ============================================================================
bool CPersonInfo::operator<(const CPersonInfo &rhs)
{
  	if (m_age < rhs.GetAge())
   	{
   		return true;
   	}
   	else
   	{
   		return false;
   	}
}



// =========================================================================
//      Overloaded stream operators prototypes
// =========================================================================

// ==== Overloaded Istream Operator ===========================================
//
//  Overloads the extraction operator to extract a CPersonInfo object.
//
// Input:
//		person	[IN]: const reference to a CPersonInfo object
//		ins	[IN]: An input reference stream.
//
// Output:
//		An input reference stream
//
// ============================================================================
std::istream& operator>>(std::istream &ins, CPersonInfo &person)
{
	std::string name;
	ins >> name;
	person.SetFirstName(name);

	ins >> name;
	person.SetLastName(name);

	int age;
	ins >> age;
	person.SetAge(age);

	double checking;
	ins >> checking;
	person.SetChecking(checking);

	double savings;
	ins >> savings;
	person.SetSavings(savings);

	return ins;
}



// ==== Overloaded Ostream Operator ===========================================
//
//  Overloads the insertion operator to display a CPersonInfo object.
//
// Input:
//		outs	[IN]: An output reference stream.
//		person	[IN]: A reference to a CPersonInfo object.
//
// Output:
//		An output reference stream.
//
// ============================================================================
std::ostream& operator<<(std::ostream &outs, const CPersonInfo &person)
{
	outs << "First Name: " << person.GetFirstName() << endl;
	outs << "Last Name: " << person.GetLastName() << endl;
	outs << "Age: " << person.GetAge() << endl;
	outs << "Checking: " << person.GetChecking() << endl;
	outs << "Savings: " << person.GetSavings() << endl;

	return outs;
}
