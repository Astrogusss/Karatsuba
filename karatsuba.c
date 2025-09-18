#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int base = 5;

//multiplicar por 10 e sua base
char* adiciona_zeros(char* num, int zeros) {
    int len = strlen(num);
    char* resultado = (char*)malloc(sizeof(char) * (len + zeros + 1));
    if (resultado == NULL) {
        return NULL;
    }

    strcpy(resultado, num);
    for (int i = 0; i < zeros; i++) {
        resultado[len + i] = '0';
    }
    resultado[len + zeros] = '\0'; 
    return resultado;
}


char* karatsuba(char* num1, char* num2){
    if(strlen(num1) < base || strlen(num2) < base){
        //conversao de vetor de char em long long int para poder manipular e multipicar os dados
        long long num1 = atoll(num1);
        long long num2 = atoll(num2);

        //multiplicacao de fato
        long resultado = num1 * num2;

        //alocacao de string de char para poder guardar o resultado da multiplicacao
        char* resultadoString = (char*)malloc(sizeof(char) * 10);

        //guardando dentro da string de char, o resultado da multipicacao
        sprintf(resultadoString, "%lld", resultado);
        
        return resultadoString;
    }
}


int main(){
    int dig, c;
    scanf("%d", &dig);

    //leitura do primeiro numero
    char* numero1 = (char*)malloc(sizeof(char) * dig);
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(numero1, dig + 1, stdin);

    //leitura do segundo numero
    char* numero2 = (char*)malloc(sizeof(char) * dig);
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(numero2, dig + 1, stdin);


    //conversao de string para long long int

    //long long num1 = atoll(numero1);
    //long long num2 = atoll(numero2);
    //printf("%lld", num1 + num2);


    

    // printf("%s ---- %s \n", numero1, numero2);

    

    return 0;
}