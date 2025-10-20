#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
// #include "cores.h"
#include "limpeza.h"
#include "validacoes.h"
#include "opera_funcionarios.h"
#include "ler_dados.h"
#include "telas_funcionarios.h"



int cadastrarFuncionario(void){
    FILE *fun;
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));

    char *nome = lerNome();
    strcpy(f->nome, nome);
    free(nome);

    char *cpf = lerCPF();
    strcpy(f->cpf, cpf);
    free(cpf);

    char *nascimento = lerIdade();
    strcpy(f->nascimento, nascimento);
    free(nascimento);

    char *telefone = lerTelefone();
    strcpy(f->telefone, telefone);
    free(telefone);

    char *email = lerEmail();
    strcpy(f->email, email);
    free(email);

    f->salario = lerSalario();

    f->status = True;

    fun = fopen("funcionarios.dat", "ab");
    if (fun == NULL) {
        perror("Erro ao abrir o arquivo");
        free(f);
        return 1;
    }
    fwrite(f, sizeof(Funcionario), 1, fun);
    fclose(fun);
    free(f);
    printf("\nDados salvos com sucesso em funcionarios.dat!\n");

    return 0;
}


void erroInvalido(void){
    system("clear");
    printf("Ocorreu algum erro, o conteúdo inserido é inválido. Por favor, tente novamente:\n");
}

int atualizarFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    int encontrado = False;

    char quemAtualizar[20];
    char oqAtualizar;

    FILE *fun;

    strcpy(quemAtualizar, lerCPF());

    fun = fopen("funcionarios.dat","r+b");
    while((fread(f, sizeof(Funcionario), 1, fun)) && (!encontrado)){
        if((strcmp(quemAtualizar, f->cpf) == 0) && (f->status)){
            do{
                oqAtualizar = telaOqueAtualizar();
                switch(oqAtualizar){
                    case '1':
                        char *nome = lerNome();
                        strcpy(f->nome, nome);
                        free(nome);
                        break;

                    case '2':
                        char *telefone = lerTelefone();
                        strcpy(f->telefone, telefone);
                        free(telefone);
                        break;
                    
                    case '3':
                        char *email = lerEmail();
                        strcpy(f->email, email);
                        free(email);
                        break;

                    case '4':
                        f->salario = lerSalario();
                        break;
                    default:
                        printf("invalido bobao\n");
                        break;
                }
            }while(oqAtualizar != '1' || oqAtualizar != '2' || oqAtualizar != '3' || oqAtualizar != '4');
            fseek(fun, (-1)*sizeof(Funcionario), SEEK_CUR);
            fwrite(f, sizeof(Funcionario), 1, fun);
            encontrado = True;
        }
        if((strcmp(quemAtualizar, f->cpf) == 0) && (!f->status)){
            printf("Não é possível atualizar dados.");
            encontrado = True;
        }
    }
    fclose(fun);
    free(f);
    if(!encontrado){
        printf("Nao encontrado");
    }
    
    return 0;
}

int pesquisarFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;

    int encontrado = False;
    char *cpf = lerCPF();

    fun = fopen("funcionarios.dat","rb");
    if (fun == NULL) {
    printf("Erro ao abrir o arquivo de funcionários.\n");
    free(f);
    return False;
    }

    while((fread(f, sizeof(Funcionario), 1, fun)) && (!encontrado)){
        if((strcmp(cpf, f->cpf) == 0) && (f->status)){
            printf("NOME: %s\nCPF: %s\nDATA DE NASCIMENTO: %s\nTELEFONE: %s\nEMAIL: %s\nSALARIO: %.2f\n", f->nome, f->cpf, f->nascimento, f->telefone, f->email, f->salario);
            encontrado = True;
        } else if((strcmp(cpf, f->cpf) == 0) && (!f->status)){
            printf("Vinculo inativo, funcionario excluido\n");
            encontrado = True;
        }
    }
    fclose(fun);
    free(f);
    if(!encontrado){
        printf("Não encontrado");
        return False;
    }

    return True;
}

int listarFuncionarios(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;

    fun = fopen("funcionarios.dat","rb");
    if(fun == NULL){
        printf("Erro ao abrir o arquivo.");
        free(f);
        return False;
    }

    while(fread(f, sizeof(Funcionario), 1, fun)){
        if(f->status){
            printf("├──────────────────────────────────────────────┤\n");
            printf("│ Nome: %-40s │\n", f->nome);
            printf("│ CPF: %-41s │\n", f->cpf);
            printf("│ Nascimento: %-34s │\n", f->nascimento);
            printf("│ Telefone: %-36s │\n", f->telefone);
            printf("│ E-mail: %-38s │\n", f->email);
            printf("│ Salário: %-36s │\n", f->salario);
        }
    }
    fclose(fun);
    free(f);
    return 0;
}




int excluirFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;

    int encontrado = False;
    char *cpf = lerCPF();

    fun = fopen("funcionarios.dat","r+b");
    if(fun == NULL){
        
    }

    while((fread(f, sizeof(Funcionario), 1, fun)) && (!encontrado)){
        if((strcmp(cpf, f->cpf) == 0) && (f->status)){
            printf("Funcionário: %s excluído\n", f->nome);
            f->status = False;
            fseek(fun, (-1)*sizeof(Funcionario), SEEK_CUR);
            fwrite(fun, sizeof(Funcionario), 1, fun);
            encontrado = True;
        } else if((strcmp(cpf, f->cpf) == 0) && (!f->status)){
            printf("Não encontrado");
            encontrado = True;
        }
    }
    fclose(fun);
    free(f);
    if(!encontrado){
        printf("Não encontrado");
    }

    return 0;

}

int excluirFuncionarioDefinitivo(void) {
    FILE *fun, *funTemp;
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));

    int encontrado = False;

    fun = fopen("funcionarios.dat", "rb");
    if (fun == NULL) {
        printf("Erro: não foi possível abrir o arquivo original.\n");
        return 1;
    }

    funTemp = fopen("temp.dat", "wb");
    if (funTemp == NULL) {
        printf("Erro: não foi possível criar o arquivo temporário.\n");
        fclose(fun);
        return 1;
    }

    char *cpf = lerCPF();

    while (fread(f, sizeof(Funcionario), 1, fun)) {
        if (strcmp(f->cpf, cpf) == 0) {
            encontrado = True;
            printf("Funcionário encontrado e excluído: %s\n", f->nome);
        } else {
            fwrite(&f, sizeof(Funcionario), 1, funTemp);
        }
    }

    fclose(fun);
    fclose(funTemp);

    // Se encontrou, substitui o arquivo original
    if (encontrado) {
        remove("funcionarios.dat");
        rename("temp.dat", "funcionarios.dat");
        printf("Exclusão realizada com sucesso.\n");
    } else {
        remove("temp.dat");
        printf("Nenhum funcionário encontrado com o CPF informado.\n");
    }

    return 0;
}