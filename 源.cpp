#include<iostream>
#include<string>
#include <stdio.h>
using namespace std;
string keyword[15] = { "if","else","void","return","while","then","for","do",      //关键字
					"int","char","double","float","case","cin","cout" };
string separater[8] = { ";",",","{","}","[","]","(",")" };    //分隔符
string operators[8] = { "+","-","*","/",">","<","=","!" };     //运算符
const int identifier = 100;         //标识符值
const int constant = 101;           //常数值
const int filter_value = 102;       //过滤字符值
/**token的属性值
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
标识符值 100
常数值101
过滤值字符102
**/

/**判断是否为字母**/
bool IsLetter(char ch) {
    if ((ch >= 'a' && ch <= 'z')|| (ch >= 'A' && ch <= 'Z')) return true;
    return false;
}

void judge(FILE* in) {
    char ch = ' ';
    string arr = "";
    while ((ch = fgetc(in)) != EOF) {//指针一个一个读取
        arr = "";//arr用完清零
        if (ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n') {
            cout << 102 << "   " << ch << "     过滤字符值";
        }              //过滤
        else if (ch == 0 ||ch== 1 ||ch== 2 ||ch== 3 ||ch== 4 ||ch== 5 ||ch== 6 ||ch== 7 ||ch== 8 ||ch== 9 ||ch== 0) {
            cout << 101 << "   " << ch << "     常数值";
        }
        else if (IsLetter(ch)) {       //判断是否为字母
            while (IsLetter(ch)) {
                arr += ch;
                ch = fgetc(in);
            }
            int b = 1;//判断是否为标识符，0为不是，1为是
            for (int i = 0; i < 15; i++) {
                if (keyword[i] == arr) {
                    cout << i + 1 << arr << "  关键字" << endl;
                    b = 0;
                    break;
                }
            }
            for (int i = 0; i < 8; i++) {
                if (separater[i] == arr) {
                    cout << i + 16 << "     " << arr << "  分隔符" << endl;
                    b = 0;
                    break;
                }
            }
            for (int i = 0; i < 8; i++) {
                if (operators[i] == arr) {
                    cout << i + 24 << "     " << arr << "  运算符" << endl;
                    b = 0;
                    break;
                }
            }
            if (b == 1) {
                cout << 100 << "    " << arr << "   标识符" << endl;
            }

        }


    }

}
int main() {
    char inFile[100];
    FILE* in;
    cout << "请输入源文件名（包括路径和后缀）:";
    while (true) {
        cin >> inFile;
        if ((fopen(inFile, "r")) != NULL) {
            in = fopen(inFile, "r");
            break;
        }
        else {
            cout << "文件名错误！" << endl;
            cout << "请输入源文件名（包括路径和后缀）:";
        }

    }
	judge(in);
    return 0;
}