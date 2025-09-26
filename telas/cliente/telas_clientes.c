#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"

char modCliente(void){
    char opCliente;

    do{
        opCliente = menuCliente();
        switch (opCliente)
        {
        case '1':
            telaCadastrarCliente();
            break;

        case '2':
            telaAtualizarCliente();
            break;

        case '3':
            telaPesquisarCliente();
            break;

        case '4':
            telaExcluirCliente();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (opCliente != '0');

    return opCliente;
}

char menuCliente(void){
    char opcao;

    printf("ÁREA DO CLIENTE\n");
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

void telaCadastrarCliente(void){
    printf("dados necessários para cadastro:\n");
    printf("|ENTER| para sair\n");

    getchar();

}

void telaAtualizarCliente(void){
    printf("o que atualizar?\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaPesquisarCliente(void){
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaExcluirCliente(void){
    printf("nome e data de nascimento para pesquisa e exclusão:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}