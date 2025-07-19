#include <stdio.h>
#include <stdlib.h>

struct queue{
    int data;
    struct queue * next;
};

typedef struct queue queue;

int min(int a,int b){
    return a < b ? a : b;
}

queue * createNode(int data){
    queue * x = (queue *)malloc(sizeof(queue));
    x->data = data;
    x->next = NULL;
}

void enqueue(queue ** rear, queue ** front, int data){
    queue * x = createNode(data);
    if(*rear == NULL){
        *rear = *front = x;
        return;
    }

    (*front)->next = x;
    *front  = x;
    return;
}

int dequeue(queue ** rear, queue ** front){
    int d = (*rear)->data;
    *rear = (*rear) ->next;
    if(*rear == NULL){
        *front = NULL;
    }
    return d;
}

int isBipartite(int n, int mat[n][n]){
    int colour[n];
    for(int  i = 0 ; i < n ; i++){
        colour[i] = -1;
    }

    queue * front = NULL;
    queue * rear = NULL;

    for(int i = 0 ; i < n ; i++){
        if(colour[i] == -1){
            colour[i] = 0;
            enqueue(&rear,&front,i);

            while(front){
                int u = dequeue(&rear,&front);
                for(int v = 0 ; v < n ; v++){
                    if(mat[u][v] == 1){
                        if(colour[v] == -1){
                            colour[v] = !colour[u];
                            enqueue(&rear,&front,v);
                        }
                        else if(colour[v] == colour[u]){
                            return -1;
                        }
                    }
                }
            }
        }
    }

    return 1;

}

int hasCycle(int n, int mat[n][n],int * count){
    int colour[n];
    for(int  i = 0 ; i < n ; i++){
        colour[i] = -1;
    }

    queue * front =NULL;
    queue * rear = NULL;

    for(int i = 0 ; i < n ; i++){
        if(colour[i] == -1){
            (*count)++;
            enqueue(&rear,&front,i);

            while(front){
                int u = dequeue(&rear,&front);
                if(colour[u] == 0){
                    return 1;
                }

                colour[u] = 0;

                for(int v = 0 ; v < n ; v++){
                    if(mat[u][v] == 1){
                        if(colour[v] == -1){
                            enqueue(&rear,&front,v);
                        }
                    }
                }
            }
        }
    }

    return -1;

}

int isTree(int n, int mat[n][n]){
    int count = 0;
    if(hasCycle(n,mat,&count) == -1 && count == 1){
        return 1;
    }
    else{
        return -1;
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int mat[n][n];

    for(int i = 0 ; i <  n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d",&mat[i][j]);
        }
    }

    char c;
    while(1){
        scanf("%c",&c);
        if(c == 'x'){
            break;
        }
        switch(c){
            case 'a':{
                int num = isBipartite(n,mat);
                printf("%d\n",num);
                break;
            }

            
            case 'b':{
                int cou;
                int num = hasCycle(n,mat,&cou);
                printf("%d\n",num);
                break;
            }
            
            case 'c':{
                int num = isTree(n,mat);
                printf("%d\n",num);
                break;
            }
        }
    }
}