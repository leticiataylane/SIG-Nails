#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "telas_clientes.h"
#include "validacoes.h"
#include "ler_dados.h"
#include "erros.h"

char modCliente(void){
    char opCliente;

    do{
        opCliente = menuCliente();
        switch (opCliente)
        {
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
            telaExcluirCliente();
            break;

        case '0':
            break;

        default:
            opcaoInvalida();
            break;
        }
    }while (opCliente != '0');

    return opCliente;
}



void telaCadastrarCliente(void){
    printf("dados necessários para cadastro:\n");
    printf("|ENTER| para sair\n");

    esperarEnter();

}

void telaAtualizarCliente(void){
    printf("o que atualizar?\n");
    printf("|ENTER| para sair\n");

    esperarEnter();
    
}

void telaPesquisarCliente(void){
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");

    esperarEnter();
    
}

void telaExcluirCliente(void){
    printf("nome e data de nascimento para pesquisa e exclusão:\n");
    printf("|ENTER| para sair\n");

    esperarEnter();
    
}

void telaListarCliente(void){
    printf("nome e data de nascimento para pesquisa:\n");
    printf("|ENTER| para sair\n");

    esperarEnter();
    
}

void atualizarCSVClientes() {
    FILE *bin = fopen("clientes.dat", "rb");
    FILE *csv = fopen("clientes.csv", "w");
    if (!bin || !csv) {
        if (bin) fclose(bin);
        if (csv) fclose(csv);
        return;
    }

    fprintf(csv, "ID,Nome,DataNascimento,Telefone,Status\n");

    Cliente c;
    while (fread(&c, sizeof(Cliente), 1, bin) == 1) {
        fprintf(csv, "%s,%s,%s,%s,%d\n", c.id, c.nome, c.dataNascimento, c.telefone, c.status);
    }

    fclose(bin);
    fclose(csv);
}

void cadastrarCliente() {
    system("clear");
    Cliente c;
    FILE *fp;

    fp = fopen("clientes.dat", "rb");

    char *idStr = gerarIdCliente();
    strcpy(c.id, idStr);
    free(idStr);

    printf("\n=== CADASTRAR CLIENTE ===\n");

    printf("Nome: ");
    setbuf(stdin, NULL); // limpa buffer
    fgets(c.nome, sizeof(c.nome), stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(c.dataNascimento, sizeof(c.dataNascimento), stdin);
    c.dataNascimento[strcspn(c.dataNascimento, "\n")] = '\0';

    printf("Telefone: ");
    fgets(c.telefone, sizeof(c.telefone), stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    c.status = 1;

    fp = fopen("clientes.dat", "ab");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        esperarEnter();
        return;
    }
    fwrite(&c, sizeof(Cliente), 1, fp);
    fclose(fp);

    atualizarCSVClientes();

    printf("\nCliente cadastrado com sucesso! ID: %s\n", c.id);
    esperarEnter();
}

void listarClientes() {
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

void atualizarCliente() {
    system("clear");
    printf("\n=== ATUALIZAR CLIENTE ===\n");
    printf("Digite o ID do cliente: ");
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
        if ((strcmp(c.id , id) == 0) && c.status == 1) {
            printf("Novo nome: ");
            fgets(c.nome, sizeof(c.nome), stdin);
            c.nome[strcspn(c.nome, "\n")] = '\0';

            printf("Nova data de nascimento: ");
            fgets(c.dataNascimento, sizeof(c.dataNascimento), stdin);
            c.dataNascimento[strcspn(c.dataNascimento, "\n")] = '\0';

            printf("Novo telefone: ");
            fgets(c.telefone, sizeof(c.telefone), stdin);
            c.telefone[strcspn(c.telefone, "\n")] = '\0';

            fseek(fp, -sizeof(Cliente), SEEK_CUR);
            fwrite(&c, sizeof(Cliente), 1, fp);
            encontrado = 1;
            free(id);
            break;
        }
    }
    free(id);

    fclose(fp);

    if (encontrado) {
        atualizarCSVClientes();
        printf("\nCliente atualizado com sucesso!\n");
    } else {
        printf("\nCliente não encontrado ou inativo.\n");
    }

    esperarEnter();
}

void excluirCliente() {
    system("clear");
    printf("\n=== EXCLUIR CLIENTE (FISICAMENTE) ===\n");
    printf("Digite o ID do cliente: ");
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
        printf("Erro ao criar arquivo temporario.\n");
        esperarEnter();
        return;
    }

    Cliente c;
    int encontrado = 0;

    while (fread(&c, sizeof(Cliente), 1, origem) == 1) {
        if (strcmp(c.id, id) != 0) {
            fwrite(&c, sizeof(Cliente), 1, temp);
        } else {
            encontrado = 1;
        }
    }
    free(id);
    fclose(origem);
    fclose(temp);

    if (!encontrado) {
        printf("\nCliente nao encontrado.\n");
        remove("temp.dat"); 
    } else {
        remove("clientes.dat");         
        rename("temp.dat", "clientes.dat"); 
        atualizarCSVClientes();         
        printf("\nCliente excluido com sucesso (fisicamente)!\n");
    }

    esperarEnter();
}

char menuCliente() {
    char op;

    system("clear");
    printf("\n=== MENU CLIENTES ===\n");
    printf("1 - Cadastrar cliente\n");
    printf("2 - Listar clientes\n");
    printf("3 - Atualizar cliente\n");
    printf("4 - Excluir cliente\n");
    printf("0 - Sair\n");
    printf("Escolha uma opção: ");
    op = opcao();
    return op;
        
}

char* gerarIdCliente(void) {
    char *idStr = malloc(10 * sizeof(char)); // 4 dígitos + '\0'
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000; // gera 1000–9999
        sprintf(idStr, "%d", id);
    } while (idExisteCliente(idStr));

    return idStr;
}

int idExisteCliente(char *idStr) {
    FILE *fp = fopen("clientes.dat", "rb");
    if (!fp) return False; // arquivo não existe ainda, ID livre

    Cliente c; 
    while (fread(&c, sizeof(Cliente), 1, fp)) {
        if (strcmp(c.id, idStr) == 0) {
            fclose(fp);
            return True; // ID duplicado
        }
    }

    fclose(fp);
    return False; // ID não existe
}

// int main() {
//     menu();
//     return 0;
// }