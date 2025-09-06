#include <stdio.h>

#define BLUE     "\033[1;34m"
#define MAGENTA  "\033[1;35m"
#define PINK     "\033[38;5;213m"
#define RESET    "\033[0m"

int main() {
    printf(BLUE "=== SIG-NAILS ===\n" RESET);
    printf(MAGENTA "💅 Agenda de Serviços\n" RESET);
    printf(PINK "Bem-vinda ao sistema SIG-NAILS!\n" RESET);
    printf(PINK"★ ★ ★ ★ ★ ★ ★ ★ ★ ★\n" RESET);
    return 0;
}