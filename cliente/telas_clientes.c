#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "telas_clientes.h"

void esperarEnter() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n'); // espera apenas o ENTER
}

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
    system("clear");
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

    printf("Nome: ");
    setbuf(stdin, NULL); // limpa buffer
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
        esperarEnter();
        return;
    }
    fwrite(&c, sizeof(Cliente), 1, fp);
    fclose(fp);

    atualizarCSVClientes();

    printf("\nCliente cadastrado com sucesso! ID: %d\n", c.id);
    esperarEnter();
}

void listarClientes() {
    system("clear");
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) {
        printf("Nenhum cliente cadastrado.\n");
        esperarEnter();
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

    esperarEnter();
}

void atualizarCliente() {
    system("clear");
    int id;
    printf("\n=== ATUALIZAR CLIENTE ===\n");
    printf("Digite o ID do cliente: ");
    scanf("%d", &id);
    setbuf(stdin, NULL); // limpa buffer

    FILE *fp = fopen("clientes.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        esperarEnter();
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

    if (encontrado) {
        atualizarCSVClientes();
        printf("\nCliente atualizado com sucesso!\n");
    } else {
        printf("\nCliente não encontrado ou inativo.\n");
    }

    esperarEnter();
}

void excluirCliente() {
    system("clear");
    int id;
    printf("\n=== EXCLUIR CLIENTE (FISICAMENTE) ===\n");
    printf("Digite o ID do cliente: ");
    scanf("%d", &id);
    setbuf(stdin, NULL); // limpa buffer

    FILE *origem = fopen("clientes.dat", "rb");
    if (!origem) {
        printf("Erro ao abrir o arquivo ou nenhum cliente existente.\n");
        esperarEnter();
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        fclose(origem);
        printf("Erro ao criar arquivo temporario.\n");
        esperarEnter();
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, origem) == 1) {
        if (c.id != id) {
            fwrite(&c, sizeof(Cliente), 1, temp);
        } else {
            encontrado = 1;
        }
    }

    fclose(origem);
    fclose(temp);

    if (!encontrado) {
        printf("\nCliente nao encontrado.\n");
        remove("temp.dat"); 
    } else {
        remove("clientes.dat");         
        rename("temp.dat", "clientes.dat"); 
        atualizarCSVClientes();         
        printf("\nCliente excluido com sucesso (fisicamente)!\n");
    }

    esperarEnter();
}

void menu() {
    int opcao;

    do {
        system("clear");
        printf("\n=== MENU CLIENTES ===\n");
        printf("1 - Cadastrar cliente\n");
        printf("2 - Listar clientes\n");
        printf("3 - Atualizar cliente\n");
        printf("4 - Excluir cliente\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        setbuf(stdin, NULL); // limpa buffer

        switch (opcao) {
            case 1: cadastrarCliente(); break;
            case 2: listarClientes(); break;
            case 3: atualizarCliente(); break;
            case 4: excluirCliente(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n"); esperarEnter(); break;
        }

    } while (opcao != 0);
}

// int main() {
//     menu();
//     return 0;
// }