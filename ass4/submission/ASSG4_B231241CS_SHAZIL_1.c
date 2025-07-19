#include <stdio.h>
#include <stdlib.h>
int mod(int n){
    if(n >= 0){
        return n;
    }
    else{
        return -n;
    }
}

int swap(int H[], int i, int j){
    int t = H[i];
    H[i] = H[j];
    H[j] = t; 
}

void MaxHeapify(int H[],int i,int n){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

 
    if(l < n && H[l] > H[i]){
        largest = l;
    }

    if(r < n && H[largest] < H[r] ){
        largest = r;
    }

    if(largest != i){
        swap(H,largest,i);
        MaxHeapify(H,largest,n);
    }
}



void InsertKey(int H[],int key,int i){
    H[i] = key;
    while( i > 0 && H[(i-1)/2] < H[i]){
        swap(H,(i-1)/2,i);
        i = (i-1)/2;
    }
}

void printHeap(int H[], int size){
    printf("\n");
    int j = 0;
    int noInlevel;
    int i = 0;
    while(i < size){
        noInlevel = 1 << j;
        for(int t = 0; t < noInlevel && i+t < size; t++){
            printf("%d ",H[i + t]);
        } 
        printf("\n");
        j++;
        i+=noInlevel;
    }
}

void printarray(int H[],int size){
    for(int i= 0 ; i < size; i++){
        printf("%d ",H[i]);
    }
}

void FindMax(int H[],int i){
    if(i == 0){
        printf("-1");
    }
    else{
        printf("%d",H[0]);
    }
    printf("\n");
}

int ExtractMax(int H[],int i){
    if(i == 0){
        printf("-1\n");
        return -1;
    }
    else{
        int r = H[0];
        swap(H,0,i-1);
        i--;
    //  H = realloc(H,(i+1) * sizeof(int));
        MaxHeapify(H,0,i);
        return r;
    }
}



void KthLargest(int H[],int k,int i){
    if(k > i){
        printf("-1\n");
        return;
    }
    int H_copy[i];
    for(int j = 0 ; j < i; j++){
        H_copy[j] = H[j];
    }

    int num;
    for(int j = 0 ; j < k; j++){
        num = ExtractMax(H_copy,i);
        i--;
    }
    printf("%d\n",num);
}

int DeleteKey(int H[],int k,int size){
    int i = 0;
    for(i = 0 ; i < size ; i ++){
        if(H[i] == k){
            break;
        }
    } 
    if(i == size){
        printf("-1\n");
        return -1;
    }

    swap(H,i,size-1);
    size--;
    MaxHeapify(H,i,size);
    if(size == 0){
        printf("0\n");
        return 0;
    }
    printarray(H,size);
    printf("\n");
}

int ReplaceKey(int H[], int oldval, int newval, int size){
    int i = 0;
    for(i = 0 ; i < size ; i ++){
        if(H[i] == oldval){
            break;
        }
    }
    if(i == size){
        return -1;
    }
    if(newval > oldval){
        H[i] = newval;
        while( i > 0 && H[(i-1)/2] < H[i]){
            swap(H,(i-1)/2,i);
            i = (i-1)/2;
        }
        return 0;
    }
    if(newval < oldval){
        H[i] = newval;
        MaxHeapify(H,i,size);
        return 1;
    }
    return 2;
}

int main(){
    char c;
    int key;
    int oldval,newval;
    int i = 0;
    int k;
//    int * H = (int *)malloc(sizeof(int));
    int H[10000];


    while(1){
        scanf("%c",&c);
        if(c == 'g'){
            break;
        }

        switch(c){
            case 'a':{
                scanf("%d", &key);
                int f=0;
                for (int k  = 0; k < i; k++)
                {
                    if (H[k] == key)
                    {
                        f =1;
                        break;
                    }
                }
                if(f == 0){
                    InsertKey(H,key,i);
                    i++;
                }
              //  H = realloc(H,(i+1) * sizeof(int));
                break;
            }
            /*
            case 'p':{
                printHeap(H,i);
                break;
            }

            case 't':{
                printarray(H,i);
                break;
            }
            */
            
            case 'b':{
                FindMax(H,i);
                break;
            }

            case 'c':{
                int t = ExtractMax(H,i);
                if(t != -1){
                    i--;
                    printf("%d ",t);
                    printarray(H,i);
                    printf("\n");
                }
                break;
            }
            
            case 'd':{
                scanf("%d",&k);
                KthLargest(H,k,i);
                break;
            }

            
            case 'e':{
                scanf("%d",&k);
                if(DeleteKey(H,k,i) != -1){
                    i--;
                }
                break;
            }
            
            case 'f':{
                scanf("%d %d",&oldval,&newval);
                int t = ReplaceKey(H,oldval,newval,i);
                if(t == -1){
                    printf("%d",mod(oldval-newval));
                }
                else{
                    printarray(H,i);
                }
                printf("\n");
                break;
            }


            
        }
    }
}