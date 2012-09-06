/*
 * ExplicitGraph.h
 *
 *  Created on: Jun 27, 2012
 *      Author: widm_hn
 */

#ifndef EXPLICITGRAPH_H_
#define EXPLICITGRAPH_H_

#include <vector>
#include <map>
#include <exception>

template<class T>
class Edge {
public:
	Edge(T destination, double cost) : destination(destination), cost(cost) {}

	T destination;
	double cost;
};

using std::vector;
using std::map;

template<class T>
class ExplicitGraph {
public:
	typedef T StateType;
	//typedef typename vector<Edge<T> >::iterator IteratorType;

	ExplicitGraph(vector<StateType>& nodes, map<StateType, vector<Edge<StateType> > >& edges) : nodes(nodes), edges(edges) {
	}

	void expand(const StateType& node, StateType* buffer, unsigned int* num_succ) const {
		vector<Edge<StateType> >& v = edges[node];
		for (typename vector<Edge<StateType> >::iterator i = v.begin(); i != v.end(); ++i) {
			*(buffer++) = i->destination;
		}
		*num_succ = v.size();
	}

	double cost(const StateType& from, const StateType& to) const {
		vector<Edge<StateType> >& v = edges[from];
		for (typename vector<Edge<StateType> >::iterator i = v.begin(); i != v.end(); ++i) {
			if (i->destination == to)
				return i->cost;
		}
		std::cerr << "WARNING: " << from << " --> " << to << " does not exist." << std::endl;
		return 1000000.0;
	}

	bool is_leaf(const StateType& s) const {
		return edges[s].empty();
	}

private:
	vector<StateType>& nodes;
	map<StateType, vector<Edge<StateType> > >& edges;
};

#endif /* EXPLICITGRAPH_H_ */
