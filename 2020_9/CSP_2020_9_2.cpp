#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, k, t, x_l, y_d, x_r, y_u;
    cin >> n >> k >> t >> x_l >> y_d >> x_r >> y_u;
    int ret1 = 0, ret2 = 0;
    int x, y;

    auto judge = [=](int x, int y) -> bool {
        return x>=x_l && x<=x_r && y >= y_d && y<=y_u;
    };

    for(int i = 0; i < n; i++) {
        bool flag1 = false, flag2 = false;
        int cnt = 0;
        for(int j = 0; j < t; j++) {
            cin >> x >> y;
            if(judge(x, y)) {
                flag1 = true;
                if(++cnt >= k) {
                    flag2 = true;
                }
            }else{
                cnt = 0;
            }
        }
        ret1 += flag1 ? 1 : 0;
        ret2 += flag2 ? 1 : 0;
    }
    cout << ret1 << endl << ret2 << endl;
    return 0;
}