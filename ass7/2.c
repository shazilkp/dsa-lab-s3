#include <stdio.h>
#include <stdlib.h>

int findRep(int parent[], int node){
    if(parent[node] == node){
        return node;
    }
    parent[node] = findRep(parent,parent[node]);                //staggered find
    return parent[node];
}

void setUnion(int u,int v, int parent[], int rank[], int n){
    int u_rep = findRep(parent,u); 
    int v_rep = findRep(parent,v);
    
    if(rank[u_rep] < rank[v_rep]){
        parent[u_rep] = v_rep;
    }
    else if(rank[u_rep] > rank[v_rep]){
        parent[v_rep] = u_rep;
    }
    else{
        parent[v_rep] = u_rep;
        rank[u_rep]++;
    }
}

void swap(int edgeCount, int edge[edgeCount][3], int i, int j) {
    int temp[3];

    temp[0] = edge[i][0];
    temp[1] = edge[i][1];
    temp[2] = edge[i][2];

    edge[i][0] = edge[j][0];
    edge[i][1] = edge[j][1];
    edge[i][2] = edge[j][2];

    edge[j][0] = temp[0];
    edge[j][1] = temp[1];
    edge[j][2] = temp[2];
}

void bubbleSort(int edgeCount, int edge[edgeCount][3]) {
    for (int i = 0; i < edgeCount - 1; i++) {
        for (int j = 0; j < edgeCount - i - 1; j++) {
            if (edge[j][2] > edge[j + 1][2])
                swap(edgeCount,edge,j,j+1);
        }
    }
}


void kruskal(int n, int edgeCount, int edge[edgeCount][3]){
    bubbleSort(edgeCount,edge);

    int parent[n];
    int rank[n];

    for (int i = 0 ; i < n ; i++) { 
        parent[i] = i; 
        rank[i] = 0; 
    }

    int minCost = 0;

    for(int i = 0 ; i < edgeCount ; i++){
        int u = findRep(parent,edge[i][0]);
        int v = findRep(parent,edge[i][1]);

        if(u != v){
            setUnion(u,v,parent,rank,n);
            minCost += edge[i][2];
        }
    }
    printf("%d\n",minCost);
}

int main(){
    int n;
    scanf("%d",&n);
    int adjList[n][n];
    int adjMat[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            adjList[i][j] = 15000;
            adjMat[i][j] = 15000 ;
        }
    }

    int t =0;
    int edgeCount = 0;
    for(int i = 0 ; i < n; i++){
        scanf("%d",&t);
       // printf("%d",t);
        char temp;
        int num = 0;
        int j = 0;
        int f = 0;
        while(1){
            scanf("%c",&temp);

            if(temp == '\n'){
                if(f == 1){
                    adjList[t][j++] = num;
                    edgeCount++;
                }
                break;
            }
            if(temp >= '0' && temp <= '9'){
                num = num *10 + (temp - '0');
              //  printf("num = %d\n",num);
                f = 1; 
            }
            if(temp == ' ' && f == 1){
               // printf("hello");
                adjList[t][j++] = num;
                edgeCount++;
                num = 0;
            }
        }
    }

    /*

    for(int i = 0 ; i < n ; i++){
        printf("%d: ",i);
        for(int j = 0 ; j < n; j++){
            printf("%d ",adjList[i][j]);
        }
        printf("\n");
    }

    */


    int weights[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            weights[i][j] = 15000;
        }
    }
    t = 0;
    for(int i = 0 ; i < n; i++){
        scanf("%d",&t);
       // printf("%d",t);
        char temp;
        int num = 0;
        int j = 0;
        int f = 0;
        while(1){
            scanf("%c",&temp);

            if(temp == '\n'){
                if(f == 1)
                    weights[t][j++] = num;
                break;
            }
            if(temp >= '0' && temp <= '9'){
                num = num *10 + (temp - '0');
              //  printf("num = %d\n",num);
                f = 1;
            }
            if(temp == ' ' && f == 1){
               // printf("hello");
                weights[t][j++] = num;
                num = 0;
            }
        }
    }

    edgeCount = edgeCount / 2 ;
    
    /*
    for(int i = 0 ; i < n ; i++){
        printf("%d: ",i);
        for(int j = 0 ; j < n; j++){
            printf("%d(%d) ",adjList[i][j],weights[i][j]);
        }
        printf("\n");
    }

    printf("edge count = %d\n",edgeCount);
    */
/*
    for(int i = 0 ; i < n ; i++){
        printf("%d: ",i);
        for(int j = 0 ; j < n; j++){
            printf("%d(%d) ",adjList[i][j],weights[i][j]);
        }
        printf("\n");
    }

    
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n && adjList[i][j] != 15000 ; j++){
            adjMat[i][adjList[i][j]] = weights[i][j];
        }
    } 

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            printf("%d ",adjMat[i][j]);
        }
        printf("\n");
    }

    for(int i = 0; i < edgeCount; i++){
        printf("%d---%d (%d)\n",edge[i][0],edge[i][1],edge[i][2]);
    }*/

    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n && adjList[i][j] != 15000 ; j++){
            adjMat[i][adjList[i][j]] = weights[i][j];
        }
    } 

    int edge[edgeCount][3];
    int k = 0;
    for(int i = 0 ; i < n ;i ++){
        for(int j = i + 1 ; j < n; j++){
            if(adjMat[i][j] == 15000){
                continue;
            }
            edge[k][0] = i;
            edge[k][1] = j;
            edge[k][2] = adjMat[i][j];
            k++;
        }
    }

    kruskal(n,edgeCount,edge);



}