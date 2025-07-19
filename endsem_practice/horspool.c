#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){
    char text[1000];
    char pattern[100];
    int s_table[256];

    scanf("%[^\n]s",text);
    getchar();
    scanf("%[^\n]s",pattern);

    int m = strlen(pattern);
    int n = strlen(text);

    

///////////////////////////shift table///////////////////////////////////
    for(int i = 0 ; i < 256 ; i++){
        s_table[i] = m; 
    }

    for(int i = 0; i < m-1 ; i++){
        s_table[pattern[i]] = m - 1 - i;
    }
/////////////////////////////////////////////////////////////////////////////////////
    int i = m - 1;

    while(i < n){
        int k = 0;
        while((k < m) && (text[i - k] == pattern[m-1-k])){
            k++;
        }
        if(k == m){
            printf("%d", i-m+1);
            return 0;
        }
        else{
            i = i + s_table[text[i]];
        }
   }

   printf("-1");

}