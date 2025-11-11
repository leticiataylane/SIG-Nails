#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "telas_gerais.h"
#include "cores.h"
#include "ler_dados.h"
#include "limpeza.h"
#include "validacoes.h"
#include "erros.h"


// void pauseEnter(void) {
//     printf("\n" rosa negrito "(Pressione Enter para continuar...)" reset);
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF) { }
// }

void telaInicial(void) {

        system("clear");

        printf(roxo negrito "╭─────────────────────────────────────────────────╮\n" reset);
        printf(roxo negrito "│ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ │\n" reset);
        printf(roxo negrito "│ ★"ciano negrito "        BEM-VINDO AO SISTEMA SIG-NAILS       "roxo negrito "★ │\n" reset);
        printf(roxo negrito "│ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ │\n" reset);
        printf(roxo negrito "╰─────────────────────────────────────────────────╯\n" reset);
        sleep(2);
}



char menuPrincipal(void) {
    char op;

    system("clear");
    printf("\n");
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);
    printf(ciano negrito "              SIG-NAILS MENU PRINCIPAL        \n" reset);
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);
    printf(ciano "1. Agendamentos\n" reset);
    printf(ciano "2. Serviços\n" reset);
    printf(ciano "3. Clientes\n" reset);
    printf(ciano "4. Funcionários\n" reset);
    printf(ciano "5. Informações\n" reset);
    printf(ciano "0. Sair\n" reset);
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);

    op = opcao();
    return op;
}



void telaSobre(void) {
    system("clear"); 
    
    printf("\n");
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset); 
    printf(ciano negrito "        SOBRE A EMPRESA E A EQUIPE        \n" reset); 
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);

    printf(ciano negrito "SIG-Nails " reset "é um sistema feito para\n");
    printf("organizar serviços de manicure e pedicure,\n");
    printf("trazendo praticidade para profissionais e clientes.\n\n");

    printf("Equipe responsável: " ciano negrito "Letícia Taylane e Flávia Juliana\n" reset);
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);

    esperarEnter(); 
}



void telaFinal() {
    system("clear");
    printf(roxo negrito "\n★────────────────────────────────────────────★\n"reset);
    printf(roxo negrito "│"ciano negrito"         SIG-Nails - ENCERRAR               "roxo negrito"│\n");
    printf(roxo negrito "★────────────────────────────────────────────★\n"reset);
    printf(roxo negrito "│" reset ciano " Obrigada por utilizar o sistema!           "roxo negrito"│\n"reset);
    printf(roxo negrito "│" reset ciano " Cuide-se e volte sempre!                   "roxo negrito"│\n");
    printf(roxo negrito"★────────────────────────────────────────────★\n"reset);
    esperarEnter();
}


void telaAjuda(void) {
    system("clear"); 
    printf("\n");
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset); 
    printf(ciano negrito "              AJUDA E CONTATO               \n" reset); 
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);
    printf(ciano negrito "★ Como navegar pelo sistema:\n" reset);
    printf("- Use os números do menu principal para escolher as opções.\n");
    printf("- Pressione ENTER quando solicitado para voltar.\n");
    printf("- Evite usar teclas diferentes dos números indicados.\n\n");

    printf(ciano negrito "★ Precisa de suporte?\n" reset);
    printf("- Email: suporte@signails.com\n");
    printf("- WhatsApp: (99) 99999-9999\n");
    printf("- Instagram: @sig_nails\n");
    printf(roxo negrito "★────────────────────────────────────────────★\n\n" reset);
    esperarEnter(); 
}