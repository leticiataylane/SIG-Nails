#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// variaveis globais
char ultimoNome[50];
char ultimoServico[50];
char ultimaData[15];
char ultimaHora[10];
int agendamentoFeito = 0;

// funcoes auxiliares de validacao
void pauseEnter(void) {
    printf("\n(Pressione Enter para continuar...)");
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int validarData(const char *data) {
    int d, m, a;
    if (sscanf(data, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    if (d < 1 || d > 31) return 0;
    if (m < 1 || m > 12) return 0;
    if (a < 2024) return 0;
    return 1;
}

int validarHora(const char *hora) {
    int h, m;
    if (sscanf(hora, "%d:%d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;
    return 1;
}

// telas

void telaComoAgendar(void) {
    system("clear");
    printf("===== COMO AGENDAR =====\n");
    printf("1. Consulte a tabela de preços.\n");
    printf("2. Escolha o serviço.\n");
    printf("3. Informe nome, data e hora.\n");
    printf("4. Aguarde a confirmação.\n");
    pauseEnter();
}

void telaPrecos(void) {
    system("clear");
    printf("===== TABELA DE PREÇOS =====\n");
    printf("Manicure ............ R$25\n");
    printf("Pedicure ............ R$30\n");
    printf("Mani + Pedi ......... R$50\n");
    printf("Spa dos Pés ......... R$45\n");
    printf("Blindagem de Unhas .. R$60\n");
    pauseEnter();
}

void telaNovoAgendamento(void) {
    char nome[50], servico[50], data[15], hora[10];

    system("clear");
    printf("===== NOVO AGENDAMENTO =====\n");

    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Serviço desejado: ");
    fgets(servico, sizeof(servico), stdin);
    servico[strcspn(servico, "\n")] = 0;

    do {
        printf("Data (dd/mm/aaaa): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0;
    } while (!validarData(data));

    do {
        printf("Hora (hh:mm): ");
        fgets(hora, sizeof(hora), stdin);
        hora[strcspn(hora, "\n")] = 0;
    } while (!validarHora(hora));

    strcpy(ultimoNome, nome);
    strcpy(ultimoServico, servico);
    strcpy(ultimaData, data);
    strcpy(ultimaHora, hora);
    agendamentoFeito = 1;

    printf("\nAgendamento registrado com sucesso!\n");
    pauseEnter();
}

void telaEditarAgendamento(void) {
    if (!agendamentoFeito) {
        printf("\nNenhum agendamento para editar!\n");
        pauseEnter();
        return;
    }

    char novoServico[50], novaData[15], novaHora[10];

    system("clear");
    printf("===== EDITAR AGENDAMENTO =====\n");
    printf("Cliente: %s\n", ultimoNome);
    printf("Serviço atual: %s\n", ultimoServico);
    printf("Data atual: %s\n", ultimaData);
    printf("Hora atual: %s\n", ultimaHora);

    printf("\nNovo serviço (Enter mantém): ");
    fgets(novoServico, sizeof(novoServico), stdin);
    novoServico[strcspn(novoServico, "\n")] = 0;
    if (strlen(novoServico) > 0) strcpy(ultimoServico, novoServico);

    printf("Nova data (dd/mm/aaaa) (Enter mantém): ");
    fgets(novaData, sizeof(novaData), stdin);
    novaData[strcspn(novaData, "\n")] = 0;
    if (strlen(novaData) > 0 && validarData(novaData)) strcpy(ultimaData, novaData);

    printf("Nova hora (hh:mm) (Enter mantém): ");
    fgets(novaHora, sizeof(novaHora), stdin);
    novaHora[strcspn(novaHora, "\n")] = 0;
    if (strlen(novaHora) > 0 && validarHora(novaHora)) strcpy(ultimaHora, novaHora);

    printf("\nAgendamento atualizado!\n");
    pauseEnter();
}

void telaRemoverAgendamento(void) {
    system("clear");
    if (!agendamentoFeito) {
        printf("Nenhum agendamento para remover!\n");
    } else {
        agendamentoFeito = 0;
        printf("Agendamento removido!\n");
    }
    pauseEnter();
}

void telaConfirmacao(void) {
    system("clear");
    printf("===== CONFIRMAÇÃO =====\n");

    if (agendamentoFeito) {
        printf("Cliente: %s\n", ultimoNome);
        printf("Serviço: %s\n", ultimoServico);
        printf("Data: %s\n", ultimaData);
        printf("Hora: %s\n", ultimaHora);
    } else {
        printf("Nenhum agendamento foi feito ainda.\n");
    }

    pauseEnter();
}

void telaAjuda(void) {
    system("clear");
    printf("===== AJUDA =====\n");
    printf("- Use os números do menu.\n");
    printf("- Pressione ENTER para voltar.\n");
    printf("\nContato: suporte@signails.com\n");
    pauseEnter();
}

void telaSobre(void) {
    system("clear");
    printf("===== SOBRE =====\n");
    printf("SIG-Nails é um sistema para ajudar manicures.\n");
    printf("Equipe: Letícia Taylane\n");
    pauseEnter();
}

void telaFinal(void) {
    system("clear");
    printf("\n===== ENCERRAR =====\n");
    printf("Obrigada por usar o sistema!\n");
    pauseEnter();
}

// codigo principal
int main(void) {
    int opcao;

    do {
        system("clear");
        printf("===== MENU PRINCIPAL =====\n");
        printf("1 - Novo agendamento\n");
        printf("2 - Confirmar agendamento\n");
        printf("3 - Editar agendamento\n");
        printf("4 - Remover agendamento\n");
        printf("5 - Tabela de preços\n");
        printf("6 - Como agendar\n");
        printf("7 - Sobre\n");
        printf("8 - Ajuda\n");
        printf("0 - Finalizar\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        if (opcao == 1) telaNovoAgendamento();
        else if (opcao == 2) telaConfirmacao();
        else if (opcao == 3) telaEditarAgendamento();
        else if (opcao == 4) telaRemoverAgendamento();
        else if (opcao == 5) telaPrecos();
        else if (opcao == 6) telaComoAgendar();
        else if (opcao == 7) telaSobre();
        else if (opcao == 8) telaAjuda();
        else if (opcao == 0) telaFinal();
        else {
            printf("Opção inválida!\n");
            pauseEnter();
        }

    } while(opcao != 0);

    return 0;
}