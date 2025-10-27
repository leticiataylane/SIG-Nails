#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "telas_servicos.h"

void esperarEnter() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n');
}

int idExisteServico(int id) {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) return 0;

    Servico s;
    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.id == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

int gerarIdServico(void) {
    srand(time(NULL));
    int id;
    do {
        id = rand() % 9000 + 1000; // Gera de 1000 a 9999
    } while (idExisteServico(id));
    return id;
}

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
    system("clear");
    Servico s;

    s.id = gerarIdServico(); // Geração automática do ID

    printf("\n=== CADASTRAR SERVIÇO ===\n");

    printf("Nome do serviço: ");
    setbuf(stdin, NULL);
    fgets(s.nome, sizeof(s.nome), stdin);
    s.nome[strcspn(s.nome, "\n")] = '\0';

    printf("Preço: ");
    scanf("%f", &s.preco);
    setbuf(stdin, NULL);

    s.status = 1;

    FILE *fp = fopen("servicos.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        esperarEnter();
        return;
    }
    fwrite(&s, sizeof(Servico), 1, fp);
    fclose(fp);

    atualizarCSVServicos();

    printf("\nServiço cadastrado com sucesso! ID: %d\n", s.id);
    esperarEnter();
}

void listarServicos() {
    system("clear");
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Nenhum serviço cadastrado.\n");
        esperarEnter();
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

    esperarEnter();
}

void atualizarServico() {
    system("clear");
    int id;
    printf("\n=== ATUALIZAR SERVIÇO ===\n");
    printf("Digite o ID do serviço: ");
    scanf("%d", &id);
    setbuf(stdin, NULL);

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        esperarEnter();
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.id == id && s.status == 1) {
            printf("Novo nome: ");
            setbuf(stdin, NULL);
            fgets(s.nome, sizeof(s.nome), stdin);
            s.nome[strcspn(s.nome, "\n")] = '\0';

            printf("Novo preço: ");
            scanf("%f", &s.preco);
            setbuf(stdin, NULL);

            fseek(fp, -sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (encontrado) {
        atualizarCSVServicos();
        printf("\nServiço atualizado com sucesso!\n");
    } else {
        printf("\nServiço não encontrado ou inativo.\n");
    }

    esperarEnter();
}

void excluirServico() {
    system("clear");
    int id;
    printf("\n=== EXCLUIR SERVIÇO ===\n");
    printf("Digite o ID do serviço: ");
    scanf("%d", &id);
    setbuf(stdin, NULL);

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        esperarEnter();
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
    else printf("\nServiço excluído com sucesso!\n");

    esperarEnter();
}

void menuServico() {
    int opcao;

    do {
        system("clear");
        printf("\n=== MENU SERVIÇOS ===\n");
        printf("1 - Cadastrar serviço\n");
        printf("2 - Listar serviços\n");
        printf("3 - Atualizar serviço\n");
        printf("4 - Excluir serviço\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        setbuf(stdin, NULL);

        switch (opcao) {
            case 1: cadastrarServico(); break;
            case 2: listarServicos(); break;
            case 3: atualizarServico(); break;
            case 4: excluirServico(); break;
            case 0: printf("\nSaindo...\n"); break;
            default: printf("\nOpção inválida!\n"); esperarEnter(); break;
        }

    } while (opcao != 0);
}

int main() {
    menuServico();
    return 0;
}
