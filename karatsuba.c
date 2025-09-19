#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const int base = 5;
typedef signed char signeddigit;

char* stripLeadingZeros(char* num) {
    if (!num) return NULL;

    // encontra o primeiro dígito diferente de '0'
    int i = 0;
    while (num[i] == '0' && num[i + 1] != '\0') {
        i++;
    }

    // se não houver zeros à esquerda, retorna cópia da string original
    if (i == 0) return num;

    // cria nova string sem os zeros à esquerda
    int len = strlen(num) - i;
    char* res = (char*) malloc(len + 1);
    if (!res) return NULL;

    strcpy(res, num + i);
    free(num);  // libera a string antiga, se for alocada dinamicamente
    return res;
}

// Converte string de dígitos '0'-'9' para vetor de dígitos numéricos (0-9)
signeddigit* str_to_digits(const char* num, int len) {
    signeddigit* res =(signeddigit*) malloc(len * sizeof(signeddigit));
    for (int i = 0; i < len; i++)
        res[i] = num[i] - '0';
    return res;
}

char* digits_to_str(signeddigit* A, int len) {
    char* res = malloc(len + 1);
    for (int i = 0; i < len; i++)
        res[i] = A[i] + '0';
    res[len] = '\0';
    return res;
}

int max(int num1, int num2) {
    if (num1 > num2) return num1;
    else return num2;
}

char* primeiraMetade(char* num) {
    int len = strlen(num);

    char* res = (char*) malloc(sizeof(char) * (len / 2 + 1));
    if (!res) return NULL;

    for (int i = 0; i < len / 2; i++) {
        res[i] = num[i];
    }

    res[len / 2] = '\0';

    return res;
}

char* segundaMetade(char* num) {
    int len = strlen(num);
    int meio = len / 2;
    int tamanho = len - meio;

    char* res = (char*) malloc(sizeof(char) * (tamanho + 1));
    if (!res) return NULL;

    for (int i = 0; i < tamanho; i++) {
        res[i] = num[i + meio];
    }

    res[tamanho] = '\0';

    return res;
}

void sum(int a, signeddigit *A, int b, signeddigit *B, int c, signeddigit *C){
    signeddigit carry = 0;

    for(int i = 1; i <= c; i++){
        signeddigit fA = 0;
        signeddigit fB = 0;
        if(a >= i) fA = A[a-i];
        if(b >= i) fB = B[b-i];
        int r = fA + fB + carry;
        C[c-i] = r % 10;
        carry = (r - C[c-i])/10;
    }
}

char* adicionaZerosEsquerda(char *num, int zeros) {
    char* res = (char*) malloc(sizeof(char) * (strlen(num) + zeros + 1));
    if (!res) return NULL;

    for (int i = 0; i < zeros; i++) {
        res[i] = '0';
    }

    for (int i = 0; i < strlen(num); i++) {
        res[i + zeros] = num[i];
    }

    res[strlen(num) + zeros] = '\0';

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
    if (strlen(num1) != strlen(num2)) {
        char* temp;
        if (strlen(num1) < strlen(num2)) {
            temp = adicionaZerosEsquerda(num1, strlen(num2) - strlen(num1));
            free(num1);   // libera o original, se foi alocado dinamicamente
            num1 = temp;
        } else if (strlen(num2) < strlen(num1)) {
            temp = adicionaZerosEsquerda(num2, strlen(num1) - strlen(num2));
            free(num2);
            num2 = temp;
        }
    }

    if(strlen(num1) < base || strlen(num2) < base){
        //conversao de vetor de char em long long int para poder manipular e multipicar os dados
        long long n1 = atoll(num1);
        long long n2 = atoll(num2);

        //multiplicacao de fato
        long long resultado = n1 * n2;

        //alocacao de string de char para poder guardar o resultado da multiplicacao
        char* resultadoString = (char*)malloc(sizeof(char) * 21);

        //guardando dentro da string de char, o resultado da multipicacao
        sprintf(resultadoString, "%lld", resultado);

        return resultadoString;
    }

    char* a = primeiraMetade(num1);
    char* b = segundaMetade(num1);
    char* c = primeiraMetade(num2);
    char* d = segundaMetade(num2);

    char* ac = karatsuba(a, c);
    char* ad = karatsuba(a, d);
    char* bc = karatsuba(b, c);
    char* bd = karatsuba(b, d);

    // ---------- cálculo de e = ad + bc ----------
    int lenE = max(strlen(ad), strlen(bc));
    signeddigit* A = str_to_digits(ad, strlen(ad));
    signeddigit* B = str_to_digits(bc, strlen(bc));
    signeddigit* C = (signeddigit*) calloc(lenE + 1, sizeof(signeddigit));

    sum(strlen(ad), A, strlen(bc), B, lenE + 1, C);

    char* e = digits_to_str(C, lenE + 1);

    free(A);
    free(B);
    free(C);

    // ---------- alinhamento de e e ac ----------
    int len = strlen(num1);
    int meio = len / 2;
    int metadeDir = len - meio;

    char* e_old = e;
    e = adiciona_zeros(e_old, metadeDir);
    free(e_old);

    char* ac_old = ac;
    ac = adiciona_zeros(ac_old, 2 * metadeDir);
    free(ac_old);

    // ---------- cálculo de aux = ac + e ----------
    int lenAux = max(strlen(ac), strlen(e));
    signeddigit* D = str_to_digits(ac, strlen(ac));
    signeddigit* E = str_to_digits(e, strlen(e));
    signeddigit* F = (signeddigit*) calloc(lenAux + 1, sizeof(signeddigit));

    sum(strlen(ac), D, strlen(e), E, lenAux + 1, F);

    char* aux = digits_to_str(F, lenAux + 1);

    free(D);
    free(E);
    free(F);

    // ---------- cálculo de res = aux + bd ----------
    int lenRes = max(strlen(aux), strlen(bd));
    signeddigit* G = str_to_digits(aux, strlen(aux));
    signeddigit* H = str_to_digits(bd, strlen(bd));
    signeddigit* I = (signeddigit*) calloc(lenRes + 1, sizeof(signeddigit));

    sum(strlen(aux), G, strlen(bd), H, lenRes + 1, I);

    char* res = digits_to_str(I, lenRes + 1);

    free(G);
    free(H);
    free(I);

    res = stripLeadingZeros(res);
    return res;
}

int main(){
    int dig, c;
    scanf("%d", &dig);

    //leitura do primeiro numero
    char* numero1 = (char*)malloc(sizeof(char) * dig + 1);
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(numero1, dig + 1, stdin);

    //leitura do segundo numero
    char* numero2 = (char*)malloc(sizeof(char) * dig + 1);
    while ((c = getchar()) != '\n' && c != EOF);
    fgets(numero2, dig + 1, stdin);

    numero1[strcspn(numero1, "\n")] = '\0';
    numero2[strcspn(numero2, "\n")] = '\0';

    char* resultado = karatsuba(numero1, numero2);
    printf("%s", resultado);

    return 0;
}
