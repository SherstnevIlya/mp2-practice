#pragma once
#include "TVector.h"

template <typename VarType>
class TMatrix : public TVector<TVector<VarType>>
{
public:
	TMatrix(int size = 10);
	TMatrix(const TMatrix<VarType>&);
	TMatrix(const TVector<TVector<VarType>>&);
	~TMatrix() = default;

	bool operator==(const TMatrix&)const;
	bool operator!=(const TMatrix&)const;
	TMatrix& operator=(const TMatrix&);
	TMatrix operator+(VarType);
	TMatrix operator-(VarType);
	TMatrix operator*(VarType);
	TMatrix operator+(const TMatrix<VarType>&);
	TMatrix operator-(const TMatrix<VarType>&);
	TMatrix operator*(const TMatrix<VarType>&);

	void Fill(VarType, VarType);
	TMatrix Transponirovat();
	VarType Determinant();

	friend std::ostream& operator<<(std::ostream& s, const TMatrix& m) {
		if (m.size <= 0) throw (std::string)"Wrong dimension";
		for (int i = 0; i < m.size; i++) 
			s << m.elems[i] << '\n';
		return s;
	}
	friend std::istream& operator>>(std::istream& s, TMatrix& m) {
		if (m.size <= 0) throw (std::string)"Wrong dimension";
		for (int i = 0; i < m.size; i++) {
			std::cout << "Entering " << i + 1 << " vector: " << std::endl;
			s >> m.elems[i];
		}
		return s;
	}
};

template<typename VarType>
TMatrix<VarType>::TMatrix(int size) : TVector<TVector<VarType>>(size)
{	
	for (int i = 0; i < size; i++) 
		this->elems[i] = TVector<VarType>(size - i, i);
}

template<typename VarType>
TMatrix<VarType>::TMatrix(const TMatrix<VarType>& m) : TVector<TVector<VarType>>(m)
{
}

template<typename VarType>
TMatrix<VarType>::TMatrix(const TVector<TVector<VarType>>& v) : TVector<TVector<VarType>>(v)
{
}

template<typename VarType>
bool TMatrix<VarType>::operator==(const TMatrix<VarType>& m) const
{
	if (this->size != m.size) return false;
	for (int i = 0; i < this->size; i++) {
		if (this->elems[i] != m.elems[i]) return false;
	}
	return true;
}

template<typename VarType>
bool TMatrix<VarType>::operator!=(const TMatrix<VarType>& m) const
{
	if (*this == m) return false;
	return true;
}

template<typename VarType>
TMatrix<VarType>& TMatrix<VarType>::operator=(const TMatrix<VarType>& m)
{
	if (*this == m) return *this;
	if (this->size != m.size) {
		this->size = m.size;
		delete[] this->elems;
		this->elems = new TVector<VarType>[m.size];
	}
	for (int i = 0; i < m.size; i++) {
		this->elems[i] = m.elems[i];
	}
	return *this;
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::operator+(VarType c)
{
	TMatrix<VarType> tmp(*this);
	for (int i = 0; i < tmp.size; i++) {
		tmp.elems[i] = tmp.elems[i] + c;
	}
	return tmp;
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::operator-(VarType c)
{
	TMatrix<VarType> tmp(*this);
	for (int i = 0; i < tmp.size; i++) {
		tmp.elems[i] = tmp.elems[i] - c;
	}
	return tmp;
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::operator*(VarType c)
{
	TMatrix<VarType> tmp(*this);
	for (int i = 0; i < tmp.size; i++) {
		tmp.elems[i] = tmp.elems[i] * c;
	}
	return tmp;
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::operator+(const TMatrix<VarType>& m)
{
	if (this->size != m.size) throw (std::string)"Different dimension";
	TMatrix<VarType> tmp(*this);
	for (int i = 0; i < tmp.size; i++) {
		tmp.elems[i] = tmp.elems[i] + m.elems[i];
	}
	return tmp;
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::operator-(const TMatrix<VarType>& m)
{
	if (this->size != m.size) throw (std::string)"Different dimension";
	TMatrix<VarType> tmp(*this);
	for (int i = 0; i < tmp.size; i++) {
		tmp.elems[i] = tmp.elems[i] - m.elems[i];
	}
	return tmp;
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::operator*(const TMatrix<VarType>& m)
{
	if (this->size != m.size) throw (std::string)"Different dimension";
	TMatrix<VarType> tmp(*this);
	for (int i = 0; i < tmp.size; i++) {
		int cols = 1;
		int index = m.elems[i].StartIndex();
		for (int j = index; j < tmp.size; j++) {
			tmp.elems[i][j] = VarType(0);
			for (int k = 0; k < cols; k++)
				tmp.elems[i][j] = tmp.elems[i][j] + this->elems[i][k + i] * m.elems[k + i][j];
			cols++;
		}
	}
	return tmp;
}

template<typename VarType>
void TMatrix<VarType>::Fill(VarType from, VarType to)
{
	if (this->size == 0) return;
	for (int i = 0; i < this->size; i++) this->elems[i].Fill(from, to);
}

template<typename VarType>
TMatrix<VarType> TMatrix<VarType>::Transponirovat()
{
	TMatrix<VarType> temp(*this);
	for (int i = 0; i < temp.size / 2; i++) {
		TVector<VarType> tmp(temp[i]);
		temp[i] = temp[temp.size - i - 1];
		temp[temp.size - i - 1] = tmp;
	}
	for (int i = 0; i < temp.size; i++) {
		temp[i].SetSI(0);
	}
	for (int i = 0; i < temp.size; i++) {
		for (int j = i; j < temp.size; j++) {
			temp[j][i] = (*this)[i][j];
		}
	}
	return temp;
}

template<typename VarType>
VarType TMatrix<VarType>::Determinant()
{
	if (this->size <= 0) throw (std::string)"Wrong dimension";
	VarType res = 1;
	for (int i = 0; i < this->size; i++)
		res = res * this->elems[i][i];
	return res;
}
