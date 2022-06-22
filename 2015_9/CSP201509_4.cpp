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

class TopoSort {
private:
    DirectedGraph *graph;
    bool *vis;
    vector<int> topo;

    bool dfs(int p) {
        vis[p] = -1;
        for(int e = graph->begin(p); e != graph->end(); e = graph->next(e)) {
            int v = graph->edge(e).to;
            if(vis[v]) continue;
            if(vis[v] < 0 || !dfs(v)) return false;
        }
        vis[p] = 1;
        topo.push_back(p);
        return true;
    }
public:
    TopoSort(DirectedGraph *graph_) {
        graph = graph_;
        vis = new bool[graph->getNodeNum() + 5]();
    }
    ~TopoSort() {
        delete []vis;
    }

    vector<int> topoSort() {
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        for(int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            if(!dfs(i)) return {};
        }
        reverse(topo.begin(), topo.end());
        return topo;
    }
};
class SCC {
private:
    int sccCnt;
    DirectedGraph *graph, *rgraph;
    bool *vis;
    vector<int> order;
    vector<vector<int> > ret;
public:
    SCC(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        sccCnt = 0;
        vis = new bool[n + 5]();
        rgraph = new DirectedGraph(n, m);
        for(int i = 1; i <= m; i++) {
            rgraph->add(graph->edge(i).to, graph->edge(i).from);
        }
    }
    ~SCC() {
        delete []vis;
        delete rgraph;
    }   

    void dfs(int p) {
        vis[p] = true;
        for(int e = graph->begin(p); e != graph->end(); e = graph->next(e)) {
            int v = graph->edge(e).to;
            if(vis[v]) continue;
            dfs(v);
        }
        order.push_back(p);
        return;
    }

    void rdfs(int p) {
        vis[p] = true;
        for(int e = rgraph->begin(p); e != rgraph->end(); e = rgraph->next(e)) {
            int v = rgraph->edge(e).to;
            if(vis[v]) continue;
            rdfs(v);
        }
        ret[sccCnt-1].push_back(p);
        return;
    }

    vector<vector<int> > kosaraju() {
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        TopoSort solver = TopoSort(graph);
        for(int i = 1; i <= n; i++) {
            if(vis[i]) continue;
            dfs(i);
        }
        reverse(order.begin(), order.end());
        memset(vis, 0, n+5);
        for(int i = 0; i < n; i++) {
            if(vis[order[i]]) continue;
            ++sccCnt;
            ret.push_back({});
            rdfs(order[i]);
        }
        return ret;
    }

};
int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n>> m;
    DirectedGraph graph(n, m);
    int u, v;
    for(int i = 1 ;i <= m; i++) {
        scanf("%d %d",&u,&v);
        graph.add(u, v);
    }
    SCC solver = SCC(&graph);
    auto ret = solver.kosaraju();
    uint64 ans = 0;
    for(int i = 0; i < ret.size(); i++) {
        uint64 size = ret[i].size();
        ans += size * (size-1) / 2;
    }
    cout << ans << endl;
    return 0;
}