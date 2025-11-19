#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    char data[100];
    struct Node* left;
    struct Node* right;   
};

struct Node* createNode(char data[]){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->left=NULL;
    newNode->right=NULL;

    strcpy(newNode->data, data);

    return newNode;
}

// struct Node* createTree(char data[]){
//     if(strcmp(data,"-1")==0){
//         return NULL;
//     }

//     struct Node* curr=createNode(data);
    
//     char leftData[100];
//     char rightData[100];

//     printf("Enter the left side for %s (-1 for NONE): ", data);
//     getchar();
//     scanf("%[^\n]", leftData);
//     curr->left=createTree(leftData);

//     printf("Enter the right child for %s (-1 for NONE): ", data);
//     getchar();
//     scanf("%[^\n]", rightData);
//     curr->right=createTree(rightData);

//     return curr;

// }




// level order tree input taking
struct Node* createTree(){
    char data[100];
    printf("Enter the root node:(-1 for NONE): ");
    scanf("%[^\n]", data);
    if(strcmp(data, "-1")==0){
        return NULL;
    }

    struct Node* root=createNode(data);

    struct Node* arr[100];
    int front=0;
    int rear=0;

    arr[rear++]=root;

    while(front!=rear){
        struct Node* curr=arr[front++];

        char leftData[100];
        char rightData[100];

        printf("Enter the left child of %s :(-1 for NONE): ", curr->data);
        getchar();
        scanf("%[^\n]", leftData);
        if(strcmp(leftData, "-1")!=0){
            curr->left=createNode(leftData);
            arr[rear++]=curr->left;
        }

        printf("Enter the right child of %s :(-1 for NONE): ", curr->data);
        getchar();
        scanf("%[^\n]", rightData);
        if(strcmp(rightData, "-1")!=0){
            curr->right=createNode(rightData);
            arr[rear++]=curr->right;
        }
    }

    return root;
}



void preorderIter(struct Node* root){
    if(root==NULL){
        return;
    }

    struct Node* stack[100];
    int top=-1;

    stack[++top]=root;

    while(top!=-1){
        struct Node* curr=stack[top--];
        printf("%s ", curr->data);
        if(curr->right) stack[++top]=curr->right;
        if(curr->left) stack[++top]=curr->left;
    }
}



// finding the deptbh
int findDepth(struct Node* root, char data[], int currDepth){ // depth of a tree==height of a tree

    if(root==NULL){
        return -1;
    }

    if(strcmp(root->data, data)==0){
        return currDepth;
    }

    int left=findDepth(root->left, data, 1+currDepth);
    if(left!=-1){
        return left;
    }

    int right=findDepth(root->right, data, 1+currDepth);
    return right;

}






int main(){
    struct Node* root;
    root=createTree();
    preorderIter(root);
    printf("The deptht of the tree is : %d", findDepth(root, root->data, 0));
    return 0;
}





// void inorder(struct Node* root){
//     if(!root){
//         return;
//     }

//     inorder(root->left);
//     printf("%s", root->data);
//     inorder(root->right);
// }



// int main(){
//     printf("Enter the root node: ");
//     char data[100];
//     struct Node* root;
//     scanf("%[^\n]", data);
//     root=createTree(data);
//     inorder(root);
//     return 0;
// }
