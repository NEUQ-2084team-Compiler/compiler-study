#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
// S->ab|abb|cddd|cbbb|d|c
class node {
public:
    string left;  //����ʽ��
    set<string> right; //����ʽ�Ҳ�
    node(const string& str) {
        left = str;
        right.clear();
    }
    void push(const string& str) {
        right.insert(str);
    }
    void print() {
        set<string>::iterator it = right.begin();
        if (it != right.end()) {
            cout << left << "->" << *it++;
            for (;it != right.end();it++)
                cout << '|' << *it;
            cout << endl;
        }
    }
   
};
map<string, int> sub;  //��¼ÿ��node���±�
vector<node> vnode;  //ÿһ������ʽ
map<string, int>mb;
string s = "S'";
int num = 1;
void commonFactor() {
    set<string>::iterator it = vnode[0].right.begin();
    for (;it != vnode[0].right.end();it++) {
        string temp = *it;
        if (mb.find(temp.substr(0, 1)) != mb.end()) {
            mb[temp.substr(0, 1)]++;
        }
        else
            mb.insert(pair<string, int>(temp.substr(0, 1), 1));
    }
    vector<string> ans1;//�����Ӻ���
    vector<string> ans2;//����
      for (map<string, int>::iterator i = mb.begin(); i != mb.end(); i++){
          bool flag = false;
         if (i->second > 1) {
             while (!vnode[0].right.empty()) {
                 set<string>::iterator itt = vnode[0].right.begin();
                 string tempp = *itt;
                 if (tempp.substr(0, 1) == i->first) {
                     if(tempp.substr(1)== "")
                        ans1.push_back("#");
                     else
                         ans1.push_back(tempp.substr(1));

                     ans2.push_back(tempp.substr(0, 1)+s);
                     flag = true;
                 }
                 else
                     ans2.push_back(tempp);
                 vnode[0].right.erase(vnode[0].right.begin());
             }
             
         }
         for (int k = 0;k < ans2.size();k++)
                 vnode[0].right.insert(ans2[k]);    //���¼����µĲ���ʽ�Ҳ�
             
        if (!ans1.empty()) {
            vnode.push_back(node(s));
            for (int k = 0;k < ans1.size();k++)//s'
                vnode[num].right.insert(ans1[k]);
        }
        if (flag) {
            s = s + "'";
            num++;
        }
           
        ans2.clear();
        ans1.clear();
      }
}
int main(){
    char buf[100];   //����ʽ
        cout << "�������ʽ��" << endl;
            cin >> buf;
            int len = strlen(buf), j;
            for (j = 0;j < len;j++)
                if (buf[j] == '-') {
                    buf[j] = 0;  //�����󲿺��Ҳ��з�
                    break;
                }
            string tmp = buf; //�õ�����ʽ����

            if (!sub[buf]) {
                vnode.push_back(node(tmp));
                sub[tmp] = vnode.size();
            }

            int idx = sub[tmp] - 1;  //��ȡ�󲿵��±�
            tmp = buf + j + 2;  //�õ�����ʽ���Ҳ�
            string ans = "";//ȥ��|��Ĳ���ʽ�Ҳ�
            for (int i = 0;i < tmp.length();i++) {
                if (tmp[i] == '|') {
                    vnode[idx].push(ans);
                    ans = "";
                }
                else {
                    ans = ans + tmp[i];
                }
            }
            vnode[idx].push(ans);
       commonFactor();
       cout << "���:" << endl;
       for (int k = 0;k < vnode.size();k++)
           vnode[k].print();
    return 0;
}