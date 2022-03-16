#include<bits/stdc++.h>
using namespace std;

int LEVEL = 10005;
int main() {
    int n, maxLevel = 0, maxSub = 0, sub = 0;
    cin >> n;
    int *a = new int[n+2]();
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        maxLevel = max(maxLevel, a[i]);
    }
    n = unique(a, a+n+2)-a-1;
    int *ans = new int[maxLevel+2]();
  
    for(int i = 1; i < n; i++) {
        if(a[i-1] > a[i] && a[i+1] > a[i]) ans[a[i]]--;
        if(a[i-1] < a[i] && a[i+1] < a[i]) ans[a[i]]++;
    }

    for(int i = maxLevel; i >= 0; i--) {
        sub += ans[i];
        maxSub = max(maxSub, sub);
    }
    delete[] ans;
    delete[] a;
    cout << maxSub;
    return 0;
}