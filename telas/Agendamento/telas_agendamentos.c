#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"
#include "telas_agendamentos.h"

char modAgendamento(void){
    char opAgendamento;

    do{
        opAgendamento = menuAgendamento();
        switch (opAgendamento)
        {
        case '1':
            telaCadastrarAgendamento();
            break;

        case '2':
            telaAtualizarAgendamento();
            break;

        case '3':
            telaPesquisarAgendamento();
            break;

        case '4':
            telaExcluirAgendamento();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (opAgendamento != '0');

    return opAgendamento;
}

char menuAgendamento(void){
    char opcao;

    printf("ÁREA DO Agendamento\n");
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

void telaCadastrarAgendamento(void){
    printf("dados necessários para cadastro:\n");
    printf("|ENTER| para sair\n");

    getchar();

}

void telaAtualizarAgendamento(void){
    printf("o que atualizar?\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaPesquisarAgendamento(void){
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}

void telaExcluirAgendamento(void){
    printf("nome e data de nascimento para pesquisa e exclusão:\n");
    printf("|ENTER| para sair\n");

    getchar();
    
}