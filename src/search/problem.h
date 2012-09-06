/*****************************************************************************

 Copyright (c) 2012 Institute of Robotics and Mechatronics, DLR

 $Revision::      $ $Author::           $
 $Date::                          $

****************************************************************************//**

 \file problem.h
 \brief your brief file description is missing
 \author widm_hn
 \date Jun 27, 2012

*****************************************************************************/
#ifndef PROBLEM_H_
#define PROBLEM_H_

template <class Graph, class T>
class LeafSearchProblem
{
public:
	LeafSearchProblem(const T start_state) : start_state(start_state) {}

	const T start_state;

	bool is_goal(const Graph& g, const T& s) const {
		return g.is_leaf(s);
	}
};

#endif /* PROBLEM_H_ */
