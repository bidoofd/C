#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

//Let this be a test application an encryption system
//apparently we were right we just need to break it up

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

int isPrime(int number) {
    int i;
    for (i=2; i<number; i++) {
        if (number % i == 0 && i != number) return 0;
    }
    return 1;
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
        if(isalpha(text[a]) != 0 || isspace(text[a]) != 0)
        {
            if(isalpha(text[a]) != 0)
            {
                long double numResult = fmod(pow((int)text[a], num1), num2);
                newText[a] = letters[(int)numResult];
            }
            else if(isspace(text[a]) != 0)
            {
                int ran = (rand() % (26));
                newText[a] = letters[ran];
            }
        }
    }
    newText[strlen(text)] = '\0';

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
        int letterNum = (int)secText[a];
        printf("%d\n", letterNum);
        long double result = fmod(pow(letterNum, num1), num2);
        printf("%Lf\n", result);
        //newText[a] = letters[(int)result];
    }

    newText[strlen(secText)] = '\0';

    printf("Your decrypted message is: %s\n", newText);

    free(secText);
}

void generate()
{
    int number1, number2;
    int flag = 0;
    while(flag != 1)
    {  
        printf("Enter two prime numbers: \n");
        printf("Enter the first prime number: \n");
        scanf("%d", &number1);
        printf("Enter the second prime number: \n");
        scanf("%d", &number2);
        if(isPrime(number1) == 1 && isPrime(number2) == 1)
        {
            break;
        }
        else
        {
            printf("NOT VALID PRIME NUMBERS\n");
        }
    }

    //int phi = (num1 - 1) * (num2 - 1);


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
        else if(choice == 3)
        {
            generate();
        }
    }
    return 0;
}