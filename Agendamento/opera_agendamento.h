#ifndef OPERA_AGENDAMENTO_H
#define OPERA_AGENDAMENTO_H
#define True 1
#define False 0

typedef struct {
    int agendamentoID;
    int clienteID;
    int servicoID;
    char data[15];
    char hora[10];
    // char funcionario[20];
    // char situacao[15];
    int status;
} Agendamento;

int cadastrarAgendamento(void);
int atualizarAgendamento(void);
int pesquisarAgendamento(void);
int listarAgendamentos(void);
int excluirAgendamento(void);

#endif