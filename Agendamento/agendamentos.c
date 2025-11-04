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
#include "clientes.h"
#include "servicos.h"
#include "erros.h"


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
            telaListarAgendamentos();
            break;

        case '5':
            telaExcluirAgendamento();
            break;

        case '0':
            break;

        default:
            opcaoInvalida();
            break;
        }
    }while (opAgendamento != '0');

    return opAgendamento;
}

char menuAgendamento(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│              ÁREA DO AGENDAMENTO             │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] CADASTRAR                               │\n" );
    printf("│  [2] ATUALIZAR                               │\n");
    printf("│  [3] PESQUISAR                               │\n");
    printf("│  [4] LISTAR                                  │\n");
    printf("│  [5] EXCLUIR                                 │\n");
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
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
    esperarEnter();

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
    // esperarEnter();

}

void telaAtualizarAgendamento(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             ATUALIZAR AGENDAMENTO            │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   A operação de atualização só será efetiva  │\n" );
    printf("│   se o agendamento estiver pendente e com o  │\n");
    printf("│   status ativo.                              │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    atualizarAgendamento();
    esperarEnter();
    
}

void telaPesquisarAgendamento(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             PESQUISAR AGENDAMENTO            │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│   Para pesquisar um agendamento, informe o   │\n" );
    printf("│   número do ID do mesmo.                     │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    pesquisarAgendamento();
    esperarEnter();
    
}

void telaExcluirAgendamento(void){
    char op;
    do{
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│              EXCLUIR AGENDAMENTO             │\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│   [1] Exclusão Lógica                        │\n");
        printf("│   [2] Exclusão definitiva                    │\n");
        printf("│   [0] Sair                                   │\n");
        printf("╰──────────────────────────────────────────────╯\n");
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
            opcaoInvalida();
            break;
        }
    }while (op != '0');

    esperarEnter();
    
}

void telaListarAgendamentos(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│             LISTA DE AGENDAMENTOS            │\n");
    listarAgendamentos();
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();

}


char telaSituacao(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│      QUAL A NOVA SITUAÇÃO DO AGENDAMENTO?    │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] CONCLUÍDO                               │\n" );
    printf("│  [2] CANCELADO                               │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

char telaOqAlterar(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            O QUE DESEJA ATUALIZAR?           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] SERVIÇO                                 │\n" );
    printf("│  [2] DATA E HORÁRIO                          │\n");
    printf("│  [3] SITUAÇÃO                                │\n");
    printf("│  [0] Sair                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}


void printAgendamento(Agendamento *a){
    char *nomeServ;
    char *nomeCli;

    printf("╭──────────────────────────────────────────────╮\n");
    printf("│              AGENDAMENTO: %s               │\n", a->agenId);
    printf("├──────────────────────────────────────────────┤\n");
    nomeCli = getNomeCli(a->clienteId);
    printf("│ Nome Cliente: %-30s │\n", nomeCli);
    free(nomeCli);
    nomeServ = getNomeServ(a->servicoId);
    printf("│ Nome Serviço: %-30s │\n", nomeServ);
    free(nomeServ);
    printf("│ Data: %.2s/%.2s/%.4s                             │\n", a->data, a->data + 2, a->data + 4);
    printf("│ Horário: %.2sh%.2sm                              │\n", a->horario, a->horario + 2);
    printf("│ Preço: R$ %.2f                              │\n", a->preco);
    printf("│ Situação: %-34s │\n", a->situacao);
    printf("╰──────────────────────────────────────────────╯\n");
}
///////////////////////////////////////////////////////////OPERACOES////////////////////////////////////////////////////////////////////////////////

int cadastrarAgendamento(void){
    int cont = 0;
    int encontrado = False;
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));

    cont = contaClientesAtivos();

    if(cont < 1){
        arqInexistente();
        free(a);
        return 1;
    }

    cont = 0;
    cont = contaServicosAtivos();

    if(cont < 1){
        arqInexistente();
        free(a);
        return 1;
    }
    

    system("clear");
    telaListarCliente();
    char *idCliente = lerIdCliente();
    strcpy(a->clienteId, idCliente);
    free(idCliente);


    telaListarServico();
    char *idServico = lerIdServico();
    strcpy(a->servicoId, idServico);
    free(idServico);

    FILE *serv = fopen("servicos.dat", "rb");
    Servico s; 
    while ((fread(&s, sizeof(Servico), 1, serv)) && (!encontrado)) {
        if (strcmp(s.id, a->servicoId) == 0) {
            a->preco = s.preco;
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

int atualizarAgendamento(void) {
    Agendamento* a = malloc(sizeof(Agendamento));
    if (a == NULL) {
        perror("Erro ao alocar memória para Agendamento");
        return 1;
    }

    int encontrado = False;
    char oqAlterar;
    FILE *agen = fopen("agendamentos.dat", "r+b");
    if (agen == NULL) {
        perror("Erro ao abrir agendamentos.dat");
        free(a);
        return 1;
    }
    telaListarAgendamentos();

    char *qualAgendamento = lerIdAgendamento();


    while ((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)) {
        if ((strcmp(qualAgendamento, a->agenId) == 0) && (a->status) && (strcmp(a->situacao, "Pendente") == 0)) {

            do {
                oqAlterar = telaOqAlterar();

                switch (oqAlterar) {
                    case '1': { // alterar serviço
                        int cont = 0;
                        cont = contaServicosAtivos();
                        if(cont < 1){
                            oqAlterar = '0';
                            break;
                        }
                        system("clear");
                        telaListarServico();
                        char *idServico = lerIdServico();
                        strcpy(a->servicoId, idServico);
                        free(idServico);

                        FILE *serv = fopen("Servicos.dat", "rb");
                        if (serv == NULL) {
                            perror("Erro ao abrir Servicos.dat");
                            oqAlterar = '0';
                            break;
                        }
                        Servico s;
                        int encontradoServico = False;

                        while ((fread(&s, sizeof(Servico), 1, serv)) && (!encontradoServico)) {
                            if (strcmp(s.id, a->servicoId) == 0) {
                                a->preco = s.preco;
                                encontradoServico = True;
                            }
                        }
                        fclose(serv);
                        oqAlterar = '0';
                        break;
                    }

                    case '2': { // alterar data e horário
                        char *data = lerData();
                        strcpy(a->data, data);
                        free(data);

                        system("clear");
                        char *horario = lerHorario();
                        strcpy(a->horario, horario);
                        free(horario);
                        oqAlterar = '0';
                        break;
                    }

                    case '3': { // alterar situação
                        char *situacao = lerSituacao(a->horario, a->data, a->situacao);
                        if (situacao != NULL) {
                            strncpy(a->situacao, situacao, sizeof(a->situacao));
                            a->situacao[sizeof(a->situacao) - 1] = '\0';
                            free(situacao);
                        }
                        oqAlterar = '0';
                        break;
                    }

                    case '0':
                        break;

                    default:
                        opcaoInvalida();
                        break;
                    }

            } while (oqAlterar != '0');

            fseek(agen, (-1) * sizeof(Agendamento), SEEK_CUR);
            fwrite(a, sizeof(Agendamento), 1, agen);
            encontrado = True;

        } else if ((strcmp(qualAgendamento, a->agenId) == 0) && (!a->status)) {
            printf("Agendamento foi excluído, impossível alterar\n");
            encontrado = True;
        }
    }

    fclose(agen);
    free(a);
    free(qualAgendamento);

    if (!encontrado) {
        printf("Agendamento não encontrado\n");
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
    telaListarAgendamentos();
    char *qual = lerIdAgendamento();

    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){//quando pesquisar, mostrar nome e data de nascimento do cliente e o valor do serviço
        if((strcmp(qual, a->agenId) == 0) && (a->status)){
            printAgendamento(a);
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
    char *nomeCli;
    char *nomeServ;
    int cont = 0;
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    agen = fopen("agendamentos.dat","rb");
    if(agen == NULL){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│    Não existem agendamentos cadastrados.     │\n");
        free(a);
        return cont;
    }

    while(fread(a, sizeof(Agendamento), 1, agen)){
        if(a->status){
            printf("├──────────────────────────────────────────────┤\n");
            printf("│ ID Agendamento: %-28s │\n", a->agenId);
            nomeCli = getNomeCli(a->clienteId);
            printf("│ Nome Cliente: %-30s │\n", nomeCli);
            free(nomeCli);
            nomeServ = getNomeServ(a->servicoId);
            printf("│ Nome Serviço: %-30s │\n", nomeServ);
            free(nomeServ);
            printf("│ Situação: %-34s │\n", a->situacao);
            cont += 1;
        }
    }
    fclose(agen);
    free(a);
    return cont;
}


int excluirAgendamento(void){
    Agendamento a;
    int encontrado = False;

    FILE *agen = fopen("agendamentos.dat", "r+b");
    if (agen == NULL) {
        printf("Erro ao abrir agendamentos.dat\n");
        return 1;
    }

    telaListarAgendamentos();
    char *qual = lerIdAgendamento();


    while (fread(&a, sizeof(Agendamento), 1, agen) == 1 && !encontrado) {
        if ((strcmp(qual, a.agenId) == 0) && a.status && strcmp(a.situacao, "Pendente") != 0) {
            a.status = False;
            fseek(agen, -sizeof(Agendamento), SEEK_CUR);
            fwrite(&a, sizeof(Agendamento), 1, agen);
            encontrado = True;
            printf("Agendamento excluído com sucesso.\n");

        } else if ((strcmp(qual, a.agenId) == 0) && !a.status) {
            printf("Agendamento já foi excluído.\n");
            encontrado = True;

        } else if ((strcmp(qual, a.agenId) == 0) && a.status && strcmp(a.situacao, "Pendente") == 0) {
            printf("Agendamento não pode ser excluído enquanto estiver pendente.\n");
            printf("Atualize a situação antes de excluir.\n");
            encontrado = True;
        }
    }

    fclose(agen);
    free(qual);

    if (!encontrado) {
        printf("Agendamento não encontrado.\n");
        return 2;
    }

    return 0;

}

int excluirAgendamentoDefinitivo(void) {
    FILE *agen, *agenTemp;
    Agendamento* a = (Agendamento*) malloc(sizeof(Agendamento));

    int encontrado = False;

    agen = fopen("agendamentos.dat", "rb");
    if (agen == NULL) {
        printf("Erro: não foi possível abrir o arquivo original.\n");
        free(a);
        return 1;
    }

    agenTemp = fopen("temp.dat", "wb");
    if (agenTemp == NULL) {
        printf("Erro: não foi possível criar o arquivo temporário.\n");
        fclose(agen);
        free(a);
        return 1;
    }

    telaListarAgendamentos();
    char *id = lerIdAgendamento();

    while (fread(a, sizeof(Agendamento), 1, agen) == 1) {
        if ((strcmp(a->agenId, id) == 0) && (strcmp(a->situacao, "Pendente") != 0)) {
            encontrado = True;
            printf("Agendamento encontrado e excluído: %s\n", a->agenId);
        } else {
            fwrite(a, sizeof(Agendamento), 1, agenTemp);
        }
    }

    fclose(agen);
    fclose(agenTemp);

    if (encontrado) {
        remove("agendamentos.dat");
        rename("temp.dat", "agendamentos.dat");
        printf("Exclusão realizada com sucesso.\n");
    } else {
        remove("temp.dat");
        printf("Nenhum agendamento encontrado com o ID informado ou situação inválida.\n");
    }

    free(a);
    free(id);

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




char* gerarIdAgendamento(void) {
    char *idStr = malloc(10 * sizeof(char)); // 4 dígitos + '\0'
    if (!idStr) return NULL;

    int id;
    do {
        id = rand() % 9000 + 1000; // gera 1000–9999
        sprintf(idStr, "%d", id);
    } while (idExisteCliente(idStr));

    return idStr;
}



int contaClientesAtivos(void){
    int cont = 0;
    FILE *cli = fopen("clientes.dat", "rb");
    if (cli == NULL) {
        arqInexistente();
        return cont;
    }
    Cliente c; 
    while (fread(&c, sizeof(Cliente), 1, cli)) {
        if (c.status){
            cont += 1;
        }
    }
    fclose(cli);
    return cont;

}


int contaServicosAtivos(void){
    int cont = 0;
    FILE *serv = fopen("servicos.dat", "rb");
    if (serv == NULL) {
        return cont;
    }
    Servico s; 
    while (fread(&s, sizeof(Servico), 1, serv)) {
        if (s.status){
            cont += 1;
        }
    }
    fclose(serv);
    return cont;

}


char* getNomeServ(char* id) {
    char *nomeServ = NULL;
    int encontrado = False;
    FILE *serv = fopen("servicos.dat", "rb");
    if (serv == NULL) {
        arqInexistente();
        return NULL;
    }

    Servico s;
    while ((fread(&s, sizeof(Servico), 1, serv)) && (!encontrado)) {
        if (strcmp(s.id, id) == 0) {
            nomeServ = malloc(strlen(s.nome) + 1);
            if (nomeServ == NULL) {
                perror("Erro de alocação");
                fclose(serv);
                return NULL;
            }
            strcpy(nomeServ, s.nome);
            encontrado = True;
        }
    }

    fclose(serv);
    return nomeServ; // deve ser liberado com free() pelo chamador
}

char* getNomeCli(char* id) {
    char *nomeCli = NULL;
    int encontrado = False;
    FILE *cli = fopen("clientes.dat", "rb");
    if (cli == NULL) {
        arqInexistente();
        return NULL;
    }

    Cliente c;
    while ((fread(&c, sizeof(Cliente), 1, cli)) && (!encontrado)) {
        if (strcmp(c.id, id) == 0) {
            nomeCli = malloc(strlen(c.nome) + 1); // aloca o espaço exato
            if (nomeCli == NULL) {
                perror("Erro de alocação");
                fclose(cli);
                return NULL;
            }
            strcpy(nomeCli, c.nome);
            encontrado = True;
        }
    }

    fclose(cli);
    return nomeCli; // deve ser liberado com free() por quem chama
}