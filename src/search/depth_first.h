/*****************************************************************************

 Copyright (c) 2012 Institute of Robotics and Mechatronics, DLR

 $Revision::      $ $Author::           $
 $Date::                          $

****************************************************************************//**

 \file search.h
 \brief your brief file description is missing
 \author widm_hn
 \date Jun 26, 2012

*****************************************************************************/
#ifndef DEPTH_FIRST_H_
#define DEPTH_FIRST_H_

#include <datastructures/stack.h>
#include <search/problem.h>
#include <cfloat>
#include <iostream>

template <class Graph, class Problem=LeafSearchProblem<Graph, typename Graph::StateType>, int STACK_SIZE=1023, int MAX_DEPTH=63, int MAX_BRANCH=63>
class DepthFirstSearch
{
public:

	typedef typename Graph::StateType S;

	vector<S> operator()(const Graph& g, const Problem& problem)
	{
		this->g = &g;
		this->problem = &problem;

		best_cost = DBL_MAX;
		best_path.clear();
		current_path.clear();

		rec_dfs(problem.start_state, 0.0);
		return best_path;


		//S buffer[MAX_BRANCH];
		//unsigned int num_succ;

		//double best_cost = DBL_MAX;
		//double cost = 0.0;
		////double last_cost = 0.0;

		//Stack<S, STACK_SIZE> stack;
		//Stack<unsigned int, MAX_DEPTH> expansion_stack;
		//Stack<double, MAX_DEPTH> cost_stack;
		//stack.push(problem.start_state);
		////current_path.push(problem.start_state);

		//Stack<S, MAX_DEPTH> current_path;
		//Stack<S, MAX_DEPTH> best_path;

		//while (!stack.is_empty()) {
		//	S e = stack.pop();

		//	std::cout << "Current Path = " << current_path << std::endl;
		//	std::cout << "Current Elem = " << e << std::endl;
		//	std::cout << "Stack = " << stack << std::endl;

		//	double c = 0.0;
		//	if (!current_path.is_empty())
		//		c = g.cost(current_path.peek(), e);
		//	cost_stack.push(c);
		//	cost += c;

		//	std::cout << "Current Cost = " << cost << std::endl;

		//	current_path.push(e);
		//	if (problem.is_goal(g, e) && cost < best_cost) {
		//		best_path = current_path;
		//		best_cost = cost;
		//		//std::cout << "New best path = " << best_path << std::endl;
		//	}
		//	g.expand(e, buffer, &num_succ);
		//	expansion_stack.push(num_succ);
		//	for (unsigned int i = 0; i < num_succ; i++) {
		//		stack.push(buffer[i]);
		//	}
		//	while (expansion_stack.peek() == 0) {
		//		expansion_stack.pop();
		//		current_path.pop();
		//		cost -= cost_stack.pop();
		//	}
		//	expansion_stack.push(expansion_stack.pop()-1);
		//}

		////std::cout << debug(best_path) << std::endl;

		//return best_path.conv2vector();
	}

private:
	void rec_dfs(const S& current_state, double current_cost)
	{
		unsigned int num_succ;
		S buffer[MAX_BRANCH];
		current_path.push_back(current_state);
		if (problem->is_goal(*g, current_state) && current_cost < best_cost)
		{
			best_path = current_path;
			best_cost = current_cost;
			return;
		}
		else
		{
			g->expand(current_state, buffer, &num_succ);
			for (unsigned int i = 0; i < num_succ; i++)
			{
				rec_dfs(buffer[i], current_cost + g->cost(current_state, buffer[i]));
			}
			
		}
		current_path.pop_back();
	}

	vector<S> current_path;
	vector<S> best_path;
	double best_cost;

	const Graph* g;
	const Problem* problem;
};



#endif /* SEARCH_H_ */
