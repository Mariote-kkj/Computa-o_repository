#include <stdio.h>
#include <math.h>

int main() {
    char op;
    float a, b, c, media;

    printf("Escolha uma opcao para calcular a média:\n");
    printf("A - Media Aritmetica\n");
    printf("P - Media Ponderada\n");
    printf("G - Media Geometrica\n");
    printf("H - Media harmonica\n");

    printf("Opcao: ");
    scanf(" %c", &op);

    printf("Digite tres valores: ");
    scanf("%f %f %f", &a, &b, &c);

    if (op == 'A' || op == 'a') {
        media = (a + b + c) / 3;
        printf("Media aritmetica: %.2f\n", media);
    }
    else if (op == 'P' || op == 'p') {
        media = (a + b*2 + c*3) / 6;
        printf("Media ponderada: %.2f\n", media);
    }
    else if (op == 'G' || op == 'g') {
        media = cbrt(a * b * c);
        printf("Media geometrica: %.2f\n", media);
    }
    else if (op == 'H' || op == 'h') {
        media = 3 / (1/a + 1/b + 1/c);
        printf("Media harmonica: %.2f\n", media);
    }
    else {
        printf("Opcao invalida\n");
    }

    return 0;
}
