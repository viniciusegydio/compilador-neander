#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char *mnemonic;
    unsigned char opcode; //1 byte, perfeiro para o Neander
}Instruction;

Instruction table[] = {
    {"NOP", 0x00},{"STA", 0x10},{"LDA", 0x20},{"ADD", 0x30},
    {"OR", 0x50},{"AND", 0x60},{"NOT", 0x70},
    {"JMP", 0x80},{"JN", 0x90},{"JZ", 0xA0},{"HLT", 0xF0},{NULL, 0}
};

unsigned char getOpcode(const char *m){
    for(int i = 0; table[i].mnemonic; i ++){
        if(strcmp(table[i].mnemonic, m) == 0)
            return table[i].opcode;
    }
    printf("O opcode e invalido\n");
    exit(1);
}