/**
 * @file CCF201709_4.CPP
 * @author HourunLi
 * @brief ccf csp 2017 09 4 source: http://118.190.20.162/view.page?gpid=T60
 * @version 0.1
 * @date 2022-06-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <bits/stdc++.h>
using namespace std;
typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;

struct DirectedEdge {
    int next, from, to, w;
};

class DirectedGraph {
private:
    int n, m;
    uint32 *head, tot;
    DirectedEdge *edges;
public:
    DirectedGraph() {

    }
    DirectedGraph(int n_, int m_): n(n_), m(m_){
        edges = new DirectedEdge[m+5]();
        head = new uint32[n+5]();
        tot = 0;
    }

    void add(int u, int v, int w = 0) {
        edges[++tot].next = head[u];
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].w = w;
        head[u] = tot; 
    }

    uint32 begin(uint32 u) {
        return head[u];
    }

    uint32 next(uint32 e) {
        return edges[e].next;
    }

    uint32 end() {
        return 0;
    }

    DirectedEdge edge(uint32 e) {
        return edges[e];
    }

    uint32 getEdgeNum() {
        return m;
    }

    uint32 getNodeNum() {
        return n;
    }
};

void dfs(DirectedGraph &graph, int p, bool* vis) {
    vis[p] = 1;
    for(int e = graph.begin(p); e != 0; e = graph.next(e)) {
        int v = graph.edge(e).to;
        if(vis[v]) continue;
        dfs(graph, v, vis);
    }
    return;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m, ret = 0;
    cin >> n>> m;
    DirectedGraph graph(n, m), rgraph(n, m);
    bool *vis1, *vis2;
    vis1 = new bool[n+5]();
    vis2 = new bool[n+5]();
    int u, v;
    for(int i = 1; i<= m; i++) {
        cin >> u >> v;
        graph.add(u, v);
        rgraph.add(v, u);
    }
    for(int i = 1; i <= n; i++) {
        int flag = false;
        dfs(graph, i, vis1);
        dfs(rgraph, i, vis2);
        for(int j = 1; j <= n; j++) {
            if(!vis1[j] && !vis2[j]) {
                flag = true;
                break;
            }
        }
        if(!flag) ret++;
        memset(vis1, 0, n+5);
        memset(vis2, 0, n+5);
    }
    cout << ret << endl;
    delete []vis1;
    delete []vis2;
    return 0;
}

