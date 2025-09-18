#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* adiciona_zeros(char* num, int zeros) {
    int len = strlen(num);
    char* resultado = (char*)malloc(sizeof(char) * (len + zeros + 1));
    if (resultado == NULL) {
        perror("Erro de alocacao de memoria");
        return NULL;
    }

    strcpy(resultado, num); // Copia o numero original
    for (int i = 0; i < zeros; i++) {
        resultado[len + i] = '0';
    }
    resultado[len + zeros] = '\0'; // Adiciona o terminador nulo

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

char* sub_string(char* str, int inicio, int tamanho) {
    char* sub = (char*)malloc(sizeof(char) * (tamanho + 1));
    if (sub == NULL) {
        perror("Erro de alocacao de memoria");
        return NULL;
    }

    strncpy(sub, str + inicio, tamanho);
    sub[tamanho] = '\0'; // Adiciona o terminador nulo

    return sub;
}

char* soma_strings(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);
    int max_len = (len1 > len2) ? len1 : len2;

    char* resultado = (char*)malloc(sizeof(char) * (max_len + 2)); // +2 para o vai um e o \0
    if (resultado == NULL) {
        perror("Erro de alocacao de memoria");
        return NULL;
    }
    
    int i = len1 - 1, j = len2 - 1, k = 0;
    int carry = 0, sum;

    while (i >= 0 || j >= 0 || carry > 0) {
        int d1 = (i >= 0) ? num1[i--] - '0' : 0;
        int d2 = (j >= 0) ? num2[j--] - '0' : 0;

        sum = d1 + d2 + carry;
        carry = sum / 10;
        resultado[k++] = (sum % 10) + '0';
    }

    resultado[k] = '\0';
    reverter_string(resultado); // Reverte a string para a ordem correta

    return resultado;
}

char* subtrai_strings(char* num1, char* num2) {
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    char* resultado = (char*)malloc(sizeof(char) * (len1 + 1));
    if (resultado == NULL) {
        perror("Erro de alocacao de memoria");
        return NULL;
    }
    
    int i = len1 - 1, j = len2 - 1, k = 0;
    int borrow = 0, diff;

    while (i >= 0 || j >= 0) {
        int d1 = (i >= 0) ? num1[i--] - '0' : 0;
        int d2 = (j >= 0) ? num2[j--] - '0' : 0;

        diff = d1 - d2 - borrow;
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        resultado[k++] = diff + '0';
    }

    // Remove zeros a esquerda
    while (k > 1 && resultado[k - 1] == '0') {
        k--;
    }
    resultado[k] = '\0';
    reverter_string(resultado); // Reverte para a ordem correta

    return resultado;
}

char* multiplicacao_tradicional(char* x, char* y) {
    long long num_x = atoll(x);
    long long num_y = atoll(y);
    long long resultado_num = num_x * num_y;

    // Converte o resultado de volta para string
    char* resultado_str = (char*)malloc(sizeof(char) * 50); // Assumindo tamanho maximo
    if (resultado_str == NULL) {
        perror("Erro de alocacao de memoria");
        return NULL;
    }
    sprintf(resultado_str, "%lld", resultado_num);
    return resultado_str;
}


char* karatsuba(char* x, char* y) {
    // 1. CASO BASE: Se os numeros sao pequenos (ex: 1 digito),
    //    use a multiplicacao tradicional.
    if (strlen(x) < 2 || strlen(y) < 2) {
        // Converte para inteiros, multiplica, e converte de volta para string
        return multiplicacao_tradicional(x, y);
    }

    // 2. DIVISAO: Encontra o meio e divide os numeros
    int n = fmax(strlen(x), strlen(y));
    int m = n / 2;

    // Use a funcao sub_string para obter as partes
    char* a = sub_string(x, 0, n - m);
    char* b = sub_string(x, n - m, m);
    char* c = sub_string(y, 0, n - m);
    char* d = sub_string(y, n - m, m);

    // 3. RECURSAO: Faz as 3 chamadas recursivas
    char* ac = karatsuba(a, c);
    char* bd = karatsuba(b, d);

    // Soma as metades para a terceira multiplicacao
    char* a_plus_b = soma_strings(a, b);
    char* c_plus_d = soma_strings(c, d);
    char* p3 = karatsuba(a_plus_b, c_plus_d);

    // 4. COMBINACAO: Calcula o termo do meio e combina tudo
    char* mid_term = subtrai_strings(subtrai_strings(p3, ac), bd);

    // Desloca ac e mid_term para simular a multiplicacao por 10^n e 10^(n/2)
    char* ac_shifted = adiciona_zeros(ac, 2 * m);
    char* mid_term_shifted = adiciona_zeros(mid_term, m);

    // Soma todos os termos para o resultado final
    char* resultado = soma_strings(soma_strings(ac_shifted, mid_term_shifted), bd);
    
    // Libera a memoria alocada para as sub-strings e resultados intermediarios
    free(a); free(b); free(c); free(d);
    free(ac); free(bd); free(p3);
    free(a_plus_b); free(c_plus_d); free(mid_term);
    free(ac_shifted); free(mid_term_shifted);

    return resultado;
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