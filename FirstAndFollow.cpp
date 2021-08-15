#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

struct sentence
{
	char ter;	               //终结符 
	bool isEpsilon;	           //空串（用#表示）
	vector<string> nonter;     //非终结符 
};
vector<sentence> v;			   //产生式集合 

string nonTerminator = "";	               //非终结符集合 
string first[40];						   //first集合 
string follow[40];						   //follow集合 


//将文法转换成单独的产生式 
void Sentence(string str)
{
	sentence s;
	s.ter = str[0];
	s.isEpsilon = false;
	int cur = 3;
	//开始遍历传入的字符串
	for (int index = cur; index < str.length(); index++) {
		if (str[index] == '|')
		{//如果遇到或 |
			s.nonter.push_back(str.substr(cur, index - cur));
			cur = index + 1;
		}
		else if (str[index] == '#')
		{//如果遇到空串
			s.isEpsilon = true;
			cur = index + 2;
			index++;
		}
	}

	if (cur < str.length()) {
		s.nonter.push_back(str.substr(cur));
	}
	v.push_back(s);
	nonTerminator = nonTerminator + str[0];
}

//求first集
void ToFirst(int p, sentence s)
{
	for (int index = 0; index < s.nonter.size(); index++)
	{
		if (s.isEpsilon) {
			first[p] += '#';
		}
		char str = s.nonter[index][0];

		if ((str >= 'a' && str <= 'z') || (str >= '(' && str <= '+'))
		{
			first[p] += str;
		}
		else if ((str >= 'A' && str <= 'Z') && str != s.ter)
		{
			int j = nonTerminator.find(str);
			ToFirst(p, v[j]);
		}
	}
}

//求follow集 
void ToFollow(int n, char a)
{
	//$代表空串
	if (a == nonTerminator[0])
	{
		follow[n] += "$";
	}

	for (int index = 0; index < nonTerminator.length(); index++)
	{
		for (int cur = 0; cur < v[index].nonter.size(); cur++)
		{
			if (v[index].nonter[cur].find(a) != string::npos)
			{
				int loc = v[index].nonter[cur].find(a);

				if ((loc == v[index].nonter[cur].length() - 1) && a != v[index].ter)
				{

					if (index == 0) follow[n] += "$";
					ToFollow(n, nonTerminator[index]);
				}
				else if (loc < v[index].nonter[cur].length() - 1)
				{
					char loc1 = v[index].nonter[cur][loc + 1];

					if ((loc1 >= 'a' && loc1 <= 'z') || (loc1 >= '(' && loc1 <= '+'))
					{
						follow[n] += loc1;
					}
					else
					{
						int m = 0;
						for (; m < nonTerminator.length(); m++)
						{
							if (nonTerminator[m] == loc1)
							{
								follow[n] += first[m];
								break;
							}
						}
					}
				}
			}
		}
	}
}


//添加新的产生式 
void AddNewSentence()
{
	for (int index = 0; index < v.size(); index++)
	{
		if (v[index].isEpsilon)
		{
			for (int cur = 0; cur < v.size(); cur++)
			{
				for (int i = 0; i < v[cur].nonter.size(); i++)
				{
					int n = v[cur].nonter[i].find(v[index].ter);
					string str = v[cur].nonter[i];
					if (n >= 0)
					{
						v[cur].nonter.push_back(str.substr(0, n) + str.substr(n + 1));
					}

				}
			}
		}
	}
}

void Print()
{//输出文法 
	for (int i = 0; i < v.size(); i++)
	{
		sentence s = v[i];

		for (int j = 0; j < s.nonter.size(); j++)
			cout << s.ter << "->" << s.nonter[j] << endl;
		if (s.isEpsilon)
			cout << s.ter << "->" << "#" << endl;
		ToFirst(i, s);
		ToFollow(i, s.ter);
	}
}

int main()
{
	ifstream open("FirstAndFollow.txt");

	if (!open.is_open())
	{
		cout << "文件打开失败！" << endl;
	}

	string str;

	while (getline(open, str))
	{
		Sentence(str);
	}
	open.close();

	AddNewSentence();

	Print();
	cout << endl << endl;
	for (int len = 0; len < nonTerminator.length(); len++)
	{
		str = "";
		//去重
		for (int i = 0; i < first[len].length(); i++)
		{
			char c = first[len][i];
			if (str.find(c) == string::npos)
			{
				str += c;
			}

		}
		first[len] = str;
		cout << "First(" << nonTerminator[len] << ") =" << " { " << first[len] << " } " << endl;
	}

	cout <<endl<< endl;
	for (int len = 0; len < nonTerminator.length(); len++)
	{
		str = "";
		//去重    把#符去掉 
		for (int i = 0; i < follow[len].length(); i++)
		{
			char c = follow[len][i];
			if ((str.find(c) == string::npos) && c != '#')
			{
				str += c;
			}
		}
		follow[len] = str;
		cout <<"Follow("<< nonTerminator[len] << ") = " <<" { "<< follow[len]<<" } " << endl;
	}
	system("pause");
	return 0;
}