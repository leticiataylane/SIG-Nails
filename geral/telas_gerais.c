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

        printf("╭─────────────────────────────────────────────────╮\n");
        printf("|                                                 |\n");
        printf("│          BEM-VINDO AO SISTEMA SIG-NAILS         │\n");
        printf("|                                                 |\n");
        printf("╰─────────────────────────────────────────────────╯\n");
        sleep(2);
}



char menuPrincipal(void) {
    char op;

    system("clear");
    printf("\n");
    printf("╭─────────────────────────────────────────────╮\n" );
    printf("|           SIG-NAILS MENU PRINCIPAL          |\n" );
    printf("├─────────────────────────────────────────────┤\n" );
    printf("| 1. Agendamentos                             |\n" );
    printf("| 2. Serviços                                 |\n" );
    printf("| 3. Clientes                                 |\n" );
    printf("| 4. Funcionários                             |\n" );
    printf("| 5. Informações                              |\n" );
    printf("| 6. Relatórios                               |\n" );
    printf("| 0. Sair                                     |\n" );
    printf("╰─────────────────────────────────────────────╯\n" );

    op = opcao();
    return op;
}



void telaSobre(void) {
    system("clear"); 
    
    printf("\n");
    printf("╭────────────────────────────────────────────╮\n" ); 
    printf("|       SOBRE A EMPRESA E A EQUIPE           |\n" ); 
    printf("╰────────────────────────────────────────────╯\n" );

    printf("SIG-Nails ""é um sistema feito para\n");
    printf("organizar serviços de manicure e pedicure,\n");
    printf("trazendo praticidade para profissionais e clientes.\n\n");

    printf("Equipe responsável: " "Letícia Taylane e Flávia Juliana\n" );
    printf("──────────────────────────────────────────────\n" );

    esperarEnter(); 
}



void telaFinal() {
    system("clear");
    printf("╭────────────────────────────────────────────╮\n");
    printf("|         SIG-Nails - ENCERRAR               │\n");
    printf("├────────────────────────────────────────────┤\n");
    printf("│ Obrigada por utilizar o sistema!           │\n");
    printf("│ Cuide-se e volte sempre!                   │\n");
    printf("╰────────────────────────────────────────────╯\n");
    esperarEnter();
}


void telaAjuda(void) {
    system("clear"); 
    printf("\n");
    printf("╭────────────────────────────────────────────╮\n" ); 
    printf("|              AJUDA E CONTATO               |\n" ); 
    printf("╰────────────────────────────────────────────╯\n" );
    printf(" Como navegar pelo sistema:\n" );
    printf("- Use os números do menu principal para escolher as opções.\n");
    printf("- Pressione ENTER quando solicitado para voltar.\n");
    printf("- Evite usar teclas diferentes dos números indicados.\n\n");

    printf(" Precisa de suporte?\n" );
    printf("- Email: suporte@signails.com\n");
    printf("- WhatsApp: (99) 99999-9999\n");
    printf("- Instagram: @sig_nails\n");
    printf("──────────────────────────────────────────────\n" );
    esperarEnter(); 
}