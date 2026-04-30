#ifndef PARSER_H
#define PARSER_H

typedef struct {
    char label[50]; //Nome do label
    char opcode[10]; //Instrução(mnemonico ou diretiva)
    char operand[50]; //Operando(pode não existir)
    int hasLabel; //Indica se existe um label na linha
    int hasOperand; //Indica se existe um operando
    int isEOF; 
}ParsedLine;

ParsedLine parseLine();

#endif