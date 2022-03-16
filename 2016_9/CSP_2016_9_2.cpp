#include<bits/stdc++.h>

using namespace std;
int ptr[6];
int seat[20];
void rePos() {
    for(int k = 1; k <= 5; k++) {
        int row = ptr[k];
        if(row < 0) continue;
        while(5 - seat[row] < k) {
            row++;
        }
        ptr[k] = row < 20 ? row : -1; 
    }
    return;
}
void arrange(int t) {
    if(ptr[t] != -1) {
        int row = ptr[t], col = seat[row];
        for(int i = 1; i <= t; i++) {
            cout << row*5 + col + i << " ";
        }
        seat[row] += t;
        rePos();
    }else{
        for(int i = 0; i < t; i++) {
            arrange(1);
        }
    }
    return;
}
int main() {
    int n, t;
    cin >> n;
    for(int i = 0; i< n; i++) {
        cin >> t;
        arrange(t);
        cout << endl;
    }
    return 0;
}