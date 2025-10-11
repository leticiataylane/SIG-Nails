#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "telas_clientes.h"

void atualizarCSVClientes() {
    FILE *bin = fopen("clientes.dat", "rb");
    FILE *csv = fopen("clientes.csv", "w");
    if (!bin || !csv) {
        if (bin) fclose(bin);
        if (csv) fclose(csv);
        return;
    }

    fprintf(csv, "ID,Nome,DataNascimento,Telefone,Status\n");

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, bin) == 1) {
        fprintf(csv, "%d,%s,%s,%s,%d\n", c.id, c.nome, c.dataNascimento, c.telefone, c.status);
    }

    fclose(bin);
    fclose(csv);
}

void cadastrarCliente() {
    Cliente c;
    FILE *fp;
    int maiorId = 0;

    fp = fopen("clientes.dat", "rb");
    if (fp) {
        Cliente temp;
        while (fread(&temp, sizeof(Cliente), 1, fp) == 1) {
            if (temp.id > maiorId) maiorId = temp.id;
        }
        fclose(fp);
    }

    c.id = maiorId + 1;

    printf("\n=== CADASTRAR CLIENTE ===\n");
    getchar();
    printf("Nome: ");
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(c.dataNascimento, sizeof(c.dataNascimento), stdin);
    c.dataNascimento[strcspn(c.dataNascimento, "\n")] = '\0';

    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    c.status = 1;

    fp = fopen("clientes.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fwrite(&c, sizeof(Cliente), 1, fp);
    fclose(fp);

    atualizarCSVClientes();

    printf("Cliente cadastrado com sucesso! ID: %d\n", c.id);
}

void listarClientes() {
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente c;
    int encontrou = 0;

    printf("\n=== LISTA DE CLIENTES ATIVOS ===\n");
    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.status == 1) {
            printf("ID: %d | Nome: %s | Nascimento: %s | Telefone: %s\n",
                   c.id, c.nome, c.dataNascimento, c.telefone);
            encontrou = 1;
        }
    }

    fclose(fp);

    if (!encontrou)
        printf("Nenhum cliente ativo encontrado.\n");
}

void atualizarCliente() {
    int id;
    printf("\n=== ATUALIZAR CLIENTE ===\n");
    printf("Digite o ID do cliente: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen("clientes.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.id == id && c.status == 1) {
            printf("Novo nome: ");
            fgets(c.nome, sizeof(c.nome), stdin);
            c.nome[strcspn(c.nome, "\n")] = '\0';

            printf("Nova data de nascimento: ");
            fgets(c.dataNascimento, sizeof(c.dataNascimento), stdin);
            c.dataNascimento[strcspn(c.dataNascimento, "\n")] = '\0';

            printf("Novo telefone: ");
            fgets(c.telefone, sizeof(c.telefone), stdin);
            c.telefone[strcspn(c.telefone, "\n")] = '\0';

            fseek(fp, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (encontrado) atualizarCSVClientes();
    if (!encontrado) printf("Cliente não encontrado ou inativo.\n");
    else printf("Cliente atualizado com sucesso!\n");
}

void excluirCliente() {
    int id;
    printf("\n=== EXCLUIR CLIENTE ===\n");
    printf("Digite o ID do cliente: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen("clientes.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.id == id && c.status == 1) {
            c.status = 0;
            fseek(fp, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (encontrado) atualizarCSVClientes();
    if (!encontrado) printf("Cliente não encontrado.\n");
    else printf("Cliente excluído com sucesso!\n");
}

void menu() {
    int opcao;

    do {
        printf("\n=== MENU CLIENTES ===\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Atualizar cliente\n");
        printf("4 - Excluir cliente\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: atualizarCliente(); break;
            case 4: excluirCliente(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}