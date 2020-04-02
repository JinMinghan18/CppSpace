#include<iostream>
#include<cmath>
#include <cstring>
#include <iomanip>
using namespace std;
const double eps = 0.001;
class matrix {
public:
	int n, m;
	double v[110][110];
	matrix(int n, int m) :n(n), m(m) {}
	void init() {
		memset(v, 0, sizeof(v));
	}
	matrix diag() {//ȡ�ԽǾ��� 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			C.v[i][i] = v[i][i];
		}
		return C;
	}
	matrix get_L() {// ȡ�������� 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				C.v[i][j] = -v[i][j];
			}
		}
		return C;
	}
	matrix get_R() {// ȡ�������� 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			for (int j = i + 1; j <= m; j++) {
				C.v[i][j] = -v[i][j];
			}
		}
		return C;
	}
	matrix operator* (const matrix B) const//����˷� A(n,k)*B(k,m)=C(n,m);
	{
		matrix C(n, B.m);
		C.init();
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= B.m; j++)
				for (int k = 1; k <= m; k++)
					C.v[i][j] += v[i][k] * B.v[k][j];
		return C;
	}
	matrix operator+ (const matrix B) const {//��ͬ��ģ����ӷ� 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				C.v[i][j] = v[i][j] + B.v[i][j];
			}
		}
		return C;
	}
	matrix operator- (const matrix B) const {//��ͬ��ģ����ӷ� 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				C.v[i][j] = v[i][j] - B.v[i][j];
			}
		}
		return C;
	}
	matrix Reverse() { // ȡ�� 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (v[i][j] != 0)
					C.v[i][j] = 1.0 / v[i][j];
			}
		}
		return C;
	}
	matrix change() { // ת�� 
		matrix C(m, n);
		C.init();
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {
				C.v[i][j] = v[j][i];
			}
		}
		return C;
	}
	matrix qbs() {// ȡ����ֵ 
		matrix C(n, m);
		C.init();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				C.v[i][j] = fabs(v[i][j]);
			}
		}
		return C;
	}
	void display() {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				printf("%.3f\t", v[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
};
int main() {
	matrix A(6, 6);
	matrix b(6, 1);
	b.v[1][1] = 0, b.v[2][1] = 5, b.v[3][1] = -2,
		b.v[4][1] = 5, b.v[5][1] = -2, b.v[6][1] = 6;
	for (int i = 1; i <= 6; i++) {
		for (int j = 1; j <= 6; j++) {
			if (i == j) A.v[i][j] = 4;
			else if (abs(i - j) == 1) {
				A.v[i][j] = -1;
			}
			else if (abs(i - j) == 3) {
				A.v[i][j] = -1;
			}
		}
	}
	cout << "��������" << '\n';
	A.display();
	matrix B(6, 6);
	B = A.diag().Reverse() * (A.get_L() + A.get_R());
	cout << "B����" << '\n';
	B.display();
	matrix f(6, 1);
	f = A.diag().Reverse() * b;
	cout << "f����" << '\n';
	f.display();//x = bk +f 
	matrix res(6, 1);
	res.init();
	int top = 0;
	double dis[100];
	matrix temp(6, 1);
	matrix dtemp(6, 1);
	while (1) {
		temp.init();
		dtemp.init();
		temp = B * res + f;
		dtemp = temp - res;//x(k) - x(k - 1) 
		dis[++top] = sqrt(fabs((dtemp.change() * dtemp).v[1][1]));// 2���� 
		res = temp;
		if (dis[top] < eps) {
			break;
		}
	}
	cout << "������" << top << "  ��" << '\n' << '\n';
	cout << "�������̵�2����" << '\n';
	for (int i = 1; i <= top; i++) {
		cout << dis[i] << '\n';
	}
	cout << '\n' << '\n';
	matrix t(6, 1);
	t = A * res;
	cout << "A * x����b�Ƚϣ�" << '\n';
	t.display();
	cout << "�������" << '\n';
	res.display();
}

