#include <stdio.h>
#include <stdlib.h>

#define MAX 20

// ---------------- NODE & GRAPH STRUCTURES ----------------
struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
    int* visited;
};

// ---------------- GRAPH CREATION ----------------
struct Node* createNode(int v) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

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

void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->vertices; v++) {
        struct Node* temp = graph->adjList[v];
        printf("Vertex %d: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

// ---------------- RECURSIVE DFS ----------------
void DFS_Recursive(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp) {
        if (!graph->visited[temp->vertex]){
            DFS_Recursive(graph, temp->vertex);
        }
        temp = temp->next;
    }
}

// ---------------- ITERATIVE DFS ----------------
void DFS_Iterative(struct Graph* graph, int start) {
    int stack[MAX], top = -1;
    int visited[MAX] = {0};

    stack[++top] = start;
    visited[start] = 1;

    while (top != -1) {
        int vertex = stack[top--];
        printf("%d ", vertex);

        struct Node* temp = graph->adjList[vertex];
        while (temp) {
            if (!visited[temp->vertex]) {
                stack[++top] = temp->vertex;
                visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// ---------------- ITERATIVE BFS ----------------
void BFS_Iterative(struct Graph* graph, int start) {
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    visited[start] = 1;
    queue[rear++] = start;

    while (front != rear) {
        int vertex = queue[front++];
        printf("%d ", vertex);

        struct Node* temp = graph->adjList[vertex];
        while (temp) {
            if (!visited[temp->vertex]) {
                queue[rear++] = temp->vertex;
                visited[temp->vertex] = 1;
            }
            temp = temp->next;
        }
    }
}

// ---------------- RECURSIVE BFS ----------------
// helper function for recursive BFS
void BFS_Recursive_Helper(struct Graph* graph, int queue[], int* front, int* rear, int visited[]) {
    if (*front == *rear)
        return;

    int vertex = queue[(*front)++];
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp) {
        if (!visited[temp->vertex]) {
            queue[(*rear)++] = temp->vertex;
            visited[temp->vertex] = 1;
        }
        temp = temp->next;
    }

    BFS_Recursive_Helper(graph, queue, front, rear, visited);
}

void BFS_Recursive(struct Graph* graph, int start) {
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    queue[rear++] = start;
    visited[start] = 1;

    BFS_Recursive_Helper(graph, queue, &front, &rear, visited);
}

// ---------------- MAIN ----------------
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

    printf("\nAdjacency List:\n");
    printGraph(graph);

    printf("\nDFS (Recursive): ");
    for (int i = 0; i < vertices; i++) graph->visited[i] = 0;
    DFS_Recursive(graph, 0);

    printf("\nDFS (Iterative): ");
    DFS_Iterative(graph, 0);

    printf("\nBFS (Iterative): ");
    BFS_Iterative(graph, 0);

    printf("\nBFS (Recursive): ");
    BFS_Recursive(graph, 0);

    printf("\n");
    return 0;
}
