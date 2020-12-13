#include <iostream>
#include <cassert>
using namespace std;
//������
#define processNum 100
//��Դ������
#define resourceNum 100

//������Դ����
int available[resourceNum];
//���������������
int MaxResource[processNum][resourceNum];
//�ѷ�����������
int allocation[processNum][resourceNum];
//�����֤
int need[processNum][resourceNum];

//��������
int request[processNum];
//��������
int work[resourceNum];
//�Ƿ�ȫ
bool finished[processNum];
//��ȫ����
int series[processNum];

//������
int processCount;
//��Դ��
int resourceCount;

//�������ݳ�ʼ������
void init() {
	cout << "�������������";
	cin >> processCount;
	cout << "\n��������Դ����";
	cin >> resourceCount;
	cout << "���������������Դ�ɷ���ֵ";
	for (int i = 0; i < resourceCount; i++) {
		cin >> available[i];
	}
	cout << "����������������\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cin >> MaxResource[i][j];
		}
	}
	cout << "������������\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cin >> allocation[i][j];
		}
	}
	cout << "�������������\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cin >> need[i][j];
		}
	}
}

//�Ƿ���������
bool IsSafe() {
	int i = 0;
	//���������Ƿ����
	for (i = 0; i < processCount; i++) {
		if (finished[i] == true)
			continue;
		else
			break;
	}
	//���������i�ͽ�������ͬ��˵���Ѿ����
	if (i == processCount)
		return true;
	else
		return false;
}

//ѡ��needС������resourceֵ��process
bool Select(int& tmp, int tmpNeeded[][resourceNum]) {
	int j = 0;
	for (int i = 0; i < processCount; ++i) {
		//����ý����Ѿ�ʵ�ֹ�
		if (finished[i])
			continue;
		//����������Դ��
		for (j = 0; j < resourceCount; j++) {
			//�������������Դ������work��ʣ����Դ��
			if (tmpNeeded[i][j] > work[j])
				break;
		}
		//���������Դ�������㣬������i���밲ȫ�����У�����true
		if (j == resourceCount) {
			tmp = i;
			return true;
		}
	}
	return false;
}

//�ж��Ƿ����
bool Safe(int* tmpAvail, int tmpAllocation[][resourceNum], int tmpNeeded[][resourceNum]) {
	
	//��process��Ϊδ����
	for (int i = 0; i < processNum; ++i) {
		finished[i] = false;
	}
	//ϵͳ������Դ����ΪtmpAvail
	for (int j = 0; j < resourceNum; j++) {
		work[j] = tmpAvail[j];
	}
	int tmp = 0;
	int index = 0;
	//ѡ��δ��ɵĽ��̷�����Դ
	while (Select(tmp, tmpNeeded)) {
		//��tmp�Ž�����Ϊ�ѷ���״̬
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

//չʾ����
void showInfo() {
	cout << "��ǰ������Դ�ɷ���ֵ";
	for (int i = 0; i < resourceCount; i++) {
		cout << available[i];
	}
	cout << "\n����������\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cout << MaxResource[i][j];
		}

	}
	cout << "\n��ǰ�������\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cout << allocation[i][j];
		}
	}
	cout << "\n�������������\n";
	for (int i = 0; i < processCount; i++) {
		for (int j = 0; j < resourceCount; j++) {
			cout << need[i][j];
		}
	}
}

int main() {
	cout << "���ʼ���㷨\n";
	init();
	Safe(available, allocation, need);
	if (IsSafe()) {
		cout << "��ǰ״̬��ȫ����ȫ���Ϊ��\n";
		for (int i = 0; i < processCount; i++) {
			cout << series[i] << "-";
		}
		cout << "end\n";
	}
	else
		cout << "��ǰ״̬����ȫ\n";
}
