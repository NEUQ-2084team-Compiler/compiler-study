#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
#define MAX 20
using namespace std;

char noninternimal[MAX];  //非终结符
char grammer[MAX][MAX];   //文法
char sentence[MAX][MAX];  //含有间接左递归的产生式
char str[MAX][MAX], str1[MAX][MAX];
int ifUseful[MAX];        //标记无用的产生式
int row , count1 = 0, count2 = 0;

//判断文法是否含有直接左递归
int direct(char grammer[MAX][MAX])
{
	int flag = 0;
	for (int i = 0; i < row; i++)
	{
		if (grammer[i][3] == grammer[i][0])
		{//说明文法中含有直接左递归
			flag++;
			break;
		}

		if (flag > 0)
		{
			cout << "该文法含有直接左递归！" << endl;
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int indirect(char grammer[MAX][MAX])
{
	int flag = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < row; j++)
		{
			if (grammer[i + j][0] == grammer[i][3])
			{
				flag++;
				break;
			}
		}

		if (flag > 0)
		{
			break;
		}
	}

	if (flag > 0)
	{
		cout << "文法中含有间接左递归" << endl;
		return 2;
	}
	else
	{
		return 0;
	}

}

void removeDirect(char grammer[MAX][MAX])
{
	int k,j = 4;
	memset(ifUseful, 0, sizeof(ifUseful));
	for (int i = 0; i < row; i++)
	{
		if (grammer[i][3] == grammer[i][0])
		{
			grammer[i][3] == grammer[i][2];
			grammer[i][2] == grammer[i][1];
			grammer[i][1] = '\'';
			while (grammer[i][j] != 0)
			{
				j++;
			}
			grammer[i][j] = grammer[i][0];
			grammer[i][j + 1] = '\'';
			ifUseful[i] = 1;
			for (k = 0; k < 4; k++)
			{
				grammer[row][k] = grammer[i][k];
			}
			grammer[row][k] = '#';
			ifUseful[row] = 1;
		}
		else
		{
			j = 3;
			while (grammer[i][j] != 0)
			{
				j++;
			}
			grammer[i][j] = grammer[i][0];
			grammer[i][j + 1] = '\'';
			ifUseful[i] = 1;
		}
	}

	cout << "消除直接左递归之后的文法：" << endl;
	for (int t = 0; t < row + 1; t++)
	{
		if (ifUseful[t] == 1)
		{
			cout<<grammer[t]<<endl;
		}
	}
}


void removeIndirect(char grammer[MAX][MAX])
{
	int flag, flag2 = 0, row2 = row;
	int i, j, k, t, e = 0, g = 0;
	noninternimal[e] = grammer[e][0];
	for (i = 1; i < row; i++)
	{
		int flag = 0;
		for (int k = 0; k <= e; k++)
		{
			if (grammer[i][0] != noninternimal[k])
			{
				flag++;
			}
		}

		if (flag == (e + 1))
		{
			e++;
			noninternimal[e] = grammer[i][0];
		}
	}
	cout << "好" << endl;

	for (j = 0; j < e; j++)
	{
		int num = 0;
		for (int i = 0; i < row; i++)
		{
			if (grammer[i][0] == noninternimal[j])
			{
				num++;
			}
		}

		if (num > 1)
		{
			row2++;
		}

		for (i = 0; i < row; i++)
		{
			for (k = 1; k < row; k++)
			{
				if ((grammer[i][0] == grammer[i + k][3]) && (flag2 == 0))
				{
					for (int y = 0; grammer[i + k][y] != 0; y++)
					{
						sentence[g][y] = grammer[i + k][y];
					}
					flag2 = 1;
					int m = 3;
					while (grammer[i][m] != 0)
					{
						m++;
					}
					int t = m - 3;
					int n = 4;
					while (grammer[i + k][n] != 0)
					{
						n++;
					}

					for (int s = n - 1; s >= 4; s--)
					{
						grammer[i + k][s + t - 1] = grammer[i + k][s];
					}
					for (int u = 3; u < 3 + t; u++)
					{
						grammer[i + k][u] = grammer[i][u];
					}
					break;
				
				}
				else if ((grammer[i][0] == sentence[g][3]) && (flag2 == 1))
				{
					for (int y = 0; sentence[g][y] != 0; y++)
					{
						grammer[row2 - 1][y] = sentence[g][y];
					}
					int m = 3;
					while (grammer[i][m] != 0)
					{
						m++;
					}

					int t = m - 3;
					int n = 4;
					while (grammer[row2 - 1][n] != 0)
					{
						n++;
					}
					for (int s = n - 1; s >= 4; s--)
					{
						grammer[row2 - 1][s + t - 1] = grammer[row2 - 1][s];
					}
					for (int u = 3; u < 3 + t; u++)
					{
						grammer[row2 - 1][u] = grammer[i][u];
					}
					break;
				}
			}
		}
		flag2 = 0;
		g++;
	}

	memset(ifUseful, 0, sizeof(ifUseful));
	for (i = 0; i < row2; i++)
	{
		if (grammer[i][0] == noninternimal[e])
		{
			if (grammer[i][3] == grammer[i][0])
			{
				grammer[i][3] = grammer[i][2];
				grammer[i][2] = grammer[i][1];
				grammer[i][1] = '\'';
				while (grammer[i][j] != 0)
				{
					j++;
				}
				grammer[i][j] = grammer[i][0];
				grammer[i][j + 1] = '\'';
				ifUseful[i] = 1;
				for (k = 0; k < 4; k++)
				{
					grammer[row2][k] = grammer[i][k];
				}
				grammer[row2][k] = '#';
				ifUseful[row2] = 1;
			}
			else
			{
				j = 3;
				while (grammer[i][j] != 0)
				{
					j++;
				}
				grammer[i][j] = grammer[i][0];
				grammer[i][j + 1] = '\'';
				ifUseful[i] = 1;
			}
		}
		
	}
	cout<<"消除间接左递归的文法："<<endl;
	for (t = 0; t <= row2; t++)
	{
		if (ifUseful[t] == 1)
		{
			cout << grammer[t] << endl;
		}
	}
}

void permutationALL(char str[MAX][MAX],int i,int n)
{
	int k = 0, j = 0;
	char temp[MAX];
	if (i == n)
	{
		memset(grammer, 0, sizeof(grammer));
		while (k < count1)
		{
			strcpy_s(grammer[k], str[k]);
			k++;
		}
		while (k < row)
		{
			strcpy_s(grammer[k], str1[k - count1]);
			k++;
		}
		removeIndirect(grammer);
	}
	else
	{
		for (j = i; j <= n; j++)
		{
			strcpy_s(temp, str[j]);
			strcpy_s(str[j],str[i]);
			strcpy_s(str[i],temp);
			strcpy_s(temp, str[j]);
			permutationALL(str, i + 1, n);
			strcpy_s(temp, str[j]);
			strcpy_s(str[j], str[i]);
			strcpy_s(str[i], temp);
		}
	}
}

int main()
{
	cout << "请输入文法产生式的个数：" << endl;
	cin >> row;
	cout << "请输入产生式，左部和右部用->连接" << endl;
	for (int k = 0; k < row; k++)
	{
		cin >> grammer[k];
		if (strlen(grammer[k]) == 4)
		{
			strcpy_s(str1[count2++], grammer[k]);
		}
		else
		{
			strcpy_s(str[count1++], grammer[k]);
		}
	}

	if (direct(grammer) == 1)
	{
		removeDirect(grammer);
	}
	else if (indirect(grammer) == 2)
	{
		permutationALL(str, 0, count1 - 1);
	}
	else
	{
		cout << "文法不含有左递归" << endl;
	}

	
	system("pause");
	return 0;
}