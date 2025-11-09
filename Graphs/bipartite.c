#include <stdio.h>
#include <stdlib.h>

#define MAX 100

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
};

// ---------------- Graph Creation ----------------
struct Node* createNode(int vertex) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    return graph;
}

// ---------------- Add Edge ----------------
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src); // for undirected graph
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// ---------------- BFS Bipartite Check ----------------
int isBipartite(struct Graph* graph, int start) {
    int color[MAX];
    for (int i = 0; i < graph->vertices; i++)
        color[i] = -1; // -1 means uncolored

    int queue[MAX], front = 0, rear = 0;

    color[start] = 0;
    queue[rear++] = start;

    while (front != rear) {
        int u = queue[front++];

        struct Node* temp = graph->adjList[u];
        while (temp) {
            int v = temp->vertex;

            if (color[v] == -1) {
                // Assign alternate color to this adjacent vertex
                color[v] = 1 - color[u];
                queue[rear++] = v;
            } else if (color[v] == color[u]) {
                // Same color on adjacent vertices → not bipartite
                return 0;
            }

            temp = temp->next;
        }
    }

    return 1;
}

// ---------------- Main ----------------
int main() {
    int vertices, edges;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter %d edges (u v):\n", edges);
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    int bipartite = 1;
    // Check all components
    for (int i = 0; i < vertices; i++) {
        if (graph->adjList[i] != NULL) {
            if (!isBipartite(graph, i)) {
                bipartite = 0;
                break;
            }
        }
    }

    if (bipartite)
        printf("Graph is bipartite.\n");
    else
        printf("Graph is not bipartite.\n");

    return 0;
}
