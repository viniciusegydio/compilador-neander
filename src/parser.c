#include <string.h>
#include "../include/parser.h"
#include "../include/lexer.h"

extern Token obterProxToken();

ParsedLine parseLine(){
    ParsedLine line;
    memset(&line, 0, sizeof(line));

    Token t = obterProxToken();

    if(t.tipo == TOKEN_EOF){
        line.isEOF = 1;
        return line;
    }

    if(t.tipo == TOKEN_EOL)
        return line;
    
    if(t.tipo == TOKEN_LABEL){
        strcpy(line.label, t.lexeme);
        line.hasLabel = 1;
        t = obterProxToken();
    }

    if(t.tipo == TOKEN_MNEMONIC || t.tipo == TOKEN_DIRECTIVE)
        strcpy(line.opcode, t.lexeme);

    t = obterProxToken();

    if(t.tipo == TOKEN_IDENTIFIER || t.tipo == TOKEN_NUMBER){
        strcpy(line.operand, t.lexeme);
        line.hasOperand = 1;
    }

    while(t.tipo != TOKEN_EOL && t.tipo != TOKEN_EOF)
        t = obterProxToken();

    return line;
}