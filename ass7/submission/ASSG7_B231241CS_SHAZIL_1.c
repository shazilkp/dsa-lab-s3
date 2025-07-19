#include <stdio.h>
#include <stdlib.h>

int getMin(int n,int isInTree[],int key[]){
    int min = 100000;
    int min_i;
    for(int i = 0 ; i < n ; i++){
        if(!isInTree[i] && key[i] < min){
            min = key[i];
            min_i = i;
        }
    }
    return min_i;
}

int sequence(int n,int adjMat[n][n],int root){
    int key[n];
    int isInTree[n];
    int parent[n];
    for(int i = 0 ; i < n ; i++){
        key[i] = 100000;
        isInTree[i] = 0;
        parent[i] = -1;
    }
    key[root] = 0;
    int runWeight = 0;
    for(int i = 0 ; i < n ; i++){
        int u = getMin(n,isInTree,key);
        isInTree[u] = 1;
        for(int v = 0; v < n; v++){
            if(adjMat[u][v] && !isInTree[v] && (adjMat[u][v] < key[v])){
                parent[v] = u;
                key[v] = adjMat[u][v];
            }
        }
        
         if(parent[u] != -1){
            printf("%d %d (%d) ",parent[u],u,adjMat[parent[u]][u]); 
            runWeight += adjMat[parent[u]][u];
        }
        
    }

   printf("\n");
   return runWeight;

}


int main(){
    int n;
    scanf("%d",&n);
    int adjMat[n][n];
    for(int i = 0 ; i < n ; i ++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d",&adjMat[i][j]);
        }
    }
    char c;
    int weight = -1;

    while(1){
        scanf("%c",&c);
        if(c == 'e'){
            break;
        }
        switch(c){
            case 's':{
                int root;
                scanf("%d",&root);
                weight = sequence(n,adjMat,root);
                break;
            }

            case 'b':{
                if(weight != -1){
                    printf("%d\n",weight);
                }
                else{
                    printf("%d\n",sequence(n,adjMat,0));
                }
                break;
            }
        }
    }

    
    
}