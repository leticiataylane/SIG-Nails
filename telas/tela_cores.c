#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tela_cores.h"

//cores ANSI
#define reset   "\033[0m"
#define normal  "\033[22m"
#define negrito    "\033[1m"
#define vermelho     "\033[31m"
#define salmao    "\033[38;5;209m"
#define pessego   "\033[38;5;216m"
#define amarelo  "\033[33m"
#define verde   "\033[32m"
#define menta     "\033[38;5;121m"
#define ciano     "\033[1;36m"
#define turquesa  "\033[38;5;45m"
#define azul    "\033[34m"
#define roxo  "\033[1;35m"
#define lilas     "\033[38;5;183m"
#define rosa     "\033[38;5;213m"
#define prata       "\033[38;5;250m"
// #define dourado     "\033[38;5;220m"
// #define pinkShock   "\033[38;5;199m"
// #define azulRoyal   "\033[38;5;21m"
// #define vinho       "\033[38;5;125m"
// #define vinho1   "\033[38;5;88m"   
// #define vinho2   "\033[38;5;89m"   
// #define vinho3   "\033[38;5;90m"   
// #define vinho4   "\033[38;5;125m"  
// #define vinho5   "\033[38;5;52m"   

void cores(void) {
    system("clear");
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(roxo "★"rosa negrito"           CORES DISPONÍVEIS               "roxo"★ \n"reset);
    printf(roxo negrito "✿ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ★ ✿\n"reset);
    printf(ciano negrito "OBS.:" normal" As cores abaixo são apenas ilustrativas, você encontra muito mais variedades no nosso espaço!\n\n" reset);
    printf(vermelho"✿"reset" Vermelho        "turquesa"✿"reset" Turquesa\n"reset);
    printf(salmao"✿"reset" Salmão          "azul"✿"reset" Azul\n"reset);
    printf(pessego"✿"reset" Pêssego         "roxo"✿"reset" Roxo\n"reset);
    printf(amarelo"✿"reset" Amarelo         "lilas"✿"reset" Lilás\n"reset);
    printf(verde"✿"reset" Verde           "rosa"✿"reset" Rosa\n"reset);
    printf(menta"✿"reset" Menta           "prata"✿"reset" Prata\n"reset);

    printf(rosa negrito "\nPressione ENTER para continuar...\n"reset);
    getchar();
    
}

// int main() {
//     cores();
//     return 0;
// }