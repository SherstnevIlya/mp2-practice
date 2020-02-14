#pragma once

#include "iostream"

template <typename TKey, typename TData>
struct TNode {
	TKey key;
	TData* pData;
	TNode* pNext;

	TNode();
	TNode(TKey, TData*);
	TNode(const TNode<TKey, TData>&);
	~TNode();
	template <typename TKey, typename TData>
	friend std::ostream& operator<<(std::ostream&, const TNode<TKey, TData>&);
};

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode() {
	pData = nullptr;
	pNext = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(TKey key, TData* data) {
	pNext = nullptr;
	this->key = key;
	if (data != nullptr) {
		pData = new TData;
		*pData = *data;
	}
	else pData = nullptr;
}

template <typename TKey, typename TData>
TNode<TKey, TData>::TNode(const TNode<TKey, TData>& node) {
	if (node.pData != nullptr) {
		pData = new TData;
		*pData = *node.pData;
	}
	else pData = nullptr;
	pNext = node.pNext;
	key = node.key;
}

template<typename TKey, typename TData>
TNode<TKey, TData>::~TNode() {
	if (pData != nullptr)
		delete pData;
}

template <typename TKey, typename TData>
std::ostream& operator<<(std::ostream& s, const TNode<TKey, TData>& node) {
	s << "[" << node.key << " : " << *(node.pData) << "]";
	return s;
};
