#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

//Let this be a test application an encryption system

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

void encrypt()
{
    char *text;
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    int num1, num2;

    //Enter text
    printf("Enter the text you want to encrypt: ");
    //INFINITE STRING
    text = inputString(stdin, 10);
    //create new string
    char newText[strlen(text)];
    //enter numbers
    printf("Enter the two encryption numbers you want to choose. \n");
    printf("Enter the first number: \n");
    scanf("%2147483647d", &num1);
    printf("Enter the second number: \n");
    scanf("%2147483647d", &num2);
    
    fflush(stdin);
    //lowers text
    strlwr(text);
    
    for(int a = 0; a < strlen(text); a++)
    {
        if(isalpha(text[a]) == 0 || isspace(text[a]) == 0)
        {
            if(isalpha(text[a]) == 0)
            {
                int numMessage = c_to_n(text[a]) + 1;
                int numResult = (int)pow(numMessage, num1) % num2;
                for(int b = 0; b < sizeof(letters); b++)
                {
                    if(b == numResult)
                    {
                        newText[a] = letters[b];
                    }
                }
            }
            /*else if(isspace(text[a]) == 0)
            {
                int ran = (rand() % (26));
                newText[a] = letters[ran];
            }*/
        }
    }

    printf("Your encrypted message is: %s\n", newText);

    free(text);
}

void decrypt()
{
    int num1, num2;
    char *secText;
    char letters[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

    printf("Enter your ciphered text: \n");
    secText = inputString(stdin, 10);
    char newText[strlen(secText)];
    printf("Enter the two encryption numbers you want to choose. \n");
    printf("Enter the first number: \n");
    scanf("%2147483647d", &num1);
    printf("Enter the second number: \n");
    scanf("%2147483647d", &num2);
    
    fflush(stdin);
    //lowers text
    strlwr(secText);
    for(int a = 0; a < strlen(secText); a++)
    {
        for(int b = 0; b < sizeof(letters); b++)
        {
            if(secText[a] == letters[b])
            {
                int letterNum = b + 1;
                int result = fmod((float)powf(letterNum, num1), num2);
                //printf("%d\n", result);
                newText[a] = letters[result];
            }
        }
    }

    printf("Your decrypted message is: %s\n", newText);

    free(secText);
}

int main(void)
{
    int choice = 0;
    //while loop for options
    while(choice != 4)
    {
        printf("Choose an option:\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Generate Key\n");
        printf("4. Exit\n");
        scanf("%1d", &choice);
        fflush(stdin);
        if(choice == 1)
        {
            encrypt();
        }
        else if(choice == 2)
        {
            decrypt();
        }
    }
    return 0;
}