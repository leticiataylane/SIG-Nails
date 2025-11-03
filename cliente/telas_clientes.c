#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "telas_clientes.h"
#include "../utils/validacoes.h"
#include "../utils/ler_dados.h"
#include "../geral/erros.h"
#include "../geral/cores.h"


// --- funcao principal
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
                telaListarCliente();
                break;
            case '4':
                telaPesquisarCliente();
                break;
            case '5':
                telaExcluirCliente();
                break;
            case '0':
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while (opCliente != '0');

    return opCliente;
}

// --- telas (ainda a atualizar)
void telaCadastrarCliente(void) {
    printf("=== CADASTRO DE CLIENTE ===\n");
    cadastrarCliente();
}

void telaAtualizarCliente(void) {
    printf("=== ATUALIZAR CLIENTE ===\n");
    atualizarCliente();
}

void telaListarCliente(void) {
    printf("=== LISTAR CLIENTES ===\n");
    listarClientes();
}

void telaPesquisarCliente(void) {
    printf("=== PESQUISAR CLIENTE ===\n");
    pesquisarCliente();
}

void telaExcluirCliente(void) {
    printf("=== EXCLUIR CLIENTE ===\n");
    excluirCliente();
}

// --- operaçoes
void cadastrarCliente(void) {
    system("clear");
    Cliente c;
    FILE *fp;

    char *idStr = gerarIdCliente();
    strcpy(c.id, idStr);
    free(idStr);

    char *nome = lerNome();
    strcpy(c.nome, nome);
    free(nome);

    char *nascimento = lerNascimento();
    strcpy(c.dataNascimento, nascimento);
    free(nascimento);

    char *telefone = lerTelefone();
    strcpy(c.telefone, telefone);
    free(telefone);

    c.status = 1;

    fp = fopen("clientes.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        esperarEnter();
        return;
    }

    fwrite(&c, sizeof(Cliente), 1, fp);
    fclose(fp);

    printf("\nCliente cadastrado com sucesso! ID: %s\n", c.id);
    esperarEnter();
}

void listarClientes(void) {
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
            printf("ID: %s | Nome: %s | Nascimento: %s | Telefone: %s\n",
                   c.id, c.nome, c.dataNascimento, c.telefone);
            encontrou = 1;
        }
    }

    fclose(fp);

    if (!encontrou)
        printf("Nenhum cliente ativo encontrado.\n");

    esperarEnter();
}

void atualizarCliente(void) {
    system("clear");
    printf("\n=== ATUALIZAR CLIENTE ===\n");

    char *id = lerIdCliente();

    FILE *fp = fopen("clientes.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        esperarEnter();
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if ((strcmp(c.id, id) == 0) && c.status == 1) {

            char *nome = lerNome();
            strcpy(c.nome, nome);
            free(nome);

            char *nasc = lerNascimento();
            strcpy(c.dataNascimento, nasc);
            free(nasc);

            char *tel = lerTelefone();
            strcpy(c.telefone, tel);
            free(tel);

            fseek(fp, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, fp);
            encontrado = 1;
            break;
        }
    }

    free(id);
    fclose(fp);

    if (encontrado)
        printf("\nCliente atualizado com sucesso!\n");
    else
        printf("\nCliente não encontrado ou inativo.\n");

    esperarEnter();
}

void excluirCliente(void) {
    system("clear");
    printf("\n=== EXCLUIR CLIENTE ===\n");

    char *id = lerIdCliente();

    FILE *origem = fopen("clientes.dat", "rb");
    if (!origem) {
        printf("Erro ao abrir o arquivo ou nenhum cliente existente.\n");
        esperarEnter();
        return;
    }

    FILE *temp = fopen("temp.dat", "wb");
    if (!temp) {
        fclose(origem);
        printf("Erro ao criar arquivo temporário.\n");
        esperarEnter();
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, origem) == 1) {
        if (strcmp(c.id, id) != 0)
            fwrite(&c, sizeof(Cliente), 1, temp);
        else
            encontrado = 1;
    }

    free(id);
    fclose(origem);
    fclose(temp);

    if (!encontrado) {
        printf("\nCliente não encontrado.\n");
        remove("temp.dat");
    } else {
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        printf("\nCliente excluído com sucesso!\n");
    }

    esperarEnter();
}

void pesquisarCliente(void) {
    system("clear");
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) {
        printf("Nenhum cliente cadastrado.\n");
        esperarEnter();
        return;
    }

    char *idBusca = lerIdCliente();
    Cliente c;
    int encontrou = 0;

    printf("\n=== RESULTADOS DA PESQUISA ===\n");
    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.status == 1 && strcmp(c.id, idBusca) == 0) {
            printf("ID: %s | Nome: %s | Nascimento: %s | Telefone: %s\n",
                   c.id, c.nome, c.dataNascimento, c.telefone);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum cliente encontrado com esse ID.\n");

    free(idBusca);
    fclose(fp);
    esperarEnter();
}

// --- menu e IDs
char menuCliente(void) {
    char op;

    system("clear");
    printf("\n=== MENU CLIENTES ===\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Listar clientes\n");
    printf("3 - Pesquisar cliente\n");
    printf("4 - Excluir cliente\n");
    printf("0 - Sair\n");
    op = opcao();
    return op;
}

char* gerarIdCliente(void) {
    char *idStr = malloc(10 * sizeof(char));
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000;
        sprintf(idStr, "%d", id);
    } while (idExisteCliente(idStr));

    return idStr;
}

int idExisteCliente(char *idStr) {
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) return 0;

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (strcmp(c.id, idStr) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}