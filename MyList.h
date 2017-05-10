#pragma once
#include <utility>
#include <iostream>
using namespace std;
namespace LIST
{
	/*******************************************************

	List������ͼ��ʾ�����õ���˫�˶��е���ʽʵ�ֵġ��ڶ��е�
	
	ͷ����β������Ԫ�ؽϿ죬�ڶ��е������м�λ�ò����ɾ��Ԫ��Ҳ

	�Ͽ졣���Ǳ������бȽϺ�ʱ��

   	------      ------         ------
   |      |--->|       | ---->|      |  
   |      |<---|       |<-----|      |
   --------     --------       -------
	*********************************************************/
	template<class T>  struct Node
	{
		struct Node<T>*  m_pNext;
		struct Node<T>*  m_pPre;
		T m_value;
	    
	};


	template<class T> bool comparebig(struct Node<T> Tone,struct Node<T> Ttwo)
	{
		return Tone.m_value >Ttwo.m_value;
	}

   template<class T>  class CMyList
	{
		public:
			    //LIST����׼����
			    typedef bool(*pCompare)(struct Node<T>,struct Node<T>);
				explicit CMyList(void)
				{
					m_icount = 0;
					m_pHead = new Node<T>();
					m_pEnd = new Node<T>();
					m_pHead->m_pNext = m_pEnd;
					m_pHead->m_pPre = NULL;
					m_pEnd->m_pPre = m_pHead;
					m_pEnd->m_pNext = NULL;
					
				}
				~CMyList(void)
				{
					struct Node<T>*pTemp = m_pHead;
					while( NULL != m_pHead)
					{
						m_pHead = m_pHead->m_pNext;
						if(NULL != pTemp)
						{
							delete pTemp;
						}

						pTemp = m_pHead; 
					}
				}

				/*************
					����ͷ������Ԫ��
				**************/
				void pushfront(T value)
				{
					m_icount++;
					struct Node<T>* pValue = new Node<T>();
					pValue->m_pNext = m_pHead->m_pNext;
					m_pHead->m_pNext->m_pPre = pValue;
					pValue->m_pPre = m_pHead;
					m_pHead->m_pNext = pValue;
					pValue->m_value = value; 
				}

				/*************
					����ͷ��ȡ��Ԫ��
				**************/

				T popfront()
				{
					if(0 == m_icount)
					{
						return NULL;
					}
					m_icount--;
					struct Node<T>* pValue = m_pHead->m_pNext;
					T value = pValue->m_value;
					m_pHead->m_pNext = m_pHead->m_pNext->m_pNext;
					m_pHead->m_pNext->m_pPre = m_pHead; 
					if(NULL != pValue)
					{
						delete pValue;
					}
					return value;
					
				}
		
				/*************
					����β������Ԫ��
				**************/
				void pushend(T value)
				{
					m_icount++;
					struct Node<T>* pValue = new Node<T>();
					pValue->m_value = value;
					pValue->m_pNext = m_pEnd;
					m_pEnd->m_pPre->m_pNext = pValue;
					pValue->m_pPre =m_pEnd->m_pPre;
					m_pEnd->m_pPre = pValue;
				}

				/*************
					����β��ɾ��Ԫ��
				**************/
				T popend()
				{
					if(0 == m_icount)
					{
						return NULL;
					}
					m_icount--;
					struct Node<T>* pValue = m_pEnd->m_pPre;
					T value = pValue->m_value;
					m_pEnd->m_pPre = m_pEnd->m_pPre->m_pPre;
					m_pEnd->m_pPre->m_pNext = m_pEnd; 
					if(NULL != pValue)
					{
						delete pValue;
					}
					return value;
					
				}

				/*************
					�����С
				**************/
				int size()
				{
					return m_icount;
				}

				/*************
					�����Ƿ�Ϊ��
				**************/
				bool  empty()
				{
					return 0 == m_icount;
				}

				/*************
					ȡ����ΪiIndex��Ԫ��
				**************/
				T operator[](int iIndex)
				{
					int iCount = 0;
					struct Node<T>* pValue = m_pHead->m_pNext;
					while(iCount < iIndex)
					{

						pValue = pValue->m_pNext;
						iCount++;
					}

					return pValue->m_value;
				}

				/*************
					�������
				**************/
				void  clear()
				{
					m_icount = 0;
					struct Node<T>*pTemp = m_pHead;
					while( m_pEnd != m_pHead)
					{
						m_pHead = m_pHead->m_pNext;
						if(NULL != pTemp)
						{
							delete pTemp;
						}

						pTemp = m_pHead; 
					}
				}

				/*************
					��i��λ�ò���Ԫ��
				**************/
				void  insert(int iIndex, T value)
				{
					m_icount++;
					int iCount = 1;
					struct Node<T>* pValue = m_pHead;
					while(iCount < iIndex)
					{

						pValue = pValue->m_pNext;
						iCount++;
					}

					struct Node<T>* pInsetValue = new Node<T>();
					pInsetValue->m_value = value;
					pInsetValue->m_pNext = pValue->m_pNext;
					pValue->m_pNext->m_pPre = pInsetValue;
				    pValue->m_pNext = pInsetValue;
				    pInsetValue->m_pPre = pValue;		

				}


				/*************
					��i��λ��ɾ��Ԫ��
				**************/
				T  erase(int iIndex)
				{
					if(0 == m_icount)
					{
						return NULL;
					}
					m_icount--;
					int iCount = 0;
					struct Node<T>* pValue = m_pHead;
					while(iCount < iIndex)
					{

						pValue = pValue->m_pNext;
						iCount++;
					}
					T rev = pValue->m_value;

					pValue->m_pPre->m_pNext = pValue->m_pNext;
					pValue->m_pNext->m_pPre = pValue->m_pPre;		
	
					return rev;
				}

				/*************
					�������캯��
				**************/
				CMyList(CMyList &tCMyList)
				{
					m_pHead = new Node<T>();
					m_pEnd = new Node<T>();
					m_pHead->m_pNext = m_pEnd;
					m_pHead->m_pPre = NULL;
					m_pEnd->m_pPre = m_pHead;
					m_pEnd->m_pNext = NULL;
					Node<T>*pTemp = tCMyList.m_pHead->m_pNext;
					while(pTemp != tCMyList.m_pEnd)
					{
						this->pushend(pTemp->m_value);
						pTemp = pTemp->m_pNext;
					}
					m_icount = tCMyList.m_icount;
				}

				/*************
					��ֵ���캯��
				**************/
				CMyList operator=(CMyList &tCMyList)
				{
					if(this == &tCMyList)
					{
						return *this;
					}

					this->clear();

					m_pHead = new Node<T>();
					m_pEnd = new Node<T>();
					m_pHead->m_pNext = m_pEnd;
					m_pHead->m_pPre = NULL;
					m_pEnd->m_pPre = m_pHead;
					m_pEnd->m_pNext = NULL;
					Node<T>*pTemp = tCMyList.m_pHead->m_pNext;
					while(pTemp!= tCMyList.m_pEnd)
					{
						this->pushend(pTemp->m_value);
						pTemp = pTemp->m_pNext;
					}
					m_icount = tCMyList.m_icount;

					return *this;
				}
			
				/*************
					�������Ԫ��
				**************/
				void printelement()
				{
					struct Node<T>* pTemp = m_pHead->m_pNext;
					int icount = 0;
					while(pTemp != m_pEnd)
					{					
						cout<<" "<<pTemp->m_value;
						if(0!= icount && 0 == icount % 5)
						{
							cout<<endl;
						}
						pTemp = pTemp->m_pNext;
						icount++;
					}
					cout<<endl;
				}
				/*************
					�������������
				**************/
				void sort(pCompare pConFunc = &comparebig)
				{
					struct Node<T>*pNext = m_pHead->m_pNext;
				    bool isSort = true;
					while( pNext->m_pNext != m_pEnd && isSort)
					{
						isSort = false;
						struct Node<T>*pNextCom = m_pHead->m_pNext;
						while(pNextCom->m_pNext != m_pEnd)
						{
							struct Node<T>*pNextNextCom =  pNextCom->m_pNext;
							if(false == pConFunc(*pNextCom,*pNextNextCom))
							{
								isSort = true;
								T swap = pNextCom->m_value;
								pNextCom->m_value = pNextNextCom->m_value;
								pNextNextCom->m_value = swap;
							}

							pNextCom = pNextCom->m_pNext;
						}

						pNext = pNext->m_pNext;
					}
				}

	private:
			struct Node<T>* m_pHead;
			struct Node<T>* m_pEnd;
			int m_icount;
			
	};
}

