#include <iostream>
using namespace std;

//********************************
//在输入代码结尾+一个#号作为结束
//********************************

//关键字
const char keyWord[15][10] = { "int","double","float","long","if","else","while","for","switch","case","do","main","void","class","struct" };
char token[10];
int m = 0;//输入的代码里第m个单词
int row = 1;//行数
char c;
char prog[100];//存放输入的全部代码
int scan() {
	if (m == 0) {
		c = prog[m];
		m++;
	}

	int num = 0;//记录本个单词字符数
	for (int i = 0;i < 10;i++) {
		token[i] = NULL;
	}
	//跳过空格
	while (c == ' ' || c == '\t') {
		c = prog[m];
		m++;
	}
	//记录行数
	if (c == '\n') {
		c = prog[m];
		m++;
		row++;
	}
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
			token[num] = c;
			c = prog[m];
			m++;
			num++;
		}
		token[num] = '\0';
		num++;
		for (int i = 0;i < 15;i++) {
			if (strcmp(token, keyWord[i]) == 0) 
				return i+3;//是种别码为i+3的关键字
		}

			return 2;//是标识符
	}
	else if (c >= '0' && c <= '9') {
		while ((c>= '0' && c <= '9') || c == '.') {
			token[num] = c;
			c = prog[m];
			m++;
			num++;
		}
		return 1;//是数字
	}
	else {
		token[num] = c;
		num++;
		switch (c) {
		case '+': {
			c = prog[m];
			m++;
			if (c == '+') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 37;
			}
			else
				return 18;
		}
		case '-': {
			c = prog[m];
			m++;
			if (c == '-') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 38;
			}
			else
				return 19;
		}
		case '*': {
			c = prog[m];
			m++;
			if (c == '/') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 40;
			}
			else
				return 20;
		}
		case '/': {
		
			c = prog[m];
			m++;
			if (c == '*') {
				token[num] = c;
				num++;
				
				while (1) {
					c = prog[m];
					m++;
					if (c == '\n') {
						c = prog[m];
						m++;
						row++;
					}
					if (c == '*'&&prog[m] == '/')
						return 39;
					if (c == '#')
						return -1;
				}
			}
			else if (c == '/') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 41;
			}
			else
				return 21;
		}
		case '>': {
			c = prog[m];
			m++;
			if (c == '=') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 23;
			}
			else
				return 22;
		}
		case '=': {
			c = prog[m];
			m++;
			if (c == '=') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 42;
			}
			else
				return 24;
		}
		case '<': {
			c = prog[m];
			m++;
			if (c == '=') {
				token[num] = c;
				num++;
				c = prog[m];
				m++;
				return 26;
			}
			else

				return 25;
		}
		case'(':c = prog[m];
			m++; return 27;
		case')':c = prog[m];
			m++;return 28;
		case';':c = prog[m];
			m++; return 29;
		case'"':c = prog[m];
			m++;return 30;
		case'&':c = prog[m];
			m++;return 31;
		case'[':c = prog[m];
			m++; return 32;
		case']':c = prog[m];
			m++;return 33;
		case'{': c = prog[m];
			m++; return 34;
		case'}':c = prog[m];
			m++; return 35;
		case'|':c = prog[m];
			m++; return 36;
		case'\n':c = prog[m];
			m++; return -3;
		case'#': return -2;//设定#为末尾
		default: {
			c = prog[m];
			m++; return -1;}
		}
	}



}



int main() {
	int n, m = 0;
	char ch=0;
	cout << "请输入:" << endl;
	while (ch != '#') {
		cin.get(ch);
		prog[m] = ch;
		m++;
	}
	while (1) {
		n = scan();
		switch (n)
		{
		case -1:
			cout << "第" <<row<< "行有错误" << endl;
			break;
		case -2: {
			system("pause");
			return 0;
		}
		case -3 : break;
		default:
			cout << "<" << n << "," << token << ">" << endl;
			break;
		}

	}
	return 0;
}