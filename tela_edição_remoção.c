#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==VARIÁVEIS GLOBAIS 
char ultimoNome[50];
char ultimoServico[50];
char ultimaData[15];
char ultimaHora[10];
int agendamentoFeito = 0; // controle se já existe agendamento

// == FUNÇÕES DE VALIDAÇÃO

// Valida se a data está no formato dd/mm/aaaa
int validarData(const char *data) {
    int d, m, a;
    if (sscanf(data, "%d/%d/%d", &d, &m, &a) != 3) return 0;
    if (d < 1 || d > 31) return 0;
    if (m < 1 || m > 12) return 0;
    if (a < 2024) return 0;
    return 1;
}

// Validar a hora no formato hh:mm
int validarHora(const char *hora) {
    int h, m;
    if (sscanf(hora, "%d:%d", &h, &m) != 2) return 0;
    if (h < 0 || h > 23) return 0;
    if (m < 0 || m > 59) return 0;
    return 1;
}

// == TELAS

// Como agendar
void telaComoAgendar(void) {
    system("clear");
    printf("\033[1;36m===========================\n");
    printf("        COMO AGENDAR       \n");
    printf("===========================\033[0m\n");
    printf("1. Consulte nossa tabela de preços.\n");
    printf("2. Escolha o serviço desejado.\n");
    printf("3. Informe seus dados: nome, data e hora.\n");
    printf("4. Aguarde a confirmação.\n");
    printf("\nPressione ENTER para voltar...\n");
    getchar();
}

// Tabela de preços
void telaPrecos(void) {
    system("clear");
    printf("\033[1;35m===========================\n");
    printf("        TABELA DE PREÇOS   \n");
    printf("===========================\033[0m\n");
    printf("\033[1;33mManicure ............ R$25\n");
    printf("Pedicure ............ R$30\n");
    printf("Mani + Pedi ......... R$50\n");
    printf("Spa dos Pés ......... R$45\n");
    printf("Blindagem de Unhas .. R$60\033[0m\n");
    printf("\nPressione ENTER para voltar...\n");
    getchar();
}

// Novo agendamento
void telaNovoAgendamento(void) {
    char nome[50];
    char servico[50];
    char data[15];
    char hora[10];

    system("clear");
    printf("\033[1;36m===========================\n");
    printf("      NOVO AGENDAMENTO    \n");
    printf("===========================\033[0m\n");

    // Nome
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    // Serviço
    printf("Serviço desejado: ");
    fgets(servico, sizeof(servico), stdin);
    servico[strcspn(servico, "\n")] = 0;

    // Data com validação
    do {
        printf("Data (dd/mm/aaaa): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0;

        if (!validarData(data)) {
            printf("Data inválida! Tente novamente.\n");
        }
    } while (!validarData(data));

    // Hora com validação
    do {
        printf("Hora (hh:mm): ");
        fgets(hora, sizeof(hora), stdin);
        hora[strcspn(hora, "\n")] = 0;

        if (!validarHora(hora)) {
            printf("Hora inválida! Tente novamente.\n");
        }
    } while (!validarHora(hora));

    // Guarda os dados
    strcpy(ultimoNome, nome);
    strcpy(ultimoServico, servico);
    strcpy(ultimaData, data);
    strcpy(ultimaHora, hora);
    agendamentoFeito = 1;

    printf("\n\033[1;32mAgendamento registrado com sucesso!\033[0m\n");
    printf("\nPressione ENTER para voltar...\n");
    getchar();
}

// Editar agendamento
void telaEditarAgendamento(void) {
    if (!agendamentoFeito) {
        system("clear");
        printf("\033[1;31mNenhum agendamento para editar!\033[0m\n");
        printf("\nPressione ENTER para voltar...\n");
        getchar();
        return;
    }

    char novoServico[50];
    char novaData[15];
    char novaHora[10];

    system("clear");
    printf("\033[1;36m===========================\n");
    printf("     EDITAR AGENDAMENTO    \n");
    printf("===========================\033[0m\n");

    printf("Cliente: %s\n", ultimoNome);
    printf("Serviço atual: %s\n", ultimoServico);
    printf("Data atual: %s\n", ultimaData);
    printf("Hora atual: %s\n", ultimaHora);

    // Novo serviço
    printf("\nNovo serviço (ou Enter para manter): ");
    fgets(novoServico, sizeof(novoServico), stdin);
    novoServico[strcspn(novoServico, "\n")] = 0;
    if (strlen(novoServico) > 0) strcpy(ultimoServico, novoServico);

    // Nova data
    do {
        printf("Nova data (dd/mm/aaaa) (ou Enter para manter): ");
        fgets(novaData, sizeof(novaData), stdin);
        novaData[strcspn(novaData, "\n")] = 0;

        if (strlen(novaData) == 0) break;
        if (!validarData(novaData)) {
            printf("Data inválida! Tente novamente.\n");
        } else {
            strcpy(ultimaData, novaData);
            break;
        }
    } while (1);

    // Nova hora
    do {
        printf("Nova hora (hh:mm) (ou Enter para manter): ");
        fgets(novaHora, sizeof(novaHora), stdin);
        novaHora[strcspn(novaHora, "\n")] = 0;

        if (strlen(novaHora) == 0) break;
        if (!validarHora(novaHora)) {
            printf("Hora inválida! Tente novamente.\n");
        } else {
            strcpy(ultimaHora, novaHora);
            break;
        }
    } while (1);

    printf("\n\033[1;32mAgendamento atualizado com sucesso!\033[0m\n");
    printf("\nPressione ENTER para voltar...\n");
    getchar();
}

// Remover agendamento
void telaRemoverAgendamento(void) {
    system("clear");
    if (!agendamentoFeito) {
        printf("\033[1;31mNenhum agendamento para remover!\033[0m\n");
    } else {
        agendamentoFeito = 0;
        printf("\033[1;32mAgendamento removido com sucesso!\033[0m\n");
    }
    printf("\nPressione ENTER para voltar...\n");
    getchar();
}

// Confirmação do agendamento
void telaConfirmacao(void) {
    system("clear");
    printf("\033[1;35m===========================\n");
    printf(" CONFIRMAÇÃO DE AGENDAMENTO\n");
    printf("===========================\033[0m\n");

    if (agendamentoFeito) {
        printf("Cliente: %s\n", ultimoNome);
        printf("Serviço: %s\n", ultimoServico);
        printf("Data: %s\n", ultimaData);
        printf("Hora: %s\n", ultimaHora);
    } else {
        printf("\033[1;31mNenhum agendamento foi feito ainda.\033[0m\n");
    }

    printf("\nPressione ENTER para voltar...\n");
    getchar();
}

// ==================== MAIN ====================
int main(void) {
    int opcao;

    do {
        system("clear");
        printf("\033[1;36m===========================\n");
        printf("        MENU PRINCIPAL     \n");
        printf("===========================\033[0m\n");
        printf("1 - Como agendar\n");
        printf("2 - Tabela de preços\n");
        printf("3 - Novo agendamento\n");
        printf("4 - Confirmar agendamento\n");
        printf("5 - Editar agendamento\n");
        printf("6 - Remover agendamento\n");
        printf("0 - Sair\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // limpar buffer do enter

        if (opcao == 1) telaComoAgendar();
        else if (opcao == 2) telaPrecos();
        else if (opcao == 3) telaNovoAgendamento();
        else if (opcao == 4) telaConfirmacao();
        else if (opcao == 5) telaEditarAgendamento();
        else if (opcao == 6) telaRemoverAgendamento();
        else if (opcao == 0) printf("Saindo...\n");
        else {
            printf("Opção inválida!\n");
            getchar();
        }

    } while (opcao != 0);

    return 0;
}