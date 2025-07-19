#include <stdio.h>
#include <stdlib.h>

int min(int a,int b){
    return a < b ? a : b;
}

struct stack{
    int data;
    struct stack * next;
};

typedef struct stack stack;

stack * createNode(int data){
    stack * x = (stack *)malloc(sizeof(stack));
    x->data = data;
    x->next = NULL;
}

void push(stack ** tos,int data){
    stack * newNode = createNode(data);
    if(*tos == NULL){
        *tos = newNode;
    }
    else{
        newNode->next = *tos;
        *tos = newNode;
    }
}

int pop(stack ** tos){
    if(*tos != NULL){
        int n = (*tos)->data;
        *tos = (*tos)->next;
        return n;
    }
    else 
        return -1;
}

/*
int dfs(int i, int n, int mat[n][n], int isVisited[]){
    stack * tos = NULL;
    push(&tos,i);
    isVisited[i] = 1;
    while(tos){
        int node = pop(&tos);
        for(int i = 0 ; i < n && mat[n][i] != -1 ; i++){
            if(!isVisited[mat[node][i] - 1]){
                push(&tos,mat[node][i] - 1);
                isVisited[mat[node][i] - 1] = 1;
            }
            else{
                return 1;
            }
        }
    }
    return -1;
}

int hasCycle2(int n,int mat[n][n]){
    int isVisited[n];
    for(int i = 0 ; i < n; i ++){
        isVisited[i] = 0 ;
    }

    int count = 0 ;
    for(int i = 0 ; i < n ; i++){
        if(!isVisited[i]){
            if(dfs(i,n,mat,isVisited) ==  )
            count++;
        }
    }

    return count;
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
                    printf("i = %d u = %d\n",i,u);
                    return 1;
                }

                colour[u] = 0;

                for(int v = 0 ; v < n && mat[u][v] != -1 ; v++){
                        printf("mat[%d][%d] = %d\n",u,v,mat[u][v]);
                        if(colour[mat[u][v] - 1] == -1){
                            enqueue(&rear,&front,mat[u][v] -1);
                        }
                    
                }
            }
        }
    }

    return -1;

}


*/

int dag_util_rec(int u ,int n, int adjList[n][n], int color[]){
    color[u] = 0;
    int returnVal = 0;
    for(int v = 0 ; v < n && (adjList[u][v] != -1 && adjList[u][v] != 0); v++){
        if(color[adjList[u][v] - 1] == -1){
            returnVal = dag_util_rec(adjList[u][v] - 1,n,adjList,color);
        }
        else if(color[adjList[u][v] - 1] == 0){
            return 1;
        }
    }
    color[u] = 1;
    return returnVal;
}

void isDAG(int n,int adjList[n][n]){
    int color[n];
    for(int i = 0 ; i < n ; i++){
        color[i] = -1;
    }

    for(int i = 0 ; i < n ; i++){
        if(color[i] == -1){
            if(dag_util_rec(i,n,adjList,color) == 1){
                printf("-1\n");
                return;
            }
        }
    }
    printf("1\n");
}

void dfs(int u,int n,int adjList[n][n],int isVisited[],stack ** tos,int wantToKeepStack){
    isVisited[u] = 1;
    for(int v = 0 ; v < n && (adjList[u][v] != -1 && adjList[u][v] != 0); v++){
        if(!isVisited[adjList[u][v] - 1]){
            dfs(adjList[u][v] - 1,n,adjList,isVisited,tos,wantToKeepStack);
        }
    }
    if(wantToKeepStack){
        push(tos,u);
    }
}

void noOfStronglyConnectedComponents(int n, int adjList[n][n]){         //kosaraju algo-the one discussed in class;
    
    int time = 0 ;
    int isVisited[n];
    for(int i = 0 ; i  < n ; i ++){
        isVisited[i] = 0;
    }

    stack * finTimeStack = NULL;
    
    for(int i = 0 ; i < n ; i++){
        if(!isVisited[i]){
            dfs(i,n,adjList,isVisited,&finTimeStack,1);
        }
    }

    for(int i = 0 ; i  < n ; i ++){
        isVisited[i] = 0;
    }
    

    int revAdjList[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            revAdjList[i][j] = -1;
        }
    }

    for(int  i = 0; i < n ; i++){
        for(int j = 0 ; j < n && adjList[i][j] != -1 && adjList[i][j] != 0; j++){
           // printf("tri %d tri\n",adjList[i][j]);
            int k;
            for(k = 0 ; k < n && revAdjList[adjList[i][j] - 1][k] != -1; k++);
             revAdjList[adjList[i][j] - 1][k] = i+1;
        }
    }

    stack * dummy = NULL;
    int numComponents = 0;
    while(finTimeStack){
        int v = pop(&finTimeStack);
        if(!isVisited[v]){
            numComponents++;
            dfs(v,n,revAdjList,isVisited,&dummy,0);
        }
    }
    printf("%d\n",numComponents);
    
}

int main(){
    int e,v;
    scanf("%d %d",&v,&e);
    int adjList[v][v];
    for(int i = 0 ; i < v ; i++){
        for(int j = 0 ; j < v; j++){
            adjList[i][j] = -1;
        }
    }

    int t =0;
    for(int i = 0 ; i < v; i++){
        scanf("%d",&t);
       // printf("%d",t);
        char temp;
        int num = 0;
        int j = 0;
        int f = 0;
        while(1){
            scanf("%c",&temp);

            if(temp == '\n'){
                adjList[t-1][j++] = num;
                break;
            }
            if(temp >= '0' && temp <= '9'){
                num = num *10 + (temp - '0');
              //  printf("num = %d\n",num);
                f = 1; 
            }
            if(temp == ' ' && f == 1){
               // printf("hello");
                adjList[t-1][j++] = num;
                num = 0;
            }
        }
    }
    
    for(int i = 0 ; i < v ; i++){
        for(int j = 0 ; j < v; j++){
                printf("%d ",adjList[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    
    char c;
    while(1){
        scanf("%c",&c);
        if(c == 'x'){
            break;
        }
        switch(c){
            /*
            case 'a':{
                int cou;
                int num = hasCycle(v,adjList,&cou);
                printf("%d\n",num);
                break;
            }
            */

            case 'a':{
                isDAG(v,adjList);
                break;
            }

            case 'b':{
                noOfStronglyConnectedComponents(v,adjList);
                break;
            }
            
        }
    }


    
    for(int i = 0 ; i < v ; i++){
        for(int j = 0 ; j < v; j++){
            if(adjList[i][j] == -1){
                printf(" ");
            }
            else{
                printf("%d ",adjList[i][j]);
            }
        }
        printf("\n");
    }
}