/***********************************************************
* Author:				Levi Pomeroy
* Date Created:			03/08/17
* Last Mod Date:		03/09/17
* Lab Number:			CST 211
* Filename:				Lab 6 - Dijkstra
*
* Overview:
*	This program reads a text file, populates the graph with the 
*	data and then calculated the shortest distance between the 
*	vertices.
*
* Input:
*	The input will consist of the users choice of the starting 
*	and ending vertices.
*
* Output:
*	The output of this program will consist of the distance from
*	start to end, the path to take, and the estimated time to get
*	there based on the distance and speed limits.
************************************************************/
#include "methods.h"

int main()
{
	Graph<string, string> graph;	//Create graph
	string edgeInfo[47][4];			//Holds the files info

	try
	{
		ReadLine(edgeInfo);		//Reads the file and stores in array
	}
	catch (Exception & ex)
	{
		cout << ex << endl;
	}

	try
	{
		PopulateGraph(edgeInfo, graph);	//Populates the graph with the info from the file
	}
	catch (Exception & ex)
	{
		cout << ex << endl;
	}

	try
	{
		Dijkstra(graph);	//Finds the shorest path from a starting vertex to an ending vertex
	}
	catch (Exception & ex)
	{
		cout << ex << endl;
	}

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //Memory leak check
	return 0;
}

