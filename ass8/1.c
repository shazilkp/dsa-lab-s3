#include <stdio.h>
#include <stdlib.h>

int main()
{
    char string[1000000];
    scanf("%s",string);
    
    char pattern[100000];
    scanf("%s",pattern);
    
    int patternsize = 0;
    int stringsize = 0;

    while(pattern[patternsize] != '\n' && pattern[patternsize] != '\0'){
      patternsize++;
    }
    
    while(string[stringsize] != '\n' && string[stringsize] != '\0'){
      stringsize++;
    }

  //  printf("%s %s",pattern,string);
    
    int lps[patternsize];
    
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while(i < patternsize){
      
      if(pattern[i] == pattern[len]){
        len++;
        lps[i] = len;
        i++;
      }
      
      else{
        if(len > 0){
          len = lps[len -1];
        }
        else{
          lps[i] = 0;
          i++;
        }
      }
    }
    
    i=0;
    int j=0;
    
    int currIndex = -1;
    int count = 0;
    while(i < stringsize){
      if(string[i] == pattern[j]){
        i++;j++;
        
        if(j == patternsize){   //if entire pattern matched
          currIndex = i-j;
          count++;
          j = lps[j - 1];
        }
      }
      
      else{
        if(j > 0){
          j = lps[i-1];
        }
        else{
          i++;
        }
      }
      
    }
    
    if(count == 0){
      printf("-1");
      return 0;
    }
    printf("%d %d",currIndex,count);
    
    
    
}