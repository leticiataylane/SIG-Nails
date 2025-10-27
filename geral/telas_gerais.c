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

        printf(roxo negrito "╭─────────────────────────────────────────────────────────────╮\n" reset);
        printf(roxo negrito "│ ✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿ │\n" reset);
        printf(roxo negrito "│ ★"rosa negrito "        BEM-VINDO AO SISTEMA SIG-NAILS       "roxo negrito "★ │\n" reset);
        printf(roxo negrito "│ ✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿ │\n" reset);
        printf(roxo negrito "╰─────────────────────────────────────────────────────────────╯\n" reset);
        sleep(3);
}



char menuPrincipal(void) {
    char op;


    system("clear"); // limpa a tela
    printf(roxo negrito "✿ ★ ★ ★ ★ SIG-NAILS ★ ★ ★ ★ ✿\n" reset);
    printf(rosa "1. Agendamentos\n"reset);
    printf(rosa "2. Serviços\n"reset);
    printf(rosa "3. Clientes\n"reset);
    printf(rosa "4. Funcionários\n"reset);
    printf(rosa "5. Informações\n"reset);
    printf(rosa "0. Sair\n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n" reset);
    printf(ciano "Escolha uma opção (1-6): "reset);
    op = opcao();
    return op;
}



void telaSobre(void) {
    system("clear"); 
    
    printf("\n");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset); 
    printf(rosa negrito "     SOBRE A EMPRESA E A EQUIPE       \n"reset); 
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n\n"reset);

    printf(ciano negrito"SIG-Nails "reset "é um sistema feito para\n");
    printf("organizar serviços de manicure e pedicure,\n");
    printf("trazendo praticidade para profissionais e clientes.\n\n");

    printf("👩 Equipe responsável:" rosa negrito "Letícia Taylane\n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n\n"reset);
    printf("Pressione ENTER para voltar ao menu...\n");
    esperarEnter(); 
}



void telaFinal() {
    system("clear"); // limpa a tela
    printf(roxo negrito "\n✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(roxo negrito "★"rosa negrito"         SIG-Nails - ENCERRAR        "roxo negrito"★\n");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(roxo negrito "★" reset rosa " Obrigada por utilizar o sistema!    "roxo negrito"★\n"reset);
    printf(roxo negrito "★" reset rosa " Cuide-se e volte sempre!            "roxo negrito"★\n");
    printf(roxo negrito"✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n\n"reset);

    printf(ciano "Pressione ENTER para sair..."reset);
    esperarEnter(); // espera o usuário apertar enter
}


void telaAjuda(void) {
    system("clear"); 
    printf("\n");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset); 
    printf(roxo negrito "★"rosa negrito"          AJUDA E CONTATO          "roxo negrito"★\n"reset); 
    printf(roxo negrito"✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n\n"reset);

    printf(ciano negrito "✿ Como navegar pelo sistema:\n"reset);
    printf("- Use os números do menu principal para escolher as opções.\n");
    printf("- Pressione ENTER quando solicitado para voltar.\n");
    printf("- Evite usar teclas diferentes dos números indicados.\n\n");

    printf(ciano negrito "✿ Precisa de suporte?\n"reset);
    printf("- Email: suporte@signails.com\n");
    printf("- WhatsApp: (99) 99999-9999\n");
    printf("- Instagram: @sig_nails\n\n");
    printf(rosa "Pressione ENTER para voltar ao menu...\n"reset);
    esperarEnter(); 
}

