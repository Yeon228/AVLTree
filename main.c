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
void preOrder(node* p){
    if(p != NULL){
        printf("%d ",p->data);
        preOrder(p->leftChild);
        preOrder(p->rightChild);
    }
}

void postOrder(node* p){
    if(p != NULL){
        postOrder(p->leftChild);
        postOrder(p->rightChild);
        printf("%d ",p->data);
    }
}

void inOrder(node* p){
    if(p != NULL){
        inOrder(p->leftChild);
        printf("%d ",p->data);
        inOrder(p->rightChild);
    }
}
node* deletion(node* p, int val){
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
    else if(p != NULL && p->leftChild != NULL && p->rightChild != NULL && p->data == val){
        if(p->leftChild->rightChild != NULL){
            node* tempLeft = p->leftChild;
            if(tempLeft->rightChild != NULL){
                tempLeft = tempLeft->rightChild;
                temp = p;
                tempLeft->leftChild = p->leftChild;
                tempLeft->rightChild = p->rightChild;
                free(temp);
            }
        }
        else{
            temp = p;
            p->leftChild->rightChild = p->rightChild;
            p = p->leftChild;
            free(temp);
            return p;
        }

    }
    else{
        if(p != NULL && p->leftChild != NULL){
            p->leftChild = deletion(p->leftChild,val);
        }
        if(p != NULL && p->rightChild != NULL){
            p->rightChild = deletion(p->rightChild,val);
        }
    }
    return p;
}
void main(){
    setbuf(stdout, 0);
    node* root = NULL;
    int temp = 0;
    while (1) {
        printf("Select Option 1 : Insertion , 2 : Deletion , 3 : Traversal , ELSE : Exit\n");
        scanf("%d", &temp);
        if(temp == 1){
            printf("Input value : ");
            int val;
            scanf("%d", &val);
            printf("\n");
            root = add(root,val);
        }
        else if(temp == 2){
            printf("Delete value : ");
            int val;
            scanf("%d", &val);
            printf("\n");
            root = deletion(root,val);
        }
        else if(temp == 3){
            printf("Select Traversal Option 1 : preorder , 2 : inorder , 3 : postorder\n");
            int n;
            scanf("%d", &n);
            if(n == 1)preOrder(root);
            else if(n==2)inOrder(root);
            else if(n==3)postOrder(root);
        }
        else{
            printf("Exit....\n");
            break;
        }
    }
}
