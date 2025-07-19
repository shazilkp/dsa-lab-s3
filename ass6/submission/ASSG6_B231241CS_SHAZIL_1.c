#include <stdio.h>
#include <stdlib.h>

int minDistanceVetrex(int n, int dist[], int shortestPathTreeSet[]){
    int min = 10000000;
    int min_index;

    for(int i = 0 ; i < n ; i++){
        if(shortestPathTreeSet[i] == 0 && dist[i] <= min){
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijikstra(int n, int adjList[n][n], int weights[n][n], int src){
    int dist[n];
    int shortestPathTreeSet[n];

    for(int i = 0 ; i < n ; i++){
        dist[i] = 10000000;
        shortestPathTreeSet[i] = 0;
    }

    dist[src] = 0;

    for(int i = 0 ; i < n-1 ; i++){
        int v = minDistanceVetrex(n,dist,shortestPathTreeSet);

        for(int j = 0 ; j < n && adjList[v][j] != -1 && adjList[v][j] != 0; j++){       //neighbours of v
       // printf(" %d %d \n",v+1,adjList[v][j]);
           if(shortestPathTreeSet[adjList[v][j] - 1] == 0 && dist[v] != 10000000){  //if neighbour is not in shortest treeset && v is visited
            if(dist[adjList[v][j] - 1] >  weights[v][j] + dist[v]){          //if distance through neighbour is smaller than already present update
                dist[adjList[v][j] - 1] = dist[v] + weights[v][j];
              //  printf("%d : %d\n",v,dist[v]);
            }
           }
        }
        shortestPathTreeSet[v] = 1;
    }
    for(int i = 0 ; i  < n ; i++){
        printf("%d ",dist[i]);
    }
    printf("\n");

}

int main(){
    int n;
    scanf("%d",&n);
    int adjList[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            adjList[i][j] = -1;
        }
    }

    int t =0;
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

    int weights[n][n];
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n; j++){
            weights[i][j] = -1;
        }
    }
    t =0;
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
                weights[t-1][j++] = num;
                break;
            }
            if(temp >= '0' && temp <= '9'){
                num = num *10 + (temp - '0');
              //  printf("num = %d\n",num);
                f = 1; 
            }
            if(temp == ' ' && f == 1){
               // printf("hello");
                weights[t-1][j++] = num;
                num = 0;
            }
        }
    }
    int src;
    scanf("%d",&src);

    printf("n = %d src =%d\n",n,src);
    for(int i = 0 ; i < n ; i++){
        printf("%d: ",i+1);
        for(int j = 0 ; j < n; j++){
            printf("%d(%d) ",adjList[i][j],weights[i][j]);
        }
        printf("\n");
    }

    dijikstra(n,adjList,weights,src-1);
}