#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"

char modServico(void){
    char opServico;

    do{
        opServico = menuServico();
        switch (opServico)
        {
        case '1':
            telaCadastrarServico();
            break;

        case '2':
            telaAtualizarServico();
            break;

        case '3':
            telaPesquisarServico();
            break;

        case '4':
            telaExcluirServico();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (opServico != '0');

    return opServico;
}

char menuServico(void){
    char opcao;

    printf("ÁREA DO Servico\n");
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

void telaCadastrarServico(void){
    printf("dados necessários para cadastro:\n");
    printf("|ENTER| para sair\n");

    getchar();

}

void telaAtualizarServico(void){
    printf("o que atualizar?\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaPesquisarServico(void){
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaExcluirServico(void){
    printf("nome e data de nascimento para pesquisa e exclusão:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}