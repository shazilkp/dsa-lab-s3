#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>


int findP(int i,int parent[]){
    if(parent[i] == i){
        return i;
    }
    parent[i] = findP(parent[i],parent);
    return parent[i];
}

void setunion(int u,int v,int parent[]){
    int u_p = findP(u,parent);
    int v_p = findP(v,parent);

    if(u_p != v_p){
        parent[u_p] = v_p;
    }
}

bool equationsPossible(char** equations, int equationsSize) {

    int n = 26;
    int parent[n];
    for(int i = 0 ; i < n ; i ++){
        parent[i] = i;
    }

    for(int i = 0 ; i < equationsSize ; i++){
        if(equations[i][1] == '='){
            if(equations[i][0] != equations[i][3]){
                setunion(equations[i][0]-'a',equations[i][3] - 'a',parent);
            }
        }
    }

    for(int i = 0 ; i < n ; i++){
        printf("parent[%c] = %c",i+'a',parent[i]+'a');
    }

    for(int i = 0 ; i < equationsSize ; i++){
        if(equations[i][1] == '!'){
            if(parent[equations[i][0] - 'a'] == parent[equations[i][3] - 'a']){
                return false;
            }
            
        }
    }
    return true;
}

int main(){
    char string[4][4];
    strcpy(string[0],"a==b");
    strcpy(string[1],"e==c");
    strcpy(string[2],"b==c");
    strcpy(string[3],"a!=e");

    for(int i = 0 ; i < 4; i++){
        printf("%s\n",string[i]);
    }

    equationsPossible(string,4);
}