#include <stdio.h>
#include <stdlib.h>

#define MAX 50

// --------------------- Node & Graph Structures ---------------------
struct Node {
    int vertex;
    struct Node* next;
};

struct Graph {
    int vertices;
    struct Node** adjList;
    int* visited;
};

// --------------------- Helper Functions ---------------------
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

    // Undirected edge
    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

void printGraph(struct Graph* graph) {
    printf("\nAdjacency List Representation:\n");
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

// --------------------- DFS Implementation ---------------------
void DFS(struct Graph* graph, int vertex) {
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    struct Node* temp = graph->adjList[vertex];
    while (temp) {
        if (!graph->visited[temp->vertex])
            DFS(graph, temp->vertex);
        temp = temp->next;
    }
}

// --------------------- Count Components (DFS) ---------------------
int countComponents_DFS(struct Graph* graph) {
    int count = 0;
    for (int i = 0; i < graph->vertices; i++)
        graph->visited[i] = 0;

    for (int i = 0; i < graph->vertices; i++) {
        if (!graph->visited[i]) {
            count++;
            printf("\nComponent %d: ", count);
            DFS(graph, i);
        }
    }
    return count;
}

// --------------------- MAIN ---------------------
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

    printGraph(graph);

    // Count components and check connectivity
    int comp = countComponents_DFS(graph);

    printf("\n\nTotal connected components = %d\n", comp);
    if (comp == 1)
        printf("Graph is CONNECTED\n");
    else
        printf("Graph is NOT CONNECTED\n");

    return 0;
}


// #include <stdio.h>
// #include <stdlib.h>

// #define MAX 50

// // --------------------- Node & Graph Structures ---------------------
// struct Node {
//     int vertex;
//     struct Node* next;
// };

// struct Graph {
//     int vertices;
//     struct Node** adjList;
//     int* visited;
// };

// // --------------------- Helper Functions ---------------------
// struct Node* createNode(int v) {
//     struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
//     newNode->vertex = v;
//     newNode->next = NULL;
//     return newNode;
// }

// struct Graph* createGraph(int vertices) {
//     struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
//     graph->vertices = vertices;
//     graph->adjList = (struct Node**)malloc(vertices * sizeof(struct Node*));
//     graph->visited = (int*)malloc(vertices * sizeof(int));

//     for (int i = 0; i < vertices; i++) {
//         graph->adjList[i] = NULL;
//         graph->visited[i] = 0;
//     }
//     return graph;
// }

// void addEdge(struct Graph* graph, int src, int dest) {
//     struct Node* newNode = createNode(dest);
//     newNode->next = graph->adjList[src];
//     graph->adjList[src] = newNode;

//     // Undirected edge
//     newNode = createNode(src);
//     newNode->next = graph->adjList[dest];
//     graph->adjList[dest] = newNode;
// }

// void printGraph(struct Graph* graph) {
//     printf("\nAdjacency List Representation:\n");
//     for (int v = 0; v < graph->vertices; v++) {
//         struct Node* temp = graph->adjList[v];
//         printf("Vertex %d: ", v);
//         while (temp) {
//             printf("%d -> ", temp->vertex);
//             temp = temp->next;
//         }
//         printf("NULL\n");
//     }
// }

// // --------------------- DFS Implementation ---------------------
// void DFS(struct Graph* graph, int vertex) {
//     graph->visited[vertex] = 1;
//     printf("%d ", vertex);

//     struct Node* temp = graph->adjList[vertex];
//     while (temp) {
//         if (!graph->visited[temp->vertex])
//             DFS(graph, temp->vertex);
//         temp = temp->next;
//     }
// }

// // --------------------- BFS Implementation ---------------------
// void BFS(struct Graph* graph, int start) {
//     int queue[MAX], front = 0, rear = 0;

//     graph->visited[start] = 1;
//     queue[rear++] = start;

//     while (front != rear) {
//         int vertex = queue[front++];
//         printf("%d ", vertex);

//         struct Node* temp = graph->adjList[vertex];
//         while (temp) {
//             if (!graph->visited[temp->vertex]) {
//                 graph->visited[temp->vertex] = 1;
//                 queue[rear++] = temp->vertex;
//             }
//             temp = temp->next;
//         }
//     }
// }

// // --------------------- Connectedness (DFS-based) ---------------------
// int isConnected_DFS(struct Graph* graph) {
//     for (int i = 0; i < graph->vertices; i++)
//         graph->visited[i] = 0;

//     DFS(graph, 0);

//     for (int i = 0; i < graph->vertices; i++)
//         if (!graph->visited[i])
//             return 0;

//     return 1;
// }

// // --------------------- Connectedness (BFS-based) ---------------------
// int isConnected_BFS(struct Graph* graph) {
//     for (int i = 0; i < graph->vertices; i++)
//         graph->visited[i] = 0;

//     BFS(graph, 0);

//     for (int i = 0; i < graph->vertices; i++)
//         if (!graph->visited[i])
//             return 0;

//     return 1;
// }

// // --------------------- Count Components (DFS) ---------------------
// int countComponents_DFS(struct Graph* graph) {
//     int count = 0;
//     for (int i = 0; i < graph->vertices; i++)
//         graph->visited[i] = 0;

//     for (int i = 0; i < graph->vertices; i++) {
//         if (!graph->visited[i]) {
//             count++;
//             printf("\nComponent %d (DFS): ", count);
//             DFS(graph, i);
//         }
//     }
//     return count;
// }

// // --------------------- Count Components (BFS) ---------------------
// int countComponents_BFS(struct Graph* graph) {
//     int count = 0;
//     for (int i = 0; i < graph->vertices; i++)
//         graph->visited[i] = 0;

//     for (int i = 0; i < graph->vertices; i++) {
//         if (!graph->visited[i]) {
//             count++;
//             printf("\nComponent %d (BFS): ", count);
//             BFS(graph, i);
//         }
//     }
//     return count;
// }

// // --------------------- MAIN ---------------------
// int main() {
//     int vertices, edges;
//     printf("Enter number of vertices: ");
//     scanf("%d", &vertices);

//     struct Graph* graph = createGraph(vertices);

//     printf("Enter number of edges: ");
//     scanf("%d", &edges);

//     printf("Enter edges (u v):\n");
//     for (int i = 0; i < edges; i++) {
//         int u, v;
//         scanf("%d %d", &u, &v);
//         addEdge(graph, u, v);
//     }

//     printGraph(graph);

//     printf("\n\n--- Using DFS ---\n");
//     if (isConnected_DFS(graph))
//         printf("Graph is CONNECTED (DFS)\n");
//     else
//         printf("Graph is NOT CONNECTED (DFS)\n");

//     int compDFS = countComponents_DFS(graph);
//     printf("\nTotal connected components (DFS) = %d\n", compDFS);

//     printf("\n--- Using BFS ---\n");
//     if (isConnected_BFS(graph))
//         printf("Graph is CONNECTED (BFS)\n");
//     else
//         printf("Graph is NOT CONNECTED (BFS)\n");

//     int compBFS = countComponents_BFS(graph);
//     printf("\nTotal connected components (BFS) = %d\n", compBFS);

//     return 0;
// }
