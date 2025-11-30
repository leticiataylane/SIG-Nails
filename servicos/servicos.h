#ifndef TELAS_SERVICOS_H
#define TELAS_SERVICOS_H

typedef struct Servico {
    char id[10];
    char nome[50];
    double preco;
    int status;
} Servico;

typedef struct listaServ {
    Servico serv;
    struct listaServ *prox;
} listaServ;

char modServico(void);
char menuServico(void);
void cadastrarServico(void);
void pesquisarServico(void);
void listarServicos(void);
void atualizarServico(void);
void excluirServico(void);
char* gerarIdServico(void);
int idExisteServico(char *idStr);

void telaCadastrarServico(void);
void telaAtualizarServico(void);
void telaPesquisarServico(void);
void telaExcluirServico(void);
void telaListarServico(void);

#endif