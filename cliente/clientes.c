#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "clientes.h"
#include "servicos.h"
#include "validacoes.h"
#include "ler_dados.h"
#include "erros.h"
#include "cores.h"
#include "funcionarios.h"
#include "agendamentos.h"
#include "relatorios.h"

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
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│                 MENU DE CLIENTES              │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│ [1] CADASTRAR                                 │\n");
    printf("│ [2] ATUALIZAR                                 │\n");
    printf("│ [3] PESQUISAR                                 │\n");
    printf("│ [4] LISTAR                                    │\n");
    printf("│ [5] EXCLUIR                                   │\n");
    printf("│ [0] VOLTAR AO MENU PRINCIPAL                  │\n");
    printf("╰───────────────────────────────────────────────╯\n");

    opC = opcao();
    return opC;
}

void telaCadastrarCliente(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│            CADASTRO DE NOVO CLIENTE           │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│ Insira as informações abaixo:                 │\n");
    printf("│ - Nome                                        │\n");
    printf("│ - Data de Nascimento                          │\n");
    printf("│ - Telefone                                    │\n");
    printf("╰───────────────────────────────────────────────╯\n");
    cadastrarCliente();
    esperarEnter();
}

void telaAtualizarCliente(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│               ATUALIZAR CLIENTE               │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│ Informe o ID do cliente a atualizar.          │\n");
    printf("│ Somente clientes ativos podem ser alterados.  │\n");
    printf("╰───────────────────────────────────────────────╯\n");
    atualizarCliente();
    esperarEnter();
}

void telaPesquisarCliente(void) {
    system("clear");
    printf("╭────────────────────────────────────────────────╮\n");
    printf("│               PESQUISAR CLIENTE                │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│ Digite o ID do cliente para buscar seus dados. │\n");
    printf("╰────────────────────────────────────────────────╯\n");
    pesquisarCliente();
    esperarEnter();
}

void telaListarCliente(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│                LISTA DE CLIENTES              │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("| Veja a seguir a lista de clientes cadastrados.|\n");
    printf("╰───────────────────────────────────────────────╯\n");
    listarClientes();
    esperarEnter();
}

void telaExcluirCliente(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│                EXCLUSÃO DE CLIENTE            │\n");
    printf("├───────────────────────────────────────────────┤\n");   
    printf("│ A exclusão LÓGICA (cliente inativo).          │\n");
    printf("╰───────────────────────────────────────────────╯\n");
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
    printf("╭─────────────────────────── CLIENTES ENCONTRADOS ───────────────────────────╮\n");
    printf("│ %-7s│ %-34s│ %-14s│ %-14s│\n",
           "ID", "Nome", "Nascimento", "Telefone");
    printf("├────────┼───────────────────────────────────┼───────────────┼───────────────┤\n");
    while (fread(&c, sizeof(Cliente), 1, fp) == 1) {
        if (c.status == 1) {
            printf("│ %-7s│ %-35s│ %-14s│ %-14s│\n",
                   c.id, c.nome, c.dataNascimento, c.telefone);
            encontrou = 1;
        }
    }
    printf("╰────────────────────────────────────────────────────────────────────────────╯\n");

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
            printf("Novo nome: ");
            char *nome = lerNome();
            strcpy(c.nome, nome);
            free(nome);

            printf("Nova data de nascimento: ");
            char *nasc = lerNascimento();
            strcpy(c.dataNascimento, nasc);
            free(nasc);

            printf("Novo telefone: ");
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
        printf("\nCliente excluído com sucesso!\n");
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

            printf("╭─────────────────────────── CLIENTES ENCONTRADOS ───────────────────────────╮\n");
            printf("│ %-7s│ %-34s│ %-14s│ %-14s│\n",
                   "ID", "Nome", "Nascimento", "Telefone");
            printf("├────────┼───────────────────────────────────┼───────────────┼───────────────┤\n");

            printf("│ %-7s│ %-35s│ %-14s│ %-14s│\n",
                   c.id, c.nome, c.dataNascimento, c.telefone);

            printf("╰────────────────────────────────────────────────────────────────────────────╯\n");

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