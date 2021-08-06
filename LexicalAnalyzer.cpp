#include<iostream>
#include<string>
#include<fstream>
using namespace std;

string code="";
char  token[1000];
char ch;
int id, index, row, number = 0;
string keyWords[29] = { "main","if","else","then","while","do","public","private","protect","switch","for","class","struct","typedef","NULL","include","using","namespace","case","break" ,"endl","return","int","double","float","bool","void","char","string"};

//�����ַ��ĺ���
void LexicalAnalyzer()
{
    //token�ÿ�
	for (int i = 0; i < 10; i++)
	{
		token[i] = NULL;
	}
	ch = code[index++];

    //�Թ��ո�
	while (ch == ' ')
	{
		ch = code[index++];
	}

    //�����ж��ǲ�����ĸ
    int m = 0;
	if ((ch >= 'a' && ch <= 'z')|| (ch >= 'A' && ch <= 'Z'))
	{
        //������
        m = 0;
        while ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')||ch=='_')
        {
            token[m++] = ch;
            ch = code[index++];
        }

        token[m++] = '\0';//��β

        index--;//������һλ

        id = 0;
        string str = token;

        for (int n = 0; n < 29; n++) 
        { //��ʶ��������ַ����Ѷ���ı�ʾ�����Ƚ�
          //����ʶ��˳�򣬱������Ϊ1��29
            if (str.compare(keyWords[n])==0)
            {
                id = n + 1;
                break;
            }
        }
    }
    else if ((ch >= '0' && ch <= '9'))  //�����ֱ�����30
    {
        number = 0;
        while ((ch >= '0' && ch <= '9'))
        {//ƴ������
            number = number * 10 + ch - '0';
            ch = code[index++];
        }
        
        index--;
        id = 30;
            
    }
    else switch (ch)   //�����ַ� 
    {
    case'<':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == '<') //λ�����
        {
            id = 31;
            token[m++] = ch;
        }
        else if (ch == '=')//С�ڵ���
        {
            id = 32;
            token[m++] = ch;
        }
        else//С��
        {
            id = 33;
            index--;
        }
        break;
    }
    case'>':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == '=') //���ڵ���
        {
            id = 34;
            token[m++] = ch;
        }
        else if (ch == '>')//λ�����
        {
            id = 35;
            token[m++] = ch;
        }
        else
        {
            id = 36;
            index--;
        }
        break;
    }
    case'+': 
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == '=')
        {
            id = 37;
            token[m++] = ch;
        }
        else if (ch == '+')
        {
            id = 38;
            token[m++] = ch;
        }
        else
        {
            id = 39;
            index--;
        }
        break;
    }
    case'-':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == '=') 
        {
            id = 40;
            token[m++] = ch;
        }
        else if (ch == '-')
        {
            id = 41;
            token[m++] = ch;
        }
        else
        {
            id = 42;
            index--;
        }
        break;
    }
    case'\\':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == 't') // \t
        {
            id = 43;
            token[m++] = ch;
        }
        else if (ch == 'n')//  \n
        {
            id = -2;
            token[m++] = ch;
        }
        else if (ch == '0')//  \0
        {
            id = -4;
            token[m++] = ch;
        }
        break;
    }
    case'!':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == '=') //������
        {
            id = 44;
            token[m++] = ch;
        }
     
        break;
    }
    case'=':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == '=') //����
        {
            id = 45;
            token[m++] = ch;
        }
        else
        {
            id = 46;
            index--;
        }
        break;
    }
    
    
    case':':
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == ':')
        {
            token[m++] = ch;
            id = 47;//������־
           
        }
        else
        {
            id = 48;
            index--;
        }
        break;
    }
    case'(':id = 49; token[0] = ch; break;
    case')':id = 50; token[0] = ch; break;
    case'{':id = 51; token[0] = ch; break;
    case'}':id = 52; token[0] = ch; break;
    case',':id = 53; token[0] = ch; break;
    case'#':
    {
        m = 0;
        token[m++] = ch; 
        ch = code[index++];
        if (ch == '#')
        {
            token[m++] = ch;
            ch = code[index++];

            if (ch == '#')
            {
                id = -24;//������־
                token[m++] = ch;
            }
        }
        else
        {
            id = 54;
            index--;
        }
        break;
    }
    
    
    case'/':id = 55; token[0] = ch; break;
    case'\t':id = 56; token[0] = ch; break;
    case'.':id = 57; token[0] = ch; break;
    case'_':id = 58; token[0] = ch; break;
    case'"':id = 59; token[0] = ch; break;
    case 39:id = 60; token[0] = ch; break;
    case'[':id = 61; token[0] = ch; break;
    case']':id = 62; token[0] = ch; break;
    case';':id = 63; token[0] = ch; break;
    case'*':id = 64; token[0] = ch; break;
    case'&':id = 65; token[0] = ch; break;
    case'%'://d,o,x,u,c,s,f,e,g
    {
        m = 0;
        token[m++] = ch;
        ch = code[index++];
        if (ch == 'd') 
        {
            id = 66;
            token[m++] = ch;
        }
        else if (ch == 'o')
        {
            id = 67;
            token[m++] = ch;
        }
        else if (ch == 'x')
        {
            id = 68;
            token[m++] = ch;
        }
        else if (ch == 'u')
        {
            id = 69;
            token[m++] = ch;
        }
        else if (ch == 'c')
        {
            id = 70;
            token[m++] = ch;
        }
        else if (ch == 's')
        {
            id = 71;
            token[m++] = ch;
        }
        else if (ch == 'f')
        {
            id = 72;
            token[m++] = ch;
        }
        else if (ch == 'e')
        {
            id = 73;
            token[m++] = ch;
        }
        else if (ch == 'g')
        {
            id = 74;
            token[m++] = ch;
        }
        else
        {
            id = 75;
            index--;
        }
        break;
    }
    case'\n':id = -2; break;//�жϻس�
    case' ':id = -3; break; //�жϿո�
    default: id = -1; break;
    }

}

int main()
{
    //��code.txt�ж�ȡԴ����
    ifstream read;
    read.open("code.txt", ios::in);
    char* temp[200];
    string line;
   
    if (read.is_open())
    {
        cout << "�Ѷ�ȡcode.txt�ļ���" << endl<< endl;
        while (getline(read, line))
        {//һ��һ�ж�ȡ�������code�ַ�����
            code += line;
        }
        code += "###";//��ӡ�###�����������־
    }
    else
    {
        cout << "�ļ���ȡ����" << endl;
    }
    

    read.close();

    index = 0; 
    row = 1;
   
   //����ȡ��������־ʱ��������
   while(id!=-24)
   {
       LexicalAnalyzer();
        switch (id)
        {
        case 30: cout << "<  " << id << "\t, " << number << "  >" << endl;   break;
        case -1: cout << "�� " << row << "�з�������" << endl;   break;
        case -2: row = row++; break;
        case 56: break; // \t����ʾtoken
        case -3: break; // \t����ʾtoken
        case -24: break; // ������־����ʾtoken
        default: cout << "<  " << id << "\t, " << token << "  >" << endl;   break;
        }
    }
    cout << endl << "������ɣ�" << endl<<endl;
    system("pause");
	return 0;

    //���ʷ��Ŷ�Ӧ�ֱ������
    //https://kibo24-1305312055.cos.ap-beijing.myqcloud.com/C10WARED58CMM@FCI3%7BEACO.png