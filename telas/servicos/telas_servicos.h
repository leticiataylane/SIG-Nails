#ifndef TELAS_SERVICOS_H 
#define TELAS_SERVICOS_H

typedef struct servico {
    char nome[50];
    float preco;
} Servico;

char modServico(void);
char menuServico(void);
void telaCadastrarServico(void);
void telaAtualizarServico(void);
void telaPesquisarServico(void);
void telaExcluirServico(void);

#endif