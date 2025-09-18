#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int base = 5;

char* primeiraMetade(char* num) {
    int len = strlen(num);

    char* res = (char*) malloc(sizeof(char) * len / 2);
    if (!res) return NULL;

    for (int i = 0; i < len / 2; i++) {
        res[i] = num[i];
    }

    res[len / 2] = '\0';

    return res;
}

char* segundaMetade(char* num) {
    int len = strlen(num);

    char* res = (char*) malloc(sizeof(char) * len / 2);
    if (!res) return NULL;

    for (int i = 0; i < (len / 2) + 1; i++) {
        res[i] = num[i + (len / 2)];
    }

    res[(len / 2) + 1] = '\0';

    return res;
}

char* soma(char* num1, char* num2, char* num3) {
    long long x = atoll(num1);
    long long y = atoll(num2);
    long long z = atoll(num3);

    x += y;
    x += z;

    char* res = (char*) malloc(sizeof(strlen(num1) + strlen(num2)));
    if (!res) return NULL;

    sprintf(res, "%lld", x);

    return res;
}

char* subtracao(char* num1, char* num2, char* num3) {
    long long x = atoll(num1);
    long long y = atoll(num2);
    long long z = atoll(num3);

    x -= y;
    x -= z;

    char* res = (char*) malloc(sizeof(strlen(num1) + strlen(num2)));
    if (!res) return NULL;

    sprintf(res, "%lld", x);

    return res;
}

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
        long long n1 = atoll(num1);
        long long n2 = atoll(num2);

        //multiplicacao de fato
        long long resultado = n1 * n2;

        //alocacao de string de char para poder guardar o resultado da multiplicacao
        char* resultadoString = (char*)malloc(sizeof(char) * 10);

        //guardando dentro da string de char, o resultado da multipicacao
        sprintf(resultadoString, "%lld", resultado);

        return resultadoString;
    }

    char* a = primeiraMetade(num1);
    char* b = segundaMetade(num1);
    char* c = primeiraMetade(num2);
    char* d = segundaMetade(num2);

    char* ac = karatsuba(a, c);
    char* bd = karatsuba(b, d);

    char* aEb = soma(a, b, "a");
    char* cEd = soma(c, d, "a");

    char* aEbcEd = karatsuba(aEb, cEd);

    char* e = subtracao(aEbcEd, ac, bd);

    e = adiciona_zeros(e, strlen(e) / 2);
    ac = adiciona_zeros(ac, strlen(ac));

    char *res = soma(ac, e, bd);

    return res;
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

// Teste da função que divide os números ao meio;
    //char* primeira = primeiraMetade(numero1);
    //char* segunda = segundaMetade(numero1);
    //printf("%s , %s", primeira, segunda);

// Teste da função soma();
    //char* resultado = soma(numero1, numero2);
    //printf("%s", resultado);

// Teste Karatsuba();
    char* resultado = karatsuba(numero1, numero2);

    printf("%s", resultado);











    //conversao de string para long long int

    //long long num1 = atoll(numero1);
    //long long num2 = atoll(numero2);
    //printf("%lld", num1 + num2);




    // printf("%s ---- %s \n", numero1, numero2);



    return 0;
}
