#include<iostream>
#include<string>
#include<fstream>
using namespace std;

/*
文法：
E -> T E'
E' -> + T E'| #
T -> F T'
T' -> * F T'| #
F -> ( E ) | id
*/
string GRAMMER[100][100];//容纳文法的数组
string FIRST[100][100];//容纳first集的数组
string FOLLOW[100][100];//容纳follow集的数组
const int MAX = 100;

int getFirst() {//获取并输出First集,第一列是非终结符，之后是集合
	int index = 1;//二维数组一维长度的索引
	bool judge = true;//找非终结符，添加标准，当不在增加值，即index不在增加时，取消循环
	while (judge) {
		for (int f = 0; f < 5; f++) {
			FIRST[f][0] = GRAMMER[f][0];
			if (GRAMMER[f][1] == "+") {//如果第一个是终结符，那么FIRST集的第一个就是该终结符
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
		for (int k = 0; k < 5; k++) {//找全终结符
			for (int j = 0; j < 100; j++) {
				if (GRAMMER[k][j] == "|") {
					FIRST[k][index] == GRAMMER[k][j + 1];
					index++;
				};

			}
		}

		for (int f = 0; f < 5; f++) {//找非终结符
			if (GRAMMER[f][1] == "F") {//找非终结符中的终结符
				for (int j = 1; j < 5; j++) {
					FIRST[f][index] = GRAMMER[f][j];
				}

			}
			for (int k = 0; k < 5; k++) {//追溯首非终结符
				if (FIRST[k][0] == GRAMMER[f][index]) {
					index++;
					for (int l = 1; l < 5; l++) {
						FIRST[k][index] == GRAMMER[f][l];
					}
				}
			}
		}
	}cout << FIRST << endl;//输出
}
int getFollow() {//获取并输出Follow集，第一列是非终结符，之后是集合
	for (int f = 0; f < 100; f++) {
		FOLLOW[f][0] = GRAMMER[f][0];
	}
	FOLLOW[0][1] = "$";//开始符号的右端有$结束标记
	int index = 2;//记录数组长度的索引
	for (int k = 0; k < 5; k++) {//如果A->aBb，那么FIRST(b)中除#外所有符号都在FOLLOW(b);
		if (GRAMMER[k][1] == "T") { FOLLOW[k][index] == ")"; }
		if (GRAMMER[k][2] == "T") {
			FOLLOW[k][index] == ")";//(与）的情况
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
	infile.open("grammer.txt");//读入文法文件
	int line = 0;
	while (!infile.eof())
	{
		infile.getline(buffer, MAX);
		for (int f = 0; f <= MAX; f++) {//给GRAMMER数组赋值文法，二维为零是->左侧的非终结符，二维大于零依次对应右侧的终结符和非终结符
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