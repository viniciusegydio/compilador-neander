#include <string.h>
#include "../include/parser.h"
#include "../include/lexer.h"

extern Token obterProxToken();

ParsedLine parseLine(){
    ParsedLine line;
    memset(&line, 0, sizeof(line)); //Seta sizeof(line) bytes da variável line como o valor 0

    Token t = obterProxToken();

    if(t.tipo == TOKEN_EOL)
        return line;
    
    if(t.tipo == TOKEN_LABEL){
        strcpy(line.label, t.lexeme);
        line.hasLabel = 1;
        t = obterProxToken(); //Continua procurando pelos próximos tokens depois do label
    }

    if(t.tipo == TOKEN_MNEMONIC || t.tipo == TOKEN_DIRECTIVE)
        strcpy(line.opcode, t.lexeme);

    t = obterProxToken();

    if(t.tipo == TOKEN_IDENTIFIER || t.tipo == TOKEN_NUMBER){
        strcpy(line.operand, t.lexeme);
        line.hasOperand = 1;
    }

    while(t.tipo != TOKEN_EOL && t.tipo != TOKEN_EOF) //Garante que vai até o token de fim de linha ou fim de arquivo, caso exista lixo
        t = obterProxToken();

    return line;
}