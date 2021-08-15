#include <iostream>
#include <string>
#include <set>
#include <map>
#include <fstream>

using namespace std;

struct FirstAndFollow {
	set<string> productions;//����ʽ
	map<string, set<string>> splitproductions;//�ֽ��Ĳ���ʽ
	set<string> T;//�ս��
	set<string> nonT;//���ս��
	map<string, set<string>> first;//First��
	map<string, set<string>> follow;//Follow��
	void init();
	void split();//�ֽ����ʽ
	void findTAndnonT();//����ս���ͷ��ս��
	bool isnonT(string s);
	bool isT(string s);
	set<string> getFirst(string s);//��õ���first��
	void getFirst2();//�������first��
	void getFollow();//�������follow��
	void getFollow2();//��follow���Ĳ���3
};

void FirstAndFollow::init() {
	string line;
	ifstream in("productions.txt");
	if (in) {
		//�ķ���ʼ���ŵ�follow���з���$
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
	//set ֻ��ͨ�������� it�����ڲ�Ԫ�� ����for�Ǳ���set
	for (set<string>::iterator it = productions.begin(); it != productions.end(); it++) {
		string temp = *it;
		for (int i = 0; i < temp.length(); i++) {
			position = temp.find("->");
			//�Ƚ����ҷֿ�
			string left = temp.substr(0, position);
			string right = temp.substr(position + 2);
			set<string>temp;
			string t;
			//�ָ�|ǰ��
			for (int j = 0; j < right.length(); j++) {
				if (right[j] == '|') {
					temp.insert(t);
					t = "";
				}
				else
				{
					//���ַ���ĩβ���
					t.append(right.substr(j, 1));
				}

			}
			temp.insert(t);
			//pair��Ҫ�������ǽ�����������ϳ�һ������
			splitproductions.insert(pair<string, set<string>>(left, temp));
		}
	}
	//map �Զ�����key �� value�Ķ�Ӧ��key �� value��������������Ҫ�����ͣ������Զ������͡�
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
			//�Ǵ�д��ĸ
			if (temp[i] >= 'A' && temp[i] <= 'Z') {
				//��'
				if (temp[i + 1] == '\'') {
					nonT.insert(temp.substr(i, 2));
					i++;
				}
				else {
					nonT.insert(temp.substr(i, 1));
				}
			}
			//���ս��
			else
			{
				T.insert(temp.substr(i, 1));
			}
		}
	}

	cout << "���ս��" << endl;
	for (set<string>::iterator it = nonT.begin(); it != nonT.end(); it++) {
		cout << *it << endl;
	}

	cout << "�ս��" << endl;
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
	//  count()����s���ֵĴ���
	if (splitproductions.count(s) > 0) {
		set<string>temp = splitproductions[s];
		for (set<string>::iterator it = temp.begin(); it != temp.end(); it++) {
			string temp1 = *it;
			if (temp1 == "#") {
				first[s].insert("#");
			}
			else {
				int flagAll = 0;//���еķ��ս����first������#��
				//λ��i�б�
				for (int i = 0; i < temp1.length(); i++) {
					int flag = 0;//��ǰ�ķ��ս����first����#��
					if (temp1[i + 1] == '\'') {//��'�ķ��ս��
						set<string>t1 = getFirst(temp1.substr(i, 2));
						for (set<string>::iterator itt = t1.begin(); itt != t1.end(); itt++) {
							if (*itt == "#") {//��ʱ�մ����ɲ���
								flag = 1;
							}
							else {
								first[s].insert(*itt);
							}
						}
						i++;
					}
					
					else if (isnonT(temp1.substr(i, 1)))//�������ս��
					{
						set<string>t2 = getFirst(temp1.substr(i, 1));
						for (set<string>::iterator itt = t2.begin(); itt != t2.end(); itt++) {
							if (*itt == "#") {//��ʱ�մ����ɲ���
								flag = 1;
							}
							else {
								first[s].insert(*itt);
							}
						}
					}
					else {//�ս��
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
	cout << "First��" << endl;
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
				if (isT(temp.substr(i, 1))) {//�ս��
					continue;
				}
				else if (i + 1 < temp.length() && temp[i + 1] == '\'') {//���С��ķ��ս��
					if (isT(temp.substr(i + 2, 1))) {//���ս���������ս��
						follow[temp.substr(i, 2)].insert(temp.substr(i + 2, 1));
						i++;
					}
					else {//���ս�������Ƿ��ս��s
						//�Ѻ�����ս����first��FirstAndFollow����follow����
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
				else {//�������ķ��ս��

					if (i + 1 < temp.length() && isT(temp.substr(i + 1, 1))) {//���ս���������ս��
						follow[temp.substr(i, 1)].insert(temp.substr(i + 1, 1));
						i++;
					}
					else {//���ս�������Ƿ��ս��s
						//�Ѻ�����ս����first��FirstAndFollow����follow����
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
	//��һ����Ҫ����м��Σ���Ϊfollow�ǲ���������
	getFollow2();
	getFollow2();
	getFollow2();
	cout << "Follow��" << endl;
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
				if (isT(now)) {//����ʽ������ս��
					break;
				}
				else {//����ʽ����Ƿ��ս��
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
