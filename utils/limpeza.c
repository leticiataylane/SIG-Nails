#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "limpeza.h"
#include "erros.h"


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

void limpaNum(char *num){
    int j =0;
    for(int i = 0; num[i] != '\0'; i +=1){
        if(isdigit((unsigned char)num[i])){
            num[j] = num[i];
            j +=1;
        }
    }
    num[j] = '\0';
}

void limpaEspacos(char *str) {
    int i = 0;
    while (str[i] == ' ') i++;

    if (i > 0) {
        memmove(str, str + i, strlen(str + i) + 1);
    }
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
}