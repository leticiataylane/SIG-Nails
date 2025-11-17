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
void cabecarioRelatorioServico(const char op);
void relatorioServico(const char op);
////////////////////////////////////////////////////////////////////CLIENTES////////////////////////////////////////////////////////////////////////////


char modRelatorioCliente(void);
char menuRelatorioCliente(void);
void printRelatCliente(Cliente *c);
void cabecarioRelatorioCliente(const char op);
void relatorioCliente(const char op);
////////////////////////////////////////////////////////////////FUNCIONARIOS////////////////////////////////////////////////////////////////////////////


char modRelatorioFuncionario(void);
char menuRelatorioFuncionario(void);
void printRelatFuncionario(Funcionario *f);
void cabecarioRelatorioFuncionario(const char op);
void relatorioFuncionario(const char op);

#endif