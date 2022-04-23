#include<bits/stdc++.h>
using namespace std;

struct DOT{
    int x, y;
};
int main() {
    struct DOT A[1000], B[1000];
    int n, m;
    int x, y;
    char type;
    int cnt1 = 0, cnt2 = 0;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        cin >> x >> y >> type;
        if(type == 'A') {
            A[cnt1].x = x;
            A[cnt1++].y = y;
        } else if(type == 'B') {
            B[cnt2].x = x;
            B[cnt2++].y = y;
        }   
    }
    long long int k1, k2, k3;
    for(int i = 0; i < m; i++) {
        cin >> k1 >> k2 >> k3;
        long long int flag = (k1 + k2*A[0].x + k3*A[0].y) > 0 ? 1 : -1;
        bool ret = false;
        for(int j = 1; j < cnt1; j++) {
            long long int t = k1 + k2*A[j].x + k3*A[j].y;
            if(flag * t < 0) {
                cout << "No\n";
                ret = true;
                break;
            }
        }
        if(ret) {
            continue;
        }
        for(int j = 0; j < cnt2; j++) {
            long long int t = k1 + k2*B[j].x + k3*B[j].y;
            if(flag * t > 0) {
                ret = true;
                cout << "No\n";
                break;
            } 
        }
        if(ret) {
            continue;
        }
        cout << "Yes\n";
    }
    return 0;
}
/*
9 3
1 1 A
1 0 A
1 -1 A
2 2 B
2 3 B
0 1 A
3 1 B 
1 3 B 
2 0 A 
0 2 -3 
-3 0 2 
-3 1 1
*/