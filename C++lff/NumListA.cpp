#include <iostream>
#include <cstring>
#include <fstream>
#include"windows.h"
#include"numCount.h" 
#include <ctime>
using namespace std;

inline void NumList::checkNum()
{
	Node *p = last; 
	Node *t = p;
	for( ; p!=head;)//从高位开始 
	{
		if(p->data == 0)//为0就删除 
		{
			p = p->front;
			delete t;
			t = p;//把t指向删除后下一个 高位 
		}
		else break;//如果没有高位0就结束 
	}
	last = p;//末尾设成删除后的p 
}

inline void NumList::checkLen()
{
	Node *p = last;
	int cnt = 0;
	for(;p!=head->front;p = p->front)//指针p指向的不是最后一位 就向下走一位 
	{
		cnt++;
	}
	len = cnt;//数出来的长度赋值给len 
}

inline void NumList::insert(int a)
{
	if (head == 0)
	{
		head = new Node(a);
		len++;
		last = head;
	}
	else
	{
		Node *p = head;
		p->front = new Node(a, p, 0);
		len++;
		head = p->front;
	}
}

inline void NumList::insertnum(int a)
{
	if (head == 0)
	{
		head = new Node(a);
		len++;
		last = head;
	}
	else
	{
		Node *pa = last;
		pa->next = new Node(a, 0, pa);
		len++;
		last = pa->next;
	}
}

void NumList::inputNum(string s)
{
	if (s[0] != '-')
	{
		int len = s.length();
		for (int i = len - 1; i >= 0; i--)
		{
			int n = s[i] - '0';
			insertnum(n);
		}
	}
	else
	{
		int len = s.length();
		for (int i = len - 1; i >= 1; i--)
		{
			int n = s[i] - '0';
			insertnum(n);
		}
	}
}
//输出到屏幕 

void NumList::printNum()
{
	if (flag == 1)
		cout << "-";
	int s[100000];
	int lens = len - 1;
	Node *pa = head;
	if (Emptylist())
	{
		cout << "大数不存在" << endl;
		return;
	}
	else
	{
		while (pa != 0)
		{
			s[lens] = pa->data;
			lens--;
			pa = pa->next;
		}
	}
	for (int i = 0; i < len; i++)
	{
		cout<<s[i];
	}
	cout << endl << "该大数的位数为：" << len << endl;
	
}	 
//输出到fileout.txt文件中 


void NumList::printTxt()
{
	ofstream out("outfile.txt",ios::app);
	if (flag == 1)
		out << "-";
	int s[100000];
	int lens = len - 1;
	Node *p1 = head;
	if (Emptylist())
	{
		out << "大数不存在" << endl;
		return;
	}
	else
	while(p1 != 0)
	{
		s[lens] = p1->data;
		lens--;
		p1 = p1->next;
	}

	for (int i = 0; i < len; i++) out << s[i];
	out << endl;
	out << "该大数的位数为：" << len << "位。" << endl;

}
//将链表转换成字符串 

string NumList::listToString()
{
	string s;
	Node *p = last;
	for(;p!=0;p = p->front)
	{
		s+=(p->data +'0');
	}
	return s;
}
//自加 
inline NumList NumList::operator ++()
{
	int tmp = 0;
	Node *p = head;
	tmp = p->data+1;
	p->data = tmp%10;
	tmp/=10;
	if(tmp>0)//考虑进位 
	{
		for(p = p->front;p!=0;p = p->front)
		{
			tmp += p->data;
			p->data=tmp%10;
			tmp/=10; 
		}
		if(tmp>0)//如果最高位也进位,则位数加1 
		{
			len++;
			last->front = new Node(1);
			p = last;
			last = last->front;
			last->front =p; 
		} 
	}
	return *this;
}

inline NumList NumList::operator +(const NumList &list)
{
	NumList Sum;
	int tmp = 0;
	Node *p1 = head; //左链表头 
	Node *p2 = list.head; //右链表头 
	if (len >= list.len)
	{
		Node *p1 = head;
		Node *p2 = list.head;
		int t = 0;
		while (p2 != NULL)
		{
			int tmp;
			if (t == 0)
			{
				tmp = p1->data + p2->data;
			}
			else
			{
				tmp = p1->data + p2->data + t;
			}
			t = tmp / 10;
			tmp = tmp % 10;
			Sum.insertnum(tmp);
			if (t != 0 && len == list.len &&p2->next == NULL)
			{
				Sum.insertnum(1);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p1 != NULL)
		{
			if(t!= 0)
			{
				int tmp = p1->data + t;
				t = tmp / 10;
				tmp = tmp%10;
				Sum.insertnum(tmp);
				if (t != 0 && p1->next == NULL)
				{
					Sum.insertnum(1);
				}
			}
			else
			{
				Sum.insertnum(p1->data);
			}
			p1 = p1->next;
		}
		return Sum;
	}
	else 
	{
		Node* p1 = head;
		Node* p2 = list.head;
		int t = 0;
		while (p1 != 0)
		{
			int temp;
			if (t == 0)
			{
				temp = p1->data + p2->data;
			}
			else
			{
				temp = p1->data + p2->data + t;
			}
			t = temp / 10;
			temp = temp % 10;
			Sum.insertnum(temp);
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p2 != 0)
		{
			if (t != 0)
			{
				int temp = p2->data + t;
				t = temp / 10;
				temp = temp % 10;
				Sum.insertnum(temp);
				if (t != 0 && p2->next == 0)
				{
					Sum.insertnum(1);
				}
			}
			else
			{
				Sum.insertnum(p2->data);
				Sum.len++;
			}
			p2 = p2->next;
		}
		return Sum;
	}
	
}
bool NumList::operator > (const NumList &list)
{
	Node *p1 = last;
	Node *p2 = list.last;
	if (len < list.len) return false;
	else if (len > list.len) return true;
	else
	{
		while (p1 != 0)
		{
			if (p1->data < p2->data) return false;
			else if (p1->data > p2->data) return true;
			p1 = p1->front;
			p2 = p2->front;
		}
		return true;
	}
}

//bool operator >(NumList &list1,NumList &list2)
//{
//	if(list1.len>list2.len)
//		return true;
//	else if(list1.len<list2.len)
//		return false;
//	else 
//	{
//		Node *p1 = list1.last;
//		Node *p2 = list2.last;
//		while(p1 != 0)
//		{
//			if(p1->data <p2->data)
//				return false;
//			else 
//				return true;
//			p1 = p1->front;
//			p2 = p2->front;
//		}
//		return false; 
//	}
//}

inline bool NumList::operator<(const NumList &list)//(ok)
{
	Node *pa = last;
	Node *pb = list.last;
	if (len > list.len)  return false;
	else if (len < list.len) return true;
	else
	{
		while (pa != 0)
		{
			if (pa->data > pb->data) return false;
			else if (pa->data < pb->data) return true;
			pa = pa->front;
			pb = pb->front;
		}
		return false;
	}
}

NumList NumList::operator -(const NumList &list)
{
	NumList Res;
	Node *p1 = head;
	Node *p2 = list.head;
	int tmp = 0;
	if (*this > list) 
	{
		while (p2 != 0)
		{
			if (p1->data < p2->data)
			{
				int temp = p1->data + 10 - tmp - p2->data;
				tmp = 1;
				Res.insertnum(temp);
			}
			else if (p1->data == p2->data && tmp == 1)
			{
				tmp = 1;
				Res.insertnum(9);
			}
			else
			{
				int temp2 = p1->data - p2->data - tmp;
				tmp = 0;
				Res.insertnum(temp2);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p1 != 0)
		{
			if (p1->data < tmp)
			{
				Res.insertnum(9);
				tmp = 1;
			}
			else
			{
				if (p1->data - tmp == 0 && p1->next == 0)
				{
					break;
				}
				Res.insertnum(p1->data - tmp);
				tmp = 0;
			}
			p1 = p1->next;
		}
		while (Res.last->data == 0 && len > 1)
		{
			Res.last = Res.last->front;
			Res.last->next = 0;
			Res.len--;
			if (Res.last == Res.head) break;
		}
	}
	else
	{
		Res.flag = 1;
		while (p1 != 0)
		{
			if(p2->data <p1->data)
			{
				int temp = p2->data + 10 - tmp - p1->data;
				tmp = 1;
				Res.insertnum(temp);
			}
			else if (p2->data == p1->data && tmp == 1)
			{
				tmp = 1;
				Res.insertnum(9);
			}
			else
			{
				int temp2 = p2->data - p1->data - tmp;
				tmp = 0;
				Res.insertnum(temp2);
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		while (p2 != 0)
		{
			if (p2->data < tmp)
			{
				Res.insertnum(9);
				tmp = 1;
			}
			else
			{
				if (p2->data - tmp == 0 && p2->next == 0)
					break;
				Res.insertnum(p2->data - tmp);
				tmp = 0;
			}
			p2 = p2->next;
		}
		while (Res.last->data == 0 && len > 1)
		{
			Res.last = Res.last->front;
			Res.last->next = 0;
			Res.len--;
			if (Res.last == Res.head) break;
		}
	}
	
	return Res;
}

NumList NumList::operator *(const NumList &list)
{
	NumList temp1, temp2, temp3;
	temp1.insertnum(1);
	const NumList one = temp1;
	temp2 = *this;
	temp3 = list;
	NumList result;
	result.insertnum(0);
	Node* pa = head;
	int left = 0;
	if (temp2 < one || temp3 < one) return result;
	else
	{
		while (pa != 0)
		{
			NumList temp;
			for (int i = 0; i < left; i++)
			{
				temp.insertnum(0);
			}
			Node* pb = list.head;
			int t = 0;
			while (pb != 0)
			{
				int tempnum = pa->data * pb->data + t;
				t = tempnum / 10;
				tempnum = tempnum % 10;
				temp.insertnum(tempnum);
				pb = pb->next;
			}
			if (t != 0)
			{
				temp.insertnum(t);
			}
			result = result + temp;
			pa = pa->next;
			left++;
		}
		return result;
	}
}

NumList NumList::operator =(const NumList &list)
{
	this->flag = list.flag;
	if (this != &list)
	{
		if (list.head != 0) 
		{
			this->flag = list.flag;
			head = 0;
			len = 0;
			Node *pb = list.head;
			while (pb != 0)
			{
				insertnum(pb->data);
				pb = pb->next;
			}
			return *this;
		}
		else 
		{
			this->flag = list.flag;
			head = 0;
			len = 0;
			return *this;
		}
	}
	else return *this;
}


inline NumList NumList::operator /(const NumList &list)//(ok)
{
	NumList temp1, temp2;
	temp1.insertnum(1);
	const NumList one = temp1;
	temp2 = list;
	NumList result;
	if (temp2 < one)
	{
		cout << "分母为0时除法无意义，该处返回0代替。" << endl;
		result.insertnum(0);
		return result;
	}
	if (len < list.len)
	{
		result.insertnum(0);
		return result;
	}
	else
	{
		NumList end;
		end.insertnum(0);
		NumList myself = *this;
		while (1)
		{
			NumList r = list;
			NumList temp;
			if (myself < r) break;
			int i;
			for (i = 0; i < myself.len - list.len; i++) r.insert(0);
			if (myself < r)
			{
				r = list;
				for (i = 0; i < myself.len - list.len - 1; i++)
					r.insert(0);
			}
			int s = 0;
			while (1)
			{
				if (myself < r) break;
				myself = myself - r;
				s++;
			}
			for (int j = 0; j < i; j++)
				temp.insertnum(0);
			temp.insertnum(s);
			end = end + temp;
		}
		return end;
	}
}

NumList NumList::mi(const NumList &list,const NumList &mod)
{
	NumList index, zero, one;
	zero.insertnum(0);
	one.insertnum(1);
	index.insertnum(1);
	if (list.last->data == 0) return one;
	NumList temp1 = *this, temp2 = list;
	while (zero < temp2)
	{
		index = index * temp1;
		index = index % mod;
		temp2 = temp2 - one;
	}
	return index;
}

NumList NumList::operator %(const NumList &list)
{

	NumList result = *this;
	NumList temp, temp1;
	temp1 = list;
	temp = result / temp1;
	NumList temp2;
	temp2 = temp * temp1;
	result = result - temp2;
	result.flag = this->flag;
	return result;
}

inline bool NumList::Emptylist()//判空 (finish)
{
	if (head == NULL && last == NULL) return 1;
	else return 0;
}

//NumList NumList::Mi(const NumList & list, const NumList &m)
//{
//	NumList temp, temp1, temp2;
//	temp.insertnum(2);
//	temp1.insertnum(0);
//	temp2.insertnum(1);
//	const NumList two = temp;
//	const NumList zero = temp1;
//	const NumList one = temp2;
//	NumList myself = *this;
//	NumList r = list;
//	NumList result = one;
//	while (r > zero)
//	{
//		NumList t1;
//		t1 = r % two;
//		if (t1 > zero)
//		{
//			result = (result * myself) % m;
//		}
//		myself = (myself * myself) % m;
//		r = r / two;
//	}
//	return result;
//}

void enter();

void solve(string s)
{
	string m;
	cout << "请输入模数,输入0表示默认模数2^128" << endl;
	cin >> m;
	clock_t start, end;
	start = clock();
	system("cls");
	if (m == "0")
	{
		m = "340282366920938463463374607431768211456";
	}

	int lens = s.length();
	string s1, s2;
	string f;
	int marks = 0;//记录符号位
	for (int i = 0; i < lens; i++)
	{
		if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '%' || s[i] == '/' || s[i] == '^')
		{
			f = s[i];
			marks = i;
			break;
		}
	}
	for (int i = 0; i < marks; i++)
	{
		s1.append(1, s[i]);
	}
	for (int i = marks + 1; i < lens; i++)
	{
		s2.append(1, s[i]);
	}

	NumList l1, l2, l3, mo;
	l1.inputNum(s1);
	l2.inputNum(s2);
	mo.inputNum(m);
	if (f == "+")
	{
		l3 = l1 + l2;
		l3 = l3 % mo;
	}
	else if (f == "-")
	{
		l3 = l1 - l2;
		l3 = l3 % mo;
	}
	else if (f == "*")
	{
		l3 = l1 * l2;
		l3 = l3 % mo;
	}
	else if (f == "/")
	{
		l3 = l1 / l2;
		l3 = l3 % mo;
	}
	else if (f == "%")
	{
		l3 = l1 % l2;
		l3 = l3 % mo;
	}
	else if (f == "^")
	{
		l3 = l1.mi(l2, mo);
	}
	end = clock();
	double t = end - start;
	t = t / CLOCKS_PER_SEC;
	cout << "请选择输出的位置" << endl;
	cout << "1、屏幕\t2、文件\n";
	int choose2;
	cin >> choose2;
	if (choose2 == 1)
	{
		
		l3.printNum();
		cout << "耗时" << t << "s"<<endl;
		
		//mo.printNum();
	}
	else if (choose2 == 2)
	{
		ofstream out("outfile.txt", ios::app);
		out << "第一个大数为:"<<endl;
		l1.printTxt();
		out << endl;
		out << "第二个大数为:" << endl;
		l2.printTxt();
		out << endl;
		out << "模数为" << endl;
		mo.printTxt();
		out << "两数经过“" << f << "”运算后" << endl;
		l3.printTxt();
		cout << "耗时"<<t<<"s"<<endl;
		out << "耗时" << t << "s" << endl;
	
	}
	while (true)
	{
		cout << " ________________________________________________________" << endl;
		cout << "|           请输入数字选择你使用的功能                   |" << endl;
		cout << "|           1、查看输入的两个大数                        |" << endl;
		cout << "|           2、重新开始使用                              |" << endl;
		cout << "|           0、退出                                      |" << endl;
		cout << " ————————————————————————————" << endl;
		int choose3 = 0;
		cin >> choose3;

		if (choose3 == 0) {
			system("cls");
			cout << "感谢你的使用，再见" << endl;
			system("pause");
			exit(0);
		}
		else if (choose3 == 1)
		{
			system("cls");
			cout << " ________________________________________________________" << endl;
			cout << "|           请输入数字选择你使用的功能                   |" << endl;
			cout << "|           1、查看输入的两个大数                        |" << endl;
			cout << "|           2、重新开始使用                              |" << endl;
			cout << "|           0、退出                                      |" << endl;
			cout << " ————————————————————————————" << endl;
			cout << "大数1为" << s1 << "		" << "大数2为" << s2 << endl;
		}
		else
		{
			system("cls");
			enter();
		}


	}
}

void enter()
{
	cout << "                欢迎使用大整数计算                 " << "\n";
	cout << " ________________________________________________________" << endl;
	cout << "|           请输入数字选择你使用的功能                   |" << "\n";
	cout << "|           1、键盘输入大数计算式                        |" << endl;
	cout << "|           2、从文件输入大数计算式                      |" << endl;
	cout << "|           0、退出                                      |" << endl;
	cout << " ————————————————————————————" << endl;
	string choose1;
	cin >> choose1;
	if (choose1[0] == '0')
	{
		cout << "感谢你的使用，再见" << endl;
		system("pause");
		exit(0);
	}
	else if (choose1[0] == '1') {
		system("cls");
		cout << "请按数字-符号-数字格式输入" << endl;
		
		string s;
		cin >> s;
		solve(s);
	}
	else if (choose1[0] == '2')
	{
		ifstream infile("filein.txt", ios::in);
		if (!infile)
		{
			cerr << "打开文件错误" << endl;
			return;
		}
		string s;
		infile >> s;
		solve(s);
	}
	else
	{
		system("cls");
		//设置红色
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED);
		cerr << "                请选择可选功能序号" << endl;
		cerr << "                请选择可选功能序号" << endl;
		cerr << "                请选择可选功能序号" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED |
			FOREGROUND_GREEN | FOREGROUND_BLUE);//设置三色相加
		enter();
	}
}






