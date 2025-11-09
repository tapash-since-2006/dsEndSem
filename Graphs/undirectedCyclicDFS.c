#include <stdio.h>
#include <stdlib.h>

struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
    int* visited;
};

// Create a new node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create a graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Add an undirected edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// DFS to detect cycle in undirected graph
int isCyclicUtil(struct Graph* graph, int v, int parent) {
    graph->visited[v] = 1;
    struct Node* temp = graph->adjList[v];

    while (temp) {
        if (!graph->visited[temp->vertex]) {
            if (isCyclicUtil(graph, temp->vertex, v))
                return 1;
        } else if (temp->vertex != parent) {
            return 1; // found a back edge
        }
        temp = temp->next;
    }
    return 0;
}

// Check for cycle
int isCyclic(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = 0;

    for (int i = 0; i < graph->vertices; i++) {
        if (!graph->visited[i]) {
            if (isCyclicUtil(graph, i, -1))
                return 1;
        }
    }
    return 0;
}

int main() {
    int vertices, edges;
    printf("Enter number of vertices: ");
    scanf("%d", &vertices);

    struct Graph* graph = createGraph(vertices);

    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    if (isCyclic(graph))
        printf("Graph contains a cycle\n");
    else
        printf("Graph does not contain a cycle\n");

    return 0;
}
