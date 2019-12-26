#pragma once

template <typename V>
class TStack {
public:
	virtual bool Empty() const = 0;
	virtual bool Full() const = 0;
	virtual void Push(V) = 0;
	virtual void Pop() = 0;
	virtual V Top() const = 0;
};