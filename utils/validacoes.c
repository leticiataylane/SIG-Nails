#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>  
#include "validacoes.h"
#include "limpeza.h"
#include "erros.h"

#define True 1
#define False 0


int validaDataInserida(char *dataInserida){
    limpaNum(dataInserida);

    time_t tempoAtual = time(NULL);        
    struct tm *dataAtual = localtime(&tempoAtual); 
  
    int anoA = dataAtual->tm_year + 1900;

    int tam = strlen(dataInserida);
    if(tam != 8){
        //mensagem de data de dataInserida incompleta, pedir para o usáario colocar no modelo 00/00/0000
        return False;
    }
    int diaI = ((dataInserida[0] - '0')*10 + (dataInserida[1] - '0'));
    int mesI = ((dataInserida[2] - '0')*10 + (dataInserida[3] - '0'));
    int anoI = ((dataInserida[4] - '0')*1000 + (dataInserida[5] - '0')*100 + (dataInserida[6] - '0')*10 + (dataInserida[7] - '0'));

    if(diaI > 31 || diaI < 1){
        return False;
    }
    if(mesI > 12 || mesI < 1){
        return False;
    }
    if(anoI < anoA || anoI > anoA + 2){
        return False;
    }
    
    if(mesI ==  4 || mesI == 6 || mesI == 9 || mesI == 11){
        if(diaI > 30){
            return False;
        }
    }
    if(mesI == 2){
        if(diaI > 29){
            return False;
        }
        if(diaI == 29){
            if(!((anoI % 4 == 0 && anoI %100 != 0) || (anoI % 400 == 0))){
                return False;
            }
        }
    }
    // Monta struct tm para calcular o dia da semana
    struct tm dataI = {0};//inicializa tudo com 0 porque pode conter lixo nos tipos de data não detalhada
    dataI.tm_mday = diaI;
    dataI.tm_mon  = mesI - 1;
    dataI.tm_year = anoI - 1900;

    mktime(&dataI);  // calcula tm de tudo

    // Rejeita sábado (6) ou domingo (0)
    if(dataI.tm_wday == 0 || dataI.tm_wday == 6){
        return False;//trabalha apenas de segunda a sexta
    }

return True;
}

int validaHorario(char *horario) {
    limpaNum(horario);
    char horaChar[3]; // 2 dígitos + '\0'
    char minChar[3];   // 2 dígitos + '\0'
    int h = 0;
    int m = 0;
    int tam = strlen(horario);

    if(tam != 4) return False;

    // copia os dois primeiros caracteres
    strncpy(horaChar, horario, 2);
    horaChar[2] = '\0'; // adiciona o terminador de string
    h = atoi(horaChar);

    // copia os dois últimos caracteres
    strncpy(minChar, horario + 2, 2);
    minChar[2] = '\0';
    m = atoi(minChar);


    if (h < 8 || h > 20) return False;  // horário de funcionamento
    if (h > 12 && h < 14) return False;
    if (m < 0 || m > 59) return False;

    return True;
}





int validaNascimento(char *nascimento){
    limpaNum(nascimento);

    time_t tempoAtual = time(NULL);        
    struct tm *dataAtual = localtime(&tempoAtual); 

    int anoA = dataAtual->tm_year + 1900;

    int tam = strlen(nascimento);
    if(tam != 8){
        //mensagem de data de nascimento incompleta, pedir para o usáario colocar no modelo 00/00/0000
        return False;
    }
    int diaN = ((nascimento[0] - '0')*10 + (nascimento[1] - '0'));
    int mesN = ((nascimento[2] - '0')*10 + (nascimento[3] - '0'));
    int anoN = ((nascimento[4] - '0')*1000 + (nascimento[5] - '0')*100 + (nascimento[6] - '0')*10 + (nascimento[7] - '0'));

    if(diaN > 31 || diaN < 1){
        return False;
    }
    if(mesN > 12 || mesN < 1){
        return False;
    }
    if(anoN > anoA || anoN < anoA - 100){
        return False;
    }
    
    if(mesN ==  4 || mesN == 6 || mesN == 9 || mesN == 11){
        if(diaN > 30){
            return False;
        }
    }
    if(mesN == 2){
        if(diaN > 29){
            return False;
        }
        if(diaN == 29){
            if(!((anoN % 4 == 0 && anoN %100 != 0) || (anoN % 400 == 0))){
                return False;
            }
        }
    }
return True;
}


int validaIdade(char *nascimento){
    limpaNum(nascimento);

    time_t tempoAtual = time(NULL);        
    struct tm *dataAtual = localtime(&tempoAtual); 

    int diaA = dataAtual->tm_mday;        
    int mesA = dataAtual->tm_mon + 1;     
    int anoA = dataAtual->tm_year + 1900;

    int diaN = ((nascimento[0] - '0')*10 + (nascimento[1] - '0'));
    int mesN = ((nascimento[2] - '0')*10 + (nascimento[3] - '0'));
    int anoN = ((nascimento[4] - '0')*1000 + (nascimento[5] - '0')*100 + (nascimento[6] - '0')*10 + (nascimento[7] - '0'));

    int idade = (anoA - anoN);
    if (mesN > mesA || (mesN == mesA && diaN > diaA)){
        idade -= 1;
    }

    if(idade < 18 || idade > 66){
        return False;
    }
    return True;
}



int validaCPF(char *cpf) {//código de validação feito por Flávia Carvalho
    int tam;
    int cont = 0;
    int soma = 0;
    int resto = 0;
    int verifica1 = 0;
    int verifica2 = 0;
    tam = strlen(cpf);
    if(tam != 11){
        return False;
    }
    for(int i = 0; i < 11; i +=1){
        if(cpf[0] == cpf[i]){
            cont += 1;
        }
    }
    if (cont >= 11){
        return False;
    }

    for(int i = 0; i<9; i +=1){
        soma += (cpf[i] - '0')*(10 - i);// pega o valor do código '0' e subtrai pelo valor do codigo de cpf[i]
    }

    resto = soma %11;

    if(resto<2){
        verifica1 = 0;
    }
    else if(resto>=2){
        verifica1 = 11 - resto;
    }

    if((cpf[9] - '0') != verifica1){
        return False;
    }

    soma = 0;
    resto = 0;

    for(int i = 0; i < 10; i += 1){
        soma += (cpf[i] - '0')*(11-i);
    }

    resto = soma%11;

    if(resto<2){
        verifica2 = 0;
    }
    else if(resto>=2){
        verifica2 = 11 - resto;
    }
    if(cpf[10] - '0' != verifica2){
        return False;
    }
    return True;

    }


int validaEmail(char *email){//validação feita por Flávia Carvalho
    int cont = 0;
    int cont2 = 0;
    int tam = 0;
    char letra;
    for(int i = 0; email[i] != '\0'; i += 1){
        if(email[i] == '@'){
            cont += 1;//conta quantos @ tem no email
            if(i == 0){
                return False;//se o @ estiver na posição inicial, retorna falso
            }
            if((!isalnum(email[i+1])) || (!isalnum(email[i-1]))){//se os caracteres imediatamente antes ou apos o @ não forem letra ou número, invalido
                return False;
            }
            for(int j = i; email[j] != '\0'; j +=1){
                if(email[j] == '.'){
                    cont2 += 1;
                }
            }
        }
        if(email[i] == '.' && email[i+1] == '.'){//se um ponto vier seguido de outro, retorna falso
                return False;
            }
        letra = email[i];
        if (!(isalnum(letra) || letra == '.' || letra == '-' || letra == '_' || letra == '@')){ //se o caracter não for nenhuma dessas alternativas, retorna falso
            return False;
        }
    }
    if(cont != 1){//se a contagem de @ for diferente de 1
        return False;
    }
    if(cont2 < 1){//se acontagem de . for menor que 1, retorna falso
        return False;
    }

    cont = 0;

    tam = strlen(email);//recebe o tamanho da string começando a contagem por 1
    if(!isalnum(email[tam - 1])){//se o caracter não for letra ou numero, invalido
        return False;
    }
    if(!isalnum(email[0])){//se o primeiro caracter não for letra ou número, invalido
        return False;
    }
    for(int j = tam-1; email[j] != '.'; j -= 1){//enquanto o caracter do email na posição j não for um . conta quantos caracteres tem
        cont +=1;
    }
    if(cont < 2){ //se for menor que 2, não aceita
        return False;
    }
    cont = 0;
    for(int k = 0; email[k] != '@'; k += 1){//na mesma ideia, só que conta o tamanho da parte local do email
        cont +=1;
    }
    if(cont < 3 || cont > 64){//se for menor que 3 ou maior que 64, invalido (minimo e maximo permitido que encontrei que algumas empresas permitem, Outlook/Hotmail por exemplo, varia 3 a 6 o minimo)
        return False;
    }
return True;
}



int validaNome(char *nome){
    const char *acentos = "áàâãéêíóôõúüçÁÀÂÃÉÊÍÓÔÕÚÜÇ";
    int cont = 0;
    int tam = strlen(nome);
    if(tam < 5){
        return False;
    }
    for(int i = 0; nome[i] != '\0'; i += 1 ){
        if((!(isalpha((unsigned char)nome[i])) && nome[i] != '\'' && nome[i] != '-' && nome[i] != ' ')){//testa se não é letra ou simbolo comum, para depois testar se é letra acentuada
            if(!(strchr(acentos, nome[i]))){
                return False;
            }
        }
        if(nome[i] == ' '){
            cont +=1;
        }
        if((nome[i] == ' ' && nome[i+1] == ' ') || (nome[i] == ' ' && nome[i+1] == '\'') || (nome[i] == ' ' && nome[i+1] == '-')){
            return False;
        }
        if((nome[i] == '\'' && nome[i+1] == ' ') || (nome[i] == '\'' && nome[i+1] == '\'') || (nome[i] == '\'' && nome[i+1] == '-')){
            return False;
        }
        if((nome[i] == '-' && nome[i+1] == ' ') || (nome[i] == '-' && nome[i+1] == '\'') || (nome[i] == '-' && nome[i+1] == '-')){
            return False;
        }
    }
    if(cont == 0){
            return False;
        }
    return True;
}

int validaNomeCurto(char *str) {
    if (str == NULL || strlen(str) < 2) {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; i++) {
        if (!isalpha(str[i]) && str[i] != ' ') {
            return 0;
        }
    }

    return 1;
}


int validaTelefone(char *telefone){
    limpaNum(telefone);

    int tam;
    int d1;
    tam = strlen(telefone);
    d1 = (telefone[0] - '0');
    if (tam == 11){
        if(d1 == 0){
            return False;
        }
        if(telefone[2]-'0' != 9){
            return False;
        }
        return True;
    }
    if(tam == 10){
        if((telefone[2] - '0') < 2){
            return False;
        }
        else if((telefone[2] - '0') > 5){
            return False;
        }
        return True;
    }
    return False;
}


int validaSituacao(const char* horario, const char* data, const char* situacao, const char op){
    time_t agora;
    struct tm *tempo;
    int horaAtual, minutoAtual, diaAtual, mesAtual, anoAtual;
    int dia, mes, ano, h, m;
    char horaChar[3], minChar[3], diaChar[3], mesChar[3], anoChar[5];


    strncpy(horaChar, horario, 2);
    horaChar[2] = '\0'; 
    h = atoi(horaChar);

    strncpy(minChar, horario + 2, 2);
    minChar[2] = '\0';
    m = atoi(minChar);


    strncpy(diaChar, data, 2); diaChar[2] = '\0';
    strncpy(mesChar, data + 2, 2); mesChar[2] = '\0';
    strncpy(anoChar, data + 4, 4); anoChar[4] = '\0';
    dia = atoi(diaChar);
    mes = atoi(mesChar);
    ano = atoi(anoChar);

    time(&agora);                 // obtém o tempo atual
    tempo = localtime(&agora); // converte para o horário local

    diaAtual = tempo->tm_mday;
    mesAtual = tempo->tm_mon + 1;    // tm_mon vai de 0 a 11
    anoAtual = tempo->tm_year + 1900; // tm_year é contado desde 1900
    horaAtual = tempo->tm_hour;   // pega a hora (0–23)
    minutoAtual = tempo->tm_min;

    int dataAgen = ano * 10000 + mes * 100 + dia; 
    int dataAtual = anoAtual * 10000 + mesAtual * 100 + diaAtual;
    int minutosAgen = h * 60 + m;
    int minutosAtuais = horaAtual * 60 + minutoAtual;

    if(strcmp(situacao, "Pendente") != 0) return False;
    if(op == '1'){
        if (dataAgen > dataAtual){
            printf("Impossível marcar como concluído no momento, tente novamente 2h após a conclusão do serviço.\n");//print temporario
            return False;
        }
        // se é o mesmo dia, precisa ter passado pelo menos 2h
        if (dataAgen == dataAtual) {
            if ((minutosAtuais - minutosAgen) < 120){
                printf("Impossível marcar como concluído no momento, tente novamente 2h após a conclusão do serviço.\n");//print temporario
                return False;
            }
        }
        return True;
        
    } else if (op == '2') {
        if (dataAtual < dataAgen) {
            return True;
        }
        if (dataAtual == dataAgen) {
            if ((minutosAgen - minutosAtuais) >= 120){
                return True;
            }else{
                printf("Impossível marcar como cancelado, cancelamento com mínimo de 2h de antecedência\n");//print temporario
                return False;
            }
        }
        return False;
    }
    return False;
}