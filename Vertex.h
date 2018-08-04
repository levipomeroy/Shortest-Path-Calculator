/************************************************************************
* Class: Vertex
*
* Purpose: This class holds and manages the data associated with a vertex, 
*		   to be used within a graph.
*
* Manager functions
*	Vertex()
*		Sets m_processed to false and clears the list of edges.
*	~Vertex()
*		Returns data members to default values
*	Vertex(const Vertex<V, E> & copy)
*		Calls op= to handle the assignment of the copy.
*	operator=(const Vertex<V, E> & rhs)
*		Sets this to rhs, and all of its data members
*
* Methods:
* 	GetData()
*		Returns the data in a vertex
*	GetProcessed()
*		Returns whether or not the vertex has been processed.
*	SetProcessed(bool process)
*		Sets the processed status.
*	GetEdges()
*		Returns a list of edges that are attached to the vertex.
*************************************************************************/
#include "Edge.h"
#include <list>
using std::list;

#pragma once
#ifndef  VERTEX_H
#define VERTEX_H

template<typename V, typename E>
class Vertex
{
public:
	Vertex();
	Vertex(V data);
	~Vertex();
	Vertex(const Vertex<V, E> & copy);
	const Vertex<V, E> & operator=(const Vertex<V, E> & rhs);

	V GetData();
	bool GetProcessed();
	void SetProcessed(bool process);
	list<Edge<V, E>> & GetEdges();

private:
	V m_data;
	bool m_processed;
	list<Edge<V, E>> m_edges;
};
#endif 

/**********************************************************************
* Purpose: This function sets m_processed to false and clears m_edges.
*
* Precondition:	members were unassigned.
*
* Postcondition: members are assigned to default values.
************************************************************************/
template<typename V, typename E>
inline Vertex<V, E>::Vertex() : m_processed(false)
{
	m_edges.clear();
}

/**********************************************************************
* Purpose: This function sets m_processed to false and clears m_edges,
*		   and sets m_data to data.
*
* Precondition:	members were unassigned.
*
* Postcondition: members are assigned.
************************************************************************/
template<typename V, typename E>
inline Vertex<V, E>::Vertex(V data) : m_data(data), m_processed(false)
{
	m_edges.clear();
}

/**********************************************************************
* Purpose: This function sets members to default values.
*
* Precondition:	members may be assigned.
*
* Postcondition: members are assigned to default values.
************************************************************************/
template<typename V, typename E>
inline Vertex<V, E>::~Vertex()
{
	m_processed = false;	//reset to default
	m_edges.clear();
}

/**********************************************************************
* Purpose: This function calls op= to handle the assignment of the copy.
*
* Precondition:	copy's members were unassigned.
*
* Postcondition: copy's members are assigned.
************************************************************************/
template<typename V, typename E>
inline Vertex<V, E>::Vertex(const Vertex<V, E>& copy)
{
	*this = copy;
}

/**********************************************************************
* Purpose: This function sets this's members to rhs's members
*
* Precondition:	rhs members were unassigned.
*
* Postcondition: rhs members are assigned.
************************************************************************/
template<typename V, typename E>
inline const Vertex<V, E>& Vertex<V, E>::operator=(const Vertex<V, E>& rhs)
{
	if (this != &rhs)
	{
		m_processed = rhs.m_processed;
		m_data = rhs.m_data;
		m_edges = rhs.m_edges;
	}
	return *this;
}

/**********************************************************************
* Purpose: This function returns the data of the vertex
*
* Precondition:	N/A
*
* Postcondition: data of the vertex is returned.
************************************************************************/
template<typename V, typename E>
inline V Vertex<V, E>::GetData()
{
	return m_data;
}

/**********************************************************************
* Purpose: This function returns the processed status of the vertex
*
* Precondition:	N/A
*
* Postcondition: The processed status of the vertex is returned.
************************************************************************/
template<typename V, typename E>
inline bool Vertex<V, E>::GetProcessed()
{
	return m_processed;
}

/**********************************************************************
* Purpose: This function sets the processed status of the vertex
*
* Precondition:	N/A
*
* Postcondition: The processed status of the vertex is set to passed value.
************************************************************************/
template<typename V, typename E>
inline void  Vertex<V, E>::SetProcessed(bool process)
{
	m_processed = process;
}

/**********************************************************************
* Purpose: This function returns the list of edges connected to vertex.
*
* Precondition:	N/A
*
* Postcondition: The list of edges of the vertex is returned.
************************************************************************/
template<typename V, typename E>
inline list<Edge<V, E>> & Vertex<V, E>::GetEdges()
{
	return m_edges;
}
