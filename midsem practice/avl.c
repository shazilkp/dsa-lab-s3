#include <stdio.h>
#include <stdlib.h>

struct avl{
    int data;
    struct avl * left;
    struct avl * right;
    int h;
};

typedef struct avl node;

struct q{
    node * treeNode;
    struct q * next;
    struct q* prev;
};

typedef struct q q;

q * createQNode(node * x){
    q * y = (q *)malloc(sizeof(q));
    y->treeNode = x;
    y->next = NULL;
    y->prev = NULL;

    return y;
}


int max(int a ,int b){
    return a > b ? a : b ;
}

int height(node * x){
    if(!x){
        return -1;
    }
    else{
        return x->h;
    }
}

node * smallest(node * x){
    while(x->left){
        x=x->left;
    }
    return x;
}

node * updateHeight(node * x){
    if(x){
        x->h = 1 + max(height(x->right),height(x->left));
    }
    return x;
}

int b_factor(node * x){
    if(!x){
        return 0;
    }
    return height(x->left) - height(x->right);
}

node * createNode(int data){
    node * x = (node *)malloc(sizeof(node));
    x->data = data;
    x->left = NULL;
    x->right = NULL;
    x->h = 0;
    return x;
}

node * l_rotate(node * z){
    node * y = z->right;
    node * t2 = y->left;

    y->left = z;
    z->right = t2;

    z = updateHeight(z);
    y = updateHeight(y);
     
    return y;
}

node * r_rotate(node * z){
    node * y = z->left;
    node * t2 = y->right;

    y->right = z;
    z->left = t2;

    z = updateHeight(z);
    y = updateHeight(y);
     
    return y;
}

void enque(q** head,node * x){
    q* newQNode = createQNode(x);
    if(!*head){
        *head = newQNode;
    }
    else{
        q * y = *head;
        while(y->next){
            y=y->next;
        }
        y->next= newQNode;
        newQNode->prev = y;
    }
}

node * deque(q ** head){
    if(!*head){
        return NULL;
    }

    q * hCopy = *head;
    *head = (*head)->next;
    return hCopy->treeNode;
}

node * insert(node * root, int data){
    if(root == NULL){
        return createNode(data);
    }

    if(root->data >= data){
        root->left = insert(root->left,data);
    }
    else{
        root->right = insert(root->right,data);
    }

    root = updateHeight(root);
    int b_val = b_factor(root);

    if(b_val > 1 && b_factor(root->left) >=0 ){                 //ll
        return r_rotate(root);
    }

    if(b_val > 1 && b_factor(root->left) < 0){                   //lr
        root->left = l_rotate(root->left);
        return r_rotate(root);
    }

    if(b_val < -1 && b_factor(root->right) <=0 ){                 //rr
        return l_rotate(root);
    }

    if(b_val < -1 && b_factor(root->right) > 0){                   //rl
        root->right = r_rotate(root->right);
        return l_rotate(root);
    }

    return root;
}

node * delete(node * root, int data){
    if(root == NULL){
        return NULL;
    }

    if(data > root->data){
        root -> right = delete(root->right,data);
    }
    else if(data < root->data){
        root->left = delete(root->left,data);
    }
    else{
        printf("hello");
        node * t = NULL;
        //1 or no child
        if(!root->left && !root->right){
            printf("sru");
            return NULL;
        }
        else if(!root->left && root->right){
            root = root->right;
        }
        else if(root->left && !root->right){
            root = root->left;
        }

        else if(root->left && root->right){
            printf("world");
            node * succ = smallest(root->right);
            root->data = succ->data;
            printf("%d",succ->data);
            root->right = delete(root->right,succ->data);
        }
    }
    root = updateHeight(root);
  //  printf("%d",root->h);
    int b_val = b_factor(root);

/*
    if(b_val > 1 && b_factor(root->left) >=0 ){                 //ll
        return r_rotate(root);
    }

    if(b_val > 1 && b_factor(root->left) < 0){                   //lr
        root->left = l_rotate(root->left);
        return r_rotate(root);
    }

    if(b_val < -1 && b_factor(root->right) <=0 ){                 //rr
        return l_rotate(root);
    }

    if (b_val < -1 && bal_fact(root->right) > 0) {
        root->right = r_rotate(root->right);
        return l_rotate(root);
    }

    */
    if(b_val > 1 && b_factor(root->left) >= 0){                            //ll
        return r_rotate(root);
    }

    if(b_val > 1 && b_factor(root->left) < 0){
        root->left = l_rotate(root->left);
        return r_rotate(root);
    }

    if(b_val < -1 && b_factor(root->right) <= 0){
        return l_rotate(root);
    }

    if(b_val < -1 && b_factor(root->right) > 0){                   // rl
        root->right = r_rotate(root->right);
        return l_rotate(root);
    }

    return root;
}

void drawtree(node * root,int n,char label){
	if(root == NULL){
		return;
	}
	for(int i = 0;i<n;i++){
		printf("    ");
	}
	printf("%d%c(%d)",root->data,label,root->h);
	printf("\n");
	printf("\n");
	drawtree(root->right,n+1,'R');
	drawtree(root->left,n+1,'L');
}

node * convert(node * root, char in[], int * j){
  
    /*  if(in[*j] == ' '){
        (*j)++;
    }
    */

    if(in[*j] >= '0'  && in[*j] <= '9'){
        int num = 0;
        int d = 0;
        while(in[*j] >= '0'  && in[*j] <= '9'){
            d = in[*j] - '0';
            num = num * 10 + d;
            (*j)++;
        }
        (*j)++;
        node * t = createNode(num);
        return convert(t,in,j);
    }

    if(in[*j] == ')'){
        (*j)+=2;
        return root;
    }

    int lvisit = 0;
    if(!lvisit){
        if(in[*j] == '('){
            (*j)+=2;
            lvisit = 1;
            root->left = convert(root->left,in,j);
        }
    }

    if(lvisit){
        if(in[*j] == '('){
            (*j)+=2;
            root->right = convert(root->right,in,j);
            (*j)+=2;
        }
    }

    root = updateHeight(root);
    printf("rd%drd\n",root->data);
    return root;
}



node *  convertInPre(int in[],int pre[], int inorderStart, int inorderEnd,int * preI){

    if(inorderStart > inorderEnd){
        return NULL;
    }

    int val = pre[(*preI)++];
    node * curr = createNode(val);

    if(inorderStart == inorderEnd){
        return curr;
    }


    int index;
    for(index = inorderStart; index <=inorderEnd ; index++){
        if(in[index] == val){
            break;
        }
    }

    curr->left = convertInPre(in,pre,inorderStart,index-1,preI);
    curr->right = convertInPre(in,pre,index+1,inorderEnd,preI);
    curr =  updateHeight(curr);
    return curr;


}


int qSize(q * head){
    int i  =0 ;
    while(head){
        i++;
        head = head->next;
    }
    return i;
}

void levelOrder(node * root){
    q * head = NULL;
    enque(&head,root);
    int num;
    while(head){
        num = qSize(head);
        while(num > 0){
            node * t  = deque(&head);
            if(t->left){
                enque(&head,t->left);
            }
            if(t->right){
                enque(&head,t->right);
            }
            printf("%d ",t->data);
            num--;
        }
        printf("\n");
    }
}

int main(){

    
    node * root = NULL;
    root = insert(root,65);
   // drawtree(root,0,'H');
    root = insert(root,5);
  //  drawtree(root,0,'H');
    root = insert(root,40);
  //  drawtree(root,0,'H');
    root = insert(root,35);
  //  drawtree(root,0,'H');
    root = insert(root,3);
  //  drawtree(root,0,'H');
    root = insert(root,14);
    root = insert(root,37);
    root = insert(root,75);
    drawtree(root,0,'H');
     printf("\n");
   levelOrder(root);
   // root = delete(root,35);
    printf("\n");
   // drawtree(root,0,'H');


    

   /*
   char in[1000];
   scanf("%[^\n]%c",in);
   int i;
   for(i = 0; i < 1000; i++){
    if(in[i] == '\0'){
        break;
    }
   }
   node * root = NULL;
   int j = 0; 
   root = convert(root,in,&j);
   drawtree(root,0,'H');

   */
  /*
  int n;
  scanf("%d",&n);
  int in[n];
  int pre[n];
  for(int i = 0 ; i < n ; i++){
    scanf("%d",&in[i]);
  }

  for(int i = 0 ; i < n ; i++){
    scanf("%d",&pre[i]);
  }
  int j = 0;

  node * root = convertInPre(in,pre,0,n-1,&j);
  drawtree(root,0,'H');
  */
}