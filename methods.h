/*************************************************************
* Author:		Levi Pomeroy
* Filename:		Methods.h
* Date Created:	3/8/17
* Modifications:	3/8/17 – Fixed populate graph 
*					3/8/17 - Added print funtions
*					3/9/17 - Fixed, so works with mutiple.
**************************************************************/
#include <iostream>
#include <vector>
#include <climits>
#include <crtdbg.h>
#include "Graph.h"
#include<fstream>
#include <string>
using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::ifstream;
using std::vector;
using std::string;
using std::ios;

void ReadLine(string edgeInfo[][4]);	//Reads text file

template <typename V, typename E>
void PopulateGraph(string edgeInfo[][4], Graph<V, E> & graph);	//Fill graph with data

template <typename V, typename E>
void Dijkstra(Graph<V, E> & graph);	//Calculate the min distance

template <typename V, typename E>
int GetIndex(Graph<V, E> & graph, V data);	//Finds index of vertex to be used in array

template <typename V, typename E>
void FindNext(int distance[], Graph<V, E> & graph, Vertex<V, E> & cur);	//Finds the next vertex to be processed

template <typename V, typename E>
void SetProcessed(Graph<V, E> & graph,Vertex<V,E> cur);	//Sets the vertex to processed

template <typename V, typename E>
bool Done(Graph<V, E> & graph);	//Returns whether or not the graph is done being processed

template <typename V, typename E>
void DistanceAndPath(Graph<V, E> & graph, Vertex<V, E> end, int dist[], V pred[]);	//Prints the distance, path and time from a to b

/////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************
* Purpose: This function reads the text file and tokenizes it, and stores
*		   it in a 2d array.
*
* Precondition:	Text file is unread or processed.
*
* Postcondition: Text file is read and processed.
************************************************************************/
void ReadLine(string edgeInfo[][4])
{
	ifstream in;
	string token = "\0";
	string delimeter = ",";
	int first_index = 0;

	in.open("new.txt", ios::in);	//Open file fore reading

	if (in.is_open())	//if its opened
	{
		while (in.good())
		{
			if (getline(in, token))	//Get a whole line
			{
				size_t pos = 0;
				string temp = "\0";
				int count = 0;
				while ((pos = token.find(delimeter)) != string::npos)	//Seperate line by commas
				{
					temp = token.substr(0, pos);
					edgeInfo[first_index][count] = temp;	//Store it
					token.erase(0, pos + delimeter.length());
					count++;
				}
				edgeInfo[first_index][3] = token;
			}
			first_index++;
		}
		in.close();	//close file
	}
	else
	{
		throw Exception("Error opening file!");
	}
}

/**********************************************************************
* Purpose: This function populates the graph with the 2d array of info
*		   read in from the text file.
*
* Precondition:	Graph is empty.
*
* Postcondition: Graph is full of info from text file.
************************************************************************/
template<typename V, typename E>
void PopulateGraph(string edgeInfo[][4], Graph<V, E> & graph)
{
	for (int i = 0; i < 47; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				graph.InsertVertex(edgeInfo[i][j]);	//Add first vertex
			}
			else if (j == 1)
			{
				graph.InsertVertex(edgeInfo[i][j]);	//Add second vertex
			}
			else if (j == 2)
			{
				graph.AddEdge(edgeInfo[i][j - 2], edgeInfo[i][j - 1], edgeInfo[i][j], stoi(edgeInfo[i][j + 1]));	//Add edge between them
			}
		}
	}
}

/**********************************************************************
* Purpose: This function reads the graph and calculates the minimium 
*		   distance from the starting vertex to every other vertex in
*		   the graph.
*
* Precondition:	N/A
*
* Postcondition: Minimium distance from starting node to other nodes is
*				 calculated.
************************************************************************/
template<typename V, typename E>
void Dijkstra(Graph<V, E> & graph)
{
	if (graph.GetCount() == 0)
	{
		throw Exception("Graph is empty");
	}

	const int SIZE = graph.GetCount();	//Size of graph
	int * distance = new int[SIZE];		//Arrays size of number of vetices in graph
	V * pred = new V[SIZE];				//Holds the predessors of each vertex
	string start;
	string end;

	for (int i = 0; i < SIZE; i++)	//Initialize everything to negative one
	{
		distance[i] = -1;
		pred[i] = "-1";
	}

	cout << "Start vertex: ";	//Get starting vertex 
	getline(cin,start);

	cout << "End vertex: ";		//Get end vertex
	getline(cin, end);
	if (start == end)
	{
		throw Exception("Distance: 0\nPath: You are literally already there\nTime: 0");
	}
	Vertex<V, E> * temp = nullptr;
	Vertex<V, E> current;
	Vertex<V, E> evert;
	
	bool sfound = false;
	bool efound = false;
	int count = 0;
	int sindex = 0;

	//Checks if starting and ending vertices are in graph and finds index
	for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); (sfound != true || efound != true) && viter != graph.GetVertices().end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetData() == start)
		{
			sfound = true;
			sindex = count;
			current = *temp;
		}
		else if (temp->GetData() == end)
		{
			efound = true;
			evert = *temp;
		}
		count++;
	}

	if (sfound != true)
	{
		delete[] distance;	
		delete[] pred;
		throw Exception("Starting vertex is not in the graph!");
	}
	else if (efound != true)
	{
		delete[] distance;
		delete[] pred;
		throw Exception("Ending vertex is not in the graph!");
	}
	distance[sindex] = 0; //Distance from the starting point is always 0

	//Main loop to calculate distances
	while (!Done(graph))
	{
		Edge<V, E> * etemp;
		int index = -1;

		for (list<Edge<V, E>>::iterator eiter = current.GetEdges().begin(); eiter != current.GetEdges().end(); eiter++)
		{
			etemp = &(*eiter);
			if (etemp->GetDestination()->GetProcessed() != true)
			{
				index = GetIndex(graph, etemp->GetDestination()->GetData());
				if (distance[index] == -1 || distance[index] > etemp->GetWeight() + distance[sindex])	//if -1 or smaller
				{
					pred[index] = current.GetData();
					distance[index] = etemp->GetWeight() + distance[sindex];
				}
			}
		}
		SetProcessed(graph, current);	//Set calculated vertex to processed
		FindNext(distance, graph, current);	//Finds the next eligible vertex
		sindex = GetIndex(graph, current.GetData());
	}

	DistanceAndPath(graph, evert, distance, pred);	//Prints distance and path and time from point a to b
	delete[] distance;
	delete[] pred;
}

/**********************************************************************
* Purpose: This function gets the index to be used in the distance and 
*		   pred array based on the spot it is in the graph
*
* Precondition:	N/A
*
* Postcondition: Index for the arrays is known.
************************************************************************/
template<typename V, typename E>
int GetIndex(Graph<V, E> & graph, V data)
{
	int index = -1;
	int count = 0;
	bool found = false;
	Vertex<V, E> * temp = nullptr;

	for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); !found && viter != graph.GetVertices().end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetData() == data)
		{
			found = true;
			index = count;
		}
		count++;
	}

	//If node is not found in graph
	if (index == -1)
	{
		throw Exception("Data is not in the graph");
	}

	return index;
}

/**********************************************************************
* Purpose: This function finds the next vertex to be calaculated. Based
*		   on non negative, least, and unprocessed.
*
* Precondition:	N/A
*
* Postcondition: New current vertex is known.
************************************************************************/
template<typename V, typename E>
void FindNext(int distance[], Graph<V, E>& graph, Vertex<V, E> & cur)
{
	int min = INT_MAX;
	int count = 0;

	Vertex<V, E> * temp = nullptr;

	for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); viter != graph.GetVertices().end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetProcessed() == false)	//Unprocessed
		{
			if (distance[count] > 0)	//If not -1
			{
				if (distance[count] < min)	//Smallest yet
				{
					min = distance[count];
					cur = *temp;	//Lowest, unprocessed, non-negative vertex
				}
			}
		}
		count++;
	}
}

/**********************************************************************
* Purpose: This function sets the vertex to processed.
*
* Precondition:	N/A
*
* Postcondition: Vertex is set as processed.
************************************************************************/
template<typename V, typename E>
inline void SetProcessed(Graph<V, E> & graph, Vertex<V, E> cur)
{
	Vertex<V, E> * temp = nullptr;
	bool found = false;

	for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); !found && viter != graph.GetVertices().end(); ++viter)
	{
		temp = &(*viter);
		if (cur.GetData() == temp->GetData())
		{
			found = true;
			temp->SetProcessed(true);
		}
	}
}

/**********************************************************************
* Purpose: This function returns whether or not the graph is done being
*		   processed.
*
* Precondition:	N/A
*
* Postcondition: Returns whether or not the graph is done being processed.
************************************************************************/
template<typename V, typename E>
inline bool Done(Graph<V, E>& graph)
{
	bool done = true;
	Vertex<V, E> * temp = nullptr;

	for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); viter != graph.GetVertices().end(); ++viter)
	{
		temp = &(*viter);
		if (temp->GetProcessed() == false)
		{
			done = false;
		}
	}
	return done;
}

/**********************************************************************
* Purpose: This function prints the distance from the starting vertex
*		   to the ending vertex, the path to get there, and the estimated 
*		   time to do so.
*
* Precondition:	N/A
*
* Postcondition: Distance, path and time is printed.
************************************************************************/
template<typename V, typename E>
inline void DistanceAndPath(Graph<V, E>& graph, Vertex<V, E> end, int dist[], V pred[])
{
	vector<V> path;
	double time = 0;
	int index = GetIndex(graph, end.GetData());
	V stop_condition = "-1";
	cout << "\nDistance: " << dist[index] << endl;	//Prints total distance

	//************************** Calculate path **********************************
	cout << "Path: " << endl;
	path.push_back(end.GetData());
	while (pred[index] != stop_condition)
	{
		Vertex<V, E> * temp = nullptr;

		//Finds path
		for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); viter != graph.GetVertices().end(); ++viter)
		{
			temp = &(*viter);
			if (temp->GetData() == pred[index])
			{
				path.push_back(pred[index]);
				index = GetIndex(graph, temp->GetData());
			}
		}
	}

	//Prints path
	for (int i = path.size()-1; i >= 0; i--)
	{
		if (i > 0)
		{
			cout << path[i] << " to " << endl;
		}
		else
		{
			cout << path[i] << endl;
		}
	}
	cout << endl;

	//************************** Calculate time **********************************
	bool found = false;
	Vertex<V, E> * temp = nullptr;
	Vertex<V, E> current;
	Edge<V, E> * etemp = nullptr;
	for (int i = path.size() - 1; i >= 0; i--)
	{
		found = false;
		for (list<Vertex<V, E>>::iterator viter = graph.GetVertices().begin(); i>0 && !found && viter != graph.GetVertices().end(); ++viter)
		{
			temp = &(*viter);
			if (temp->GetData() == path[i])
			{
				found = true;
				current = *temp;

				for (list<Edge<V, E>>::iterator eiter = current.GetEdges().begin(); eiter != current.GetEdges().end(); ++eiter)
				{
					etemp = &(*eiter);
					if (etemp->GetDestination()->GetData() == path[i - 1])
					{
						if (etemp->GetData() == "I-5")
						{
							time += ((double)etemp->GetWeight() / (double)65);
						}
						else	//Any other road
						{
							time += ((double)etemp->GetWeight() / (double)55);
						}
					}
				}
			}
		}
	}
	time *= 60;	//Convert to minutes
	cout << "Estimated time: " << time << " minutes" << endl;
	cout << "or about " << time / 60 << " hours" << "\n\n";
}

