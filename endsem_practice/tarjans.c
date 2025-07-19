#include <stdio.h>
#include <stdlib.h>


void bridge_rec(int i,int n,int mat[n][n],int isVisited[],int para,int low[],int disc[],int * time,int * count){
    isVisited[i] = 1;
    disc[i] = low[i] = ++(*time);

    for(int j = 0 ; j < n ; j++){
        if(mat[i][j]){
            if(j == para){
                continue;
            }

            if(isVisited[j]){
                low[i]=min(low[i],disc[j]);
            }

            if(!isVisited[j]){
                bridge_rec(j,n,mat,isVisited,i,low,disc,time,count);

                low[i]=min(low[i],low[j]);
            }

            if(low[j] > disc[i]){
                (*count)++;
            }
        }
    }
}

int main(){

}