 #include <stdio.h>
 #include <stdlib.h>

void swap(int arr[],int a,int b){
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}


void insert(int heap[],int size,int num){
    heap[size] = num;
    while(size > 0 && heap[(size-1)/2] < heap[size]){
        swap(heap,size,(size-1)/2);
        size = (size-1)/2;
    }
}

void maxHeapify(int heap[],int i, int size){
    int large = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if( l < size && heap[l] > heap[large]){
        large = l;
    }

    if(r < size && heap[r] > heap[large]){
        large = r;
    }

    if(large != i){
        swap(heap,large,i);
        maxHeapify(heap,large,size);
    }
}

void deleteMax(int heap[] , int size){
    swap(heap,0,size-1);
    size--;
    maxHeapify(heap,0,size);
}





 int main(){

 }