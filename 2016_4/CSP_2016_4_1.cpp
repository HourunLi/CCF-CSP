#include<bits/stdc++.h>
using namespace std;

int main() {
    // freopen("input.txt", "r", stdin);
    int n, ans = 0, pre, now;
    // flag = 1 means up; flag = 0 means down
    int flag = -1;
    cin >> n;
    cin >> pre;
    for(int i = 1; i < n; i++) {
        cin >> now;
        if(flag >= 0 && flag != now > pre) ans++;
        flag = now > pre;
        pre = now;
    }
    cout << ans << endl;
    return 0;
}