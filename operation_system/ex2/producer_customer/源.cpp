#include<windows.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;
#define N 10//��������С
#define WaitTime 5000//�ȴ�ʱ��
//�����ź���
HANDLE m_S_Empty;//������sem 
HANDLE m_S_Full;//������sem 
HANDLE m_S_muteX;//����
int bufferArea[N]={-1};//��Ʒ��Ϣ������
int ConsumeID = 0;//�����ѵĲ�Ʒ��
int ProductID = 0;//�����Ĳ�Ʒ��
unsigned short in = 0;//��Ʒ���뻺�������±�
unsigned short out = 0;//��Ʒ�����������±�
void Consume()
{
	ConsumeID = bufferArea[out];
	bufferArea[out] = -1;
	out = (out + 1) % N;
	cout << "����������һ����Ʒ��Ϊ" << ConsumeID << "�Ĳ�Ʒ" << endl;
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
		if (i == in)  cout << "\t<--����";
		if (i == out) cout << "\t<--����";
		cout << endl;
	}
	cout << "---------------------" << endl;
}
void Produce()
{
	cout << "\n����һ����Ʒ��Ϊ" << ++ProductID << "�Ĳ�Ʒ" << endl;
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
		if (i == in)  cout << "\t<--����";
		if (i == out) cout << "\t<--����";
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
			else cout << "��������" << endl;
		}
		else cout << "buffer��������" << endl;
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
			cout << "��������" << endl;
		}
		else cout << "buffer��������" << endl;
	}
	return 0;
}
int main() {
	m_S_muteX = CreateMutex(NULL, FALSE, NULL);
	m_S_Empty = CreateSemaphore(NULL, N, N, NULL);//������ֵΪn
	m_S_Full = CreateSemaphore(NULL, 0, N, NULL);//������ֵΪ0
	DWORD producerID;//������id
	DWORD consumerID;//������id
	HANDLE hThreads1;//�������߳�
	HANDLE hThreads2;//�������߳�
	hThreads1 = CreateThread(NULL, 0, Producer, NULL, 0, &producerID);
	if (hThreads1 == NULL) cout << "�����߷����̴߳���" << endl;
	else cout << "�����߲����ɹ�" << endl;
	hThreads2 = CreateThread(NULL, 0, Consumer, 0, 0, &consumerID);
	if (hThreads2 == NULL) cout << "�����߷����̴߳���" << endl;
	else cout << "�����߲����ɹ�" << endl;
	getchar();//�س���������
	return 0;
}
