#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


struct Node{
    char item;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(char c){
    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));
    newNode->item=c;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}


struct Node* createTree(char data){

    if(data=='-1'){
        return NULL;
    }

    struct Node* root=createNode(data);

    char l;
    char r;

    printf("Enter the left child of %c (-1 for NONE)", root->item);
    scanf("%c", l);
    root->left=createTree(l);

    printf("Enter the right child of %c (-1 for NONE)", root->item);
    scanf("%c", r);
    root->right=createTree(r);


    return root;

}



// helper to find the node with a particualr key which is useful
struct Node* findNode(struct Node* root, char key){
    if(root==NULL){
        return NULL;
    }

    if(root->item==key){
        return root;
    }

    struct Node* left=findNode(root->left, key);
    if(left!=NULL){
        return left;
    }

    return findNode(root->right, key);
}


// all kind of the relationship

// important


int ancestorsAll(struct Node* root, char target){
    if(root==NULL){
        return 0;
    }

    if(root->item==target){
        return 1;
    }

    if(ancestorsAll(root->left, target) || ancestorsAll(root->right, target)){
        printf("%c ", root->item);
        return 1;
    }

    return 0;
}

char ancestorOrParent(struct Node* root, char parent, char target){
    if(root==NULL){
        return '\0';
    }

    if(root->item==target){
        return parent;
    }

    char left=ancestorOrParent(root->left, root->item, target);
    if(left!='\0'){
        return left;
    }

    char right=ancestorOrParent(root->right, root->item, target);
    return right;
}


// int findParent(struct Node* root, int key){
//     if(root==NULL){
//         return -1;
//     }

//     if(root->left && root->left->item==key){
//         return root->item;
//     }

//     if(root->right && root->right->item==key){
//         return root->item;
//     }

//     int left=findParent(root->left, key);
//     if(left!=-1){
//         return left;
//     }
//     return findParent(root->right, key);
// }



void siblings(struct Node* root, char key){
    if(root==NULL){
        return;
    }

    if(root->left && root->left->item==key && root->right){
        printf("%c ", root->right->item);
        return;
    }

    if(root->right && root->right->item==key && root->left){
        printf("%c ", root->left->item);
        return;
    }

    siblings(root->left, key);
    siblings(root->right, key);
}

void offspring(struct Node* root, char key){
    struct Node* node=findNode(root, key);
    if(node==NULL){
        return;
    }

    if(node->left){
        printf("%c ", node->left->item);
    }
    if(node->right){
        printf("%c ", node->right->item);
    }
}

void descendants(struct Node* node){
    if(node==NULL){
        return; 
    }
    preorder(node->left);
    preorder(node->right);
}
