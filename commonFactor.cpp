#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;
/* 
S->ab|abb|cddd|cbb|d|c
T->ab|abb
*/
class node {
public:
    string left;  //����ʽ��
    vector<string> right; //����ʽ�Ҳ�
    node(const string& str) {
        left = str;
        right.clear();
    }
    void push(const string& str) {
        right.push_back(str);
    }
    void print() {
        vector<string>::iterator it = right.begin();
        if (it != right.end()) {
            cout << left << "->" << *it++;
            for (;it != right.end();it++)
                cout <<"|"<< *it;
            cout << endl;
        }
    }

};
vector<node> vnode;  //ÿһ������ʽ
map<string, int>mb;//��ŵ�һ���ַ�
//��ȡ�����ǰ׺
string longestCommonPrefix(vector<string>& strs) {
    if (strs.size() == 0)return "";
    string s = strs[0];
    for (int i = 1;i < strs.size();i++)
    {
        int n = min(s.size(), strs[i].size());
        int cnt = 0;
        string s1 = strs[i];
        while (cnt < n && s[cnt] == s1[cnt])
        {
            cnt++;
        }
        s = s.substr(0, cnt);
    }
    return s;
}
void commonFactor() {
    int num = vnode.size();
    for (int n = 0;n <num ;n++) {
        vector<string>::iterator it = vnode[n].right.begin();
        for (;it != vnode[n].right.end();it++) {
            string temp = *it;
            if (mb.find(temp.substr(0, 1)) != mb.end()) {
                mb[temp.substr(0, 1)]++;
            }
            else
                mb.insert(pair<string, int>(temp.substr(0, 1), 1));
        }
        vector<string> ans1;//�����Ӻ���
        vector<string> ans2;//����
        vector<string> temp;
        string s = "";
        for (map<string, int>::iterator i = mb.begin(); i != mb.end(); i++) {
            if (i->second > 1) {
                while (!vnode[n].right.empty()) {
                    vector<string>::iterator itt = vnode[n].right.begin();
                    string tempp = *itt;
                    if (tempp.substr(0, 1) == i->first) {
                        temp.push_back(tempp);
                    }
                    else
                        ans2.push_back(tempp);
                    vnode[n].right.erase(vnode[n].right.begin());
                }

            }
            if (!temp.empty()) {
                s = s + "'";
                string ans = longestCommonPrefix(temp); //������
                int len = ans.length();
                for (int j = 0;j < temp.size();j++) {
                    if(temp[j].substr(len) == "")
                        ans1.push_back("#");
                    else
                    ans1.push_back(temp[j].substr(len));

                }
                ans2.push_back(ans + vnode[n].left +s );
                vnode.push_back(node(vnode[n].left +s));
                for (vector<node>::iterator q = vnode.begin();q!= vnode.end();q++) {
                    if (q->left == vnode[n].left + s) {
                        for (int k = 0;k < ans1.size();k++)//s'
                            q->right.push_back(ans1[k]);
                    }
                  
                            
                }
                
            }
            for (int k = 0;k < ans2.size();k++)
                vnode[n].right.push_back(ans2[k]);    //���¼����µĲ���ʽ�Ҳ�
            ans2.clear();
            ans1.clear();
            temp.clear();
        }

    }

}
int main() {
    int num;
    char buf[100];   //����ʽ
    cout << "����ʽ����" << endl;
    while (cin >> num) {
        vnode.clear();
        int n = 0;//��ǰ�ǵ�n��ʽ��
        cout << "�������ʽ��" << endl;
        for (int i = 0;i < num;i++) {
            cin >> buf;
            int len = strlen(buf), j;
            for (j = 0;j < len;j++)
                if (buf[j] == '-') {
                    buf[j] = 0;  //�����󲿺��Ҳ��з�
                    break;
                }
            string tmp = buf; //�õ�����ʽ����
            vnode.push_back(node(tmp));
            tmp = buf + j + 2;  //�õ�����ʽ���Ҳ�
            string ans = "";//ȥ��|��Ĳ���ʽ�Ҳ�
            for (int i = 0;i < tmp.length();i++) {
                if (tmp[i] == '|') {
                    vnode[n].push(ans);
                    ans = "";
                }
                else {
                    ans = ans + tmp[i];
                }
            }
            vnode[n++].push(ans);
        }
        string str = longestCommonPrefix(vnode[0].right);
         commonFactor();

        cout << "���:" << endl;
        for (int k = 0;k < vnode.size();k++)
            vnode[k].print();
    }
    return 0;

}