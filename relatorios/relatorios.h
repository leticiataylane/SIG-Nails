#ifndef RELATORIOS_H
#define RELATORIOS_H


char modRelatorios(void);
char menuRelatorios(void);
///////////////////////////////////////////////////////////AGENDAMENTOS////////////////////////////////////////////////////////////////////////
char modRelatorioAgendamento(void);
char menuRelatorioAgendamento(void);
void printRelatAgendamento(Agendamento *a);
void cabecarioRelatorioAgendamento(const char op);
void relatorioAgendamento(const char op);


/////////////////////////////////////////////////////SERVICOS/////////////////////////////////////////////////////////////////////

char modRelatorioServico(void);
char menuRelatorioServico(void);
void printRelatServico(Servico *s);
void cabecalhoRelatorioServico(const char op);
void relatorioServico(const char op);
listaServ* inserirServicoOrdenado(listaServ *lista, Servico novo, int crescente);
void relatorioPrecoServico(void);
void liberarListaServ(listaServ *lista);


////////////////////////////////////////////////////////////////////CLIENTES////////////////////////////////////////////////////////////////////////////

char modRelatorioCliente(void);
char menuRelatorioCliente(void);
void cabecalhoRelatorioCliente(char op);
void printRelatCliente(Cliente *c);
listaCliente* inserirClienteFim(listaCliente* lista, Cliente cli);
listaCliente* inserirClienteInicio(listaCliente* lista, Cliente cli);
void liberarListaCliente(listaCliente* lista);
int temResultadosClienteLista(char op, listaCliente* lista);
void relatorioCliente(const char op);
void relatorioHistoricoCliente(void);


////////////////////////////////////////////////////////////////FUNCIONARIOS////////////////////////////////////////////////////////////////////////////

char modRelatorioFuncionario(void);
char menuRelatorioFuncionario(void);
void printRelatFuncionario(listaFunc* lista);
void cabecarioRelatorioFuncionario(const char op);
void relatorioFuncionario(const char op);
listaFunc* listaInvertidaFuncionario(Funcionario f, listaFunc* lista);
void liberaListaFunc(listaFunc* lista);
listaFunc* listaAlfabeticaFuncionario(Funcionario f, listaFunc* lista);


void liberarListaAgen(listaAgen* lista);
void printRelatAgendamentoListas(listaAgen* lista);
listaAgen* listaDataAgendamento(Agendamento a, listaAgen* lista);



#endif