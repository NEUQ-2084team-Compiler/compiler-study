#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*
�ķ���
E -> T E'
E' -> + T E'| #
T -> F T'
T' -> * F T'| #
F -> ( E ) | id
*/
string GRAMMER[100][100];//�����ķ�������
string FIRST[100][100];//����first��������
string FOLLOW[100][100];//����follow��������
const int MAX = 100;

int getFirst() {//��ȡ�����First��,��һ���Ƿ��ս����֮���Ǽ���
	int index = 1;//��ά����һά���ȵ�����
	bool judge = true;//�ҷ��ս������ӱ�׼������������ֵ����index��������ʱ��ȡ��ѭ��
	while (judge) {
		for (int f = 0; f < 5; f++) {
			FIRST[f][0] = GRAMMER[f][0];
			if (GRAMMER[f][1] == "+") {//�����һ�����ս������ôFIRST���ĵ�һ�����Ǹ��ս��
				FIRST[f][index] = GRAMMER[f][1];
			}
			if (GRAMMER[f][1] == "*") {
				FIRST[f][index] = GRAMMER[f][1];
			}
			if (GRAMMER[f][1] == "(") {
				FIRST[f][index] = GRAMMER[f][1];
			}
			if (GRAMMER[f][1] == "id") {
				FIRST[f][index] = GRAMMER[f][1];
			}
			if (GRAMMER[f][1] == ")") {
				FIRST[f][index] = GRAMMER[f][1];
			}
			if (GRAMMER[f][1] == "#") {
				FIRST[f][index] = GRAMMER[f][1];
			}
		}
		index++;
		for (int k = 0; k < 5; k++) {//��ȫ�ս��
			for (int j = 0; j < 100; j++) {
				if (GRAMMER[k][j] == "|") {
					FIRST[k][index] == GRAMMER[k][j + 1];
					index++;
				};

			}
		}

		for (int f = 0; f < 5; f++) {//�ҷ��ս��
			if (GRAMMER[f][1] == "F") {//�ҷ��ս���е��ս��
				for (int j = 1; j < 5; j++) {
					FIRST[f][index] = GRAMMER[f][j];
				}

			}
			for (int k = 0; k < 5; k++) {//׷���׷��ս��
				if (FIRST[k][0] == GRAMMER[f][index]) {
					index++;
					for (int l = 1; l < 5; l++) {
						FIRST[k][index] == GRAMMER[f][l];
					}
				}
			}
		}
	}cout << FIRST << endl;//���
}
int getFollow() {//��ȡ�����Follow������һ���Ƿ��ս����֮���Ǽ���
	for (int f = 0; f < 100; f++) {
		FOLLOW[f][0] = GRAMMER[f][0];
	}
	FOLLOW[0][1] = "$";//��ʼ���ŵ��Ҷ���$�������
	int index = 2;//��¼���鳤�ȵ�����
	for (int k = 0; k < 5; k++) {//���A->aBb����ôFIRST(b)�г�#�����з��Ŷ���FOLLOW(b);
		if (GRAMMER[k][1] == "T") { FOLLOW[k][index] == ")"; }
		if (GRAMMER[k][2] == "T") {
			FOLLOW[k][index] == ")";//(�룩�����
			if (GRAMMER[k][3] == "E'") {
				FOLLOW[k][index + 1] == "$";
				FOLLOW[k][index + 2] == ")";
			}
		}index++;
		if (FIRST[1][1] == "+") {
			FOLLOW[2][index ] == "+";
			FOLLOW[3][index ] == "+";
		}index++;
		if (FIRST[3][1] == "*") {
			FOLLOW[4][index] == "*";
		}
	}
}
int main() {
	char buffer[MAX];
	ifstream infile;
	infile.open("grammer.txt");//�����ķ��ļ�
	int line = 0;
	while (!infile.eof())
	{
		infile.getline(buffer, MAX);
		for (int f = 0; f <= MAX; f++) {//��GRAMMER���鸳ֵ�ķ�����άΪ����->���ķ��ս������ά���������ζ�Ӧ�Ҳ���ս���ͷ��ս��
			if ((const char*)buffer[f] == "->") {
				GRAMMER[line][0] = buffer[f - 1];
				GRAMMER[line][1] = buffer[f + 1];
				for (int k = 2; (bool)buffer[k + f] != false; k++) {
					GRAMMER[line][k] = buffer[f + k];
				}
			}

		}
		line++;
	}
	infile.close();
	getFirst();
	getFollow();
}