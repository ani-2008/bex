#include <stdio.h>
#include <string.h>
#define MAX_SIZE 4096

typedef enum{
    VAL, AND, OR, NOT
}Tokens;

struct Token{
    Tokens tok;
    int value; 
};

struct Token tokens[MAX_SIZE];
int tokens_ptr = 0;

void lexer(char *s)
{
    while(*s != '\0'){
        if(*s == ' '){
            ;
        }else if(*s == '0' || *s == '1'){
            tokens[tokens_ptr++] = (struct Token){.tok = VAL, .value = *s - '0'};
        }else if(*s == '.'){
            tokens[tokens_ptr++] = (struct Token){.tok = AND, .value = -1};
        }else if(*s == '+'){
            tokens[tokens_ptr++] = (struct Token){.tok = OR, .value = -1};
        }else if(*s == '~'){
            tokens[tokens_ptr++] = (struct Token){.tok = NOT, .value = -1};
        }
        s++;
    }
}

int main()
{
    char *buff;
    while(strcmp(buff,"quit\n")!=0 && strcmp(buff,"exit\n")!=0){
        printf("> ");
        fgets(buff,MAX_SIZE,stdin);
        lexer(buff);
    }
}
