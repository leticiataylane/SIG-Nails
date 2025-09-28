#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"

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
    printf("4.excluir\n");
    printf("0.sair\n");

    scanf("%c", opcao);
    getchar();

    return opcao;


}

void telaCadastrarFuncionario(void){
    printf("dados necessários para cadastro:\n");
    printf("|ENTER| para sair\n");

    getchar();

}

void telaAtualizarFuncionario(void){
    printf("o que atualizar?\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaPesquisarFuncionario(void){
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaExcluirFuncionario(void){
    printf("nome e data de nascimento para pesquisa e exclusão:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}