#include "StdAfx.h"
#include "MyVector.h"
namespace MyVector
{

/***************************************************************************************
       vector���������൱��һ���ڲ������������ڴ�Ĵ�����飬��Ϊ��������Ԥ��һ���ֿռ�
�������β�������ɾ������Ч�ʱȽϸߡ����漴����Ч��Ҳ�Ƚϸߡ����������м�ɾ���Ͳ�������Ч�ʽϵͣ�
���ҳ�ʱ��ʹ�ú�ǰcapacity����ʱ����Ҫ���������ڴ棬����Ҫ����ǰ������ȫ����������������ڴ棬Ҫͨ��SWAP�ķ�ʽ�����ͷš�

                                                           size                 capacity
                                                            |                   |
															|		            |
---------------------------------------------------------------------------------
|                                                                                |
|                 һ�����������ڴ�                                                              |
|                                                                                | 
---------------------------------------------------------------------------------

****************************************************************************************/
/***
	���캯��
***/
template<class T> CMyVector<T>::CMyVector(int iDefaultSize=1000)
{

	m_pMemrory = new T [iDefaultSize]; 
	m_isSize = 0;
	m_iMaxSize = iDefaultSize;
	m_iDefaultSize = iDefaultSize;
	memset(m_pMemrory,0,m_iMaxSize*sizeof(T));
}

/***
	��������
***/
template<class T> CMyVector<T>::~CMyVector(void)
{
	if(NULL != m_pMemrory)
	{
		delete []m_pMemrory;
		m_pMemrory = NULL;
	}

	m_isSize = 0;
	m_iMaxSize = 0;
}



/***
	�������
***/
template<class T>  void CMyVector<T>::push_back(T &value)
{
	if(m_isSize == m_iMaxSize)
	{	

		T *pTemp = m_pMemrory;
		m_pMemrory = new T[m_iMaxSize*2];
		memset(m_pMemrory,0,m_iMaxSize*2*sizeof(T));
	    memcpy(m_pMemrory,pTemp,m_iMaxSize*sizeof(T));
		m_iMaxSize = m_iMaxSize * 2;
	
		if(NULL != pTemp)
		{
			delete []pTemp;
			pTemp = NULL;
		}
	}
	
	m_pMemrory[m_isSize] = value;

	m_isSize++;
}



/***
	ɾ������
***/
template<class T>  void CMyVector<T>:: pop_back()
{
	if(0 == m_isSize)
	{
		return;
	}
	m_isSize--;
}


/***
	��������Ϊi��Ԫ��
***/
template<class T>  T& CMyVector<T>::operator[](const int &index) const
{
	if(index > m_isSize)
	{
		return NULL;
	}

	return m_pMemrory[index];
}

/***
	���ش�С
***/
template<class T> int  CMyVector<T>::size()
{
    return m_isSize;
}


/***
	��������
***/
template<class T> int CMyVector<T>::capacity()
{
	return m_iMaxSize;
}


/***
	�ж��Ƿ�Ϊ��
***/
template<class T> bool  CMyVector<T>::empty()
{
	return  0 == m_isSize;
}


/***
	���ؿ�ʼ��ָ��
***/
template<class T>  T* CMyVector<T>::begin() const
{
	return m_pMemrory;
}

/***
	���ؽ�����ָ��
***/
template<class T>  T* CMyVector<T>:: end() const
{
	return m_pMemrory+m_isSize;
}


/***
	�������캯��
***/
template<class T>  CMyVector<T>::CMyVector (const CMyVector<T> &tCMyVector)
{
	this->m_iMaxSize = tCMyVector.m_iMaxSize;
	this->m_isSize = tCMyVector.m_isSize;
	this->m_pMemrory = new T[this->m_iMaxSize];
	this->m_iDefaultSize = tCMyVector.m_iDefaultSize;
	memcpy(this->m_pMemrory,tCMyVector.m_pMemrory,this->m_iMaxSize*sizeof(T));
}


/***
	��ֵ���캯��
***/
template<class T>  CMyVector<T>& CMyVector<T>::operator= (const CMyVector<T> &tCMyVector)
{
	if(this==&tCMyVector)
	{
		return *this;
	}
	if(NULL != this->m_pMemrory)
	{
		delete []this->m_pMemrory;
		m_pMemrory = NULL;
	}

	this->m_iMaxSize = tCMyVector.m_iMaxSize;
	this->m_isSize = tCMyVector.m_isSize;
	this->m_pMemrory = new T[this->m_iMaxSize];
	this->m_iDefaultSize = tCMyVector.m_iDefaultSize;
	memcpy(this->m_pMemrory,tCMyVector.m_pMemrory,this->m_iMaxSize*sizeof(T));
	return *this;
}

/***
	������е����ݣ�����ɾ���ڴ�
***/
template<class T>  void  CMyVector<T>::clear()
{
	this->m_isSize = 0;
	memset(this->m_pMemrory,0,this->m_iMaxSize*sizeof(T));

}


/***
	������������
***/
template<class T>  void  CMyVector<T>::swap(CMyVector<T> &tCMyVector)
{
	if(this==&tCMyVector)
	{
		return;
	}
	int temp = this->m_iMaxSize;
	this->m_iMaxSize = tCMyVector.m_iMaxSize;
	tCMyVector.m_iMaxSize = temp;
	temp = this->m_isSize;
	this->m_isSize = tCMyVector.m_isSize;
	tCMyVector.m_isSize = temp;
	temp = this->m_iDefaultSize ;
	this->m_iDefaultSize = tCMyVector.m_iDefaultSize;
	tCMyVector.m_iDefaultSize = temp;
	T *pTemp = this->m_pMemrory; 
	this->m_pMemrory = tCMyVector.m_pMemrory;
	tCMyVector.m_pMemrory = pTemp;
	pTemp = NULL;
}

/***
	����������ݣ����ָ��ڴ�ΪĬ�ϴ�С
***/
template<class T>  void CMyVector<T>::ClearAll()
{
	this->m_isSize = 0;
	
	if(this->m_iMaxSize != this->m_iDefaultSize)
	{
		T *pTemp = this->m_pMemrory;
		this->m_pMemrory = new T[this->m_iDefaultSize];
        if(NULL != pTemp)
		{
			delete []pTemp;
			pTemp = NULL;
		}
		memset(this->m_pMemrory,0,this->m_iDefaultSize * sizeof(T));

	}

	this->m_iMaxSize = this->m_iDefaultSize;
}


/***
	���µ��������Ĵ�С
***/
template<class T>  void CMyVector<T>::resize(const int &isize)
{
	if(isize != this->m_iMaxSize)
	{
		T *pTemp = new T[isize];
		int iCopySize = isize>m_iMaxSize?m_iMaxSize:isize;
		memcpy(pTemp,this->m_pMemrory,iCopySize*sizeof(T));
		if(NULL != m_pMemrory)
		{
			delete []m_pMemrory;
			m_pMemrory = NULL;
		}
		this->m_isSize = this->m_isSize>isize?isize:this->m_isSize;
		m_pMemrory = pTemp;
		m_iMaxSize  = isize;
		
		
	}
}


/***
	ɾ���ƶ�λ��Ԫ��
***/
template<class T>  void CMyVector<T>::erase(int &index)
{
	if(index > this->m_isSize)
	{
		return;
	}

	memcpy(&this->m_pMemrory[index],&this->m_pMemrory[index+1] ,(this->m_isSize - index)*sizeof(T));
	this->m_isSize--;
}


/***
	ɾ��������λ��Ԫ��
***/
template<class T>  T*  CMyVector<T>::erase(T* it)
{
	T* it_next = it+1;
 	T* save = it;    
	string sTemp = *save;

	T* tEnd = &this->m_pMemrory[m_isSize];
	while(it_next != tEnd)
	{
		*it = *it_next;
		it++;
		it_next++;
	}
	this->m_isSize--;
	return save;
}

/****
	vector��Ԫ�ط�ת
****/
template<class T> void CMyVector<T>::reverse()
{
	for(int i = 0; i < this->m_isSize / 2; i++)
	{
		T temp = this->m_pMemrory[i];
		this->m_pMemrory[i] = this->m_pMemrory[this->m_isSize - 1];
		this->m_pMemrory[this->m_isSize - 1] = temp;
	}
}

/***
	�������Ԫ��
***/
template<class T>  void CMyVector<T>::PrinAllElement()
{
	for(int i = 0; i < this->m_isSize; i++)
	{
		cout<<this->m_pMemrory[i]<<" ";
		if(0 == i % 5)
		{
			cout<<endl;
		}
	}
	cout<<endl;
}

}