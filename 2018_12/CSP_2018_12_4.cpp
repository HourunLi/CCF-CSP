#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;

struct DirectedEdge {
    int next, from, to, w;
};

struct UndirectedEdge {
    int u, v, w;
    bool operator < (const UndirectedEdge &other) const {
        return w < other.w;
    }
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

    void add(int u, int v, int w) {
        edges[++tot].next = head[u];
        edges[tot].from = u;
        edges[tot].to = v;
        edges[tot].w = w;
        head[u] = tot; 
    }

    uint32 begin(uint32 u) {
        return head[u];
    }

    uint32 next(uint32 p) {
        return edges[p].next;
    }

    uint32 end() {
        return 0;
    }

    DirectedEdge edge(uint32 p) {
        return edges[p];
    }

    uint32 getEdgeNum() {
        return m;
    }

    uint32 getNodeNum() {
        return n;
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

    void add(int u, int v, int w) {
        edges[++tot].u = u;
        edges[tot].v = v;
        edges[tot].w = w;
    }

    void edgesSort() {
        sort(edges+1, edges+m+1);
    }

    UndirectedEdge edge(uint32 p) {
        return edges[p];
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
    Kruskal(int n, int m) {
        graph = new UndirectedGraph(n, m);
        unionFind = new UnionFind(n);
    }

    ~Kruskal() {
        delete graph;
        delete unionFind;
    }

    void add(int u, int v, int w) {
        graph->add(u, v, w);
        return;
    }

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
    int n, m, s;
    cin >> n >> m >> s;
    Kruskal solver = Kruskal(n, m);
    int u, v, t;
    for(int i =1; i<= m; i++) {
        scanf("%d %d %d", &u, &v, &t);
        solver.add(u, v, t);
    }
    Pair ans = solver.solve();
    cout << ans.second << endl;
    return 0;
}