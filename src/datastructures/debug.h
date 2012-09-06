/*****************************************************************************

 Copyright (c) 2012 Institute of Robotics and Mechatronics, DLR

 $Revision::      $ $Author::           $
 $Date::                          $

****************************************************************************//**

 \file debug.h
 \brief your brief file description is missing
 \author widm_hn
 \date Jul 6, 2012

*****************************************************************************/
#ifndef DEBUG_H_
#define DEBUG_H_

#include <sstream>
#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <boost/heap/fibonacci_heap.hpp>

using std::stringstream;
using std::string;
using std::vector;

template <class Iterable>
std::ostream& print_iterable(std::ostream& s, const Iterable& v)
{
	if (v.size() > 0) {
		typename Iterable::const_iterator b = v.begin();
		s << "[" << *b;
		for (typename Iterable::const_iterator i = ++b; i != v.end(); ++i) {
			s << ", " << *i;
		}
	}
	else {
		s << "[";
	}
	s << "]";

	return s;
}

template <class T> 
std::ostream& operator<<(std::ostream& s, const vector<T>& v) 
{
	return print_iterable(s, v);
}

template <class T> 
std::ostream& operator<<(std::ostream& s, boost::heap::fibonacci_heap<T>& heap)
{
	return print_iterable(s, heap);
}


#endif /* DEBUG_H_ */
