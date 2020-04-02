#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
#define e 0.00000001
#define maxn 50

int n = 4;
double matrix[maxn][maxn];
double b[maxn];
double m[maxn][maxn];
double x[maxn];

//中间矩阵输出
//参数为小原次数
void PrintProc(int cases) {
	cout << "第" << cases << "次消元结果" << endl;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			cout << setw(10) << matrix[i][j] << " ";
		}
		cout << setw(10)<< b[i] << endl<<endl;
	}
}
void Printres() {
	for(int i = 1;i<=n;i++)
		cout << "x" << i << "= " << setprecision(11)<<x[i]<<endl;
}


void ShunXuXiaoYuan() {//顺序消元法
	//消元计算
	for (int k = 1; k < n; k++) {
		for (int i = k + 1; i <= n; i++) {
			m[i][k] = matrix[i][k] / matrix[k][k];
			for (int j = k + 1; j <= n; j++) {
				matrix[i][j] -= m[i][k] * matrix[k][j];
			}
		}
		for (int i = k + 1; i <= n; i++) {
			b[i] -= m[i][k] * b[k];
		}
		PrintProc(k);
	}
	//回代
	x[n] = b[n] / matrix[n][n];
	for (int i = n - 1; i > 0; i--) {
		x[i] = b[i];
		for (int j = i + 1; j <= n; j++) {
			x[i] -= matrix[i][j] * x[j];
		}
		x[i] /= matrix[i][i];
	}
	Printres();
}

void LieZhuXiaoYuan() {
	for (int k = 1; k < n; k++) {
		double abs_max = -1;
		int max_ik;
		for (int i = k; i <= n; i++) {
			if (abs(matrix[i][k]) > abs_max) {
				abs_max = abs(matrix[i][k]);
				max_ik = i;
			}
		}
		if (max_ik != k) {
			double temp;
			for (int j = 1; j <= n; j++) {
				temp = matrix[max_ik][j];
				matrix[max_ik][j] = matrix[k][j];
				matrix[k][j] = temp;
			}
			temp = b[max_ik];
			b[max_ik] = b[k];
			b[k] = temp;
		}
		for (int i = k + 1; i <= n; i++) {
			matrix[i][k] /= matrix[k][k];
			for (int j = k + 1; j <= n; j++) {
				matrix[i][j] -= matrix[i][k] * matrix[k][j];
			}
			b[i] -= matrix[i][k] * b[k];
		}
		PrintProc(k);
		if (k < n - 1) continue;
		else {
			if (abs(matrix[n][n]) < e) {
				cout << 0;
				break;
			}
			else {
				x[n] = b[n] / matrix[n][n];
				for (int i = n - 1; i > 0; i--) {
					x[i] = b[i];
					for (int j = i + 1; j <= n; j++) {
						x[i] -= matrix[i][j] * x[j];
					}
					x[i] /= matrix[i][i];
				}
				Printres();
			}
		}
	}
}


int main()
{
	int n = 4;
	matrix[1][1] = 1.1348; matrix[1][2] = 3.8326; matrix[1][3] = 1.1651; matrix[1][4] = 3.4017;
	matrix[2][1] = 0.5301; matrix[2][2] = 1.7875; matrix[2][3] = 2.5330; matrix[2][4] = 1.5435;
	matrix[3][1] = 3.4129; matrix[3][2] = 4.9317; matrix[3][3] = 8.7643; matrix[3][4] = 1.3142;
	matrix[4][1] = 1.2371; matrix[4][2] = 4.9998; matrix[4][3] = 10.6721; matrix[4][4] = 0.0147;
	b[1] = 9.5342; b[2] = 6.3941; b[3] = 18.4231; b[4] = 16.9237;
	ShunXuXiaoYuan();
	//LieZhuXiaoYuan();
}