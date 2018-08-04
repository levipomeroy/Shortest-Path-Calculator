/************************************************************************
* Class: Graph
*
* Purpose: This class has a list of vertices, which holds a list of edges.
*		   It allows access to and manages the graphs data.
*
* Manager functions
*	Graph()
*		Sets m_count to 0 and clears the list of vertices.
*	~Graph()
*		Returns data members to default values
*	Graph(const Graph<V, E> & copy)
*		Calls op= to handle the assignment of the copy.
*	operator=(const Graph<V, E> & rhs)
*		Sets this to rhs, and all of its data members
*
* Methods:
* 	InsertVertex(V data)
*		Inserts a vertex into the graph.
*	RemoveVertex(V data)
*		Removes a vertex from the graph.
*	IsEmpty()
*		Returns whether or npt he graph is empty.
*	Reset()
*		Resets all the verices processed status to false.
*	GetVertices()
*		Returns the list of vertices in the graph.
*	PrintGraph()
*		Prints some attributes of the graph, mainly for testing.
*	AddEdge(V from, V to, E data, int weight)
*		Adds an edge between two vertices.
*	RemoveEdge(V from, V to)
*		Removes an edge between two vertices.
*	DepthFirst(void(*visit)(V data))
*		Traverses the graph by depth first order.
*	BreadthFirst(void(*visit)(V data))
*		Traverses the graph by breadthfirst order.
*************************************************************************/
#include <list>
#include <stack>
#include <queue>
#include "Vertex.h"
#include "Exception.h"
using std::iterator;
using std::list;
using std::stack;
using std::queue;
using std::iterator;

#pragma once
#ifndef GRAPH_H
#define GRAPH_H

template <typename V, typename E>
class Graph
{
public:
	Graph();
	~Graph();
	Graph(Graph<V, E> & copy);
	const Graph<V, E> & operator=(Graph<V, E> & rhs);

	void InsertVertex(V data);
	void RemoveVertex(V data);
	bool IsEmpty();
	void Reset();
	list<Vertex<V, E>> & GetVertices();
	void PrintGraph();
	void AddEdge(V from, V to, E data, int weight);
	void RemoveEdge(V from, V to);
	const int GetCount();

	void DepthFirst(void(*visit)(V data));
	void BreadthFirst(void(*visit)(V data));

private:
	list<Vertex<V, E>> m_vertices;	//List of vertices
	int m_count;	//Count of vertices
};
#endif

/**********************************************************************
* Purpose: This function sets m_count to 0 and clears the list of vertices.
*
* Precondition:	members were unassigned.
*
* Postcondition: members are assigned to default values.
************************************************************************/
template<typename V, typename E>
inline Graph<V, E>::Graph() : m_count(0)
{
	m_vertices.clear();
}

/**********************************************************************
* Purpose: This function sets members to default values.
*
* Precondition:	members may be assigned.
*
* Postcondition: members are assigned to default values.
************************************************************************/
template<typename V, typename E>
inline Graph<V, E>::~Graph()
{
	m_vertices.clear();
	m_count = 0;
}

/**********************************************************************
* Purpose: This function calls op= to handle the assignment of the copy.
*
* Precondition:	copy's members were unassigned.
*
* Postcondition: copy's members are assigned.
************************************************************************/
template<typename V, typename E>
inline Graph<V, E>::Graph(Graph<V, E>& copy)
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
inline const Graph<V, E>& Graph<V, E>::operator=(Graph<V, E> & rhs)
{
	if (this != &rhs)
	{
		m_vertices.clear();

		m_vertices.clear();
		Vertex<V, E> * temp = nullptr;
		Edge<V, E> * edge_temp = nullptr;
		list<Vertex<V, E>>::iterator viter;
		list<Edge<V, E>>::iterator eiter;

		for (viter = rhs.m_vertices.begin(); viter != rhs.m_vertices.end(); ++viter)
		{
			temp = &(*viter);
			InsertVertex(temp->GetData());
		}

		for (viter = rhs.m_vertices.begin(); viter != rhs.m_vertices.end(); ++viter)
		{
			temp = &(*viter);
			for (eiter = temp->GetEdges().begin(); eiter != temp->GetEdges().end();++eiter)
			{
				edge_temp = &(*eiter);
				AddEdge(temp->GetData(), edge_temp->GetDestination()->GetData(), edge_temp->GetData(), edge_temp->GetWeight());
			}
		}
		m_count = rhs.m_count;
	}
	return *this;
}

/**********************************************************************
* Purpose: This function inserts a vertex into the graph.
*
* Precondition:	N/A
*
* Postcondition: Vertex is in the graph, graphs size goes up one.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::InsertVertex(V data)
{
	Vertex<V, E> * temp = nullptr;
	list<Vertex<V, E>>::iterator viter;
	bool already_exists = false;
	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetData() == data)
		{
			already_exists = true;
		}
	}
	if (already_exists == false)
	{
		m_vertices.push_back(Vertex<V, E>(data));
		m_count = m_vertices.size();	//Increase count of vertices
	}
}

/**********************************************************************
* Purpose: This function removes a vertex from the graph.
*
* Precondition:	Vertex is in graph.
*
* Postcondition: Vertex is not in the graph, graphs size goes down one.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::RemoveVertex(V data)
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}

	bool found = false;
	Vertex<V, E> * temp = nullptr;
	Edge<V, E> * edge_temp = nullptr;
	list<Edge<V, E>>::iterator eiter;
	Vertex<V, E> * vto = nullptr;

	for (list<Vertex<V, E>>::iterator viter = m_vertices.begin(); found != true && viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);

		eiter = temp->GetEdges().begin();
		while (eiter != temp->GetEdges().end())
		{
			edge_temp = &(*eiter);

			if (edge_temp->GetDestination()->GetData() == data)
			{
				temp->GetEdges().erase(eiter);
				eiter = temp->GetEdges().begin(); //reset iter
			}

			++eiter;

		}
		if (temp->GetData() == data)
		{
			found = true;
			temp->GetEdges().clear();	//Clear all edges out of list
			m_vertices.erase(viter);	//Remove vertex from list
			viter = m_vertices.begin();
		}
	}

	if (found == false)
	{
		throw Exception("Unable to find vertex to delete");
	}
	m_count = m_vertices.size();	//Increase count of vertices
}

/**********************************************************************
* Purpose: This function returns whether or not the graph is empty.
*
* Precondition:	N/A.
*
* Postcondition: The empty status is returned.
************************************************************************/
template<typename V, typename E>
inline bool Graph<V, E>::IsEmpty()
{
	bool empty = false;
	if (m_vertices.size() == 0)
	{
		empty = true;
	}
	return empty;
}

/***********************************************************************
* Purpose: This function resets the processed status of each vertex to false.
*
* Precondition:	Processed status may be set.
*
* Postcondition: Processed status of each vertex is reset to false.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::Reset()
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}

	Vertex<V, E> * temp = nullptr;
	for (list<Vertex<V, E>>::iterator viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		temp->SetProcessed(false);
	}
}

/**********************************************************************
* Purpose: This function returns the list of vertices contained in the graph.
*
* Precondition:	N/A.
*
* Postcondition: The list of vertices is returned.
************************************************************************/
template<typename V, typename E>
inline list<Vertex<V, E>> &Graph<V, E>::GetVertices()
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}
	return m_vertices;
}

/**********************************************************************
* Purpose: This function prints some aspects of the graph, mainly for testing.
*
* Precondition:	N/A.
*
* Postcondition: The graph is printed.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::PrintGraph()
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}

	Vertex<V, E> * temp = nullptr;
	list<Vertex<V, E>>::iterator viter;
	int i = 1;
	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &*viter;
		cout << "*********vertex #" << i << " *********" << endl;
		cout << "Data: " << temp->GetData() << endl;
		cout << "Number of edges: " << temp->GetEdges().size() << endl;
		cout << "Processed: ";
		if (temp->GetProcessed() == 1)
		{
			cout << "true" << endl;
		}
		else
		{
			cout << "false" << endl;
		}
		i++;
	}
}

/**********************************************************************
* Purpose: This function adds an edge to the graph between two vertices.
*
* Precondition:	N/A.
*
* Postcondition: The edge is added.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::AddEdge(V from, V to, E data, int weight)
{
	Vertex<V, E> * vfrom = nullptr;
	Vertex<V, E> * vto = nullptr;
	bool found = false;

	Vertex<V, E> * temp = nullptr;
	list<Vertex<V, E>>::iterator viter;
	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetData() == from)
		{
			vfrom = temp;
			found = true;
		}
	}

	temp = nullptr;
	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetData() == to)
		{
			vto = temp;
			found = true;
		}
	}

	if (found == false)
	{
		throw Exception("Unable to add edge; vertex was not found!");
	}
	vfrom->GetEdges().push_back(Edge<V, E>(vto, data, weight));	//Add it to list of edges for the given vertex
	vto->GetEdges().push_back(Edge<V, E>(vfrom, data, weight));
}

/**********************************************************************
* Purpose: This function removes an edge from the graph between two vertices.
*
* Precondition:	N/A.
*
* Postcondition: The edge is removed.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::RemoveEdge(V from, V to)
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}

	Vertex<V, E> * vfrom = nullptr;
	Vertex<V, E> * vto = nullptr;
	bool found_from = false;
	bool found_to = false;

	Vertex<V, E> * temp = nullptr;
	list<Vertex<V, E>>::iterator viter;
	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetData() == from)
		{
			vfrom = temp;
			found_from = true;
		}
	}

	Edge<V, E> * edge_temp = nullptr;
	list<Edge<V, E>>::iterator eiter;
	for (eiter = vfrom->GetEdges().begin(); found_to != true && eiter != vfrom->GetEdges().end(); ++eiter)
	{
		edge_temp = &(*eiter);
		if (edge_temp->GetDestination()->GetData() == to)
		{
			found_to = true;
			vto = edge_temp->GetDestination();
			if (found_from == true && found_to == true)
			{
				vfrom->GetEdges().erase(eiter);
				eiter = vfrom->GetEdges().begin(); //reset iter
			}
		}
	}

	edge_temp = nullptr;
	found_to = false;
	eiter = vto->GetEdges().begin();
	while (vto->GetEdges().size() >= 1 && found_to != true && eiter != vto->GetEdges().end())
	{
		edge_temp = &(*eiter);

		if (edge_temp->GetDestination()->GetData() == from)
		{
			found_to = true;
			if (found_from == true && found_to == true)
			{
				vto->GetEdges().erase(eiter);
				eiter = vto->GetEdges().end(); //reset iter
			}
		}
		if (vto->GetEdges().size() >= 1)
		{
			++eiter;
		}
	}

	if (found_from != true || found_to != true)
	{
		throw Exception("Unable to remove edge; vertex was not found!");
	}
}

/**********************************************************************
* Purpose: This function returns the count, size of the graph.
*
* Precondition:	N/A.
*
* Postcondition: The size is returned.
************************************************************************/
template<typename V, typename E>
inline const int Graph<V, E>::GetCount()
{
	return m_count;
}

/**********************************************************************
* Purpose: This function traverses the graph in depth first order.
*
* Precondition:	N/A.
*
* Postcondition: N/A.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::DepthFirst(void(*visit)(V data))
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}

	stack<Vertex<V, E>*> vstack;
	Vertex<V, E> * temp = nullptr;
	list<Vertex<V, E>>::iterator viter;
	list<Edge<V, E>>::iterator eiter;

	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		vstack.push(temp);	//Push vertex on stack

		while (vstack.size() != 0)
		{
			temp = vstack.top();
			vstack.pop();	//Pop top of stack

			if (temp->GetProcessed() == false)
			{
				visit(temp->GetData());
				temp->SetProcessed(true);

				Edge<V, E> * edge_temp = nullptr;
				eiter = temp->GetEdges().begin();
				while (temp->GetEdges().size() >= 1 && eiter != temp->GetEdges().end())
				{
					edge_temp = &(*eiter);
					if (edge_temp->GetDestination()->GetProcessed() == false)
					{
						vstack.push(edge_temp->GetDestination());
					}
					++eiter;
				}
			}
		}
	}
	Reset();	//Reset processed flags for each vertex in graph
}

/**********************************************************************
* Purpose: This function traverses the graph in breadth first order.
*
* Precondition:	N/A.
*
* Postcondition: N/A.
************************************************************************/
template<typename V, typename E>
inline void Graph<V, E>::BreadthFirst(void(*visit)(V data))
{
	if (IsEmpty())
	{
		throw Exception("Graph is empty");
	}

	queue<Vertex<V, E>*> vqueque;
	Vertex<V, E> * temp = nullptr;
	list<Vertex<V, E>>::iterator viter;
	list<Edge<V, E>>::iterator eiter;

	for (viter = m_vertices.begin(); viter != m_vertices.end(); ++viter)
	{
		temp = &(*viter);
		vqueque.push(temp);	//Push vertex on stack

		while (vqueque.size() != 0)
		{
			temp = vqueque.front();
			vqueque.pop();	//Pop top of stack

			if (temp->GetProcessed() == false)
			{
				visit(temp->GetData());
				temp->SetProcessed(true);

				Edge<V, E> * edge_temp = nullptr;
				eiter = temp->GetEdges().begin();
				while (temp->GetEdges().size() >= 1 && eiter != temp->GetEdges().end())
				{
					edge_temp = &(*eiter);
					if (edge_temp->GetDestination()->GetProcessed() == false)
					{
						vqueque.push(edge_temp->GetDestination());
					}
					++eiter;
				}
			}
		}
	}
	Reset();	//Reset processed flags for each vertex in graph
}
