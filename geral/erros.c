#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "cores.h"
#include "erros.h"
#include "ler_dados.h" 

void opcaoInvalida(void){
    printf("Opção inválida! Tente novamente.\n");
    esperarEnter();
    return;
}

void dadosInvalidos(void){
    printf("Dado inválido! Tente novamente.\n");
    esperarEnter();
    return;
}

void arqInexistente(void){
    printf("Ocorreu algun erro, o arquivo não pode ser aberto.\n");
}