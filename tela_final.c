#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define reset   "\033[0m"
#define negrito    "\033[1m"
#define ciano     "\033[1;36m"
#define roxo  "\033[1;35m"
#define rosa     "\033[38;5;213m"
#define vermelho     "\033[31m"


void telaFinal() {
    system("clear"); // limpa a tela
    printf(roxo negrito "\n✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(roxo negrito "★"rosa negrito"         SIG-Nails - ENCERRAR        "roxo negrito"★\n");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(roxo negrito "★" reset rosa " Obrigada por utilizar o sistema!    "roxo negrito"★\n"reset);
    printf(roxo negrito "★" reset rosa " Cuide-se e volte sempre!            "roxo negrito"★\n");
    printf(roxo negrito"✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n\n"reset);

    printf(ciano "Pressione ENTER para sair..."reset);
    getchar(); // espera o usuário apertar enter
}

// int main (){
//     telaFinal(); 
//     return 0; 
// }
