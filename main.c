#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include "cores.h"
#include "telas_gerais.h"
#include "clientes.h"
#include "servicos.h"
#include "agendamentos.h"
#include "funcionarios.h"
#include "relatorios.h"
#include "erros.h"
 
int main(void) {
    char op;

    telaInicial();
    do {
        op = menuPrincipal();
        switch(op) {
            case '1':
                modAgendamento();
                break;
            case '2':
                modServico();
                break;
            case '3':
                modCliente();
                break;
            case '4':
                modFuncionario();
                break;
            case '5':
                telaSobre();
                telaAjuda();
                break;
            case '6':
                modRelatorios();
            case '0':
                telaFinal();
                break;
            default:
                opcaoInvalida();
                break;
        }
    } while(op != '0'); // continua até o usuário escolher sair

    return 0;

}