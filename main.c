#include <stdio.h>
#include <stdlib.h>


#include "tela_inicial.c"
#include "tela_sobre.c"
#include "tela_ajuda.c"
#include "tela_edicao_remocao.c"
#include "tela_final.c"

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
        printf("0 - Sair\n");
        printf("==========================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer do ENTER

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
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Pressione ENTER.\n");
                getchar();
        }
    } while(opcao != 0);

    return 0;
}