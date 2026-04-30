#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "../include/parser.h"

extern void addSymbol(const char *, int); //Evita erro de múltiplas definições

int isTwoByte(const char *op){
    return !(!strcmp(op, "NOP") || !strcmp(op, "NOT") || !strcmp(op, "HLT")); //Se não tiver operando, tem 1 byte, senão, tem 2 bytes
}

void firstPass(){
    int addr = 0;
    ParsedLine l;

    while(1){
        l = parseLine();

        if(l.isEOF)
            break;
        
        if(l.opcode[0] == '\0' && l.label[0] == '\0')
            continue;

        if(l.hasLabel) //Adiciona a tabela de símbolos se tiver label
            addSymbol(l.label, addr);

        if(!strcmp(l.opcode, "ORG")) //Começa a escrever em um endereço de memória específico
            addr = atoi(l.operand); //Transforma ASC2 em inteiro

        else if(!strcmp(l.opcode, "DATA"))
            addr++; //Reserva um espaço de memória

        else if(!strcmp(l.opcode, "SPACE"))
            addr+= atoi(l.operand); //Reserva vários espaços de memóri a
        
        else if(l.opcode[0])
            addr += isTwoByte(l.opcode) ? 2 : 1; //Adiciona um ou dois bytes dependendo se tiver operando
    }
}