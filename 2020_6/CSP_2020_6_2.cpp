#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, u, v;
    cin >> n >> u >> v;
    int ind, val;
    vector<pair<int, int> > a, b;
    for(int i = 0; i < u; i++) {
        cin >> ind >> val;
        a.emplace_back(make_pair(ind ,val));
    }
    for(int i = 0; i < v; i++) {
        cin >> ind >> val;
        b.emplace_back(make_pair(ind ,val));
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    int ind1 = 0, ind2 = 0;
    int size1 = a.size(), size2 = b.size();
    long long int ret = 0;
    while(ind1 < size1 && ind2 < size2) {
        if(a[ind1].first == b[ind2].first) {
            ret += (long long int) a[ind1].second * (long long int) b[ind2].second;
            ind1++;
            ind2++;
        } else if(a[ind1].first > b[ind2].first) {
            ind2++;
        } else{
            ind1++;
        }
    }
    cout << ret << endl;
    return 0;
}
/*
10 3 4
4 5
7 -3
10 1 
1 10  
4 20  
5 30 
7 40 
*/