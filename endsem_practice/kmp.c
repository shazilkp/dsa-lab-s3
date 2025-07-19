#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char text[1000];
    char pattern[100];

    scanf("%[^\n]s",text);
    scanf(" ");
    scanf("%[^\n]s",pattern);

    int m = strlen(pattern);
    int n = strlen(text);

    ////////////////////////////lps creation///////////////////////////////////
    int lps[m];

    int len = 0 ;//len stores the len og longest prefix which is aslo a proper suffix

    lps[0] = 0;  

    int i = 1;
    while(i < m){
        if(pattern[i] == pattern[len]){
            len++;
            lps[i] = len;
            i++;
        }

        else{
            if(len != 0){
                len = lps[len -1];      //reset to previous
            }
            else{
                lps[i]=0;
                i++;
            }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////

    i = 0 ;
    int j = 0;

    while(i < n){
        if(text[i] == pattern[j]){
            i++;j++;
        

            if(j == m){
                //add i-j to array
                j = lps[j -1];
            }
        }

        else{
            if(j != 0){
                j = lps[j -1];
            }
            else{
                i++;
            }
        }
    }
}