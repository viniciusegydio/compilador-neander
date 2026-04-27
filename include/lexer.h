#ifndef LEXER_H
#define LEXER_H

typedef enum{
    TOKEN_LABEL, //Rótulo de memória usado para marcar um endereço
    TOKEN_MNEMONIC, //Instruções da máquina como LDA, ADD, STA e HLT
    TOKEN_DIRECTIVE, //Comandos do assembler não executados pela CPU(ORG, DATA, SPACE...) que organizam a memória
    TOKEN_NUMBER, //Números literais
    TOKEN_IDENTIFIER, //Nome de alguma coisa, como um label utilizado como referência
    TOKEN_EOL, //Fim de linha, utilizado para separar instruções
    TOKEN_EOF //Fim de arquivo para parar o lexer/parser
}tipoToken;

typedef struct{
    tipoToken tipo;
    char lexeme[64]; //Suficiente 
}Token;

void initLexer(const char *source);
Token obterProxToken();

#endif