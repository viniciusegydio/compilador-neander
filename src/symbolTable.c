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
        if(strcmp(table[i].label, label) == 0){
            printf("Essa label ja existe na tabela");
            exit(1);
        }
    }
    strcpy(table[count].label, label);
    table[count++].address = addr;
}

int getSymbolAddress(const char *label){
    for(int i = 0; i < count; i++){
        if(strcmp(table[i].label, label) == 0)
            return table[i].address;
    }
    printf("Label nao encontrado na tabela\n");
    exit(1);
}