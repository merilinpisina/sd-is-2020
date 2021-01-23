#include "graph.h"

#include <set>
#include <algorithm>
#include <cassert>
#include <list>

const int MAX_DIST = 999999;

void displaySinglePath(int start, int *prev, int current) {
    // std::cout << start << " to " <<current <<std::endl;
    if (current == start) {
        return;
    }
    displaySinglePath(start, prev, prev[current - 1] + 1);
    std::cout << current << " -> ";
}

void displayPaths(int start, int *prev, int numberOfNodes) {
    for (int i = 0; i < numberOfNodes; ++i) {
        std::cout << start << " -> ";
        displaySinglePath(start, prev, i + 1);
        std::cout << std::endl;
    }
}

// display all (shortest) path lengths
void dijkstra(Graph g, int *dist, int *prev, int start) {
    int n = g.getNumberOfNodes();
    for (int i = 0; i < n; ++i) {
        dist[i] = MAX_DIST;
        prev[i] = -1;
    }

    dist[start - 1] = 0; // distance of start node
    std::set<int> s; // create an empty set of nodes
    std::list<int> q; // create an empty list to hold adjacent nodes

    for (int i = 0; i < n; ++i) {
        q.push_back(i); // add each node into the list
    }

    while (!q.empty()) {
        std::list<int>::iterator i = min_element(q.begin(), q.end());
        int current = *i;
        q.remove(current);
        s.insert(current);
        for (GraphNode* it = g.head[current]; it!=nullptr; it = it->next) {
            // std::cout << "current -> next" << " " << current + 1 << " -> " << it->value << std::endl;
            if (dist[current]+it->cost < dist[it->value - 1]) {
                dist[it->value - 1] = dist[current]+it->cost;
                prev[it->value - 1] = current;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (dist[i] == MAX_DIST) {
            std::cout << start << " -> " << i + 1 << " " << "path doesn't exist" <<std::endl;
        }
        else {
            std::cout << start << " -> " << i + 1 << " " << dist[i] <<std::endl;
        }
    }
    displayPaths(start, prev, n);
}

void testGraph() {
    GraphEdge edges[] = {
        // (x, y, c) -> edge from x to y with cost c
        {1, 2, 2}, 
        {1, 3, 4}, 
        {2, 5, 3}, 
        {3, 4, 2}, 
        {4, 2, 4}, 
        {5, 4, 3}
    };

    int numberOfNodes = 6;
    int numberOfEdges = sizeof(edges) / sizeof(edges[0]);
    try {
        Graph graph(edges, numberOfEdges, numberOfNodes);
        std::cout << "Graph display:\n" << "(start, end, cost)\n";
        for (int i = 0; i < numberOfNodes; ++i) {
            display(graph.head[i], i);
        }
        
        assert(numberOfNodes == graph.getNumberOfNodes());

        int start = 1;
        int *dist = new (std::nothrow) int[graph.getNumberOfNodes()],
            *prev = new (std::nothrow) int[graph.getNumberOfNodes()];
        if (dist == nullptr || prev == nullptr) {
            std::cout << "Could not allocate dist or prev" << std::endl;
            return;
        }

        dijkstra(graph, dist, prev, start);
        std::cout << std::endl;
        graph.BFS(1);
        std::cout << std::endl;
        graph.DFS(1);
    } catch (std::exception e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
    }
}

int main() {
    testGraph();
    return 0;
}