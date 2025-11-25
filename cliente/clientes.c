#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "clientes.h"
#include "validacoes.h"
#include "ler_dados.h"
#include "erros.h"
#include "cores.h"

//  módulo principal 
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
                telaListarCliente();
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

//  Telas 
char menuCliente(void) {
    char opC;

    system("clear");
    printf(roxo negrito"\n★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│                 MENU DE CLIENTES              │\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│"ciano negrito" [1] Cadastrar Novo Cliente                    "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" [2] Atualizar Cliente                         "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" [3] Pesquisar Cliente                         "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" [4] Listar Clientes                           "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" [5] Excluir Cliente (lógica)                  "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" [0] Voltar ao Menu Principal                  "reset roxo negrito"│\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);

    opC = opcao();
    return opC;
}

void telaCadastrarCliente(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│            CADASTRO DE NOVO CLIENTE           │\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│"ciano negrito" Insira as informações abaixo:                "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" - Nome                                         "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" - Data de Nascimento                            "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" - Telefone                                     "reset roxo negrito"│\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    cadastrarCliente();
    esperarEnter();
}

void telaAtualizarCliente(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│               ATUALIZAR CLIENTE               │\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│"ciano negrito" Informe o ID do cliente a atualizar.          "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" Somente clientes ativos podem ser alterados.  "reset roxo negrito"│\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    atualizarCliente();
    esperarEnter();
}

void telaPesquisarCliente(void) {
    system("clear");
    printf(roxo negrito"★────────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│               PESQUISAR CLIENTE                │\n"reset);
    printf(roxo negrito"★────────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│"ciano negrito" Digite o ID do cliente para buscar seus dados.│\n"reset);
    printf(roxo negrito"★────────────────────────────────────────────────★\n"reset);
    pesquisarCliente();
    esperarEnter();
}

void telaListarCliente(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│                LISTA DE CLIENTES              │\n"reset);
    listarClientes();
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    esperarEnter();
}

void telaExcluirCliente(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│                EXCLUSÃO DE CLIENTE            │\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│"ciano negrito" A exclusão será LÓGICA (cliente inativo).    "reset roxo negrito"│\n"reset);
    printf(roxo negrito"│"ciano negrito" Deseja continuar? (S/N)                      "reset roxo negrito"│\n"reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    excluirCliente();
    esperarEnter();
}

//  Operações 
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
}

void listarClientes(void) {
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    Cliente c;
    int encontrou = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.status == 1) {
            printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
            printf(roxo negrito"│"ciano negrito" ID: %-40s \n"reset, c.id);
            printf(roxo negrito"│"ciano negrito" Nome: %-38s \n"reset, c.nome);
            printf(roxo negrito"│"ciano negrito" Nascimento: %-32s \n"reset, c.dataNascimento);
            printf(roxo negrito"│"ciano negrito" Telefone: %-35s \n"reset, c.telefone);
            encontrou = 1;
        }
    }

    fclose(fp);
    if (!encontrou)
        printf("Nenhum cliente ativo encontrado.\n");
}

void atualizarCliente(void) {
    char *id = lerIdCliente();
    FILE *fp = fopen("clientes.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        free(id);
        esperarEnter();
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if ((strcmp(c.id, id) == 0) && c.status == 1) {
            printf(ciano negrito"Novo nome: "reset);
            char *nome = lerNome();
            strcpy(c.nome, nome);
            free(nome);

            printf(ciano negrito"Nova data de nascimento: "reset);
            char *nasc = lerNascimento();
            strcpy(c.dataNascimento, nasc);
            free(nasc);

            printf(ciano negrito"Novo telefone: "reset);
            char *tel = lerTelefone();
            strcpy(c.telefone, tel);
            free(tel);

            fseek(fp, -(long) sizeof(Cliente), SEEK_CUR);
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
}

void excluirCliente(void) {
    char *id = lerIdCliente();
    FILE *fp = fopen("clientes.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        free(id);
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (strcmp(c.id, id) == 0 && c.status == 1) {
            c.status = 0;
            fseek(fp, -(long) sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, fp);
            encontrado = 1;
            break;
        }
    }

    fclose(fp);
    free(id);

    if (encontrado)
        printf("\nCliente excluído logicamente com sucesso!\n");
    else
        printf("\nCliente não encontrado ou já inativo.\n");
}

void pesquisarCliente(void) {
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) {
        printf("Nenhum cliente cadastrado.\n");
        esperarEnter();
        return;
    }

    char *idBusca = lerIdCliente();
    Cliente c;
    int encontrou = 0;

    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.status == 1 && strcmp(c.id, idBusca) == 0) {
            printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
            printf(roxo negrito"│"ciano negrito" ID: %-40s "roxo negrito"│\n"reset, c.id);
            printf(roxo negrito"│"ciano negrito" Nome: %-38s "roxo negrito"│\n"reset, c.nome);
            printf(roxo negrito"│"ciano negrito" Nascimento: %-32s "roxo negrito"│\n"reset, c.dataNascimento);
            printf(roxo negrito"│"ciano negrito" Telefone: %-35s "roxo negrito"│\n"reset, c.telefone);
            printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
            encontrou = 1;
        }
    }

    fclose(fp);
    free(idBusca);
    if (!encontrou)
        printf("Nenhum cliente encontrado com esse ID.\n");
}

//  IDs 
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