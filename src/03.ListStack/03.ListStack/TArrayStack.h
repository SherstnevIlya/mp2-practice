#pragma once

#include "TStack.h"

template <typename V>
class TArrayStack : public TStack<V> {
	size_t size;
	size_t top;
	V* elems;
public:
	TArrayStack(size_t);
	TArrayStack(const TArrayStack&);
	~TArrayStack();
	bool Empty() const;
	bool Full() const;
	void Push(V);
	void Pop();
	V Top() const;
	TArrayStack& operator=(const TArrayStack&);
};

template <typename V>
TArrayStack<V>::TArrayStack(size_t maxsize) {
	if (maxsize == 0) throw "Wrong size";
	size = maxsize;
	elems = new V[maxsize];
	top = 0;
}

template <typename V>
TArrayStack<V>::TArrayStack(const TArrayStack<V>& s) {
	this->size = s.size;
	this->top = s.top;
	elems = new V[size];
	for (int i = 0; i < top; i++) {
		elems[i] = s.elems[i];
	}
}

template <typename V>
TArrayStack<V>::~TArrayStack() {
	delete[] elems;
}

template <typename V>
bool TArrayStack<V>::Empty() const {
	return (top == 0);
}

template <typename V>
bool TArrayStack<V>::Full() const {
	return (top == size);
}

template <typename V>
void TArrayStack<V>::Push(V value) {
	if (Full()) throw "Stack overflow";
	elems[top++] = value;
}

template <typename V>
void TArrayStack<V>::Pop() {
	if (Empty()) throw "Stack is empty";
	top--;
}

template <typename V>
V TArrayStack<V>::Top() const {
	if (Empty()) throw "Stack is empty";
	return elems[top - 1];
}

template<typename V>
TArrayStack<V>& TArrayStack<V>::operator=(const TArrayStack<V>& tmp)
{
	if (size != tmp.size)
	{
		size = tmp.size;
		delete[] elems;
		elems = new V[size];
	}
	for (size_t i = 0; i < size; i++)
		elems[i] = tmp.elems[i];
	return *this;
}