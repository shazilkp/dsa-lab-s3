#include <stdio.h>
#include <stdlib.h>

struct bst{
    int data;
    struct bst * l;
    struct bst * r;
    struct bst * parent;
};

typedef struct  bst node;

node * createNode(int data){
    node * x = (node *)malloc(sizeof(node));
    x->data = data;
    x->r = NULL;
    x->l = NULL;
    return x;
}

node * minimum(node * x){
    while(x->l){
        x=x->l;
    }
    return x;
}

node * insert(node * root,int data){
    if(!root){
        return createNode(data);
    }

    if(root->data >= data){
        root->l =  insert(root->l,data);
        if(root->l){
            root->l->parent = root;
        }
    }
    else{
        root->r = insert(root->r,data);
        if(root->r){
            root->r->parent = root;
        }
    }
    return root;
}

void transplant(node ** root,node ** x,node ** y){
    if((*x)->parent==NULL){
        *root = *y;
    }
    else {
            if((*x)->parent->l == *x){
                (*x)->parent->l = *y;
            }
            if((*x)->parent->r == *x)
                (*x)->parent->r = *y;
        }
    if(*y != NULL){
        (*y)->parent = (*x)->parent;
    }
}

void delete(node * root, node * x){
    if(x == NULL){
        return;
    }
    if(x->l == NULL){
        transplant(&root,&x,&(x->r));
    }
    else if(x->r == NULL){
        transplant(&root,&x,&(x->l));
    }
    else{
        node * y = minimum(x->r);
        if(y->parent != x){
            transplant(&root,&y,&(y->r));
            y->r = x->r;
            y->r->parent = y;
        }
        transplant(&root,&x,&y);
        y->l=x->l;
        y->l->parent = y;
    }
}

node * search(node * root, int data){
    if(root){
        if(root->data == data){
            return root;
        }
        if(root->data > data){
            return search(root->l,data);
        }
        else if(root->data < data){
            return search(root->r,data);
        }
    }
    
}

int search2(node * root, node * p){
    if(root){
        if(root == p){
            return 1;
        }
        if(root->data > p->data){
            return search2(root->l,p);
        }
        else if(root->data < p->data){
            return search2(root->r,p);
        }
    }
    return 0;
    
}

int exists(node* root, node * p, node * q){
    if(search2(root,p) && search2(root,q)){
        return 1;
    }
    else{
        return 0;
    }
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
	drawtree(root->r,n+1,'R');
	drawtree(root->l,n+1,'L');
}


node * commonAncestor(node * root,node * p, node * q){
    if(!root){
        return NULL;
    }
    if(!exists(root->l,p,q) && !exists(root->r,p,q)){
        return root;
    }
    else if(root->data < p->data){
        return commonAncestor(root->r,p,q);
    }
    else{
        return commonAncestor(root->l,p,q);
    }
}

int main(){
    node * root = NULL;
    root = insert(root,15);
    root = insert(root,89);
    root = insert(root,3);
    root = insert(root,36);
    root = insert(root,23);
    root = insert(root,53);
    root = insert(root,27);
    root = insert(root,9);
    root = insert(root,12);
    root = insert(root,1);
    
    drawtree(root,0,'H');

   // delete(root,search(root,36));
    //delete(root,search(root,3));
    //drawtree(root,0,'H');
    node * t = commonAncestor(root,search(root,9),search(root,12));
    printf("%d",t->data);

}