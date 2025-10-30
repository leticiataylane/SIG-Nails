#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "telas_servicos.h"
#include "../utils/ler_dados.h"
#include "../utils/limpeza.h"
#include "../utils/validacoes.h"
#include "../geral/erros.h"

char modServico(void) {
    char opServico;

    do {
        opServico = menuServico();
        switch (opServico) {
            case '1':
                telaCadastrarServico();
                break;
            case '2':
                telaAtualizarServico();
                break;
            case '3':
                telaPesquisarServico();
                break;
            case '4':
                telaExcluirServico();
                break;
            case '0':
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while (opServico != '0');

    return opServico;
}

void telaCadastrarServico(void) {
    printf("dados necessários para cadastro:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void telaAtualizarServico(void) {
    printf("o que atualizar?\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void telaPesquisarServico(void) {
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void telaListarServico(void) {
    printf("listagem de serviços:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void telaExcluirServico(void) {
    printf("nome e data de nascimento para pesquisa e exclusão:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void cadastrarServico(void) {
    system("clear");
    Servico s;
    FILE *fp;

    char *idStr = gerarIdServico();
    strcpy(s.id, idStr);
    free(idStr);

    printf("\n=== CADASTRAR SERVIÇO ===\n");

    printf("Nome do serviço: ");
    setbuf(stdin, NULL);
    fgets(s.nome, sizeof(s.nome), stdin);
    s.nome[strcspn(s.nome, "\n")] = '\0';

    printf("Preço: ");
    scanf("%f", &s.preco);
    setbuf(stdin, NULL);

    s.status = 1;

    fp = fopen("servicos.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        esperarEnter();
        return;
    }
    fwrite(&s, sizeof(Servico), 1, fp);
    fclose(fp);

    printf("\nServiço cadastrado com sucesso! ID: %s\n", s.id);
    esperarEnter();
}

void listarServicos(void) {
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
            printf("ID: %s | Nome: %s | Preço: %.2f\n", s.id, s.nome, s.preco);
            encontrou = 1;
        }
    }

    fclose(fp);

    if (!encontrou)
        printf("Nenhum serviço ativo encontrado.\n");

    esperarEnter();
}

void atualizarServico(void) {
    system("clear");

    printf("\n=== ATUALIZAR SERVIÇO ===\n");
    printf("Digite o ID do serviço: ");
    char *id = lerIdServico();

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        esperarEnter();
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if ((strcmp(s.id, id) == 0) && s.status == 1) {
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
    free(id);
    fclose(fp);

    if (encontrado)
        printf("\nServiço atualizado com sucesso!\n");
    else
        printf("\nServiço não encontrado ou inativo.\n");

    esperarEnter();
}

void excluirServico(void) {
    system("clear");

    printf("\n=== EXCLUIR SERVIÇO ===\n");
    printf("Digite o ID do serviço: ");
    char *id = lerIdServico();

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        esperarEnter();
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if ((strcmp(s.id, id) == 0) && s.status == 1) {
            s.status = 0;
            fseek(fp, -sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            encontrado = 1;
            break;
        }
    }
    free(id);
    fclose(fp);

    if (!encontrado)
        printf("Serviço não encontrado.\n");
    else
        printf("\nServiço excluído com sucesso!\n");

    esperarEnter();
}

char menuServico(void) {
    char op;

    system("clear");
    printf("\n=== MENU SERVIÇOS ===\n");
    printf("1 - Cadastrar serviço\n");
    printf("2 - Listar serviços\n");
    printf("3 - Atualizar serviço\n");
    printf("4 - Excluir serviço\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    op = opcao(); // função externa (provavelmente em validacoes.h)
    return op;
}

char* gerarIdServico(void) {
    char *idStr = malloc(10 * sizeof(char)); 
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000; // gera 1000–9999
        sprintf(idStr, "%d", id);
    } while (idExisteServico(idStr));

    return idStr;
}

int idExisteServico(char *idStr) {
    FILE *fp = fopen("servicos.dat", "rb"); // corrige maiúscula
    if (!fp) return 0;

    Servico s; 
    while (fread(&s, sizeof(Servico), 1, fp)) {
        if (strcmp(s.id, idStr) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// int main(void) {
//     srand(time(NULL)); // garante IDs diferentes
//     modServico();
//     return 0;
// }