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
#include "../geral/cores.h"

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
    printf(roxo negrito"\n★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│                MENU DE SERVIÇOS               │\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│" ciano negrito" [1] Cadastrar Serviço                         " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito" [2] Atualizar Serviço                         " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito" [3] Pesquisar Serviço                         " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito" [4] Listar Serviços                           " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito" [5] Excluir Serviço                           " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito" [0] Voltar ao Menu Principal                  " reset roxo negrito"│\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    op = opcao();
    return op;
}

void telaCadastrarServico(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│          CADASTRO DE NOVO SERVIÇO             │\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│" ciano negrito"  Insira as informações abaixo:                " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito"  - Nome do Serviço                            " reset roxo negrito"│\n" reset);
    printf(roxo negrito"│" ciano negrito"  - Preço                                      " reset roxo negrito"│\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    cadastrarServico();
    esperarEnter();
}

void telaAtualizarServico(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│              ATUALIZAR SERVIÇO                │\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│"ciano negrito" Informe o ID do serviço que deseja atualizar. "roxo negrito"│\n" reset);
    printf(roxo negrito"│"ciano negrito" Apenas serviços ativos podem ser alterados.   "roxo negrito"│\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    atualizarServico();
    esperarEnter();
}

void telaPesquisarServico(void) {
    system("clear");
    printf(roxo negrito"★────────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│               PESQUISAR SERVIÇO                │\n" reset);
    printf(roxo negrito"★────────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│" ciano negrito"  Digite o ID do serviço para buscar seus dados │\n" reset);
    printf(roxo negrito"★────────────────────────────────────────────────★\n" reset);
    pesquisarServico();
    esperarEnter();
}

void telaListarServico(void) {
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    printf(roxo negrito"│                LISTA DE SERVIÇOS              │\n"reset);
    listarServicos();
    printf(roxo negrito"★───────────────────────────────────────────────★\n"reset);
    esperarEnter();
}

void telaExcluirServico(void) {
    char op;
    system("clear");
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│                EXCLUIR SERVIÇO                │\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
    printf(roxo negrito"│" ciano negrito" [1] Exclusão Lógica (Inativar Serviço)        │\n" reset);
    printf(roxo negrito"│" ciano negrito" [0] Voltar                                    │\n" reset);
    printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);

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

    printf(roxo negrito"\n★ CADASTRAR SERVIÇO ★\n\n" reset);

    char *nome = lerNomeCurto("Nome do serviço: ");
    strcpy(s.nome, nome);
    free(nome);

    s.preco = lerPrecoServico();  
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

    printf("\n★ Serviço cadastrado com sucesso! ID: %s ★\n", s.id);
}

void listarServicos(void) {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Nenhum serviço cadastrado.\n");
        return;
    }

    Servico s;
    int encontrou = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (s.status == 1) {
            printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
            printf(roxo negrito"│" ciano negrito" ID: %-40s  │\n" reset, s.id);
            printf(roxo negrito"│" ciano negrito" Nome: %-38s │ \n" reset, s.nome);
            printf(roxo negrito"│" ciano negrito" Preço: R$%-37.2f  │\n" reset, s.preco);
            encontrou = 1;
        }
    }
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
            printf(ciano negrito "Novo nome: " reset);
            setbuf(stdin, NULL);
            fgets(s.nome, sizeof(s.nome), stdin);
            s.nome[strcspn(s.nome, "\n")] = '\0';

            printf(ciano negrito "Novo preço: " reset);
            s.preco = lerDinheiro();

            fseek(fp, -sizeof(Servico), SEEK_CUR);
            fwrite(&s, sizeof(Servico), 1, fp);
            encontrado = 1;
            break;
        }
    }
    free(id);
    fclose(fp);

    if (encontrado)
        printf("\n★ Serviço atualizado com sucesso! ★\n");
    else
        printf("\nServiço não encontrado ou inativo.\n");

    esperarEnter();
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
        printf("\n★ Serviço excluído logicamente com sucesso! ★\n");

    esperarEnter();
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
            printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
            printf(roxo negrito"│" ciano negrito" ID: %-40s " roxo negrito"│\n" reset, s.id);
            printf(roxo negrito"│" ciano negrito" Nome: %-38s " roxo negrito"│\n" reset, s.nome);
            printf(roxo negrito"│" ciano negrito" Preço: %-37.2f " roxo negrito"│\n" reset, s.preco);
            printf(roxo negrito"★───────────────────────────────────────────────★\n" reset);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum serviço encontrado com esse ID.\n");

    free(idBusca);
    fclose(fp);
    esperarEnter();
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