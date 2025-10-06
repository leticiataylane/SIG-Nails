#ifndef OPERA_FUNCIONARIOS_H
#define OPERA_FUNCIONARIOS_H

typedef struct {
    char cpf[20];
    char nome[60];
    char nascimento[15];
    char telefone[20];
    char email[70];
    char turno[10];
    float salario;
    char situacao[10];
} Funcionario;

int cadsFuncionario(void);
int atualizaFuncionario(void);
int excluirFuncionario(void);

#endif
