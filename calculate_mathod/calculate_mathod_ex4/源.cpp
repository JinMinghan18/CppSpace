#include <iostream>
#include<cmath>
#include<iomanip>
using namespace std;
struct point {
	double x[10];
	double y[10];
};



double fenDuanXianXing(double a,point p1){
	int pos = 0;
	for (int i = 0; i < 6; i++) {
		if (a < p1.x[i]) {
			pos = i - 1;
			break;
		}
	}
	return (a - p1.x[pos + 1]) * p1.y[pos] / (p1.x[pos] - p1.x[pos + 1]) + (a - p1.x[pos]) * p1.y[pos + 1] / (p1.x[pos + 1] - p1.x[pos]);
}

double fenDuanErCi(double a, point p) {
	int pos = 0;
	for (int i = 0; i < 6; i++) {
		if (a < p.x[i]) {
			pos = i - 1;
			break;
		}
	}
	double k1, k2, k3;
	k1 = (a - p.x[pos]) * (a - p.x[pos + 1]) / ((p.x[pos - 1] - p.x[pos]) * (p.x[pos - 1] - p.x[pos + 1]));
	k2 = (a - p.x[pos - 1]) * (a - p.x[pos + 1]) / ((p.x[pos] - p.x[pos - 1]) * (p.x[pos] - p.x[pos + 1]));
	k3 = (a - p.x[pos - 1]) * (a - p.x[pos]) / ((p.x[pos + 1] - p.x[pos - 1]) * (p.x[pos + 1] - p.x[pos]));
	return k1 * p.y[pos - 1] + k2 * p.y[pos] + k3 * p.y[pos + 1];
}

double lagrange(double a, point p) {
	double kk[6] = {1,1,1,1,1,1};
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 6; i++) {
			if (i != k) {
				kk[k] *= (a - p.x[i]) / (p.x[k] - p.x[i]);
			}
				
		}
	}
	double res = 0;
	for (int i = 0; i < 6; i++) { 
		res += p.y[i] * kk[i];
	}
	return res;
}


int main() {
	point p;
	p.x[0] = 0.0;p.x[1] = 0.1;	p.x[2] = 0.195;	p.x[3] = 0.3;	p.x[4] = 0.401;	p.x[5] = 0.5;
	p.y[0] = 0.39894;p.y[1] = 0.39695;	p.y[2] = 0.39142;	p.y[3] = 0.38138;	p.y[4] = 0.36812;	p.y[5] = 0.35206;
	cout <<"分段线性插值的结果分别为"<<endl<<"0.15\t"<<fenDuanXianXing(0.15, p)<<"\n0.31\t"<< fenDuanXianXing(0.31, p)<<"\n0.47\t"<< fenDuanXianXing(0.47, p)<<endl;
	cout << "二次插值的结果分别为" << endl << "0.15\t" << fenDuanErCi(0.15, p) << "\n0.31\t" << fenDuanErCi(0.31, p) << "\n0.47\t" <<fenDuanErCi(0.47,p)<<endl;
	cout <<"拉格朗日插值的结果分别为"<< "\n0.15    " << lagrange(0.15, p) << "\n0.31\t" << lagrange(0.31, p) << "\n0.47\t" << lagrange(0.47, p);
}