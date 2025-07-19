#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int is_prime(int n){
    if(n <= 1){
        return 0;
    }
    for(int i = 2 ; i < sqrt(n)+1 ; i++){  
        if((n%i) == 0){
            return 0;
        }
    }
    return 1;
}

int nearest_prime(int n){
    int p = 0;
    for(int i = n-1; i>=2 ; i--){
        if(is_prime(i)){
            p = i;
            break;
        }
    }
    return p;
}

int h1(int k,int n){
    return k % n;
}

int h2(int k, int r){
    return r - (k % r);
}

int doublehash(int k,int n,int i){
    int r = nearest_prime(n);
    return (h1(k,n) + i * h2(k,r)) % n;
}

int linearHash(int k,int n,int i){
    return (h1(k,n) + i)%n;
}

int quadraticHash(int k,int n,int i){
    return (h1(k,n) + i*i)%n;
}


void LinearProbing(int hash[],int input[],int n,int m){
    for(int i= 0; i< n;i++){
        hash[i]=-1;
    }
    int collisioncount = 0;
    for(int j = 0; j < m;j++){
        for(int i=0;i<n;i++){
            int index = linearHash(input[j],n,i);
            if(hash[index] == -1){
                hash[index] = input[j];
                printf("%d ",index);
                break;
            }
            else{
                collisioncount++;
            }
        }
    }
    printf("\n%d\n",collisioncount);
}

void QuadraticProbing(int hash[],int input[],int n, int m){
    for(int i= 0; i< n;i++){
        hash[i]=-1;
    }
    int collisioncount = 0;
    for(int j = 0; j < m;j++){
        for(int i=0;i<n;i++){
            int index = quadraticHash(input[j],n,i);
            if(hash[index] == -1){
                hash[index] = input[j];
                printf("%d ",index);
                break;
            }
            else{
                collisioncount++;
            }
        }
    }
    printf("\n%d\n",collisioncount);
}

void DoubleHashing(int hash[],int input[],int n, int m){
    for(int i= 0; i< n;i++){
        hash[i]=-1;
    }
    int collisioncount = 0;
    for(int j = 0; j < m;j++){
        for(int i=0;i<n;i++){
            int index = doublehash(input[j],n,i);
            if(hash[index] == -1){
                hash[index] = input[j];
                printf("%d ",index);
                break;
            }
            else{
                collisioncount++;
            }
        }
    }
    printf("\n%d\n",collisioncount);
}


void printarray(int arr[],int n){
    for(int i=0 ; i<n ;i++){
        printf("%d ",arr[i]);
    }
}

int main(){
    int n,m;
    scanf("%d %d",&n,&m);
    int input[m];
    for(int i = 0 ; i < m; i++){
        scanf("%d",&input[i]);
    }
    int hash[n];
    char c;
    while(1){
        scanf("%c",&c);
        if(c == 'd'){
            break;
        }
        switch(c){
            case 'a':{
                LinearProbing(hash,input,n,m);
                break;
            }

            case 'b':{
                QuadraticProbing(hash,input,n,m);
                break;
            }

            case 'c':{
                DoubleHashing(hash,input,n,m);
                break;
            }

            case'p':{
                printarray(hash,n);
                break;
            }
        }
    }


}