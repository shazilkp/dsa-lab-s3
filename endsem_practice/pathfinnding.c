#include <stdio.h>
#include <stdlib.h>



void dijikstra(int n, int adjMat[n][n],int src){
    int dist[n];
    int tree[n];
    for(int i = 0; i < n ; i++){
        dist[i] = 9999;
        tree[i] = 0;
    }

    dist[src] = 0;

    for(int i = 0 ; i < n ; i++){
        int u = findmin(n,dist);
        tree[u] = 1;
        for(int j = 0 ; j < n ; j++){
            if(adjMat[u][j] && dist[j] > dist[u] + adjMat[u][j] && !tree[j]){
                dist[j] = dist[u] + adjMat[u][j];
            }
        }
    }
}

void floyd_warshall(int n, int adjMat[n][n],int weight[n][n]){
    for(int k = 0 ; k < n ; k++){
        for(int i = 0 ; i < n ; i++){
            for(int j = 0 ; j < n ; j ++){
                if(adjMat[i][j] > weight[i][k] + weight[k][j]){
                    adjMat[i][j] = weight[i][k] + weight[k][j];
                }
            }
        }
    }
}


int main(){

}