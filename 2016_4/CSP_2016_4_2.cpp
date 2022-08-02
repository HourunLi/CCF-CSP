#include<bits/stdc++.h>
using namespace std;
int mmap[20][10];
struct Node {
    int x, y;
    Node(int x, int y) : x(x), y(y) {

    }
    Node() {}
};

void display() {
    for(int i = 14; i >= 0; i--) {
        for(int j = 0; j < 10; j ++) {
            cout << mmap[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    // freopen("input.txt", "r", stdin);
    
    Node arr[16];
    int arrSize = 0, offset;

    for(int i = 14; i >= 0; i--) {
        for(int j = 0; j < 10; j++) {
            cin >> mmap[i][j];
        }
    }

    for(int x = 3; x >= 0; x--) {
        for(int y = 0; y < 4; y++) {
            int tmp;
            cin >> tmp;
            if(tmp) {
                arr[arrSize++] = Node(x, y);
            }
        }
    }
    cin >> offset;
    offset--;
    int minH = 15;
    for(int h = 14; h >=-3; h--) {
        bool fit = true;
        for(int i = 0; i < arrSize; i ++) {
            int x = arr[i].x, y = arr[i].y;
            if(h + x < 0 || h + x >= 15 || mmap[h + x][offset+y]) {
                fit = false;
                break;
            }
        }
        if(!fit && minH < 15) {
            break;
        } 
        if(fit) {
            minH = h;
        }
    }
    if(minH < 15) {
        for(int i = 0; i < arrSize; i ++) {
            int x = arr[i].x, y = arr[i].y;
            mmap[minH + x][offset+y] = 1;
        }
    }

    display();
    return 0;
}