#pragma once
#include <iostream>

template <typename VarType>
class TVector {
protected:
	int size;
	VarType* elems;
	int startIndex;
public:
	TVector(int size = 10, int startIndex = 0);
	TVector(const TVector<VarType>&);
	~TVector();

	bool operator==(const TVector&)const;
	bool operator!=(const TVector&)const;
	TVector<VarType> operator+(VarType);
	TVector<VarType> operator-(VarType);
	TVector<VarType> operator*(VarType);
	TVector<VarType> operator+(const TVector&);
	TVector<VarType> operator-(const TVector&);
	VarType operator*(const TVector&);
	TVector<VarType>& operator= (const TVector&);
	VarType Length()const;
	int Size()const;
	int StartIndex()const;

	void Fill(VarType, VarType);

	friend std::ostream& operator << (std::ostream& s, const TVector& v) {
		if (v.size <= 0) throw (std::string)"Wrong dimension";
		s << "[";
		for (int i = 0; i < v.StartIndex(); i++) {
			s << std::setw(5) << std::right << ' ';
		}
		for (int i = 0; i < v.size; i++) {
			s << std::setw(5) << std::right << v.elems[i] << ' ';
		}
		s << "]";
		return s;
	}
	
	friend std::istream& operator >> (std::istream& s, TVector& v) {
		if (v.size <= 0) throw (std::string)"Wrong dimension";
		for (int i = 0; i < v.size; i++) {
			std::cout << "Enter " << i + 1 << " element: ";
			s >> v.elems[i];
			std::cout << std::endl;
		}
		return s;
	}

	const VarType& operator [] (int index) const;
	VarType& operator [] (int index);
};

template<typename VarType>
TVector<VarType>::TVector(int size, int startIndex)
{
	if (size <= 0) throw (std::string)"Invalid size";
	this->size = size;
	this->startIndex = startIndex;
	elems = new VarType[size];
}

template<typename VarType>
TVector<VarType>::TVector(const TVector<VarType>& V)
{
	size = V.size;
	startIndex = V.startIndex;
	elems = new VarType[size];
	for (int i = 0; i < size; i++) {
		elems[i] = V.elems[i];
	}
}

template<typename VarType>
TVector<VarType>::~TVector()
{
	size = 0;
	startIndex = 0;
	delete[] elems;
}

template<typename VarType>
bool TVector<VarType>::operator==(const TVector<VarType>& V) const
{
	if ((size != V.size) && (startIndex != V.startIndex)) return false;
	for (int i = 0; i < size; i++) {
		if (elems[i] != V.elems[i]) return false;
	}
	return true;
}

template<typename VarType>
bool TVector<VarType>::operator!=(const TVector<VarType>& V) const
{
	if (*this == V) return false;
	return true;
}

template<typename VarType>
TVector<VarType> TVector<VarType>::operator+(VarType c)
{
	TVector<VarType> tmp(*this);
	for (int i = 0; i < size; i++) {
		tmp.elems[i] += c;
	}
	return tmp;
}

template<typename VarType>
TVector<VarType> TVector<VarType>::operator-(VarType c)
{
	TVector<VarType> tmp(*this);
	for (int i = 0; i < size; i++) {
		tmp.elems[i] -= c;
	}
	return tmp;
}

template<typename VarType>
TVector<VarType> TVector<VarType>::operator*(VarType c)
{
	TVector<VarType> tmp(*this);
	for (int i = 0; i < size; i++) {
		tmp.elems[i] *= c;
	}
	return tmp;
}

template<typename VarType>
TVector<VarType> TVector<VarType>::operator+(const TVector<VarType>& V)
{
	if ((size != V.size) && (startIndex != V.startIndex)) throw (std::string)"Different dimension";
	TVector<VarType> tmp(*this);
	for (int i = 0; i < size; i++) {
		tmp.elems[i] += V.elems[i];
	}
	return tmp;
}

template<typename VarType>
TVector<VarType> TVector<VarType>::operator-(const TVector<VarType>& V)
{
	if ((size != V.size) && (startIndex != V.startIndex)) throw (std::string)"Different dimension";
	TVector<VarType> tmp(*this);
	for (int i = 0; i < size; i++) {
		tmp.elems[i] -= V.elems[i];
	}
	return tmp;
}

template<typename VarType>
VarType TVector<VarType>::operator*(const TVector<VarType>& V)
{
	if ((size != V.size) && (startIndex != V.startIndex)) throw (std::string)"Different dimension";
	VarType res = 0;
	for (int i = 0; i < size; i++) {
		res += elems[i] * V.elems[i];
	}
	return res;
}

template<typename VarType>
TVector<VarType>& TVector<VarType>::operator=(const TVector<VarType>& V)
{
	if (elems == V.elems) throw (std::string)"Self-assignment";
	size = V.size;
	startIndex = V.startIndex;
	delete[] elems;
	elems = new VarType[size];
	for (int i = 0; i < size; i++) {
		elems[i] = V.elems[i];
	}
	return *this;
}

template<typename VarType>
VarType TVector<VarType>::Length() const
{
	VarType res = 0;
	for (int i = 0; i < size; i++) res += elems[i] * elems[i];
	return sqrt(res);
}

template<typename VarType>
int TVector<VarType>::Size() const
{
	return size;
}

template<typename VarType>
int TVector<VarType>::StartIndex() const
{
	return startIndex;
}

template<typename VarType>
void TVector<VarType>::Fill(VarType from, VarType to)
{
	if (size <= 0) throw (std::string)"Invalid vector";
	for (int i = 0; i < size; i++) {
		VarType randValue(rand());
		VarType randOperand = randValue * (to - from) / VarType(RAND_MAX);
		elems[i] = randOperand + from;
	}
}

template<typename VarType>
const VarType& TVector<VarType>::operator[](int index) const
{
	if (index - startIndex >= size) throw (std::string)"Wrong index";
	return elems[index - startIndex];
}

template<typename VarType>
VarType& TVector<VarType>::operator[](int index) {
	if (index - startIndex >= size) throw (std::string)"Wrong index";
	return elems[index - startIndex];
}