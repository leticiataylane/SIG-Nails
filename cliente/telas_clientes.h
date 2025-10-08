#ifndef TELAS_CLIENTES_H 
#define TELAS_CLIENTES_H

typedef struct cliente {
    char nome[80];
    char dataNascimento[11];
    char telefone[20];
} Cliente;

char modCliente(void);
char menuCliente(void);
void telaCadastrarCliente(void);
void telaAtualizarCliente(void);
void telaPesquisarCliente(void);
void telaExcluirCliente(void);

#endif