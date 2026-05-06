#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int numeroSecreto, palpite, tentativas;
    int jogarNovamente = 1;

    srand(time(NULL));

    while (jogarNovamente) {
        numeroSecreto = (rand() % 20) + 1;
        tentativas = 0;
        palpite = 0;

        printf("\n--- Novo Jogo: Adivinhe o numero entre 1 e 20 ---\n");

        while (palpite != numeroSecreto) {
            printf("Digite seu palpite: ");
            scanf("%d", &palpite);
            tentativas++;

            if (palpite < numeroSecreto) {
                printf("O numero secreto e maior.\n");
            } else if (palpite > numeroSecreto) {
                printf("O numero secreto e menor.\n");
            } else {
                printf("\nParabens! Voce acertou em %d tentativas.\n", tentativas);
            }
        }

        if (tentativas >= 1 && tentativas <= 3) {
            printf("Classificacao: OTIMO!\n");
            jogarNovamente = 0;
        } else if (tentativas >= 4 && tentativas <= 6) {
            printf("Classificacao: BOM!\n");
            jogarNovamente = 0;
        } else if (tentativas >= 7 && tentativas <= 10) {
            printf("Classificacao: FRACO. O jogo vai recomecar.\n");
            jogarNovamente = 1;
        } else {
            printf("Classificacao: PESSIMO. O jogo vai recomecar.\n");
            jogarNovamente = 1;
        }
    }

    printf("Fim do programa.\n");
    return 0;
}
