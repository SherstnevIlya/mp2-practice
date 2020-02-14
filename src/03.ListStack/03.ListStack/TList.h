#pragma once

#include "TNode.h"

template <typename TKey, typename TData>
class TList {
protected:
	TNode<TKey, TData>* pFirst;
	TNode<TKey, TData>* pNext;
	TNode<TKey, TData>* pPrevious;
	TNode<TKey, TData>* pCurrent;

public:
	TList();
	TList(const TList<TKey, TData>&);
	TList(const TNode<TKey, TData>*);
	~TList();

	void InsertBegin(TKey, TData*);
	void InsertEnd(TKey, TData*);
	void InsertBefore(TKey, TKey, TData*);
	void InsertAfter(TKey, TKey, TData*);
	void Remove(TKey);
	void Reset();
	void Next();
	bool IsEnded() const;
	bool IsEmpty() const;
	TKey getFirstNodeKey() const;
	template <typename TKey, typename TData>
	friend std::ostream& operator<<(std::ostream&, const TList<TKey, TData>&);
};

template <typename TKey, typename TData>
TList<TKey, TData>::TList() {
	pFirst = nullptr;
	pPrevious = nullptr;
	pNext = nullptr;
	pCurrent = nullptr;
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(const TList& list) {
	pFirst = new TNode<TKey, TData>(*(list.pFirst));
	TNode<TKey, TData>* node = pFirst;
	TNode<TKey, TData>* tmp = list.pFirst;
	while (tmp->pNext != nullptr) {
		node->pNext = new TNode<TKey, TData>(*(tmp->pNext));
		node = node->pNext;
		tmp = tmp->pNext;
	}
	pPrevious = nullptr;
	pCurrent = pFirst;
	if (pFirst->pNext != nullptr)
		pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
TList<TKey, TData>::TList(const TNode<TKey, TData>* node) {
	pFirst = new TNode<TKey, TData>(*node);
	TNode<TKey, TData>* kek = pFirst;
	TNode<TKey, TData>* tmp = new TNode<TKey, TData>(*node);
	while (tmp->pNext != nullptr) {
		kek->pNext = new TNode<TKey, TData>(*(tmp->pNext));
		kek = kek->pNext;
		tmp = tmp->pNext;
	}
	pPrevious = nullptr;
	pCurrent = pFirst;
	if (pFirst->pNext != nullptr)
		pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
TList<TKey, TData>::~TList() {
	TNode<TKey, TData>* tmp = pFirst;
	TNode<TKey, TData>* next;
	while (tmp != nullptr) {
		next = tmp->pNext;
		delete tmp;
		tmp = next;
	}
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBegin(TKey newKey, TData* data) {
	if (pFirst == nullptr) {
		pFirst = new TNode<TKey, TData>(newKey, data);
		pCurrent = pFirst;
		return;
	}
	TNode<TKey, TData>* newFirstNode = new TNode<TKey, TData>(newKey, data);
	newFirstNode->pNext = pFirst;
	if (pCurrent == pFirst)
		pPrevious = newFirstNode;
	pFirst = newFirstNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertEnd(TKey newKey, TData* data) {
	if (pFirst == nullptr) {
		pFirst = new TNode<TKey, TData>(newKey, data);
		pCurrent = pFirst;
		return;
	}
	TNode<TKey, TData>* lastNode = new TNode<TKey, TData>(newKey, data);
	TNode<TKey, TData>* penultimateNode = pFirst;
	while (penultimateNode->pNext != nullptr) {
		penultimateNode = penultimateNode->pNext;
	}
	penultimateNode->pNext = lastNode;
	if (pCurrent = penultimateNode)
		pNext = lastNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertBefore(TKey key, TKey newKey, TData* data) {
	if (pFirst == nullptr) return;
	if (pFirst->key == key)	{
		InsertBegin(newKey, data);
		return;
	}
	TNode<TKey, TData>* previousNode = pFirst;
	while ((previousNode->pNext != nullptr) && (previousNode->pNext->key != key)) {
		previousNode = previousNode->pNext;
	}
	if (previousNode->pNext == nullptr)
		throw (std::string)"No next";
	TNode<TKey, TData>* nextNode = previousNode->pNext;
	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(newKey, data);
	previousNode->pNext = newNode;
	newNode->pNext = nextNode;
	if (pCurrent == previousNode)
		pNext = newNode;
	if (pCurrent == nextNode)
		pPrevious = newNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::InsertAfter(TKey key, TKey newKey, TData* data) {
	if (pFirst == nullptr) return;
	TNode<TKey, TData>* previousNode = pFirst;
	while ((previousNode != nullptr) && (previousNode->key != key))	{
		previousNode = previousNode->pNext;
	}
	if (previousNode == nullptr) {
		throw (std::string)"Trying to point before first";
	}
	TNode<TKey, TData>* nextNode = previousNode->pNext;
	TNode<TKey, TData>* newNode = new TNode<TKey, TData>(newKey, data);
	previousNode->pNext = newNode;
	newNode->pNext = nextNode;
	if (pCurrent == previousNode)
		pNext = newNode;
	if (pCurrent == nextNode)
		pPrevious = newNode;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Remove(TKey key) {
	if (pFirst == nullptr) return;
	if (pFirst->key == key) {
		bool wasFirstNodeCurrent = (pCurrent == pFirst);
		bool wasFirstNodePrevious = (pPrevious == pFirst);
		TNode<TKey, TData>* nextNode = pFirst->pNext;
		delete pFirst;
		pFirst = nextNode;
		if (wasFirstNodeCurrent)  pCurrent = nullptr;
		if (wasFirstNodePrevious) pPrevious = nullptr;
		return;
	}
	TNode<TKey, TData>* previousNode = pFirst;
	while ((previousNode->pNext != nullptr) && (previousNode->pNext->key != key)) {
		previousNode = previousNode->pNext;
	}
	if (previousNode->pNext == nullptr) {
		throw (std::string)"List ended";
	}
	TNode<TKey, TData>* nextNode = previousNode->pNext->pNext;
	bool wasRemovingNodeCurrent = (pCurrent == previousNode->pNext);
	bool wasRemovingNodeNext = (pNext == previousNode->pNext);
	delete previousNode->pNext;
	previousNode->pNext = nextNode;
	if (wasRemovingNodeCurrent)
		pCurrent = nullptr;
	if (wasRemovingNodeNext)
		pNext = nullptr;
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Reset() {
	pCurrent = pFirst;
	pPrevious = nullptr;
	if (pFirst != nullptr)
		pNext = pFirst->pNext;
}

template <typename TKey, typename TData>
bool TList<TKey, TData>::IsEnded() const {
	if (pCurrent == nullptr) return true;
	return false;
}

template <typename TKey, typename TData>
bool TList<TKey, TData>::IsEmpty() const {
	return (pFirst == nullptr);
}

template <typename TKey, typename TData>
void TList<TKey, TData>::Next() {
	if (IsEnded() == true) {
		throw (std::string)"Ended";
	}
	pPrevious = pCurrent;
	pCurrent = pNext;
	if (pNext != nullptr) {
		pNext = pNext->pNext;
	}
}

template <typename TKey, typename TData>
TKey TList<TKey, TData>::getFirstNodeKey() const {
	if (pFirst == nullptr) {
		throw (std::string)"Null pointer";
	}
	return pFirst->key;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& s, const TList<TKey, TData>& list) {
	TNode<TKey, TData>* node = list.pFirst;
	while (node != nullptr)	{
		s << *(node);
		if (node->pNext != nullptr)
			s << " --> ";
		node = node->pNext;
	}
	return s;
};
