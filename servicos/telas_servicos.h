#ifndef TELAS_SERVICOS_H 
#define TELAS_SERVICOS_H

typedef struct Servico {
    char id[10];
    char nome[50];
    float preco;
    int status;
} Servico;

char menuServico(void);
char modServico(void);
void atualizarCSVServicos();
void cadastrarServico();
void listarServicos();
void atualizarServico();
void excluirServico();
char* gerarIdServico(void);
int idExisteServico(char *idStr);



void telaCadastrarServico(void);
void telaAtualizarServico(void);
void telaPesquisarServico(void);
void telaExcluirServico(void);
void telaListarServico(void);
#endif