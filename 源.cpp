#include<iostream>
#include<string>
#include <stdio.h>
using namespace std;
string keyword[15] = { "if","else","void","return","while","then","for","do",      //�ؼ���
					"int","char","double","float","case","cin","cout" };
string separater[8] = { ";",",","{","}","[","]","(",")" };    //�ָ���
string operators[8] = { "+","-","*","/",">","<","=","!" };     //�����
const int identifier = 100;         //��ʶ��ֵ
const int constant = 101;           //����ֵ
const int filter_value = 102;       //�����ַ�ֵ
/**token������ֵ
if 1
else 2
void 3
return 4
while 5
then 6
for 7
do 8
int 9
char 10
double 11
float 12
case 13
cin 14
cout 15
; 16
, 17
{ 18
} 19
[ 20
] 21
( 22
) 23
+ 24
- 25
* 26
/ 27
> 28
< 29
= 30
! 31
��ʶ��ֵ 100
����ֵ101
����ֵ�ַ�102
**/

/**�ж��Ƿ�Ϊ��ĸ**/
bool IsLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z')|| (ch >= 'A' && ch <= 'Z')) return true;
    return false;
}

void judge(FILE* in) {
    char ch = ' ';
    string arr = "";
    while ((ch = fgetc(in)) != EOF) {//ָ��һ��һ����ȡ
        arr = "";//arr��������
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            cout << 102 << "   " << ch << "     �����ַ�ֵ";
        }              //����
        else if (ch == 0 ||ch== 1 ||ch== 2 ||ch== 3 ||ch== 4 ||ch== 5 ||ch== 6 ||ch== 7 ||ch== 8 ||ch== 9 ||ch== 0) {
            cout << 101 << "   " << ch << "     ����ֵ";
        }
        else if (IsLetter(ch)) {       //�ж��Ƿ�Ϊ��ĸ
            while (IsLetter(ch)) {
                arr += ch;
                ch = fgetc(in);
            }
            int b = 1;//�ж��Ƿ�Ϊ��ʶ����0Ϊ���ǣ�1Ϊ��
            for (int i = 0; i < 15; i++) {
                if (keyword[i] == arr) {
                    cout << i + 1 << arr << "  �ؼ���" << endl;
                    b = 0;
                    break;
                }
            }
            for (int i = 0; i < 8; i++) {
                if (separater[i] == arr) {
                    cout << i + 16 << "     " << arr << "  �ָ���" << endl;
                    b = 0;
                    break;
                }
            }
            for (int i = 0; i < 8; i++) {
                if (operators[i] == arr) {
                    cout << i + 24 << "     " << arr << "  �����" << endl;
                    b = 0;
                    break;
                }
            }
            if (b == 1) {
                cout << 100 << "    " << arr << "   ��ʶ��" << endl;
            }

        }


    }

}
int main() {
    char inFile[100];
    FILE* in;
    cout << "������Դ�ļ���������·���ͺ�׺��:";
    while (true) {
        cin >> inFile;
        if ((fopen(inFile, "r")) != NULL) {
            in = fopen(inFile, "r");
            break;
        }
        else {
            cout << "�ļ�������" << endl;
            cout << "������Դ�ļ���������·���ͺ�׺��:";
        }

    }
	judge(in);
    return 0;
}