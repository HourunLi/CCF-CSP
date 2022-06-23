#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint32;
typedef long long ll;
typedef unsigned long long uint64;
typedef pair<int, int> Pair;
int *type, k;
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
    uint32 ans, cnt;
    uint32 *dist;
    bool *vis;
    DirectedGraph *graph;
public:
    Dijkstra(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        dist = new uint32[n+5]();
        memset(dist, INF, (n+5) * sizeof(uint32));
        vis = new bool[n+5]();
        ans = cnt = 0;
    }

    ~Dijkstra() {
        delete[] dist;
        delete[] vis;
    }

    void init() {
        int n = graph->getNodeNum();
        memset(dist, INF, (n+5) * sizeof(uint32));
        memset(vis, 0, n+5);
        ans = cnt = 0;
    }
    // add edge
    void add(int u, int v, int w = 0) {
        graph->add(u, v, w);
    }

    void dijkstra(int source) {
        priority_queue<Pair, vector<Pair>, greater<Pair> > q;
        dist[source] = 0;
        q.push(make_pair(0, source));
        while(!q.empty() && cnt < k) {
            int s = q.top().second;
            q.pop();
            if(vis[s]) continue;
            vis[s] = true;
            if(type[s]) {
                ++cnt;
                ans += dist[s];
            }
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                if(vis[t]) continue;
                if(dist[s] + graph->edge(e).w < dist[t]){
                    dist[t] = dist[s] + graph->edge(e).w;
                    q.push(make_pair(dist[t], t));
                }
            }
        }
    }

    uint32 getAnswer() {
        return ans;
    }
};

class SPFA {
private:    
    uint32 *dist;
    bool *inqueue;
    DirectedGraph *graph;
    unordered_map<int, int> rec;
public:
    SPFA(DirectedGraph *graph_) {
        graph = graph_;
        int n = graph->getNodeNum(), m = graph->getEdgeNum();
        dist = new uint32[n+5]();
        memset(dist, INF, (n+5) * sizeof(uint32));
        inqueue = new bool[n+5]();
    }
    ~SPFA() {
        delete[] dist;
        delete[] inqueue;
    }
    void init() {
        int n = graph->getNodeNum();
        memset(dist, INF, (n+5) * sizeof(uint32));
        memset(inqueue, 0, n+5);
        rec = unordered_map<int, int>();
    }

    // add edge
    void add(int u, int v, int w = 0) {
        graph->add(u, v, w);
    }

    void spfa(int source) {
        queue<int> q;
        dist[source] = 0;
        q.push(source);
        inqueue[source] = true;
        while(!q.empty()) {
            int s = q.front();
            q.pop();
            inqueue[s] = false;
            if(type[s]) {
                rec[s] = dist[s];
            }
            for(int e = graph->begin(s); e != graph->end(); e = graph->next(e)) {
                int t = graph->edge(e).to;
                if(dist[t] > dist[s] + graph->edge(e).w) {
                    dist[t] = dist[s] + graph->edge(e).w;
                    if(!inqueue[t]) {
                        inqueue[t] = true; 
                        q.push(t);
                    }
                }
            }
        }
    }
    uint32 getAnswer() {
        int ans = 0, cnt = 0;
        priority_queue<int, vector<int>, greater<int> > q;
        // for(auto it = rec.begin(); it != rec.end(), cnt < k; it++, cnt++) {
        for(auto it = rec.begin(); it != rec.end(); it++) {
            q.push(it->second);
        }

        while(!q.empty() && cnt < k) {
            ans += q.top();
            q.pop();
            cnt++;
        }
        return ans;
    }
};

int main() {
    // freopen("input.txt", "r", stdin);
    int n, m;
    cin >> n >> m >> k;
    DirectedGraph graph(n, 2*m);
    Dijkstra solver(&graph);
    type = new int[n+5]();
    for(int i = 1; i<= n; i++) {
        scanf("%d", &type[i]);
    }
    int u, v, w;
    
    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &w);
        solver.add(u, v, w);
        solver.add(v, u, w);
    }

    for(int i = 1; i <= n; i++) {
        // if(type[i]) {
        solver.dijkstra(i);
        // cout << "hehe\n";
        cout << solver.getAnswer() << endl;
        solver.init();
        // }
    }
    delete []type;
    return 0;
}
