#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <ctype.h> 

//Cores ANSI
#define reset   "\033[0m"
#define negrito    "\033[1m"
#define ciano     "\033[1;36m"
#define roxo  "\033[1;35m"
#define rosa     "\033[38;5;213m"
#define vermelho     "\033[31m"

// Função que espera Enter
void pauseEnter(void) {
    printf("\n" rosa negrito "(Pressione Enter para continuar...)" reset);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// Função auxiliar: verifica se nome tem só letras e espaços
int nomeValido(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0; // encontrou algo que não é letra nem espaço
        }
    }
    return 1;
}

// Função para mostrar a "tela inicial"
void telaInicial(char usuario[50]) {
    do {
        system("clear"); // limpa a tela

        printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n" reset);
        printf(roxo negrito "★"rosa negrito "        BEM-VINDO AO SISTEMA SIG-NAILS       "roxo negrito "★\n" reset);
        printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n" reset);

        printf(ciano "\nDigite seu nome para entrar: "reset);
        fgets(usuario, 50, stdin);

        // remove '\n' (ajuda do chatGPT)
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == 0 || !nomeValido(usuario)) {
            printf(vermelho "\n⚠️  Nome inválido! Use apenas letras e espaços.\n" reset);
            pauseEnter();
        }

    } while (strlen(usuario) == 0 || !nomeValido(usuario));

    printf("\nOlá, " rosa negrito "%s" reset "! Seja bem-vindo(a) ao sistema.\n", usuario);

    pauseEnter();
}

// Função para mostrar o menu principal
int menuPrincipal(void) {
    char entrada[10];
    int opcao = 0;

    do {
        system("clear"); // limpa a tela
        printf(roxo negrito "✿ ★ ★ ★ ★ OPÇÕES DO CLIENTE ★ ★ ★ ★ ✿\n" reset);
        printf(rosa "1. Agendamentos e preços\n"reset);
        printf(rosa "2. Cores\n"reset);
        printf(rosa "3. Atendentes\n"reset);
        printf(rosa "4. Informações\n"reset);
        printf(rosa "0. Sair\n"reset);
        printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n" reset);
        printf(ciano "Escolha uma opção (0-4): "reset);

        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            opcao = atoi(entrada);
        }

        if (opcao < 0 || opcao > 4) {
            printf(vermelho "\nOpção inválida! Digite um número de 0 a 4.\n" reset);
            pauseEnter();
        }

    } while (opcao < 0 || opcao > 4);

    return opcao;
}

/*
int main(void) {
    char usuario[50];
    int opcao;

    telaInicial(usuario);
    opcao = menuPrincipal();

}
*/
