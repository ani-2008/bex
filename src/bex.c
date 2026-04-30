#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_SIZE 4096

typedef enum{
    VAL, AND, OR, NOT, LPARA, RPARA
}Tokens;

struct Token{
    Tokens tok;
    int value; 
};

struct Token tokens[MAX_SIZE];
int tokens_ptr = 0;
int current_tokens_index = 0;

int parse_or();
int parse_and();
int parse_val();

int parse_val()
{
    if(tokens[current_tokens_index].value == 0 || tokens[current_tokens_index].value == 1){
        return tokens[current_tokens_index++].value;
    
    }else if(tokens[current_tokens_index].tok == 4){
        current_tokens_index++;
        int result = parse_or();
        if(tokens[current_tokens_index++].tok == 5){
            return result;
        }

    }else{
        while(tokens[current_tokens_index].tok == 3){
            current_tokens_index++;
            int x = parse_val();
            return !x;
        }
    }
}


int parse_and()
{
    int result = parse_val();
    
    while(tokens[current_tokens_index].tok == 1){
        current_tokens_index++;
        int next_val = parse_val();

        result = result && next_val;
    }

    return result;
}

int parse_or()
{
    int result = parse_and();

    while(tokens[current_tokens_index].tok == 2){
        current_tokens_index++;
        int next_val = parse_and();
        
        result = result || next_val;
    }
    return result;
}


int lexer(char *s)
{
    while(*s != '\0'){
        if(*s == ' ' || *s == '\n'){
            ;
        }else if(*s == '0' || *s == '1'){
            tokens[tokens_ptr++] = (struct Token){.tok = VAL, .value = *s - '0'};
        }else if(*s == '.'){
            tokens[tokens_ptr++] = (struct Token){.tok = AND, .value = -1};
        }else if(*s == '+'){
            tokens[tokens_ptr++] = (struct Token){.tok = OR, .value = -1};
        }else if(*s == '~'){
            tokens[tokens_ptr++] = (struct Token){.tok = NOT, .value = -1};
        }else if(*s == '('){
            tokens[tokens_ptr++] = (struct Token){.tok = LPARA, .value = -1};
        }else if(*s == ')'){
            tokens[tokens_ptr++] = (struct Token){.tok = RPARA, .value = -1};
        }else{
            return -1;
        }
        s++;
    }
    return 0;
}

int main()
{
    char *buff = NULL;
    size_t len = 0;
    ssize_t bytes_read;
    do {
        printf("> ");
        bytes_read = getline(&buff, &len, stdin);
        if(bytes_read == -1){
            printf("\n");
            break;
        }
        if(lexer(buff) == 0){
            if(!(*buff == '\0' || *buff == '\n')){
                int x = parse_or();
                printf("%d\n",x);
                tokens_ptr = 0;
                current_tokens_index = 0;
            }
        }else{printf("ERROR: UNEXPECTED CHARACTER !!!!\n");}
    }while( ( strcmp(buff,"quit\n")!=0 && strcmp(buff,"exit\n")!=0 ));

    free(buff);
}
