#include <stdio.h>
#include <stdlib.h>


int mod(int n){
    if(n<0){
        return -n;
    }
    else{
        return n;
    }
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
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

node * ParaToTree(node * root, char * in,int *j){

    if(in[*j] == ' '){
        (*j)++;
    }

    if(in[*j] >= '0' && in[*j] <= '9'){
        int num = 0;
        int d=0;
        while(in[*j] >= '0' && in[*j] <= '9'){
            d = in[*j] - 48;
            num = num*10 + d;
            (*j)++;
        }
        (*j)++;
        node * temp =  createNode(num);
        temp = ParaToTree(temp,in,j);
        return temp;
    }
    int lvisited = 0;

    if(in[*j] == ')'){
        (*j) = (*j) + 2;
        return root;
    }
                                //"1 ( 2 ( 4 ) ( 6 ) ) ( 3 )"
    if(!lvisited){
        if(in[*j] == '('){
            (*j) = (*j) + 2;
            lvisited = 1;
            root->left = ParaToTree(root->left,in,j);
            //printf("%d %d %c %d\n",root->data,*j ,in[*j],root->lvisited);
        }
    }
    if(lvisited == 1){
        if(in[*j] == '('){
           // printf("rightbaby %d\n",root->data);
            (*j) = (*j) + 2;
            root->right = ParaToTree(root->right,in,j);
        //    (*j) = (*j) + 2;
        }
    }

    root->h = update_H(root);
    return root;
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

void PrintPara(node * root){
	printf("%d ",root->data);
	
	if(root->left == NULL && root->right == NULL){
		return;
	}
	
	if(root->left != NULL){	
		printf("( ");
		PrintPara(root->left);
		printf(") ");
	}
	else{
		printf("( ) ");
	
	}
	
	if(root->right != NULL){	
		printf("( ");
		PrintPara(root->right);
		printf(") ");

	}
	else{
		printf("( ) ");

	}
}

node * smallest(node * root){
    while(root->left){
        root = root->left;
    }
    return root;
}

node * largest(node * root){
    while(root->right){
        root = root->right;
    }
    return root;
}
node * AVL_SeqInsert(node * root, int * numArray, int numArraySize){
    for(int k = 0 ; k < numArraySize ; k++){
        root = AVL_insert(root,numArray[k]);
    }
    PrintPara(root);
    printf("\n");
    return root;
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

node * search(node * root,int num){
    if(root == NULL)
        return NULL;
    if(root->data == num)
        return root;
    node * t= search(root->left,num);
    if(t != NULL){
        return t;
    }
    return search(root->right,num);
}

void preorder(node * root){
	if(root ==  NULL){
		return;
	}
    printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);
}

node * successor(node * root,int key){
    node * x = root;
    node * succ = NULL;
    while(x != NULL){
        if(key == x->data){
            break;
        }
        if(key > x->data){
            x=x->right;
        }
        else if(key < x->data){
            succ = x;
            x=x->left;
        }
    }
    if(!x){
        return NULL;
    }

    if(x->right){
        return smallest(x->right);
    }
    else{
        return succ;
    } 
}

int AVL_SuccessorPath(node * root, int n){
    node * succ = successor(root,n);
    if(!succ){
        //printf("%d",root->h);
        return root->h;
    }
    else{
        node * x = root;
        while(x != NULL){
            printf("%d ",x->data);
            if(succ->data == x->data){
                break;
            }
            if(succ->data > x->data){
                x=x->right;
            }
            else if(succ->data < x->data){
                x=x->left;
            }
        }
        printf("\n");
        return -1;
    }

}

int TreeSum(node * root){
    if(!root){
        return 0;
    }

    return root->data + TreeSum(root->left) + TreeSum(root->right);
}

void AVL_SubtreeSum(node * root, int n){
    node * x = root;
    while(x != NULL){
        if(n == x->data){
            break;
        }
        if(n > x->data){
            x=x->right;
        }
        else if(n < x->data){
            x=x->left;
        }
    }
    if(!x){
        printf("-1\n");
        return;
    }
    else{
        printf("%d ",TreeSum(x));
        PrintPara(x);
        printf("\n");
    }
}


void AVL_findClosest(node * root,int n){
    node * upSucc = NULL;
    node * upPred = NULL;
    node * x = root;
    node * succ = NULL;
    node * pred = NULL;
    while(x != NULL){
        if(n == x->data){
            break;
        }
        if(n > x->data){
            upPred = x;
            x = x->right;
        }
        else if(n < x->data){
            upSucc = x;
            x = x->left;
        }
    }
    if(!x){
        printf("-1");
        return;
    }
    if(x->right){
        succ = smallest(x->right);
    }
    else{
        succ = upSucc;
    }

    if(x->left){
        pred = largest(x->left);
    }
    else{
        pred = upPred;
    }

    if(!succ && !pred){
        printf("-1");
        return;
    }

    if(!succ || !pred){
        if(succ){
            printf("%d",succ->data);
        }
        else{
            printf("%d",pred->data);
        }
        return;
    }

    if(mod(succ->data - n) == mod(pred->data - n)){
        printf("%d",min(succ->data,pred->data));
        return;
    }
    printf("%d",mod(succ->data - n) > mod(pred->data - n) ? pred->data  : succ->data);
    return;
}
int main(){
    
    char c;
    char * inputParaRep = NULL;
    int i=0;            //size for input para rep
    inputParaRep = (char *)malloc(sizeof(char));
    while(scanf("%c",&c) && c != '\n'){
        inputParaRep[i] = c;
        inputParaRep = realloc(inputParaRep,(i+2)*sizeof(char));
        i++;
    }
    int j = 0;      //iterator to traverse through input para rep to convert
    node * root = NULL;
    root = ParaToTree(root,inputParaRep,&j);
    
    int numArraySize=0;
    char d,b;
    int * numArray = NULL;
    numArray = (int *)malloc(sizeof(int));
    while(1){
        scanf("%c",&d);
        if(d == 'g'){
            break;
        }
        switch(d){
            case 'a':{
                int numArraySize=0;
                int num=0;
                int d;
                while(scanf("%c",&b)){
                    if(b >= '0' && b <='9'){
                        d = b - '0';
                        num = num * 10 + d;
                    }
                    else if(num !=0){
                        numArray[numArraySize]=num;
                        numArray = realloc(numArray,(numArraySize+2)*sizeof(int));
                        numArraySize++;
                        num = 0;
                        if(b == '\n'){
                            break;
                        }
                    }                    
                }
                root = AVL_SeqInsert(root,numArray,numArraySize);
                break;

            }

            case 'b':{
                int n1,n2;
                scanf("%d %d",&n1,&n2);
                int deleteCount=0;
                for(int i = n1; i <= n2; i++){
                    if(search(root,i)){
                        deleteCount++;
                        root = AVL_delete_recursive(root,i);
                    }
                }
                if(deleteCount>0){
                    printf("%d ",deleteCount);
                    preorder(root);
                }
                else{
                    printf("-1");
                }
                printf("\n");
                break;
            }

            case 'c':{
                int n;
                scanf("%d",&n);
                int t = AVL_SuccessorPath(root,n);
                if(t != -1){
                    printf("%d\n",t);
                }
                break;
            }

            case 'd':{
                int n;
                scanf("%d",&n);
                AVL_SubtreeSum(root,n);
                break;
            }

            
            case 'f':{
                drawtree(root,0,'H');
                break;
            }
        

            case 'e':{
                int n;
                scanf("%d",&n);
                AVL_findClosest(root,n);
                printf("\n");
                break;

            }


        }
    }
   /*
    node * root = NULL;
 //   char t[]="8 ( 4 ( 2 ( 1 ( 10 ) ( ) ) ( ) ) ( ) ) ( 50 ( 40 ) ( 100 ( 90 ) ( 110 ) ) )";
 char t[]= "8 ( 4 ( 2 ( 1 ) ( ) ) ( ) ) ( 50 ( 40 ) ( 100 ( 90 ) ( 110 ) ) )";
    int j=0;
    root = convert(root,t,&j);
    drawtree(root,0,'H');
    */
}
