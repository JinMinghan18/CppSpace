#include <iostream>
#include <cmath>
#include <iomanip>
#include<fstream>
using namespace std;
#define e 2.7182828

double getValue(double x) 
{
	return pow(e, x) + 10 * x - 2;
}

//二分法求方程近似根

//int main()
//{
//	double left_Boundary = 0, right_Boundary = 1;
//	double temp = (left_Boundary + right_Boundary) / 2;
//
//	ofstream fout("data2.txt");
//
//	while (abs(getValue(temp))>0.5*pow(10,-3))
//	{
//		if (getValue(temp) * getValue(right_Boundary) < 0)
//			left_Boundary = temp;
//		if (getValue(temp) * getValue(left_Boundary) < 0)
//			right_Boundary = temp;
//		temp = (right_Boundary + left_Boundary) / 2;
//		fout << temp << endl;
//		cout << temp << endl;
//	}
//}