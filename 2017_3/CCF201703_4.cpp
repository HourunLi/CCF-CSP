#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;

#define INF 0x3f3f3f3f

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

class Dijkstra{
private:
    int *dist;
    bool *vis;
    DirectedGraph *graph;
    priority_queue<Pair, vector<Pair>, greater<Pair> > q;
public:
    Dijkstra(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        dist = new int[n+5]();
        memset(dist, INF, (n+5) * sizeof(int));
        vis = new bool[n+5]();
    }

    ~Dijkstra() {
        delete[] dist;
        delete[] vis;
    }

    // add edge
    void add(int u, int v, int w = 0) {
        graph->add(u, v, w);
    }

    void dijkstra(int s) {
        dist[s] = 0;
        q.push(make_pair(0, s));
        while(!q.empty()) {
            int s = q.top().second;
            q.pop();
            if(vis[s]) continue;
            vis[s] = true;
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                int maxWeight = max(dist[s], graph->edge(e).w);
                dist[t] = min(dist[t], maxWeight);
                if(!vis[t]) {
                    q.push(make_pair(dist[t], t));
                }
            }
        }
    }

    int getAnswer(int t) {
        return dist[t];
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    DirectedGraph graph(n, 2*m);
    int u, v, w;
    for(int i = 1 ;i <= m; i++) {
        scanf("%d %d %d",&u, &v, &w);
        graph.add(u, v, w);
        graph.add(v, u, w);
    }

    Dijkstra solver(&graph);
    solver.dijkstra(1);
    cout << solver.getAnswer(n) << endl;
    return 0;
}