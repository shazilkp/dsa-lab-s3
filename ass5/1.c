#include <stdio.h>
#include <stdlib.h>

struct stack{
    int data;
    struct stack * next;
};

typedef struct stack stack;

int min(int a,int b){
    return a < b ? a : b;
}

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

int dfs(int i, int n, int mat[n][n], int isVisited[]){
    stack * tos = NULL;
    push(&tos,i);
    isVisited[i] = 1;
    int count = 1;
    while(tos){
        int node = pop(&tos);
        for(int i = 0 ; i < n; i ++){
            if(mat[node][i] == 1 && !isVisited[i]){
                push(&tos,i);
                isVisited[i] = 1;
                count++;
            }
        }
    }
    return count;
}

int noOfConnectedComponents(int n,int mat[n][n]){
    int isVisited[n];

    for(int i = 0 ; i < n; i ++){
        isVisited[i] = 0 ;
    }

    int count = 0 ;
    for(int i = 0 ; i < n ; i++){
        if(!isVisited[i]){
            dfs(i,n,mat,isVisited);
            count++;
        }
    }
    return count;
}


void swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1])
                swap(arr, j, j + 1);
        }
    }
}

void sizeOfComponents(int n,int mat[n][n]){

    int isVisited[n];
    for(int i = 0 ; i < n; i ++){
        isVisited[i] = 0 ;
    }

    stack * tos = NULL;
    int count = 0 ;
    for(int i = 0 ; i < n ; i++){
        if(!isVisited[i]){
            push(&tos,dfs(i,n,mat,isVisited));
            count++;
        }
    }

    int numArray[count];
    stack * x = tos;
    int i=0;
    while(x){
        numArray[i] = pop(&x);
        i++;
    }
    
    bubbleSort(numArray,count);
    for(int i = 0 ; i < count; i++){
        printf("%d ",numArray[i]);
    }
    printf("\n");
}



void bridgeRec(int i, int n, int mat[n][n], int isVisited[], int para,int low[],int discovery[],int * time,int * count){

    isVisited[i] = 1;

    *time = *time +1;
    discovery[i] = low [i] = *time;

    for(int j = 0 ; j < n ; j++){
        if(mat[i][j] == 1){
            if(j == para){
                continue;
            }

            if(isVisited[j]){
                low[i] = min(low[i],discovery[j]);
            }

            if(!isVisited[j]){
                para = i;
                bridgeRec(j,n,mat,isVisited,para,low,discovery,time,count);
            }

            low[i] = min(low[i],low[j]);
            if(low[j] > discovery[i]){              //j can only be reached by passing through i
                (*count)++;
               // printf("count = %d: %d -> %d\n",*count,i+1,j+1);
            }
        }
    }
}

void noOfBridges(int n,int mat[n][n]){                  //if there is only 1 way to reach a vertex v then its a bridge
    int isVisited[n];
    int para = -1;
    int disc[n];
    int low[n];

    for(int i = 0 ; i < n; i ++){
        isVisited[i] = 0 ;
        low[i] = disc[i] = -1;              //essentially levels of our dfs tree
    }

    int time = 0;
    int count = 0 ;
    for(int i = 0 ; i < n ; i++){
        if(!isVisited[i]){
            bridgeRec(i,n,mat,isVisited,para,low,disc,&time,&count);
        }
    }


   /* for(int i = 0 ; i < n ;i ++){
        printf("%d: low = %d disc = %d\n",i,low[i],disc[i]);
    }
    */
    printf("%d\n",count);
}

void isAP_rec(int i,int n,int mat[n][n],int isVisited[],int para,int low[],int discovery[],int *time,int isAp[]){
    isVisited[i] = 1;
    *time = *time +1;
    discovery[i] = low [i] = *time;
    int children = 0;
    for(int j = 0 ; j < n ; j++){
        if(mat[i][j] == 1){
           // printf("%d is %d\n",j,isVisited[j]);
            if(j == para){
              //  printf("para :i = %d j = %d\n",i,j);
                continue;
            }

            if(!isVisited[j]){
              //  printf("hello");
                children++;
              //  printf("unvi_neighbour :i = %d j = %d\n",i,j);
                isAP_rec(j,n,mat,isVisited,i,low,discovery,time,isAp);
            

                low[i] = min(low[i],low[j]);
              //  printf("i = %d j = %d: low[%d] = %d disc[%d] = %d,para = %d\n",i,j,j,low[j],i,discovery[i],para);
                if(para != -1 && low[j] >= discovery[i]){              //j can only be reached by passing through i
                    isAp[i] =1;
                //    printf("truman89\n");
                // printf("count = %d: %d -> %d\n",*count,i+1,j+1);
                }
            }

            else {
                low[i] = min(low[i],discovery[j]);
               // printf("visi_neighbour :i = %d j = %d\n",i,j);
            }

        }
    }
    if(children > 1 && para == -1){     //root of tree with multiple children is ap
        isAp[i] = 1;
    }
}

void noOfArticulationPoints(int n,int mat[n][n]){
    int isVisited[n];
    int isAp[n];
    int para = -1;
    int disc[n];
    int low[n];
    
    for(int i = 0 ; i < n; i ++){
        isVisited[i] = 0 ;
        isAp[i] = 0;
        low[i] = disc[i] = 0;
    }

    int time = 0;
    int count = 0 ;

    for(int i = 0 ; i < n ; i++){
        if(!isVisited[i]){
            isAP_rec(i,n,mat,isVisited,para,low,disc,&time,isAp);
        }
    }
    int c = 0;
    for(int i = 0 ; i < n ; i ++){
        if(isAp[i]){
          //  printf("%d is ap\n",i);
            c++;
        }
    }

    for(int i = 0 ; i < n ; i ++){
       // printf("%d: disc:%d low:%d\n",i,disc[i],low[i]); 
    }
    printf("%d\n",c); 
}

int main(){
    int n;
    scanf("%d",&n);
    int mat[n][n];

    for(int i = 0 ; i <  n ; i++){
        for(int j = 0 ; j < n ; j++){
            scanf("%d",&mat[i][j]);
        }
    }

    char c;
    while(1){
        scanf("%c",&c);
        if(c == 'x'){
            break;
        }
        switch(c){
            case 'a':{
                int num = noOfConnectedComponents(n,mat);
                printf("%d\n",num);
                break;
            }

            
            case 'b':{
                sizeOfComponents(n,mat);
                break;
            }

            case 'c':{
                noOfBridges(n,mat);
                break;
            }

            case 'd':{
                noOfArticulationPoints(n,mat);
                break;
            }
            

            
        }
    }
}