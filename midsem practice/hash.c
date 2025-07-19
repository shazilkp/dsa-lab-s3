#include <stdio.h>
#include <stdlib.h>

int h1(int num, int k ){
    return num % k;
} 

int quadHash(int num,int i,int k){
    return (h1(num,k) + i*i) % k;
}

void insert(int H[], int val,int k){
    for(int i = 0 ; i < k; i++){
        int index = quadHash(val,i,k);
        if(H[index] == -1){
            H[index] = val;
            break;
        }
    }
}

void printhash(int hash[],int k){
    for(int i = 0;  i < k ; i++){
        printf("%d ",hash[i]);
    }
}

int main(){
    int hash[1000];
    for(int i = 0 ; i < 1000; i++){
        hash[i] = -1;
    }
    int input[1000];
    int k;
    scanf("%d",&k);
    int count = 0;
    char c;
    int val;
    while(1){
        scanf("%c",&c);
        if(c == 'e'){
            break;
        }
        switch(c){
            case 'i':{
                scanf("%d",&val);
                input[count] = val;
                count++;
                if(count*100/k > 75){
                    k = 2*k;
                    for(int i = 0 ; i < 1000; i++){
                        hash[i] = -1;
                    }
                    for(int i = 0;  i< count; i++){
                        insert(hash,input[i],k);
                    }
                }
                else{
                    insert(hash,input[count-1],k);
                }
                break;
            }

            case 'p':{
                printhash(hash,k);
                break;
            }
        }
        
    }

}