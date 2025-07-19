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

struct node{
    int key;
    int index;
};

typedef struct node node;

int swap(node H[], int i, int j){
    node t = H[i];
    H[i] = H[j];
    H[j] = t; 
}

void min_heapify(node H[],int n,int i){
    int l = 2 *i + 1;
    int r = 2* i +  2;

    int smallest = i;
    if(l < n && H[l].key < H[smallest].key){
        smallest = l; 
    }

    if(r < n && H[r].key < H[smallest].key){
        smallest = r;
    }

    if(smallest != i){
        swap(H,smallest,i);
        min_heapify(H,n,smallest);
    }
}

void buildHeap(node arr[],int n){

    for(int i = (n/2) -1; i>= 0; i--){
      //  printf("l %d l\n",i);
        min_heapify(arr,n,i);
    }
}

int extractMin(node H[],int currSize){
    int min = H[0].index;
    swap(H,0,currSize -1);
    min_heapify(H,currSize-1,0);
    return min;

}

void printarr(node H[],int n){
    for(int i = 0 ; i < n ; i++){
        printf("%d(%d) ",H[i].index,H[i].key);
    }
    printf("\n");
}

int sequence(int n,int adjMat[n][n],int root){
    int key[n];
    int isInTree[n];
    int parent[n];
    node heap[n];
    int currsize = 0;

    for(int i = 0 ; i < n ; i++){
        key[i] = 100000;
        heap[i].index = i;
        heap[i].key = 100000;
        isInTree[i] = 0;
        parent[i] = -1;
    }



    key[root] = 0;
    int runWeight = 0;
    for(int i = 0 ; i < n ; i++){
        int u = getMin(n,isInTree,key);
        isInTree[u] = 1;
      //  printf("u =%d\n",u);
        for(int v = 0; v < n; v++){
            if(adjMat[u][v] && !isInTree[v] && (adjMat[u][v] < key[v])){
                parent[v] = u;
                key[v] = adjMat[u][v];
                printf("v=%d\n",v);
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

void decreaseKey(node H[], int n, int node,int newval){
    int i = 0;
    for(i = 0 ; i < n ; i++){
        if(H[i].index == node){
            break;
        }
    }

    H[i].key = newval;
        while( i > 0 && H[(i-1)/2].key > H[i].key){
            swap(H,(i-1)/2,i);
            i = (i-1)/2;
        }
}

int isInHeap(node H[], int n, int node){
    for(int i = 0 ; i < n ; i++){
        if(H[i].index == node){
            return 1;
        }
    }
    return 0;
}
int sequence2(int n,int adjMat[n][n],int root){
    int key[n];
    int isInTree[n];
    int parent[n];
    node heap[n];

    for(int i = 0 ; i < n ; i++){
        key[i] = 100000;
        heap[i].index = i;
        heap[i].key = 100000;
        isInTree[i] = 0;
        parent[i] = -1;
    }
    

    //key[root] = 0;
    heap[root].key = 0;
   // printarr(heap,n);
    buildHeap(heap,n);
    //printarr(heap,n);




    int runWeight = 0;
    int currsize = n;
    for(int i = 0 ; i < n ; i++){
      //  int u = getMin(n,isInTree,key);
        int u = extractMin(heap,currsize);
//printf("u = %d",u);
      //  printarr(heap,currsize);
        currsize--;
      //  isInTree[u] = 1;
     // printf("u = %d\n",u);
        for(int v = 0; v < n; v++){
            int j = 0;
            for(j = 0 ; j < currsize ; j++){
                if(heap[j].index == v){
                    break;
                }
            }

            if(adjMat[u][v] && j!=currsize && (adjMat[u][v] < heap[j].key)){
                parent[v] = u;
                key[v] = adjMat[u][v];
                decreaseKey(heap,currsize,v,adjMat[u][v]);
               // printf("v =%d, ind = %d,, ",v,j);
               // printarr(heap,currsize);
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

int main1(){
    int n =6;
    node arr[n];
    for(int i = 0 ;i < n; i++){
        arr[i].index = i;
        arr[i].key = 10000;
    }

    arr[1].key = 0;
    printarr(arr,n);
    buildHeap(arr,n);
    printarr(arr,n);
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