#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct patient{
    char name[30];
    int pat_id;
    int severity;
};

typedef struct patient pat;

void swap(pat H[],int i, int j){
    pat t = H[i];
    H[i] = H[j];
    H[j] = t;
}

void AdmitPatient(pat PQ[],int pat_id,char name[],int severity,int i){
    PQ[i].pat_id = pat_id;
    PQ[i].severity = severity;
  //  printf("inside admir pat = %d\n",PQ[i].pat_id);
    strcpy(PQ[i].name,name);

    while( i > 0 && PQ[(i-1)/2].severity > PQ[i].severity){
        swap(PQ,(i-1)/2,i);  
        i = (i-1)/2;
    }
}

void printQ(pat PQ[],int size){
    for(int i= 0; i < size; i++){
        printf("%d ",PQ[i].pat_id);
    }
    printf("\n");
}

void MinHeapify(pat PQ[],int i,int n){
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

 
    if(l < n && PQ[l].severity < PQ[i].severity){
        smallest = l;
    }

    if(r < n && PQ[smallest].severity > PQ[r].severity ){
        smallest = r;
    }

    if(smallest != i){
        swap(PQ,smallest,i);
        MinHeapify(PQ,smallest,n);
    }
}

int TreatPatient(pat PQ[],int i){
    if(i == 0){
        printf("-1\n");
        return -1;
    }
    else{
        pat t = PQ[0];
        swap(PQ,0,i-1);
        i--;
    //  H = realloc(H,(i+1) * sizeof(int));
        MinHeapify(PQ,0,i);
        printf("%d %s\n",t.pat_id,t.name);
        return 0;
    }
}

void extractMIN(pat PQ[],int i){
    if(i == 0){
        return;
    }
    else{
        pat t = PQ[0];
        swap(PQ,0,i-1);
        i--;
    //  H = realloc(H,(i+1) * sizeof(int));
        MinHeapify(PQ,0,i);
        printf("%d %s %d\n",t.pat_id,t.name,t.severity);
        return;
    }
}

int UpdateSeverity(pat PQ[], int pat_id, int newSev, int size){
    int i = 0;
    for(i = 0 ; i < size ; i ++){
        if(PQ[i].pat_id == pat_id){
            break;
        }
    }
    if(i == size){
        return -1;
    }
    if(newSev > PQ[i].severity){
        PQ[i].severity = newSev;
        MinHeapify(PQ,i,size);
        return 1;
    }
    if(newSev < PQ[i].severity){
        PQ[i].severity = newSev;
        while( i > 0 && PQ[(i-1)/2].severity > PQ[i].severity){
            swap(PQ,(i-1)/2,i);
            i = (i-1)/2;
        }
        return 0;
    }
    return 2;
}

void QueryPatient(pat PQ[], int pat_id, int size){
    int i;
    for(i = 0; i < size ; i++){
        if(PQ[i].pat_id == pat_id){
            break;
        }
    }

    if(i == size){
        printf("-1\n");
    }
    else{
        printf("%s %d\n",PQ[i].name,PQ[i].severity);
    }
}

void FindMostSevere(pat PQ[], int size){
    if(size == 0){
        printf("-1\n");
    }
    int n;
    n = size < 3 ? size : 3;
    pat PQ_copy[size];
    for(int i = 0 ; i < size ; i++){
        PQ_copy[i] = PQ[i];
    }
    for(int i = 0 ; i < n ; i++){
        extractMIN(PQ,size);
        size--;
    }
}

void printarray(pat PQ[],int size){
    for(int i= 0; i < size; i++){
        printf("%s %d %d\n",PQ[i].name,PQ[i].severity,PQ[i].pat_id);
    }

}


int main(){
    char c;
    int pat_id,severity;
    char name[30];
    int oldval,newval;
    int i = 0;
    int k;

    pat PQ[10000];


    while(1){
        scanf("%c",&c);
        if(c == 'g'){
            break;
        }

        switch(c){
            case 'a':{
                scanf("%d %d %s",&pat_id,&severity,name);
              //  printf("%d\n",pat_id);
                AdmitPatient(PQ,pat_id,name,severity,i);
                i++;
                printQ(PQ,i);
                break;
            }
            /*
            case 'p':{
                printHeap(H,i);
                break;
            }
            */
            case 't':{
                printarray(PQ,i);
                break;
            }
            
            

            case 'b':{
                int t = TreatPatient(PQ,i);
                if(t != -1){
                    i--;
                }
                break;
            }

            case 'c':{
                scanf("%d %d",&pat_id,&newval);
                int t = UpdateSeverity(PQ,pat_id,newval,i);
                if(t == -1){
                    printf("-1\n");
                }
                else{
                    printQ(PQ,i);
                }
                break;
            }
            
            case 'd':{
                scanf("%d",&pat_id);
                QueryPatient(PQ,pat_id,i);
                break;
            }

            
            case 'e':{
                FindMostSevere(PQ,i);
                break;
            }
            
           


            
        }
    }
}