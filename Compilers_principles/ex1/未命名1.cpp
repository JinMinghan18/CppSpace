#if(__cplusplus == 201103L)
#include <unordered_map>
#include <unordered_set>
#else
#include <tr1/unordered_map>
#include <tr1/unordered_set>
namespace std
{
    using std::tr1::unordered_map;
    using std::tr1::unordered_set;
}
#endif
#include<bits/stdc++.h> 
using namespace std;

const int n = 1e3 + 10;
ofstream out("output.txt");

map<char, int> priority;

inline bool CheckNumber(char a) { return (a >= '0' && a <= '9'); }
inline void PrintChar(int v)
{
    stack<char> s;
    do
    {
        s.push(v % 26 + 65);
        v /= 26;
    } while (v);
    while (!s.empty())
    {
    	cout<< s.top();
        out << s.top();
        s.pop();
    }
}

class Edge {
public:
    Edge(int _st = -1, int _ed = -1, int _value = -1) :st(_st), ed(_ed), value(_value) {};
    int st, ed, value;//��㣬�յ㣬ֵ 
};

class Regular_Expression {
public:
    Regular_Expression();
    void NewInfix();    //���.
    void Infix_To_Postfix();    //��׺ת��׺
    void Postfix_To_NFA();  //��׺תNFA
    void write();//������ļ���dos���� 
    char Infix[n], Postfix[n];   //��׺����׺
    vector<Edge> Transfer;  //ת�ƺ���
    vector<int> State;  //״̬��
    int Start, End;
    string notation;
};

//���ļ��ж�ȡ����ʽ
Regular_Expression::Regular_Expression() {
    ifstream in("input.txt");
    in >> notation >> Infix;//������ż��ϡ���׺���ʽ 
    in.close(); 
}

void Regular_Expression::write()
{
    vector<int> Start, End;
    Start.resize(State.size());
    End.resize(State.size());
    out << "״̬����:";
    for (vector<int>::iterator it = State.begin(); it != State.end(); it++)
    {
        PrintChar(*it);
        if (it + 1 != State.end()) out << ',';
    }
    out << "\n���ż���:" << notation;
    for (vector<Edge>::iterator it = Transfer.begin(); it != Transfer.end(); it++)
    {
        End[it->st]++;
        Start[it->ed]++;
    }
    for (size_t i = 0; i < State.size(); i++)
    {
        if (Start[i] == 0) this->Start = i;
        if (End[i] == 0) this->End = i;
    }
    cout << "\n��̬��:";
    out << "\n��̬��:";
    PrintChar(this->Start);
    out << "\n��̬��:";
    cout << "\n��̬��:";
    PrintChar(this->End);
    out << "\nת�ƺ���(-1Ϊ��):\n";
	cout << "\nת�ƺ���(-1Ϊ��):\n";
    for (vector<Edge>::iterator it = Transfer.begin(); it != Transfer.end(); it++)
    {
    	cout<< "(";
        out << "(";
        PrintChar(it->st);
        cout << "," << it->value << ",";
        out << "," << it->value << ",";
        PrintChar(it->ed);
        cout << ")\n";
		out << ")\n";
    }
}

void Regular_Expression::NewInfix()
{
    int len = strlen(Infix), len2 = 0;
    char NewInfix[n] = {};
    for (int i = 0; i < len; i++)
    {
        NewInfix[len2++] = Infix[i];
        if (i + 1 < len)
        {
            // )(   )0  *(  *0  0(  00��������м�Ҫ���.
            if (Infix[i] == ')' && Infix[i + 1] == '(' ||
                Infix[i] == ')' && CheckNumber(Infix[i + 1]) ||
                Infix[i] == '*' && Infix[i + 1] == '(' ||
                Infix[i] == '*' && CheckNumber(Infix[i + 1]) ||
                CheckNumber(Infix[i]) && Infix[i + 1] == '(' ||
                CheckNumber(Infix[i]) && CheckNumber(Infix[i + 1])
                )
                NewInfix[len2++] = '.';
        }
    }
    for (int i = 0; i < len2; i++) Infix[i] = NewInfix[i];
}
//��׺ת��׺ 
void Regular_Expression::Infix_To_Postfix()
{
    int len = strlen(Infix), len2 = 0;
    stack<char> s;
    for (int i = 0; i < len; i++)
    {
        char c = Infix[i];
        if (CheckNumber(c)) { Postfix[len2++] = c; continue; }
        switch (c)
        {
        case '(':   s.push(c);    break;
        case ')':
            while (s.top() != '(')
            {
                Postfix[len2++] = s.top();
                s.pop();
            }
            s.pop();
            break;
        case '*':   Postfix[len2++] = '*'; break;
        default:
            while (!s.empty()) {
                char t = s.top();
                if (priority[t] >= priority[c]) {
                    Postfix[len2++] = t;
                    s.pop();
                }
                else {
                    s.push(c);
                    break;
                }
            }
            if (s.empty()) s.push(c);
        }
    }
    while (!s.empty()) {
        Postfix[len2++] = s.top();
        s.pop();
    }
}
//��׺תnfa 
void Regular_Expression::Postfix_To_NFA()
{
    int len = strlen(Postfix);
    stack<Edge> s;
    for (int i = 0; i < len; i++)
    {
        char c = Postfix[i];
        if (CheckNumber(c))
        {
            size_t n = State.size();
            State.push_back(n);
            State.push_back(n + 1);
            Edge e(n, n + 1, c - 48);
            Transfer.push_back(e);
            s.push(e);
        }
        else if (c == '*') {
            size_t n = State.size();
            State.push_back(n);
            State.push_back(n + 1);
            Edge tmp = s.top();
            s.pop();
            Transfer.push_back(Edge(tmp.ed, tmp.st, -1));
            Transfer.push_back(Edge(n, tmp.st, -1));
            Transfer.push_back(Edge(n, n + 1, -1));
            Transfer.push_back(Edge(tmp.ed, n + 1, -1));
            s.push(Edge(n, n + 1, -1));
        }
        else if (c == '|') {
            size_t n = State.size();
            State.push_back(n);
            State.push_back(n + 1);
            Edge tmp1 = s.top();
            s.pop();
            Edge tmp2 = s.top();
            s.pop();
            Transfer.push_back(Edge(n, tmp1.st, -1));
            Transfer.push_back(Edge(n, tmp2.st, -1));
            Transfer.push_back(Edge(tmp1.ed, n + 1, -1));
            Transfer.push_back(Edge(tmp2.ed, n + 1, -1));
            s.push(Edge(n, n + 1));
        }
        else if (c == '.') {
            Edge tmp2 = s.top();
            s.pop();
            Edge tmp1 = s.top();
            s.pop();
            Transfer.push_back(Edge(tmp1.ed, tmp2.st, -1));
            s.push(Edge(tmp1.st, tmp2.ed, -1));
        }
    }
}

int main()
{
    // �������ȼ�
    priority['*'] = 3;
    priority['.'] = 2;
    priority['|'] = 1;

    Regular_Expression reg;
    reg.NewInfix();
    cout << reg.Infix << '\n';      // ������.�����׺���ʽ
    reg.Infix_To_Postfix();     //��׺ת��׺
    cout << reg.Postfix << '\n';    // �����׺���ʽ
    reg.Postfix_To_NFA();       // ��׺תNFA
    reg.write();                // ������
    system("pause"); 
	return 0;
}

// (12)*(1*0)1(12)0(0)0 �������.
