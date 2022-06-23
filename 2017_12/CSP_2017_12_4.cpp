#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;

#define INF 0x3f3f3f3f

struct DirectedEdge {
    int t, next, from, to, w;
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

    void add(int t, int u, int v, int w = 0) {
        edges[++tot].next = head[u];
        edges[tot].t = t;
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


struct Node {
    int to, s;
    uint32 dist;
    Node(int to_, uint32 dist_, int s_) {
        to = to_;
        dist = dist_;
        s = s_;
    }

    bool operator < (const Node& other) const {
        return dist > other.dist; 
    }

};
class Dijkstra{
private:
    uint32 *dist;
    bool *vis;
    DirectedGraph *graph;
    priority_queue<Node> q;
public:
    Dijkstra(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        dist = new uint32[n+5]();
        memset(dist, INF, (n+5) * sizeof(uint32));
        vis = new bool[n+5]();
    }

    ~Dijkstra() {
        delete[] dist;
        delete[] vis;
    }
    // add edge
    void add(int t, int u, int v, int w = 0) {
        graph->add(t, u, v, w);
    }

    void dijkstra(int source) {
        dist[source] = 0;
        q.push(Node(source, 0, 0));
        while(!q.empty()) {
            Node top = q.top();
            q.pop();
            int s = top.to;
            if(vis[s]) continue;
            vis[s] = true;
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                if(vis[t]) continue;
                if(graph->edge(e).t == 0) {
                    if(dist[s] + graph->edge(e).w < dist[t]) {
                        dist[t] = dist[s] + graph->edge(e).w;
                        q.push(Node(t, dist[t], 0));
                    }
                } else {
                    uint32 length = dist[s] + (graph->edge(e).w + 2 * top.s)*(graph->edge(e).w);
                    if(length < dist[t]) {
                        dist[t] = length;
                        q.push(Node(t, dist[t], top.s + graph->edge(e).w));
                    }
                }
            }
        }
    }

    uint64 getAnswer(int t) {
        return dist[t];
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    DirectedGraph graph(n, 2*m);
    Dijkstra solver(&graph);
    int t, u, v, w;
    
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d %d", &t, &u, &v, &w);
        solver.add(t, u, v, w);
        solver.add(t, v, u, w);
    }
    solver.dijkstra(1);
    cout << solver.getAnswer(n);
    return 0;
}
