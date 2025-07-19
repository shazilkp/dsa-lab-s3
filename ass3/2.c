#include <stdio.h>
#include<stdlib.h>

struct linkedl{
    int key;
    struct linkedl* next;
};

typedef struct linkedl chain;

chain* createnode(int key){
    chain * node = (chain*)malloc(sizeof(chain));
    node->key = key;
    node->next = NULL;
    return node;
}

int h(int key,int n){
    return key % n;
}

int insertnode(chain** head,int key){
    chain* node = createnode(key);
    chain * x = *head;
    chain* prev = NULL;
    if(!x){
        *head = node;
        return 0;
    }
    int flag = 0;
    while(x!=NULL){
        if(x->key == key){
            flag = -1;
            break;
        }
        if(x->key > key){
            break;
        }
        prev = x;
        x = x->next;
    }
    if(flag == -1){
        printf("-1\n");
        return -1;
    }
    
    if(prev == NULL){
        node->next = *head;
        *head = node;
        return 0;   
    }
    prev->next = node;
    node->next = x;
    return 1;
}

void insert(chain * hash[],int key, int n){
    insertnode(&hash[h(key,n)],key);
}

void printhash(chain * hash[],int n){
    for(int i =0 ; i < n; i++){
        chain * x = hash[i];
        printf("%d. ",i);
        while(x != NULL){
            printf("%d -> ",x->key);
            x=x->next;
        }
        printf("NULL\n");
    }
}

void search(chain * hash[],int key,int n){
    int index = h(key,n);
    int posInChain = 1;
    chain * x = hash[index];
    while(x != NULL){
        if(x->key == key){
            break;
        }
        
        posInChain++;
        x=x->next;
    }
    if(!x){
        printf("-1");
    }
    else{
        printf("%d %d",index,posInChain);
    }
    printf("\n");
}

void delete(chain * hash[], int key, int n){
    int index = h(key,n);
    int posInChain = 1;
    chain * x = hash[index];
    chain * prev = NULL;
    while(x != NULL){
        if(x->key == key){
            break;
        }
        
        posInChain++;
        prev = x;
        x=x->next;
    }
    if(!x){
        printf("-1\n");
        return;
    }
    else{
        printf("%d %d\n",index,posInChain);
    }
    if(x == hash[index]){
        *(&hash[index]) = (hash[index])->next;
        return; 
    }
    if(prev){
        prev->next = x->next;
        return;
    }
}

void update(chain * hash[],int oldKey,int newKey,int n){
    int oldindex = h(oldKey,n);
    int newindex = h(newKey,n);
    int oldposInChain = 1;
    chain * x = hash[oldindex];
    chain * prev = NULL;
    while(x != NULL){
        if(x->key == oldKey){
            break;
        }
        oldposInChain++;
        prev = x;
        x=x->next;
    }
    if(!x){
        printf("-1\n");
        return;
    }

    if(insertnode(&hash[newindex],newKey) != -1){
        printf("%d %d\n",oldindex,oldposInChain);
        if(x == hash[oldindex]){
            *(&hash[oldindex]) = (hash[oldindex])->next;
            return; 
        }
        if(prev){
            prev->next = x->next;
            return;
        }
    }

}

void printElementsInChain(chain * hash[],int index){
    chain * x = hash[index];
    if(!x){
        printf("-1\n");
        return;
    } 
    printf("%d",x->key);
    x=x->next;
    while(x){
        printf(" %d",x->key);
        x=x->next;
    }
    printf("\n");
}

int main(){
    int n;
    scanf("%d",&n);
    chain * hash[n];
    for(int i=0; i<n; i++){
        hash[i] = NULL;
    }
    char c;
    int key;
    while(1){
        scanf("%c",&c);
        if(c == 'f'){
            break;
        }

        switch(c){
            case 'a':{
                scanf("%d",&key);
                insert(hash,key,n);
                break;
            }

            case 'b':{
                scanf("%d",&key);
                search(hash,key,n);
                break;
            }

            case 'c':{
                scanf("%d",&key);
                delete(hash,key,n);
                break;
            }

            case 'd':{
                int oldKey,newKey;
                scanf("%d %d",&oldKey,&newKey);
                update(hash,oldKey,newKey,n);
                break;
            }

            case 'e':{
                int index;
                scanf("%d",&index);
                printElementsInChain(hash,index);
                break;
            }
            
            /*
            case 'p':{
                printhash(hash,n);
            }
            */
        }
    }


}