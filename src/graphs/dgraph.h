#ifndef DGRAPH_H_
#define DGRAPH_H_

template <class T, class A>
class DirectedGraphNode
{
public:

	DirectedGraphNode(const T& value) : value(value) {}

	const T& value;
	vector<DirectedGraphNode*> successors;

private:
};

template <class T, class Cost>
class DirectedGraph
{
public:

	typedef DirectedGraphNode<T> StateType;

	DirectedGraph(const DirectedGraphNode<T>* root, const Cost& cost_fcn) : root(root), cost_fcn(cost_fcn) {}

	void expand(const StateType& node, StateType* buffer, unsigned int* num_succ) const {
		unsigned int j = 0;
		for (typename vector<DirectedGraphNode*>::iterator i = node.successors.begin(); i != node.successors.end(); ++i)
		{
			buffer[j++] = *i;
		}
		num_succ = j;
	}

	double cost(const StateType& from, const StateType& to) const {
		return cost_fcn(from.value, to.value);
	}

private:
	const DirectedGraphNode<T>* root;
	const Cost& cost_fcn;
};


#endif