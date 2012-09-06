/*****************************************************************************

 Copyright (c) 2012 Institute of Robotics and Mechatronics, DLR

 $Revision::      $ $Author::           $
 $Date::                          $

******************************************************************************/

#include <graphs/ExplicitGraph.h>
#include <graphs/utils.h>
#include <search/search.h>
#include <vector>
#include <map>
#include <iostream>

using std::vector;
using std::map;

template <class S>
class SimpleHeuristic
{
public:
	double operator()(S state) 
	{
		return 1.0;
	}
};

int explicit_test() {
	vector<char> nodes;
	nodes.push_back('A');
	nodes.push_back('B');
	nodes.push_back('C');
	nodes.push_back('D');
	nodes.push_back('E');

	map<char, vector<Edge<char> > > edges;
	Edge<char> e1('B', 1.0);
	Edge<char> e2('C', 5.0);
	Edge<char> e3('D', 2.0);
	Edge<char> e4('E', 3.0);
	edges['A'].push_back(e1);
	edges['A'].push_back(e2);
	edges['B'].push_back(e3);
	edges['B'].push_back(e4);

	LeafSearchProblem<ExplicitGraph<char>, char> problem('A');
	ExplicitGraph<char> g(nodes, edges);

	DepthFirstSearch<ExplicitGraph<char> > allocatorDFS;
	vector<char> path = allocatorDFS(g, problem);
	std::cout << "Best Path DFS = " << path << std::endl;
	std::cout << "Best Cost DFS = " << cost(g, path) << std::endl;

	AStarSearch<ExplicitGraph<char>, SimpleHeuristic<char> > allocatorAS;
	SimpleHeuristic<char> h;
	path = allocatorAS(g, problem, h);
	std::cout << "Best Path AStar = " << path << std::endl;
	std::cout << "Best Cost AStar = " << cost(g, path) << std::endl;

	return 0;
}

