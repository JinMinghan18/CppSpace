#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
//每个进程需要的资源数
#define resourceNum 3
//进程数量
#define processNum 4
//当前可获取资源数
int availableResource[resourceNum] = { 0,1,1 };
//系统拥有总资源数
int allResource[resourceNum] = { 9,3,6 };
//各个进程所需总资源数
vector<vector<int>> allResourceNeeded = { {3,2,2},{6,1,3},{3,1,4},{4,2,2} };
//int (*allResourceNeeded)[3] = new int[processNum][resourceNum];// { {3,2,2},{6,1,3},{3,1,4},{4,2,2} };
//各个进程当前已分配资源数
vector<vector<int>> resourceAllocation = { {1,0,0},{6,1,2},{2,1,1},{0,0,2} };
//int resourceAllocation[processNum][resourceNum] = { {1,0,0},{6,1,2},{2,1,1},{0,0,2} };
//是否安全
bool Finish[processNum];
//安全次序
int safeseries[processNum] = { 0,0,0,0 };
//资源数计算
int num;
//输出相关信息
void printInfo() {
	

	cout << "当前可获取资源数" << endl;
	for (int i = 0; i < resourceNum; i++) {
		cout << availableResource[i] << " ";
	}
	cout << endl << "--------------------"<<endl;

	cout << "PID\t进程所需总资源\t进程已分配资源\t进程还需资源\n";

	//cout <<	 allResourceNeeded[1][1] << endl;
	//cout << resourceAllocation[1][1] << endl;
	for (int i = 0; i < 4; i++) {
		cout << "P" << i << "\t";

		for (int j = 0; j < 3; i++) {

			//cout << allResourceNeeded[i][j] << "\t";
			printf("%2d\t", allResourceNeeded[i][j]);
			//cout << resourceAllocation[i][j] << "\t";
			cout << allResourceNeeded[i][j] - resourceAllocation[i][j];
		}
		cout << endl;
	}

}
//int main() {
//	//allResourceNeeded = { {3,2,2},{6,1,3},{3,1,4},{4,2,2} };
//	printInfo();
//	return 0;
//}
