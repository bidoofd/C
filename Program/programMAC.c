#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

//Let this be a test application an ecnryption system

int c_to_n(char c)
{
    int n = -1;
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = strchr(alphabet, toupper((unsigned char)c));

    if (p)
    {
        n = p - alphabet;
    }

    return n;
}

char * strlwr(char * s)
{
        char *t = s;
 
        if (!s)
        {
                return 0;
        }
 
        int i = 0;
        while ( *t != '\0' )
        {
                if (*t >= 'A' && *t <= 'Z' )
                {
                        *t = *t + ('a' - 'A');
                }
                t++;
        }
 
        return s;
}

char *inputString(FILE* fp, size_t size){
//The size is extended by the input with the value of the provisional
    char *str;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(*str)*size);//size is start size
    if(!str)return str;
    while(EOF!=(ch=fgetc(fp)) && ch != '\n'){
        str[len++]=ch;
        if(len==size){
            str = realloc(str, sizeof(*str)*(size+=16));
            if(!str)return str;
        }
    }
    str[len++]='\0';

    return realloc(str, sizeof(*str)*len);
}

int main(void)
{
    char *text;
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int num1, num2;

    printf("Enter the text you want to encrypt: ");
    text = inputString(stdin, 10);
    char newText[strlen(text)];
    printf("Enter the two encryption numbers you want to choose. \n");
    printf("Enter the first number: \n");
    scanf("%2147483647d", &num1);
    printf("Enter the second number: \n");
    scanf("%2147483647d", &num2);
    
    strlwr(text);
    
    for(int a = 0; a < strlen(text); a++)
    {
        int numMessage = c_to_n(text[a]) + 1;
        int numResult = (int)pow(numMessage, num1) % num2;
        //printf("%d\n", numResult);
        for(int b = 0; b < sizeof(letters); b++)
        {
            if(b == numResult)
            {
                newText[b] = letters[b];
            }
        }
    }
    
    for(int a = 0; a < strlen(newText); a++)
    {
        printf("%c", newText[a]);
    }

    free(text);
    return 0;
}