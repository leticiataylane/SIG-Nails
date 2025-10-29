#ifndef TELAS_CLIENTES_H 
#define TELAS_CLIENTES_H

typedef struct Cliente {
    char id[10];
    char nome[80];
    char dataNascimento[11];
    char telefone[20];
    int status;
} Cliente;

<<<<<<< HEAD

=======
>>>>>>> 48fee429b30f026078cbcd427d933508d8c35027
char modCliente(void);
void atualizarCSVClientes();
void cadastrarCliente();
void listarClientes();
void atualizarCliente();
void excluirCliente();
char menuCliente();
char* gerarIdCliente(void);
int idExisteCliente(char *idStr);


void telaCadastrarCliente(void);
void telaAtualizarCliente(void);
void telaPesquisarCliente(void);
void telaExcluirCliente(void);
void telaListarCliente(void);
<<<<<<< HEAD
=======

>>>>>>> 48fee429b30f026078cbcd427d933508d8c35027

#endif