#include <stdio.h>
#include <stdlib.h>

typedef signed char singledigit;

//SOMA TUDO OK
void sum(int a, singledigit *A, int b, singledigit *B, int c, singledigit *C){
  singledigit carry = 0;

  for(int i = 1; i <= c; i++){
    singledigit fA = 0;
    singledigit fB = 0;
    if(a >= i) fA = A[a-i];
    if(b >= i) fB = B[b-i];
    int r = fA + fB + carry;
    C[c-i] = r % 10;
    carry = (r - C[c-i])/10;
  }
}

//SUBTRACAO TUDO OK
void subtrair(int n, singledigit *A,int m, singledigit *B,singledigit *C){
    int borrow = 0;
    int a,b,s;
    int na = n, nb = m;
    int nc = na;
    for (int i = 0; i < nc; i++){
        C[i] = 0;
    }

    for(int i =0;i < nc;i++){
        a = (i < na) ? A[na - 1 - i] : 0;
        b = (i < nb) ? B[nb - 1 - i] : 0;
        s = a - b - borrow;
        if (s < 0) {
            s += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        C[nc - 1 - i] = s;
    }
}

void shift(int sh, int n, singledigit *A){
    for(int i = 0; i < n-sh; i++) A[i] = A[i+sh];
    for(int i = n - sh; i < n; i++) A[i] = 0;
}

void single_multi(int n, singledigit *A, singledigit B, int m, singledigit *C){
    int carry = 0;
    for(int i = 1; i <= n; i++){
        int r = (A[n-i] * B) + carry;
        C[m-i] = r % 10;
        carry = (r - C[m-i])/10;
    }
    C[m-n-1] = carry;
}

//MULTIPLICACAO TUDO OK
void tradicional_multi(int n, singledigit *A, singledigit *B, int m, singledigit *C){
  singledigit * T = calloc(m, sizeof(singledigit));
  for(int i = 1; i <= n; i++){

    single_multi(n, A, B[n-i], m, T);
    shift(i-1,m,T);
    sum(m, T, m, C, m, C);
    for(int j = 0; j < m; j++) T[j] = 0;
  }
  free(T);
  return;
}


int main(){
    int dig;
    char aux;

    //descobrir quantos digitos tem em cada numero
    scanf("%d", &dig);
    getchar();

    singledigit* numero1 = (singledigit*)malloc(sizeof(singledigit) * dig);
    singledigit* numero2 = (singledigit*)malloc(sizeof(singledigit) * dig);

    for(int i = 0; i < dig; i++){
        scanf("%c", &aux);
        numero1[i] = atoi(&aux);
    }
    getchar();

    for(int i = 0; i < dig; i++){
        scanf("%c", &aux);
        numero2[i] = atoi(&aux);
    }; 
    getchar();

    //TUDO OK COM MULTIPLICACAO
    // singledigit* resultadoMultiplicacao = (singledigit*)malloc(sizeof(singledigit) * dig * 2);
    // tradicional_multi(dig, numero1, numero2, dig*2, resultadoMultiplicacao);
    // for(int i = 0; i < dig*2; i++) printf("%d", resultadoMultiplicacao[i]);

    //TUDO OK COM SOMA
    //singledigit* resultadoSoma = (singledigit*)malloc(sizeof(singledigit) * (dig + 1));
    //sum(dig, numero1, dig, numero2, dig + 1, resultadoSoma);
    //for(int i = 0; i < dig + 1; i++) printf("%d", resultadoSoma[i]);

    //TODO OK COM SUBTRACAO (OBSSSS: O PRIMEIRO NUMERO TEM QUE SER MAIOR QUE O SEGUNDO)
    // singledigit* resultadoSubtracao = (singledigit*)malloc(sizeof(singledigit) * dig);
    // subtrair(dig, numero1, dig, numero2, resultadoSubtracao);
    // for(int i = 0; i < dig; i++) printf("%d", resultadoSubtracao[i]);

    return 0;
}