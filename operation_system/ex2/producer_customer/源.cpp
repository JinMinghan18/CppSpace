#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define N 10//缓冲区大小
#define WaitTime 5000//等待时间
//定义信号量
HANDLE m_S_Empty;//生产者sem 
HANDLE m_S_Full;//消费者sem 
HANDLE m_S_muteX;//互斥
int bufferArea[N]={-1};//产品信息缓冲区
int ConsumeID = 0;//被消费的产品号
int ProductID = 0;//生产的产品号
unsigned short in = 0;//产品进入缓冲区的下标
unsigned short out = 0;//产品出缓冲区的下标
void Consume()
{
	ConsumeID = bufferArea[out];
	bufferArea[out] = -1;
	out = (out + 1) % N;
	cout << "消费者消费一个产品号为" << ConsumeID << "的产品" << endl;
	for (int i = 0; i < N; ++i)
	{
		cout << i << " :";
		if (bufferArea[i] == -1)
		{
			cout << "null";
		}
		else
		{
			cout << bufferArea[i];
		}
		if (i == in)  cout << "\t<--生产";
		if (i == out) cout << "\t<--消费";
		cout << endl;
	}
	cout << "---------------------" << endl;
}
void Produce()
{
	cout << "\n生产一个产品号为" << ++ProductID << "的产品" << endl;
	bufferArea[in] = ProductID;
	in = (in + 1) % N;
	for (int i = 0; i < N; i++)
	{
		cout << i << ":";

		if (bufferArea[i] == -1)
		{
			cout << "null";
		}
		else
		{
			cout << bufferArea[i];
		}
		if (i == in)  cout << "\t<--生产";
		if (i == out) cout << "\t<--消费";
		cout << endl;
	}
	cout << "---------------------" << endl;
}

DWORD WINAPI Producer(LPVOID lpPara)
{
	while (true)
	{
		if (WaitForSingleObject(m_S_Empty, WaitTime) == WAIT_OBJECT_0)
		{
			if (WaitForSingleObject(m_S_muteX, WaitTime) == WAIT_OBJECT_0)
			{
				Produce();
				ReleaseMutex(m_S_muteX);
				ReleaseSemaphore(m_S_Full, 1, NULL);
			}
			else cout << "发生互斥" << endl;
		}
		else cout << "buffer缓冲已满" << endl;
	}
	return 0;
}

DWORD WINAPI Consumer(LPVOID lpPara)
{
	//	int i = rand() %5;
	//	Sleep(4000);
	while (true)
	{
		if (WaitForSingleObject(m_S_Full, WaitTime) == WAIT_OBJECT_0)
		{
			if (WaitForSingleObject(m_S_muteX, WaitTime) == WAIT_OBJECT_0)
			{
				Consume();
				ReleaseMutex(m_S_muteX);
				ReleaseSemaphore(m_S_Empty, 1, NULL);
			}
			cout << "发生互斥" << endl;
		}
		else cout << "buffer缓冲已满" << endl;
	}
	return 0;
}
int main() {
	m_S_muteX = CreateMutex(NULL, FALSE, NULL);
	m_S_Empty = CreateSemaphore(NULL, N, N, NULL);//计数初值为n
	m_S_Full = CreateSemaphore(NULL, 0, N, NULL);//计数初值为0
	DWORD producerID;//生产者id
	DWORD consumerID;//消费者id
	HANDLE hThreads1;//生产者线程
	HANDLE hThreads2;//消费者线程
	hThreads1 = CreateThread(NULL, 0, Producer, NULL, 0, &producerID);
	if (hThreads1 == NULL) cout << "生产者发生线程错误" << endl;
	else cout << "生产者产生成功" << endl;
	hThreads2 = CreateThread(NULL, 0, Consumer, 0, 0, &consumerID);
	if (hThreads2 == NULL) cout << "消费者发生线程错误" << endl;
	else cout << "消费者产生成功" << endl;
	getchar();//回车结束进程
	return 0;
}
