#include <iostream>
#include <climits>  // INT_MAX

using namespace std;

const int N = 7;
const int INF = INT_MAX;

struct Edge {
    int vertex; // Adjacent vertex (peak)
    int weight;
    Edge* next;

    Edge(int v, int w, Edge* n = nullptr) : vertex(v), weight(w), next(n) { }
};

// Array of pointers to adjacency lists for every vertex
Edge* adjList[N];

void deleteGraph() {
    for (int i = 0; i < N; i++) {
        Edge* current = adjList[i];
        while (current != nullptr) {
            Edge* nextEdge = current->next; // last one will --> to nullptr;
            delete current;
            current = nextEdge;
        }

        adjList[i] = nullptr;
    }
}

void addEdge(int u, int v, int weight) { // u -- start vertex
    // u --> v
    adjList[u] = new Edge(v, weight, adjList[u]); // Edge3 --> Edge2 --> Edge1
    // v --> u
    adjList[v] = new Edge(u, weight, adjList[v]); // same
}


int minKey(int key[], bool inMTS[]) {
    int min = INF;
    int minIndex = INF;

    for (int v = 0; v < N; v++) {
        if (!inMTS[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}


void primAlgorithm() {
    int parent[N];  // MST
    int key[N];  // min weight for every vertex
    bool inMST[N];
    int sum;

    // initialization
    for (int i = 0; i < N; i++) {
        key[i] = INF;
        inMST[i] = false;
    }

    key[0] = 0;
    parent[0] = -1; //first vertex -- root;

    for (int cnt = 0; cnt < N - 1; cnt++) {
        int u = minKey(key, inMST);
        inMST[u] = true;

        Edge* current = adjList[u];

        while (current != nullptr) {
            int v = current->vertex;
            int weight = current->weight;

            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
            }

            current = current->next;
        }

    }

    cout << "Edges of Minimum Spanning Tree (MST)" << endl;
    for (int i = 1; i < N; i++) {
        cout << char(parent[i] + 'A') << " - " << char(i + 'A') << " : " << key[i] << "\n";
        sum += key[i];
    }
    cout << "\nfinal sum: " << sum << endl;
}

  
int main() {
    for (int i = 0; i < N; i++) {
        adjList[i] = nullptr;
    }

   
    addEdge(0, 1, 3);  // A-B
    addEdge(0, 5, 2);  // A-F
    addEdge(1, 2, 3);  // B-C
    addEdge(1, 6, 6);  // B-G
    addEdge(2, 3, 3);  // C-D
    addEdge(2, 6, 1);  // C-G
    addEdge(3, 4, 5);  // D-E
    addEdge(4, 5, 4);  // E-F
    addEdge(4, 6, 2);  // E-G
    addEdge(5, 6, 5);  // F-G

   
    primAlgorithm();

   
    deleteGraph();

    return 0;
}