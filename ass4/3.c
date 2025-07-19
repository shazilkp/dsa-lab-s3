#include <stdio.h>
#include <stdlib.h>

struct data{
    int JID;
    int p;
};

typedef struct data data;

void swap(data Q[],int i, int j){
    data t = Q[i];
    Q[i] = Q[j];
    Q[j] = t;
}

void MinHeapify(data Q[],int i,int n){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

 
    if(l < n && Q[l].p < Q[i].p){
        smallest = l;
    }

    if(r < n && Q[smallest].p > Q[r].p ){
        smallest = r;
    }

    if(smallest != i){
        swap(Q,smallest,i);
        MinHeapify(Q,smallest,n);
    }
}

void Add(data Q[],int JID,int p,int i){
    Q[i].JID = JID;
    Q[i].p = p;

    while( i > 0 && Q[(i-1)/2].p > Q[i].p){
        swap(Q,(i-1)/2,i);  
        i = (i-1)/2;
    }
}

int Schedule(data Q[],int i){
    if(i == 0){
        return -1;
    }
    else{
        data t = Q[0];
        swap(Q,0,i-1);
        i--;
    //  H = realloc(H,(i+1) * sizeof(int));
        MinHeapify(Q,0,i);
        return t.JID;
    }
}

void Next_job(data Q[],int i){
    if(i == 0){
        printf("-1");
    }
    else{
        printf("%d",Q[0].JID);
    }
    printf("\n");
}

int replace_priority(data Q[], int JID, int newP, int size){
    int i;
    for(i = 0 ; i < size ; i ++){
        if(Q[i].JID == JID){
            break;
        }
    }
    if(i == size){
        return -1;
    }
    if(newP > Q[i].p){
        Q[i].p = newP;
        MinHeapify(Q,i,size);
        return 1;
    }
    if(newP < Q[i].p){
        Q[i].p = newP;
        while( i > 0 && Q[(i-1)/2].p > Q[i].p){
            swap(Q,(i-1)/2,i);
            i = (i-1)/2;
        }
        return 0;
    }
    return 2;
}

void Display(data Q[],int size){
    for(int i= 0; i < size; i++){
        printf("%d %d\n",Q[i].JID,Q[i].p);
    }
}


int main(){
    char c;
    int JID,p;
    int i = 0;
    data Q[1000];
    while(1){
        scanf("%c",&c);
        if(c == 'g'){
            break;
        }
        switch(c){
            case 'a':{
                scanf("%d %d",&JID,&p);
                Add(Q,JID,p,i);
                i++;
                break;
            }

            case 'b':{
                int t = Schedule(Q,i);
                printf("%d\n",t);
                if(t != -1){
                    i--;
                }
                break;
            }

            case 'c':{
                Next_job(Q,i);
                break;
            }

            case 'd':{
                scanf("%d %d",&JID,&p);
                int t = replace_priority(Q,JID,p,i);
                if(t == -1){
                    printf("%d\n",t);
                }
                break;
            }

            case 'e':{
                if(i == 0){
                    printf("-1\n");
                }
                else{
                    Display(Q,i);
                }
                break;
            }
        }
    }
}