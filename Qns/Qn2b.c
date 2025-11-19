#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 20;

struct Node{
    int id;
    struct Node* next;
};

struct Node* createNode(int id){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->id=id;
    newNode->next=NULL; 
}


struct Graph{
    int vertices;
    struct Node** adjList;
    int* visited;
};

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


void addEdge(struct Graph* graph, int src, int dest){
    struct Node* newNode=createNode(dest);
    newNode->next=graph->adjList[src];
    graph->adjList[src]=newNode;
}

void printGraph(struct Graph* graph){
    int vertices=graph->vertices;

    for(int i=0; i<vertices ; i++){
        printf("Vertex %d: ", i);
        struct Node* temp=graph->adjList[i];
        while(temp){
            printf("%d", temp->id);
            temp=temp->next;
        }
        printf("\n");
    }
}

void dfs(struct Graph* graph, int start){
    graph->visited[start]=1;
    printf(start);

    struct Node* temp=graph->adjList[start];

    while(temp){
        if(!graph->visited[temp->id]){
            dfs(graph, temp->id);
        }
        temp=temp->next;
    }
}



void bfs(struct Graph* graph, int start){
    for(int i=0;i<graph->vertices;i++){
        graph->visited[i]=0;
    }
    graph->visited[start]=1;

    int queue[100];
    int front=0;
    int rear=0;

    queue[rear++]=start;

    while(front!=rear){
        int vertex=queue[front++];
        printf("%d ", vertex);

        struct Node* temp=graph->adjList[vertex];
        while(temp){
            if(!graph->visited[temp->id]){
                queue[rear++]=temp->id;
                graph->visited[temp->id]=1;
            }
            temp=temp->next;
        }
    }
}
