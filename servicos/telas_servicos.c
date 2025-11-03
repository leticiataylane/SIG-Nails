#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
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
                pesquisarServico(); 
                break;
            case '4':
                telaListarServico();
                break;
            case '5':
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

// --- Telas ---
char menuServico(void) {
    char op;

    system("clear");
    printf("\n=== MENU SERVIÇOS ===\n");
    printf("1 - Cadastrar serviço\n");
    printf("2 - Listar serviços\n");
    printf("3 - Pesquisar serviço\n");
    printf("4 - Atualizar serviço\n");
    printf("5 - Excluir serviço\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    op = opcao();
    return op;
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
    printf("pesquisa de serviços:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void telaListarServico(void) {
    printf("listagem de serviços:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

void telaExcluirServico(void) {
    printf("exclusão de serviços:\n");
    printf("|ENTER| para sair\n");
    esperarEnter();
}

// --- funcoes
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
    s.preco = lerDinheiro();  
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
            s.preco = lerDinheiro();
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

//funcao de pesquisar o servico com id
void pesquisarServico(void) {
    system("clear");
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Nenhum serviço cadastrado.\n");
        esperarEnter();
        return;
    }

    char *idBusca = lerIdServico();
    Servico s;
    int encontrou = 0;

    printf("\n=== RESULTADOS DA PESQUISA ===\n");
    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.status == 1 && strcmp(s.id, idBusca) == 0) {
            printf("ID: %s | Nome: %s | Preço: %.2f\n", s.id, s.nome, s.preco);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum serviço encontrado com esse ID.\n");

    free(idBusca);
    fclose(fp);
    esperarEnter();
}
// --- IDs ---

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
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) return 0;

    Servico s; 
    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (strcmp(s.id, idStr) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}