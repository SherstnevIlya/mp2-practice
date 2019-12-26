#pragma once

#include "TStack.h"
#include "TList.h"

template<typename V>
class TListStack : public TStack<V> {
protected:
	TList<V, void*>* list;
public:
	TListStack();
	TListStack(const TListStack&);
	~TListStack();
	bool Empty() const;
	bool Full() const;
	void Push(V);
	void Pop();
	V Top() const;
};

template<typename V>
TListStack<V>::TListStack() {
	list = new TList<V, void*>;
}

template<typename V>
TListStack<V>::TListStack(const TListStack& lstack) {
	list = new TList<V, void*>(*(lstack->list));
}

template<typename V>
TListStack<V>::~TListStack() {
	delete list;
}

template<typename V>
bool TListStack<V>::Empty() const {
	return list->IsEmpty();
}

template<typename V>
bool TListStack<V>::Full() const {
	return false;
}

template<typename V>
void TListStack<V>::Push(V value) {
	list->InsertBegin(value, nullptr);
}

template<typename V>
void TListStack<V>::Pop() {
	if (Empty()) throw (std::string)"Stack is empty";
	list->Remove(list->getFirstNodeKey());
}

template<typename V>
V TListStack<V>::Top() const {
	if (Empty()) throw (std::string)"Stack is empty";
	return list->getFirstNodeKey();
}