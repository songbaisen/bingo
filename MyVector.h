#pragma once
#include <utility>
#include <iostream>
using namespace std;
namespace MyVector
{
	template<class T> class CMyVector
	{
	public:
		 typedef T* iterator;
		 typedef const T* const_iterator;
		 explicit CMyVector(int iDefaultSize = 1000);
		~CMyVector(void);
		 void push_back(T &value);
		 void pop_back();
		 int size();
		 int capacity();
		 bool empty();
		 void clear();
		 void swap(CMyVector &tCMyVector);
		 void ClearAll();
		 void resize(const int &isize);
		 void PrinAllElement();
		 void erase(int &index);
		 void reverse();
		 iterator erase(iterator it);
		 T& operator[](const int &index) const;
		 iterator begin() const;
		 iterator end() const;
		 CMyVector (const CMyVector &tCMyVector);
		 CMyVector& operator= (const CMyVector &tCMyVector);
		 T *m_pMemrory;
	private:
		 int m_isSize;
		 int m_iMaxSize;
		 int m_iDefaultSize;
	};
}

