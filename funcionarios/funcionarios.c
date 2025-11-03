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
#include "erros.h"
//

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
            opcaoInvalida();
            break;
        }
    }while (opFuncionario != '0');

    return opFuncionario;
}

char menuFuncionario(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│              ÁREA DO FUNCIONÁRIO             │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] CADASTRAR                               │\n" );
    printf("│  [2] ATUALIZAR                               │\n");
    printf("│  [3] PESQUISAR                               │\n");
    printf("│  [4] LISTAR                                  │\n");
    printf("│  [5] EXCLUIR                                 │\n");
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;


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
    esperarEnter();

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
    esperarEnter();
    
}

void telaPesquisarFuncionario(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             PESQUISAR FUNCIONÁRIO            │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   Para pesquisar um funcionário, informe o   │\n" );
    printf("│   CPF do mesmo.                              │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    pesquisarFuncionario();
    esperarEnter();
    
}

void telaListarFuncionarios(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             LISTA DE FUNCIONÁRIOS            │\n");
    listarFuncionarios();
    printf("╰──────────────────────────────────────────────╯\n");
    

    esperarEnter();
    
}

void telaExcluirFuncionario(void){
    char op;
    do{
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│              EXCLUIR FUNCIONÁRIO             │\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│   [1] Exclusão Lógica                        │\n");
        printf("│   [2] Exclusão definitiva                    │\n");
        printf("│   [0] Sair                                   │\n");
        printf("╰──────────────────────────────────────────────╯\n");
        op = opcao();
        switch (op)
        {
        case '1':
            excluirFuncionario();
            op = '0';
            break;

        case '2':
            excluirFuncionarioDefinitivo();
            op = '0';
            break;

        case '0':
            break;

        default:
            opcaoInvalida();
            break;
        }
    }while (op != '0');
    esperarEnter();
    
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
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;

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

    printf("╭──────────────────────────────────────────────╮\n");
    printf("│                  FUNCIONÁRIO                 │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│ Nome: %-38s │\n", f->nome);
    printf("│ CPF: %-39s │\n", f->cpf);
    printf("│ Data: %.2s/%.2s/%.4s                             │\n", f->nascimento, f->nascimento + 2, f->nascimento + 4);
    printf("│ Telefone: (%.2s) %.1s %.4s-%.4s                   │\n",  f->telefone, f->telefone + 2,  f->telefone + 3, f->telefone + 7);
    printf("│ E-mail: %-36s │\n", f->email);
    printf("│ Salário: R$%-33.2f │\n", f->salario);
    printf("╰──────────────────────────────────────────────╯\n");

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


int atualizarFuncionario(void){
    FILE *fun;
    Funcionario* f = (Funcionario*) malloc(sizeof(Funcionario));
    int encontrado = False;
    char quemAtualizar[20];
    char oqAtualizar;

    strcpy(quemAtualizar, lerCPF());

    fun = fopen("funcionarios.dat", "r+b");
    if (fun == NULL) {
        perror("Erro ao abrir o arquivo");
        free(f);
        return 1;
    }

    while (fread(f, sizeof(Funcionario), 1, fun) == 1) {
        if (strcmp(quemAtualizar, f->cpf) == 0) {
            if (!f->status) {
                printf("Não é possível atualizar dados (funcionário inativo).\n");
                encontrado = True;
                break;
            }

            do {
                oqAtualizar = telaOqueAtualizar();
                switch (oqAtualizar) {
                    case '1': {
                        char *nome = lerNome();
                        strcpy(f->nome, nome);
                        free(nome);
                        break;
                    }
                    case '2': {
                        char *telefone = lerTelefone();
                        strcpy(f->telefone, telefone);
                        free(telefone);
                        break;
                    }
                    case '3': {
                        char *email = lerEmail();
                        strcpy(f->email, email);
                        free(email);
                        break;
                    }
                    case '4':
                        f->salario = lerSalario();
                        break;
                    case '0':
                        break;
                    default:
                        printf("Opção inválida. Tente novamente.\n");
                        break;
                }
            } while (oqAtualizar != '1' && oqAtualizar != '2' &&
                     oqAtualizar != '3' && oqAtualizar != '4' && oqAtualizar != '0');

            fseek(fun, -sizeof(Funcionario), SEEK_CUR);
            fwrite(f, sizeof(Funcionario), 1, fun);
            encontrado = True;
            if(oqAtualizar != '0'){
                printf("Dados atualizados com sucesso!\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("Funcionário não encontrado.\n");
    }

    fclose(fun);
    free(f);
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
            printf("╭──────────────────────────────────────────────╮\n");
            printf("│                  FUNCIONÁRIO                 │\n");
            printf("├──────────────────────────────────────────────┤\n");
            printf("│ Nome: %-38s │\n", f->nome);
            printf("│ CPF: %-39s │\n", f->cpf);
            printf("│ Data: %.2s/%.2s/%.4s                             │\n", f->nascimento, f->nascimento + 2, f->nascimento + 4);
            printf("│ Telefone: (%.2s) %.1s %.4s-%.4s                   │\n",  f->telefone, f->telefone + 2,  f->telefone + 3, f->telefone + 7);
            printf("│ E-mail: %-36s │\n", f->email);
            printf("│ Salário: R$%-33.2f │\n", f->salario);
            printf("╰──────────────────────────────────────────────╯\n");
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
        printf("├──────────────────────────────────────────────┤\n");
        printf("│           Erro ao abrir o arquivo.           │");
        free(f);
        return False;
    }

    while(fread(f, sizeof(Funcionario), 1, fun)){
        if(f->status){
            printf("├──────────────────────────────────────────────┤\n");
            printf("│ Nome: %-38s │\n", f->nome);
            printf("│ CPF: %-39s │\n", f->cpf);
            printf("│ Data: %.2s/%.2s/%.4s                             │\n", f->nascimento, f->nascimento + 2, f->nascimento + 4);
            printf("│ Telefone: (%.2s) %.1s %.4s-%.4s                   │\n",  f->telefone, f->telefone + 2,  f->telefone + 3, f->telefone + 7);
            printf("│ E-mail: %-36s │\n", f->email);
            printf("│ Salário: R$%-33.2f │\n", f->salario);
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
            fwrite(f, sizeof(Funcionario), 1, fun);;
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
        free(f);
        return 1;
    }

    funTemp = fopen("temp.dat", "wb");
    if (funTemp == NULL) {
        printf("Erro: não foi possível criar o arquivo temporário.\n");
        fclose(fun);
        free(f);
        return 1;
    }

    char *cpf = lerCPF();

    while (fread(f, sizeof(Funcionario), 1, fun) == 1) {
        if (strcmp(f->cpf, cpf) == 0) {
            encontrado = True;
            printf("Funcionário encontrado e excluído: %s\n", f->nome);
        } else {
            fwrite(f, sizeof(Funcionario), 1, funTemp);
        }
    }

    fclose(fun);
    fclose(funTemp);

    if (encontrado) {
        remove("funcionarios.dat");
        rename("temp.dat", "funcionarios.dat");
        printf("Exclusão realizada com sucesso.\n");
    } else {
        remove("temp.dat");
        printf("Nenhum funcionário encontrado com o CPF informado.\n");
    }

    free(f);
    free(cpf);

    return 0;
}