#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct{
    char name[20];
    int value;
    int init;
}Var; //Variável do pseudo-código

Var vars[20];
int vcount = 0;

int find(char *n){
    for(int i = 0; i < vcount; i++){
        if(!strcmp(vars[i].name, n))
            return i;
    }
    return -1;
}

void generateFromPseudo(const char *code){ //Transforma pseudo-linguagem em assembly do Neander)
    FILE *f = fopen("out.asm", "w");
    fprintf(f, "ORG 0\n");

    char buff[500];
    strcpy(buff, code);

    char *line = strtok(buff, "\n"); //Quebra o buffer em linhas

    while(line){
        //var: resultado; op1[20]: primeiro operando; op2[20]: segundo operando; op: operador
        char var[20], op1[20], op2[20], op; 

        if(sscanf(line, "%[^=]=%s %c %s", var, op1, &op, op2) == 4){ //Divide a string nas 4 variáveis usando o "%[^=]=%s %c %s" como formato
            if(op == '+'){
                fprintf(f,"LDA %s\nADD %s\nSTA %s\n",op1, op2, var);
            }
            else if(op == '-'){ //Subtração negando e somando 1 
                fprintf(f, "LDA %s\nNOT\nAdd ONE\nSTA TEMP\n"
                "LDA %s\nADD TEMP\nSTA %s\n",
                op2, op1, var);
            }
        } 
        else if(sscanf(line, "%[^=]=%s", var, op1) == 2){
            vars[vcount].init = 1;
            strcpy(vars[vcount].name, var);
            vars[vcount++].value = atoi(op1);
        }
        line = strtok(NULL, "\n");
    }

    fprintf(f, "\n");
    for(int i = 0; i<vcount; i++)
        fprintf(f,"%s: DATA %d\n",vars[i].name,vars[i].value);

    fprintf(f,"ONE: DATA 1\nTEMP: SPACE 1\n");
    fclose(f);
}