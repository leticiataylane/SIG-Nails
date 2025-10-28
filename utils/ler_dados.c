#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "ler_dados.h"
#include "limpeza.h"
#include "validacoes.h"
#include "erros.h"
#include "agendamentos.h"
#include "telas_servicos.h"
#include "telas_clientes.h"


void esperarEnter() {
    printf("\nPressione ENTER para continuar...");
    while (getchar() != '\n'); // espera apenas o ENTER
}

char opcao(void){
    char *escolha = lerString("Digite apenas o número:");
    char op = escolha[0];
    free(escolha);
    return op;
}

char* lerString(const char* msg){
    char linha[256] = "";
    char *str;
    int tam = 0;

    printf("%s", msg);
    fgets(linha, 256, stdin);
    limpaFgets(linha);

    tam = strlen(linha);
    str = (char*) malloc(tam + 1);
    if(str == NULL){
        printf("Erro ao alocar memória.");
        exit(1);
    }
    strcpy(str, linha);
    return str;
}

char* lerNome(void){
    char *nome = NULL;
    int valido = 0;
    do{
        nome = lerString("Digite o nome:\n");
        limpaNome(nome);
        valido = validaNome(nome);
        if(!valido){
            dadosInvalidos();
            free(nome);
        }
    }while(!valido);

    return nome;
}

char* lerCPF(void){
    char *cpf = NULL;
    int valido = 0;

    do {
        cpf = lerString("Digite o CPF:\n");
        limpaNum(cpf);
        valido = validaCPF(cpf);

        if (!valido) {
            dadosInvalidos();
            free(cpf);
        }
    } while (!valido);

    return cpf;
}

char* lerNascimento(void){
    char *nascimento = NULL;
    int valido = 0;
    do{
        nascimento = lerString("Digite a data de nascimento:\n");
        valido = validaNascimento(nascimento);
        if(!valido){
            dadosInvalidos();
            free(nascimento);
        }
    }while(!valido);
    
    return nascimento;
}

char* lerIdade(void){
    char *nascimento = NULL;
    int valido = 0;
    do{
        nascimento = lerNascimento();
        valido = validaIdade(nascimento);
        if(!valido){
            printf("Idade invalida para contratação. Aceitamos novos funcionários de 18 a 66 anos de idade.\n");
            free(nascimento);
        }
    }while(!valido);

    return nascimento;
    
}

char* lerData(void){
    char *data = NULL;
    int valido = 0;
    do{
        data = lerString("Digite a data:\n");
        valido = validaDataInserida(data);
        if(!valido){
            dadosInvalidos();
            free(data);
        }
    }while(!valido);
    
    return data;

}

char* lerHorario(void){
    char *horario = NULL;
    int valido = 0;
    do{
        horario = lerString("Digite o horário:");
        valido = validaHorario(horario);
        if(!valido){
            dadosInvalidos();
            free(horario);
        }
    }while(!valido);

    return horario;
}

char* lerTelefone(void){
    char *telefone = NULL;
    int valido = 0;
    do{
        telefone = lerString("Digite o número de telefone:\n");
        valido = validaTelefone(telefone);
        if(!valido){
            dadosInvalidos();
            free(telefone);
        }
    }while(!valido);

    return telefone;
}

char* lerEmail(void){
    char *email = NULL;
    int valido = 0;
    do{
        email = lerString("Digite o email:\n");
        valido = validaEmail(email);
        if(!valido){
            dadosInvalidos();
            free(email);
        }
    }while(!valido);

    return email;
}

float lerDinheiro(void){
    char *dinheiroChar = NULL;
    float dinheiro = 0;

    
    dinheiroChar = lerString("Digite o valor:\n");
    limpaNum(dinheiroChar);

    dinheiro = atof(dinheiroChar);
    free(dinheiroChar);
    return dinheiro;
}

float lerSalario(void){
    float salario = 0;
    int salarioValido = False;
    do{
        salario = lerDinheiro();
        if(salario >= 1518){
            salarioValido = True;
        }else{
            printf("valor insuficiente. Tente novamente:\n");
        }
    }while(!salarioValido);
    return salario;  
}

char* lerIdAgendamento(void){
    char* idChar = NULL;
    int valido = 0;

    do{
        idChar = lerString("Digite o número do ID:");
        limpaNum(idChar);
        valido = idExisteAgendamento(idChar);
        if(!valido){
            dadosInvalidos();
            free(idChar);
        }
    }while(!valido);
    return idChar;
}


char* lerIdServico(void){
    char* idChar = NULL;
    int valido = 0;

    do{
        idChar = lerString("Digite o número do ID:");
        limpaNum(idChar);
        valido = idExisteServico(idChar);
        if(!valido){
            dadosInvalidos();
            free(idChar);
        }
    }while(!valido);
    return idChar;
}


char* lerIdCliente(void){
    char* idChar = NULL;
    int valido = 0;

    do{
        idChar = lerString("Digite o número do ID:");
        limpaNum(idChar);
        valido = idExisteCliente(idChar);
        if(!valido){
            dadosInvalidos();
            free(idChar);
        }
    }while(!valido);
    return idChar;
}


char* lerSituacao(const char* horario, const char* data, const char* situacao) {
    char *novaSituacao = NULL;
    char op;
    int valido = 0;

    op = telaSituacao();  // mostra opções (1 - Concluído, 2 - Cancelado, etc.)
    valido = validaSituacao(horario, data, situacao, op);

    if (valido) {
        switch (op) {
            case '1':
                strcpy(novaSituacao, "Concluído");
                break;
            case '2':
                strcpy(novaSituacao, "Cancelado");
                break;
            default:
                opcaoInvalida();
                break;
        }
    }
    return novaSituacao;
}
