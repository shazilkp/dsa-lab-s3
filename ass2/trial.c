#include <stdio.h>
#include <stdlib.h>

struct bst{
	struct bst* parent;
	int data;
	struct bst* left;
	struct bst* right;
};

typedef struct bst node;

node * maximum(node * root){
	node * x = root;
	while(x->right != NULL){
		x = x->right;
	}
	return x;
}
node * createNode(int data){
	node * x = (node *)malloc(sizeof(node));
	x->parent = NULL;
	x->left = NULL;
	x->right = NULL;
	x->data = data;
	return x;
}


node * predecessor(node * root, int data){
	node * x = root;
	while(x != NULL && x->data != data) {
		if(x->data >= data){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}
	if(x == NULL){
		return NULL;
	}
	if(x->left != NULL){
		return maximum(x->left);
	}
	else{
		node * pred = NULL;
		node * y = x;
		while(y->parent != NULL){
			if(y->parent->right == y){
				pred = y->parent;
				break;
			}
			y = y->parent;
		}
		if(pred == NULL){
			printf("no pred!!\n");
			return NULL;
		}
		return pred;	
	}
}
void insert(node ** root, int data){
	node * x = createNode(data);
	node * y = *root;
	node * para = NULL;
	if(*root == NULL){
		*root = x;
		return;
	}
	while(y != NULL){
		para = y;
		if(y->data >=  data){
			y = y->left;
		}
		else {
			y = y->right;
		}
	}
	if(para->data >= data){
		para->left = x;
	}
	else{
		para->right = x;
	}
	x->parent = para;
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
	if(root ==  NULL){
		return;
	}
	printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);

}

void convert(node * root){
	printf("%d ",root->data);
	
	if(root->left == NULL && root->right == NULL){
		return;
	}
	
	if(root->left != NULL){	
		printf("( ");
		convert(root->left);
		printf(") ");
	}
	else{
		printf("( ) ");
	
	}
	
	if(root->right != NULL){	
		printf("( ");
		convert(root->right);
		printf(") ");

	}
	else{
		printf("( ) ");

	}
}

void drawtree(node * root,int n,char label){
	if(root == NULL){
		return;
	}
	for(int i = 0 ; i < n ; i++){
		printf("    ");
	}
	printf("%d%c",root->data,label);
	printf("\n");
	printf("\n");
	drawtree(root->right,n+1,'R');
	drawtree(root->left,n+1,'L');
}

int main(){
	node * root = NULL;
	insert(&root,8);
	insert(&root,4);
	insert(&root,2);
	insert(&root,1);
	insert(&root,50);
	insert(&root,40);
    insert(&root,100);
	insert(&root,90);
	insert(&root,110);
	/*
	insert(&root,8);
	insert(&root,45);
	//inorder(root);
	node * pred;
	pred = predecessor(root,45);
	if(pred!=NULL)
		printf("\n%d",pred->data);
	*/
	printf("\n");
    drawtree(root,0,'H');
	convert(root);
	

}
