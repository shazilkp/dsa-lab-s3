#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct bt{
	int data;
	struct bt* left;
	struct bt* right;
};

typedef struct bt node;


node * createNode(int data){
	node * x = (node *)malloc(sizeof(node));
	x->left = NULL;
	x->right = NULL;
	x->data = data;
	return x;
}

void drawtree(node * root,int n,char label){
	if(root == NULL){
		return;
	}
	for(int i = 0;i<n;i++){
		printf("    ");
	}
	printf("%d%c",root->data,label);
	printf("\n");
	printf("\n");
	drawtree(root->right,n+1,'R');
	drawtree(root->left,n+1,'L');
}

void inorder(node * root){
	if(root ==  NULL){
		return;
	}
	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);

}

void preorder(node * root){
	if(root == NULL){
		return;
	}
    printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);
	
}


node * insertRandom(node * root, int data){
    if(root == NULL){
        return createNode(data);
    }

    int l_or_r = rand() % 2;

    if(l_or_r == 0){
        root->left = insertRandom(root->left,data);
    }
    else{
        root->right = insertRandom(root->right,data);
    }

    return root;
}


node * generateRandomTree(int n,int arr[]){
    node * root = createNode(arr[0]);
    for(int i = 0; i < n-1; i++){
        insertRandom(root,arr[i+1]);
    }
    return root;
}

struct linkedlist{
	node * currNode;
	struct linkedlist* next;
	struct linkedlist* prev;
};

typedef struct linkedlist llnode; 

llnode * createQueueNode(node * currNode){
	llnode * x = (llnode *)malloc(sizeof(llnode));
	x->currNode = currNode;
	x->next = NULL;
	x->prev = NULL;
	return x;
}

void enqueue(llnode **head,llnode ** tail, node * currNode){
	llnode * node = createQueueNode(currNode);
	if(*tail && *head){
		(*tail)->next = node;
		*tail = (*tail)->next;
		//printf("%d ",(*tail)->currNode->data);
	}
	else{
		*head = *tail = node; 
	}
}

node * dequeue(llnode ** head){
	if(*head){
		node * dequeuedElement = (*head)->currNode;
		llnode * oldHead = *head;
		*head = (*head)->next;
		free(oldHead);
		return dequeuedElement;
	}
	return NULL;
}

int queueSize(llnode * head){
	llnode * x = head;
	int count = 0;
	while(x){
		count++;
		x=x->next;
	}
	return count;
}

void levelOrder(node * root){
	int ncl;
	llnode * head = createQueueNode(root);
	llnode * tail = head;

	while(head!= NULL){
		ncl = queueSize(head);
		while(ncl > 0){
			node * current = dequeue(&head);
			printf("%d ",current->data);
			if(current->left){
				enqueue(&head,&tail,current->left);
			}
			if(current->right){
				enqueue(&head,&tail,current->right);
			}
			ncl--;
		}
	}
}

int main(){

    srand(time(NULL));
    #define M 15
    #define N 15

    int in, im;

    im = 0;
    int vektor[M];
    for (in = 0; in < N && im < M; in++) {
    int rn = N - in;
    int rm = M - im;
    if (rand() % rn < rm)    
        /* Take it */
        vektor[im++] = in + 1; /* +1 since your range begins from 1 */
    }

    for(int i=0;i<M;i++){
        printf("%d ",vektor[i]);
    }
    printf("\n");

    node * root = generateRandomTree(M,vektor);
    inorder(root);
    printf("\n");
    preorder(root);
    printf("\n");
    
    //drawtree(root,0,'H');
}