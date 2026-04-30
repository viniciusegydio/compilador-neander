#include <stdio.h>
#include <stdlib.h>

extern unsigned char memory[256];

unsigned char AC = 0, PC = 0, IR = 0; 
unsigned char N = 0, Z = 0;

void flags(){
    Z = (AC == 0);
    N = (AC & 0x80) != 0; //Comparação AND bit a bit que verifica se o bit mais signficativo está ligado(complemento de dois)
}

void runProgram(){ 
    int run = 1;

    for(int i = 0; i < 20; i++){
        printf("%02X ", memory[i]);
    }
    printf("\n");

    while(run){ //Ciclo de execução da CPU(fetch -> decode -> execute)
        IR = memory[PC++]; //Instrução atual(fetch)

        unsigned char opcode = IR & 0xF0;
        unsigned char a; //Operando da instrução(endereço)

        switch(opcode){ //decode e execute
            case 0x20: a = memory[PC++]; AC = memory[a]; break; //LDA
            case 0x10: a = memory[PC++]; memory[a] = AC; break; //STA
            case 0x30: a = memory[PC++]; AC+=memory[a]; break; //ADD
            case 0x70: AC=~AC; break; //NOT
            case 0x80: a = memory[PC++]; PC =a; break; //JMP
            case 0xF0: run = 0; break; //HLT

            default:
                printf("Opcode invalido: %02X em PC:%02X\n", opcode, PC-1);
                run = 0;
                break;
        }
        flags();
        printf("PC:%02X AC:%02X\n", PC, AC); //"%02X": hexadecimal
    }
}
