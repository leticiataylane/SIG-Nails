#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
// #include "cores.h"
#include "limpeza.h"
#include "validacoes.h"
#include "opera_agendamento.h"



int gerarIdAgendamento(void) {
    FILE *arq;
    int qtd = 0;

    arq = fopen("agendamentos.dat", "rb");
    if (arq != NULL) {
        fseek(arq, 0, SEEK_END); // vai pro final do arquivo
        long tamanho = ftell(arq); // pega o tamanho em bytes
        qtd = tamanho / sizeof(Agendamento); // calcula quantos registros tem
        fclose(arq);
    }

    // Se não existir arquivo ainda, qtd será 0
    // O próximo ID será qtd + 1
    return qtd + 1;
}




int cadastrarAgendamento(void){
    int contErro = 0;
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));

    FILE *agen;

    do{
        //listarClientes();
        printf("Insira o ID do cliente:\n");
        scanf("%d", a->clienteID);
        getchar();
        if(!pesquisarClienteID(a->clienteID)){
            system("clear");
            printf("Ocorreu algum erro, o ID que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(a);
                    return 1;
                }
            }
        }
    }while(!pesquisarClienteID(a->clienteID));

    contErro = 0;

    do{
        //listarServicos();
        printf("Insira o ID do serviço:\n");
        scanf("%d", a->servicoID);
        getchar();
        if(!pesquisarServicoID(a->servicoID)){
            system("clear");
            printf("Ocorreu algum erro, o ID que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(a);
                    return 1;
                }
            }
        }
    }while(!pesquisarServicoID(a->servicoID));

    contErro = 0;

    do{
        printf("Insira a data do agendamento:\n");
        fgets(a->data, 20, stdin);
        limpaFgets(a->data);
        if(!validaDataInserida(a->data)){
            system("clear");
            printf("Ocorreu algum erro, a data que você digitou é inválida.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(a);
                    return 1;
                }
            }
        }        
    }while(!validaDataInserida(a->data));
    
    contErro = 0;

    do{
        printf("Insira o horário do agendamento:\n");
        fgets(a->hora, 10, stdin);
        limpaFgets(a->hora);
        if(!validaHora(a->hora)){
            system("clear");
            printf("Ocorreu algum erro, o horário que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(a);
                    return 1;
                }
            }
        }
    }while(!validaHora(a->hora));

    /////// Adicionar também o cpf do funcionario escolhido para o serviço??

    // strcpy(a->situacao, "Pendente");
    a->agendamentoID = gerarIdAgendamento;
    a->status = True;

    FILE *agen = fopen("agendamentos.dat", "ab");
    if (agen == NULL) {
        perror("Erro ao abrir o arquivo");
        free(a);
        return 1;
    }
    fwrite(a, sizeof(Agendamento), 1, agen);
    fclose(agen);
    free(a);
    printf("\nDados salvos com sucesso em agendamentos.dat!\n");

    return 0;
}


int atualizarAgendamento(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    int encontrado = False;
    int qualAgendamento;
    char oqAlterar;


    //listarAgendamentos();
    scanf("%d", &qualAgendamento);
    getchar();


    FILE *agen;

    FILE *agen = fopen("agendamentos.dat", "r+b");
    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){
        if((qualAgendamento == a->agendamentoID) && (a->status)){
            do{
                oqAlterar = telaOqAlterar();
                switch (oqAlterar)
                {
                case '1':
                    do{
                        //listarServicos();
                        printf("Insira o ID do serviço:\n");
                        scanf("%d", a->servicoID);
                        getchar();
                        if(!pesquisarServicoID(a->servicoID)){
                            system("clear");
                            printf("Ocorreu algum erro, o ID que você digitou é inválido.\n");
                        }
                    }while(!pesquisarServicoID(a->servicoID));
                    break;
                
                case '2':
                    do{
                        printf("Insira a data do agendamento:\n");
                        fgets(a->data, 20, stdin);
                        limpaFgets(a->data);
                        if(!validaDataInserida(a->data)){
                            system("clear");
                            printf("Ocorreu algum erro, a data que você digitou é inválida.\n");
                        }        
                    }while(!validaDataInserida(a->data));
                    break;

                case '3':
                    do{
                        printf("Insira o horário do agendamento:\n");
                        fgets(a->hora, 10, stdin);
                        limpaFgets(a->hora);
                        if(!validaHora(a->hora)){
                            system("clear");
                            printf("Ocorreu algum erro, o horário que você digitou é inválido.\n");
                        }
                    }while(!validaHora(a->hora));
                    break;
                //case '4':
                    //alterar o  funcionario
                    //break;

                default:
                    opInvalida();
                    break;
                }
            }while(oqAlterar != '1' && oqAlterar != '2' && oqAlterar != '3');
            fseek(agen, (-1)*sizeof(Agendamento), SEEK_CUR);
            fwrite(agen, sizeof(Agendamento), 1, agen);
            encontrado = True;
        } else if ((qualAgendamento == a->agendamentoID) && (!a->status)){
            printf("Agendamento foi excluído");
            encontrado = True;
        }
    }
    fclose(agen);
    free(a);
    if(!encontrado){
        printf("Nao encontrado");
    }
    return 0;
}

int pesquisarAgendamento(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    int encontrado = False;
    int qual;


    printf("Digite o CPF de que funcionário você deseja excluir o vínculo:\n");
    scanf("%d", &qual);
    getchar();


    agen = fopen("agendamentos.dat","rb");
    if (agen == NULL) {
    printf("Erro ao abrir o arquivo de funcionários.\n");
    free(a);
    return False;
    }

    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){
        if((qual == a->agendamentoID) && (a->status)){
            printf("NOME DO CLIENTE: %s\nDATA: %s\nHORA: %s\nSERVICO: %s\n", a->clienteID, a->data, a->hora, a->servicoID);
            encontrado = True;
        } else if((qual == a->agendamentoID) && (!a->status)){
            printf("AGENDAMENTO excluido\n");
            encontrado = True;
        }
    }
    fclose(agen);
    free(a);
    if(!encontrado){
        printf("Não encontrado");
        return False;
    }

    return 0;
}




int listarAgendamentos(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    agen = fopen("agendamentos.dat","rb");

    while(fread(a, sizeof(Agendamento), 1, agen)){
        if(a->status){
            printf("NOME DO CLIENTE: %s\nDATA: %s\nHORA: %s\nSERVICO: %s\n", a->clienteID, a->data, a->hora, a->servicoID);
        }
    }
    fclose(agen);
    free(a);
    return 0;
}

int excluirAgendamento(void){
    Agendamento* a;
    a = (Agendamento*) malloc(sizeof(Agendamento));
    FILE *agen;

    int encontrado = False;
    int qual;


    printf("qual agendamento:\n");
    scanf("%d", &qual);
    getchar();


    agen = fopen("agendamentos.dat","r+b");

    while((fread(a, sizeof(Agendamento), 1, agen)) && (!encontrado)){
        if((qual == a->agendamentoID) && (a->status)){
            printf("NOME DO CLIENTE: %s\nDATA: %s\nHORA: %s\nSERVICO: %s\n", a->clienteID, a->data, a->hora, a->servicoID);
            a->status = False;
            fseek(agen, (-1)*sizeof(Agendamento), SEEK_CUR);
            fwrite(agen, sizeof(Agendamento), 1, agen);
            encontrado = True;

        } else if((qual == a->agendamentoID) && (!a->status)){
            printf("Não encontrado");
            encontrado = True;
        }
    }
    fclose(agen);
    free(a);
    if(!encontrado){
        printf("Não encontrado");
    }

    return 0;

}