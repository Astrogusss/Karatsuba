#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//multiplicar por 10 e sua base



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

    printf("%s", karatsuba(numero1, numero2));
    

    // printf("%s ---- %s \n", numero1, numero2);

    

    return 0;
}