#ifndef FUNCIONARIOS_H 
#define FUNCIONARIOS_H
#define True 1
#define False 0

typedef struct {
    char cpf[20];
    char id[6];
    char nome[60];
    char nascimento[15];
    char telefone[20];
    char email[70];
    float salario;
    int status;
} Funcionario;

char modFuncionario(void);
char menuFuncionario(void);
void telaCadastrarFuncionario(void);
void telaAtualizarFuncionario(void);
void telaPesquisarFuncionario(void);
void telaListarFuncionarios(void);
void telaExcluirFuncionario(void);
char telaOqueAtualizar(void);
///////////////////////////////////////////////////////////OPERACOES////////////////////////////////////////////////////////////////////////////////



int cadastrarFuncionario(void);
int atualizarFuncionario(void);
int pesquisarFuncionario(void);
int listarFuncionarios(void);
int excluirFuncionario(void);
int excluirFuncionarioDefinitivo(void);

int telaFuncionariosDisponiveis(char funcionariosDisp[10][5], char *data, char *horario);
char* gerarIdFuncionario(void);
int idExisteFuncionario(char *idStr);
int idFuncionarioDisp(char funcionariosDisp[10][5], const char *idChar);

#endif