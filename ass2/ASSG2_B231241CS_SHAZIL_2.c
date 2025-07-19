#include <stdio.h>
#include <stdlib.h>

struct avl{
    int key;
    int value;
    struct avl* left;
    struct avl* right;
    int h;
};

typedef struct avl node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

void printnode(node * x){
    if(!x){
        return;
    }
    printf("%d %d\n",x->key,x->value);
}

node * createNode(int key,int value){
	node * x = (node *)malloc(sizeof(node));
	x->left = NULL;
	x->right = NULL;
    x->h = 0;
	x->key = key;
    x->value = value;
	return x;
}

int height(node * root){
    if(!root){
        return -1;
    }
    return root->h;
}

int bal_fact(node * root){
    if(!root){
        return 0;
    }
    return height(root->left) - height(root->right);
}

int isBalanced(node * root){
    int b_fact = bal_fact(root);
    if(b_fact == 0 || b_fact == -1 || b_fact == 1){
        return 1;
    }
    else{
        return 0;
    }
}

int update_H(node * root){
    return 1 + max(height(root->left),height(root->right));
}

node * r_rotate(node * z){
    node * y = z->left;
    node * t = y->right;
    y->right = z;
    z->left = t;
    z->h = update_H(z);
    y->h = update_H(y);
    return y;
}

node * l_rotate(node * z){
    node * y = z->right;
    node * t = y->left;
    y->left = z;
    z->right = t;
    z->h = update_H(z);
    y->h = update_H(y);
    return y;
}

node * Insert(node * root, int key,int value){
    if(root == NULL){
        return createNode(key,value);
    }

    if(key == root->key){
        root->value = value;
        return root;
    }
    else if(key > root->key){
        root->right = Insert(root->right,key,value);
    }
    else{
        root->left = Insert(root->left,key,value);
    }

    root->h = update_H(root);
    if(!isBalanced(root)){
        if(key > root->key){
            if(key > root->right->key){               //RR
                return l_rotate(root);
            }
            else{                                       //RL    
                root->right = r_rotate(root->right);
                return l_rotate(root);
            }
        }
        if(key <= root->key){
            if(key < root->left->key){               //LL
                return r_rotate(root);
            }
            else{                                       //LR    
                root->left = l_rotate(root->left);
                return r_rotate(root);
            }
        }
    }
    return root;
}

void upperBound(node * root,int key){         //element if it exists or its inorder successor
    node * x = root;
    node * succ = NULL;
    while(x != NULL){
        if(key == x->key){
            break;
        }
        if(key > x->key){
            x=x->right;
        }
        else if(key < x->key){
            succ = x;
            x=x->left;
        }
    }
    
    if(x){
        printnode(x);
        return;
    }
    if(succ){
        printnode(succ);
        return;
    }
    printf("-1\n");
    
    return;
}

void Find(node * root,int key){
    node * x = root;
    while(x != NULL){
        if(key == x->key){
            break;
        }
        if(key > x->key){
            x=x->right;
        }
        else if(key < x->key){
            x=x->left;
        }
    }
    if(!x){
        printf("-1\n");
        return;
    }
    if(x){
        printnode(x);
        return;
    }
}

void Size(node * root,int * size){
    if(!root){
        return;
    }
    (*size)++;
    if(root->left){
        Size(root->left,size);
    }
    if(root->right){
        Size(root->right,size);
    }
}

int Empty(node * root){
    if(!root){
        return 1;
    }
    if(root){
        return 0;
    }
}

void DisplayElements(node * root){
    if(!root){
        return;
    }
    DisplayElements(root->right);
    printf("%d ",root->key);
    DisplayElements(root->left);
}

void drawtree(node * root,int n,char label){
	if(root == NULL){
		return;
	}
	for(int i = 0 ; i < n ; i++){
		printf("    ");
	}
	printf("%d%c(%d)",root->key,label,root->h);
	printf("\n");
	printf("\n");
	drawtree(root->right,n+1,'R');
	drawtree(root->left,n+1,'L');
}

int main(){
    node * root = NULL;
    char c;
    int key,value;
    while(1){
        scanf("%c",&c);
        if(c == 't'){
            break;
        }
        switch(c){
            case 'i':{
                scanf("%d %d",&key,&value);
                root = Insert(root,key,value);
                break;
            }

            case 'u':{
                scanf("%d",&key);
                upperBound(root,key);
                break;
            }

            case 'f':{
                scanf("%d",&key);
                Find(root,key);
                break;
            }

            case 's':{
                int s=0;
                Size(root,&s);
                printf("%d\n",s);
                break;
            }

            case 'e':{
                printf("%d\n",Empty(root));
                break;
            }

            case 'd':{
                if(Empty(root)){
                    printf("-1\n");
                }
                else{
                    DisplayElements(root);
                    printf("\n");
                }
                break;
            }

            case 'c':{
                drawtree(root,0,'H');
                break;
            }

            default:break;
        }
    }
}