#include <stdio.h>
#include <stdlib.h>
#include "../include/pseudoParser.h"
#include "../include/parser.h"
#include "../include/lexer.h"
#include "../include/assemblerFirstPass.h"
#include "../include/assemblerSecondPass.h"
#include "../include/executor.h"

void generateFrompseudo(const char*);
void firstpass();
void secondPass();
void runProgram();
void initlexer(const char*);
extern unsigned char memory[256];

char* readFile(const char* f){
    FILE *fp= fopen(f,"r");
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

    generateFromPseudo(input);

    char *code=readFile("out.asm");

    initLexer(code);
    firstPass();

    initLexer(code);
    secondPass();

    runProgram();

    free(code);
}