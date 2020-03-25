#include <iostream>
#include <cmath>
#include<iomanip>
#include<fstream>
using namespace std;
#define maxIterativeTime 100
#define e 2.7182828
double get_Key(double x)
{
	return (2 - pow(e, x)) / 10;
}
//迭代法求方程近似根
int main()
{
	double x0 = 0;
	int cnt = 0;
	double temp_result = x0;
	double final_result;
	ofstream fout("data.txt");

	while (cnt < maxIterativeTime) 
	{
		
		cout << temp_result<<endl;
		fout << cnt <<" "<<temp_result << endl;
		temp_result = get_Key(temp_result);
		cnt++;
		final_result = temp_result;
	}



}