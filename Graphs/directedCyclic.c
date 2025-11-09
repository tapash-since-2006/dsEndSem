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
    int* recStack;
};

// Create node
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Create graph
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
    graph->visited = (int*)malloc(vertices * sizeof(int));
    graph->recStack = (int*)malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
        graph->recStack[i] = 0;
    }

    return graph;
}

// Add directed edge
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

// DFS with recursion stack to detect cycle
int isCyclicUtil(struct Graph* graph, int v) {
    if (!graph->visited[v]) {
        graph->visited[v] = 1;
        graph->recStack[v] = 1;

        struct Node* temp = graph->adjList[v];
        while (temp) {
            int w = temp->vertex;
            if (!graph->visited[w] && isCyclicUtil(graph, w))
                return 1;
            else if (graph->recStack[w])
                return 1;
            temp = temp->next;
        }   
    }
    graph->recStack[v] = 0;
    return 0;
}

// Check cycle in directed graph
int isCyclic(struct Graph* graph) {
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = graph->recStack[i] = 0;

    for (int i = 0; i < graph->vertices; i++)
        if (isCyclicUtil(graph, i))
            return 1;

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
