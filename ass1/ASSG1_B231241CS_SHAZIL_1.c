#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct bt{
	int data;
	struct bt* left;
	struct bt* right;
};

typedef struct bt node;

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

void enqueueBack(llnode **head,llnode ** tail, node * currNode){
	llnode * node = createQueueNode(currNode);
	if(*tail && *head){
		(*tail)->next = node;
		node->prev = *tail;
		*tail = (*tail)->next;
		//printf("%d ",(*tail)->currNode->data);
	}
	else{
		*head = *tail = node; 
	}
}

void enqueueFront(llnode **head,llnode ** tail, node * currNode){
	llnode * node = createQueueNode(currNode);
	if(*tail && *head){
		node->next = *head;
		(*head)->prev = node;
		*head = (*head)->prev; 
		//printf("%d ",(*tail)->currNode->data);
	}
	else{
		*head = *tail = node; 
	}
}

node * dequeueFront(llnode ** head,llnode ** tail){
	if(*head){
		node * dequeuedElement = (*head)->currNode;
		llnode * oldHead = *head;
		*head = (*head)->next;
		if(*head == NULL){
			*tail = NULL;
		}
		else{
			(*head)->prev = NULL;
		}
		free(oldHead);
		return dequeuedElement;
	}
	return NULL;
}

node * dequeueBack(llnode ** head, llnode ** tail){
	if(*tail){
		node * dequeuedElement = (*tail)->currNode;
		llnode * oldtail = *tail;
		*tail = (*tail)->prev;
		if(*tail == NULL){
			*head = NULL; 
		}
		else{
			(*tail)->next = NULL;

		}
		free(oldtail);
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


node * createNode(int data){
	node * x = (node *)malloc(sizeof(node));
	x->left = NULL;
	x->right = NULL;
	x->data = data;
	return x;
}

node * constructTree(int inorder[],int preorder[],int *preorderIndex, int inorderStart, int inorderEnd){
	if(inorderStart > inorderEnd){
		return NULL;								//no node
	}

	node * x = createNode(preorder[(*preorderIndex)++]);

	if(inorderStart == inorderEnd){					//no children
		return x;
	}

	int index;
	for(index = inorderStart ; index <= inorderEnd ; index++){			//find the index(in the inorder) of the element to be inserted
		if(x->data == inorder[index]){
			break;
		}
	}

	x->left = constructTree(inorder,preorder,preorderIndex,inorderStart,index-1);
	x->right = constructTree(inorder,preorder,preorderIndex,index+1,inorderEnd);

	return x;
}


void printqueue(llnode * head){
	llnode * x = head;
	while(x){
		printf("%d ",x->currNode->data);
		x=x->next;
	}
}

void ZIG_ZAG(node * root){
	int no_node_curr_level;
	llnode * head = createQueueNode(root);
	llnode * tail = head;
	node * current;
	int flag = 0;
	while(head){
		flag = !flag;
		no_node_curr_level = queueSize(head);
		while(no_node_curr_level > 0){
			if(!flag){
				current = dequeueFront(&head,&tail);
				if(current->left){
					enqueueBack(&head,&tail,current->left);
				}
				if(current->right){
					enqueueBack(&head,&tail,current->right);
				}
			}
			if(flag){
				current = dequeueBack(&head,&tail);
				if(current->right){
					enqueueFront(&head,&tail,current->right);
				}
				if(current->left){
					enqueueFront(&head,&tail,current->left);
				}
			}
			printf("%d ",current->data);
			no_node_curr_level--;
		}

	}
}

int maxQueue(llnode * head){
	llnode * x = head;
	int max = -1;
	while(x){
		if(x->currNode->data > max){
			max = x->currNode->data;
		}
		x=x->next;
	}
	return max;
}

void LevelMax(node * root){
	int no_node_curr_level;
	llnode * head = createQueueNode(root);
	llnode * tail = head;

	while(head){
		printf("%d ",maxQueue(head));
		no_node_curr_level = queueSize(head);
		while(no_node_curr_level > 0){
			node * current = dequeueFront(&head,&tail);
			if(current->left){
				enqueueBack(&head,&tail,current->left);
			}
			if(current->right){
				enqueueBack(&head,&tail,current->right);
			}
			no_node_curr_level--;
		}
	}
}

void PostOrder(node * root){
	if(root == NULL){
		return;
	}
	PostOrder(root->left);
	PostOrder(root->right);
	printf("%d ",root->data);
}


int maxDepth(node * root){
	if(root == NULL){
		return 0;
	}
	int right_depth = maxDepth(root->right);
	int left_depth = maxDepth(root->left);

	return (right_depth > left_depth ? right_depth : left_depth) + 1;		//largest of 2 + 1
}


/*
void printLevel(node * root, int level,int even){
	if(root == NULL){
		return;
	}

	if(level == 0){
		printf("%d ",root->data);
		return;
	}
	if(even){
		printLevel(root->right,level-1,even);
		printLevel(root->left,level-1,even);
	}
	else{
		printLevel(root->left,level-1,even);
		printLevel(root->right,level-1,even);
	}
}

void ZIG_ZAG2(node * root){
	int depth = maxDepth(root);
	int even = 1;
	for(int i = 0; i < depth ; i++){
		printLevel(root,i,even);
		even = !even;
	}
}

*/

int RightLeafSum(node * root){

	if(root == NULL){				//base case
		return 0;
	}

	if(root->right){
		if(root->right->right == NULL && root->right->left == NULL){					//if right leaf add to sum
				int t = root->right->data + RightLeafSum(root->left) ;
				return t;
		}
	}

	int leftsum = RightLeafSum(root->left);
	int rightsum = RightLeafSum(root->right);
	return leftsum+rightsum;

}

int Diameter(node * root){
	if(root == NULL){
		return 0;
	}
	int d_left = Diameter(root->left);
	int d_right = Diameter(root->right);

	int longestPathRoot = maxDepth(root->left) + maxDepth(root->right) + 1;			//longest path with the current node as root ie current subtree

	return d_left > d_right ? (d_left > longestPathRoot ? d_left : longestPathRoot) : (d_right > longestPathRoot ? d_right : longestPathRoot); //largest of the 3
}

int main(){
	int n;
	scanf("%d",&n);
	int inorder[n];
	int preorder[n];
	
	int preorderIndex = 0;
	for(int i = 0 ; i < n ; i++){
		scanf("%d",&inorder[i]);
	}
	
	for(int i = 0 ; i < n ; i++){
		scanf("%d",&preorder[i]);
	}

	node * root = constructTree(inorder,preorder,&preorderIndex,0,n-1);

	char c;
	while(1){
	scanf("%c",&c);
	if(c == 'e'){
		break;
	}
	switch(c){
		case 'p':{
				PostOrder(root);
				printf("\n");
				break;
				}
		case 'z':{
				ZIG_ZAG(root);
				printf("\n");
				break;
				}
		case 'm':{
				LevelMax(root);
				printf("\n");
				break;
				}
		case 'd':{
				int dia = Diameter(root);
				printf("%d\n",dia);
				break;
				}
		case 's':{
				int sum = RightLeafSum(root);
				printf("%d\n",sum);
				break;
				}
		default:break;
	}
	}
	
}
