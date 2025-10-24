#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "cores.h"
#include "agendamentos.h"
#include "limpeza.h"
#include "validacoes.h"
#include "ler_dados.h"


char modAgendamento(void){
    char opAgendamento;

    do{
        opAgendamento = menuAgendamento();
        switch (opAgendamento)
        {
        case '1':
            telaCadastrarAgendamento();
            break;

        case '2':
            telaAtualizarAgendamento();
            break;

        case '3':
            telaPesquisarAgendamento();
            break;

        case '4':
            telaExcluirAgendamento();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (opAgendamento != '0');

    return opAgendamento;
}

char menuAgendamento(void){
    char op;

    printf("ÁREA DO Agendamento\n");
    printf("___________________");
    printf("1.cadastrar\n");
    printf("2.atualizar\n");
    printf("3.pesquisar\n");
    printf("4.listar\n");
    printf("5.excluir\n");
    printf("0.sair\n");

    op = opcao();

    return op;


}

void telaCadastrarAgendamento(void){
    
    system("clear");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(rosa negrito "                GUIA DE AGENDAMENTO                   \n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(azul" 1. Escolha para qual cliente agendar o serviço[ATENÇÃO: só serão agendados serviços para clientes já cadastrados].\n"reset);
    printf(azul" 2. Veja a tabela de preços e serviços e escolha o desejado.\n"reset);
    printf(azul" 3. Informe os dados do agendamento: ID do cliente, ID do serviço, data e hora (8h - 20h).\n"reset);
    printf(azul" 4. Aguarde a confirmação.\n"reset);
    printf(rosa negrito "\nPressione ENTER para continuar...\n"reset);
    getchar();

    cadastrarAgendamento();

    // system("clear");
    // printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    // printf(rosa negrito "        TABELA DE PREÇOS   \n"reset);
    // printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    // printf(negrito "Manicure"reset rosa negrito" ............ "ciano"R$25\n"reset);//adicionar printagem automática
    // printf(negrito "Pedicure"reset rosa negrito" ............ "ciano"R$30\n"reset);
    // printf(negrito "Mani + Pedi"reset rosa negrito" ......... "ciano"R$50\n"reset);
    // printf(negrito "Spa dos Pés"reset rosa negrito" ......... "ciano"R$45\n"reset);
    // printf(negrito "Blindagem de Unhas"reset rosa negrito" .. "ciano"R$60\n"reset);
    // printf(rosa negrito "\nPressione ENTER para continuar...\n"reset);
    // getchar();

}

void telaAtualizarAgendamento(void){
    atualizarAgendamento();
    
}

void telaPesquisarAgendamento(void){
    pesquisarAgendamento();
    
}

void telaExcluirAgendamento(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│              EXCLUIR AGENDAMENTO             │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   [1] Exclusão Lógica                        │\n");
    printf("│   [2] Exclusão definitiva                    │\n");
    printf("│   [0] Sair                                   │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    do{
        op = opcao();
        switch (op)
        {
        case '1':
            excluirAgendamento();
            break;

        case '2':
            excluirAgendamentoDefinitivo();
            break;

        case '0':
            break;

        default:
            opInvalida();
            break;
        }
    }while (op != '0');

    printf("|ENTER| para sair\n");

    getchar();


    
}


char telaSituacao(void){
    char op;
    printf("Qual a nova situação do agendamento?\n");
    printf("1.Concluído\n");
    printf("2.Cancelado\n");
    printf("0.Sair\n");
    op = opcao();
}

///////////////////////////////////////////////////////////OPERACOES////////////////////////////////////////////////////////////////////////////////

int cadastrarAgendamento(void){
    int encontrado = False;
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));

    FILE *agen;

    system("clear");
    listarClientes();
    char *idCliente = lerIdCliente();
    strcpy(a->clienteId, idCliente);
    free(idCliente);

    FILE *cli = fopen("clientes.dat", "rb");
    cliente c; 
    while ((fread(&c, sizeof(cliente), 1, cli)) && (!encontrado)) {
        if (strcmp(c.servId, a->clienteId) == 0) {

            strcpy(a->clienteNome, c.nome);
            fclose(cli);
            encontrado = True;
        }
    }
    fclose(cli);
    
    system("clear");
    listarServicos();
    char *idServico = lerIdServico();
    strcpy(a->servicoId, idServico);
    free(idServico);

    FILE *serv = fopen("Servicos.dat", "rb");
    Servico s; 
    while ((fread(&s, sizeof(Servico), 1, serv)) && (!encontrado)) {
        if (strcmp(s.servId, a->servicoId) == 0) {
            a->preco = s.preco;
            strcpy(a->servicoNome, s.nome);
            fclose(serv);
            encontrado = True;
        }
    }
    fclose(serv);


    system("clear");
    char *data = lerData();
    strcpy(a->data, data);
    free(data);
    
    char *horario = lerHorario();
    strcpy(a->horario, horario);
    free(horario);

    char *idStr = gerarIdAgendamento();
    strcpy(a->agenId, idStr);
    free(idStr);

    strcpy(a->situacao, "Pendente");

    a->status = True;

    FILE *agen = fopen("agendamentos.dat", "ab");
    if (agen == NULL) {
        perror("Erro ao abrir o arquivo");
        free(a);
        return 1;
    }
    fwrite(a, sizeof(Agendamento), 1, agen);
    fclose(agen);
    free(a);
    printf("\nDados salvos com sucesso em agendamentos.dat!\n");

    return 0;
}


int atualizarAgendamento(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    int encontrado = False;
    char oqAlterar;
    
    listarAgendamentos();
    char *qualAgendamento = lerIdAgendamento();

    FILE *agen;

    FILE *agen = fopen("agendamentos.dat", "r+b");
    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){
        if((qualAgendamento == a->agenId) && (a->status) && (strcpm(a->situacao, "Pendente") == 0)){
            do{
                oqAlterar = telaOqAlterar();
                switch (oqAlterar)
                {
                case '1':
                    system("clear");
                    listarServicos();
                    char *idServico = lerIdServico();
                    strcpy(a->servicoId, idServico);
                    free(idServico);
                    FILE *serv = fopen("Servicos.dat", "rb");
                    Servico s; 
                    while ((fread(&s, sizeof(Servico), 1, serv)) && (!encontrado)) {
                        if (strcmp(s.servId, a->servicoId) == 0) {
                            a->preco = s.preco;
                            strcpy(a->servicoNome, s.nome);
                            fclose(serv);
                            encontrado = True;
                        }
                    }
                    fclose(serv);
                    break;

                case '2':
                    char *data = lerData();
                    strcpy(a->data, data);
                    free(data);
                    system("clear");

                    char *horario = lerHorario();
                    strcpy(a->horario, horario);
                    free(horario);
                    break;

                case '3':
                    char *situacao = lerSituacao(a->horario, a->data, a->situacao);
                    if(situacao != NULL){
                        strcpy(a->situacao, situacao);
                        free(situacao);
                    }
                    break;

                case '0':
                    break;

                default:
                    opInvalida();
                    break;
                }
            }while(oqAlterar != '1' && oqAlterar != '2' && oqAlterar != '3' && oqAlterar != '0');
            fseek(agen, (-1)*sizeof(Agendamento), SEEK_CUR);
            fwrite(agen, sizeof(Agendamento), 1, agen);
            encontrado = True;
        } else if ((qualAgendamento == a->agenId) && (!a->status)){
            printf("Agendamento foi excluído, impossível alterar");
            encontrado = True;
        }
    }
    fclose(agen);
    free(a);
    if(!encontrado){
        printf("Nao encontrado");
    }
    return 0;
}


int pesquisarAgendamento(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    int encontrado = False;
    
    agen = fopen("agendamentos.dat","rb");
    if (agen == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        free(a);
        return False;
    }
    listarAgendamentos();
    char *qual = lerIdAgendamento();

    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){//quando pesquisar, mostrar nome e data de nascimento do cliente e o valor do serviço
        if((qual == a->agenId) && (a->status)){
            printf("AGENDAMENTO ID: %s\nID CLIENTE: %s\nNOME CLIENTE: %s\nDATA: %s\nHORA: %s\nID SERVICO: %s\nNOME SERVICO: %s\nVALOR SERVICO: R$%.2f\nSITUAÇÃO: %s\n", a->agenId, a->clienteNome, a->clienteId, a->data, a->horario, a->servicoId, a->servicoNome, a->preco, a->situacao);
            encontrado = True;
        } else if((qual == a->agenId) && (!a->status)){
            printf("AGENDAMENTO excluido\n");
            encontrado = True;
        }
    }
    free(qual);
    fclose(agen);
    free(a);
    if(!encontrado){
        printf("Não encontrado");
        return False;
    }

    return 0;
}


int listarAgendamentos(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    agen = fopen("agendamentos.dat","rb");

    while(fread(a, sizeof(Agendamento), 1, agen)){
        if(a->status){
            printf("AGENDAMENTO ID: %s\nID CLIENTE: %s\nDATA: %s\nHORA: %s\nID SERVICO: %s\nSITUAÇÃO: %s\n", a->agenId, a->clienteId, a->data, a->horario, a->servicoId, a->situacao);
        }
    }
    fclose(agen);
    free(a);
    return 0;
}


int excluirAgendamento(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    int encontrado = False;


    listarAgendamentos();
    char *qual = lerIdAgendamento();


    agen = fopen("agendamentos.dat","r+b");

    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){
        if((qual == a->agenId) && (a->status) && (strcmp(a->situacao, "Pendente") != 0)){
            printf("AGENDAMENTO ID: %s\nID CLIENTE: %s\nDATA: %s\nHORA: %s\nSERVICO: %s\nSITUAÇÃO: %s\n", a->agenId, a->clienteId, a->data, a->horario, a->servicoId, a->situacao);
            a->status = False;
            fseek(agen, (-1)*sizeof(Agendamento), SEEK_CUR);
            fwrite(agen, sizeof(Agendamento), 1, agen);
            encontrado = True;

        } else if((qual == a->agenId) && (!a->status)){
            printf("Agendamento já foi excluído");
            encontrado = True;
        }else if((qual == a->agenId) && (a->status) && (strcmp(a->situacao, "Pendente") == 0)){
            printf("Agendamento não pode ser excluído enquanto se encontra pendente. Atualize a situação antes de excluir.\n");
            encontrado = True;
        }
    }
    free(qual); 
    fclose(agen);
    free(a);
    if(!encontrado){
        printf("Não encontrado");
    }

    return 0;

}

int excluirAgendamentoDefinitivo(void) {
    FILE *agen, *agenTemp;
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));

    int encontrado = False;

    agen = fopen("Agendamentos.dat", "rb");
    if (agen == NULL) {
        printf("Erro: não foi possível abrir o arquivo original.\n");
        return 1;
    }

    agenTemp = fopen("temp.dat", "wb");
    if (agenTemp == NULL) {
        printf("Erro: não foi possível criar o arquivo temporário.\n");
        fclose(agen);
        return 1;
    }

    char *id = lerIdAgendamento();

    while (fread(a, sizeof(Agendamento), 1, agen)) {
        if ((strcmp(a->agenId, id) == 0) && (strcmp(a->situacao, "Pendente") != 0)) {
            encontrado = True;
            printf("Agendamento encontrado e excluído: %s\n", a->agenId);
        } else {
            fwrite(&a, sizeof(Agendamento), 1, agenTemp);
        }
    }

    fclose(agen);
    fclose(agenTemp);

    // Se encontrou, substitui o arquivo original
    if (encontrado) {
        remove("agendamentos.dat");
        rename("temp.dat", "agendamentos.dat");
        printf("Exclusão realizada com sucesso.\n");
    } else {
        remove("temp.dat");
        printf("Nenhum agendamento encontrado com o id informado.\n");
    }

    return 0;
}


int idExisteAgendamento(char *idStr) {
    FILE *fp = fopen("agendamentos.dat", "rb");
    if (!fp) return False; // arquivo não existe ainda, ID livre

    Agendamento a; 
    while (fread(&a, sizeof(Agendamento), 1, fp)) {
        if (strcmp(a.agenId, idStr) == 0) {
            fclose(fp);
            return True; // ID duplicado
        }
    }

    fclose(fp);
    return False; // ID não existe
}


int idExisteServico(char *idStr) {
    FILE *fp = fopen("Servicos.dat", "rb");
    if (!fp) return False; // arquivo não existe ainda, ID livre

    Servico s; 
    while (fread(&s, sizeof(Servico), 1, fp)) {
        if (strcmp(s.servId, idStr) == 0) {
            fclose(fp);
            return True; // ID duplicado
        }
    }

    fclose(fp);
    return False; // ID não existe
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


char* gerarIdCliente(void) {
    char *idStr = malloc(5 * sizeof(char)); // 4 dígitos + '\0'
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000; // gera 1000–9999
        sprintf(idStr, "%d", id);
    } while (idExisteCliente(idStr));

    return idStr;
}

char* gerarIdServico(void) {
    char *idStr = malloc(5 * sizeof(char)); // 4 dígitos + '\0'
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000; // gera 1000–9999
        sprintf(idStr, "%d", id);
    } while (idExisteCliente(idStr));

    return idStr;
}

char* gerarIdAgendamento(void) {
    char *idStr = malloc(5 * sizeof(char)); // 4 dígitos + '\0'
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000; // gera 1000–9999
        sprintf(idStr, "%d", id);
    } while (idExisteCliente(idStr));

    return idStr;
}