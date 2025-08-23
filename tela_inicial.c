// #include <stdio.h>
// #include <string.h>
// #include <stdlib.h>
// #include <ctype.h>

// ==== Cores ANSI para terminal do linux (peguei na net para deixar mais bonito graficamente)
#define C_RESET   "\033[0m"
#define C_BOLD    "\033[1m"
#define C_CYAN    "\033[36m"
#define C_MAGENTA "\033[35m"
#define C_YELLOW  "\033[33m"
#define C_RED     "\033[31m"
#define C_GREEN   "\033[32m"


void pauseEnter(void) {
    printf("\n" C_YELLOW "(Pressione Enter para continuar...)" C_RESET);
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

// verifica se nome tem só letras e espaços
int nomeValido(const char *nome) {
    for (int i = 0; nome[i] != '\0'; i++) {
        if (!isalpha(nome[i]) && nome[i] != ' ') {
            return 0; 
        }
    }
    return 1;
}

// Função para mostrar a "tela inicial"
void telaInicial(char usuario[50]) {
    do {
        system("clear"); 

        printf(C_MAGENTA "=============================================\n" C_RESET);
        printf(C_BOLD   "        BEM-VINDO AO SISTEMA SIG-NAILS        \n" C_RESET);
        printf(C_MAGENTA "=============================================\n" C_RESET);

        printf("\nDigite seu nome para entrar: ");
        fgets(usuario, 50, stdin);

        // remove '\n'
        usuario[strcspn(usuario, "\n")] = '\0';

        if (strlen(usuario) == 0 || !nomeValido(usuario)) {
            printf(C_RED "\n⚠️  Nome inválido! Use apenas letras e espaços.\n" C_RESET);
            pauseEnter();
        }

    } while (strlen(usuario) == 0 || !nomeValido(usuario));

    printf("\nOlá, " C_CYAN "%s" C_RESET "! Seja bem-vindo(a) ao sistema.\n", usuario);

    pauseEnter();
}


int menuPrincipal(void) {
    char entrada[10];
    int opcao = 0;

    do {
        system("clear"); 

        printf(C_MAGENTA "=============== MENU PRINCIPAL ===============\n" C_RESET);
        printf("1. Agendamentos\n");
        printf("2. Serviços\n");
        printf("3. Sobre o sistema\n");
        printf("4. Sair\n");
        printf(C_MAGENTA "==============================================\n" C_RESET);
        printf("Escolha uma opção (1-4): ");

        if (fgets(entrada, sizeof(entrada), stdin) != NULL) {
            entrada[strcspn(entrada, "\n")] = '\0';
            opcao = atoi(entrada);
        }

        if (opcao < 1 || opcao > 4) {
            printf(C_RED "\n⚠️  Opção inválida! Digite um número de 1 a 4.\n" C_RESET);
            pauseEnter();
        }

    } while (opcao < 1 || opcao > 4);

    return opcao;
}

void executar_tela_inicial(void) {
    char usuario[50];
    int opcao;

    telaInicial(usuario);
    opcao = menuPrincipal();

    printf(C_GREEN "\nVocê escolheu");
}

// int main() {
//     executar_tela_inicial();
//     return 0;
// }