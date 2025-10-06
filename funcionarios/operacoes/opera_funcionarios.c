#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
// #include "cores.h"
#include "limpeza.h"
#include "validacoes.h"
#include "opera_funcionarios.h"


int cadsFuncionario(void){
    Funcionario f;
    int contErro = 0;
    char opTurno;
    char salarioValido = 'n';



    


    do{
    printf("Insira o nome do funcionário:\n");
    fgets(f.nome, 60, stdin);
    limpaFgets(f.nome);
    limpaNome(f.nome);
    if(!validaNome(f.nome)){
        system("clear");
        printf("Ocorreu algum erro, o nome que você digitou é inválido.\n");
        contErro += 1;
        if (contErro >= 3){
            if(!tenteNovamente()){
                return 1;
            }
        }
    }
    }while(!validaNome(f.nome));

    contErro = 0;

    do{
        printf("Insira o CPF do funcionário:\n");
        fgets(f.cpf, 20, stdin);
        limpaFgets(f.cpf);
        limpaCPF(f.cpf);
        if(!validaCPF(f.cpf)){
            system("clear");
            printf("Ocorreu algum erro, o CPF que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    return 1;
            }
        }
    }
    }while(!validaCPF(f.cpf));

    contErro = 0;

    do{
        printf("Insira a data de nascimento do funcionário:\n");
        fgets(f.nascimento, 20, stdin);
        limpaFgets(f.nascimento);
        if(!validaNascimento(f.nascimento)){
            system("clear");
            printf("Ocorreu algum erro, a data que você digitou é inválida.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    return 1;
            }
        }

        contErro = 0;

        } else if (!validaIdade(f.nascimento)){
            system("clear");
            printf("Idade invalida para contratação. Aceitamos novos funcionários de 18 a 66 anos de idade.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    return 1;
            }
        }
        }
    }while(!validaNascimento(f.nascimento) || !validaIdade(f.nascimento));

    do{
    printf("Insira o telefone do funcionário:\n");
    fgets(f.telefone, 20, stdin);
    limpaFgets(f.telefone);
    if(!validaTelefone(f.telefone)){
        system("clear");
        printf("Ocorreu algum erro, o telefone que você digitou é inválido.\n");
        contErro += 1;
        if (contErro >= 3){
            if(!tenteNovamente()){
                return 1;
            }
        }
    }
    }while(!validaTelefone(f.telefone));


    do{
    printf("Insira o email do funcionário:\n");
    fgets(f.email, 70, stdin);
    limpaFgets(f.email);
    if(!validaEmail(f.email)){
        system("clear");
        printf("Ocorreu algum erro, o email que você digitou é inválido.\n");
        contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    return 1;
            }
        }
    }
    }while(!validaEmail(f.email));


    do{
        opTurno = telaTurnoFuncionario();
        printf("Digite o salário do funcionário:\n");
        scanf("%f", &f.salario);
        getchar();

        switch(opTurno){
            case '1':
                if (f.salario >= 1518){
                    salarioValido = 's';
                    strcpy(f.turno, "Completo");//copia a string para a variavel
                }else{
                    printf("Atenção, o turno de trabalho escolhido foi o período completo.\n");
                    printf("O salário do funcionário deve ser maior ou igual a um salário mínimo. (R$ 1.518)\n");
                }
                break;
            case '2':
                if (f.salario >= 759){
                    salarioValido = 's';
                    strcpy(f.turno, "Manhã");//copia a string para a variavel

                }else{
                    printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                    printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                }
                break;
            case '3':
                if (f.salario >= 759){
                    salarioValido = 's';
                    strcpy(f.turno, "Tarde");//copia a string para a variavel
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

    strcpy(f.situacao, "Ativo");

    FILE *fp = fopen("funcionarios.csv", "at");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // escreve os dados separados por ;
    fprintf(fp, "%s;%s;%s;%s;%s;%s;%.2f;%s\n", 
            f.cpf,f.nome, f.nascimento, f.telefone, f.email, f.turno, f.salario, f.situacao);

    fclose(fp);
    printf("\nDados salvos com sucesso em funcionarios.csv!\n");

    return 0;

}


int atualizaFuncionario(void){
    Funcionario f;
    Funcionario N;


    int contErro = 0;
    char quemAtualizar[20];
    char oqAtualizar;
    char opTurno;
    char salarioValido = 'n';

    FILE *fun;
    FILE *funTemp;

    printf("Digite o CPF de que funcionário você deseja atualizar os dados:\n");
    fgets(quemAtualizar, 20, stdin);
    limpaFgets(quemAtualizar);
    limpaCPF(quemAtualizar);

    oqAtualizar = telaOqueAtualizar();

    fun = fopen("funcionarios.csv","rt");
    funTemp = fopen("funcionarios_temp.csv", "wt");
    while(fscanf(fun,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%[^\n]\n", f.cpf, f.nome, f.nascimento, f.telefone, f.email, f.turno, &f.salario, f.situacao) == 8){
        if(strcmp(quemAtualizar, f.cpf) != 0){
            fprintf(funTemp,"%s;%s;%s;%s;%s;%s;%.2f;%s\n", f.cpf, f.nome, f.nascimento, f.telefone, f.email, f.turno, f.salario, f.situacao);

        }else{
            if(strcmp(f.situacao, "Inativo") == 0){
                printf("Imposcsivel atualizar os dador de um funcionario inativo.");//criar tela de erro
                return 1;
            }

            switch(oqAtualizar){
                case '1':
                contErro = 0;
                    do{
                        printf("Insira o novo nome do funcionário:\n");
                        fgets(N.nome, 60, stdin);
                        limpaFgets(N.nome);
                        limpaNome(N.nome);
                        if(!validaNome(N.nome)){
                            system("clear");
                            printf("Ocorreu algum erro, o nome que você digitou é inválido.\n");
                            contErro += 1;
                            if (contErro >= 3){
                                if(!tenteNovamente()){
                                    fclose(fun);
                                    fclose(funTemp);
                                    remove("funcionarios_temp.csv");
                                    return 1;
                                }
                            }
                        }
                        strcpy(f.nome, N.nome);
                        }while(!validaNome(N.nome));
                        break;

                case '2':
                contErro = 0;
                    do{
                        printf("Insira o novo telefone do funcionário:\n");
                        fgets(N.telefone, 20, stdin);
                        limpaFgets(N.telefone);
                        if(!validaTelefone(N.telefone)){
                            system("clear");
                            printf("Ocorreu algum erro, o telefone que você digitou é inválido.\n");
                            contErro += 1;
                            if (contErro >= 3){
                                if(!tenteNovamente()){
                                    fclose(fun);
                                    fclose(funTemp);
                                    remove("funcionarios_temp.csv");
                                    return 1;
                                }
                            }
                        }
                        strcpy(f.telefone, N.telefone);
                        }while(!validaTelefone(N.telefone));
                        break;
                
                case '3':
                contErro = 0;
                        do{
                            printf("Insira o email do funcionário:\n");
                            fgets(N.email, 70, stdin);
                            limpaFgets(N.email);
                            if(!validaEmail(N.email)){
                                system("clear");
                                printf("Ocorreu algum erro, o email que você digitou é inválido.\n");
                                contErro += 1;
                                    if (contErro >= 3){
                                        if(!tenteNovamente()){
                                            fclose(fun);
                                            fclose(funTemp);
                                            remove("funcionarios_temp.csv");
                                            return 1;
                                    }
                                }
                            }
                            strcpy(f.email, N.email);

                            }while(!validaEmail(N.email));
                            break;

                case '4':
                contErro = 0;
                do{
                    opTurno = telaTurnoFuncionario();
                    printf("Digite o salário do funcionário:\n");
                    scanf("%f", &N.salario);
                    getchar();

                    switch(opTurno){
                        case '1':
                        salarioValido = 'n';
                            if (N.salario >= 1518){
                                strcpy(f.turno, "Completo");//copia a string para a variavel
                                salarioValido = 's';
                            }else{
                                printf("Atenção, o turno de trabalho escolhido foi o período completo.\n");
                                printf("O salário do funcionário deve ser maior ou igual a um salário mínimo. (R$ 1.518)\n");
                            }
                            break;
                        case '2':
                        salarioValido = 'n';
                            if (N.salario >= 759){
                                strcpy(f.turno, "Manhã");//copia a string para a variavel
                                salarioValido = 's';

                            }else{
                                printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                                printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                            }
                            break;
                        case '3':
                        salarioValido = 'n';
                            if (N.salario >= 759){
                                strcpy(f.turno, "Tarde");//copia a string para a variavel
                                salarioValido = 's';
                            }else{
                                printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                                printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                            }
                            break;
                        
                        default:
                            printf("Opção inválida. Tente novamente:\n");
                            break;

                    }

                    f.salario = N.salario;
                }while(salarioValido != 's');
                break;


                default:
                    printf("invalido bobao\n");
                    break;

            }
            fprintf(funTemp,"%s;%s;%s;%s;%s;%s;%.2f;%s\n", f.cpf, f.nome, f.nascimento, f.telefone, f.email, f.turno, f.salario, f.situacao);
            printf("certo\n");

        }

    }
    fclose(fun);
    fclose(funTemp);
    remove("funcionarios.csv");
    rename("funcionarios_temp.csv","funcionarios.csv");
    
    return 0;
}




int excluirFuncionario(void){
    FILE *fun;
    FILE *funTemp;
    char certeza;
    char quemExcluir[20];
    char nome[60];
    char cpf[20];
    char nascimento[15];
    char telefone[20];
    char email[70];
    char situacao[10]; 
    char turno[10];
    float salario = 0;

    printf("Digite o CPF de que funcionário você deseja excluir o vínculo:\n");
    fgets(quemExcluir, 20, stdin);
    limpaFgets(quemExcluir);
    limpaCPF(quemExcluir);


    fun = fopen("funcionarios.csv","rt");
    funTemp = fopen("funcionarios_temp.csv", "wt");

    while(fscanf(fun,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%f;%[^\n]\n", cpf, nome, nascimento, telefone, email, turno, &salario, situacao) == 8){
        if(strcmp(quemExcluir, cpf) != 0){
            fprintf(funTemp,"%s;%s;%s;%s;%s;%s;%.2f;%s\n", cpf, nome, nascimento, telefone, email, turno, salario, situacao);

        }else{
            printf("funcionario encontrado, tem certeza que deseja excluir o vínculo?\n");
            scanf("%c", &certeza);
            getchar();
            certeza = tolower(certeza);
            if (certeza != 's'){
                fclose(fun);
                fclose(funTemp);
                remove("funcionarios_temp.csv");
                return 1;
            } else{
                strcpy(situacao, "Inativo");
                fprintf(funTemp,"%s;%s;%s;%s;%s;%s;%.2f;%s\n", cpf, nome, nascimento, telefone, email, turno, salario, situacao);

            }


        }

    }
    fclose(fun);
    fclose(funTemp);
    remove("funcionarios.csv");
    rename("funcionarios_temp.csv","funcionarios.csv");

    return 0;

}





char telaOqueAtualizar(void){
    char oqAtualizar;
    printf("atualizar o que? 1.nome 2.telefone 3.email 4.turno e salario\n");
    scanf("%c", &oqAtualizar);
    return oqAtualizar;

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

int telaTenteNovamente(void){
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

