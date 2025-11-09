#include <stdio.h>
#include <string.h>
#include "clientes.h"
#include "servicos.h"
#include "agendamentos.h"
#include "funcionarios.h"
#include "ler_dados.h"
#include "relatorios.h"


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
                telaFinal();
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while(op != '0'); // continua até o usuário escolher sair

    return op;

}

///////////////////////////////////////////////////////////AGENDAMENTOS////////////////////////////////////////////////////////////////////////
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
    } while(op != '0'); // continua até o usuário escolher sair

    return op;

}

char menuRelatorioAgendamento(void){
    char op;
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
    printf("├──────────────────────────────────────────────┤\n");
    printf("│ ID Agendamento: %-28s │\n", a->agenId);
    nomeCli = getNomeCli(a->clienteId);
    printf("│ Nome Cliente: %-30s │\n", nomeCli);
    free(nomeCli);
    nomeServ = getNomeServ(a->servicoId);
    printf("│ Nome Serviço: %-30s │\n", nomeServ);
    free(nomeServ);
    printf("│ Situação: %-34s │\n", a->situacao);
}


void cabecarioRelatorioAgendamento(const char op){
    switch(op) {
            case '1': // PENDENTES
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS AGENDAMENTOS          │\n");
                printf("│                   PENDENTES                  │\n");
                break;

            case '2': // CONCLUÍDOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS AGENDAMENTOS          │\n");
                printf("│                   CONCLUÍDOS                 │\n");             
                break;

            case '3': // CANCELADOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS AGENDAMENTOS          │\n");
                printf("│                   CANCELADOS                 │\n"); 
                break;

            case '4': // TODOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DE TODOS OS             │\n");
                printf("│                 AGENDAMENTOS                 │\n");
                break;

            case '5': // ATIVOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS AGENDAMENTOS          │\n");
                printf("│                    ATIVOS                    │\n");     
                break;

            case '6': // EXCLUÍDOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS AGENDAMENTOS          │\n");
                printf("│                   EXCLUÍDOS                  │\n");
                break;
        }

}

void relatorioAgendamento(const char op){
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

    while (fread(a, sizeof(Agendamento), 1, agen)) {
        int deveImprimir = 0; // controle de filtragem

        switch(op) {
            case '1': // PENDENTES
                if (strcmp(a->situacao, "Pendente") == 0){
                    deveImprimir = 1;
                }
                break;

            case '2': // CONCLUÍDOS
                if (strcmp(a->situacao, "Concluído") == 0){
                    deveImprimir = 1;
                }
                break;

            case '3': // CANCELADOS
                if (strcmp(a->situacao, "Cancelado") == 0){
                    deveImprimir = 1;
                }
                break;

            case '4': // TODOS
                deveImprimir = 1;
                break;

            case '5': // ATIVOS
                if (a->status == True){
                    deveImprimir = 1;
                }
                break;

            case '6': // EXCLUÍDOS
                if (a->status == False){
                    deveImprimir = 1;
                }
                break;
        }

        if (deveImprimir) {
            printRelatAgendamento(a);
            cont +=1;
        }
    }
    fclose(agen);
    free(a);

    if(cont < 1){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│    Não existem agendamentos com o filtro     │\n");
        printf("│                  escolhido.                  │\n");
        
    }

    printf("╰──────────────────────────────────────────────╯\n");

    esperarEnter();

}

/////////////////////////////////////////////////////SERVICOS/////////////////////////////////////////////////////////////////////

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
    } while(op != '0'); // continua até o usuário escolher sair

    return op;

}

char menuRelatorioServico(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            RELATÓRIOS DOS SERVIÇOS           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   │\n");
    printf("│  [2] ATIVOS                                  │\n");
    printf("│  [3] EXCLUÍDOS                               │\n"); 
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void printRelatServico(Servico *s){
    printf("├──────────────────────────────────────────────┤\n");
    printf("│ ID: %-40s  │\n", s->id);
    printf("│ Nome: %-38s │ \n", s->nome);
    printf("│ Preço: R$%-37.2f  │\n", s->preco);
}


void cabecarioRelatorioServico(const char op){
    switch(op) {

            case '1': // TODOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DE TODOS OS             │\n");
                printf("│                   SERVIÇOS                   │\n");
                break;

            case '2': // ATIVOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DOS SERVIÇOS            │\n");
                printf("│                    ATIVOS                    │\n");     
                break;

            case '3': // EXCLUÍDOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DOS SERVIÇOS            │\n");
                printf("│                   EXCLUÍDOS                  │\n");
                break;
        }

}

void relatorioServico(const char op){
    int cont = 0;
    Servico *s;
    s = (Servico*) malloc(sizeof(Servico));
    FILE *serv;
    

    serv = fopen("servicos.dat","rb");
    if(serv == NULL){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│      Não existem serviços cadastrados.       │\n");
        free(s);
        return cont;
    }

    while (fread(s, sizeof(Servico), 1, serv)) {
        int deveImprimir = 0; // controle de filtragem

        switch(op) {
            case '1': // TODOS
                deveImprimir = 1;
                break;

            case '2': // ATIVOS
                if (s->status == True){
                    deveImprimir = 1;
                }
                break;

            case '3': // EXCLUIDOS
                if (s->status == False){
                    deveImprimir = 1;
                }
                break;
        }

        if (deveImprimir) {
            printRelatServico(s);
            cont +=1;
        }
    }
    fclose(serv);
    free(s);

    if(cont < 1){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│      Não existem serviços com o filtro       │\n");
        printf("│                  escolhido.                  │\n");
        
    }

    printf("╰──────────────────────────────────────────────╯\n");

    esperarEnter();

}


////////////////////////////////////////////////////////////////////CLIENTES////////////////////////////////////////////////////////////////////////////


char modRelatorioCliente(void){
    char op;
    do {
        op = menuRelatorioCliente();
        switch(op) {
            case '1':
                cabecarioRelatorioCliente(op);
                relatorioCliente(op);
                break;
            case '2':
                cabecarioRelatorioCliente(op);
                relatorioCliente(op);
                break;
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
    } while(op != '0'); // continua até o usuário escolher sair

    return op;

}

char menuRelatorioCliente(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│            RELATÓRIOS DOS CLIENTES           │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   │\n");
    printf("│  [2] ATIVOS                                  │\n");
    printf("│  [3] EXCLUÍDOS                               │\n"); 
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void printRelatCliente(Cliente *c){
    printf("★───────────────────────────────────────────────★\n");
    printf("│ ID: %-40s \n", c->id);
    printf("│ Nome: %-38s \n", c->nome);
    printf("│ Nascimento: %-32s \n", c->dataNascimento);
    printf("│ Telefone: %-35s \n", c->telefone);
}


void cabecarioRelatorioCliente(const char op){
    switch(op) {

            case '1': // TODOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DE TODOS OS             │\n");
                printf("│                   CLIENTES                   │\n");
                break;

            case '2': // ATIVOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DOS CLIENTES            │\n");
                printf("│                    ATIVOS                    │\n");     
                break;

            case '3': // EXCLUÍDOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DOS CLIENTES            │\n");
                printf("│                   EXCLUÍDOS                  │\n");
                break;
        }

}

void relatorioCliente(const char op){
    int cont = 0;
    Cliente *c;
    c = (Cliente*) malloc(sizeof(Cliente));
    FILE *cli;
    

    cli = fopen("clientes.dat","rb");
    if(cli == NULL){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│      Não existem clientes cadastrados.       │\n");
        free(c);
        return cont;
    }

    while (fread(c, sizeof(Cliente), 1, cli)) {
        int deveImprimir = 0; // controle de filtragem

        switch(op) {
            case '1': // TODOS
                deveImprimir = 1;
                break;

            case '2': // ATIVOS
                if (c->status == True){
                    deveImprimir = 1;
                }
                break;

            case '3': // EXCLUIDOS
                if (c->status == False){
                    deveImprimir = 1;
                }
                break;
        }

        if (deveImprimir) {
            printRelatCliente(c);
            cont +=1;
        }
    }
    fclose(cli);
    free(c);

    if(cont < 1){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│      Não existem clientes com o filtro       │\n");
        printf("│                  escolhido.                  │\n");
        
    }

    printf("╰──────────────────────────────────────────────╯\n");

    esperarEnter();

}


////////////////////////////////////////////////////////////////FUNCIONARIOS////////////////////////////////////////////////////////////////////////////


char modRelatorioFuncionario(void){
    char op;
    do {
        op = menuRelatorioFuncionario();
        switch(op) {
            case '1':
                cabecarioRelatorioFuncionario(op);
                relatorioFuncionario(op);
                break;
            case '2':
                cabecarioRelatorioFuncionario(op);
                relatorioFuncionario(op);
                break;
            case '3':
                cabecarioRelatorioFuncionario(op);
                relatorioFuncionario(op);
                break;
            case '0':
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while(op != '0'); // continua até o usuário escolher sair

    return op;

}

char menuRelatorioFuncionario(void){
    char op;
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│          RELATÓRIOS DOS FUNCIONARIOS         │\n");
    printf("├──────────────────────────────────────────────┤\n");
    printf("│  [1] TODOS                                   │\n");
    printf("│  [2] ATIVOS                                  │\n");
    printf("│  [3] EXCLUÍDOS                               │\n"); 
    printf("│  [0] SAIR                                    │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    op = opcao();
    return op;
}

void printRelatFuncionario(Funcionario *f){
    printf("├──────────────────────────────────────────────┤\n");
    printf("│ Nome: %-38s │\n", f->nome);
    printf("│ CPF: %-39s │\n", f->cpf);
    printf("│ Data: %.2s/%.2s/%.4s                             │\n", f->nascimento, f->nascimento + 2, f->nascimento + 4);
    printf("│ Telefone: (%.2s) %.1s %.4s-%.4s                   │\n",  f->telefone, f->telefone + 2,  f->telefone + 3, f->telefone + 7);
    printf("│ E-mail: %-36s │\n", f->email);
    printf("│ Salário: R$%-33.2f │\n", f->salario);
}


void cabecarioRelatorioFuncionario(const char op){
    switch(op) {

            case '1': // TODOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│            RELATÓRIO DE TODOS OS             │\n");
                printf("│                 FUNCIONÁRIOS                 │\n");
                break;

            case '2': // ATIVOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS FUNCIONÁRIOS          │\n");
                printf("│                    ATIVOS                    │\n");     
                break;

            case '3': // EXCLUÍDOS
                printf("╭──────────────────────────────────────────────╮\n");
                printf("│          RELATÓRIO DOS FUNCIONÁRIOS          │\n");
                printf("│                   EXCLUÍDOS                  │\n");
                break;
        }

}

void relatorioFuncionario(const char op){
    int cont = 0;
    Funcionario *f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;
    

    fun = fopen("FUNCIONARIOS.dat","rb");
    if(fun == NULL){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│    Não existem funcionários cadastrados.     │\n");
        free(f);
        return cont;
    }

    while (fread(f, sizeof(Funcionario), 1, fun)) {
        int deveImprimir = 0; // controle de filtragem

        switch(op) {
            case '1': // TODOS
                deveImprimir = 1;
                break;

            case '2': // ATIVOS
                if (f->status == True){
                    deveImprimir = 1;
                }
                break;

            case '3': // EXCLUIDOS
                if (f->status == False){
                    deveImprimir = 1;
                }
                break;
        }

        if (deveImprimir) {
            printRelatFuncionario(f);
            cont +=1;
        }
    }
    fclose(fun);
    free(f);

    if(cont < 1){
        printf("├──────────────────────────────────────────────┤\n");
        printf("│    Não existem funcionários com o filtro     │\n");
        printf("│                  escolhido.                  │\n");
        
    }

    printf("╰──────────────────────────────────────────────╯\n");

    esperarEnter();

}