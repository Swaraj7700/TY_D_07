// C++ program for BFS of an undirected graph
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// BFS from given source s || list of vector for adj int and vector(bool) for checking visited adj nodes
void bfs(vector<vector<int>>& adj, int s,
                 vector<bool>& visited) 
{
    // queue for BFS
    queue<int> q;

    // mark the visited node and enqueue it
    visited[s] = true;
    q.push(s);

    // Iterate the queue yill not empty
    while (!q.empty()) {
      
        // Dequeue a node from queue and print it
        int curr = q.front();
        q.pop();
        cout << curr << " ";
// if adj vertices are not visited / visit it and enqueue it
        for (int x : adj[curr]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push(x);
            }
        }
    }
}

// Function to add an edge to the graph (undirected)
void addEdge(vector<vector<int>>& adj,
                          int u, int v) 
{
    adj[u].push_back(v);
    adj[v].push_back(u); 
}

int main() 
{
    // Number of vertices in the graph
    int V = 5;

    // Adjacency list representation of the graph
    vector<vector<int>> adj(V);

    // Add edges to the graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 4);

    // Mark all the vertices as not visited
    vector<bool> visited(V, false);

    // Perform BFS traversal starting from vertex 0
    cout << "BFS starting from 0 : \n";
    bfs(adj, 0, visited);

    return 0;
}

// Applications - web crawling and network routing , finding shortest paths