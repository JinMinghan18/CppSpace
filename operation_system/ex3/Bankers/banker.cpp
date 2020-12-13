#include <iostream>
#include <cassert>
using namespace std;
//进程数
#define processNum 100
//资源种类数
#define resourceNum 100

//可用资源向量
int available[resourceNum];
//最大需求向量矩阵
int MaxResource[processNum][resourceNum];
//已分配向量矩阵
int allocation[processNum][resourceNum];
//需求举证
int need[processNum][resourceNum];

//请求向量
int request[processNum];
//工作向量
int work[resourceNum];
//是否安全
bool finished[processNum];
//安全序列
int series[processNum];

//进程数
int processCount;
//资源数
int resourceCount;

//各种数据初始化输入
void init() {
	cout << "请输入进程数：";
	cin >> processCount;
	cout << "\n请输入资源数：";
	cin >> resourceCount;
	cout << "请依次输入各类资源可分配值";
	for (int i = 0; i < resourceCount; i++) {
		cin >> available[i];
	}
	cout << "请输入最大需求矩阵\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cin >> MaxResource[i][j];
		}
	}
	cout << "请输入分配矩阵\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cin >> allocation[i][j];
		}
	}
	cout << "请输入需求矩阵\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cin >> need[i][j];
		}
	}
}

//是否进程已完成
bool IsSafe() {
	int i = 0;
	//遍历进程是否完成
	for (i = 0; i < processCount; i++) {
		if (finished[i] == true)
			continue;
		else
			break;
	}
	//如果遍历的i和进程数相同，说明已经完成
	if (i == processCount)
		return true;
	else
		return false;
}

//选择need小于现有resource值的process
bool Select(int& tmp, int tmpNeeded[][resourceNum]) {
	int j = 0;
	for (int i = 0; i < processCount; ++i) {
		//如果该进程已经实现过
		if (finished[i])
			continue;
		//遍历各个资源数
		for (j = 0; j < resourceCount; j++) {
			//如果进程申请资源数超过work中剩余资源数
			if (tmpNeeded[i][j] > work[j])
				break;
		}
		//如果各个资源都可满足，将进程i加入安全队列中，返回true
		if (j == resourceCount) {
			tmp = i;
			return true;
		}
	}
	return false;
}

//判断是否存在
bool Safe(int* tmpAvail, int tmpAllocation[][resourceNum], int tmpNeeded[][resourceNum]) {
	
	//将process置为未结束
	for (int i = 0; i < processNum; ++i) {
		finished[i] = false;
	}
	//系统现有资源更新为tmpAvail
	for (int j = 0; j < resourceNum; j++) {
		work[j] = tmpAvail[j];
	}
	int tmp = 0;
	int index = 0;
	//选择未完成的进程分配资源
	while (Select(tmp, tmpNeeded)) {
		//将tmp号进程设为已分配状态
		finished[tmp] = true;
		for (int k = 0; k < resourceCount; k++) {
			work[k] += tmpAllocation[tmp][k];
		}
		series[index++] = tmp;
	}
	if (IsSafe()) {
		return true;
	}
	else
		return false;
}

//展示内容
void showInfo() {
	cout << "当前各类资源可分配值";
	for (int i = 0; i < resourceCount; i++) {
		cout << available[i];
	}
	cout << "\n最大需求矩阵\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cout << MaxResource[i][j];
		}

	}
	cout << "\n当前分配矩阵\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cout << allocation[i][j];
		}
	}
	cout << "\n请输入需求矩阵\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cout << need[i][j];
		}
	}
}

int main() {
	cout << "请初始化算法\n";
	init();
	Safe(available, allocation, need);
	if (IsSafe()) {
		cout << "当前状态安全，安全序号为：\n";
		for (int i = 0; i < processCount; i++) {
			cout << series[i] << "-";
		}
		cout << "end\n";
	}
	else
		cout << "当前状态不安全\n";
}
