#pragma once
#include <utility>
#include <iostream>
using namespace std;
namespace MyDeque
{
	/*****************************************

     ���е�ʵ��������ʾ������һ���������飬������һ�������Ķ����ڴ�顣�ڶ��е�ͷ��β��

	 �����ɾ��Ԫ���нϸߵ�Ч�ʡ�Ϊ�˱�֤����������ԣ�������Ҫά��һ�����ӵ������������

	 ���е��м�����ɾ��Ԫ�أ����漰���ڴ���ƶ���Ч�ʽϵ͡��������漴���ʵ�Ч��Ҳû��

	 vector�ߡ�������Ҫ�Զ������򣬿�������vector�����źú��������С�
               
     ��������                         �����ڴ��
      ----------                      -----------------------------------------------------
	 |         |-------------------->|       |          |           |           |          |                                              
	 -----------                     |       |          |           |           |          |                                              
                                       -----------------------------------------------------
	 |         |
	 -----------
	 |         |
	 -----------
	 |         |
	 -----------
	 |         |
	 -----------
	 |         |
	 -----------
	 |         |
	 -----------
	 |         |
	 -----------
	 	

	******************************************/
	template <class T> class CMyDeque
	{
		public:
				typedef T* iterator;
				typedef const T* const_iterator;

				explicit CMyDeque(int iArraySize = 5, int iElementSize = 1000)
				{
					m_iArraySize = iArraySize;
					m_iElementSize = iElementSize;
					m_pArray =(T**) new T[m_iArraySize];
					for(int i = 0; i < m_iArraySize; ++i)
					{
						T *Array = new T[sizeof(T) * m_iElementSize];
						memset(Array,0,sizeof(T)*m_iElementSize);
						m_pArray[i] = Array;
					}
					
					m_curFront = &m_pArray[m_iArraySize/2][m_iElementSize/2+1];
					m_curBack = &m_pArray[m_iArraySize/2][m_iElementSize/2];
					m_iFrontIndex = m_iBackIndex = m_iArraySize/2;
					m_cout = 0;
				}
				
				~CMyDeque(void)
				{
					for(int i = 0; i < m_iArraySize; ++i)
					{
						T *Array = m_pArray[i];
						if(NULL != Array)
						{
							delete []Array;
							Array = NULL;
						}
					}

					delete []m_pArray;
				}

				/********
				      �������캯��
				**********/
				CMyDeque(CMyDeque &tCMyDeque)
				{
					m_iArraySize = tCMyDeque.m_iArraySize;
					m_iElementSize = tCMyDeque.m_iElementSize;
					m_pArray =(T**) new T[m_iArraySize];
					for(int i = 0; i < m_iArraySize; ++i)
					{
						T *Array = new T[sizeof(T) * m_iElementSize];
						memcpy(Array,&tCMyDeque.m_pArray[i],sizeof(T)*m_iElementSize);
						m_pArray[i] = Array;
					}						
					m_iFrontIndex = tCMyDeque.m_iFrontIndex;
					m_iBackIndex = tCMyDeque.m_iBackIndex;
					m_curFront = &m_pArray[m_iFrontIndex][tCMyDeque.m_curFront - &tCMyDeque.m_pArray[m_iFrontIndex][0]];
					m_curBack = &m_pArray[m_iBackIndex][tCMyDeque.m_curBack - &tCMyDeque.m_pArray[m_iBackIndex][0]];
					
					m_cout = tCMyDeque.m_cout;

				}

				/********
				      ��ֵ���캯��
				**********/
				CMyDeque operator=(CMyDeque &tCMyDeque)
				{
					if(this == &tCMyDeque)
					{
						return * this;
					}

					for(int i = 0; i < m_iArraySize; ++i)
					{
						T *Array = m_pArray[i];
						if(NULL != Array)
						{
							delete []Array;
							Array = NULL;
						}
					}

					delete []m_pArray;


					m_iArraySize = tCMyDeque.m_iArraySize;
					m_iElementSize = tCMyDeque.m_iElementSize;
					m_pArray =(T**) new T[m_iArraySize];
					for(int i = 0; i < m_iArraySize; ++i)
					{
						T *Array = new T[sizeof(T) * m_iElementSize];
						T *copy = tCMyDeque.m_pArray[i];
						memcpy(Array,tCMyDeque.m_pArray[i],sizeof(T)*m_iElementSize);
						m_pArray[i] = Array;
					}						
					m_iFrontIndex = tCMyDeque.m_iFrontIndex;
					m_iBackIndex = tCMyDeque.m_iBackIndex;
					m_curFront = &m_pArray[m_iFrontIndex][tCMyDeque.m_curFront - &tCMyDeque.m_pArray[m_iFrontIndex][0]];
					m_curBack = &m_pArray[m_iBackIndex][tCMyDeque.m_curBack - &tCMyDeque.m_pArray[m_iBackIndex][0]];
					
					m_cout = tCMyDeque.m_cout;

					return * this;

				}

				T* begin()
				{
					if(this->m_curBack == &this->m_pArray[this->m_iBackIndex][this->m_iElementSize - 1])
					{
						return &this->m_pArray[this->m_iBackIndex + 1][0];
					}
					return this->m_curBack+1;
				}

				T* end()
				{
					if(this->m_curFront == &this->m_pArray[this->m_iFrontIndex][0])
					{
						return &this->m_pArray[this->m_iFrontIndex - 1][this->m_iElementSize - 1];
					}
					return this->m_curFront  - 1;
				}


				/********
				      ����ͷ������Ԫ��
				**********/
				void pushfront(T &Element)
				{
					m_cout++;
					//���ǵ�ǰ�̶���������һ��Ԫ��
					if(m_curFront != &m_pArray[m_iFrontIndex][m_iElementSize - 1])
					{
						*m_curFront= Element;
						m_curFront++;
							
					}
					else
					{
						*m_curFront= Element;
						m_iFrontIndex++;
						//���һ����������
						if(m_iFrontIndex == m_iArraySize)
						{
							//�����������飬�����ڴ��
							ReAloocFrontArray();
						}
						m_curFront = &m_pArray[m_iFrontIndex][0];	
					}
					
				}


				/********
				      ���Ӷ���ͷ�Ĵ�С
				**********/
				void ReAloocFrontArray()
				{
					T **TEMP;
					
					m_iArraySize += 5;
					TEMP = (T**) new T[m_iArraySize];
					
					for(int i = m_iArraySize - 5; i < m_iArraySize; i++)
					{
						T *Array = new T[sizeof(T) * m_iElementSize];
						memset(Array,0,sizeof(T)*m_iElementSize);
						TEMP[i] = Array;
					}

					for(int i = 0; i < m_iArraySize - 5; i++)
					{
						TEMP[i] = m_pArray[i];
					}
					
					T **swap;
					swap = TEMP;
					TEMP = m_pArray;
					m_pArray = swap;
					if(NULL != TEMP)
					{
						delete []TEMP;
					}
				}

				/********
				      ����ͷ��ɾ��Ԫ��
				**********/
				T popfront()
				{
					//�Ѿ��ǿյ���
					if(0 == m_cout)
					{
						return NULL;
					}
					T iRev;
                   //�̶�����ĵ�һ��Ԫ��
					if(m_curFront == &m_pArray[m_iFrontIndex][0])
					{
                        //���һ���̶�����
						if(m_iFrontIndex != m_iBackIndex)
						{
							//��С��������
							ReduceFrontAlocArray();
						}

						m_curFront = &m_pArray[m_iFrontIndex][m_iElementSize - 1];
						iRev = *m_curFront;
					}
					else
					{
						iRev = *(m_curFront - 1);
						m_curFront--;
					}
					m_cout--;
					return iRev;
				}

				/***************
					����ͷ����������Ĵ�С
				***************/
				void ReduceFrontAlocArray()
				{	
					if(m_iArraySize -1  != m_iFrontIndex)
					{
						m_iFrontIndex--;
						return ;
					}
					delete []m_pArray[m_iFrontIndex];
					T **TEMP;
					m_iArraySize--;
					TEMP = (T**) new T[m_iArraySize];
					

					for(int i = 0; i < m_iArraySize; i++)
					{
						TEMP[i] = m_pArray[i];
					}
					
					T **swap;
					swap = TEMP;
					TEMP = m_pArray;
					m_pArray = swap;
					m_iFrontIndex--;
					if(NULL != TEMP)
					{
						delete []TEMP;
					}
				

				}
             
				/******
					����β������Ԫ��
				*******/
				void pushback(T &Element)
				{
					m_cout++;
					//���ǵ�ǰ�̶�����ĵ�һ��Ԫ��
					if(m_curBack != &m_pArray[m_iBackIndex][0])
					{
						*m_curBack= Element;
						m_curBack--;
							
					}
					else
					{
						*m_curBack= Element;
						m_iBackIndex--;
						//���һ����������
						if(m_iBackIndex == -1)
						{
							//�����������飬�����ڴ��
							ReAloocArray();
						}
						m_curBack = &m_pArray[m_iBackIndex][m_iElementSize - 1];
					}
					
				}

				/*******************
				 ���·�����������
				********************/
				void ReAloocArray()
				{
					T **TEMP;
					m_iArraySize += 5;
					TEMP = (T**) new T[m_iArraySize];
					
					for(int i = 0; i < 5; i++)
					{
						T *Array = new T[sizeof(T) * m_iElementSize];
						memset(Array,0,sizeof(T)*m_iElementSize);
						TEMP[i] = Array;
					}

					for(int i = 5; i < m_iArraySize; i++)
					{
						TEMP[i] = m_pArray[i - 5];
					}
					
					m_iBackIndex = 5;
					m_iFrontIndex +=5;
					T **swap;
					swap = TEMP;
					TEMP = m_pArray;
					m_pArray = swap;
					if(NULL != TEMP)
					{
						delete []TEMP;
					}
				}

				/**************
					����β��ɾ��Ԫ��
				**************/
				T popback()
				{
					m_cout--;
					//�Ѿ��ǿյ���
					if(0 == m_cout)
					{
						return NULL;
					}
					T iRev;
                   //�̶���������Ԫ��
					if(m_curBack == &m_pArray[m_iBackIndex][m_iElementSize - 1])
					{
						iRev = *m_curBack;
                        //���һ���̶�����
						if(m_iFrontIndex != m_iBackIndex)
						{
							//��С��������
							ReduceBackAlocArray();
						}
						m_curBack = &m_pArray[m_iBackIndex][0];
									
					}
					else
					{
						iRev = *(m_curBack + 1); 
						m_curBack++;
					}
					return iRev;
				}

				/***************
					������������Ĵ�С
				***************/
				void ReduceBackAlocArray()
				{
					if(0 != m_iBackIndex)
					{
						m_iBackIndex++;
						return ;
					}
					delete []m_pArray[m_iBackIndex];
					T **TEMP;
					m_iArraySize--;
					TEMP = (T**) new T[m_iArraySize];
					

					for(int i = 0; i < m_iArraySize; i++)
					{
						TEMP[i] = m_pArray[i+1];
					}
					
					T **swap;
					swap = TEMP;
					TEMP = m_pArray;
					m_pArray = swap;
					m_iBackIndex = 0;
					m_iFrontIndex--;
					if(NULL != TEMP)
					{
						delete []TEMP;
					}


				}
				
				/***********
					�����Ƿ�Ϊ��
				***********/
				bool empty()
				{
					return m_count == 0;
				}
       
				/************
					��õ�i��λ�õ�Ԫ��
				************/
				T& operator[](int iIndex)
				{
					int iDiff = &m_pArray[m_iBackIndex][m_iElementSize - 1]-m_curBack;
					if(iIndex > iDiff)
					{
						int i = (iIndex - iDiff) % m_iElementSize;
						return m_pArray[m_iBackIndex + iIndex/m_iElementSize ][i];
					}

					return *(m_curBack + iIndex+1);
				}

				/***********
					ɾ����i��Ԫ��
				************/
				T erase(int iindex)
				{
                   if(iindex == 0)
				   {
					   return popback();
				   }
				   else
				   {
					   m_cout--;
					   int iElementIndex = iindex + 1;
					   	int iDiff = &m_pArray[m_iBackIndex][m_iElementSize - 1]-m_curBack + 1;
						if(iindex > iDiff)
						{
							 iElementIndex  = (iindex - iDiff) % m_iElementSize;
						}	

						T rev = *(m_curBack + iElementIndex);

					   int iArrayDelIndex = m_iBackIndex + iindex / m_iElementSize;				 					  
					   memmove(m_curBack + iElementIndex ,m_curBack + iElementIndex + 1,m_iElementSize - iElementIndex - 1);
					   if(iArrayDelIndex + 1 != m_iArraySize)
					   {
							m_pArray[iArrayDelIndex][m_iElementSize - 1] = m_pArray[iArrayDelIndex + 1][0];
					   }
					  
					   for(int i = iArrayDelIndex+1;i <= m_iFrontIndex; i++)
					   {
							memmove(&m_pArray[i][0],&m_pArray[i][1],m_iElementSize-1);
							 if(i + 1 != m_iArraySize)
							{
								m_pArray[i][m_iElementSize - 1] = m_pArray[i + 1][0];
							}
					   }	  
					return rev;			
				   }

			
				}

				/*****
					��i��λ�ò���Ԫ��
				******/
				void insert(int iindex,T element)
				{
					if(iindex == 0)
				   {
					   pushback(element);
				   }
				   else
				   {
					   m_cout++;
					   int iElementIndex = iindex + 1;
					   	int iDiff = &m_pArray[m_iBackIndex][m_iElementSize - 1]-m_curBack + 1;
						if(iindex > iDiff)
						{
							 iElementIndex  = (iindex - iDiff) % m_iElementSize;
						}				                   

					   int iArrayDelIndex = m_iBackIndex + iindex / m_iElementSize;
					   T save = m_pArray[iArrayDelIndex][m_iElementSize - 1];						  
					   memmove(m_curBack + iElementIndex + 1,m_curBack + iElementIndex,m_iElementSize - iElementIndex - 1);
					  *(m_curBack + iElementIndex) = element;
					  
					   for(int i = iArrayDelIndex+1;i <= m_iFrontIndex; i++)
					   {
						   T temp = m_pArray[i][m_iElementSize - 1];
							memmove(&m_pArray[i][1],&m_pArray[i][0],m_iElementSize-1);
							m_pArray[i][0] = save;
							save = temp;
					   }	  
				   }
				}

				int size()
				{
					return this->m_cout;
				}

		private:
				T **m_pArray;
				int m_iArraySize;
				int m_iElementSize;
				int m_iFrontIndex;
				int m_iBackIndex;
				int m_cout;
				T *m_curFront;
				T *m_curBack;

	};
}
