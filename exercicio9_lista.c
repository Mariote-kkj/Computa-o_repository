/****************************
 * Faça uma função com protótipo:
void intercalaVetores(int v1[], int v2[], int v3[], int n);
que receba como parâmetros de entrada dois vetores de inteiros (e sua dimensão) e preencha um terceiro vetor de tal
forma que este possua nas posições de índice par os valores do primeiro e nas posições de índice ímpar os valores do
segundo vetor (em outras palavras: intercalar os dois vetores iniciais. Obs - Todos os elementos dos vetores originais
devem estar presentes no vetor intercalado conforme a figura abaixo).
transcrição da figura acima:
exemplo do primeiro vetor com 4 elementos: 1 2 5 4
exemplo do segundo vetor com 4 elementos: 2 3 7 3
resultado do vetor que intercala o primeiro e segundo: 1 2 2 3 5 7 4 3
******************************/
#include <stdio.h>

void intercalaVetores(int v1[], int v2[], int v3[], int n);

int main() {
    int n = 6;
    int v1[] = {-2, 2, -5, 4, 1, 7};
    int v2[] = {2, -3, 7, -3,-2, -4};
    
    int v3[12]; 
    
    intercalaVetores(v1, v2, v3, n);
    
    printf("Vetor intercalado:\n");
    for (int i = 0; i < 2 * n; i++) {
        printf("%d ", v3[i]);
    }
    printf("\n");
    
    return 0;
}

void intercalaVetores(int v1[], int v2[], int v3[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        v3[2 * i] = v1[i];
        v3[(2 * i) + 1] = v2[i];
    }
}
