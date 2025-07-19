#include <stdio.h>
#include <stdlib.h>


void floyd_warshall(int n, int adjMat[n][n], int dist[n][n]){
    for(int k = 0 ; k < n ; k++){
        for(int i = 0; i< n ; i++){
            for(int j = 0 ; j < n ; j++){

                 if(dist[i][k] != -1 && dist[k][j] != -1  && (dist[i][j] == -1 || (dist[i][k] + dist[k][j] < dist[i][j]))){

                    dist[i][j] = dist[i][k] + dist[k][j];

                }
            }
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    int adjMat[n][n];
    int dist[n][n];
    for(int i = 0; i< n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d",&adjMat[i][j]);
            dist[i][j] = adjMat[i][j];
        }
    }

    floyd_warshall(n,adjMat,dist);

    for(int i = 0; i< n ; i++){
        for(int j = 0 ; j < n ; j++){
            printf("%d ",dist[i][j]);
        }
        printf("\n");
    }

}