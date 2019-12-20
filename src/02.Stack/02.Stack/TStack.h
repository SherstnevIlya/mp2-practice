#pragma once

template <typename V>
class TStack {
	size_t size;
	size_t top;
	V* elems;
public:
	TStack(size_t);
	TStack(const TStack&);
	~TStack();
	bool Empty() const;
	bool Full() const;
	void Push(V);
	void Pop();
	V Top() const;
	TStack& operator=(const TStack&);
};

template <typename V>
TStack<V>::TStack(size_t maxsize) {
	if (maxsize == 0) throw "Wrong size";
	size = maxsize;
	elems = new V[maxsize];
	top = 0;
}

template <typename V>
TStack<V>::TStack(const TStack<V>& s) {
	this->size = s.size;
	this->top = s.top;
	elems = new V[size];
	for (int i = 0; i < top; i++) {
		elems[i] = s.elems[i];
	}
}

template <typename V>
TStack<V>::~TStack() {
	delete[] elems;
}

template <typename V>
bool TStack<V>::Empty() const {
	return (top == 0);
}

template <typename V>
bool TStack<V>::Full() const {
	return (top == size);
}

template <typename V>
void TStack<V>::Push(V value) {
	if (Full()) throw "Stack overflow";
	elems[top++] = value;
}

template <typename V>
void TStack<V>::Pop() {
	if (Empty()) throw "Stack is empty";
	top--;
}

template <typename V>
V TStack<V>::Top() const {
	if (Empty()) throw "Stack is empty";
	return elems[top - 1];
}

template<typename V>
TStack<V>& TStack<V>::operator=(const TStack<V>& tmp)
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