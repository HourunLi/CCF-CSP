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

struct Node {
    int from, to, dist, w;

    Node(int from_, int to_, int dist_, int w_) {
        from = from_;
        to = to_;
        dist = dist_;
        w = w_;
    
    }
    
    bool operator < (const Node& other) const {
        if (dist != other.dist) return dist > other.dist;
        return w > other.w;
    }
};

class Dijkstra{
private:
    int ans;
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
        ans = 0;
    }

    ~Dijkstra() {
        delete[] dist;
        delete[] vis;
    }
    // add edge
    void add(int u, int v, int w = 0) {
        graph->add(u, v, w);
    }

    void dijkstra(int source) {
        dist[source] = 0;
        q.push(Node(source, source, 0, 0));
        while(!q.empty()) {
            Node top = q.top();
            q.pop();
            int s = top.to;
            if(vis[s]) continue;
            vis[s] = true;
            ans += top.w;
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                if(vis[t]) continue; 
                if(dist[s] + graph->edge(e).w <= dist[t]) {
                    dist[t] = dist[s] + graph->edge(e).w;
                    q.push(Node(s, t, dist[t], graph->edge(e).w));
                }                    
            }
        }
    }

    int getAnswer() {
        return ans;
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m;
    DirectedGraph graph(n, 2*m);
    Dijkstra solver(&graph);
    int u, v, w;
    
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
        solver.add(v, u, w);
    }
    solver.dijkstra(1);
    cout << solver.getAnswer();
    return 0;
}
