#ifndef BRIO_H_
#define BRIO_H_

#include <assembly_graph.h>

template <class AssemblyState>
class BRIOGraph
{
public:
	typedef AssemblyState StateType;

	void expand(const StateType& node, StateType* buffer, unsigned int* num_succ) const {
		
	}

	double cost(const StateType& from, const StateType& to) const {
		
	}

	bool is_leaf(const StateType& s) const {
		
	}

private:



};



#endif