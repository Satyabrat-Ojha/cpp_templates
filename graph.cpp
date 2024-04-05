#include <bits/stdc++.h>
using namespace std;

class Hash {
    map<tuple<int,int,int>,int> hash_table;
public:
    Hash() {}
    int hash(int x) { return hash({x,0,0}); }
    int hash(tuple<int,int> x) { return hash({get<0>(x),get<1>(x),0}); }
    int hash(tuple<int,int,int> x) {
        if (hash_table.find(x) == hash_table.end()) {
            int new_hash = hash_table.size();
            hash_table[x] = new_hash;
        }
        return hash_table[x];
    }
};

class Graph {
	bool is_directed;
public:
	vector<vector<pair<int,int>>>adj;
    int n;
    Hash h;

    // Initializes graph with n vertices and is it directed
	Graph(int n_, bool is_directed_ = true){
		n=n_+1; is_directed = is_directed_;
		adj.resize(n,vector<pair<int,int>>());
	}

    // Adds edge from u to v with weight w
    void add_edge(int u, int v, int w = 1) { add_edge_internal(h.hash(u), h.hash(v), w); }
    void add_edge(tuple<int,int> u, tuple<int,int> v, int w = 1) { add_edge_internal(h.hash(u), h.hash(v), w); }
    void add_edge(tuple<int,int,int> u, tuple<int,int,int> v, int w = 1) { add_edge_internal(h.hash(u), h.hash(v), w); }

private :
	void add_edge_internal(int u, int v, int w=1) {
		add_edge_weighted_directed(u,v,w);
		if(!is_directed) add_edge_weighted_directed(v,u,w);
	}
	void add_edge_weighted_directed(int u, int v, int w=1) { adj[u].push_back({v,w}); }
};

class Djikstra {
    vector<int> min_dist_from_source;
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
    void run(int source) { run_internal((G->h).hash(source)); }
    void run(tuple<int,int> source) { run_internal((G->h).hash(source)); }
    void run(tuple<int,int,int> source) { run_internal((G->h).hash(source)); }

    // Returns minimum distance from source to target
    int min_dist(int target) { return min_dist_from_source[(G->h).hash(target)]; }
    int min_dist(tuple<int,int> target) { return min_dist_from_source[(G->h).hash(target)]; }
    int min_dist(tuple<int,int,int> target) { return min_dist_from_source[(G->h).hash(target)]; }

    // Returns whether target is visited
    bool is_visited(int target) { return visited[(G->h).hash(target)]; }
    bool is_visited(tuple<int,int> target) { return visited[(G->h).hash(target)]; }
    bool is_visited(tuple<int,int,int> target) { return visited[(G->h).hash(target)]; }

private:
    void run_internal(int source) {
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0,source});
        min_dist_from_source[source] = 0;

        while (!pq.empty()) {
            int dist = pq.top().first, u = pq.top().second; 
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;

            for (auto e: G->adj[u]) {
                int v = e.first, w = e.second;
                if (min_dist_from_source[v] == -1 || min_dist_from_source[v] > dist + w) {
                    min_dist_from_source[v] = dist + w;
                    pq.push({min_dist_from_source[v], v});
                }
            }
        }
    }
};

int main() {
    // GFG Djikstra example
    Graph G(9,false);
    G.add_edge(0,1,4);
    G.add_edge(0,7,8);
    G.add_edge(1,2,8);
    G.add_edge(1,7,11);
    G.add_edge(2,3,7);
    G.add_edge(2,8,2);
    G.add_edge(2,5,4);
    G.add_edge(3,4,9);
    G.add_edge(3,5,14);
    G.add_edge(4,5,10);
    G.add_edge(5,6,2);
    G.add_edge(6,7,1);
    G.add_edge(6,8,6);
    G.add_edge(7,8,7);

    Djikstra D(&G);
    D.run(0);

    for(int i=0;i<9;i++)
    	cout<<D.min_dist(i)<<" ";
}