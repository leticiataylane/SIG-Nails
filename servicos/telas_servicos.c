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
    printf("\n★───────────────────────────────────────────────★\n");
    printf("│                MENU DE SERVIÇOS               │\n");
    printf("★───────────────────────────────────────────────★\n");
    printf("│ [1] Cadastrar Serviço                         │\n");
    printf("│ [2] Atualizar Serviço                         │\n");
    printf("│ [3] Pesquisar Serviço                         │\n");
    printf("│ [4] Listar Serviços                           │\n");
    printf("│ [5] Excluir Serviço                           │\n");
    printf("│ [0] Voltar ao Menu Principal                  │\n");
    printf("★───────────────────────────────────────────────★\n");
    op = opcao();
    return op;
}

void telaCadastrarServico(void) {
    system("clear");
    printf("★───────────────────────────────────────────────★\n");
    printf("│          CADASTRO DE NOVO SERVIÇO             │\n");
    printf("★───────────────────────────────────────────────★\n");
    printf("│  Insira as informações abaixo:                │\n");
    printf("│  - Nome do Serviço                            │\n");
    printf("│  - Preço                                      │\n");
    printf("★───────────────────────────────────────────────★\n");
    cadastrarServico();
    esperarEnter();
}

void telaAtualizarServico(void) {
    system("clear");
    printf("★───────────────────────────────────────────────★\n");
    printf("│              ATUALIZAR SERVIÇO                │\n");
    printf("★───────────────────────────────────────────────★\n");
    printf("│ Informe o ID do serviço que deseja atualizar. │\n");
    printf("│ Apenas serviços ativos podem ser alterados.   │\n");
    printf("★───────────────────────────────────────────────★\n");
    atualizarServico();
    esperarEnter();
}

void telaPesquisarServico(void) {
    system("clear");
    printf("★───────────────────────────────────────────────★\n");
    printf("│               PESQUISAR SERVIÇO               │\n");
    printf("★───────────────────────────────────────────────★\n");
    printf("│  Digite o ID do serviço para buscar seus dados│\n");
    printf("★───────────────────────────────────────────────★\n");
    pesquisarServico();
    esperarEnter();
}

void telaListarServico(void) {
    system("clear");
    printf("★───────────────────────────────────────────────★\n");
    printf("│                LISTA DE SERVIÇOS              │\n");
    printf("★───────────────────────────────────────────────★\n");
    listarServicos();
    printf("★───────────────────────────────────────────────★\n");
    esperarEnter();
}

void telaExcluirServico(void) {
    char op;
    system("clear");
    printf("★───────────────────────────────────────────────★\n");
    printf("│                EXCLUIR SERVIÇO                │\n");
    printf("★───────────────────────────────────────────────★\n");
    printf("│ [1] Exclusão Lógica (Inativar Serviço)        │\n");
    printf("│ [2] Exclusão Definitiva (Remover do Sistema)  │\n");
    printf("│ [0] Voltar                                    │\n");
    printf("★───────────────────────────────────────────────★\n");

    do {
        op = opcao();
        switch (op) {
            case '1':
                excluirServico();
                break;
            case '2':
                excluirServicoDefinitivo();
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

    printf("\n★ CADASTRAR SERVIÇO ★\n\n");

    printf("Nome do serviço: ");
    setbuf(stdin, NULL);
    fgets(s.nome, sizeof(s.nome), stdin);
    s.nome[strcspn(s.nome, "\n")] = '\0';

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
            printf("★───────────────────────────────────────────────★\n");
            printf("│ ID: %-40s  │\n", s.id);
            printf("│ Nome: %-38s │ \n", s.nome);
            printf("│ Preço: R$%-37.2f  │\n", s.preco);
            encontrou = 1;
        }
    }
    fclose(fp);

    if (!encontrou)
        printf("Nenhum serviço ativo encontrado.\n");
}

void atualizarServico(void) {
    printf("\nDigite o ID do serviço a atualizar: ");
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
            printf("Novo nome: ");
            setbuf(stdin, NULL);
            fgets(s.nome, sizeof(s.nome), stdin);
            s.nome[strcspn(s.nome, "\n")] = '\0';

            printf("Novo preço: ");
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
    printf("Digite o ID do serviço para exclusão: ");
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

// exclusão definitiva
void excluirServicoDefinitivo(void) {
    char *id = lerIdServico();

    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        printf("Erro ao abrir o arquivo de serviços.\n");
        free(id);
        esperarEnter();
        return;
    }

    FILE *fpTemp = fopen("temp.dat", "wb");
    if (!fpTemp) {
        printf("Erro ao criar arquivo temporário.\n");
        fclose(fp);
        free(id);
        esperarEnter();
        return;
    }

    Servico s;
    int encontrado = 0;

    while (fread(&s, sizeof(Servico), 1, fp) == 1) {
        if (strcmp(s.id, id) == 0) {
            encontrado = 1;
            printf("Serviço encontrado e removido definitivamente: %s\n", s.nome);
            continue; 
        }
        fwrite(&s, sizeof(Servico), 1, fpTemp);
    }

    fclose(fp);
    fclose(fpTemp);
    free(id);

    if (encontrado) {
        remove("servicos.dat");
        rename("temp.dat", "servicos.dat");
        printf("Exclusão definitiva realizada com sucesso.\n");
    } else {
        remove("temp.dat");
        printf("Nenhum serviço encontrado com esse ID.\n");
    }

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
            printf("★───────────────────────────────────────────────★\n");
            printf("│ ID: %-40s │\n", s.id);
            printf("│ Nome: %-38s │\n", s.nome);
            printf("│ Preço: %-37.2f │\n", s.preco);
            printf("★───────────────────────────────────────────────★\n");
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