#include <stdio.h>
#include <stdlib.h>

int getMin(int n,int tree[],int key[]){
    int min = 9999;
    int min_i;
    for(int i = 0 ; i < n ; i ++){
        if(!tree[i] && key[i] < min){
            min = key[i];
            min_i = i;
        }
    }
}

void prims(int n,int adjMat[n][n],int src){
    int key[n];
    int parent[n];
    int tree[n];

    for(int i = 0 ; i < n ; i++){
        key[i] = 9999;
        tree[i] = 0;
        parent[i] = -1;
    }

    int sum = 0;

    key[src] = 0;
    parent[src] = -1;
    for(int i = 0; i < n ; i++){
        int u = getMin(n,tree,key);
        tree[u] = 1;
        for(int v = 0 ; v < n ; v++){
            if(adjMat[u][v] && !tree[v] && key[v] > adjMat[u][v]){
                parent[v] = u;
                key[v] = adjMat[u][v];
            }
        }

        if(parent[u] != -1){
            printf("%d %d\n",parent[u],u);
            sum += adjMat[parent[u]][u];
        }
    }

}




int main(){

}