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
        switch(op) {
            case '1':
                cabecarioRelatorioAgendamento(op);
                relatorioAgendamento(op);
                break;
            case '2':
                cabecarioRelatorioAgendamento(op);
                relatorioAgendamento(op);
                break;
            case '3':
                cabecarioRelatorioAgendamento(op);
                relatorioAgendamento(op);
                break;
            case '4':
                cabecarioRelatorioAgendamento(op);
                relatorioAgendamento(op);
                break;
            case '5':
                cabecarioRelatorioAgendamento(op);
                relatorioAgendamento(op);
                break;
            case '6':
                cabecarioRelatorioAgendamento(op);
                relatorioAgendamento(op);
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
    printf("│  [6] EXCLUÍDOS                               │\n");
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void printRelatAgendamento(Agendamento *a){
    char *nomeCli;
    char *nomeServ;
    printf("├───────────────┬────────────────────────────────────┬────────────┬───────────────┤\n");
    printf("│ ID: %-12s │ ", a->agenId);
    nomeCli = getNomeCli(a->clienteId);
    printf("%-34s │ ", nomeCli);
    free(nomeCli);
    nomeServ = getNomeServ(a->servicoId);
    printf("%-10s │ %-13s │\n", nomeServ, a->situacao);
    free(nomeServ);
    printf("├───────────────┴────────────────────────────────────┴────────────┴───────────────┤\n");
}

void cabecarioRelatorioAgendamento(const char op){
    switch(op) {
        case '1': printf("╭──────────────────────────────────────────────╮\n│          RELATÓRIO DOS AGENDAMENTOS          │\n│                   PENDENTES                  │\n"); break;
        case '2': printf("╭──────────────────────────────────────────────╮\n│          RELATÓRIO DOS AGENDAMENTOS          │\n│                   CONCLUÍDOS                 │\n"); break;
        case '3': printf("╭──────────────────────────────────────────────╮\n│          RELATÓRIO DOS AGENDAMENTOS          │\n│                   CANCELADOS                 │\n"); break;
        case '4': printf("╭──────────────────────────────────────────────╮\n│            RELATÓRIO DE TODOS OS             │\n│                 AGENDAMENTOS                 │\n"); break;
        case '5': printf("╭──────────────────────────────────────────────╮\n│          RELATÓRIO DOS AGENDAMENTOS          │\n│                    ATIVOS                    │\n"); break;
        case '6': printf("╭──────────────────────────────────────────────╮\n│          RELATÓRIO DOS AGENDAMENTOS          │\n│                   EXCLUÍDOS                  │\n"); break;
    }
}

void relatorioAgendamento(const char op){
    int cont = 0;
    Agendamento* a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen = fopen("agendamentos.dat","rb");
    if(!agen){
        printf("├──────────────────────────────────────────────┤\n│    Não existem agendamentos cadastrados.     │\n╰──────────────────────────────────────────────╯\n");
        esperarEnter();
        free(a);
        return;
    }
    while(fread(a,sizeof(Agendamento),1,agen)){
        int deveImprimir = 0;
        switch(op){
            case '1': if(strcmp(a->situacao,"Pendente")==0) deveImprimir=1; break;
            case '2': if(strcmp(a->situacao,"Concluído")==0) deveImprimir=1; break;
            case '3': if(strcmp(a->situacao,"Cancelado")==0) deveImprimir=1; break;
            case '4': deveImprimir=1; break;
            case '5': if(a->status==True) deveImprimir=1; break;
            case '6': if(a->status==False) deveImprimir=1; break;
        }
        if(deveImprimir){ printRelatAgendamento(a); cont++; }
    }
    fclose(agen);
    free(a);

    if(cont<1){
        printf("├──────────────────────────────────────────────┤\n│    Não existem agendamentos com o filtro     │\n│                  escolhido.                  │\n");
    }
    printf("╰──────────────────────────────────────────────╯\n");
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
    printf("╭──────────────────────────────────────────────╮\n│            RELATÓRIOS DOS SERVIÇOS           │\n├──────────────────────────────────────────────┤\n│  [1] TODOS\n│  [2] ATIVOS\n│  [3] EXCLUÍDOS\n│  [0] SAIR\n╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void cabecarioRelatorioServico(const char op){
    switch(op) {
        case '1': printf("╭──────────────────────────────────────────────╮\n│            RELATÓRIO DE TODOS OS             │\n│                   SERVIÇOS                   │\n"); break;
        case '2': printf("╭──────────────────────────────────────────────╮\n│            RELATÓRIO DOS SERVIÇOS            │\n│                    ATIVOS                    │\n"); break;
        case '3': printf("╭──────────────────────────────────────────────╮\n│            RELATÓRIO DOS SERVIÇOS            │\n│                   EXCLUÍDOS                  │\n"); break;
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
    if(!serv){ printf("├──────────────────────────────────────────────┤\n│      Não existem serviços cadastrados.       │\n╰──────────────────────────────────────────────╯\n"); esperarEnter(); free(s); return;}
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
    if(cont<1){ printf("├──────────────────────────────────────────────┤\n│      Não existem serviços com o filtro       │\n│                  escolhido.                  │\n"); }
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();
}

/////////////////////////////////////////////////////////// CLIENTES ///////////////////////////////////////////

char modRelatorioCliente(void){
    char op;
    do {
        op = menuRelatorioCliente();
        switch(op){
            case '1': case '2': case '3':
                cabecarioRelatorioCliente(op);
                relatorioCliente(op);
                break;
            case '0': break;
            default: opcaoInvalida(); break;
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
            printf("╭───────────────────────── RELATÓRIO DE TODOS OS CLIENTES ─────────────────────────╮\n"); 
            printf("│ ID    │ Nome                          │ Nascimento │ Telefone       │\n"); 
            printf("├───────┼───────────────────────────────┼────────────┼───────────────┤\n"); 
            break;
        case '2': 
            printf("╭────────────────────────── RELATÓRIO DE CLIENTES ATIVOS ─────────────────────────╮\n"); 
            printf("│ ID    │ Nome                          │ Nascimento │ Telefone       │\n"); 
            printf("├───────┼───────────────────────────────┼────────────┼───────────────┤\n"); 
            break;
        case '3': 
            printf("╭──────────────────────── RELATÓRIO DE CLIENTES EXCLUÍDOS ────────────────────────╮\n"); 
            printf("│ID    │ Nome                          │ Nascimento │ Telefone       │\n"); 
            printf("├───────┼───────────────────────────────┼────────────┼───────────────┤\n"); 
            break;
        case '4': 
            printf("╭──────────────────────── RELATÓRIO DE CLIENTES INATIVOS ────────────────────────╮\n"); 
            printf("│ID    │ Nome                          │ Nascimento │ Telefone       │\n"); 
            printf("├───────┼───────────────────────────────┼────────────┼───────────────┤\n"); 
            break;
        case '0': 
            opcaoInvalida();
            break;
    }
}

void printRelatCliente(Cliente *c){
    printf("│ %-6s │ %-29s │ %-10s │ %-13s │\n", c->id, c->nome, c->dataNascimento, c->telefone);
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

    printf("╭────────────────────── RELATÓRIO DE CLIENTES INATIVOS ──────────────────────╮\n");
    printf("│ ID    │ Nome                          │ Nascimento │ Telefone       │\n");
    printf("├───────┼───────────────────────────────┼────────────┼───────────────┤\n");

    while(fread(c,sizeof(Cliente),1,cli)){
        if(c->status == True){ // Apenas clientes ativos
            int temAgendamento = 0;
            agen = fopen("agendamentos.dat","rb");
            if(agen){
                while(fread(a,sizeof(Agendamento),1,agen)){
                    if(strcmp(a->clienteId, c->id) == 0 && strcmp(a->situacao,"Concluído")!=0){
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

/////////////////////////////////////////////////////////// FUNCIONÁRIOS ///////////////////////////////////////////

char modRelatorioFuncionario(void){
    char op;
    do{
        op = menuRelatorioFuncionario();
        switch(op){
            case '1': case '2': case '3':
                cabecarioRelatorioFuncionario(op);
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
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void cabecarioRelatorioFuncionario(const char op){
    switch(op){
        case '1': printf("╭───────────────────────── RELATÓRIO DE TODOS OS FUNCIONÁRIOS ───────────────────────╮\n│ Nome                        │ CPF             │ Nascimento │ Telefone         │ E-mail                    │ Salário     │\n├─────────────────────────────┼─────────────────┼────────────┼─────────────────┼───────────────────────────┼─────────────┤\n"); break;
        case '2': printf("╭────────────────────────── RELATÓRIO DE FUNCIONÁRIOS ATIVOS ────────────────────────╮\n│ Nome                        │ CPF             │ Nascimento │ Telefone         │ E-mail                    │ Salário     │\n├─────────────────────────────┼─────────────────┼────────────┼─────────────────┼───────────────────────────┼─────────────┤\n"); break;
        case '3': printf("╭───────────────────────── RELATÓRIO DE FUNCIONÁRIOS EXCLUÍDOS ──────────────────────╮\n│ Nome                        │ CPF             │ Nascimento │ Telefone         │ E-mail                    │ Salário     │\n├─────────────────────────────┼─────────────────┼────────────┼─────────────────┼───────────────────────────┼─────────────┤\n"); break;
    }
}

void printRelatFuncionario(Funcionario *f){
    printf("│ %-27s │ %-15s │ %.2s/%.2s/%.4s │ (%.2s) %.1s %.4s-%.4s │ %-25s │ R$%-8.2f │\n",
           f->nome, f->cpf, f->nascimento, f->nascimento+2, f->nascimento+4,
           f->telefone, f->telefone+2, f->telefone+3, f->telefone+7, f->email, f->salario);
}

void relatorioFuncionario(const char op){
    int cont=0;
    Funcionario *f=(Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun=fopen("FUNCIONARIOS.dat","rb");
    if(!fun){ printf("├──────────────────────────────────────────────┤\n│    Não existem funcionários cadastrados.     │\n╰──────────────────────────────────────────────╯\n"); esperarEnter(); free(f); return;}
    while(fread(f,sizeof(Funcionario),1,fun)){
        int deveImprimir=0;
        switch(op){ case '1': deveImprimir=1; break; case '2': if(f->status==True) deveImprimir=1; break; case '3': if(f->status==False) deveImprimir=1; break; }
        if(deveImprimir){ printRelatFuncionario(f); cont++; }
    }
    fclose(fun);
    free(f);
    if(cont<1){ printf("├──────────────────────────────────────────────┤\n│    Não existem funcionários com o filtro     │\n│                  escolhido.                  │\n"); }
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();
}