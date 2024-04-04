typedef long long ll;

class Hash {
    map<tuple<ll,ll,ll>,int> hash_table;

public:
    Hash() {}
    int hash(ll x) { return hash({x,0,0}); }
    int hash(tuple<ll,ll> x) { return hash({get<0>(x),get<1>(x),0}); }
    int hash(tuple<ll,ll,ll> x) {
        if (hash_table.find(x) == hash_table.end()) { hash_table[x] = hash_table.size(); }
        return hash_table[x];
    }
};

class Graph {
    vector<vector<pair<int,int>>> adj;
    int n;
    Hash h;

public:
    // Initializes graph with n vertices
    Graph(ll n_) {
        n = n_;
        adj.resize(n, vector<pair<int,int>>());
    }

    // Adds edge from u to v with weight w
    void add_edge(ll u, ll v, ll w) { add_edge_internal(h.hash(u), h.hash(v), w); }
    void add_edge(tuple<ll,ll> u, tuple<ll,ll> v, ll w) { add_edge_internal(h.hash(u), h.hash(v), w); }
    void add_edge(tuple<ll,ll,ll> u, tuple<ll,ll,ll> v, ll w) { add_edge_internal(h.hash(u), h.hash(v), w); }

private:
    void add_edge_internal(int u, int v, int w) { adj[u].push_back({v,w}); }
};

class Djikstra {
    vector<ll> min_dist_from_source;
    vector<bool> visited;
    Graph *G;

public:
    // Initializes BFS with graph G
    Djikstra(Graph *G_) {
        G = G_;
        min_dist_from_source.assign(G->n, -1);
        visited.assign(G->n, false);
    }

    // Runs BFS from source
    void run(ll source) { run_internal((G->h).hash(source)); }
    void run(tuple<ll,ll> source) { run_internal((G->h).hash(source)); }
    void run(tuple<ll,ll,ll> source) { run_internal((G->h).hash(source)); }

    // Returns minimum distance from source to target
    ll min_dist(ll target) { return min_dist_from_source((G->h).hash(target)); }
    ll min_dist(tuple<ll,ll> target) { return min_dist_from_source((G->h).hash(target)); }
    ll min_dist(tuple<ll,ll,ll> target) { return min_dist_from_source((G->h).hash(target)); }

    // Returns whether target is visited
    bool is_visited(ll target) { return visited((G->h).hash(target)); }
    bool is_visited(tuple<ll,ll> target) { return visited((G->h).hash(target)); }
    bool is_visited(tuple<ll,ll,ll> target) { return visited((G->h).hash(target)); }

private:
    void run_internal(int source) {
        priority_queue<pair<ll,ll>, vector<pair<ll,ll>>, greater<pair<ll,ll>>> pq;
        pq.push({0,source});
        min_dist_from_source[source] = 0;

        while (!pq.empty()) {
            auto [dist, u] = pq.top(); 
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;

            for (auto [v,w] : G->adj[u]) {
                if (min_dist_from_source[v] == -1 || min_dist_from_source[v] > dist + w) {
                    min_dist_from_source[v] = dist + w;
                    pq.push({min_dist_from_source[v], v});
                }
            }
        }
    }
};