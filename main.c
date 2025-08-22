#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "tela_inicial.c"
#include "tela_sobre.c"
#include "tela_ajuda.c"
#include "tela_edição_remoção.c"


void telaFinal() {
    system("clear"); // limpa a tela
    printf("\n====================================\n");
    printf("         SIG-Nails - ENCERRAR        \n");
    printf("====================================\n");
    printf(" Obrigada por utilizar o sistema!    \n");
    printf(" Cuide-se e volte sempre!            \n");
    printf("====================================\n\n");

    printf("Pressione ENTER para sair...");
    getchar(); // espera o usuário apertar enter
}



int main(void) {
    int opcao;

    do {
        system("clear");
        printf("===== MENU PRINCIPAL =====\n");
        printf("1 - Tela Inicial\n");
        printf("2 - Sobre\n");
        printf("3 - Ajuda\n");
        printf("4 - Edição/Remoção\n");
        printf("5 - Finalizar\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); 

        switch(opcao) {
            case 1:
                telaInicial();
                break;
            case 2:
                telaSobre();
                break;
            case 3:
                telaAjuda();
                break;
            case 4:
                telaEdicaoRemocao();
                break;
            case 5:
                telaFinal();
                break;
            default:
                printf("Opção inválida! Pressione ENTER.\n");
                getchar();
        }
    } while(opcao != 0);

    return 0;
}