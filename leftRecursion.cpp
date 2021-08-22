#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
using namespace std;
/*
  3
  Q->Rb|b
  R->Sa|a
  S->Qc|c
*/

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
        cout << left<<"->"<<*it++; 
        for (;it != right.end();it++)
           cout << '|' << *it;
        cout<< endl;
    }
};
map<string, int> sub;  //��¼ÿ��node���±�
vector<node> vnode;  //ÿһ������ʽ

//��ʼ������
void init() {
    sub.clear();
    vnode.clear();
}
//���������ݹ�
void Indirect() {
    for (int i = 0;i < vnode.size();i++) {
        for (int j = 0;j < i;j++) {
            vector<string> ans;
            set<string>& righti = vnode[i].right;
            set<string>& rightj = vnode[j].right;
            char ch = vnode[j].left[0]; //ȡ����Aj����ʽ���󲿵ķ��ս��
            set<string>::iterator iti, itj;
            for (iti = righti.begin();iti != righti.end();iti++) {
                if (iti->at(0) == ch) //�����ǰ����ʽ�Ҳ��ķ��ս����Aj��ͬ
                    for (itj = rightj.begin();itj != rightj.end();itj++)
                        ans.push_back(*itj + iti->substr(1));   //�����滻����,�ȴ洢����
            }
            while (!righti.empty()) {
                if (righti.begin()->at(0) != ch) //�洢��ǰû���滻�Ĳ���ʽ�Ҳ�
                    ans.push_back(*righti.begin());
                righti.erase(righti.begin());  //���滻���Ĳ���ʽ�Ҳ�Ҳɾ����
            }
            for (int k = 0;k < ans.size();k++)  //���滻���Ĳ���ʽ�Ҳ����и��²���
                righti.insert(ans[k]);
        }
    }
    cout << "���������ݹ飺" << endl;
    for (int k = 0;k < vnode.size();k++)
        vnode[k].print();
}
//����ֱ����ݹ�
void Direct() {
    for (int i = 0;i < vnode.size();i++) {
        char ch = vnode[i].left[0];
        set<string>& right = vnode[i].right;  //�õ���ǰ�Ҳ�
        //set<string>& rightt = vnode[i].right;
        set<string>::iterator it;
        string tmp = vnode[i].left.substr(0, 1) + "\'"; //�Է��ս������
        bool flag = true;
        for (it = right.begin();it != right.end();it++) {
            if (it->at(0) == ch) {
                vnode.push_back(node(tmp));
                sub[tmp] = vnode.size();
                flag = false;
                break;
            }
        }
        int idx = sub[tmp] - 1;
          if (flag) continue; //���ڷ��ս������ͬ�Ĳ���ʽ������Ҫ����
        vector<string> ans;
        set<string>& tmpSet = vnode[idx].right;
        tmpSet.insert("#");  //��ӿռ�
        while (!vnode[i].right.empty()) {
            if (vnode[i].right.begin()->at(0) == ch)
                tmpSet.insert(vnode[i].right.begin()->substr(1) + tmp);
            else
               ans.push_back(vnode[i].right.begin()->substr(0) + tmp);
            vnode[i].right.erase(vnode[i].right.begin());   //ɾ����ԭ������ʽ�Ҳ�
        }
        for (int k = 0;k < ans.size();k++)
            vnode[i].right.insert(ans[k]);    //���¼����µĲ���ʽ�Ҳ�
    }
    cout << endl;
    cout << "����ֱ����ݹ飺" << endl;
    for (int k = 0;k < vnode.size();k++)
        vnode[k].print();
}
int main() {
    int n;   //����ʽ������
    char buf[100];   //����ʽ
    cout << "����ʽ������" << endl;
    while (cin >> n) {
        init(); //��ʼ��
        cout << "�������ʽ��" << endl;
        for (int i = 0;i < n;i++) {
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
        }
        //for (int k = 0;k < vnode.size();k++)
         //  vnode[k].print();
        Indirect(); //���������ݹ�
        Direct(); //����ֱ����ݹ�
    }
    return 0;
}