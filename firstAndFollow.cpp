#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>

using namespace std;

struct FirstAndFollow {
	set<string> productions;//产生式
	map<string, set<string>> splitproductions;//分解后的产生式
	set<string> T;//终结符
	set<string> nonT;//非终结符
	map<string, set<string>> first;//First集
	map<string, set<string>> follow;//Follow集
	void init();
	void split();//分解产生式
	void findTAndnonT();//获得终结符和非终结符
	bool isnonT(string s);
	bool isT(string s);
	set<string> getFirst(string s);//获得单个first集
	void getFirst2();//获得所有first集
	void getFollow();//获得所有follow集
	void getFollow2();//求follow集的步骤3
};

void FirstAndFollow::init() {
	string line;
	ifstream in("productions.txt");
	if (in) {
		//文法开始符号的follow集中放入$
		getline(in, line);
		productions.insert(line);
		follow[line.substr(0, 1)].insert("$");
		cout << line << endl;
		while (getline(in, line)) {
			productions.insert(line);
			cout << line << endl;
		}
	}
}
void FirstAndFollow::split() {
	int position = 0;
	//set 只能通过迭代器 it访问内部元素 下面for是遍历set
	for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
		string temp = *it;
		for (int i = 0; i < temp.length(); i++) {
			position = temp.find("->");
			//先将左右分开
			string left = temp.substr(0, position);
			string right = temp.substr(position + 2);
			set<string>temp;
			string t;
			//分割|前后
			for (int j = 0; j < right.length(); j++) {
				if (right[j] == '|') {
					temp.insert(t);
					t = "";
				}
				else
				{
					//在字符串末尾添加
					t.append(right.substr(j, 1));
				}

			}
			temp.insert(t);
			//pair主要的作用是将两个数据组合成一个数据
			splitproductions.insert(pair<string, set<string>>(left, temp));
		}
	}
	//map 自动建立key － value的对应。key 和 value可以是任意你需要的类型，包括自定义类型。
	for (map<string, set<string>>::iterator it = splitproductions.begin(); it != splitproductions.end(); it++) {
		cout << it->first << "    ";
		for (set<string>::iterator itt = it->second.begin(); itt != it->second.end(); itt++) {
			cout << *itt << "    ";
		}
		cout << endl;
	}


}
void FirstAndFollow::findTAndnonT() {
	for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
		string temp = *it;
		for (int i = 0; i < temp.length(); i++) {
			if (temp[i] == '-' || temp[i] == '>' || temp[i] == '|')
				continue;
			//是大写字母
			if (temp[i] >= 'A' && temp[i] <= 'Z') {
				//带'
				if (temp[i + 1] == '\'') {
					nonT.insert(temp.substr(i, 2));
					i++;
				}
				else {
					nonT.insert(temp.substr(i, 1));
				}
			}
			//是终结符
			else
			{
				T.insert(temp.substr(i, 1));
			}
		}
	}

	cout << "非终结符" << endl;
	for (set<string>::iterator it = nonT.begin(); it != nonT.end(); it++) {
		cout << *it << endl;
	}

	cout << "终结符" << endl;
	for (set<string>::iterator it = T.begin(); it != T.end(); it++) {
		cout << *it << endl;
	}
}
bool FirstAndFollow::isnonT(string s) {
	if (nonT.find(s) != nonT.end()) {
		return true;
	}
	return false;
}
bool FirstAndFollow::isT(string s) {
	if (T.find(s) != T.end()) {
		return true;
	}
	return false;
}
set<string> FirstAndFollow::getFirst(string s) {
	//  count()返回s出现的次数
	if (splitproductions.count(s) > 0) {
		set<string>temp = splitproductions[s];
		for (set<string>::iterator it = temp.begin(); it != temp.end(); it++) {
			string temp1 = *it;
			if (temp1 == "#") {
				first[s].insert("#");
			}
			else {
				int flagAll = 0;//所有的非终结符的first集都有#；
				//位置i判别
				for (int i = 0; i < temp1.length(); i++) {
					int flag = 0;//当前的非终结符的first集有#；
					if (temp1[i + 1] == '\'') {//带'的非终结符
						set<string>t1 = getFirst(temp1.substr(i, 2));
						for (set<string>::iterator itt = t1.begin(); itt != t1.end(); itt++) {
							if (*itt == "#") {//此时空串不可插入
								flag = 1;
							}
							else {
								first[s].insert(*itt);
							}
						}
						i++;
					}
					
					else if (isnonT(temp1.substr(i, 1)))//单个非终结符
					{
						set<string>t2 = getFirst(temp1.substr(i, 1));
						for (set<string>::iterator itt = t2.begin(); itt != t2.end(); itt++) {
							if (*itt == "#") {//此时空串不可插入
								flag = 1;
							}
							else {
								first[s].insert(*itt);
							}
						}
					}
					else {//终结符
						first[s].insert(temp1.substr(i, 1));
					}
					if (i == temp1.length() - 1 && flag == 1) {
						flagAll = 1;
					}
					if (flag == 0)
						break;

				}
				if (flagAll == 1) {
					first[s].insert("#");
				}
			}
		}
	}
	return first[s];
}
void FirstAndFollow::getFirst2() {
	for (map<string, set<string>>::iterator it = splitproductions.begin(); it != splitproductions.end(); it++) {
		getFirst(it->first);
	}
	cout << "First集" << endl;
	for (map<string, set<string>>::iterator it = first.begin(); it != first.end(); it++) {
		cout << it->first << "  :  ";
		for (set<string>::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
		{
			cout << *itt << "    ";
		}
		cout << endl;
	}

}
void FirstAndFollow::getFollow() {
	for (map<string, set<string>>::iterator it = splitproductions.begin(); it != splitproductions.end(); it++) {
		string left = it->first;
		set<string>right = it->second;
		for (set<string>::iterator itt = right.begin(); itt != right.end(); itt++) {
			string temp = *itt;

			for (int i = 0; i < temp.length(); i++) {
				if (isT(temp.substr(i, 1))) {//终结符
					continue;
				}
				else if (i + 1 < temp.length() && temp[i + 1] == '\'') {//带有’的非终结符
					if (isT(temp.substr(i + 2, 1))) {//非终结符后面是终结符
						follow[temp.substr(i, 2)].insert(temp.substr(i + 2, 1));
						i++;
					}
					else {//非终结符后面是非终结符s
						//把后面非终结符的first集FirstAndFollow加入follow集中
						string s;
						if (i + 3 < temp.length() && temp[i + 3] == '\'') {
							s = temp.substr(i + 2, 2);
						}
						else {
							s = temp.substr(i + 2, 1);
						}
						set<string> FirstAndFollow = first[s];
						for (set<string>::iterator nn = FirstAndFollow.begin(); nn != FirstAndFollow.end(); nn++) {
							if (*nn != "#")
								follow[temp.substr(i, 2)].insert(*nn);
						}
					}
				}
				else {//不带’的非终结符

					if (i + 1 < temp.length() && isT(temp.substr(i + 1, 1))) {//非终结符后面是终结符
						follow[temp.substr(i, 1)].insert(temp.substr(i + 1, 1));
						i++;
					}
					else {//非终结符后面是非终结符s
						//把后面非终结符的first集FirstAndFollow加入follow集中
						string s;
						if (i + 2 < temp.length() && temp[i + 2] == '\'') {
							s = temp.substr(i + 1, 2);
						}
						else {
							s = temp.substr(i + 1, 1);
						}
						set<string> FirstAndFollow = first[s];
						for (set<string>::iterator nn = FirstAndFollow.begin(); nn != FirstAndFollow.end(); nn++) {
							if (*nn != "#")
								follow[temp.substr(i, 1)].insert(*nn);
						}
					}
				}
			}
		}
	}
	//这一个需要多进行几次，因为follow是不断增长的
	getFollow2();
	getFollow2();
	getFollow2();
	cout << "Follow集" << endl;
	for (map<string, set<string>>::iterator it = follow.begin(); it != follow.end(); it++) {
		cout << it->first << "  :  ";
		for (set<string>::iterator itt = it->second.begin(); itt != it->second.end(); itt++)
		{
			cout << *itt << "    ";
		}
		cout << endl;
	}
}
void FirstAndFollow::getFollow2() {
	for (map<string, set<string>>::iterator it = splitproductions.begin(); it != splitproductions.end(); it++) {
		string left = it->first;
		set<string>right = it->second;
		for (set<string>::iterator ii = right.begin(); ii != right.end(); ii++) {
			string temp = *ii;
			for (int j = temp.length() - 1; j > 0; j--) {
				string now;
				if (temp[j] == '\'') {
					now = temp.substr(j - 1, 2);
					j--;
				}
				else now = temp.substr(j, 1);
				if (isT(now)) {//产生式最后是终结符
					break;
				}
				else {//产生式最后是非终结符
					set<string>aa = follow[left];
					for (set<string>::iterator pp = aa.begin(); pp != aa.end(); pp++) {
						follow[now].insert(*pp);
					}
				}
				if (first[now].find("#") == first[now].end())
					break;
			}
		}
	}
}
int main() {
	FirstAndFollow F;
	F.init();
	F.split();
	F.findTAndnonT();
	F.getFirst2();
	F.getFollow();
}
