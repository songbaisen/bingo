// CVector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<string>
#include<vector>
#include "MyVector.cpp"
#include "MyDeque.h";
#include "MyList.h"
using namespace MyDeque;
using namespace MyVector;
using namespace LIST;


int _tmain(int argc, _TCHAR* argv[])
{
	int *t = new int[10];
	int *pb = &t[9];
	int isizea = sizeof(pb);
	int isizeb = sizeof(*pb);
	int diffa = pb - t; 
	float *ta = new float[10];
	float *pa = &ta[9];
	 isizea = sizeof(pa);
	isizeb = sizeof(*pa);
	int diffb = pa -ta;

	int *f = t;
	if(f != NULL)
	{
		delete []f;
	}
	CMyVector<int> tCMyVector(40);
	for(int i = 0; i < 30; ++i)
	{
		tCMyVector.push_back(i);
	}
	
	tCMyVector.PrinAllElement();
	int iSize = tCMyVector.size();
	int capacity = tCMyVector.capacity();
	for(int i = 0; i < 30; ++i)
	{
		tCMyVector.push_back(i);
	}
   iSize = tCMyVector.size();
    capacity = tCMyVector.capacity();
	tCMyVector.PrinAllElement();

	CMyVector<int> vTemp;
	vTemp.swap(tCMyVector);

	iSize = vTemp.size();
	capacity = vTemp.capacity();
	vTemp.PrinAllElement();

	tCMyVector = vTemp;
	tCMyVector.PrinAllElement();
	tCMyVector.resize(20);
	tCMyVector.PrinAllElement();

	tCMyVector.clear();
	
	 iSize = tCMyVector.size();
    capacity = tCMyVector.capacity();
	tCMyVector.ClearAll();
	iSize = tCMyVector.size();
    capacity = tCMyVector.capacity();
    tCMyVector.PrinAllElement();

	CMyVector<string> vStr;
	string sTemp = "a";
	vStr.push_back(sTemp);
	sTemp = "b";
	vStr.push_back(sTemp);
	sTemp = "c";
	vStr.push_back(sTemp);
	sTemp = "d";
	vStr.push_back(sTemp);
	sTemp = "e";
	vStr.push_back(sTemp);
    vStr.PrinAllElement();
	int index = 1;
	vStr.erase(index);

	CMyVector<string> ::iterator iter = vStr.begin();
	while( iter != vStr.end())
	{
		if(*iter == "a")
		{
			iter = vStr.erase(iter);
			string sTemp = *iter;
		}
		cout<<*iter++<<endl;
	}

	vStr.reverse();
	vStr.PrinAllElement();

	int iTest = 1;
	int *p[5];
//	p= new int[5];
	p[0]=&iTest;
	p[1]=&iTest;
	int **q;
	q = (int **)new int[5];
	q[0] = &iTest;
	CMyDeque<int> dCMyDeque;
    /*int ivalue = 4;
	dCMyDeque.pushback(ivalue);
	ivalue = 5;
	dCMyDeque.pushback(ivalue);*/

	for(int i = 0;i < 90000; i++)
	{
		dCMyDeque.pushfront(i);
	}
	
	int iTestb = dCMyDeque[0];
	int iTesta = dCMyDeque[1001];

	for(int i = 5000;i !=0; i--)
	{
		int iTest = dCMyDeque.popfront();
	}
	int iInsertvalue = dCMyDeque[5];
	dCMyDeque.insert(5,100);
	iInsertvalue = dCMyDeque[4];
	 iInsertvalue = dCMyDeque[5];
	 iInsertvalue = dCMyDeque[6];
	
	 CMyDeque<int> cCMyDeque;
	 cCMyDeque = dCMyDeque;
	 iInsertvalue = cCMyDeque.erase(5);
	iInsertvalue = cCMyDeque[4];
	 iInsertvalue = cCMyDeque[5];
	 iInsertvalue = cCMyDeque[6];

	
	  class CMyList<int> tCMyList;
	  for(int i = 100; i >=0; i --)
	  {
		tCMyList.pushfront(i);
	  }
	  
	  int itesta = tCMyList[77];

	  tCMyList.insert(4,99);
      tCMyList.printelement();
	  int testaaai = tCMyList.erase(4);
	  class CMyList<int> pCopy = tCMyList;
	   pCopy = tCMyList;
	  tCMyList.printelement();
	  pCopy.sort();
	  pCopy.printelement();
	  int ia  = tCMyList.popfront();
	  tCMyList.popfront();
	  ia = tCMyList.popend();
	  tCMyList.pushend(88);
	  tCMyList.pushend(888);
	  
	   tCMyList.printelement();
	 cout<<"size is "<<tCMyList.size()<<endl;
	char c;
	cin>>c;
	return 0;
}

