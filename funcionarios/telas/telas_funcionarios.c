#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"
#include "telas_funcionarios.h"
#include "opera_funcionarios.h"

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
    char opcao;

    printf("ÁREA DO Funcionario\n");
    printf("___________________");
    printf("1.cadastrar\n");
    printf("2.atualizar\n");
    printf("3.pesquisar\n");
    printf("4.listar\n");
    printf("5.excluir\n");
    printf("0.sair\n");

    scanf("%c", opcao);
    getchar();

    return opcao;


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
        scanf("%c", &op);
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
    char oqAtualizar;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            O QUE DESEJA ATUALIZAR?           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] NOME                                    │\n" );
    printf("│  [2] TELEFONE                                │\n");
    printf("│  [3] EMAIL                                   │\n");
    printf("│  [4] SALÁRIO                                 │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    scanf("%c", &oqAtualizar);
    return oqAtualizar;

}