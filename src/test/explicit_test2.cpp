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
private:
	map<S, double> values;
public:
	SimpleHeuristic(map<S, double> values) : values(values)
	{
	}

	double operator()(S state) 
	{
		return values[state];
	}
};

int explicit_test2() {
	/*map<string, double> heur;
	heur["Saa"] = 222.0;
	heur["Kai"] = 158.0;
	heur["Kar"] = 140.0;
	heur["Fra"] = 96.0;
	heur["Lud"] = 108.0;
	heur["Hei"] = 87.0;
	heur["Wue"] = 0.0;

	vector<string> nodes;
	nodes.push_back("Saa");
	nodes.push_back("Kai");
	nodes.push_back("Kar");
	nodes.push_back("Fra");
	nodes.push_back("Lud");
	nodes.push_back("Hei");
	nodes.push_back("Wue");

	map<string, vector<Edge<string> > > edges;
	edges["Saa"].push_back(Edge<string>("Kai", 70.0));
	edges["Saa"].push_back(Edge<string>("Kar", 145.0));
	edges["Kai"].push_back(Edge<string>("Fra", 103.0));
	edges["Kai"].push_back(Edge<string>("Lud", 53.0));
	edges["Kar"].push_back(Edge<string>("Hei", 84.0));
	edges["Fra"].push_back(Edge<string>("Wue", 116.0));
	edges["Lud"].push_back(Edge<string>("Wue", 183.0));
	edges["Hei"].push_back(Edge<string>("Wue", 102.0));*/

	map<char, double> heur;
	heur['S'] = 222.0;
	heur['K'] = 158.0;
	heur['R'] = 140.0;
	heur['F'] = 96.0;
	heur['L'] = 108.0;
	heur['H'] = 87.0;
	heur['W'] = 0.0;

	vector<char> nodes;
	nodes.push_back('S');
	nodes.push_back('K');
	nodes.push_back('R');
	nodes.push_back('F');
	nodes.push_back('L');
	nodes.push_back('H');
	nodes.push_back('W');

	map<char, vector<Edge<char> > > edges;
	edges['S'].push_back(Edge<char>('K', 70.0));
	edges['S'].push_back(Edge<char>('R', 145.0));
	edges['K'].push_back(Edge<char>('F', 103.0));
	edges['K'].push_back(Edge<char>('L', 53.0));
	edges['R'].push_back(Edge<char>('H', 84.0));
	edges['F'].push_back(Edge<char>('W', 116.0));
	edges['L'].push_back(Edge<char>('W', 183.0));
	edges['H'].push_back(Edge<char>('W', 102.0));

	LeafSearchProblem<ExplicitGraph<char>, char> problem('S');
	ExplicitGraph<char> g(nodes, edges);

	DepthFirstSearch<ExplicitGraph<char> > allocatorDFS;
	vector<char> path = allocatorDFS(g, problem);
	std::cout << "Best Path DFS = " << path << std::endl;
	std::cout << "Best Cost DFS = " << cost(g, path) << std::endl;

	AStarSearch<ExplicitGraph<char>, SimpleHeuristic<char> > allocatorAS;
	SimpleHeuristic<char> h(heur);
	path = allocatorAS(g, problem, h);
	std::cout << "Best Path AStar = " << path << std::endl;
	std::cout << "Best Cost AStar = " << cost(g, path) << std::endl;

	return 0;
}

