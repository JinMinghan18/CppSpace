#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include "BST.h"

//......�������������Ҫ�Ŀ�
using namespace std;
#define num 100
//�������򷽷��ĺ�������,���ע�Ͳ��ֵ������㷨
template<class T>
void BubbleSort(vector<T> &x);//ð������
template<class T>
void SelectSort(vector<T> &x);//ѡ������
template<class T>
void InsertSort(vector<T> &x);//��������
template<class T>
void ShellSort(vector<T> &x);//ϣ������
template<class T>
void CountedSort(vector<T> &x);//��������
template<class T>
void RadixSort(vector<T> &x);//��������
template<class T>
void BSTSort(vector<T> &x);//�������������

template<class T>
void QuickSort(vector<T> &x,int p,int q);//��������
template<class T>
void HeapSort(vector<T> &x,int size);//������


template<class T>
void Display(vector<T> &x);
template<class T>
void ResetData(vector<T> &x,vector<T> &y);//ʹ��y����x
//......�������������Ҫ�ĺ�������

 







int main()
{
	clock_t start,end;
	double sum;
	vector<int> a(num+1),b(num+1); 
	//��Ч���ݴ�1��ʼ��Ҳ������ƴ�0��ʼ�����и�����Ҫ����
    int i;
    srand(time(0));//��������ӳ�ʼ��
	for(i=1;i<=num;i++)
	{	a[i]=rand()%10000+1; //�������1-10000�ڵ���ֵ��Ϊ�������
	    b[i]=a[i];
	}
	//����ǰ��ʾ����
	cout<<"����ǰ"<<endl;
    Display(a);
	//ð������
	start = clock();
    BubbleSort(a);
    end = clock();
    sum = (double)(start - end)/CLOCKS_PER_SEC;
	cout<<"ð�������"<<endl;
	Display(a);
	cout<<"����ʱ��"<<sum<<endl; 
    //ѡ������
   ResetData(a,b);
   start = clock();
   SelectSort(a);
   end= clock();
   sum = (double)(start - end)/CLOCKS_PER_SEC;
   cout<<"ѡ�������"<<endl;
   Display(a);
   cout<<"����ʱ��"<<sum<<endl; 
   //��������
   ResetData(a,b);
   start = clock();
   InsertSort(a);
   end = clock();
   sum = (double)(start - end)/CLOCKS_PER_SEC;
   cout<<"���������"<<endl;
   Display(a);
   cout<<"����ʱ��"<<sum<<endl; 
   
   //ϣ������
   ResetData(a,b);
   start = clock();
   ShellSort(a);
   end = clock();
   sum = (double)(start - end)/CLOCKS_PER_SEC;
   cout<<"ϣ�������"<<endl;
   Display(a);
   cout<<"����ʱ��"<<sum<<endl; 
    //��������
   ResetData(a,b);
   start = clock();
   CountedSort(a);
   end = clock();
   sum = (double)(start - end)/CLOCKS_PER_SEC;
   cout<<"���������"<<endl;
   Display(a);
   cout<<"����ʱ��"<<sum<<endl; 
    //��������
   ResetData(a,b);
   start = clock();
   RadixSort(a);
   end = clock(); 
   sum = (double)(start - end)/CLOCKS_PER_SEC;
   cout<<"���������"<<endl;
   Display(a);
   cout<<"����ʱ��"<<sum<<endl; 
   //�����Ʒ��BST����
   ResetData(a, b);
   start = clock();
   BSTSort(a);
   end = clock(); 
   sum = (double)(start - end)/CLOCKS_PER_SEC;
   cout << "BST�����" << endl;
   Display(a);
   cout<<"����ʱ��"<<sum<<endl; 

  //��������
  ResetData(a,b);
  start = clock();
  QuickSort(a,1,num);
  end = clock();
  sum = (double)(start - end)/CLOCKS_PER_SEC;
  cout<<"���������"<<endl;
  Display(a);
  cout<<"����ʱ��"<<sum<<endl; 
 // ������
  ResetData(a,b);
  start = clock();
  HeapSort(a,num);
  end = clock();
  sum = (double)(start - end)/CLOCKS_PER_SEC;
  cout<<"�������"<<endl;
  Display(a);
  cout<<"����ʱ��"<<sum<<endl; 
   system("pause");
}

template<class T>
void Display(vector<T> &x)
{    
	for(int i=1;i<=num;i++)
	{	cout<<x[i]<<" ";
	    if(i%15==0) cout<<endl;
	}
	cout << endl;
}

template<class T>
void ResetData(vector<T> &x,vector<T> &y)//ʹ��y����x
{
	for(int i=1;i<=num;i++)
	{
		x[i]=y[i];
	}
}
template<class T>
void BubbleSort(vector<T> &x)
{
	int tmp = 0;
	for(int i = 1;i<=100;i++)
	{
		int flag = 0;//�Ż��㷨�ã��ж��Ƿ����
		for(int j = 1;j<=100-i;j++)
		{
			if(x[j]>x[j+1])
			{
				tmp = x[j];
				x[j] = x[j+1];
				x[j + 1] = tmp;
				flag = 1;
 			}
		} 
		if(flag ==0)
		{
			return ;
		}
	}
}

template<class T>
void SelectSort(vector<T> &x)//ѡ������
{
	int left = 1;
	int right = num;
	while(left<right) 
	{
		int max = left;
		int min = right;
		for(int i = 1+left;i<=right;i++)
		{
			if(x[i]<x[min])
			{
				min = i;
			}
			if(x[i]>x[max])
			{
				max = i;
			}
		}
		if(min != left)
		{
			int tmp = x[left];
			x[left] = x[min];
			x[min] = tmp;
		}
		if(max == left)
		{
			max = min;
		}
		if(max != right) 
		{
			int tmp = x[right];
			x[right] = x[max];
			x[max] = tmp;
		}
		left++;
		right--;
	}
} 
template<class T>
void InsertSort(vector<T> &x)//��������
{
	for (int i = 1; i <= num; i++) 
	{
		for (int j = i; j > 0; j--)
		{
			if (x[j] < x[j - 1])
			{
				int tmp = x[j];
				x[j] = x[j - 1];
				x[j - 1] = tmp;
			}
		}
	}
}
template<class T>
void ShellSort(vector<T> &x)//ϣ������
{
	int h = 1;
	while (h <  num / 3)
	{
		h = 3 * h + 1;
	}
	while (h >= 1)
	{
		for (int i = h; i <= num; i++)
		{
			for (int j = i; j >= h && x[j] < x[j - h]; j -= h)
			{
				swap(x[j], x[j - h]);
			}
		}
		h /= 2;
	}
}
template<class T>
void CountedSort(vector<T> &x)//��������
{
	int max, min;
	max = min = x[0];
	for (int i = 1; i <= num; i++)
	{
		if (x[i] > max) max = x[i];
		if (x[i] < min) min = x[i];
	}
	int tmp = max - min + 1;
	vector<int> s(tmp);
	for (int i = 1; i <= num; i++)
	{
		s[x[i] - min]++;
	}
	int cnt = 1;
	for (int i = 0; i < tmp; i++)
	{
		for (int j = 0; j < s[i]; j++)
		{
			x[cnt] = i + min;
			cnt++;
		}
	}
}
template<class T>
int maxlen(T a)
{
	double aa = a;
	int cnt = 0;
	while (aa > 1)
	{
		aa /= 10;
		cnt++;
	}
	return cnt;
}
template<class T>
void RadixSort(vector<T> &x)//��������
{
	int maxl = 0;//���λ��
	queue<T> queues[10];
	for (int i = 0; i < num; i++)
	{
		if (maxl < maxlen(x[i]))	maxl = maxlen(x[i]);
	}

	for (int i = 0; i < maxl; i++)
	{
		for (int j = 1; j <= num; j++)
		{
			int res = (int)(x[j] / pow(10,i)) % 10;
			queues[res].push(x[j]);
		}
		for (int k = 0,cnt = 1 ; k < 10; k++)
		{
			while (!queues[k].empty())
			{
				x[cnt++] = queues[k].front();
				queues[k].pop();
			}
		}
	}
}
template<class T>
int spilt(vector<T> &x, int p, int q)
{
	int i = p - 1;
	for (int j = p; j <= q; j++)
	{
		if (x[j] < x[q])
		{
			swap(x[++i], x[j]);
		}
	}
	swap(x[++i], x[q]);
	return i;
}
template<class T>
void QuickSort(vector<T> &x,int p ,int q)//��������
{
	if (p < q)
	{
		int pos = spilt(x, p, q);
		QuickSort(x, p, pos - 1);
		QuickSort(x, pos + 1, q);
	}
}
template<class T>
void adjust(vector<T> &x, int node, int size)
{
	int left = 2 * node;
	int right = 2 * node + 1;
	int max = node;
	if (left<size&&x[left]>x[max]) max = left;
	if (right<size&&x[right]>x[max]) max = right;
	if (max != node)
	{
		swap(x[max], x[node]);
		adjust(x, max, size);
	}
}
template<class T>
void HeapSort(vector<T> &x, int size)
{
	for (int i = size / 2; i >= 1; i--)
	{
		adjust(x, i, size);
	}
	for (int i = size; i >= 1; i--)
	{
		swap(x[1], x[i]);
		adjust(x, 1, i);
	}
}
template<class T>
void BSTSort(vector<T> &x)
{
	BST<int> tree;
	for (int i = 1; i <= num; i++)
	{
		tree.add(x[i]);
	}
	int *temp = new int[101];
	tree.inorder(temp);
	for (int i = 1; i <= num; i++)
	{
		x[i] = temp[i];
	}
}
