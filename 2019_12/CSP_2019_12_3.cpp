#include<bits/stdc++.h>
using namespace std;

#ifdef DEBUG
#define print(...) printf(__VA_ARGS__)
#else
#define print(...)
#endif


void processCh(map<string, int> &mmap, string s, int mode, int factor) {
    if(s == "") return;
    // cout << s << " " << factor << endl;
    int p = 0;
    int n = s.size();
    for(p; p < n; p++) {
        if(s[p] >='0' && s[p] <='9') break;
    }
    int num = 1;
    for(int i = p; i < n; i++) {
        num = 0;
        if(!(s[i] >= '0' && s[i] <= '9')) break;
        num = num*10 + (s[i]-'0');
    }
    string e = s.substr(0, p);

    if(mode) {
        mmap[e] -= num*factor;
    } else{
        mmap[e] += num*factor;
    }

    // for(auto i : mmap) {
    //     cout << i.first << " " << i.second << " || ";
    // }
    // cout << endl;
}
void processWord(map<string, int> &mmap, string s, int mode, int factor = 1) {
    // cout << s << " " << factor << endl;
    int n  = s.size();
    int st = 0;

    if(s[0] == '(') {
        int last;
        stack<int> sta;
        sta.push(0);
        for(int i = 1; i < n; i++) {
            if(s[i] == '(') {
                sta.push(i);
            } else if(s[i] == ')') {
                sta.pop();
                if(sta.empty()) {
                    last = i;
                }
            }
        }
        int aa = last+1, tmp = 1;
        if(aa < n && s[aa] >= '0' && s[aa] <= '9') {
            tmp = 0;
        }
        for(aa; aa < n; aa++) {
            if(!(s[aa] >= '0' && s[aa] <= '9')) break;
            tmp = tmp*10 + (s[aa]-'0');
        }
        processWord(mmap, s.substr(1, last-1), mode, tmp*factor);
        st = aa;
    }

    if(s[st] >= '0' && s[st] <= '9') {   
        int tmp = 0;
        for(st; st < n; st++) {
            if(!(s[st] >= '0' && s[st] <= '9')) break;
            tmp = tmp*10 + (s[st]-'0');
        }
        factor *= tmp;
    } 

    int end = st;
    string ele;
    while(end++ < n) {
        if(s[end] >='A' && s[end] <= 'Z') {
            processCh(mmap, s.substr(st, end-st), mode, factor);
            st = end;
        } else if(s[end] == '(') {
            processCh(mmap, s.substr(st, end-st), mode, factor);
            processWord(mmap, s.substr(end), mode, factor);
            return;
        }
    }
    processCh(mmap, s.substr(st, n-st), mode, factor);
    return;
}
void judge(string buffer) {
    // cout << "----------------------------\n" << buffer << "\n---------------------\n";
    int n = buffer.length();
    map<string, int> mmap;
    int mid = buffer.find('=', 0);
    int pre = 0;
    while(true) {
        int now = buffer.find('+', pre);
        if(now > mid || now == string::npos) {
            processWord(mmap, buffer.substr(pre, mid-pre), 0); 
            break;
        }
        processWord(mmap, buffer.substr(pre, now-pre), 0); 
        pre = now+1;
    }
    pre = mid + 1;
    while(true) {
        int now = buffer.find('+', pre);
        if(now == string::npos) {
            processWord(mmap, buffer.substr(pre), 1); 
            break;
        }
        processWord(mmap, buffer.substr(pre, now-pre), 1); 
        pre = now+1;
    } 
    for(auto i : mmap) {
        if(i.second != 0) {
            cout << "N\n";
            return;
        }
    }
    cout << "Y\n";
}
int main() {
    // freopen("input.txt", "r", stdin);
    int n;
    cin >> n;
    string buffer;
    for(int i = 0; i < n; i++) {
        cin >> buffer;
        judge(buffer);
    }
}