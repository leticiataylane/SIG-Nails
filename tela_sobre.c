#include <stdio.h>
#include <stdlib.h>

// Função da tela SOBRE
void telaSobre(void) {
    system("clear"); 
    
    printf("\n");
    printf("\033[1;35m==========================================\033[0m\n"); // Magenta
    printf("\033[1;33m         SOBRE A EMPRESA E A EQUIPE       \033[0m\n"); // Amarelo
    printf("\033[1;35m==========================================\033[0m\n\n");

    printf("\033[1;36mSIG-Nails\033[0m é um sistema feito para\n");
    printf("organizar serviços de manicure e pedicure,\n");
    printf("trazendo praticidade para profissionais e clientes.\n\n");

    printf("👩 Equipe responsável: \033[1;35mLetícia Taylane\033[0m\n\n");

    printf("\033[1;35m==========================================\033[0m\n");
    printf("Pressione ENTER para voltar ao menu...\n");
    printf("\033[1;35m==========================================\033[0m\n");

    getchar(); 
}


int main() {
    telaSobre(); 
    return 0;
}