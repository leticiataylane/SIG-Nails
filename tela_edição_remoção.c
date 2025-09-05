#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Cores ANSI
#define reset   "\033[0m"
#define negrito    "\033[1m"
#define ciano     "\033[1;36m"
#define roxo  "\033[1;35m"
#define rosa     "\033[38;5;213m"
#define vermelho     "\033[31m"

// variáveis globais para armazenar o último agendamento
char ultimoNome[50];
char ultimoServico[50];
char ultimaData[15];
char ultimaHora[10];
int agendamentoFeito = 0; // controle se já existe agendamento

// funções de validação

// verifica se ano é bissexto
int ehBissexto(int ano) {
    return (ano % 400 == 0) || (ano % 4 == 0 && ano % 100 != 0);
}

// valida a data (aceita ddmmaaaa ou dd/mm/aaaa)
int validarData(char *dataEntrada) {
    int d, m, a;
    int diasPorMes[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

    if (strlen(dataEntrada) == 8 && sscanf(dataEntrada, "%2d%2d%4d", &d, &m, &a) == 3) {
        sprintf(dataEntrada, "%02d/%02d/%04d", d, m, a);
    }
    else if (sscanf(dataEntrada, "%d/%d/%d", &d, &m, &a) != 3) {
        return 0;
    }

    if (ehBissexto(a)) diasPorMes[2] = 29;
    if (m < 1 || m > 12) return 0;
    if (d < 1 || d > diasPorMes[m]) return 0;
    if (a < 2024) return 0;

    return 1;
}

// valida hora (aceita hhmm ou hh:mm)
int validarHora(char *horaEntrada) {
    int h, m;

    if (strlen(horaEntrada) == 4 && sscanf(horaEntrada, "%2d%2d", &h, &m) == 2) {
        sprintf(horaEntrada, "%02d:%02d", h, m);
    }
    else if (sscanf(horaEntrada, "%d:%d", &h, &m) != 2) {
        return 0;
    }

    if (h < 8 || h > 20) return 0;  // horário de funcionamento
    if (m < 0 || m > 59) return 0;

    return 1;
}


// Como agendar
void telaComoAgendar(void) {
    system("clear");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito "                COMO AGENDAR                   \n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf("1. Consulte nossa tabela de preços.\n");
    printf("2. Escolha o serviço desejado.\n");
    printf("3. Informe seus dados: nome, data e hora.\n");
    printf("4. Aguarde a confirmação.\n");
    printf(rosa negrito "\nPressione ENTER para continuar...\n"reset);
    getchar();
}

// Tabela de preços
void telaPrecos(void) {
    system("clear");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito "        TABELA DE PREÇOS   \n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito "Manicure ............ "ciano"R$25\n"reset);
    printf(rosa negrito "Pedicure ............ "ciano"R$30\n"reset);
    printf(rosa negrito "Mani + Pedi ......... "ciano"R$50\n"reset);
    printf(rosa negrito "Spa dos Pés ......... "ciano"R$45\n"reset);
    printf(rosa negrito "Blindagem de Unhas .. "ciano"R$60\n"reset);
    printf(negrito "\nPressione ENTER para continuar...\n"reset);
    getchar();
}

// Novo agendamento
void telaNovoAgendamento(void) {
    char nome[50];
    char servico[50];
    char data[15];
    char hora[10];

    system("clear");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito "         NOVO AGENDAMENTO    \n");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);

    // Nome
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = 0;

    
    printf("Serviço desejado: ");
    fgets(servico, sizeof(servico), stdin);
    servico[strcspn(servico, "\n")] = 0;

    
   // Data
    do {
        printf("Data (ddmmaaaa ou dd/mm/aaaa): ");
        fgets(data, sizeof(data), stdin);
        data[strcspn(data, "\n")] = 0;

        if (!validarData(data)) {
            printf(vermelho "Data inválida! Tente novamente.\n" reset);
        }
    } while (!validarData(data));

    // Hora
    do {
        printf("Hora (hhmm ou hh:mm): ");
        fgets(hora, sizeof(hora), stdin);
        hora[strcspn(hora, "\n")] = 0;

        if (!validarHora(hora)) {
            printf(vermelho "Hora inválida! Tente novamente.\n" reset);
        }
    } while (!validarHora(hora));

    strcpy(ultimoNome, nome);
    strcpy(ultimoServico, servico);
    strcpy(ultimaData, data);
    strcpy(ultimaHora, hora);
    agendamentoFeito = 1;

    printf(roxo negrito "Agendamento registrado com sucesso!\n"reset);
    printf(rosa negrito "Pressione ENTER para voltar...\n"reset);
    getchar();
}


void telaEditarAgendamento(void) {
    if (!agendamentoFeito) {
        system("clear");
        printf(ciano "Nenhum agendamento para editar!\n"reset);
        printf(rosa negrito"Pressione ENTER para voltar...\n");
        getchar();
        return;
    }

    char novoServico[50];
    char novaData[15];
    char novaHora[10];

    system("clear");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito "     EDITAR AGENDAMENTO    \n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);

    printf(ciano negrito "Cliente:"reset" %s\n", ultimoNome);
    printf(ciano negrito "Serviço atual:"reset" %s\n", ultimoServico);
    printf(ciano negrito "Data atual:"reset" %s\n", ultimaData);
    printf(ciano negrito "Hora atual:"reset" %s\n", ultimaHora);

    //serviço
    printf(rosa "\nNovo serviço (ou Enter para manter): "reset);
    fgets(novoServico, sizeof(novoServico), stdin);
    novoServico[strcspn(novoServico, "\n")] = 0;
    if (strlen(novoServico) > 0) strcpy(ultimoServico, novoServico);

    //data
do {
    printf("Nova data (ddmmaaaa ou dd/mm/aaaa, ou Enter para manter): ");
    fgets(novaData, sizeof(novaData), stdin);
    novaData[strcspn(novaData, "\n")] = 0;

    if (strlen(novaData) == 0) break; // mantém a data atual

    if (!validarData(novaData)) {
        printf(vermelho "Data inválida! Tente novamente.\n" reset);
    } else {
        strcpy(ultimaData, novaData);
    }
} while (!validarData(novaData) && strlen(novaData) > 0);

//hora
do {
    printf("Nova hora (hhmm ou hh:mm, ou Enter para manter): ");
    fgets(novaHora, sizeof(novaHora), stdin);
    novaHora[strcspn(novaHora, "\n")] = 0;

    if (strlen(novaHora) == 0) break; // mantém a hora atual

    if (!validarHora(novaHora)) {
        printf(vermelho "Hora inválida! Tente novamente.\n" reset);
    } else {
        strcpy(ultimaHora, novaHora);
    }
} while (!validarHora(novaHora) && strlen(novaHora) > 0);

    printf(roxo negrito "\nAgendamento atualizado com sucesso!\n"reset);
    printf(rosa negrito "Pressione ENTER para voltar...\n"reset);
    getchar();
}

// remover agend
void telaRemoverAgendamento(void) {
    system("clear");
    if (!agendamentoFeito) {
        printf(ciano "Nenhum agendamento para remover!\n"reset);
    } else {
        agendamentoFeito = 0;
        printf(roxo negrito "Agendamento removido com sucesso!\n"reset);
    }
    printf(rosa negrito "Pressione ENTER para voltar...\n"reset);
    getchar();
}

// confirmação do agend
void telaConfirmacao(void) {
    system("clear");
    printf(roxo negrito"✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito"          CONFIRMAÇÃO DE AGENDAMENTO         \n"reset);
    printf(roxo negrito"✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);

    if (agendamentoFeito) {
        printf(ciano "Cliente:"reset" %s\n", ultimoNome);
        printf(ciano "Serviço:"reset" %s\n", ultimoServico);
        printf(ciano "Data:"reset" %s\n", ultimaData);
        printf(ciano "Hora:"reset" %s\n", ultimaHora);
    } else {
        printf(ciano "Nenhum agendamento foi feito ainda.\n"reset);
    }

    printf(rosa negrito"Pressione ENTER para voltar...\n"reset);
    getchar();
}
 int main(void) {
    telaComoAgendar();
    telaPrecos();
    telaNovoAgendamento();
    telaEditarAgendamento();
    telaConfirmacao();
    telaRemoverAgendamento();
    return 0;
}