#include<bits/stdc++.h>
using namespace std;

int N, K;
double P[16];
//start from 0
bool getKBit(int v, int k) {
    return (v >> k) & 1;
}

int getBits(int v, int N) {
    int ret = 0;
    for(int i = 0; i < N ;i++){
        ret += (v >> i) & 1;
    }
    return  ret;
}

bool isOK(int t, int val) {
    int bits = getBits(val, N);
    return (t - bits) >= (N- bits)*K;
}

bool add(int k, int val, double t, double **dp) {
    bool flag = (dp[k][val] == 0);
    dp[k][val] += t;
    return flag;
}

int main(){
    cin >> N >> K;
    for(int i = 0; i < N ;i++) 
        cin >> P[i];
    
    double** dp = (double **)calloc(N*K, sizeof(double *));
    for(int i = 0; i < N*K; i++) {
        dp[i] = (double *)calloc((1<<N), sizeof(double));
    }
    dp[0][0] = 1;
    double ans = 0;
    queue<pair<int, int>> q; //k, val; 
    q.push({0, 0});
    while(!q.empty()) {
        for(int i = 0; i < N*K; i++) {
            for(int j = 0; j < (1<<N); j++) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        auto top = q.front(); q.pop();
        if(isOK(top.first, top.second)) {
            ans += dp[top.first][top.second] * top.first;
        }else{
            for(int i = 0; i < N ;i++) {
                int t = top.first, val = top.second;
                if(getKBit(val, i)) {
                    if(add(t+1, val, P[i]*dp[t][val], dp)) {
                        q.push({t+1, val});
                    }
                }else{
                    if(add(t+1, val+(1<<i), P[i]*dp[t][val], dp)) {
                        q.push({t+1, val+(1<<i)});
                    }                   
                }
            }
        }
    }
    
    cout << ans;
    return 0;
}
/*
6 5
0.1 0.15 0.35 0.05 0.25 0.1 
*/