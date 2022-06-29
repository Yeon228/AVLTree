#include <stdio.h>
#include <stdlib.h>
#include <d3dx9.h>

typedef struct node{
    int data;
    struct node* leftChild;
    struct node* rightChild;
}node;


node* LL(node * temp){
    node *newNode = temp->leftChild;
    if(temp->leftChild!=NULL){
        temp->leftChild = newNode->rightChild;
        newNode->rightChild = temp;
        return newNode;
    }
}
node* RR(node * temp){
    node *newNode = temp->rightChild;
    temp->rightChild = newNode->leftChild;
    newNode->leftChild = temp;
    return newNode;
}
node* RL(node * temp){
    node *newNode = temp->rightChild;
    temp->rightChild = LL(newNode);
    return RR(temp);
}
node* LR(node * temp){
    node *newNode = temp->leftChild;
    temp->leftChild = LL(newNode);
    return LL(temp);
}

int getHeight(node* p){
    int height = 0;
    if(p != NULL){
        height = getHeight(p->leftChild) > getHeight(p-> rightChild) ? getHeight(p->leftChild) : getHeight(p->rightChild);
        height++;
    }
    return height;
}
node* change(node * p){
    int left = getHeight(p->leftChild);
    int right = getHeight(p->rightChild);
    if(left - right > 1){
        if(getHeight(p->leftChild->leftChild) > 0){
            p = LL(p);
            return p;
        }
        else{
            p = LR(p);
            return p;
        }
    }
    if(left - right < -1){
        if(getHeight(p->rightChild->rightChild) > 0){
            p = RR(p);
            return p;
        }
        else{
            p = RL(p);
            return p;
        }
    }
    else return p;
}
node* add(node* p, int val){
    if(p == NULL){
        p = malloc(sizeof (node));
        p->data = val;
        p->leftChild = NULL;
        p->rightChild = NULL;
    }
    else if(p-> data < val){
        p->rightChild = add(p->rightChild,val);
        p = change(p);
    }
    else if(p-> data > val){
        p->leftChild = add(p->leftChild,val);
        p = change(p);
    }
    return p;
}
node* addBST(node* p, int val){
    if(p==NULL){
        p = malloc(sizeof(node));
        p->data = val;
        p->leftChild = NULL;
        p->rightChild = NULL;
    }else if(p->data < val){
        p->rightChild = addBST(p->rightChild,val);
    }else if(p->data > val){
        p->leftChild = addBST(p->leftChild,val);
    }
    return p;
}
void preOrder(node* p){
    if(p != NULL){
        printf("%d ",p->data);
        preOrder(p->leftChild);
        preOrder(p->rightChild);
    }
}
void deletion(node* p, int val){
    node* temp;
    if(p != NULL && p->leftChild !=NULL && val == p->leftChild->data){
        if(p->leftChild->leftChild != NULL){
            temp = p->leftChild->leftChild;
            free(p->leftChild);
            p->leftChild = temp;
        }
        else if(p->leftChild->rightChild != NULL){
            temp = p->leftChild->rightChild;
            free(p->rightChild);
            p->rightChild = temp;
        }
    }
    else if(p != NULL && p->rightChild != NULL && val == p->rightChild->data){
        if(p->rightChild->leftChild != NULL){
            temp = p->rightChild->leftChild;
            free(p->rightChild);
            p->rightChild = temp;
        }
        else if(p->rightChild->rightChild != NULL){
            temp = p->rightChild->rightChild;
            free(p->rightChild);
            p->rightChild = temp;
        }
    }
    else{
        if(p != NULL && p->leftChild != NULL){
            deletion(p->leftChild,val);
        }
        if(p != NULL && p->rightChild != NULL){
            deletion(p->rightChild,val);
        }
    }
}
void main(){
    node* root = NULL;
    node* BSTroot = NULL;
    printf("Insert node to AVL tree:\n");
    int count = 0;
    int temp = 0;
    while (1) {
        scanf("%d", &temp);
        count++;
        root = add(root, temp);
        BSTroot = addBST(BSTroot,temp);
        if (count == 9)break;
    }
    printf("\n\nPreorder traversal of the constructed AVL tree is\n");
    preOrder(BSTroot);
    deletion(root,10);
    printf("\nPreorder traversal after deletion of 10\n");
    preOrder(root);
}