#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct bt{
	int modelNo;
	int price;
	char name[50];

	struct bt* parent;
	struct bt* left;
	struct bt* right;
};

typedef struct bt node;

node * maximum(node * root){
	node * x = root;
	while(x->right != NULL){
		x = x->right;
	}
	return x;
}

node * minimum(node * root){
	node * x = root;
	while(x->left != NULL){
		x = x->left;
	}
	return x;
}
node * Create_Node(int model_number, char model_name[], int price){
	node * x = (node *)malloc(sizeof(node));
	x->left = NULL;
	x->right = NULL;
	x->parent = NULL;
	x->modelNo = model_number;
	strcpy(x->name,model_name);
	x->price = price;
	return x;
}

void printnode(node *x){
	printf("%d %s %d\n",x->modelNo,x->name,x->price);
}

void Add(node ** root, node * x ){
	node * y = *root;
	node * para = NULL;
	if(*root == NULL){
		*root = x;
		return;
	}
	while(y != NULL){
		para = y;
		if(y->modelNo >=  x->modelNo){
			y = y->left;
		}
		else {
			y = y->right;
		}
	}
	if(para->modelNo >= x->modelNo){
		para->left = x;
	}
	else{
		para->right = x;
	}
	x->parent = para;
}

void transplant(node ** root,node ** x,node ** y){
    if((*x)->parent==NULL){
        *root = *y;
    }
    else {
            if((*x)->parent->left == *x){
                (*x)->parent->left = *y;
            }
            if((*x)->parent->right == *x)
                (*x)->parent->right = *y;
        }
    if(*y != NULL){
        (*y)->parent = (*x)->parent;
    }
}




void Delete(node ** root,node * x){
    if(x==NULL){
        printf("-1\n");
        return;
    }
    if(x->left== NULL){
        transplant(root,&x,&(x->right));
    }
    else if(x->right==NULL){
        transplant(root,&x,&(x->left));
    }
    else{
            node *y=minimum(x->right);
            if(y->parent != x){
                transplant(root,&y,&(y->right));
                y->right = x->right;
                y->right->parent=y;
            }
            transplant(root,&x,&y);
            y->left=x->left;
            y->left->parent=y;
        }
	printnode(x);
	free(x);
}

node * Search(node * root,int modelNum){
    while(root != NULL){
        if(root->modelNo == modelNum){
            break;
        }
        if(root->modelNo > modelNum){
            root=root->left;
        }
        else
            root=root->right;
    }
    return root;
}

void Inorder(node * root){
	if(root ==  NULL){
		return;
	}
	Inorder(root->left);
	printnode(root);
	Inorder(root->right);

}

void Preorder(node * root){
	if(root ==  NULL){
		return;
	}
	printnode(root);
	Preorder(root->left);
	Preorder(root->right);

}

void Postorder(node * root){
	if(root ==  NULL){
		return;
	}
	Postorder(root->left);
	Postorder(root->right);
	printnode(root);
}

node * Modify(node * root, int model_number, int new_price){
	node * x = Search(root,model_number);
	if(!x){
		return x;
	}
	else{
		x->price = new_price;
		return x;
	}
}

int main(){
	node * root = NULL;
	char c;
	char name[50];
	int model_num,price;
	while(1){
	scanf("%c",&c);
	if(c == 'e'){
		break;
	}
	switch(c){
		case 'a':{
				scanf("%d %s %d",&model_num,name,&price);
				Add(&root,Create_Node(model_num,name,price));
				break;
				}
		case 'd':{
				scanf("%d",&model_num);
				Delete(&root,Search(root,model_num));
				break;
				}
		case 's':{
				scanf("%d",&model_num);
				node * x= Search(root,model_num);
				if(x){
					printnode(x);
				}
				else{
					printf("-1\n");
				}
				break;
				}
		case 'i':{
				Inorder(root);
				break;
				}
		case 'p':{
				Preorder(root);
				break;
				}
		case 't':{
				Postorder(root);
				break;
				}
		case 'm':{
				int newprice;
				scanf("%d %d",&model_num,&newprice);
				node * x = Modify(root,model_num,newprice);
				if(x){
					printnode(x);
				}
				else{
					printf("-1\n");
				}
				break;
				}

		default:break;
	}
	}
	

}
