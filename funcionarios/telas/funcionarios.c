#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"
#include "limpeza.h"
#include "validacoes.h"
#include "funcionarios.h"
#include "ler_dados.h"


char modFuncionario(void){
    char opFuncionario;

    do{
        opFuncionario = menuFuncionario();
        switch (opFuncionario)
        {
        case '1':
            telaCadastrarFuncionario();
            break;

        case '2':
            telaAtualizarFuncionario();
            break;

        case '3':
            telaPesquisarFuncionario();
            break;

        case '4':
            telaListarFuncionarios();
            break;

        case '5':
            telaExcluirFuncionario();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (opFuncionario != '0');

    return opFuncionario;
}

char menuFuncionario(void){
    char op;

    printf("ÁREA DO Funcionario\n");
    printf("___________________");
    printf("1.cadastrar\n");
    printf("2.atualizar\n");
    printf("3.pesquisar\n");
    printf("4.listar\n");
    printf("5.excluir\n");
    printf("0.sair\n");

    op = opcao();


}

void telaCadastrarFuncionario(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│     DADOS PARA O CADASTRO DE FUNCIONÁRIOS    │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│ Nome:                                        │\n" );
    printf("│ CPF:                                         │\n");
    printf("│ Nascimento:                                  │\n");
    printf("│ Telefone:                                    │\n");
    printf("│ E-mail:                                      │\n");
    printf("│ Salário:                                     │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    cadastrarFuncionario();
    printf("|ENTER| para sair\n");
    getchar();

}



void telaAtualizarFuncionario(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             ATUALIZAR FUNCIONÁRIO            │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   A operação de atualização só será efetiva  │\n" );
    printf("│   se o funcionário estiver cadastrado e com  │\n");
    printf("│   vínculo ativo.                             │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    atualizarFuncionario();
    printf("|ENTER| para sair\n");
    getchar();
    
}

void telaPesquisarFuncionario(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             PESQUISAR FUNCIONÁRIO            │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   Para pesquisar um funcionário, informe o   │\n" );
    printf("│   CPF do mesmo.                              │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    pesquisarFuncionario();
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaListarFuncionario(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│              LISTAR FUNCIONÁRIOS             │\n");
    listarFuncionarios();
    printf("╰──────────────────────────────────────────────╯\n");
    
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaExcluirFuncionario(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│              EXCLUIR FUNCIONÁRIO             │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   [1] Exclusão Lógica                        │\n");
    printf("│   [2] Exclusão definitiva                    │\n");
    printf("│   [0] Sair                                   │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    do{
        op = opcao();
        switch (op)
        {
        case '1':
            excluirFuncionario();
            break;

        case '2':
            excluirFuncionarioDefinitivo();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (op != '0');

    printf("|ENTER| para sair\n");

    getchar();
    
}


char telaOqueAtualizar(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            O QUE DESEJA ATUALIZAR?           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] NOME                                    │\n" );
    printf("│  [2] TELEFONE                                │\n");
    printf("│  [3] EMAIL                                   │\n");
    printf("│  [4] SALÁRIO                                 │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();

}


///////////////////////////////////////////////////////////OPERACOES////////////////////////////////////////////////////////////////////////////////



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