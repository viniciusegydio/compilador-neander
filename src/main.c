#include <stdio.h>
#include <stdlib.h>
#include "../include/pseudoParser.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/assemblerFirstPass.h"
#include "../include/assemblerSecondPass.h"
#include "../include/executor.h"

void firstPass();
void secondPass();
void runProgram();

extern unsigned char memory[256];

char* readFile(const char* f){
    FILE *fp= fopen(f,"r");

    if(!fp){
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    fseek(fp,0,SEEK_END);
    int sz= ftell(fp);
    rewind(fp);

    char *buf= malloc(sz+1);
    fread(buf,1,sz,fp);
    buf[sz]=0;
    fclose(fp);
    return buf;
}

int main(){
    const char *input =
        "A = 10\n"
        "B = 20\n"
        "R = A + B\n";

    printf("1\n");
    generateFromPseudo(input);
    printf("2\n");

    char *code=readFile("out.asm");

    initLexer(code);
    printf("3\n");

    firstPass();
    printf("4\n");

    initLexer(code);
    printf("5\n");
    
    secondPass();
    printf("6\n");
    
    runProgram();
    printf("7\n");

    free(code);
}