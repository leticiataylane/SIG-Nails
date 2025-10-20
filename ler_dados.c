#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
#include "ler_dados.h"
#include "limpeza.h"
#include "validacoes.h"

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
    char *nome;
    do{
        nome = lerString("Digite o nome:\n");
        limpaNome(nome);
        if(!validaNome(nome)){
            erroInvalido();
            free(nome);
        }
    }while(!validaNome(nome));

    return nome;
}

char* lerCPF(void){
    char *cpf;
    do{
        cpf = lerString("Digite o CPF:\n");
        limpaCPF(cpf);
        if(!validaCPF(cpf)){
            erroInvalido();
            free(cpf);
        }
    }while(!validaCPF(cpf));
    return cpf;
}

char* lerNascimento(void){
    char *nascimento;
    do{
        nascimento = lerString("Digite a data de nascimento:\n");
        if(!validaNascimento(nascimento)){
            erroInvalido();
            free(nascimento);
        }
    }while(!validaNascimento(nascimento));
    
    return nascimento;
}

char* lerIdade(void){
    char *nascimento;
    do{
        nascimento = lerNascimento();
        if(!validaIdade(nascimento)){
            system("clear");
            printf("Idade invalida para contratação. Aceitamos novos funcionários de 18 a 66 anos de idade.\n");
            free(nascimento);
        }
    }while(!validaIdade(nascimento));

    return nascimento;
    
}

char* lerData(void){
    char *data;
    do{
        data = lerString("Digite a data de nascimento:\n");
        if(!validaDataInserida(data)){
            erroInvalido();
            free(data);
        }
    }while(!validaDataInserida(data));
    
    return data;

}

char* lerTelefone(void){
    char *telefone;
    do{
        telefone = lerString("Digite o número de telefone:\n");
        if(!validaTelefone(telefone)){
            erroInvalido();
            free(telefone);
        }
    }while(!validaTelefone(telefone));

    return telefone;
}

char* lerEmail(void){
    char *email;
    do{
        email = lerString("Digite o email:\n");
        if(!validaEmail(email)){
            erroInvalido();
            free(email);
        }
    }while(!validaEmail(email));

    return email;
}

float lerDinheiro(void){
    char *dinheiroChar;
    float dinheiro = 0;
    int j = 0;
    
    dinheiroChar = lerString("Digite o valor:\n");
    for(int i = 0; dinheiroChar[i] != '\0'; i += 1){
        if(isdigit((unsigned char)dinheiroChar[i])){
            dinheiroChar[j] = dinheiroChar[i];
            j += 1;
        }
    }
    dinheiroChar[j] = '\0';

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

// int lerId(void){
//     char* idChar;
//     int id;
//     int j;
//     do{
//         idChar = lerString("Digite o número do ID:");
//         for(int i = 0; idChar[i] != '\0'; i += 1){
//             if(isdigit((unsigned char)idChar[i])){
//                 idChar[j] = idChar[i];
//                 j += 1;
//             }
//     }
//     }while(!idEncontrado);

// }

