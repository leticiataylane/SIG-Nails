#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
// #include "cores.h"
#include "limpeza.h"
#include "validacoes.h"


int cadsFuncionario(void){
    char nome[60];
    char cpf[20];
    char nascimento[15];
    char telefone[20];
    char email[70];
    char situacao[10]; 
    char turno[10];
    char opTurno;
    char salarioValido = 'n';
    float salario = 0;


    


    do{
    printf("Insira o nome do funcionário:\n");
    fgets(nome, 60, stdin);
    limpaFgets(nome);
    limpaNome(nome);
    if(!validaNome(nome)){
        system("clear");
        printf("Ocorreu algum erro, o nome que você digitou é inválido.\n");
        if(!tenteNovamente()){
                return 1;
            }
        }
    }while(!validaNome(nome));

    do{
        printf("Insira o CPF do funcionário:\n");
        fgets(cpf, 20, stdin);
        limpaFgets(cpf);
        limpaCPF(cpf);
        if(!validaCPF(cpf)){
            system("clear");
            printf("Ocorreu algum erro, o CPF que você digitou é inválido.\n");
            if(!tenteNovamente()){
                return 1;
            }
        }
    }while(!validaCPF(cpf));

    do{
        printf("Insira a data de nascimento do funcionário:\n");
        fgets(nascimento, 20, stdin);
        limpaFgets(nascimento);
        if(!validaNascimento(nascimento)){
            system("clear");
            printf("Ocorreu algum erro, a data que você digitou é inválida.\n");
            if(!tenteNovamente()){
                return 1;
            }
        } else if (!validaIdade(nascimento)){
            system("clear");
            printf("Idade invalida para contratação. Aceitamos novos funcionários de 18 a 66 anos de idade.\n");
            if(!tenteNovamente()){
                return 1;
            }
        }
    }while(!validaNascimento(nascimento) || !validaIdade(nascimento));

    do{
    printf("Insira o telefone do funcionário:\n");
    fgets(telefone, 20, stdin);
    limpaFgets(telefone);
    if(!validaTelefone(telefone)){
        system("clear");
        printf("Ocorreu algum erro, o telefone que você digitou é inválido.\n");
        if(!tenteNovamente()){
                return 1;
            }
        }
    }while(!validaTelefone(telefone));


    do{
    printf("Insira o email do funcionário:\n");
    fgets(email, 70, stdin);
    limpaFgets(email);
    if(!validaEmail(email)){
        system("clear");
        printf("Ocorreu algum erro, o email que você digitou é inválido.\n");
        if(!tenteNovamente()){
                return 1;
            }
        }
    }while(!validaEmail(email));


    do{
        opTurno = telaTurnoFuncionario();
        printf("Digite o salário do funcionário:\n");
        scanf("%f", &salario);
        getchar();

        switch(opTurno){
            case '1':
                if (salario >= 1518){
                    salarioValido = 's';
                    strcpy(turno, "Completo");//copia a string para a variavel
                }else{
                    printf("Atenção, o turno de trabalho escolhido foi o período completo.\n");
                    printf("O salário do funcionário deve ser maior ou igual a um salário mínimo. (R$ 1.518)\n");
                }
                break;
            case '2':
                if (salario >= 759){
                    salarioValido = 's';
                    strcpy(turno, "Manhã");//copia a string para a variavel

                }else{
                    printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                    printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                }
                break;
            case '3':
                if (salario >= 759){
                    salarioValido = 's';
                    strcpy(turno, "Tarde");//copia a string para a variavel
                }else{
                    printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                    printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                }
                break;
            
            default:
                printf("Opção inválida. Tente novamente:\n");
                break;

        }
    }while(salarioValido != 's');

    strcpy(situacao, "Ativo");

    FILE *fp = fopen("funcionarios.csv", "a");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // escreve os dados separados por ;
    fprintf(fp, "%s;%s;%s;%s;%s;%s;%.2f;%s\n", 
            cpf,nome, nascimento, telefone, email, turno, salario, situacao);

    fclose(fp);
    printf("\nDados salvos com sucesso em funcionarios.csv!\n");

}



char telaTurnoFuncionario(void){
    char turno;
    printf("Qual período o funcionário irá trabalhar?\n");//tornar tela mais bonitinha
    printf("1. Completo (8h-20h)\n");
    printf("2. Meio-período manhã (8h-13h)\n");
    printf("3. Meio-período tarde (15h-20h)\n");
    printf("\nPor favor, digite apenas o número referente ao período de trabalho do funcionário:\n");
    scanf("%c", &turno);
    return turno;

}

int tenteNovamente(void){
    char tentar;
    printf("Deseja tentar novamente?(s/n)\n");
    printf("Em caso negativo a operação de cadastro será interrompida.\n");
    scanf("%c", &tentar);
    getchar();
    tentar = towlower(tentar);
    return (tentar == 's');

}


int main(void){
    cadsFuncionario();
    return 0;
}

