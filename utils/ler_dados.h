#ifndef LER_DADOS_H
#define LER_DADOS_H

char opcao(void);
void esperarEnter();
char* lerString(const char* msg);

char* lerNome(void);
char* lerCPF(void);

char* lerNascimento(void);
char* lerIdade(void);
char* lerData(void);

char* lerHorario(void);

char* lerTelefone(void);
char* lerEmail(void);

float lerDinheiro(void);
float lerSalario(void);

char* lerIdAgendamento(void);
char* lerIdServico(void);
char* lerIdCliente(void);

char* lerSituacao(const char* horario, const char* data, const char* situacao);


#endif