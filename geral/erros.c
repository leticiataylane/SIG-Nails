#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "cores.h"
#include "erros.h"
#include "ler_dados.h" 

void opcaoInvalida(void){
    printf("Opção inválida! Tente novamente.\n");
    esperarEnter();
}

void dadosInvalidos(void){
    printf("Dado inválido! Tente novamente.\n");
    esperarEnter();
}

void arqInexistente(void){
    printf("Ocorreu algun erro, o arquivo não pode ser aberto.\n");
}

void semResulFiltro(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│     Não existem resultados no filtro         │\n");
    printf("│                  escolhido.                  │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();
}

void naoHaCadastro(void){
    printf("╭──────────────────────────────────────────────╮\n");
    printf("│       Não existem dados cadastrados.         │\n");
    printf("╰──────────────────────────────────────────────╯\n");
    esperarEnter();
}