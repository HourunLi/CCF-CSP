#include<bits/stdc++.h>
using namespace std;

struct Location {
    int distance;
    int number;
} locs[205];

int cmp(const void *a, const void *b) {
    struct Location *aa = (struct Location *)a;
    struct Location *bb = (struct Location *)b;

    if (aa->distance != bb->distance) {
        return aa->distance - bb->distance;
    }

    return aa->number - bb->number;
}

// bool comp(Location a, Location b) {
//     if(a.distance != b.distance) {
//         return a.distance < b.distance;
//     }else{
//         return a.number < b.number;
//     }
// }

int main() {
    // freopen("test.txt", "r", stdin);
    int n, X, Y, x, y;
    cin >> n >> X >> Y;

    int i = 0;
    for(int i = 0; i < n; i++){
        cin >> x >> y;
        locs[i].distance = (x- X) * (x- X) + (y - Y) * (y- Y);
        locs[i].number = i+1;
    }

    qsort(locs, n, sizeof(Location), cmp);
    // sort(locs, locs + n, comp);
    cout << locs[0].number << endl << locs[1].number << endl << locs[2].number << endl;
    return 0;
}

