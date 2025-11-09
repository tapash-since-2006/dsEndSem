#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// directed graph 

// intialize

struct Node{
    int vertex;
    struct Node* next;
};

struct Graph{
    int vertices;
    struct Node** adjList;
    int* visited;
};


// creation

struct Node* createNode(int vertex){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->vertex=vertex;
    newNode->next=NULL;
    return newNode;
}


struct Graph* createGraph(int vertices){
    struct Graph* graph=(struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices=vertices;
    graph->adjList=(struct Node**)malloc(vertices*sizeof(struct Node*));
    graph->visited=(int*)malloc(vertices*sizeof(int));
    for(int i=0;i<vertices;i++){
        graph->adjList[i]=NULL;
        graph->visited[i]=0;
    }

    return graph;
}


// adding an edge

void addEdge(struct Graph* graph, int src, int dest){
    struct Node* newNode=createNode(dest);
    newNode->next=graph->adjList[src];
    graph->adjList[src]=newNode;
}


// printing the adj list
void printAdjList(struct Graph* graph){
    for(int i=0;i<graph->vertices;i++){
        struct Node* temp=graph->adjList[i];
        printf("Vertex %d: ", i);
        while(temp){
            printf("%d -> ", temp->vertex);
            temp=temp->next;
        }
        printf("NULL\n");
    }
}

// taking the graph as input and than calling the fucntion for creating the edge here
void inputListGraph(struct Graph* graph){
    int edges;
    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    printf("Enter %d edges (u,v): \n", edges);
    for(int i=0;i<edges;i++){
        int u,v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    printAdjList(graph);
}





// DFS traversals

void dfsRec(struct Graph* graph, int vertex){
    graph->visited[vertex]=1;
    printf("%d ", vertex);

    struct Node* temp=graph->adjList[vertex];

    while(temp){
        if(!graph->visited[temp->vertex]){
            dfsRec(graph, temp->vertex);
        }
        temp=temp->next;
    }
}


// BFS traversal 

void bfsIter(struct Graph* graph, int vertex){
    int queue[MAX];
    int front=0;
    int rear=0;

    graph->visited[vertex]=1;
    queue[rear++]=vertex;

    while(front!=rear){
        int vertex=queue[front++];
        printf("%d ", vertex);

        struct Node* temp=graph->adjList[vertex];
        while(temp!=NULL){
            if(!graph->visited[temp->vertex]){
                queue[rear++]=temp->vertex;
                graph->visited[temp->vertex]=1;
            }
            temp=temp->next;
        }
    }
}



// connected or not and the number of block

int connected(struct Graph* graph){
    int count=0;

    for(int i=0; i<graph->vertices;i++){
        graph->visited[i]=0;
    }

    for(int i=0;i<graph->vertices;i++){
        if(!graph->visited[i]){
            count++;
            printf("Component %d of Graph: ", count);
            dfsRec(graph, i);
        }
    }

    return count;
}




int main(){
    int vertices, start;
    printf("Enter the number of vertices: ");
    scanf("%d", &vertices);
    
    struct Graph* graph=createGraph(vertices);
    inputListGraph(graph);

    printf("\nEnter the starting index for the treaversal");
    scanf("%d", &start);

    for(int i = 0; i < vertices; i++){
        graph->visited[i] = 0; // to ensure that visited is 0
    }

    printf("\n DFS traversal of the graph: ");
    dfsRec(graph, start);

    for(int i = 0; i < vertices; i++){
        graph->visited[i] = 0; // to ensure that visited is 0
    }


    printf("\n BFS traversal of the graph: ");
    bfsIter(graph, start);


    return 0;
}

