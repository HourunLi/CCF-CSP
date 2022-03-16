//找到一个通用的简单地可以表达面积的表达式
#include<bits/stdc++.h>
using namespace std;

#define MAXN 600
int nums[MAXN+1][MAXN+1];
int S[MAXN+1][MAXN+1];
int n, r, t, l;

int calS(int i,int j) {
    return nums[i][j] - S[i-1][j-1] + S[i-1][j] +S[i][j-1]; 
}

double MEAN(int x, int y) {
    int bottom = min(x+r, n);
    int right = min(y+r, n);
    int top = max(x-r, 1);
    int left = max(y-r, 1);

    double area = S[bottom][right] - S[bottom][left-1] - S[top-1][right] + S[top-1][left-1];
    int cnt = (bottom - top + 1) * (right - left + 1);
    return area/cnt;
}

int main(){
    int ret = 0;
    // cin >> n >> l >> r >> t;
    // for(int i = 1; i <= n; i++) {
    //     for(int j = 1; j <= n; j++) {
    //         cin >> nums[i][j];
    //         S[i][j] = calS(i, j);
    //     }
    // }

    // for(int i = 1; i <= n; i++) {
    //     for(int j = 1; j <= n; j++) {
    //         double grey = MEAN(i, j);
    //         if(grey <= t) {
    //             ret++;
    //         }
    //     }
    // }
    // cout << ret;
    for(int i = 0; i < 10 ; i++) {
        cout << rand() << " ";
    }
    return 0;

}