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
    string left;  //产生式左部
    set<string> right; //产生式右部
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
map<string, int> sub;  //记录每个node的下标
vector<node> vnode;  //每一个产生式

//初始化工作
void init() {
    sub.clear();
    vnode.clear();
}
//消除间接左递归
void Indirect() {
    for (int i = 0;i < vnode.size();i++) {
        for (int j = 0;j < i;j++) {
            vector<string> ans;
            set<string>& righti = vnode[i].right;
            set<string>& rightj = vnode[j].right;
            char ch = vnode[j].left[0]; //取所有Aj产生式的左部的非终结符
            set<string>::iterator iti, itj;
            for (iti = righti.begin();iti != righti.end();iti++) {
                if (iti->at(0) == ch) //如果当前产生式右部的非终结符和Aj相同
                    for (itj = rightj.begin();itj != rightj.end();itj++)
                        ans.push_back(*itj + iti->substr(1));   //进行替换操作,先存储起来
            }
            while (!righti.empty()) {
                if (righti.begin()->at(0) != ch) //存储当前没有替换的产生式右部
                    ans.push_back(*righti.begin());
                righti.erase(righti.begin());  //被替换过的产生式右部也删除掉
            }
            for (int k = 0;k < ans.size();k++)  //将替换过的产生式右部进行更新操作
                righti.insert(ans[k]);
        }
    }
    cout << "消除间接左递归：" << endl;
    for (int k = 0;k < vnode.size();k++)
        vnode[k].print();
}
//消除直接左递归
void Direct() {
    for (int i = 0;i < vnode.size();i++) {
        char ch = vnode[i].left[0];
        set<string>& right = vnode[i].right;  //拿到当前右部
        //set<string>& rightt = vnode[i].right;
        set<string>::iterator it;
        string tmp = vnode[i].left.substr(0, 1) + "\'"; //对非终结符更改
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
          if (flag) continue; //对于非终结符不相同的产生式我们需要跳过
        vector<string> ans;
        set<string>& tmpSet = vnode[idx].right;
        tmpSet.insert("#");  //添加空集
        while (!vnode[i].right.empty()) {
            if (vnode[i].right.begin()->at(0) == ch)
                tmpSet.insert(vnode[i].right.begin()->substr(1) + tmp);
            else
               ans.push_back(vnode[i].right.begin()->substr(0) + tmp);
            vnode[i].right.erase(vnode[i].right.begin());   //删除掉原本产生式右部
        }
        for (int k = 0;k < ans.size();k++)
            vnode[i].right.insert(ans[k]);    //更新加入新的产生式右部
    }
    cout << endl;
    cout << "消除直接左递归：" << endl;
    for (int k = 0;k < vnode.size();k++)
        vnode[k].print();
}
int main() {
    int n;   //产生式的数量
    char buf[100];   //产生式
    cout << "产生式数量：" << endl;
    while (cin >> n) {
        init(); //初始化
        cout << "输入产生式：" << endl;
        for (int i = 0;i < n;i++) {
            cin >> buf;
            int len = strlen(buf), j;
            for (j = 0;j < len;j++)
                if (buf[j] == '-') {
                    buf[j] = 0;  //进行左部和右部切分
                    break;
                }
            string tmp = buf; //拿到产生式的左部

            if (!sub[buf]) {
                vnode.push_back(node(tmp));
                sub[tmp] = vnode.size();
            }

            int idx = sub[tmp] - 1;  //获取左部的下标
            tmp = buf + j + 2;  //拿到产生式的右部
            string ans = "";//去除|后的产生式右部
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
        Indirect(); //消除间接左递归
        Direct(); //消除直接左递归
    }
    return 0;
}