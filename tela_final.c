#include <stdio.h>
#include <stdlib.h>

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

int main (){
    telaFinal(); // chama a função para exibir a tela final
    return 0; // encerra o programa
}
