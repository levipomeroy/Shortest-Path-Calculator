#include <iostream>
using std::ostream;
/************************************************************************
* Class: Exception
*
* Purpose: This class manages exceptions and the message associated with
*		   each one, explaining the reason for the error.
*
* Manager functions:
* 	Exception ()
* 		The default msg is set to nullptr.
*	Exception (char * msg)
*		Assigns the m_msg to msg.
*	Exception (const Exception & copy)
*		Sets m_msg to copy.m_msg, using string copy.
*	operator= (const Exception & rhs)
*		Checks for self-assignment, and if not self assigned, sets m_msg
*		to copy.m_msg, using string copy.
*	~Exception()
*		Deletes m_msg and resets it to nullptr.
*
Methods:
*	GetMessage() const
*		Returns m_msg;
*	SetMessage(char * msg)
*		Sets m_msg to msg;
*	operator<<
*		Overloads the ouptut operator to allow simple output of an exception.
*************************************************************************/
#ifndef EXCEPTION_H
#define EXCEPTION_H

class Exception
{
private:
	char * m_msg;

public:
	Exception();	//Default constructor
	Exception(char * msg);	//Sets m_msg to msg
	Exception(const Exception & copy);	//Copy constructor
	~Exception();	//Destructor
	Exception & operator=(const Exception & rhs);	//Assignment operator
	const char * GetMessage() const;	//Gets m_msg
	void SetMessage(char * msg);	//Set m_msg to msg
	friend ostream & operator<< (ostream & stream, const Exception & except);	//Output operator
};

#endif;
