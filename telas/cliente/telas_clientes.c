#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct cliente {
    char nome[80];
    char dataNascimento[11];
    char telefone[20];
} Cliente;

Cliente clientes[100];
int qtdClientes = 0;


char menuCliente(void);
void telaCadastrarCliente(void);
void telaAtualizarCliente(void);
void telaPesquisarCliente(void);
void telaExcluirCliente(void);
void salvarClientesCSV(Cliente clientes[], int qtd);
void carregarClientesCSV(Cliente clientes[], int *qtd);
int pesquisarCliente(char nome[], char data[]);


char modCliente(void) {
    char opCliente;

    do {
        opCliente = menuCliente();
        switch (opCliente) {
            case '1':
                telaCadastrarCliente();
                break;
            case '2':
                telaAtualizarCliente();
                break;
            case '3':
                telaPesquisarCliente();
                break;
            case '4':
                telaExcluirCliente();
                break;
            case '0':
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }
    } while (opCliente != '0');

    return opCliente;
}

char menuCliente(void) {
    char opcao[3];
    system("clear");
    printf("\n=== ÁREA DO CLIENTE ===\n");
    printf("1. Cadastrar\n");
    printf("2. Atualizar\n");
    printf("3. Pesquisar\n");
    printf("4. Excluir\n");
    printf("0. Sair\n");
    printf("Escolha: ");

    fgets(opcao, sizeof(opcao), stdin);
    return opcao[0];
}

void telaCadastrarCliente(void) {
    system("clear");
    if (qtdClientes >= 100) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    Cliente novo;
    printf("Nome do cliente: ");
    fgets(novo.nome, 80, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = '\0';

    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(novo.dataNascimento, 11, stdin);
    novo.dataNascimento[strcspn(novo.dataNascimento, "\n")] = '\0';

    printf("Telefone com DDD: ");
    fgets(novo.telefone, 20, stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = '\0';

    clientes[qtdClientes++] = novo;

    salvarClientesCSV(clientes, qtdClientes);
    printf("Cliente cadastrado com sucesso!\n");
    getchar(); 
}

void telaPesquisarCliente(void) {
    system("clear");
    char nome[80], data[11];
    printf("Digite o nome do cliente: ");
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(data, sizeof(data), stdin);
    data[strcspn(data, "\n")] = '\0';

    int idx = pesquisarCliente(nome, data);
    if (idx == -1) {
        printf("Cliente não encontrado.\n");
    } else {
        printf("Cliente encontrado!\n Nome: %s |Nascimento: %s |Telefone: %s\n",
               clientes[idx].nome,
               clientes[idx].dataNascimento,
               clientes[idx].telefone);
    }
    printf("\nPressione ENTER para voltar ao menu...");
    getchar(); 
}


void telaAtualizarCliente(void) {
    system("clear");
    char nome[80], data[11];
    printf("Digite o nome do cliente a atualizar: ");
    fgets(nome, 80, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = '\0';

    int idx = pesquisarCliente(nome, data);
    if (idx == -1) {
        printf("Cliente não encontrado.\n");
        return;
    }

    char tmp[80];
    printf("Novo nome (ENTER para manter): ");
    fgets(tmp, 80, stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) strcpy(clientes[idx].nome, tmp);

    printf("Nova data de nascimento (ENTER para manter): ");
    fgets(tmp, 11, stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) strcpy(clientes[idx].dataNascimento, tmp);

    printf("Novo telefone (ENTER para manter): ");
    fgets(tmp, 20, stdin);
    tmp[strcspn(tmp, "\n")] = '\0';
    if (strlen(tmp) > 0) strcpy(clientes[idx].telefone, tmp);

    salvarClientesCSV(clientes, qtdClientes);
    printf("Cliente atualizado com sucesso!\n");
}

void telaExcluirCliente(void) {
    system("clear");
    char nome[80], data[11];
    printf("Digite o nome do cliente a excluir: ");
    fgets(nome, 80, stdin);
    nome[strcspn(nome, "\n")] = '\0';

    printf("Digite a data de nascimento (dd/mm/aaaa): ");
    fgets(data, 11, stdin);
    data[strcspn(data, "\n")] = '\0';

    int idx = pesquisarCliente(nome, data);
    if (idx == -1) {
        printf("Cliente não encontrado.\n");
        return;
    }

    for (int i = idx; i < qtdClientes - 1; i++) {
        clientes[i] = clientes[i + 1];
    }
    qtdClientes--;

    salvarClientesCSV(clientes, qtdClientes);
    printf("Cliente excluído com sucesso!\n");
}

int pesquisarCliente(char nome[], char data[]) {
    system("clear");
    for (int i = 0; i < qtdClientes; i++) {
        if (strcmp(clientes[i].nome, nome) == 0 &&
            strcmp(clientes[i].dataNascimento, data) == 0) {
            return i;
        }
    }
    return -1;
}

void salvarClientesCSV(Cliente clientes[], int qtd) {
    FILE *fp = fopen("clientes.csv", "w");
    if (!fp) {
        printf("Erro ao abrir arquivo clientes.csv\n");
        return;
    }

    for (int i = 0; i < qtd; i++) {
        fprintf(fp, "%s;%s;%s\n",
                clientes[i].nome,
                clientes[i].dataNascimento,
                clientes[i].telefone);
    }

    fclose(fp);
}

void carregarClientesCSV(Cliente clientes[], int *qtd) {
    FILE *fp = fopen("clientes.csv", "r");
    if (!fp) {
        *qtd = 0;
        return;
    }

    char linha[150];
    *qtd = 0;
    while (fgets(linha, sizeof(linha), fp)) {
        linha[strcspn(linha, "\n")] = '\0';
        sscanf(linha, "%79[^;];%10[^;];%19[^\n]",
               clientes[*qtd].nome,
               clientes[*qtd].dataNascimento,
               clientes[*qtd].telefone);
        (*qtd)++;
    }

    fclose(fp);
}


// int main(void) {
//     carregarClientesCSV(clientes, &qtdClientes);
//     printf("Iniciando módulo de clientes...\n");
//     modCliente();
//     printf("\nEncerrando sistema...\n");
//     return 0;
// }
