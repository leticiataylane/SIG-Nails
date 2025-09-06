#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// ===== CORES ANSI =====
#define reset   "\033[0m"
#define negrito "\033[1m"
#define normal  "\033[22m"
#define verde   "\033[32m"
#define azul    "\033[34m"
#define rosa    "\033[38;5;213m"
#define amarelo "\033[33m"
#define roxo    "\033[1;35m"
#define ciano   "\033[1;36m"
#define vermelho     "\033[31m"


// ===== TELA DE ATENDENTES =====
void atendentes(void) {
    system("clear");

    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n" reset);
    printf(roxo "★" rosa negrito "             EQUIPE SIG-NAILS              " roxo "★\n" reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n\n" reset);

    printf(verde   "✿"reset " Ana Souza .......... Design de Unhas\n");
    printf(azul    "✿"reset " Maria Oliveira ..... Manicure e Pedicure\n");
    printf(rosa    "✿"reset " Juliana Lima ....... Nail Art\n");
    printf(amarelo "✿"reset " Carla Santos ....... Alongamento de Unhas\n\n");

    printf(ciano negrito "OBS.:" normal " Cada atendente é responsável por sua especialidade.\n" reset);
    printf("Ao agendar um serviço, o sistema selecionará automaticamente quem irá atendê-lo.\n\n");

    printf(rosa negrito "Pressione ENTER para voltar ao menu...\n" reset);
    getchar();
}


// int main() {
//     atendentes();
//     return 0;
// }