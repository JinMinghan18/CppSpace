#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
//ÿ��������Ҫ����Դ��
#define resourceNum 3
//��������
#define processNum 4
//��ǰ�ɻ�ȡ��Դ��
int availableResource[resourceNum] = { 0,1,1 };
//ϵͳӵ������Դ��
int allResource[resourceNum] = { 9,3,6 };
//����������������Դ��
vector<vector<int>> allResourceNeeded = { {3,2,2},{6,1,3},{3,1,4},{4,2,2} };
//int (*allResourceNeeded)[3] = new int[processNum][resourceNum];// { {3,2,2},{6,1,3},{3,1,4},{4,2,2} };
//�������̵�ǰ�ѷ�����Դ��
vector<vector<int>> resourceAllocation = { {1,0,0},{6,1,2},{2,1,1},{0,0,2} };
//int resourceAllocation[processNum][resourceNum] = { {1,0,0},{6,1,2},{2,1,1},{0,0,2} };
//�Ƿ�ȫ
bool Finish[processNum];
//��ȫ����
int safeseries[processNum] = { 0,0,0,0 };
//��Դ������
int num;
//��������Ϣ
void printInfo() {
	

	cout << "��ǰ�ɻ�ȡ��Դ��" << endl;
	for (int i = 0; i < resourceNum; i++) {
		cout << availableResource[i] << " ";
	}
	cout << endl << "--------------------"<<endl;

	cout << "PID\t������������Դ\t�����ѷ�����Դ\t���̻�����Դ\n";

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
