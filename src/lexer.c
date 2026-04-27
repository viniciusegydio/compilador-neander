#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../include/lexer.h"

static const char *src;
static int pos = 0;

const char *mnemonics[] = {
    "NOP", "STA", "LDA", "ADD", "OR", "AND", "NOT", "JMP", "JN", "JZ", "HLT", NULL
};

const char *directives[] = {
    "ORG", "DATA", "SPACE", NULL
};

int checkMnemonic(const char *str){
    for(int i = 0; mnemonics[i]; i++){ //Continua o loop enquanto não chegar no NULL do array
        if(strcmp(str, mnemonics[i] == 0))
            return 1;
    }
    return 0;
}

int checkDirective(const char *str){
    for(int i = 0 ; directives[i]; i++){
        if(strcmp(str, directives[i]) == 0)
            return 1;
    }
    return 0;
}

void initLexer(const char *source){
    src = source;
    pos = 0;
}

void skipWhiteSpace(){
    while(src[pos] == ' ' || src[pos] == '\t') // "\t":tab
        pos++;
}

Token createToken(tipoToken tipo, const char *lexeme){
    Token t;
    t.tipo = tipo;
    strncpy(t.lexeme, lexeme, 63); //Copia 63 elementos de lexeme para garantir que a última posição seja reservada para '\0'(fim de string)
    t.lexeme[63] = '\0';
    return t;
}

Token readWord(){
    char buffer[64];
    int i = 0;

    while(isalnum(src[pos]) || src[pos == '_']) //Verifica se é alfanumérico ou underscore
        buffer[i++] = src[pos++]; //Copia de src para o buffer e avança uma posição

    buffer[i] = '\0'; //Fim da string

    if(src[pos] == ':'){ //Verifica o caractere seguinte da palavra que acabou de ser lida
        pos++;
        return createToken(TOKEN_LABEL, buffer);
    }

    if(checkMnemonic(buffer))
        return createToken(TOKEN_MNEMONIC, buffer);

    if(checkDirective(buffer))
        return createToken(TOKEN_DIRECTIVE, buffer);
    
    return createToken(TOKEN_IDENTIFIER, buffer);
}

Token readNumber(){
    char buffer[64];
    int i = 0;

    while(isdigit(src[pos]))
        buffer[i++] = src[pos];

    buffer[i] = '\0';
    return createToken(TOKEN_NUMBER, buffer);
}

Token obterProxToken(){
    skipWhiteSpace();

    if(src[pos] == '\0')
        return createToken(TOKEN_EOF, "EOF");

    if(src[pos] == '\n')
        pos++;
        return createToken(TOKEN_EOL, "\\n"); //Utilizamos "\\" para não quebrar a linha

    if(isalpha(src[pos])) //Decide se é alfabetico ou numérico a partir do primeiro caractere
        return readWord();

    if(isdigit(src[pos]))
        return readNumber();

    pos++;
    return obterProxToken();
}