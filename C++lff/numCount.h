#pragma once
#include<iostream>
#include <string>
using namespace std;
class Node
{
	public:
		//���������ӿڷ��ؽڵ��data/front/next 
		Node *next;//ָ��������ӵĽڵ� 
		Node *front;//ָ��ǰһ���ڵ� 
		int data;
		Node(int a = 0,Node *n = NULL,Node *f =NULL):data(a),next(n),front(f){}
};
//ʮ����������� 
class NumList
{
	private:
		Node *head;//���λ��������ǰ 
		Node *last;
	public:
		int flag;//��¼������Ϣ 0Ϊ�� 1Ϊ�� 
		int len;//������
		NumList(){head = 0;last = 0;len = 0;flag = 0;}
		void checkNum();//ɾ����λ��0�� 
		void checkLen();//ȷ������ĳ������ڱȽϡ�
		void printNum();//�� 
		void inputNum(string s);//��������ַ�ת�浽�������
		void printTxt();// �� 
		string listToString();//����תΪ�ַ�����
		void insert(int a);//�����λ�����֡�
		void insertnum(int a);//�����λ������
		bool operator <(const NumList &list);//�����<������ 
		bool Emptylist();//�п�
		NumList operator +(const NumList &list);
		NumList operator -(const NumList &list);
		NumList operator *(const NumList &list);
		NumList operator /(const NumList &list);
		NumList operator %(const NumList &list);
		NumList operator =(const NumList &list);
		NumList mi(const NumList &list,const NumList &mod);
		NumList operator ++();
		//NumList Mi(const NumList &list ,const NumList &m);
		bool operator>(const NumList &list);
		friend void enter();
		friend void solve(string s);
};
