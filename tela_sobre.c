#include <stdio.h>
#include <stdlib.h>

//Cores ANSI
#define reset   "\033[0m"
#define negrito    "\033[1m"
#define ciano     "\033[1;36m"
#define roxo  "\033[1;35m"
#define rosa     "\033[38;5;213m"
#define vermelho     "\033[31m"


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
    getchar(); 
}


// int main() {
//     telaSobre(); 
//     return 0;
// }