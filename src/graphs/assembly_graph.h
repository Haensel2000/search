#ifndef ASSEMBLY_GRAPH_H_
#define ASSEMBLY_GRAPH_H_

#include <datastructures/debug.h>
#include <boost/cstdint.hpp>
#include <vector>
#include <list>
#include <ostream>

using std::vector;
using std::list;

class Int32Subassembly
{
public:
	Int32Subassembly(unsigned int part)
	{
		value = 1 << part;
	}

	vector<unsigned int> get_parts()
	{
		vector<unsigned int> result;
		uint_fast32_t mask = 1;
		for (unsigned int i = 0; i < 32; ++i)
		{
			if (value & mask)
				result.push_back(i);
			mask <<= 1;
		}
		return result;
	}

private:
	uint_fast32_t value;
};

std::ostream& operator<<(std::ostream& s, Int32Subassembly subassembly)
{
	return s << subassembly.get_parts();
}

template <class Subassembly>
class AssemblyAction
{
public:
	AssemblyAction(const Subassembly& a, const Subassembly& b) : a(a), b(b) {}
	const Subassembly& a;
	const Subassembly& b;
};

/*---------------------------------------------------------------------*/
/*
Interface for AssemblyState a:

*/

template <class Subassembly>
class StatePartition
{
public:
	StatePartition(unsigned int num_parts)
	{ 
		for (unsigned int i = 0; i < num_parts; ++i)
		{
			partition.push_back(Subassembly(i));
		}
	}

	/* O(n^3) */
	template<class M>
	vector< AssemblyAction<Subassembly> > applicable_actions(const M assembly)
	{
		/*vector< AssemblyAction<Subassembly> > result;
		for (typename vector<Subassembly>::iterator i = partition.begin(); i != partition.end(); ++i)
		{
			for (typename vector<Subassembly>::iterator j = ++i; j != partition.end(); ++j)
			{
				vector<unsigned int> parts = i->get_parts();
				for (typename vector<unsigned int>::iterator k = parts.begin(); k != parts.end(); ++k)
				{
					std::pair<bool, edge_descriptor> b = edge(
				}
				
			}
		}*/
	}

private:
	vector<Subassembly> partition;
};

class GraphState
{
public:

	GraphState(unsigned int num_parts) : rank(num_parts), parent(num_parts)
	{
		ds(&rank[0], &parent[0]);
		for (int i = 0; i < num_parts; ++i)
		{
			ds.make_set(i);
		}
	}

	GraphState(const GraphState& copy) : rank(copy.rank), parent(copy.parent)
	{
		ds(&rank[0], &parent[0]);
	}

	void successors(const M& assembly, GraphState* buffer, unsigned int* num_succ)
	{
		int j = 0;
		for (typename list< std::pair<int, int> >::iterator i = edges.begin(); i != edges.end(); ++i)
		{
			*buffer[j] = GraphState(*this);
			buffer[j]->ds.union_set(i->first(), i->second());
			buffer[j]->edges.remove(i);
			++j;
		}
		*num_succ = j;
	}

private:
	vector<int> rank;
	vector<int> parent;
	list< std::pair<int, int> > edges;
	disjoint_sets<int*, int*> ds;
};

/*---------------------------------------------------------------------*/



template <class AssemblyState>
std::ostream& operator<<(std::ostream& s, const AssemblyState& assembly_state)
{
	return s << subassembly.get_parts();
}

template <class AssemblyState, class WorkerActionCost>
class LocalCost
{
public:

	LocalCost(const WorkerActionCost& worker_action_cost, unsigned int number_workers) : worker_action_cost(worker_action_cost), number_workers(number_workers) {}

	double operator()(const AssemblyState& a, const AssemblyState& b) 
	{

	}
private:

	const WorkerActionCost worker_action_cost;
	unsigned int number_workers;
};


/*
Interface for an assembly m:
m.num_parts 
m.connections (Graph)
m.is_feasible(AssemblyAction)
*/

/*
Interface for a scenario s:
s.part_positions
s.agent_positions
s.is_reachable(part, agent)
s.duration(action, agent)
*/

class Scenario
{
}

template <class AssemblyState, class M, class Scenario>
class ImplicitAssemblyGraph
{
public:
	typedef AssemblyState StateType;

	ImplicitAssemblyGraph(const M& assembly, const Scenario& scenario) : assembly(assembly), scenario(scenario) {}

	void expand(const StateType& node, StateType* buffer, unsigned int* num_succ) const {
		node.successors(assembly, buffer, num_succ);
	}

	double cost(const StateType& from, const StateType& to) const {
		
	}

	bool is_leaf(const StateType& s) const {
		
	}

private:
	const vector<Vector3f>& part_positions;
	const M& assembly;
	const Scenario& scenario;
};



#endif