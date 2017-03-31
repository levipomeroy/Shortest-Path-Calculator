#include "Exception.h"
/*************************************************************
* Author:		Levi Pomeroy
* Filename:		Exception.cpp
* Date Created:	1/10/17
* Modifications:	1/12/17 – Fixed ctors to allocate room for message
**************************************************************\

/**********************************************************************
* Purpose: This function initialized m_msg to nullptr.
*
* Precondition:	m_msg was unassigned.
*
* Postcondition: m_msg is set to nullptr.
************************************************************************/
Exception::Exception() :m_msg(nullptr)
{
}

/**********************************************************************
* Purpose: This function initialized m_msg to msg, using strcpy.
*
* Precondition:	m_msg was unassigned.
*
* Postcondition: m_msg is set to msg.
************************************************************************/
Exception::Exception(char * msg) : m_msg(msg)
{
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

/**********************************************************************
* Purpose: This function sets m_msg to copy.m_msg, using strcpy.
*
* Precondition:	m_msg was unassigned.
*
* Postcondition: m_msg is set to copy.m_msg.
************************************************************************/
Exception::Exception(const Exception & copy)
{
	m_msg = new char[strlen(copy.m_msg) + 1];
	strcpy(m_msg, copy.m_msg);
}

/**********************************************************************
* Purpose: This function deletes m_msg and resets it to nullptr.
*
* Precondition:	m_msg was not deleted, and was not nessecarrily set to nullptr.
*
* Postcondition: m_msg is deleted and is reset to nullptr.
************************************************************************/
Exception::~Exception()
{
	delete[] m_msg;
	m_msg = nullptr;
}

/**********************************************************************
* Purpose: This function sets m_msg to rhs.m_msg, using strcpy.
*
* Precondition:	m_msg was unassigned.
*
* Postcondition: m_msg is set to rhs.m_msg.
************************************************************************/
Exception & Exception::operator=(const Exception & rhs)
{
	if (this != &rhs)
	{
		m_msg = new char[strlen(rhs.m_msg) + 1];
		strcpy(m_msg, rhs.m_msg);
	}
	return *this;
}
/**********************************************************************
* Purpose: This function returns m_msg.
*
* Precondition:	m_msg was unavailable.
*
* Postcondition: m_msg is available.
************************************************************************/
const char * Exception::GetMessage() const
{
	return m_msg;
}

/**********************************************************************
* Purpose: This function sets m_msg to msg, using strcpy
*
* Precondition:	m_msg was unchanged.
*
* Postcondition: m_msg is set to msg.
************************************************************************/
void Exception::SetMessage(char * msg)
{
	m_msg = new char[strlen(msg) + 1];
	strcpy(m_msg, msg);
}

/**********************************************************************
* Purpose: This function overloads the ouput operator, for simple output
*		   of an exception.
*
* Precondition:	An exception cannot be explictly outputted.
*
* Postcondition: An exception can be explictly outputted.
************************************************************************/
ostream & operator<<(ostream & stream, const Exception & except)
{
	return stream << except.m_msg;
}
