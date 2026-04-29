#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/parser.h"

extern getSymbolAddress(const char*);
extern unsigned char getOpcode(const char*);

unsigned char memory[256]; //Memória do neander

int isTwoByte(const char*); 

int resolve(const char *op){ //Transforma o operando(texto) em um valor numérico(endereço ou valor)
    if(isdigit(op[0])) return atoi(op); //Caso o operando seja um valor
    return getSymbolAddress(op); //Caso o operando seja um label
}

void secondPass(){
    int addr = 0;
    ParsedLine l;
    memset(memory, 0, 256); //Zera todos os 256 endereços de memória do Neander

    while(1){
        l = parseLine();

        if(l.opcode[0] == '\0' && l.label[0] == '\0')
            break;
        
        if(!strcmp(l.opcode, "ORG"))
            addr = atoi(l.operand);
        
        else if(!strcmp(l.opcode, "DATA"))
            memory[addr++] == atoi(l.operand); //Reserva um byte 

        else if(!strcmp(l.opcode, "SPACE"))
            addr+= atoi(l.operand);

        else if(l.opcode[0]){
            memory[addr++] = getOpcode(l.opcode);
            if(isTwoByte(l.opcode)) //Se tiver 2 bytes, transforma o operando em um valor numérico
                memory[addr++] = resolve(l.operand);
        }
    }

}