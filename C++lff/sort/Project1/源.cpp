#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include<algorithm>
#include<queue>
using namespace std;
#define num 100
//各种排序方法的函数声明,完成注释部分的排序算法
template<class T>
void BubbleSort(vector<T> &x);//冒泡排序
template<class T>
void SelectSort(vector<T> &x);//选择排序
template<class T>
void InsertSort(vector<T> &x);//插入排序
template<class T>
void ShellSort(vector<T> &x);//希尔排序
template<class T>
void CountedSort(vector<T> &x);//计数排序
template<class T>
void RadixSort(vector<T> &x, int size);//基数排序
template<class T>
void BSTSort(vector<T> &x);//二叉查找树排序
template<class T>
void QuickSort(vector<T> &x, int p, int q);//快速排序
template<class T>
void HeapSort(vector<T> &x, int size);//堆排序


template<class T>
void Display(vector<T> &x);
template<class T>
void ResetData(vector<T> &x, vector<T> &y);//使用y重置x
//......自行添加其他必要的函数声明
int main()
{
	vector<int> a(num + 1), b(num + 1);
	//有效数据从1开始，也可以设计从0开始，自行根据需要调整
	int i;
	srand(time(0));//随机数种子初始化
	for (i = 1; i <= num; i++)
	{
		a[i] = rand() % 10000 + 1; //随机生成1-10000内的数值作为排序对象
		b[i] = a[i];
	}
	//排序前显示数据
	cout << "排序前" << endl;
	Display(a);

	//冒泡排序	
	double s1, f1;
	s1 = (double)clock();
	BubbleSort(a);
	f1 = (double)clock();
	cout << "冒泡排序后" << endl;
	Display(a);
	cout << "冒泡排序的时间为：" << f1 - s1 << "ms" << endl;

	//选择排序
	ResetData(a, b);
	double s2, f2;
	s2 = (double)clock();
	SelectSort(a);
	f2 = (double)clock();
	cout << "选择排序后" << endl;
	Display(a);
	cout << "选择排序的时间为：" << f2 - s2 << "ms" << endl;

	//插入排序
	ResetData(a, b);
	double s3, f3;
	s3 = (double)clock();
	InsertSort(a);
	f3 = (double)clock();
	cout << "插入排序后" << endl;
	Display(a);
	cout << "插入排序的时间为：" << f3 - s3 << "ms" << endl;

	//希尔排序
	ResetData(a, b);
	double s4, f4;
	s4 = (double)clock();
	ShellSort(a);
	f4 = (double)clock();
	cout << "希尔排序后" << endl;
	Display(a);
	cout << "希尔排序的时间为：" << f4 - s4 << "ms" << endl;

	//计数排序
	ResetData(a, b);
	double s5, f5;
	s5 = (double)clock();
	CountedSort(a);
	f5 = (double)clock();
	cout << "计数排序后" << endl;
	Display(a);
	cout << "计数排序的时间为：" << f5 - s5 << "ms" << endl;

	//基数排序
	ResetData(a, b);
	double s6, f6;
	s6 = (double)clock();
	RadixSort(a, num);
	f6 = (double)clock();
	cout << "基数排序后" << endl;
	Display(a);
	cout << "基数排序的时间为：" << f6 - s6 << "ms" << endl;

	//额外产品：BST排序
	ResetData(a, b);
	double s7, f7;
	s7 = (double)clock();
	//   BSTSort(a);
	f7 = (double)clock();
	cout << "BST排序后" << endl;
	Display(a);
	cout << "BST排序的时间为：" << f7 - s7 << "ms" << endl;

	//快速排序
	ResetData(a, b);
	double s8, f8;
	s8 = (double)clock();
	QuickSort(a, 1, num);
	f8 = (double)clock();
	cout << "快速排序后" << endl;
	Display(a);
	cout << "快速排序的时间为：" << f8 - s8 << "ms" << endl;

	//堆排序
	ResetData(a, b);
	double s9, f9;
	s9 = (double)clock();
	HeapSort(a, num);
	f9 = (double)clock();
	cout << "堆排序后" << endl;
	Display(a);
	cout << "堆排序的时间为：" << f9 - s9 << "ms" << endl;
	system("pause");
}

template<class T>
void Display(vector<T> &x)
{
	for (int i = 1; i <= num; i++)
	{
		cout << x[i] << " ";
		if (i % 15 == 0) cout << endl;
	}
	cout << endl;
}

template<class T>
void ResetData(vector<T> &x, vector<T> &y)//使用y重置x
{
	for (int i = 1; i <= num; i++)
	{
		x[i] = y[i];
	}
}
template<class T>
void BubbleSort(vector<T> &x)
{
	for (int i = 1; i < num; i++)
	{
		for (int t = num; t > i; t--)
		{
			if (x[t] < x[t - 1])
			{
				T temp = x[t];
				x[t] = x[t - 1];
				x[t - 1] = temp;
			}
		}
	}
}
template<class T>
void SelectSort(vector<T> &x)
{
	for (int i = 1; i < num; i++)
	{
		int temp = i;
		for (int j = i + 1; j <= num; j++)
		{
			if (x[temp] > x[j]) temp = j;
		}
		if (i != temp)
		{
			T b = x[temp];
			x[temp] = x[i];
			x[i] = b;
		}
	}
}
template<class T>
void InsertSort(vector<T> &x)
{
	T temp;
	int j;
	for (int i = 2; i <= num; i++)
	{
		if (x[i] < x[i - 1])
		{
			temp = x[i];
			for (j = i - 1; x[j] > temp&&j >= 1; j--)
			{
				x[j + 1] = x[j];
			}
			x[j + 1] = temp;
		}
	}
}
template<class T>
void ShellSort(vector<T> &x)
{
	int i, j, step;
	for (step = num / 2; step > 0; step = step / 2)
	{
		for (i = 1; i <= step; i++)
		{
			for (j = i + step; j <= num; j = j + step)
			{
				if (x[j] < x[j - step])
				{
					T temp = x[j];
					int k = j - step;
					while (k >= 1 && temp < x[k])
					{
						x[k + step] = x[k];
						k = k - step;
					}
					x[k + step] = temp;
				}
			}
		}
	}
}
template<class T>
void CountedSort(vector<T> &x)
{
	vector<int> counted(x.size());
	vector<T> temp_x(x.size());
	for (int i = 1; i < x.size(); i++)
	{
		counted[i] = 0;
		temp_x[i] = x[i];
	}
	for (int i = 1; i < x.size(); i++)
	{
		for (int j = i + 1; j < x.size(); j++)
		{
			if (x[i] > x[j]) counted[i]++;
			else counted[j]++;
		}
	}
	for (int i = 1; i < x.size(); i++)
		x[counted[i] + 1] = temp_x[i];
}
template<class T>
void RadixSort(vector<T> &x, int size)
{
	int i, j, k, factor;
	const int radix = 10;
	const int digits = 10;
	queue<T> queues[radix];
	for (i = 0, factor = 1; i < digits; factor *= radix, i++)
	{
		for (j = 1; j <= size; j++)
		{
			queues[(x[j] / factor) % radix].push(x[j]);
		}
		for (j = 0, k = 1; j < radix; j++)
			while (!queues[j].empty())
			{
				x[k++] = queues[j].front();
				queues[j].pop();
			}
	}
}
//template<class T>
//void BSTSort(vector<T> &x)
//{
//	BST<int> tree;
//	for(int i=1;i<=num;i++)
//	{
//		tree.add(x[i]);	
//	}
//	int *temp=new int[101]; 
//	tree.inorder(temp);
//	for(int i=1;i<=num;i++)
//	{
//		x[i]=temp[i];
//	}
//} 
template<class T>
int partition(vector<T> &x, int p, int q)
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
void QuickSort(vector<T> &x, int p, int q)
{
	if (p < q)
	{
		int h = partition(x, p, q);
		QuickSort(x, p, h - 1);
		QuickSort(x, h + 1, q);
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