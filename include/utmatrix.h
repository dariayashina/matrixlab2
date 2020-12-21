// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>
#include <exception>
using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);          // одновременно конструктор по умолчанию
                                            // и конструктор с параметрами
  TVector(const TVector &v); 
  TVector(TVector &&v);// конструктор копирования
  virtual ~TVector();
  int GetSize()   const   { return Size;       } // размер вектора
  int GetStartIndex()const{ return StartIndex; }
  void SetSize(int x)
  {
	  Size = x;
  }
  void SetStartIndex(int x)
  {
	  StartIndex = x;
  }
  ValType* GetVector()const { return pVector; }// индекс первого элемента
  ValType& operator[](int pos); 
  ValType& operator[](int pos) const;// доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение
  int FindIndex()
  {
	  for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	  {
		  if (((*this)[i] != 0))return i;
	  }
	  return -1;
  }
 
  // ввод - вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size-v.StartIndex; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.Size - v.StartIndex; i++) {
		  out << v.pVector[i] << ' ';
	  }
	out << endl;
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if ((s < 0) || (si<0) || (s>MAX_VECTOR_SIZE)) throw logic_error("");
	pVector = new ValType[s];
	for (int i = 0; i < s; i++)
	{
		pVector[i] = 0;
	}
	StartIndex = si;
	Size = s + StartIndex;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	
	pVector = new ValType[v.Size-v.StartIndex];
	for (int i = 0; i < v.Size-v.StartIndex; i++)
	{
		pVector[i] = v.pVector[i];
	}
	StartIndex = v.StartIndex;
	Size = v.Size;
} /*-------------------------------------------------------------------------*/
template <class ValType> //конструктор копирования
TVector<ValType>::TVector( TVector<ValType> &&v)
{

	pVector =v.pVector;
	v.pVector = nullptr;
	StartIndex = v.StartIndex;
	Size = v.Size;
} 
template <class ValType>
TVector<ValType>::~TVector()
{
	if (pVector != nullptr) {
		delete[]pVector;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if ((pos < StartIndex) || (pos < 0) || (pos >Size)) throw logic_error("");
    return pVector[pos-StartIndex];
} 
template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)const
{
	if ((pos < StartIndex) || (pos < 0) || (pos > Size)) throw logic_error("");
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (this == &v)return 1;

	if ((this->GetSize() == v.GetSize()) && (this->GetStartIndex() == v.GetStartIndex()))
	{
		for (int i = 0; i < v.GetSize() - v.GetStartIndex(); i++)
		{
			if (this->pVector[i] != v.pVector[i])
			{
				return 0;
			}
			return 1;
		}
	}
	return 0;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
    return !(*this==v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this == &v)
	{
		return (*this);
	}
	if (this->GetSize() == v.GetSize())
	{
		for (int i = 0; i < v.Size - v.StartIndex; i++)
		{
			pVector[i] = v.pVector[i];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		return (*this);
	}
    delete []pVector;
	pVector = new ValType[v.Size - v.StartIndex];
	for (int i = 0; i < v.Size - v.StartIndex; i++)
	{
		pVector[i] = v.pVector[i];
	}
	Size = v.Size;
	StartIndex = v.StartIndex;
	return (*this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] += val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] -= val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] *= val;
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] =res.pVector[i]+ v.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	TVector<ValType>res(*this);
	for (int i = 0; i < res.Size - res.StartIndex; i++)
	{
		res.pVector[i] = res.pVector[i] - v.pVector[i];
	}
	return res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (this->GetSize() != v.GetSize()) throw logic_error("");
	float res=0;
	for (int i = 0; i < v.Size - v.StartIndex; i++)
	{
		res = res + v.pVector[i]*this->pVector[i];
	}
	return sqrt(res);
} /*-------------------------------------------------------------------------*/


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание
 TMatrix( TVector<TVector<ValType> >&& mt);
  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s > MAX_MATRIX_SIZE) throw logic_error("");
	for (int i = 0; i < this->Size - this->StartIndex; i++)
	{
		TVector<ValType>res(s-i, i);
		this->pVector[i] = res;
	}
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
{

}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) 
{

}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this == &mt) return 1;

	if (((*this).GetStartIndex() == mt.GetStartIndex()) && ((*this).GetSize() == mt.GetSize()))
	{
		for (int i = mt.GetStartIndex(); i < mt.GetSize(); i++)
		{
			if ((*this)[i] != mt[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !((*this) == mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (&mt == this)
	{
		return (*this);
	}
	if (this->GetSize() == mt.GetSize())
	{
		for (int i = 0; i < this->Size-this->StartIndex; i++)
		{
			(*this).pVector[i] = mt.pVector[i];
		}
		return(*this);
	}
	delete[]pVector;
	pVector = new TVector<ValType>[mt.Size-mt.StartIndex];

	(*this).Size = mt.Size;
	(*this).StartIndex = mt.StartIndex;
	for (int i = (*this).GetStartIndex(); i < (*this).GetSize(); i++)
	{
		(*this)[i] = mt[i];
	}
	return (*this);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
    // благодаря наследованию от TVector<TVector<ValType> > operator+
    // уже есть, надо только его вызвать
	if (mt.Size != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this)[i] + mt[i];
	}
	return Res;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != (*this).GetSize()) throw logic_error("incorrect size");
	TMatrix<ValType>Res(*this);
	for (int i = Res.GetStartIndex(); i < Res.GetSize(); i++)
	{
		Res[i] = (*this)[i] - mt[i];
	}
	return Res;
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
