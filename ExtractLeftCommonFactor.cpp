#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<map>
using namespace std;
map<string, int> VN_dic;
vector<WF> VN_set;


class WF {
public:
	string left;
	set<string> right;
	WF(const string& temp) {
		left = temp;
		right.clear();
	}
	void print() {
		cout << left.c_str() << "=";
		set<string>::iterator it = right.begin();
		cout << it->c_str(); it++;//迭代器
		while (it != right.end()) {
			cout << it->c_str();
			it++;
		}
	}
	void insert(const string& temp)
	{
		right.insert(temp);
	}
};

void extractLeftCommonFactors() {
	for (int i = 0; i < VN_set.size(); i++)
	{
		int z = 0;
		char ch = VN_set[i].left[z];
		set<string>& temp = VN_set[i].right;
		int x=VN_dic[temp];
		bool flag = false;
		while (!flag) {
			if (ch == VN_set[x]) {
				ch = VN_set[i].left[z + 1];
				x += 1;
			}
			if (ch != VN_set[x]) {
				string Aa = ch + " / " + VN_set[x];
				ch = "Aa";
				VN_set[x] = "Aa";
			}
		}
	}

}

void print() {
	puts("**********消除左递归后的结果********");
	for (int i = 0; i < VN_set.size(); i++)
		VN_set[i].print();
	puts("");

}
int main() {
	char buf[500];
	int S;
	cout << "请输入文法的产生量";
	cin >> S;
	while (S--)
	{
		scanf("%s", buf);
		int len = strlen(buf), i;
		for (i = 0; i < len; i++)
			if (buf[i] == ':')
			{
				buf[i] = 0;
				break;
			}
		string temp = buf;
		if (!VN_dic[temp])
		{
			VN_set.push_back(WF(temp));
			VN_dic[temp] = VN_set.size();
		}
		int x = VN_dic[temp] - 1;
		temp = buf + i + 3;
		VN_set[x].insert(temp);
	}
	extractLeftCommonFactors(); 
	print();
}