#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "telas_servicos.h"


int gerarNovoIdServico() {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) return 1; 

    Servico s;
    int maiorId = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.id > maiorId)
            maiorId = s.id;
    }

    fclose(fp);
    return maiorId + 1;
}

void cadastrarServico() {
    Servico s;
    s.id = gerarNovoIdServico();

    printf("\n=== CADASTRAR SERVIÇO ===\n");
    printf("Nome do serviço: ");
    fgets(s.nome, 50, stdin);
    s.nome[strcspn(s.nome, "\n")] = '\0';

    printf("Preço do serviço: R$ ");
    scanf("%f", &s.preco);
    getchar(); 

    s.status = 1;

    FILE *fp = fopen("servicos.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    fwrite(&s, sizeof(Servico), 1, fp);
    fclose(fp);

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
            printf("ID: %d | Nome: %-30s | Preço: R$ %.2f\n",
                   s.id, s.nome, s.preco);
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
            printf("Novo nome (ENTER para manter): ");
            char tmp[50];
            fgets(tmp, sizeof(tmp), stdin);
            tmp[strcspn(tmp, "\n")] = '\0';
            if (strlen(tmp) > 0) strcpy(s.nome, tmp);

            printf("Novo preço (0 para manter): R$ ");
            float novoPreco;
            scanf("%f", &novoPreco);
            getchar();
            if (novoPreco > 0) s.preco = novoPreco;

            fseek(fp, -sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            printf("Serviço atualizado com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado)
        printf("Serviço não encontrado ou inativo.\n");
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
            printf("Serviço excluído com sucesso!\n");
            encontrado = 1;
            break;
        }
    }

    fclose(fp);

    if (!encontrado)
        printf("Serviço não encontrado.\n");
}


void menuServico() {
    int opcao;

    do {
        printf("\n=== MENU DE SERVIÇOS ===\n");
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


int main(void) {
    menuServico();
    return 0;
}