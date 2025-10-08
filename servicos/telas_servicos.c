#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "telas_servicos.h"

typedef struct servico {
    char nome[50];
    float preco;
} Servico;

Servico servicos[100];
int qtdServicos = 0;

char menuServico(void);
void telaCadastrarServico(void);
void telaAtualizarServico(void);
void telaPesquisarServico(void);
void telaExcluirServico(void);
void salvarServicosCSV(Servico servicos[], int qtd);
void carregarServicosCSV(Servico servicos[], int *qtd);
int pesquisarServico(char nome[]);

char modServico(void) {
    char opServico;
    do {
        opServico = menuServico();
        switch (opServico) {
            case '1': telaCadastrarServico(); break;
            case '2': telaAtualizarServico(); break;
            case '3': telaPesquisarServico(); break;
            case '4': telaExcluirServico(); break;
            case '0': break;
            default: printf("Opção inválida! Tente novamente.\n"); break;
        }
    } while (opServico != '0');
    return opServico;
}

char menuServico(void) {
    char opcao[3];
    system("clear");
    printf("\n=== ÁREA DE SERVIÇOS ===\n");
    printf("1. Cadastrar\n");
    printf("2. Atualizar\n");
    printf("3. Pesquisar\n");
    printf("4. Excluir\n");
    printf("0. Sair\n");
    printf("Escolha: ");
    fgets(opcao, sizeof(opcao), stdin);
    return opcao[0];
}

void telaCadastrarServico(void) {
    system("clear");
    if (qtdServicos >= 100) {
        printf("Limite de serviços atingido!\n");
        return;
    }

    Servico novo;
    printf("Nome do serviço: ");
    fgets(novo.nome, 50, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Preço do serviço: R$ ");
    scanf("%f", &novo.preco);
    while (getchar() != '\n');

    servicos[qtdServicos++] = novo;
    salvarServicosCSV(servicos, qtdServicos);
    printf("Serviço cadastrado com sucesso!\n");
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
}

void telaPesquisarServico(void) {
    char nome[50];
    printf("Digite o nome do serviço: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int idx = pesquisarServico(nome);
    if (idx == -1) {
        printf("Serviço não encontrado.\n");
    } else {
        printf("Serviço encontrado!\n Nome: %s | Preço: R$ %.2f\n",
               servicos[idx].nome,
               servicos[idx].preco);
    }
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
}

void telaAtualizarServico(void) {
    system("clear");
    char nome[50];
    printf("Digite o nome do serviço a atualizar: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int idx = pesquisarServico(nome);
    if (idx == -1) {
        printf("Serviço não encontrado.\n");
        printf("\nPressione ENTER para voltar ao menu...");
        getchar();
        return;
    }

    char tmp[50];
    float precoTmp;

    printf("Novo nome (ENTER para manter): ");
    fgets(tmp, sizeof(tmp), stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) strcpy(servicos[idx].nome, tmp);

    printf("Novo preço (0 para manter): R$ ");
    scanf("%f", &precoTmp);
    while (getchar() != '\n');
    if (precoTmp > 0) servicos[idx].preco = precoTmp;

    salvarServicosCSV(servicos, qtdServicos);
    printf("Serviço atualizado com sucesso!\n");
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
}

void telaExcluirServico(void) {
    system("clear");
    char nome[50];
    printf("Digite o nome do serviço a excluir: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    int idx = pesquisarServico(nome);
    if (idx == -1) {
        printf("Serviço não encontrado.\n");
        return;
    }

    for (int i = idx; i < qtdServicos - 1; i++) {
        servicos[i] = servicos[i + 1];
    }
    qtdServicos--;
    salvarServicosCSV(servicos, qtdServicos);
    printf("Serviço excluído com sucesso!\n");
    printf("\nPressione ENTER para voltar ao menu...");
    getchar();
}

int pesquisarServico(char nome[]) {
    for (int i = 0; i < qtdServicos; i++) {
        if (strcmp(servicos[i].nome, nome) == 0) return i;
    }
    return -1;
}

void salvarServicosCSV(Servico servicos[], int qtd) {
    FILE *fp = fopen("servicos.csv", "w");
    if (!fp) return;
    for (int i = 0; i < qtd; i++) {
        fprintf(fp, "%s;%.2f\n", servicos[i].nome, servicos[i].preco);
    }
    fclose(fp);
}

void carregarServicosCSV(Servico servicos[], int *qtd) {
    FILE *fp = fopen("servicos.csv", "r");
    if (!fp) {
        *qtd = 0;
        return;
    }
    char linha[100];
    *qtd = 0;
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        sscanf(linha, "%49[^;];%f", servicos[*qtd].nome, &servicos[*qtd].preco);
        (*qtd)++;
    }
    fclose(fp);
}

// int main(void) {
//     carregarServicosCSV(servicos, &qtdServicos);
//     printf("Iniciando módulo de serviços...\n");
//     modServico();
//     printf("\nEncerrando sistema...\n");
//     return 0;
// }
