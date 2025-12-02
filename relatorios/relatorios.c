#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "servicos.h"
#include "clientes.h"
#include "agendamentos.h"
#include "funcionarios.h"
#include "ler_dados.h"
#include "relatorios.h"
#include "erros.h"
#include "cores.h"

char modRelatorios(void){
    char op;
    do {
        op = menuRelatorios();
        switch(op) {
            case '1':
                modRelatorioAgendamento();
                break;
            case '2':
                modRelatorioServico();
                break;
            case '3':
                modRelatorioCliente();
                break;
            case '4':
                modRelatorioFuncionario();
                break;
            case '0':
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while(op != '0');
    return op;
}

char menuRelatorios(void) {
    char op;

    system("clear");
    printf("\n");
    printf("╭──────────────────────────────────────────────╮\n");
    printf("|                  RELATÓRIOS                  |\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("| [1] Agendamentos                             |\n");
    printf("| [2] Serviços                                 |\n");
    printf("| [3] Clientes                                 |\n");
    printf("| [4] Funcionários                             |\n");
    printf("| [0] Sair                                     |\n");
    printf("╰──────────────────────────────────────────────╯\n");

    op = opcao();
    return op;
}

/////////////////////////////////////////////////////////// AGENDAMENTOS ///////////////////////////////////////////
char modRelatorioAgendamento(void){
    char op;
    do {
        op = menuRelatorioAgendamento();
        if (op >= '1' && op <= '9'){
            relatorioAgendamento(op);
        }else if (op == '0'){
            break;
        }else{
            opcaoInvalida();
        }
    } while(op != '0');

    return op;
}

char menuRelatorioAgendamento(void){
    char op;
    system("clear");
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│          RELATÓRIOS DOS AGENDAMENTOS         │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] PENDENTES                               │\n" );
    printf("│  [2] CONCLUÍDOS                              │\n");
    printf("│  [3] CANCELADOS                              │\n");
    printf("│  [4] TODOS                                   │\n");
    printf("│  [5] ATIVOS                                  │\n");
    printf("│  [6] DO DIA                                  │\n");
    printf("│  [7] DO MÊS                                  │\n");
    printf("│  [8] DO FUNCIONÁRIO DO DIA                   │\n");
    printf("│  [9] DO FUNCIONÁRIO DO MÊS                   │\n");
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}


void printRelatAgendamentoListas(listaAgen* lista){
    char *nomeCli;
    char *nomeServ;
    char *nomeFunc;
    char situacao[15];
    while(lista != NULL){
        nomeCli = getNomeCli(lista->dados.clienteId);
        nomeServ = getNomeServ(lista->dados.servicoId);
        nomeFunc = getNomeFunc(lista->dados.funcionario);
        strcpy(situacao, getSituacaoStr(lista->dados.situacao));
        printf("├────────────┼─────────────────────────────────────────┼─────────────────────────────────────────┼──────────────────────────┼──────────────────┼─────────────────┼──────────────┤\n");
        printf("│    %s    │      %-30s     │       %-27s       │     %-16s     │    %.2s/%.2s/%.4s    │      %.2sh%.2sm     │  %-10s  │\n", lista->dados.agenId, nomeCli, nomeFunc, nomeServ, lista->dados.data + 6, lista->dados.data + 4, lista->dados.data, lista->dados.horario, lista->dados.horario + 2, situacao);
        free(nomeCli);
        free(nomeServ);
        free(nomeFunc);

        lista = lista->prox;
    }
}

listaAgen* listaDataAgendamento(Agendamento a, listaAgen* lista){
    listaAgen* novo = (listaAgen*) malloc(sizeof(listaAgen));
    novo->dados = a;
    novo->prox = NULL;

    if((lista == NULL) || ((strcmp(a.data, lista->dados.data) < 0 ) || ((strcmp(a.data, lista->dados.data) == 0) && (strcmp(a.horario, lista->dados.horario) < 0)))){
        novo->prox = lista;
        return novo;
    }

    listaAgen* anterior = lista;
    listaAgen* atual = lista->prox;
    
    while (atual != NULL && (strcmp(a.data, atual->dados.data) > 0 || (strcmp(a.data, atual->dados.data) == 0 && strcmp(a.horario, atual->dados.horario) > 0))){
        anterior = atual;
        atual = atual->prox;
    }
    anterior->prox = novo;
    novo->prox = atual;
    return lista; 
}

void liberarListaAgen(listaAgen* lista){
    listaAgen* aux;
    while(lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

void cabecarioRelatorioAgendamento(const char op){
    printf("╭───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮\n");
    switch(op) {
        case '1':
            printf("│                                                                              AGENDAMENTOS PENDENTES                                                                            │\n"); 
        break;
        case '2':
            printf("│                                                                             AGENDAMENTOS CONCLUÍDOS                                                                            │\n"); 
            break;
        case '3':
            printf("│                                                                             AGENDAMENTOS CANCELADOS                                                                            │\n"); 
            break;
        case '4':
            printf("│                                                                              TODOS OS AGENDAMENTOS                                                                             │\n");
            break;
        case '5':
            printf("│                                                                               AGENDAMENTOS ATIVOS                                                                             │\n"); 
            break;
        case '6':
            printf("│                                                                               AGENDAMENTOS DO DIA                                                                             │\n"); 
            break;
        case '7':
            printf("│                                                                               AGENDAMENTOS DO MÊS                                                                             │\n"); 
            break;
        case '8':
            printf("│                                                                       AGENDAMENTOS DO DIA POR FUNCIONÁRIO                                                                     │\n"); 
            break;
        case '9': 
            printf("│                                                                       AGENDAMENTOS DO MÊS POR FUNCIONÁRIO                                                                     │\n"); 
            break;
    }
    printf("├────────────┬─────────────────────────────────────────┬─────────────────────────────────────────┬──────────────────────────┬──────────────────┬─────────────────┼──────────────┤\n");
    printf("│     ID:    │                 Cliente:                │               Funcionario:              │         servico:         │       Data:      │     Horário:    │   Situação:  │\n"); 
}

void relatorioAgendamento(const char op){
    char* data = NULL;
    char* funcionarioId = NULL;
    Agendamento a;
    FILE *agen = fopen("agendamentos.dat","rb");
    if(!agen){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│    Não existem agendamentos cadastrados.     │\n");
        printf("╰──────────────────────────────────────────────╯\n");
        esperarEnter();
        return;
    }
    switch (op)
    {
    case '6':
        data = lerData(); 
        break;
    case '7':
        data = lerDataMes();
        break;
    case '8':
        telaListarFuncionarios();
        funcionarioId = lerIdFuncionarioRelat();
        data = lerData();
        break;
    case '9':
        telaListarFuncionarios();
        funcionarioId = lerIdFuncionarioRelat();
        data = lerDataMes();
        break;
    
    default:
        break;
    }
    listaAgen* lista = NULL;
    while(fread(&a,sizeof(Agendamento),1,agen)){
        switch(op){
            case '1': 
                if(a.situacao == PENDENTE){
                    lista = listaDataAgendamento(a, lista); 
                } 
                break;
            case '2': 
                if(a.situacao == CONCLUIDO){
                    lista = listaDataAgendamento(a, lista); 
                }
                break;
            case '3': 
                if(a.situacao == CANCELADO){
                    lista = listaDataAgendamento(a, lista);
                } 
                break;
            case '4': 
                lista = listaDataAgendamento(a, lista); 
                break;
            case '5': 
                if(a.status==True){
                    lista = listaDataAgendamento(a, lista); 
                } 
                break;
            case '6': 
                if(a.status && (strcmp(a.data, data) == 0)){//por dia
                    lista = listaDataAgendamento(a, lista); 
                } 
                break;
            case '7': 
                if(a.status && (strncmp(a.data, data, 6) == 0)){//por mes
                    lista = listaDataAgendamento(a, lista); 
                } 
                break;
            case '8': 
                if(a.status && (strcmp(a.data, data) == 0) && (strcmp(a.funcionario, funcionarioId) == 0)){//por dia + funcionario
                    lista = listaDataAgendamento(a, lista); 
                } 
                break;
            case '9': 
                if(a.status && (strncmp(a.data, data, 6) == 0) && (strcmp(a.funcionario, funcionarioId) == 0)){//por mes + funcionario
                    lista = listaDataAgendamento(a, lista); 
                } 
                break;
        }
    }
    fclose(agen);
    if(data != NULL){
        free(data);
    }
    if(funcionarioId != NULL){
        free(funcionarioId);
    }
    cabecarioRelatorioAgendamento(op);
    if(lista == NULL){
        printf("│    XXXXX   │                 XXXXXXXX                │               XXXXXXXXXXXX              │         XXXXXXXX         │     XX/XX/XXXX   │      XX:XX      │      XXXXX      │\n");
        printf("├────────────┴─────────────────────────────────────────┴─────────────────────────────────────────┴──────────────────────────┴──────────────────┴─────────────────┴─────────────────┤\n");
        printf("│                                                                 Não existem agendamentos com o filtro escolhido.                                                                 │\n");
        printf("├────────────┬─────────────────────────────────────────┬─────────────────────────────────────────┬──────────────────────────┬──────────────────┬─────────────────┬─────────────────┤\n");
    }else{
        printRelatAgendamentoListas(lista);
        liberarListaAgen(lista);
    }
    printf("╰────────────┴─────────────────────────────────────────┴─────────────────────────────────────────┴──────────────────────────┴──────────────────┴─────────────────┴─────────────────╯\n");
    esperarEnter();
}


/////////////////////////////////////////////////////////// SERVIÇOS ///////////////////////////////////////////

char modRelatorioServico(void){
    char op;
    do {
        op = menuRelatorioServico();
        if (op >= '1' && op <= '3') {
            relatorioServico(op);
        }
        else if (op == '4') {
            relatorioPrecoServico();
        }
        else if (op == '0') {
            break;
        }
        else {
            opcaoInvalida();
        }
    } while(op != '0');
    return op;
}

char menuRelatorioServico(void){
    char op;
    system("clear");
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            RELATÓRIOS DOS SERVIÇOS           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   |\n");
    printf("│  [2] ATIVOS                                  |\n");
    printf("│  [3] EXCLUÍDOS                               |\n");
    printf("|  [4] POR PREÇOS                              |\n");
    printf("│  [0] SAIR                                    |\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void cabecalhoRelatorioServico(const char op){
    switch(op) {
        case '1':
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│            RELATÓRIO DE TODOS OS             │\n");
        printf("│                   SERVIÇOS                   │\n");
        break;
        case '2':
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│            RELATÓRIO DOS SERVIÇOS            │\n");
        printf("│                    ATIVOS                    │\n");
        break;
        case '3':
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│            RELATÓRIO DOS SERVIÇOS            │\n");
        printf("│                   EXCLUÍDOS                  │\n");
        break;
        case '4':
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│            RELATÓRIO DOS SERVIÇOS            │\n");
        printf("│                 POR PREÇOS                   │\n");
        break;
    }
}

void printRelatServico(Servico *s){
    printf("├─────┬────────────────────────────────────┬────────────┤\n");
    printf("│ ID: %-6s │ Nome: %-30s │ R$%-8.2f │\n", s->id, s->nome, s->preco);
    printf("├─────┴────────────────────────────────────┴────────────┤\n");
}

void relatorioServico(const char op){
    int cont=0;
    Servico *s=(Servico*) malloc(sizeof(Servico));
    FILE *serv=fopen("servicos.dat","rb");
    if(!serv){
        naoHaCadastro();
        free(s);
        return;
    }
    while(fread(s,sizeof(Servico),1,serv)){
        int deveImprimir=0;
        switch(op){
            case '1': deveImprimir=1; break;
            case '2': if(s->status==True) deveImprimir=1; break;
            case '3': if(s->status==False) deveImprimir=1; break;
        }
        if(deveImprimir){ printRelatServico(s); cont++; }
    }
    fclose(serv);
    free(s);
    if(cont<1){
        semResulFiltro();
    }
}

listaServ* inserirServicoOrdenado(listaServ *lista, Servico novo, int crescente) {
    listaServ *novoNo = (listaServ*) malloc(sizeof(listaServ));
    novoNo->serv = novo;
    novoNo->prox = NULL;

    if (!lista) {
        return novoNo;
    }

    if (crescente) {
        if (novo.preco < lista->serv.preco) {
            novoNo->prox = lista;
            return novoNo;
        }
    }
    else {
        if (novo.preco > lista->serv.preco) {
            novoNo->prox = lista;
            return novoNo;
        }
    }

    listaServ *atual = lista;
    while (atual->prox != NULL) {
        if (crescente && novo.preco < atual->prox->serv.preco)
            break;
        if (!crescente && novo.preco > atual->prox->serv.preco)
            break;

        atual = atual->prox;
    }

    novoNo->prox = atual->prox;
    atual->prox = novoNo;

    return lista;
}


void relatorioPrecoServico(void) {
    FILE *fp = fopen("servicos.dat", "rb");
    if (!fp) {
        naoHaCadastro();
        return;
    }

    Servico tmp;
    listaServ *listaCres = NULL;  
    listaServ *listaDec  = NULL;  

    while (fread(&tmp, sizeof(Servico), 1, fp) == 1) {
        listaCres = inserirServicoOrdenado(listaCres, tmp, 1); // crescente
        listaDec  = inserirServicoOrdenado(listaDec,  tmp, 0); // decrescente
    }
    fclose(fp);

    if (listaCres == NULL) {
        semResulFiltro();
        return;
    }

    char op;
    do {
        system("clear");
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│        RELATÓRIO SERVIÇOS POR PREÇO          |\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│  [1] MAIS BARATOS                            │\n");
        printf("│  [2] MAIS CAROS                              │\n");
        printf("│  [0] VOLTAR                                  │\n");
        printf("╰──────────────────────────────────────────────╯\n");
        op = opcao();

        if (op == '0') {
            break;

        } else if (op == '1' || op == '2') {
            listaServ *uso = (op == '1') ? listaCres : listaDec;

            system("clear");
            printf("╭────────────── RELATÓRIO DE SERVIÇOS POR PREÇO ───────────────╮\n");
            printf("│ ID     │ Nome                            │ Preço             │\n");
            printf("├────────┼─────────────────────────────────┼────────────────────┤\n");

            listaServ *t = uso;
            while (t != NULL) {
                printRelatServico(&t->serv);
                t = t->prox;
            }

            printf("╰──────────────────────────────────────────────────────────────╯\n");
            esperarEnter();
        } else {
            opcaoInvalida();
        }
    } while (op != '0');
    liberarListaServ(listaCres);
    liberarListaServ(listaDec);
}

void liberarListaServ(listaServ *lista) {
    listaServ *aux;
    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

/////////////////////////////////////////////////////////// CLIENTES ///////////////////////////////////////////

char modRelatorioCliente(void){
    char op;
    do {
        op = menuRelatorioCliente();
        if (op >= '1' && op <= '3') {
            relatorioCliente(op);
        } else if (op == '4') {
            relatorioHistoricoCliente();
        } else if (op == '0') {
            break;
        } else {
            opcaoInvalida();
        }
    } while(op != '0');

    return op;
}

char menuRelatorioCliente(void){
    char op;
    system("clear");
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│          RELATÓRIOS DOS CLIENTES             │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   |\n");
    printf("│  [2] ATIVOS                                  |\n");
    printf("│  [3] EXCLUÍDOS                               |\n");
    printf("│  [4] HISTÓRICO                               |\n");
    printf("│  [0] SAIR                                    |\n");
    printf("╰──────────────────────────────────────────────╯\n");
    
    op = opcao();
    return op;
}

void cabecalhoRelatorioCliente(char op) {
    system("clear");

    switch (op) {
        case '1':
            printf("╭──────────────────────── RELATÓRIO DE TODOS OS CLIENTES ────────────────────────╮\n");
            printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n");
            printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n");
            break;
        case '2':
            printf("╭──────────────────────── RELATÓRIO DE CLIENTES ATIVOS ─────────────────────────╮\n");
            printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n");
            printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n");
            break;
        case '3':
            printf("╭──────────────────────── RELATÓRIO DE CLIENTES EXCLUÍDOS ───────────────────────╮\n");
            printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n");
            printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n");
            break;
        default:
            return;
    }
}

void printRelatCliente(Cliente *c){
    if (c == NULL) return;
    printf("│ %-5s │ %-32s │ %-14s │ %-18s │\n",
           c->id,
           c->nome,
           c->dataNascimento,
           c->telefone);
}

listaCliente* inserirClienteFim(listaCliente* lista, Cliente cli) {
    listaCliente* novo = (listaCliente*) malloc(sizeof(listaCliente));
    if (!novo) return lista;
    novo->dados = cli;
    novo->prox = NULL;

    if (lista == NULL) return novo;

    listaCliente* aux = lista;
    while (aux->prox != NULL) aux = aux->prox;
    aux->prox = novo;
    return lista;
}

listaCliente* inserirClienteInicio(listaCliente* lista, Cliente cli) {
    listaCliente* novo = (listaCliente*) malloc(sizeof(listaCliente));
    if (!novo) return lista;
    novo->dados = cli;
    novo->prox = lista;
    return novo;
}

void liberarListaCliente(listaCliente* lista) {
    listaCliente* atual;
    while (lista != NULL) {
        atual = lista;
        lista = lista->prox;
        free(atual);
    }
}

int temResultadosClienteLista(char op, listaCliente* lista) {
    listaCliente* aux = lista;
    while (aux != NULL) {
        if (op == '1') return 1;
        if (op == '2' && aux->dados.status == 1) return 1;
        if (op == '3' && aux->dados.status == 0) return 1;
        aux = aux->prox;
    }
    return 0;
}

void relatorioCliente(const char op){
    FILE *cli = fopen("clientes.dat","rb");
    if(!cli){
        naoHaCadastro();
        return;
    }
    Cliente tmp;
    int tem = 0;
    while (fread(&tmp, sizeof(Cliente), 1, cli) == 1) {
        if (op == '1' ||
            (op == '2' && tmp.status == 1) ||
            (op == '3' && tmp.status == 0)) {
            tem = 1;
            break;
        }
    }
    if (!tem) {
        fclose(cli);
        semResulFiltro();
        return;
    }

    cabecalhoRelatorioCliente(op);
    rewind(cli);

    while (fread(&tmp, sizeof(Cliente), 1, cli) == 1) {
        int deve = 0;
        switch(op) {
            case '1': deve = 1; break;
            case '2': if (tmp.status == 1) deve = 1; break;
            case '3': if (tmp.status == 0) deve = 1; break;
        }
        if (deve) printRelatCliente(&tmp);
    }
    printf("╰────────────────────────────────────────────────────────────────────────────────╯\n");
    fclose(cli);
    esperarEnter();
}

void relatorioHistoricoCliente(void) {
    FILE *cli = fopen("clientes.dat","rb");
    if (!cli) {
        naoHaCadastro();
        return;
    }

    listaCliente* listaOrd = NULL;
    listaCliente* listaRev = NULL;
    Cliente tmp;
    while (fread(&tmp, sizeof(Cliente), 1, cli) == 1) {
        listaOrd = inserirClienteFim(listaOrd, tmp);
        listaRev = inserirClienteInicio(listaRev, tmp);
    }
    fclose(cli);

    if (listaOrd == NULL) {
        semResulFiltro();
        return;
    }
    char opHist;
    do {
        system("clear");
        printf("╭──────────────────────────────────────────────╮\n");
        printf("│            RELATÓRIO: HISTÓRICO              │\n");
        printf("├──────────────────────────────────────────────┤\n");
        printf("│  [1] MAIS RECENTES                           │\n");
        printf("│  [2] MAIS ANTIGOS                            │\n");
        printf("│  [0] VOLTAR                                  │\n");
        printf("╰──────────────────────────────────────────────╯\n");
        opHist = opcao();

        if (opHist == '0') {
            break;
        } else if (opHist == '1' || opHist == '2') {
            listaCliente* uso = (opHist == '1') ? listaRev : listaOrd;

            system("clear");
            printf("╭─────────────────── RELATÓRIO DE CLIENTES POR HISTÓRICO ────────────────────────╮\n");
            printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n");
            printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n");

            listaCliente* t = uso;
            while (t != NULL) {
                printRelatCliente(&t->dados);
                t = t->prox;
            }
            printf("╰────────────────────────────────────────────────────────────────────────────────╯\n");
            esperarEnter();
        } else {
            opcaoInvalida();
        }
    } while (opHist != '0');
    liberarListaCliente(listaOrd);
    liberarListaCliente(listaRev);
}

/////////////////////////////////////////////////////////// FUNCIONÁRIOS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

char modRelatorioFuncionario(void){
    char op;
    do{
        op = menuRelatorioFuncionario();
        switch(op){
            case '1': case '2': case '3': case '4':
                relatorioFuncionario(op);
                break;
            case '0': break;
            default: opcaoInvalida(); break;
        }
    } while(op!='0');
    return op;
}

char menuRelatorioFuncionario(void){
    char op;
    system("clear");
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│          RELATÓRIOS DOS FUNCIONÁRIOS         │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   │\n");
    printf("│  [2] ATIVOS                                  │\n");
    printf("│  [3] EXCLUÍDOS                               │\n");
    printf("│  [4] EM ORDEM ALFABÉTICA                     │\n");
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void cabecarioRelatorioFuncionario(const char op){
    switch(op){
        case '1':
            printf("╭───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮\n"); 
            printf("│                                                                            TODOS OS FUNCIONÁRIOS                                                                          │\n"); 
        break;
        case '2':
            printf("╭───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮\n"); 
            printf("│                                                                             FUNCIONÁRIOS ATIVOS                                                                           │\n"); 
            break;
        case '3':
            printf("╭───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮\n"); 
            printf("│                                                                            FUNCIONÁRIOS INATIVOS                                                                          │\n"); 
            break;
        case '4':
            printf("╭───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────╮\n"); 
            printf("│                                                                      FUNCIONÁRIOS EM ORDEM ALFABÉTICA                                                                     │\n"); 
            break;
    }
    printf("├────────────┬─────────────────────────────────────────────┬────────────────┬─────────────────┬───────────────────┬───────────────────────────────────────┬─────────────────┤\n");
    printf("│     ID:    │                 Funcionário:                │      CPF:      │   Nascimento:   │     Telefone:     │                 Email:                │     Salário:    │\n");
}

void printRelatFuncionario(listaFunc* lista){
    while(lista != NULL){
        printf("├────────────┼─────────────────────────────────────────────┼────────────────┼─────────────────┼───────────────────┼───────────────────────────────────────┼─────────────────┤\n");
        printf("│    %s    │   %-39s   │   %-11s  │   %.2s/%.2s/%.4s    │  (%.2s) %.1s %.4s-%.4s │   %-33s   │   R$ %-10.2f │\n",lista->dados.id, lista->dados.nome, lista->dados.cpf, lista->dados.nascimento, lista->dados.nascimento+2, lista->dados.nascimento+4, lista->dados.telefone, lista->dados.telefone+2, lista->dados.telefone+3, lista->dados.telefone+7, lista->dados.email, lista->dados.salario);
        lista = lista->prox;
    }
}

// void relatorioFuncionario(const char op){
//     int cont=0;
//     Funcionario f=(Funcionario) malloc(sizeof(Funcionario));
//     FILE *fun=fopen("FUNCIONARIOS.dat","rb");
//     if(!fun){ printf("├──────────────────────────────────────────────┤\n│    Não existem funcionários cadastrados.     │\n╰──────────────────────────────────────────────╯\n"); esperarEnter(); free(f); return;}
//     while(fread(f,sizeof(Funcionario),1,fun)){
//         int deveImprimir=0;
//         switch(op){ case '1': deveImprimir=1; break; case '2': if(f->status==True) deveImprimir=1; break; case '3': if(f->status==False) deveImprimir=1; break; }
//         if(deveImprimir){ printRelatFuncionario(f); cont++; }
//     }
//     fclose(fun);
//     free(f);
//     if(cont<1){ printf("├──────────────────────────────────────────────┤\n│    Não existem funcionários com o filtro     │\n│                  escolhido.                  │\n"); }
//     printf("╰──────────────────────────────────────────────╯\n");
//     esperarEnter();
// }
void relatorioFuncionario(const char op){
    Funcionario f;
    FILE* func = fopen("funcionarios.dat", "rb");
    if(!func){
        arqInexistente();
        return;
    }
    listaFunc* lista =NULL;
    while(fread(&f, sizeof(Funcionario), 1, func)){
        switch (op)
        {
        case '1':
            lista = listaInvertidaFuncionario(f, lista);
            break;
        case '2':
            if(f.status){
                lista = listaInvertidaFuncionario(f, lista);
            }
            break;
        case '3':
            if(!f.status){
                lista = listaInvertidaFuncionario(f, lista);
            }
            break;
        case '4':
            if(f.status){
                lista = listaAlfabeticaFuncionario(f, lista);
            }
            break;
        
        default:
            break;
        }
    }
    fclose(func);
    if(lista != NULL){
        cabecarioRelatorioFuncionario(op);
        printRelatFuncionario(lista);
        liberaListaFunc(lista);
    } else {
        printf("├────────────┬─────────────────────────────────────────────┬────────────────┬─────────────────┬───────────────────┬───────────────────────────────────────┬─────────────────┤\n");
        printf("│    XXXXX   │                 XXXXXXXX                    │ XXX.XXX.XXX-XX │   XX/XX/XXXX    │ (XX) X XXXX-XXXX  │            XXXXXX@XXXX.XXXX           │    R$ XXXX.XX   │\n");
        printf("├────────────┴─────────────────────────────────────────────┴────────────────┴─────────────────┴───────────────────┴───────────────────────────────────────┴─────────────────┤\n");
        printf("│                                                                 Não existem dados com o filtro escolhido.                                                                 │\n");
        printf("├────────────┬─────────────────────────────────────────────┬────────────────┬─────────────────┬───────────────────┬───────────────────────────────────────┬─────────────────┤\n");
    }
    printf("╰────────────┴─────────────────────────────────────────────┴────────────────┴─────────────────┴───────────────────┴───────────────────────────────────────┴─────────────────╯\n");
    esperarEnter();

}


listaFunc* listaInvertidaFuncionario(Funcionario f, listaFunc* lista){
    listaFunc* novo = (listaFunc*) malloc(sizeof(listaFunc));
    novo->dados = f;
    novo->prox = lista;
    return novo;
}

void liberaListaFunc(listaFunc* lista){
    listaFunc* aux = (listaFunc*) malloc(sizeof(listaFunc));
    while(lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}

listaFunc* listaAlfabeticaFuncionario(Funcionario f, listaFunc* lista){
    listaFunc* novo = (listaFunc*) malloc(sizeof(listaFunc));
    novo->dados = f;
    novo->prox = NULL;

    if((lista == NULL) || (strcmp(f.nome, lista->dados.nome) < 0)){
        novo->prox = lista;
        return novo;
    }

    listaFunc* anterior = lista;
    listaFunc* atual = lista->prox;
    while((atual != NULL) && (strcmp(f.nome, atual->dados.nome) > 0)){
        anterior = atual;
        atual = atual->prox;
    }
    anterior->prox = novo;
    novo->prox = atual;

    return lista;
}
        