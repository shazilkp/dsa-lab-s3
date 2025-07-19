#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct tree{
    int key;
    struct tree *p;
    struct tree * l;
    struct tree * r;
    int lvisit;
};
typedef struct tree node;

node * createnode(int key){
    node * temp;
    temp=(node *)malloc(sizeof(node));
    temp->key=key;
    temp->p=NULL;
    temp->l=NULL;
    temp->r=NULL;
    temp->lvisit=0;
    return temp;
}

void printatdepth(node * x,int k){
    if(x == NULL){
        return;
    }
    if(k==0){
        printf("%d ",x->key);
        return;
    }
    printatdepth(x->l,k-1);
    printatdepth(x->r,k-1);
}


void preorder(node *root){
    if(root == NULL)
        return;

    printf("%d ",root->key);
    preorder(root->l);
    preorder(root->r);
    
} 

node * search(node * root,int num){
    if(root == NULL)
        return NULL;
    if(root->key == num)
        return root;
    node * t= search(root->l,num);
    if(t != NULL){
        return t;
    }
    return search(root->r,num);
}

void createTree(node ** root,char * input_tree){
    int j=0;
    node * current=NULL;
    while(input_tree[j]!='\0'){

        if(input_tree[j]=='('){               //new node
            int num=0,digit;
            int k=j+2;
            while(isdigit(input_tree[k])){
                digit=input_tree[k]-48;
                num=num*10+digit;
                k++;
            }

            node * temp=createnode(num);
            if(current == NULL){
                *root=temp;
            }
            if(current!=NULL){
                if(current->lvisit==0){
                    current->l=temp;
                    current->lvisit=1;
                }
                else if (current->lvisit == 1){
                    current->r=temp;
                    current->lvisit=0;
                }
            }
            temp->p=current;
            current=temp;
        }

        if(input_tree[j]==')'){             //end of the new node
            if(current->key==0 && current->p != NULL){
                if(current->p->l == current){
                    current->p->l = NULL;
                }
                if(current->p->r == current){
                    current->p->r = NULL;

                }
            }
            if(current->p == NULL && current->key == 0){
                *root=NULL;
            }
            current=current->p;
        }
    j++;
    }
}

int main(){
    char c;
    char * input_tree = NULL;
    int p=0,j=2;
    input_tree=(char *)malloc(sizeof(char));
    while((scanf("%c",&c)) && c != '\n'){
        input_tree[p]=c;
        input_tree=realloc(input_tree,j*sizeof(char));
        p++;j++;
    }
    input_tree[p]='\0';

    int x,k;
    scanf("%d",&x);
    scanf("%d",&k);

    node * root =NULL;
    createTree(&root,input_tree);
   // preorder(root);
   // node * t=search(root,6);
    printatdepth(search(root,x),k);
   // printf("%d",t->p->key);

}