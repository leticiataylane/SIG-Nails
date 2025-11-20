#ifndef AGENDAMENTOS_H 
#define AGENDAMENTOS_H

#define True 1
#define False 0



typedef struct {
    char agenId[10];
    char clienteId[10];
    char servicoId[10];
    char data[15];
    char horario[10];
    char funcionario[6];
    float preco;
    char situacao[15];
    int status;
} Agendamento;


char modAgendamento(void);

int cadastrarAgendamento(void);
int atualizarAgendamento(void);
int pesquisarAgendamento(void);
int listarAgendamentos(void);
int excluirAgendamento(void);
int excluirAgendamentoDefinitivo(void);


char menuAgendamento(void);

void telaCadastrarAgendamento(void);
void telaAtualizarAgendamento(void);
void telaPesquisarAgendamento(void);
void telaListarAgendamentos(void);
void telaExcluirAgendamento(void);
char telaHorario(void);

void printAgendamento(Agendamento *a);

char telaSituacao(void);

char* gerarIdAgendamento(void);
int idExisteAgendamento(char *idStr);
char* getNomeCli(char *id);
char* getNomeServ(char *id);
int contaServicosAtivos(void);
int contaClientesAtivos(void);

#endif