#pragma once
#include <utility>
#include <iostream>
using namespace std;
namespace MyDeque
{
	/*****************************************

     队列的实现如下所示，是由一个索引数组，来管理一定数量的定长内存块。在队列的头和尾部

	 插入和删除元素有较高的效率。为了保证对外的连续性，队列需要维持一个复杂的索引。因此在

	 队列的中间插入和删除元素，都涉及到内存的移动。效率较低。并且其随即访问的效率也没有

	 vector高。假如需要对队列排序，可以先用vector排序，排好后放入队列中。
               
     索引数组                         定长内存块
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
				      拷贝构造函数
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
				      赋值构造函数
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
				      队列头部加入元素
				**********/
				void pushfront(T &Element)
				{
					m_cout++;
					//不是当前固定数组的最后一个元素
					if(m_curFront != &m_pArray[m_iFrontIndex][m_iElementSize - 1])
					{
						*m_curFront= Element;
						m_curFront++;
							
					}
					else
					{
						*m_curFront= Element;
						m_iFrontIndex++;
						//最后一个索引数组
						if(m_iFrontIndex == m_iArraySize)
						{
							//扩大索引数组，增加内存块
							ReAloocFrontArray();
						}
						m_curFront = &m_pArray[m_iFrontIndex][0];	
					}
					
				}


				/********
				      增加队列头的大小
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
				      队列头部删除元素
				**********/
				T popfront()
				{
					//已经是空的了
					if(0 == m_cout)
					{
						return NULL;
					}
					T iRev;
                   //固定数组的第一个元素
					if(m_curFront == &m_pArray[m_iFrontIndex][0])
					{
                        //最后一个固定数组
						if(m_iFrontIndex != m_iBackIndex)
						{
							//缩小索引数组
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
					调整头部索引数组的大小
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
					队列尾部插入元素
				*******/
				void pushback(T &Element)
				{
					m_cout++;
					//不是当前固定数组的第一个元素
					if(m_curBack != &m_pArray[m_iBackIndex][0])
					{
						*m_curBack= Element;
						m_curBack--;
							
					}
					else
					{
						*m_curBack= Element;
						m_iBackIndex--;
						//最后一个索引数组
						if(m_iBackIndex == -1)
						{
							//扩大索引数组，增加内存块
							ReAloocArray();
						}
						m_curBack = &m_pArray[m_iBackIndex][m_iElementSize - 1];
					}
					
				}

				/*******************
				 重新分配索引数组
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
					队列尾部删除元素
				**************/
				T popback()
				{
					m_cout--;
					//已经是空的了
					if(0 == m_cout)
					{
						return NULL;
					}
					T iRev;
                   //固定数组的最后元素
					if(m_curBack == &m_pArray[m_iBackIndex][m_iElementSize - 1])
					{
						iRev = *m_curBack;
                        //最后一个固定数组
						if(m_iFrontIndex != m_iBackIndex)
						{
							//缩小索引数组
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
					调整索引数组的大小
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
					队列是否为空
				***********/
				bool empty()
				{
					return m_count == 0;
				}
       
				/************
					获得第i个位置的元素
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
					删除第i个元素
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
					第i个位置插入元素
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
