#include <stdio.h>
#include <stdlib.h>

static int l_count =0;
static int r_count =0;

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct avl{
    int data;
    struct avl* left;
    struct avl* right;
    int h;
};

typedef struct avl node;

node * createNode(int data){
	node * x = (node *)malloc(sizeof(node));
	x->left = NULL;
	x->right = NULL;
    x->h = 0;
	x->data = data;
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

void drawtree(node * root,int n,char label){
	if(root == NULL){
		return;
	}
	for(int i = 0 ; i < n ; i++){
		printf("    ");
	}
	printf("%d%c(%d)",root->data,label,root->h);
	printf("\n");
	printf("\n");
	drawtree(root->right,n+1,'R');
	drawtree(root->left,n+1,'L');
}

node * r_rotate(node * z){
    r_count++;
    node * y = z->left;
    node * t = y->right;
    y->right = z;
    z->left = t;
    z->h = update_H(z);
    y->h = update_H(y);
    return y;
}

node * l_rotate(node * z){
    l_count++;
    node * y = z->right;
    node * t = y->left;
    y->left = z;
    z->right = t;
    z->h = update_H(z);
    y->h = update_H(y);
    return y;
}

node * AVL_insert(node * root, int data){
    if(root == NULL){
        return createNode(data);
    }

    if(data > root->data){
        root->right = AVL_insert(root->right,data);
    }
    else{
        root->left = AVL_insert(root->left,data);
    }

    root->h = update_H(root);
    if(!isBalanced(root)){
        if(data > root->data){
            if(data > root->right->data){               //RR
                return l_rotate(root);
            }
            else{                                       //RL    
                root->right = r_rotate(root->right);
                return l_rotate(root);
            }
        }
        if(data <= root->data){
            if(data < root->left->data){               //LL
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

void Search(node * root,int key){
    node * rootcpy = root;
    while(root != NULL){
        if(root->data == key){
            break;
        }
        if(root->data >= key){
            root=root->left;
        }
        else
            root=root->right;
    }
    if(!root){
        printf("-1\n");
        return;
    }
    while(rootcpy != NULL){
        if(rootcpy->data == key){
            printf("%d ",rootcpy->data);
            break;
        }
        if(rootcpy->data > key){
            printf("%d ",rootcpy->data);
            rootcpy=rootcpy->left;
        }
        else{
            printf("%d ",rootcpy->data);
            rootcpy=rootcpy->right;
        }
    }
    printf("\n");
    return;
}

node * smallest(node * root){
    while(root->left){
        root = root->left;
    }
    return root;
}

void Postorder(node * root){
    if(root != NULL){
        Postorder(root->left);
        Postorder(root->right);
        printf("%d ",root->data);
    }
}


int AVL_balancefactor(node * root,int key){
    while(root != NULL){
        if(root->data == key){
            break;
        }
        if(root->data >= key){
            root=root->left;
        }
        else
            root=root->right;
    }
    if(!root){
        return -1;
    }
    return bal_fact(root);
}

node * AVL_delete_iterative(node ** root, int key){
    node * para = NULL;
    node * x = *root; 
    while(x != NULL){
        if(x->data == key){
            break;
        }
        para = x;
        if(x->data >= key){
            x = x->left;
        }
        else{
            x=x->right;
        }
    }

    if(!root){
        return NULL;
    }

    if(x->left == NULL && x->right == NULL){
        if(x == *root){
            *root = NULL;
            return NULL;
        }
        if(para->left == x){
            para->left = NULL;
        }
        else{
            para->right = NULL;
        }
    }

    if(x->left == NULL && x->right != NULL){
        if(para->left == x){
            para->left = x->right;
        }
        else{
            para->right = x->right;
        }
    }

    if(x->left != NULL && x->right == NULL){
        if(para->left == x){
            para->left = x->left;
        }
        else{
            para->right = x->left;
        }
    }

    if(x->left != NULL && x->right != NULL){
        node * succparent=x;
        node * succ=x->right;         //finding successor of x ie minimum of x.right
        while(succ->left != NULL){
            succparent=succ;
            succ=succ->left;
        }
        if(succparent != x){
            if(succparent->left == succ)
                succparent->left=succ->right;
            if(succparent->right == succ)
                succparent->right = succ->right;
            succ->right=x->right;
        }
        if(para!=NULL){
            if(para->left == x)
                para->left=succ;
            if(para->right == x)
                para->right = succ;
        }
        if(para == NULL){                    //x is roots
            *root = succ;
        }
        succ->left = x->left;
    }
    free(x);

}


node * AVL_delete_recursive(node * root,int key){
    if(!root){
        return root;
    }
    if(root->data > key){
        root->left = AVL_delete_recursive(root->left,key);
        
        
    }
    else if(root->data < key){
        root->right = AVL_delete_recursive(root->right,key);
    }
    else{
        node * temp = NULL;
        int f=0;
        // Cases when root has 0 children
        // or only right child
        if (root->left) {
            f=1;
            temp = root->left;
        }
        // When root has only left child
        if (root->right) {
            f = (f==0) ? -1 : 2;
            temp = root->right;
        } 

        if(f == 0){     //no children
            return NULL;
            temp = root;
            root = NULL;
        }

        if(f == 1 || f == -1){  //i child
            *root = *temp;
        }
        if(f == 2){  //both child
            node * succ = smallest(root->right);
            root->data = succ->data;
            root->right = AVL_delete_recursive(root->right, succ->data);
        }
    }

    root->h = update_H(root);
    int balance = bal_fact(root);

    if (balance > 1 && bal_fact(root->left) >= 0){
        return r_rotate(root);
    }

    // Left Right Case
    if (balance > 1 && bal_fact(root->left) < 0) {
        root->left = l_rotate(root->left);
        return r_rotate(root);
    }

    // Right Right Case
    if (balance < -1 && bal_fact(root->right) <= 0){
       return l_rotate(root);
    }
    // Right Left Case
    if (balance < -1 && bal_fact(root->right) > 0) {
        root->right = r_rotate(root->right);
        return l_rotate(root);
    }

    return root;
}
 
int ancestor(node * root,int key){
    if(!root){
        printf("-1");
        return 0;
    }
    if(key > root->data){
        int r;
        r = ancestor(root->right,key);
        if(r==1){
            printf("%d ",root->data);
        }
        return r;
    }
    else if(key < root->data){
        int r;
        r = ancestor(root->left,key);
        if(r==1){
            printf("%d ",root->data);
        }
        return r;  
    }
    else{
        printf("%d ",root->data);
        return 1;
    }
}

node  * AVL_delete(node * root, int key){
    int r = ancestor(root,key);
    printf("\n");
    if(r==0){
        return root;
    }
    if(r == 1){
        return AVL_delete_recursive(root,key);
       
    }
}

void AVL_rotations(node * root){
    printf("%d %d\n",l_count,r_count);
}

int main(){
    node * root = NULL;
    char c;
    int key;
    while(1){
        scanf("%c",&c);
        if(c == 'e'){
            break;
        }
        switch(c){
            case 'i':{
                scanf("%d",&key);
                root = AVL_insert(root,key);
                break;
            }

            case 'f':{
                scanf("%d",&key);
                Search(root,key);
                break;
            }

            case 'p':{
                Postorder(root);
                printf("\n");
                break;
            }

            case 'b':{
                scanf("%d",&key);
                printf("%d\n",AVL_balancefactor(root,key));
                break;
            }

            case 'c':{
                drawtree(root,0,'H');
                break;
            }

            case 'd':{
                scanf("%d",&key);
                root = AVL_delete(root,key);
                break;
            }

            case 's':{
                AVL_rotations(root);
                break;
            }

            default:
                break;
        }
    }
    

}