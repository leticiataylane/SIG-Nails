#ifndef TELAS_SERVICOS_H 
#define TELAS_SERVICOS_H

typedef struct Servico {
    int id;
    char nome[50];
    float preco;
    int status;
} Servico;

void menuServico(void);
void cadastrarServico(void);
void atualizarServico(void);
void listarServicos(void);
void excluirServico(void);
void atualizarCSVServicos(void);

#endif