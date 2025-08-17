#include <stdio.h>
#include <stdlib.h>

void telaAjuda(void) {
    system("clear"); // limpa a tela (Linux/Unix)

    printf("\n");
    printf("\033[1;35m==========================================\033[0m\n"); // Magenta
    printf("\033[1;33m                AJUDA E CONTATO           \033[0m\n"); // Amarelo
    printf("\033[1;35m==========================================\033[0m\n\n");

    printf("\033[1;36mComo navegar pelo sistema:\033[0m\n");
    printf("- Use os números do menu principal para escolher as opções.\n");
    printf("- Pressione ENTER quando solicitado para voltar.\n");
    printf("- Evite usar teclas diferentes dos números indicados.\n\n");

    printf("\033[1;36mPrecisa de suporte?\033[0m\n");
    printf("- Email: suporte@signails.com\n");
    printf("- WhatsApp: (99) 99999-9999\n");
    printf("- Instagram: @sig_nails\n\n");

    printf("\033[1;35m==========================================\033[0m\n");
    printf("Pressione ENTER para voltar ao menu...\n");
    printf("\033[1;35m==========================================\033[0m\n");

    getchar(); // aguarda Enter do usuário
}

int main() {
    telaAjuda ();
    return 0;
}
