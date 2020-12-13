#include<string>
#include<iostream>
#include<fstream>
#include<stack>
#include<map>
#include<unordered_map>
#include<vector>
#include<set>
using namespace std;

const int n = 1e3 + 10;
ofstream out("output.txt");

unordered_map<char, int> priority;

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
        out << s.top();
        s.pop();
    }
}

class Edge {
public:
    Edge(int _st = -1, int _ed = -1, int _value = -1) :st(_st), ed(_ed), value(_value) {};
    int st, ed, value;
};

class Regular_Expression {
public:
    Regular_Expression();
    void NewInfix();    //添加.
    void Infix_To_Postfix();    //中缀转后缀
    void Postfix_To_NFA();  //后缀转NFA
    void write();
    char Infix[n], Postfix[n];   //中缀，后缀
    vector<Edge> Transfer;  //转移函数
    vector<int> State;  //状态机
    int Start, End;
    string notation;
};

//从文件中读取正规式
Regular_Expression::Regular_Expression() {
    ifstream in("input.txt");
    in >> notation >> Infix;
    in.close();
}

void Regular_Expression::write()
{
    vector<int> Start, End;
    Start.resize(State.size());
    End.resize(State.size());
    out << "状态集合:";
    for (vector<int>::iterator it = State.begin(); it != State.end(); it++)
    {
        PrintChar(*it);
        if (it + 1 != State.end()) out << ',';
    }
    out << "\n符号集合:" << notation;
    for (vector<Edge>::iterator it = Transfer.begin(); it != Transfer.end(); it++)
    {
        End[it->st]++;
        Start[it->ed]++;
    }
    for (size_t i = 1; i <= State.size(); i++)
    {
        if (Start[i] == 0) this->Start = i;
        if (End[i] == 0) this->End = i;
    }
    out << "\n初态集:";
    PrintChar(this->Start);
    out << "\n终态集:";
    PrintChar(this->End);
    out << "\n转移函数(-1为空):\n";
    for (vector<Edge>::iterator it = Transfer.begin(); it != Transfer.end(); it++)
    {
        out << "(";
        PrintChar(it->st);
        out << "," << it->value << ",";
        PrintChar(it->ed);
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
            // )(   )0  *(  *0  0(  00六种情况中间要添加.
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
    // 设置优先级
    priority['*'] = 3;
    priority['.'] = 2;
    priority['|'] = 1;

    Regular_Expression reg;
    reg.NewInfix();
    cout << reg.Infix << '\n';      // 输出添加.后的中缀表达式
    reg.Infix_To_Postfix();     //中缀转后缀
    cout << reg.Postfix << '\n';    // 输出后缀表达式
    reg.Postfix_To_NFA();       // 后缀转NFA
    reg.write();                // 输出结果
    return 0;
}

// (12)*(1*0)1(12)0(0)0 测试添加.