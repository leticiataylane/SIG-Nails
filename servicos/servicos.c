#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include "servicos.h"
#include "ler_dados.h"
#include "limpeza.h"
#include "validacoes.h"
#include "erros.h"
#include "cores.h"

// modulos
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

// Telas

char menuServico(void) {
    char op;

    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│                 "roxo"MENU DE SERVIÇOS"reset"              │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│ "roxo"[1] CADASTRAR                "reset"                 │\n");
    printf("│ "roxo"[2] ATUALIZAR                "reset"                 │\n");
    printf("│ "roxo"[3] PESQUISAR                "reset"                 │\n");
    printf("│ "roxo"[4] LISTAR                   "reset"                 │\n");
    printf("│ "roxo"[5] EXCLUIR                  "reset"                 │\n");
    printf("│ "roxo"[0] VOLTAR AO MENU PRINCIPAL "reset"                 │\n");
    printf("╰───────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void telaCadastrarServico(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│          "roxo"CADASTRO DE NOVO SERVIÇO"reset"             │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│  Insira as informações abaixo:                │\n");
    printf("│  - Nome do Serviço                            │\n");
    printf("│  - Preço                                      │\n");
    printf("╰───────────────────────────────────────────────╯\n");
    cadastrarServico();
    esperarEnter();
}

void telaAtualizarServico(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│              "roxo"ATUALIZAR SERVIÇO"reset"                │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("| Informe o ID do serviço que deseja atualizar. │\n");
    printf("| Apenas serviços ativos podem ser alterados.   │\n");
    printf("╰───────────────────────────────────────────────╯\n");
    atualizarServico();
    esperarEnter();
}

void telaPesquisarServico(void) {
    system("clear");
    printf("╭────────────────────────────────────────────────╮\n");
    printf("│               "roxo"PESQUISAR SERVIÇO"reset"                │\n");
    printf("├────────────────────────────────────────────────┤\n");
    printf("│  Digite o ID do serviço para buscar seus dados │\n");
    printf("╰────────────────────────────────────────────────╯\n");
    pesquisarServico();
    esperarEnter();
}

void telaListarServico(void) {
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│                "roxo"LISTA DE SERVIÇOS"reset"              │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("| Veja abaixo todos os serviços cadastrados.    │\n");
    printf("╰───────────────────────────────────────────────╯\n");
    listarServicos();
    esperarEnter();
}

void telaExcluirServico(void) {
    char op;
    system("clear");
    printf("╭───────────────────────────────────────────────╮\n");
    printf("│                "roxo"EXCLUIR SERVIÇO"reset"                │\n");
    printf("├───────────────────────────────────────────────┤\n");
    printf("│ [1] Exclusão Lógica (Inativar Serviço)        │\n");
    printf("│ [0] Voltar                                    │\n");
    printf("╰───────────────────────────────────────────────╯\n");

    do {
        op = opcao();
        switch (op) {
            case '1':
                excluirServico();
                break;
            case '0':
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while (op != '0');

    esperarEnter();
}

// funcoes

void cadastrarServico(void) {
    system("clear");
    Servico s;
    FILE *fp;

    char *idStr = gerarIdServico();
    strcpy(s.id, idStr);
    free(idStr);

    printf("\n CADASTRAR SERVIÇO \n\n");

    char *nome = lerNomeCurto("Nome do serviço: ");
    strcpy(s.nome, nome);
    free(nome);

    s.preco = lerPrecoServico();

    s.status = 1;

    fp = fopen("servicos.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        esperarEnter();
        return;
    }
    fwrite(&s, sizeof(Servico), 1, fp);
    fclose(fp);

    printf("\n Serviço cadastrado com sucesso! ID: %s \n", s.id);
}

void listarServicos(void) {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Nenhum serviço cadastrado.\n");
        return;
    }
    Servico s;
    int encontrou = 0;
    printf("╭──────────────────────────── LISTA DE SERVIÇOS ───────────────────────────╮\n");
    printf("│ %-7s│ %-49s│ %-14s│\n", "ID", "Nome", "Preço");
    printf("├────────┼──────────────────────────────────────────────────┼──────────────┤\n");
    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.status == 1) {
            printf("│ %-7s│ %-49s│ R$ %-10.2f│\n",
                   s.id, s.nome, s.preco);
            encontrou = 1;
        }
    }
    printf("╰──────────────────────────────────────────────────────────────────────────╯\n");

    fclose(fp);
    if (!encontrou)
        printf("Nenhum serviço ativo encontrado.\n");
}

void atualizarServico(void) {
    char *id = lerIdServico();

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        free(id);
        esperarEnter();
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if ((strcmp(s.id, id) == 0) && s.status == 1) {
            printf( "Novo nome: ");
            fgets(s.nome, sizeof(s.nome), stdin);
            s.nome[strcspn(s.nome, "\n")] = '\0';

            
            s.preco = lerDinheiro();

            fseek(fp, - (long) sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            encontrado = 1;
            break;
        }
    }
    free(id);
    fclose(fp);

    if (encontrado)
        printf("\n Serviço atualizado com sucesso! \n");
    else
        printf("\nServiço não encontrado ou inativo.\n");
}

// exclusão logica
void excluirServico(void) {
    char *id = lerIdServico();

    FILE *fp = fopen("servicos.dat", "r+b");
    if (!fp) {
        printf("Erro ao abrir o arquivo.\n");
        free(id);
        esperarEnter();
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if ((strcmp(s.id, id) == 0) && s.status == 1) {
            s.status = 0;
            fseek(fp, - (long) sizeof(Servico), SEEK_CUR);
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
        printf("\n Serviço excluído logicamente com sucesso! \n");

}

// Pesquisa
void pesquisarServico(void) {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Nenhum serviço cadastrado.\n");
        esperarEnter();
        return;
    }

    char *idBusca = lerIdServico();
    Servico s;
    int encontrou = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.status == 1 && strcmp(s.id, idBusca) == 0) {
            printf("╭──────────────────────────── SERVIÇO ENCONTRADO ──────────────────────────╮\n");
            printf("│ %-7s│ %-49s│ %-14s│\n", "ID", "Nome", "Preço");
            printf("├────────┼──────────────────────────────────────────────────┼──────────────┤\n");
            printf("│ %-7s│ %-49s│ R$ %-10.2f│\n",
                   s.id, s.nome, s.preco);

            printf("╰──────────────────────────────────────────────────────────────────────────╯\n");

            encontrou = 1;
        }
    }
    if (!encontrou)
        printf("Nenhum serviço encontrado com esse ID.\n");

    free(idBusca);
    fclose(fp);
}

// IDs
char* gerarIdServico(void) {
    char *idStr = malloc(10 * sizeof(char)); 
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000;
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