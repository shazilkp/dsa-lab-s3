#include <stdio.h>
#include <stdlib.h>

struct q{
    int data;
    struct q* next;
};

typedef struct q q;

q * createNode(int data){
    q * t = (q *)malloc(sizeof(q));
    t->data = data;
    t->next = NULL;
    return t;
}

void enqueue(q ** rear, q ** front, int data){
    q * x = createNode(data);
    if(*rear == NULL){
        *rear = *front = x;
        return;
    }

    (*front)->next = x;
    *front  = x;
    return;
}

int dequeue(q ** rear, q ** front){
    int d = (*rear)->data;
    *rear = (*rear) ->next;
    if(*rear == NULL){
        *front = NULL;
    }
    return d;
}




void dfs_rec(int i,int n,int adjMat[n][n],int isVisited[],int parent[]){
    isVisited[i] = 1;
    printf("%d ",i);
    for(int j = 0 ; j < n ; j++){
        if(adjMat[i][j] && !isVisited[j]){
            parent[j] = i;
            dfs_rec(j,n,adjMat,isVisited,parent);
        }
    }
    // if(parent[i] != -1){
    //     printf("%d-->%d\n",parent[i],i);
    // }
}




void dfs(int n,int adjMat[n][n]){
    int isVisited[n];
    int parent[n];

    for(int i = 0 ; i < n ; i++){
        isVisited[i] = 0;
        parent[i] = -1;

    }

    for(int i = 0; i < n ; i ++){
        if(!isVisited[i]){
            dfs_rec(i,n,adjMat,isVisited,parent);
        }
    }

}

void bfs(int n,int adjMat[n][n]){
    int isVisited[n];
    int parent[n];

    for(int i = 0 ; i < n ; i++){
        isVisited[i] = 0;
        parent[i] = -1;

    }

    q * front = NULL;
    q * back = NULL;

    for(int i = 0; i < n ; i ++){
        if(!isVisited[i]){

            enqueue(&back,&front,i);
            isVisited[i] = 1;
            while(front){
                int j = dequeue(&back,&front);
                printf("%d ",j);
                for(int k = 0 ; k < n ; k ++){
                    if(adjMat[j][k] && !isVisited[k]){
                        isVisited[k] = 1;
                        enqueue(&back,&front,k);
                    }
                }
            }
            
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int adjMat[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d",&adjMat[i][j]);
        }
    }

    //dfs(n,adjMat);
    bfs(n,adjMat);
}