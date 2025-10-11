#ifndef TELAS_CLIENTES_H 
#define TELAS_CLIENTES_H

typedef struct Cliente {
    int id;
    char nome[80];
    char dataNascimento[11];
    char telefone[20];
    int status;
} Cliente;

void menu(void);
void cadastrarCliente(void);
void atualizarCliente(void);
void listarClientes(void);
void excluirCliente(void);
void atualizarCSVClientes(void);

#endif