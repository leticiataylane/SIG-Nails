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
//     printf("\n" rosa negrito "(Pressione Enter para continuar...)" );
//     int c;
//     while ((c = getchar()) != '\n' && c != EOF) { }
// }

void telaInicial(void) {

        system("clear");

        printf(roxo negrito"╭─────────────────────────────────────────────────╮\n");
        printf(            "│          BEM-VINDO AO SISTEMA SIG-NAILS         │\n");
        printf(            "╰─────────────────────────────────────────────────╯\n"reset);
        sleep(2);
}



char menuPrincipal(void) {
    char op;

    system("clear");
    printf("\n");
    printf("╭──────────────────────────────────────────────╮\n" );
    printf("|           "roxo"SIG-NAILS MENU PRINCIPAL"reset"           |\n" );
    printf("├──────────────────────────────────────────────┤\n" );
    printf("| "roxo"[1] AGENDAMENTOS "reset"                            |\n" );
    printf("| "roxo"[2] SERVIÇOS     "reset"                            |\n" );
    printf("| "roxo"[3] CLIENTES     "reset"                            |\n" );
    printf("| "roxo"[4] FUNCIONÁRIOS "reset"                            |\n" );
    printf("| "roxo"[5] INFORMAÇÕES  "reset"                            |\n" );
    printf("| "roxo"[6] RELATÓRIOS   "reset"                            |\n" );
    printf("| "roxo"[0] SAIR         "reset"                            |\n" );
    printf("╰──────────────────────────────────────────────╯\n" );

    op = opcao();
    return op;
}



void telaSobre(void) {
    system("clear"); 
    
    printf("\n");
    printf("╭──────────────────────────────────────────────────────╮\n"); 
    printf("|             SOBRE A EMPRESA E A EQUIPE               |\n"); 
    printf("├──────────────────────────────────────────────────────┤\n");
    printf("| SIG-Nails é um sistema feito para                    |\n");
    printf("| organizar serviços de manicure e pedicure, trazendo  |\n");
    printf("| praticidade para profissionais e clientes.           |\n");
    printf("├──────────────────────────────────────────────────────┤\n");
    printf("| Equipe responsável: Letícia Taylane e Flávia Juliana |\n");
    printf("╰──────────────────────────────────────────────────────╯\n");

    esperarEnter(); 
}

void telaAjuda(void) {
    system("clear"); 
    printf("\n");
    printf("╭────────────────────────────────────────────────────────────╮\n"); 
    printf("|                      AJUDA E CONTATO                       |\n"); 
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("| Como navegar pelo sistema:                                 |\n");
    printf("|- Use os números do menu principal para escolher as opções. |\n");
    printf("|- Pressione ENTER quando solicitado para voltar.            |\n");
    printf("|- Evite usar teclas diferentes dos números indicados.       |\n");
    printf("├────────────────────────────────────────────────────────────┤\n");
    printf("| Precisa de suporte?                                        |\n");
    printf("|- Email: suporte@signails.com                               |\n");
    printf("|- WhatsApp: (99) 99999-9999                                 |\n");
    printf("|- Instagram: @sig_nails                                     |\n");
    printf("╰────────────────────────────────────────────────────────────╯\n");
    esperarEnter(); 
}

void telaFinal() {
    system("clear");
    printf(roxo negrito"╭────────────────────────────────────────────╮\n");
    printf(            "|         SIG-Nails - ENCERRAR               │\n");
    printf(            "├────────────────────────────────────────────┤\n");
    printf(            "│ Obrigada por utilizar o sistema!           │\n");
    printf(            "│ Cuide-se e volte sempre!                   │\n");
    printf(            "╰────────────────────────────────────────────╯\n"reset);
    esperarEnter();
}