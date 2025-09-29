#include <ctype.h>
#include <stdio.h>
#include <string.h>


void limpaCPF(char *cpf){
    int j = 0;
    for(int i = 0; cpf[i] != '\0'; i += 1){
        if(isdigit((unsigned char)cpf[i])){
            cpf[j] = cpf[i];
            j += 1;
        }
    }
    cpf[j] = '\0';//necessário para encerrar a string, se não fica erraaaaaaaaaaaaaaaaaaaaaaaaadooooooooooooooooooooooooo
}



void limpaNome(char *nome){
    int tam;
    int inicio = 0;
    for(int i = 0; nome[i] ==' '; i +=1){
        inicio += 1;
    }
    if(inicio != 0){
        for(int j = 0; nome[j] != '\0'; j += 1){
            nome[j] = nome[inicio];
            inicio += 1;
        }
    }
    tam = strlen(nome);
    for(int k = tam-1; nome[k] == ' '; k -= 1){
        nome[k] = '\0';
    }

}

void limpaFgets(char *str){
    int tam = strlen(str);
    str[tam-1] = '\0';
}