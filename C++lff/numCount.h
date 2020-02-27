#pragma once
#include<iostream>
#include <string>
using namespace std;
class Node
{
	public:
		//三个函数接口返回节点的data/front/next 
		Node *next;//指向后面连接的节点 
		Node *front;//指向前一个节点 
		int data;
		Node(int a = 0,Node *n = NULL,Node *f =NULL):data(a),next(n),front(f){}
};
//十进制运算的类 
class NumList
{
	private:
		Node *head;//最低位，链表最前 
		Node *last;
	public:
		int flag;//记录正负信息 0为正 1为负 
		int len;//链表长度
		NumList(){head = 0;last = 0;len = 0;flag = 0;}
		void checkNum();//删除高位的0√ 
		void checkLen();//确定链表的长度用于比较√
		void printNum();//√ 
		void inputNum(string s);//将输入的字符转存到链表里√
		void printTxt();// √ 
		string listToString();//链表转为字符串√
		void insert(int a);//在最低位加数字√
		void insertnum(int a);//在最高位加数字
		bool operator <(const NumList &list);//运算符<的重载 
		bool Emptylist();//判空
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
