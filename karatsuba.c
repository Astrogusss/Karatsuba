#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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

void reverter_string(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = temp;
    }
}

//particionar string
char* particao(char* str, int inicio, int tamanho) {
    char* sub = (char*)malloc(sizeof(char) * (tamanho + 1));
    if (sub == NULL) {
        return NULL;
    }

    strncpy(sub, str + inicio, tamanho);
    sub[tamanho] = '\0';

    return sub;
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

    printf("%s", karatsuba(numero1, numero2));
    

    // printf("%s ---- %s \n", numero1, numero2);

    

    return 0;
}