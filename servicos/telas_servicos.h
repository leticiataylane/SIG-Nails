#ifndef TELAS_SERVICOS_H 
#define TELAS_SERVICOS_H

typedef struct servico {
    int id;
    char nome[50];
    float preco;
    int status;
} Servico;

void menuServico(void);
void cadastrarServico(void);
void listarServicos(void);
void atualizarServico(void);
void excluirServico(void);
int gerarNovoIdServico(void);

#endif