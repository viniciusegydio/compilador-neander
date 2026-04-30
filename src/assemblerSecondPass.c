#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/parser.h"

extern int getSymbolAddress(const char*);
extern unsigned char getOpcode(const char*);

unsigned char memory[256]; //Memória do neander

int isTwoByte(const char*); 

int resolve(const char *op){ //Transforma o operando(texto) em um valor numérico(endereço ou valor)
    if(isdigit(op[0])) return atoi(op); //Caso o operando seja um valor
    return getSymbolAddress(op); //Caso o operando seja um label
}

void generateMemFile(const char *filename){
    FILE *f = fopen(filename, "w");

    if(!f){
        printf("Erro ao criar arquivo .mem\n");
        exit(1);
    }

    for(int i = 0; i < 256; i++){
        fprintf(f, "%02X", memory[i]);

        if(i < 255)
            fprintf(f, " ");
    }

    fprintf(f, "\n");
    fclose(f);
}

void secondPass(){
    int addr = 0;
    ParsedLine l;
    memset(memory, 0, 256); //Zera todos os 256 endereços de memória do Neander

    while(1){
        l = parseLine();

        if(l.isEOF)
            break;
        
        if(l.opcode[0] == '\0' && l.label[0] == '\0')
            continue;
        
        if(!strcmp(l.opcode, "ORG"))
            addr = atoi(l.operand);
        
        else if(!strcmp(l.opcode, "DATA"))
            memory[addr++] = atoi(l.operand); //Reserva um byte 

        else if(!strcmp(l.opcode, "SPACE"))
            addr+= atoi(l.operand);

        else if(l.opcode[0]){
            memory[addr++] = getOpcode(l.opcode);
            if(isTwoByte(l.opcode)) //Se tiver 2 bytes, transforma o operando em um valor numérico
                memory[addr++] = resolve(l.operand);
        }
        generateMemFile("out.mem");
    }

}
