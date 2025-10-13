#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> 
#include <ctype.h> 
// #include "cores.h"
#include "limpeza.h"
#include "validacoes.h"
#include "opera_funcionarios.h"


int cadastrarFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    int contErro = 0;
    char opTurno;
    char salarioValido = 'n';

    do{
        printf("Insira o nome do funcionário:\n");
        fgets(f->nome, 60, stdin);
        limpaFgets(f->nome);
        limpaNome(f->nome);
        if(!validaNome(f->nome)){
            system("clear");
            printf("Ocorreu algum erro, o nome que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(f);
                    return 1;
                }
            }
        }
    }while(!validaNome(f->nome));

    contErro = 0;

    do{
        printf("Insira o CPF do funcionário:\n");
        fgets(f->cpf, 20, stdin);
        limpaFgets(f->cpf);
        limpaCPF(f->cpf);
        if(!validaCPF(f->cpf)){
            system("clear");
            printf("Ocorreu algum erro, o CPF que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(f);
                    return 1;
                }
            }
        }
    }while(!validaCPF(f->cpf));

    contErro = 0;

    do{
        printf("Insira a data de nascimento do funcionário:\n");
        fgets(f->nascimento, 20, stdin);
        limpaFgets(f->nascimento);
        if(!validaNascimento(f->nascimento)){
            system("clear");
            printf("Ocorreu algum erro, a data que você digitou é inválida.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(f);
                    return 1;
                }
            }

        contErro = 0;

        } else if (!validaIdade(f->nascimento)){
            system("clear");
            printf("Idade invalida para contratação. Aceitamos novos funcionários de 18 a 66 anos de idade.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(f);
                    return 1;
                }
            }
        }
    }while(!validaNascimento(f->nascimento) || !validaIdade(f->nascimento));

    do{
        printf("Insira o telefone do funcionário:\n");
        fgets(f->telefone, 20, stdin);
        limpaFgets(f->telefone);
        if(!validaTelefone(f->telefone)){
            system("clear");
            printf("Ocorreu algum erro, o telefone que você digitou é inválido.\n");
            contErro += 1;
            if (contErro >= 3){
                if(!tenteNovamente()){
                    free(f);
                    return 1;
                }
            }
        }
    }while(!validaTelefone(f->telefone));


    do{
        printf("Insira o email do funcionário:\n");
        fgets(f->email, 70, stdin);
        limpaFgets(f->email);
        if(!validaEmail(f->email)){
            system("clear");
            printf("Ocorreu algum erro, o email que você digitou é inválido.\n");
            contErro += 1;
                if (contErro >= 3){
                    if(!tenteNovamente()){
                        free(f);
                        return 1;
                }
            }
        }
    }while(!validaEmail(f->email));


    do{
        opTurno = telaTurnoFuncionario();
        printf("Digite o salário do funcionário:\n");
        scanf("%f", &f->salario);
        getchar();

        switch(opTurno){
            case '1':
                if (f->salario >= 1518){
                    salarioValido = 's';
                    strcpy(f->turno, "Completo");//copia a string para a variavel
                }else{
                    printf("Atenção, o turno de trabalho escolhido foi o período completo.\n");
                    printf("O salário do funcionário deve ser maior ou igual a um salário mínimo. (R$ 1.518)\n");
                }
                break;
            case '2':
                if (f->salario >= 759){
                    salarioValido = 's';
                    strcpy(f->turno, "Manhã");//copia a string para a variavel

                }else{
                    printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                    printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                }
                break;
            case '3':
                if (f->salario >= 759){
                    salarioValido = 's';
                    strcpy(f->turno, "Tarde");//copia a string para a variavel
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

    f->status = True;

    FILE *fp = fopen("funcionarios.dat", "ab");
    if (fp == NULL) {
        perror("Erro ao abrir o arquivo");
        free(f);
        return 1;
    }
    fwrite(f, sizeof(Funcionario), 1, fp);
    fclose(fp);
    free(f);
    printf("\nDados salvos com sucesso em funcionarios.dat!\n");

    return 0;

}


int atualizarFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    int encontrado = False;

    int contErro = 0;
    char quemAtualizar[20];
    char oqAtualizar;
    char opTurno;
    char salarioValido = 'n';

    FILE *fun;

    printf("Digite o CPF de que funcionário você deseja atualizar os dados:\n");
    fgets(quemAtualizar, 20, stdin);
    limpaFgets(quemAtualizar);
    limpaCPF(quemAtualizar);

    oqAtualizar = telaOqueAtualizar();

    fun = fopen("funcionarios.dat","r+b");
    while((fread(f, sizeof(Funcionario), 1, fun)) && (!encontrado)){
        if((strcmp(quemAtualizar, f->cpf) == 0) && (f->status)){
            switch(oqAtualizar){
                case '1':
                    contErro = 0;
                    do{
                        printf("Insira o novo nome do funcionário:\n");
                        fgets(f->nome, 60, stdin);
                        limpaFgets(f->nome);
                        limpaNome(f->nome);
                        if(!validaNome(f->nome)){
                            system("clear");
                            printf("Ocorreu algum erro, o nome que você digitou é inválido.\n");
                            contErro += 1;
                            if (contErro >= 3){
                                if(!tenteNovamente()){
                                    fclose(fun);
                                    free(f);
                                    return 1;
                                }
                            }
                        }
                    }while(!validaNome(f->nome));
                    break;

                case '2':
                    contErro = 0;
                    do{
                        printf("Insira o novo telefone do funcionário:\n");
                        fgets(f->telefone, 20, stdin);
                        limpaFgets(f->telefone);
                        if(!validaTelefone(f->telefone)){
                            system("clear");
                            printf("Ocorreu algum erro, o telefone que você digitou é inválido.\n");
                            contErro += 1;
                            if (contErro >= 3){
                                if(!tenteNovamente()){
                                    fclose(fun);
                                    free(f);
                                    return 1;
                                }
                            }
                        }
                    }while(!validaTelefone(f->telefone));
                    break;
                
                case '3':
                    contErro = 0;
                    do{
                        printf("Insira o email do funcionário:\n");
                        fgets(f->email, 70, stdin);
                        limpaFgets(f->email);
                        if(!validaEmail(f->email)){
                            system("clear");
                            printf("Ocorreu algum erro, o email que você digitou é inválido.\n");
                            contErro += 1;
                                if (contErro >= 3){
                                    if(!tenteNovamente()){
                                        fclose(fun);
                                        free(f);
                                        return 1;
                                }
                            }
                        }
                    }while(!validaEmail(f->email));
                    break;

                case '4':
                    contErro = 0;
                    do{
                        opTurno = telaTurnoFuncionario();
                        printf("Digite o salário do funcionário:\n");
                        scanf("%f", &f->salario);
                        getchar();

                        switch(opTurno){
                            case '1':
                            salarioValido = 'n';
                                if (f->salario >= 1518){
                                    strcpy(f->turno, "Completo");//copia a string para a variavel
                                    salarioValido = 's';
                                }else{
                                    printf("Atenção, o turno de trabalho escolhido foi o período completo.\n");
                                    printf("O salário do funcionário deve ser maior ou igual a um salário mínimo. (R$ 1.518)\n");
                                }
                                break;
                            case '2':
                            salarioValido = 'n';
                                if (f->salario >= 759){
                                    strcpy(f->turno, "Manhã");//copia a string para a variavel
                                    salarioValido = 's';

                                }else{
                                    printf("Atenção, o turno de trabalho escolhido foi meio-período.\n");
                                    printf("O salário do funcionário deve ser maior ou igual a meio salário mínimo. (R$ 759)\n");
                                }
                                break;
                            case '3':
                            salarioValido = 'n';
                                if (f->salario >= 759){
                                    strcpy(f->turno, "Tarde");//copia a string para a variavel
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
                    }while(salarioValido != 's');
                    break;


                default:
                    printf("invalido bobao\n");
                    break;
            }
            fseek(fun, (-1)*sizeof(Funcionario), SEEK_CUR);
            fwrite(fun, sizeof(Funcionario), 1, fun);
            encontrado = True;
        }
        if((strcmp(quemAtualizar, f->cpf) == 0) && (!f->status)){
            encontrado = True;
        }
    }
    fclose(fun);
    free(f);
    if(!encontrado){
        printf("Nao encontrado");
    }
    
    return 0;
}

int pesquisarFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;

    int encontrado = False;
    char quemPesquisar[20];


    printf("Digite o CPF de que funcionário você deseja excluir o vínculo:\n");
    fgets(quemPesquisar, 20, stdin);
    limpaFgets(quemPesquisar);
    limpaCPF(quemPesquisar);


    fun = fopen("funcionarios.dat","rb");
    if (fun == NULL) {
    printf("Erro ao abrir o arquivo de funcionários.\n");
    free(f);
    return False;
    }

    while((fread(f, sizeof(Funcionario), 1, fun)) && (!encontrado)){
        if((strcmp(quemPesquisar, f->cpf) == 0) && (f->status)){
            printf("NOME: %s\nCPF: %s\nDATA DE NASCIMENTO: %s\nTELEFONE: %s\nEMAIL: %s\nTURNO: %s\nSALARIO: %.2f\n", f->nome, f->cpf, f->nascimento, f->telefone, f->email, f->turno, f->salario);
            encontrado = True;
        } else if((strcmp(quemPesquisar, f->cpf) == 0) && (!f->status)){
            printf("Vinculo inativo, funcionario excluido\n");
            encontrado = True;
        }
    }
    fclose(fun);
    free(f);
    if(!encontrado){
        printf("Não encontrado");
        return False;
    }

    return 0;

}

int listarFuncionarios(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;

    fun = fopen("funcionarios.dat","rb");

    while(fread(f, sizeof(Funcionario), 1, fun)){
        if(f->status){
            printf("NOME: %s\nCPF: %s\nDATA DE NASCIMENTO: %s\nTELEFONE: %s\nEMAIL: %s\nTURNO: %s\nSALARIO: %.2f\n");
        }
    }
    fclose(fun);
    free(f);
    return 0;
}




int excluirFuncionario(void){
    Funcionario* f;
    f = (Funcionario*) malloc(sizeof(Funcionario));
    FILE *fun;

    int encontrado = False;
    char quemExcluir[20];


    printf("Digite o CPF de que funcionário você deseja excluir o vínculo:\n");
    fgets(quemExcluir, 20, stdin);
    limpaFgets(quemExcluir);
    limpaCPF(quemExcluir);


    fun = fopen("funcionarios.dat","r+b");

    while((fread(f, sizeof(Funcionario), 1, fun)) && (!encontrado)){
        if((strcmp(quemExcluir, f->cpf) == 0) && (f->status)){
            printf("NOME: %s\nCPF: %s\nDATA DE NASCIMENTO: %s\nTELEFONE: %s\nEMAIL: %s\nTURNO: %s\nSALARIO: %.2f\n");
            f->status = False;
            fseek(fun, (-1)*sizeof(Funcionario), SEEK_CUR);
            fwrite(fun, sizeof(Funcionario), 1, fun);
            encontrado = True;
        } else if((strcmp(quemExcluir, f->cpf) == 0) && (!f->status)){
            printf("Não encontrado");
            encontrado = True;
        }
    }
    fclose(fun);
    free(f);
    if(!encontrado){
        printf("Não encontrado");
    }

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


// int main(void){
//     cadsFuncionario();
//     return 0;
// }

