#include <stdio.h>
#include <stdlib.h>

//Cores ANSI
#define reset   "\033[0m"
#define negrito    "\033[1m"
#define ciano     "\033[1;36m"
#define roxo  "\033[1;35m"
#define rosa     "\033[38;5;213m"
#define vermelho     "\033[31m"

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
    getchar(); 
}
// int main() {
//     telaAjuda();
//     return 0;
// }
