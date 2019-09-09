#pragma once
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
	friend std::ostream& operator<< (const ostream&, const TVector&);
	friend std::istream operator>> (const std::istream&, TVector&);
	ValType& operator[] (int index);
};

template<typename VarType>
TVector<VarType>::TVector(int size, int startIndex)
{
	this->size = size;
	this->startIndex = startIndex;
	elems = new TypeVar[size];
}

template<typename VarType>
TVector<VarType>::TVector(const TVector<VarType>& V)
{
	size = V.size;
	startIndex = V.startIndex;
	elems = new TypeVar[size];
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
	if (size != V.size) return false;
	for (int i = 0; i < size; i++) {
		if (elems[i] != V.elems[i]) return false;
	}
	return true;
}

template<typename VarType>
 bool TVector<VarType>::operator!=(const TVector<VarType> &V) const
{
	if (size != V.size) return true;
	for (int i = 0; i < size; i++) {
		if (elems[i] != V.elems[i]) return true;
	}
	return false;
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
	 if (size != V.size) throw (std::string)"Different dimension";
	 TVector<VarType> tmp(*this);
	 for (int i = 0; i < size; i++) {
		 tmp.elems[i] += V.elems[i];
	 }
	 return tmp;
 }

 template<typename VarType>
 TVector<VarType> TVector<VarType>::operator-(const TVector<VarType>& V)
 {
	 if (size != V.size) throw (std::string)"Different dimension";
	 TVector<VarType> tmp(*this);
	 for (int i = 0; i < size; i++) {
		 tmp.elems[i] -= V.elems[i];
	 }
	 return tmp;
 }

 template<typename VarType>
 VarType TVector<VarType>::operator*(const TVector<VarType>& V)
 {
	 if (size != V.size) throw (std::string)"Different dimension";
	 VarType res = 0;
	 for (int i = 0; i < size; i++) {
		 res += elems[i] * V.elems[i];
	 }
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
	 for (int = 0; i < size; i++) res += elems[i] * elems[i];
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
