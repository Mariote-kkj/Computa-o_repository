#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int contar_acertos(int sorteados[], int apostas[])
{
    int acertos = 0;
    int ja_contado[4] = {0, 0, 0, 0};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (apostas[i] == sorteados[j] && ja_contado[j] == 0)
            {
                acertos++;
                ja_contado[j] = 1;
                break;
            }
        }
    }

    return acertos;
}

void sortear_numeros(int sorteados[])
{
    for (int i = 0; i < 4; i++)
    {
        sorteados[i] = rand() % 15 + 1;

        for (int j = 0; j < i; j++)
        {
            if (sorteados[i] == sorteados[j])
            {
                i--;
                break;
            }
        }
    }
}

int main()
{
    srand(time(NULL));

    int sorteados[4];
    int apostas[4];
    int acertos;
    int tentativas;
    int gasto_total = 0;
    char continuar;

    do
    {
        tentativas = 0;

        sortear_numeros(sorteados);

        do
        {
            tentativas++;

            printf("\nTentativa %d\n", tentativas);
            printf("Digite 4 numeros entre 1 e 15:\n");

            for (int i = 0; i < 4; i++)
            {
                scanf("%d", &apostas[i]);
            }

            acertos = contar_acertos(sorteados, apostas);

            printf("Voce acertou %d numero(s).\n", acertos);

            gasto_total += 6;

        } while (acertos != 4);

        printf("\nVoce acertou os 4 numeros em %d tentativa(s)!\n", tentativas);

        if (tentativas >= 1 && tentativas <= 10)
        {
            printf("Classificacao: OTIMO\n");
        }
        else if (tentativas <= 15)
        {
            printf("Classificacao: BOM\n");
        }
        else if (tentativas <= 25)
        {
            printf("Classificacao: FRACO\n");
        }
        else
        {
            printf("Classificacao: PESSIMO\n");
        }

        printf("Dinheiro gasto ate agora: R$ %d\n", gasto_total);

        if (tentativas > 15)
        {
            printf("\nDeseja jogar novamente? (S/N): ");
            scanf(" %c", &continuar);
        }
        else
        {
            continuar = 'N';
        }

    } while (continuar == 'S' || continuar == 's');

    printf("\nTotal gasto em todas as rodadas: R$ %d\n", gasto_total);

    return 0;
}
