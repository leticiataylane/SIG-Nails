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
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);
    printf(ciano negrito "                     RELATÓRIOS               \n" reset);
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);
    printf(ciano "1. Agendamentos\n" reset);
    printf(ciano "2. Serviços\n" reset);
    printf(ciano "3. Clientes\n" reset);
    printf(ciano "4. Funcionários\n" reset);
    printf(ciano "0. Sair\n" reset);
    printf(roxo negrito "★────────────────────────────────────────────★\n" reset);

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
        switch(op) {
            case '1':
            cabecarioRelatorioServico(op);
            relatorioServico(op);
            break;
            case '2':
            cabecarioRelatorioServico(op);
            relatorioServico(op);
            break;
            case '3':
            cabecarioRelatorioServico(op);
            relatorioServico(op);
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

char menuRelatorioServico(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            RELATÓRIOS DOS SERVIÇOS           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   |\n");
    printf("│  [2] ATIVOS                                  |\n");
    printf("│  [3] EXCLUÍDOS                               |\n");
    printf("│  [0] SAIR                                    |\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void cabecarioRelatorioServico(const char op){
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
        printf("├──────────────────────────────────────────────┤\n");
        printf("│      Não existem serviços cadastrados.       │\n");
        printf("╰──────────────────────────────────────────────╯\n");
        esperarEnter();
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
        printf("├──────────────────────────────────────────────┤\n");
        printf("│      Não existem serviços com o filtro       │\n");
        printf("│                  escolhido.                  │\n");
        printf("╰──────────────────────────────────────────────╯\n");
        esperarEnter();
    }
}

/////////////////////////////////////////////////////////// CLIENTES ///////////////////////////////////////////

char modRelatorioCliente(void) {
    char op;
    do {
        op = menuRelatorioCliente();
        switch(op){
            case '1':
            case '2':
            case '3':
            cabecarioRelatorioCliente(op);
            relatorioCliente(op);
            break;
            case '0':
            break;
            default:
            opcaoInvalida();
            break;
        }
    } while(op!='0');
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
    printf("│  [4] INATIVOS                                |\n");
    printf("│  [0] SAIR                                    |\n");
    printf("╰──────────────────────────────────────────────╯\n");
    
    op = opcao();
    return op;
}

void cabecarioRelatorioCliente(const char op){
    switch(op){
        case '1': 
        printf("╭──────────────────────── RELATÓRIO DE TODOS OS CLIENTES ────────────────────────╮\n"); 
        printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n"); 
        printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n");  
        break;
        case '2': 
        printf("╭───────────────────────── RELATÓRIO DE CLIENTES ATIVOS ─────────────────────────╮\n"); 
        printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n"); 
        printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n");  
        break;
        case '3': 
        printf("╭─────────────────────── RELATÓRIO DE CLIENTES EXCLUÍDOS ────────────────────────╮\n"); 
        printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n"); 
        printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n"); 
        break;
        case '4': 
        printf("╭──────────────────────── RELATÓRIO DE CLIENTES INATIVOS ────────────────────────╮\n"); 
        printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n"); 
        printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n"); 
        break;
        case '0': 
        break;
        default:
        opcaoInvalida();
        break;}
    }
    
    
void printRelatCliente(Cliente *c){
    printf("│ %-5s │ %-32s │ %-14s │ %-18s │\n", c->id, c->nome, c->dataNascimento, c->telefone);
}

void relatorioCliente(const char op){
    int cont = 0;
    Cliente *c = (Cliente*) malloc(sizeof(Cliente));
    FILE *cli = fopen("clientes.dat","rb");
    if(!cli){ printf("├──────────────────────────────────────────────┤\n│      Não existem clientes cadastrados.       │\n╰──────────────────────────────────────────────╯\n"); esperarEnter(); free(c); return; }
    while(fread(c,sizeof(Cliente),1,cli)){
        int deveImprimir=0;
        switch(op){ case '1': deveImprimir=1; break; case '2': if(c->status==True) deveImprimir=1; break; case '3': if(c->status==False) deveImprimir=1; break; }
        if(deveImprimir){ printRelatCliente(c); cont++; }
    }
    fclose(cli);
    free(c);
    if(cont<1){ printf("├──────────────────────────────────────────────┤\n│      Não existem clientes com o filtro       │\n│                  escolhido.                  │\n"); }
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();
}

void relatorioClientesInativos(void) {
    int cont = 0;
    Cliente *c = (Cliente*) malloc(sizeof(Cliente));
    Agendamento *a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *cli = fopen("clientes.dat","rb");
    FILE *agen;
    
    if(!cli){
        printf("├──────────────────────────────────────────────┤\n│      Não existem clientes cadastrados.       │\n╰──────────────────────────────────────────────╯\n");
        esperarEnter();
        free(c); free(a);
        return;
    }
    
    printf("╭──────────────────────── RELATÓRIO DE CLIENTES INATIVOS ────────────────────────╮\n");
    printf("│ ID    │ Nome                             │ Nascimento     │ Telefone           │\n"); 
    printf("├───────┼──────────────────────────────────┼────────────────┼────────────────────┤\n"); 
    
    while(fread(c,sizeof(Cliente),1,cli)){
        if(c->status == True){ // Apenas clientes ativos
            int temAgendamento = 0;
            agen = fopen("agendamentos.dat","rb");
            if(agen){
                while(fread(a,sizeof(Agendamento),1,agen)){
                    if(strcmp(a->clienteId, c->id) == 0 && a->situacao != CONCLUIDO){
                        temAgendamento = 1; // Cliente possui agendamento ativo
                        break;
                    }
                }
                fclose(agen);
            }
            if(!temAgendamento){ //inativo
                printRelatCliente(c);
                cont++;
            }
        }
    }
    
    fclose(cli);
    free(c);
    free(a);
    
    if(cont<1){
        printf("├──────────────────────────────────────────────┤\n│    Não existem clientes inativos.            │\n");
    }
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();
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
        