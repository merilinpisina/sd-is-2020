#ifndef GRAPH_DIRECTED_WEIGHTED
#define GRAPH_DIRECTED_WEIGHTED

#include <iostream>
#include <exception>
#include <queue>

struct GraphNode {
    int value, cost;
    GraphNode *next;

    GraphNode() = default;
    GraphNode(int value, int cost, GraphNode *next = nullptr) : value(value), cost(cost), next(next) {}
};

struct GraphEdge {
    int start, end, cost;
};

class Graph {
private:
    GraphNode* addNode(int value, int cost, GraphNode* head) {
        GraphNode *newNode = new (std::nothrow) GraphNode(value, cost, head);
        if (newNode == nullptr) {
            throw std::bad_alloc();
        }
        return newNode;
    }
    int numberOfNodes;
public:
    GraphNode **head;
    Graph(GraphEdge edges[], int numberOfEdges, int numberOfNodes) : numberOfNodes(numberOfNodes) {
        // allocate head
        head = new (std::nothrow) GraphNode*[numberOfNodes]();
        if (head == nullptr) {
            throw std::bad_alloc();
        }

        // initialize head pointers to null
        for (int i = 0; i < numberOfNodes; ++i)
            head[i] = nullptr;
        
        for (int i = 0; i < numberOfEdges; ++i) {
            // edges start at 1
            int start = edges[i].start, end = edges[i].end, cost = edges[i].cost;
            if (start > numberOfNodes || end > numberOfNodes || start <= 0 || end <= 0) {
                throw std::invalid_argument("invalid graph edge");
            }

            GraphNode *newNode = addNode(end, cost, head[start - 1]);
            head[start - 1] = newNode;
        }
    }

    int getNumberOfNodes() const {
        return numberOfNodes;
    }

    void BFS(int start) const {
        std::cout << "Print nodes: BF Traversal:" <<std::endl;
        bool *visited = new (std::nothrow) bool[numberOfNodes + 1];
        if (visited == nullptr) {
            throw std::bad_alloc();
        }

        for (int i = 0; i <= numberOfNodes; ++i) {
            visited[i] = false;
        }

        std::queue<int> q;
        visited[start] = true;
        q.push(start);
        while(!q.empty()) {
            start = q.front();
            std::cout << start << " ";
            q.pop();
            
            for(GraphNode *i = head[start - 1]; i != nullptr; i = i->next) {
                if (!visited[i->value]) {
                    visited[i->value] = true;
                    q.push(i->value);
                }
            }
        }
    }

    void DFShelper(int v, bool *visited) const {
        visited[v] = true;
        std::cout << v << " ";

        for(GraphNode *i = head[v - 1]; i != nullptr; i = i->next) {
            if (!visited[i->value]) {
                DFShelper(i->value, visited);
            }
        }
    }

    void DFS(int start) const {
        std::cout << "Print nodes: DF Traversal:" <<std::endl;
        bool *visited = new (std::nothrow) bool[numberOfNodes + 1];
        if (visited == nullptr) {
            throw std::bad_alloc();
        }

        DFShelper(start, visited);
    }

    ~Graph() {
        for (int i = 0; i < numberOfNodes; ++i) {
            delete[] head[i];
            delete[] head;
        }
    }
};

void display (GraphNode *root, int i) {
    while (root != nullptr) {
        std::cout << "(" << i + 1 << ", " << root->value << ", " << root->cost << ") ";
        root = root->next;
    }
    std::cout << std::endl;
}

#endif