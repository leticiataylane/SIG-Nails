#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "telas_servicos.h"

void atualizarCSVServicos() {
    FILE *bin = fopen("servicos.dat", "rb");
    FILE *csv = fopen("servicos.csv", "w");
    if (!bin || !csv) {
        if (bin) fclose(bin);
        if (csv) fclose(csv);
        return;
    }

    fprintf(csv, "ID,Nome,Preco,Status\n");

    Servico s;
    while (fread(&s, sizeof(Servico), 1, bin) == 1) {
        fprintf(csv, "%d,%s,%.2f,%d\n", s.id, s.nome, s.preco, s.status);
    }

    fclose(bin);
    fclose(csv);
}

void cadastrarServico() {
    Servico s;
    FILE *fp;
    int maiorId = 0;

    fp = fopen("servicos.dat", "rb");
    if (fp) {
        Servico temp;
        while (fread(&temp, sizeof(Servico), 1, fp) == 1) {
            if (temp.id > maiorId) maiorId = temp.id;
        }
        fclose(fp);
    }

    s.id = maiorId + 1;

    printf("\n=== CADASTRAR SERVIÇO ===\n");
    getchar();
    printf("Nome do serviço: ");
    fgets(s.nome, sizeof(s.nome), stdin);
    s.nome[strcspn(s.nome, "\n")] = '\0';

    printf("Preço: ");
    scanf("%f", &s.preco);
    getchar();

    s.status = 1;

    fp = fopen("servicos.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }
    fwrite(&s, sizeof(Servico), 1, fp);
    fclose(fp);

    atualizarCSVServicos();

    printf("Serviço cadastrado com sucesso! ID: %d\n", s.id);
}

void listarServicos() {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Nenhum serviço cadastrado.\n");
        return;
    }

    Servico s;
    int encontrou = 0;

    printf("\n=== LISTA DE SERVIÇOS ATIVOS ===\n");
    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.status == 1) {
            printf("ID: %d | Nome: %s | Preço: %.2f\n", s.id, s.nome, s.preco);
            encontrou = 1;
        }
    }

    fclose(fp);

    if (!encontrou)
        printf("Nenhum serviço ativo encontrado.\n");
}

void atualizarServico() {
    int id;
    printf("\n=== ATUALIZAR SERVIÇO ===\n");
    printf("Digite o ID do serviço: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.id == id && s.status == 1) {
            printf("Novo nome: ");
            fgets(s.nome, sizeof(s.nome), stdin);
            s.nome[strcspn(s.nome, "\n")] = '\0';

            printf("Novo preço: ");
            scanf("%f", &s.preco);
            getchar();

            fseek(fp, -sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (encontrado) atualizarCSVServicos();
    if (!encontrado) printf("Serviço não encontrado ou inativo.\n");
    else printf("Serviço atualizado com sucesso!\n");
}

void excluirServico() {
    int id;
    printf("\n=== EXCLUIR SERVIÇO ===\n");
    printf("Digite o ID do serviço: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.id == id && s.status == 1) {
            s.status = 0;
            fseek(fp, -sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (encontrado) atualizarCSVServicos();
    if (!encontrado) printf("Serviço não encontrado.\n");
    else printf("Serviço excluído com sucesso!\n");
}

void menuServico() {
    int opcao;

    do {
        printf("\n=== MENU SERVIÇOS ===\n");
        printf("1 - Cadastrar serviço\n");
        printf("2 - Listar serviços\n");
        printf("3 - Atualizar serviço\n");
        printf("4 - Excluir serviço\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1: cadastrarServico(); break;
            case 2: listarServicos(); break;
            case 3: atualizarServico(); break;
            case 4: excluirServico(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }

    } while (opcao != 0);
}

// int main() {
//     menuServico();
//     return 0;
// }