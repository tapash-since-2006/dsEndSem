#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node* s1[100];
struct Node* s2[100];
int top1=-1, top2=-1;

struct Node{
    int id;
    char name[100];
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int id, char name[]){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->id=id;
    strcpy(newNode->name, name);
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}


struct Node* createTree(struct Node* root, int id, char name[]){

    if(root==NULL){
        return createNode(id, name);
    }

    if(id>root->id){
        root->right=createTree(root->right, id, name);
    }else if(id<root->id){
        root->left=createTree(root->left, id, name);
    }else{
        printf("Duplicate not allowed!!");
        return root;
    }

    return root;

}


struct Node* smallest(struct Node* root){
    struct Node* smallest=root;

    while(smallest->left!=NULL){
        smallest=smallest->left;
    }

    return smallest;
}

struct Node* largest(struct Node* root){
    struct Node* largest=root;

    while(largest->right!=NULL){
        largest=largest->right;
    }

    return largest;
}



struct Node* deleteNode(struct Node * root, int key){
    // finding the inorder successor and replacing it with that
    if(root==NULL){
        return NULL;
    }

    if(key>root->id){
        root->right=deleteNode(root->right, key);
    }else if(key<root->id){
        root->left=deleteNode(root->left, key);
    }else{
        if(root->left==NULL || root->right==NULL){
            struct Node* temp=root->left?root->left:root->right;
            free(root);
            return temp;
        }else{
            // finding the inorder successor
            struct Node* successor=smallest(root->right);
            root->id=successor->id;
            strcpy(root->name, successor->name);
            root->right=deleteNode(root->right, successor->id);
        }
    }
    return root;
}


void postOrderIterative(struct Node* root){
    if(root==NULL){
        return;
    }

    s1[++top1]=root;

    while(top1>=0){
        struct Node* temp=s1[top1--];
        s2[++top2]=temp;
        if(temp->left) s1[++top1]=temp->left;
        if(temp->right) s1[++top1]=temp->right;
    }

    while(top2>=0){
        printf("%d ", s2[top2--]->id);
    }
}


int main(){
    struct Node* root=NULL;
    // root=createTree(root, 101, "Tapash");
    // root=createTree(root, 102, "Sahil");
    // root=createTree(root, 81, "Rohan");
    // root=createTree(root, 99, "Eve");
    // root=createTree(root, 106, "Niranjan");

    for(int i=0;i<5;i++){
        printf("Enter the id and name: ");
        int id;
        char name[100];
        scanf("%d", &id);
        getchar();
        scanf("%[^\n]", name);
        root= createTree(root,id,name);
    }

    postOrderIterative(root);

    root=deleteNode(root, root->id);

    printf("\n");

    postOrderIterative(root);

    return 0;
}
