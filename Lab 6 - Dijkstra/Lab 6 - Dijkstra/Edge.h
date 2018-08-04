/************************************************************************
* Class: Edge
*
* Purpose: This class holds and manages the data associated with an edge
*		   between 2 vertices.
*
*Manager functions
*	Edge()
*		Sets weight to 0 and destination to nullptr
*	Edge(Vertex<V, E> *dest, E data, int weight)
*		Sets m_dest to dest, m_data to data, and m_weight to weight
*	~Edge()
*		Returns data members to default values
*	Edge(const Edge<V, E> & copy)
*		Calls op= to handle the assignment of the copy.
*	operator=(const Edge<V, E> & rhs)
*		Sets this to rhs, and all of its data members
*
* Methods:
* 	GetWeight()
*		Returns the weight of the edge, the distance
*	GetData()
*		Returns the data of the edge.
*	GetDestination()
*		Returns the vertex that the edge points too.
*	SetDestination()
*		Sets the destination of the edge.
*************************************************************************/
#pragma once
#ifndef EDGE_H	
#define EDGE_H
template <typename V, typename E>
class Vertex;

template <typename V, typename E>
class Edge
{
public:
	Edge();
	Edge(Vertex<V, E> *dest, E data, int weight);
	~Edge();
	Edge(const Edge<V, E> & copy);
	const Edge<V, E> & operator=(const Edge<V, E> & rhs);

	int GetWeight();
	E GetData();
	Vertex<V, E>* GetDestination();
	void SetDestination(Vertex<V, E> *dest);

private:
	int m_weight;
	E m_data;
	Vertex<V, E>* m_dest;
};
#endif

/**********************************************************************
* Purpose: This function sets m_weight to 0 and m_dest to nullptr
*
* Precondition:	members were unassigned.
*
* Postcondition: members are assigned to default values.
************************************************************************/
template<typename V, typename E>
inline Edge<V, E>::Edge() : m_weight(0), m_dest(nullptr)
{
}

/**********************************************************************
* Purpose: This function sets m_dest to dest, m_data to data, and m_weight
*			weight.
*
* Precondition:	members were unassigned.
*
* Postcondition: members are assigned to passed in values.
************************************************************************/
template<typename V, typename E>
inline Edge<V, E>::Edge(Vertex<V, E> *dest, E data, int weight) : m_dest(dest), m_weight(weight), m_data(data)
{
}

/**********************************************************************
* Purpose: This function sets members to default values.
*
* Precondition:	members may be assigned.
*
* Postcondition: members are assigned to default values.
************************************************************************/
template<typename V, typename E>
inline Edge<V, E>::~Edge()
{
	m_weight = 0;
	m_dest = nullptr;
}

/**********************************************************************
* Purpose: This function calls op= to handle the assignment of the copy.
*
* Precondition:	copy's members were unassigned.
*
* Postcondition: copy's members are assigned.
************************************************************************/
template<typename V, typename E>
inline Edge<V, E>::Edge(const Edge<V, E>& copy)
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
inline const Edge<V, E>& Edge<V, E>::operator=(const Edge<V, E>& rhs)
{
	if (this != &rhs)
	{
		m_dest = rhs.m_dest;
		m_data = rhs.m_data;
		m_weight = rhs.m_weight;
	}
	return *this;
}

/**********************************************************************
* Purpose: This function returns the weight of the edge.
*
* Precondition:	N/A
*
* Postcondition: The weight of the edge is accessable.
************************************************************************/
template<typename V, typename E>
inline int Edge<V, E>::GetWeight()
{
	return m_weight;
}

/**********************************************************************
* Purpose: This function returns the data of the edge.
*
* Precondition:	N/A
*
* Postcondition: The data of the edge is accessable.
************************************************************************/
template<typename V, typename E>
inline E Edge<V, E>::GetData()
{
	return m_data;
}

/**********************************************************************
* Purpose: This function returns the destination of the edge.
*
* Precondition:	N/A
*
* Postcondition: The destination of the edge is accessable.
************************************************************************/
template<typename V, typename E>
inline Vertex<V, E>* Edge<V, E>::GetDestination()
{
	return m_dest;
}

/**********************************************************************
* Purpose: This function sets the destination of the edge.
*
* Precondition:	N/A
*
* Postcondition: The destination of the edge is set.
************************************************************************/
template<typename V, typename E>
inline void Edge<V, E>::SetDestination(Vertex<V, E> *dest)
{
	m_dest = dest;
}
