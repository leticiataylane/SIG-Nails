#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

#define reset   "\033[0m"
#define negrito "\033[1m"
#define ciano   "\033[1;36m"
#define roxo    "\033[1;35m"
#define rosa    "\033[38;5;213m"
#define vermelho "\033[31m"

void telaInicial(char usuario[50]);
int menuPrincipal(void);
void telaSobre(void);
void telaAjuda(void);
void telaEditarAgendamento(void);
void telaComoAgendar(void);
void telaRemoverAgendamento(void);
void telaConfirmacao(void);
void telaPrecos(void);
void telaFinal();
void atendentes(void);
void cores(void);

#include "tela_inicial.c"
#include "tela_edição_remoção.c"
#include "tela_sobre.c"
#include "tela_atendentes.c"
#include "tela_cores.c"
#include "tela_ajuda.c"
#include "tela_final.c"

 
int main() {
    int opcao;
    char usuario[50];
    telaInicial(usuario);
    int editar_op;
    do {
        opcao = menuPrincipal();
        switch(opcao) {
            case 1:
                telaComoAgendar();
                telaPrecos();
                telaNovoAgendamento();
                printf(rosa negrito"✿ Deseja editar ou remover o agendamento?\n");
                printf(ciano"1"reset" - Editar\n");
                printf(ciano"2"reset" - Remover\n");
                scanf("%d", &editar_op);
                if (editar_op == 1){
                    telaEditarAgendamento();
                    telaConfirmacao();
                } else if (editar_op == 2){ 
                    telaRemoverAgendamento();
                }
                break;
            case 2:
                system("clear");
                printf(rosa"Pressione "negrito"ENTER"reset rosa", conheça nossa equipe e inspire-se com algumas cores!\n"reset);
                getchar();
                atendentes();
                cores();

                break;
            case 3:
                telaAjuda();
                telaSobre();
                break;
            case 4:
                telaFinal();
                break;
        }
    } while(opcao != 4); // continua até o usuário escolher sair

    return 0;

}