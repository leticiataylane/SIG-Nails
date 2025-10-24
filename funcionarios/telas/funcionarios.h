#ifndef TELAS_FUNCIONARIOS_H 
#define TELAS_FUNCIONARIOS_H
#define True 1
#define False 0

typedef struct {
    char cpf[20];
    char nome[60];
    char nascimento[15];
    char telefone[20];
    char email[70];
    float salario;
    int status;
} Funcionario;

int cadastrarFuncionario(void);
int atualizarFuncionario(void);
int pesquisarFuncionario(void);
int listarFuncionarios(void);
int excluirFuncionario(void);


char modFuncionario(void);
char menuFuncionario(void);
void telaCadastrarFuncionario(void);
void telaAtualizarFuncionario(void);
void telaPesquisarFuncionario(void);
void telaListarFuncionario(void);  
void telaExcluirFuncionario(void);
char telaOqueAtualizar(void);

#endif