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
#ifndef ASTAR_H_
#define ASTAR_H_

#include <datastructures/stack.h>
#include <search/problem.h>
#include <cfloat>
#include <iostream>
#include <ostream>
#include <set>
#include <utility>
#include <boost/heap/fibonacci_heap.hpp>

using std::ostream;

template <class StateType>
class InternalState
{
public:

	InternalState(StateType state = StateType(), double g = 0.0, double h = 0.0, const InternalState* predecessor = 0) : state(state), g(g), h(h), predecessor(predecessor)
	{
		f = g + h;
	}

	bool operator<(const InternalState<StateType>& other) const {
		return f > other.f;
	}

	StateType state;
	const InternalState* predecessor;
	double g;
	double h;
	double f;

};

template <class S>
ostream& operator<<(ostream& s, const InternalState<S>& is)
{
	if (is.predecessor)
		return s << "(" << is.state << ", " << is.f << ", " << is.predecessor->state << ")";
	else
		return s << "(" << is.state << ", " << is.f << ", NULL)";
}

template <class Graph, class Heuristic, class Problem=LeafSearchProblem<Graph, typename Graph::StateType>, int STACK_SIZE=1023, int MAX_DEPTH=63, int MAX_BRANCH=100, class PriorityQueue=boost::heap::fibonacci_heap<InternalState<typename Graph::StateType> > >
class AStarSearch
{
public:

	typedef typename Graph::StateType S;

	void conv_path(const InternalState<S>& goal, vector<S>& result)
	{
		Stack<S, MAX_DEPTH> stack;
		const InternalState<S>* current_state = &goal;
		while (current_state)
		{
			stack.push(current_state->state);
			current_state = current_state->predecessor;
		}
		while (!stack.is_empty())
		{
			result.push_back(stack.pop());
		}
	}

	vector<S> operator()(const Graph& g, const Problem& problem, Heuristic& h)
	{
		typedef typename PriorityQueue::handle_type Handle;
		typedef std::pair<Handle, InternalState<S> > StateInfo;

		PriorityQueue openq;
		map<S, StateInfo> state2handle;
		InternalState<S> start(problem.start_state, 0, h(problem.start_state), 0);
		Handle start_handle = openq.push(start);
		state2handle[start.state] = StateInfo(start_handle, start);

		S buffer[MAX_BRANCH];
		unsigned int num_succ;

		vector<S> result;

		while (!openq.empty())
		{
			std::cout << "Open Queue = " << openq << std::endl;

			const InternalState<S> current = openq.top();
			openq.pop();

			std::cout << "Open State = " << current.state << std::endl;
			

			state2handle.erase(current.state); // optional?
			if (problem.is_goal(g, current.state))
			{
				conv_path(current, result);
				return result;
			}

			g.expand(current.state, buffer, &num_succ);

			for (unsigned int i = 0; i < num_succ; ++i)
			{
				S next_state = buffer[i];

				std::cout << "Next State = " << next_state << std::endl;
				
				typename map<S, StateInfo>::iterator handle_it = state2handle.find(next_state);
				double tentative_g = current.g + g.cost(current.state, next_state);
				if (handle_it != state2handle.end())
				{
					InternalState<S>& next = handle_it->second.second;
					if (tentative_g < next.g)
					{
						next.g = tentative_g;
						next.f = next.g + next.h;
						delete next.predecessor;
						next.predecessor = new InternalState<S>(current);
						openq.update(handle_it->second.first, next);
					}
				}
				else
				{
					InternalState<S> next_internal_state(buffer[i], tentative_g, h(next_state), new InternalState<S>(current));
					Handle next_handle = openq.push(next_internal_state);
					state2handle[next_state] = StateInfo(next_handle, next_internal_state);
				}

			}

		}
	}
};



#endif /* SEARCH_H_ */
