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
};

// ---------------- GRAPH CREATION ----------------
struct Node* createNode(int v) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    graph->adjList = malloc(vertices * sizeof(struct Node*));
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    return graph;
}

// ---------------- ADD EDGE ----------------
void addEdge(struct Graph* graph, int src, int dest, int directed) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    if (!directed) {
        newNode = createNode(src);
        newNode->next = graph->adjList[dest];
        graph->adjList[dest] = newNode;
    }
}

// ---------------- PRINT FUNCTIONS ----------------
void printAdjList(struct Graph* graph) {
    printf("\nAdjacency List:\n");
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

void printMatrix(int matrix[MAX][MAX], int vertices) {
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// ---------------- INPUT FUNCTIONS ----------------
void inputMatrix(int matrix[MAX][MAX], int* vertices, int directed) {
    int edges;
    printf("Enter number of vertices: ");
    scanf("%d", vertices);

    printf("Enter number of edges for matrix form: ");
    scanf("%d", &edges);

    printf("Enter %d edges (u v):\n", edges);
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        matrix[u][v] = 1;
        if (!directed) matrix[v][u] = 1;
    }

    printMatrix(matrix, *vertices);
}

void inputListGraph(struct Graph* graph, int directed) {
    int edges;
    printf("\nEnter number of edges for list form: ");
    scanf("%d", &edges);
    printf("Enter %d edges (u v):\n", edges);

    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v, directed);
    }
    printAdjList(graph);
}

// ---------------- CONVERSION FUNCTIONS ----------------
struct Graph* matrixToList(int matrix[MAX][MAX], int vertices, int directed) {
    struct Graph* graph = createGraph(vertices);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (matrix[i][j] == 1) {
                addEdge(graph, i, j, directed);
                if (!directed) matrix[j][i] = 0; // avoid duplication for undirected
            }
        }
    }
    return graph;
}

void listToMatrix(struct Graph* graph, int matrix[MAX][MAX]) {
    for (int i = 0; i < graph->vertices; i++) {
        struct Node* temp = graph->adjList[i];
        while (temp) {
            matrix[i][temp->vertex] = 1;
            temp = temp->next;
        }
    }
}

// ---------------- MAIN ----------------
int main() {
    int vertices;
    int matrix[MAX][MAX] = {0};
    int directed;

    printf("Is the graph directed? (1 = yes, 0 = no): ");
    scanf("%d", &directed);

    // Matrix input
    inputMatrix(matrix, &vertices, directed);

    // List input
    struct Graph* listGraph = createGraph(vertices);
    inputListGraph(listGraph, directed);

    // Matrix → List conversion
    struct Graph* convertedList = matrixToList(matrix, vertices, directed);
    printf("\nConverted (Matrix → List):");
    printAdjList(convertedList);

    // List → Matrix conversion
    int convertedMatrix[MAX][MAX] = {0};
    listToMatrix(listGraph, convertedMatrix);
    printf("\nConverted (List → Matrix):");
    printMatrix(convertedMatrix, vertices);

    return 0;
}
