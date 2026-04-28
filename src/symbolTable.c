#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char label[50];
    int address;
}Symbol;

Symbol table[100];
int count = 0;

void addSymbol(const char *label, int addr){
    for(int i = 0; i < count; i++){
        if(strcmp(table[i].label, label) == 0){ //Verifica se o label já não foi inserido na tabela
            printf("Essa label já existe na tabela");
            exit(1); //Encerra o programa devido a duplicação de label
        }
        strcpy(table[count].label, label);
        table[count++].address = addr; //Utiliza o índice count antes de incrementar;
    }
}

int getSymbolAddress(const char *label){
    for(int i = 0; i < count; i++){
        if(strcmp(table[i].label, label) == 0)
            return table[i].address;
    }
    printf("Label não encontrado na tabela\n");
    exit(1);
}