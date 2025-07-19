#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    return a > b ? a : b;
}


int main()
{

    char string[1000000];
    char pattern[1000000];
    scanf("%[^\n]s", string);

    //  char pattern[1000000];
    scanf(" ");
    scanf("%[^\n]s", pattern);

    int patternsize = 0;
    int stringsize = 0;

    while (pattern[patternsize] != '\n' && pattern[patternsize] != '\0')
    {
        patternsize++;
    }

    while (string[stringsize] != '\n' && string[stringsize] != '\0')
    {
        stringsize++;
    }

    int bpos[patternsize + 1], shift[patternsize + 1];

    for (int i = 0; i < patternsize + 1; i++)
    {
        shift[i] = 0;
    }

    int i = patternsize, j = patternsize + 1;
    bpos[i] = j;

    while (i > 0)
    {
        while (j <= patternsize && pattern[i - 1] != pattern[j - 1])
        {
            if (shift[j] == 0)
                shift[j] = j - i;

            j = bpos[j];
        }

        i--;
        j--;
        bpos[i] = j;
    }

    j = bpos[0];
    for (i = 0; i <= patternsize; i++)
    {

        if (shift[i] == 0)
        {
            shift[i] = j;
        }

        if (i == j)
        {
            j = bpos[j];
        }
    }

    int badchar[256];

    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    for (i = 0; i < patternsize; i++)
        badchar[(int)pattern[i]] = i;

    int s = 0;

    while (s <= (stringsize - patternsize))
    {
        int j = patternsize - 1;

        int k = 0;
        while (j >= 0 && pattern[j] == string[s + j])
        {
            k++;
            //  printf("pattern[%d] = %c, string[%d] = %c\n",j,pattern[j],s+j,string[s + j]);
            // printf("k = %d \n",k);
            j--;
        }
        if (j < 0)
        {
            printf("%d ", s);
            return 0;
        }

        else
        {
            s = s + max(max(1, j - badchar[string[s + j]]), shift[j + 1]);
        }
    }
    printf("-1");
}