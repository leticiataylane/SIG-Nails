#ifndef VALIDACOES_H
#define VALIDACOES_H

#define True 1
#define False 0
int validaDiaDoMes(char* dataInserida);
int validaDataInserida(char *dataInserida);
int validaHorario(char *horario);
int validaNascimento(char *nascimento);
int validaIdade(char *nascimento);
int validaCPF(char *cpf);
int validaEmail(char *email);
int validaNome(char *nome);
int validaNomeCurto(char *str);
int validaTelefone(char *telefone);
int validaSituacao(const char* horario, const char* data, int situacao, const char op);

#endif