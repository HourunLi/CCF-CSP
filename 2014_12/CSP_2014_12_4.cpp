#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;

struct UndirectedEdge {
    int u, v, w;
    bool operator < (const UndirectedEdge &other) const {
        return w < other.w;
    }
};

class UndirectedGraph {
private:
    int n, m;
    uint32 tot;
    UndirectedEdge *edges;
public:
    UndirectedGraph() {
        
    }
    UndirectedGraph(int n_, int m_): n(n_), m(m_){
        edges = new UndirectedEdge[m+5]();
        tot = 0;
    }

    void add(int u, int v, int w = 0) {
        edges[++tot].u = u;
        edges[tot].v = v;
        edges[tot].w = w;
    }

    void edgesSort() {
        sort(edges+1, edges+m+1);
    }

    UndirectedEdge edge(uint32 e) {
        return edges[e];
    }

    uint32 getEdgeNum() {
        return m;
    }

    uint32 getNodeNum() {
        return n;
    }
};

class UnionFind {
private: 
    int n;
    uint32 *parent;
public:
    UnionFind() {

    }

    UnionFind(int n): n(n) {
        parent = new uint32[n+5];
        for(int i = 0; i < n+5; i++) {
            parent[i] = i;
        }
    }
    ~UnionFind() {
        delete[] parent;
    }

    inline void merge(const int x, const int y) {
        parent[find(x)] = find(y);
    }

    uint32 find(const int x) {
        if(parent[x] == x) return x;
        parent[x] = find(parent[x]);
        return parent[x];
    }
};

class Kruskal {
private:
    UndirectedGraph *graph;
    UnionFind *unionFind;
public:
    Kruskal(UndirectedGraph *graph_) {
        graph = graph_;
        unionFind = new UnionFind(graph->getNodeNum());
    }

    ~Kruskal() {
        delete unionFind;
    }

    void add(int u, int v, int w) {
        graph->add(u, v, w);
        return;
    }

    // bool cmp(const int a, const int b) {
    //     return graph->edge(a).w < graph->edge(b).w;
    // }

    // return <min weight of MST, max edge weight>
    Pair solve() {
        int cnt = 0, ans = 0;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        graph->edgesSort();
        for(int i = 1; i <= m; i++) {
            int u = graph->edge(i).u;
            int v = graph->edge(i).v;
            int w = graph->edge(i).w;
            if(unionFind->find(u) != unionFind->find(v)) {
                unionFind->merge(u, v);
                ans += w;
                cnt++;
            }
            if(cnt == n-1) {
                return make_pair(ans, w);
            }
        }
        return make_pair(-1, -1);
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    UndirectedGraph graph(n, m);
    Kruskal solver(&graph);
    int u, v, w;
    for(int i = 1; i <= m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
    }
    Pair ans = solver.solve();
    cout << ans.first << endl;
    return 0;
}