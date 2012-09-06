/*****************************************************************************

 Copyright (c) 2012 Institute of Robotics and Mechatronics, DLR

 $Revision::      $ $Author::           $
 $Date::                          $

****************************************************************************//**

 \file stack.h
 \brief your brief file description is missing
 \author widm_hn
 \date Jun 26, 2012

*****************************************************************************/
#ifndef STACK_H_
#define STACK_H_

#include <cstring>
#include <datastructures/debug.h>

//template <class T, unsigned int SIZE=1023>
//class Stack
//{
//public:
//
//	Stack() {
//		ptr = start_ptr();
//	}
//
//	Stack(const Stack& s) {
//		*this = s;
//	}
//
//	~Stack() {
//		ptr = &data[0];
//		std::cout << "Destroying Stack: " << *this << std::endl;
//	}
//
//	void push(T element) {
//		*(++ptr) = element;
//	}
//
//	T pop() {
//		return *(ptr--);
//	}
//
//	T peek() {
//		return *ptr;
//	}
//
//	void pop(int num_elements) {
//		ptr -= num_elements;
//	}
//
//	bool is_empty() const {
//		return ptr == start_ptr();
//	}
//
//	unsigned int size() const {
//		return ptr - start_ptr();
//	}
//
//	void operator=(const Stack& s) {
//		std::memcpy(&data[0], &s.data[0], s.size()*sizeof(T));
//		ptr = start_ptr() + s.size();
//	}
//
//	vector<T> conv2vector() const {
//		vector<T> result;
//		for (unsigned int i = 0; i < size(); i++) {
//			result.push_back(data[i]);
//		}
//		return result;
//	}
//
//private:
//
//	T* start_ptr() {
//		T* p0 = &data[0];
//		return --p0;
//	}
//
//	const T* start_ptr() const {
//		const T* p0 = &data[0];
//		return --p0;
//	}
//
//	T* ptr;
//	T data[SIZE];
//};

template <typename T, unsigned int SIZE>
class Stack
{
public:

	Stack()
	{}

	T pop()
	{
		T ret = values.back();
		values.pop_back();
		return ret;
	}

	const T& peek() const
	{
		return values.back();
	}

	void push(const T& elem)
	{
		values.push_back(elem);
	}

	unsigned int size() const
	{
		return values.size();
	}

	bool is_empty() const 
	{
		return values.empty();
	}

	vector<T> conv2vector() const
	{
		return values;
	}

private:
	vector<T> values;
};

template <class T, unsigned int SIZE> std::ostream& operator<<(std::ostream& s, const Stack<T, SIZE>& stack) {
	vector<T> v = stack.conv2vector();
	s << v;
	return s;
}

#endif /* STACK_H_ */
