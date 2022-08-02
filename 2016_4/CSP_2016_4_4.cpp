#include<bits/stdc++.h>
using namespace std;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int st[105][105], ed[105][105], ans[105][105];
bool inq[105][105][1000];
int n, m, t;

struct Node {
    int x, y;
    Node(int x, int y) : x(x), y(y) { 

    }
    Node() {

    }
};
int main() {
    // freopen("input.txt", "r", stdin);
    cin >> n >> m >> t;
    for(int i = 0 ; i < t; i++) {
        int r, c;
        cin >> r >> c;
        cin >> st[r][c] >> ed[r][c];
    }
    queue<Node> q;
    q.push(Node(1, 1));
    inq[1][1][0] = true;
    while(!q.empty()) {
        Node top = q.front(); 
        q.pop();
        int x = top.x, y = top.y;
        inq[x][y][ans[x][y]] = false;
        if(x == n && y == m) {
            cout << ans[x][y];
            return 0;
        }
        for(int i = 0; i < 4; i++) {
            int nx = x + dx[i], ny = y + dy[i], ntime = ans[x][y] + 1;
            if(nx <= 0 || ny <= 0 || nx > n || ny > m) continue;
            if(st[nx][ny] <= ntime && ntime <= ed[nx][ny] || inq[nx][ny][ntime]) continue;
            ans[nx][ny] = ntime;
            inq[nx][ny][ntime] = true;
            q.push(Node(nx, ny));
        }
    }
    return 0;
}