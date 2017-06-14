#include <iostream>
#include <vector>

using namespace std;

struct Graph {

    vector< vector<long> > graph;

    Graph(unsigned long N) {
        graph.resize(N+5);
    }

    void AddEdge(long u, long v) {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }


    void ShowVertex(long u) {
        for (vector<long>::iterator it = graph[u].begin(); it != graph[u].end(); ++it) {
            cout << *it << " ";
        }
        cout << '\n';
    }
};


int main() {

    unsigned long N_vertexes;
    long K_ops;

    cin >> N_vertexes;
    cin >> K_ops;

    Graph g(N_vertexes);
    string buf;
    long op, u, v;

    for (long i = 0; i < K_ops; ++i) {

        cin>>op;
        if(op == 1)
        {
            cin >> u >> v;
            g.AddEdge(v, u);
        }

        if(op == 2)
        {
            cin>>u;
            g.ShowVertex(u);
        }
    }

    return 0;
}