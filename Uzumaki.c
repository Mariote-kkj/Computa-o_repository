#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5
#define P1 'A'      
#define P2 'B'      
#define UZUMAKI '@' 
#define VAZIO '.'

void inicializarTabuleiro(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = VAZIO;
        }
    }
}

void desenharTabuleiro(char tabuleiro[TAM][TAM]) {
    printf("\n   1   2   3   4   5\n");
    printf(" +---+---+---+---+---+\n");
    for (int i = 0; i < TAM; i++) {
        printf("%d |", i + 1);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == P1) printf(" A |");
            else if (tabuleiro[i][j] == P2) printf(" B |");
            else if (tabuleiro[i][j] == UZUMAKI) printf(" @ |");
            else printf(" . |"); 
        }
        printf("\n +---+---+---+---+---+\n");
    }
    printf("\n");
}

int tabuleiroCheio(char tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == VAZIO) return 1; 
        }
    }
    return 0; 
}

int checarEfeitoRebote(char tabuleiro[TAM][TAM], int l, int c, char seu_simbolo) {
    char vizinhos[4];
    int qtd = 0;
    
    if (l > 0) vizinhos[qtd++] = tabuleiro[l-1][c];
    if (l < TAM-1) vizinhos[qtd++] = tabuleiro[l+1][c];
    if (c > 0) vizinhos[qtd++] = tabuleiro[l][c-1];
    if (c < TAM-1) vizinhos[qtd++] = tabuleiro[l][c+1];
    
    for (int i = 0; i < qtd; i++) {
        if (vizinhos[i] != VAZIO && vizinhos[i] != seu_simbolo) {
            return 1; 
        }
    }
    return 0;
}

int checarMaldicao(char tabuleiro[TAM][TAM], int l, int c) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nl = l + i;
            int nc = c + j;
            if (nl >= 0 && nl < TAM && nc >= 0 && nc < TAM) {
                if (tabuleiro[nl][nc] == UZUMAKI) return 1;
            }
        }
    }
    return 0;
}

void espalharMaldicaoUzumaki(char tabuleiro[TAM][TAM], int l, int c, 
                             int *p1_amaldicoado, int *p1_mal_l, int *p1_mal_c,
                             int *p2_amaldicoado, int *p2_mal_l, int *p2_mal_c) {
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nl = l + i;
            int nc = c + j;
            if (nl >= 0 && nl < TAM && nc >= 0 && nc < TAM) {
                if (tabuleiro[nl][nc] == P1 && !(*p1_amaldicoado)) {
                    *p1_amaldicoado = 1;
                    *p1_mal_l = nl;
                    *p1_mal_c = nc;
                    printf("** A espiral do Uzumaki encostou na peca do Jogador 1 em [%d, %d] e a amaldicoou! **\n", nl + 1, nc + 1);
                }
                if (tabuleiro[nl][nc] == P2 && !(*p2_amaldicoado)) {
                    *p2_amaldicoado = 1;
                    *p2_mal_l = nl;
                    *p2_mal_c = nc;
                    printf("** A espiral do Uzumaki encostou na peca do Jogador 2 em [%d, %d] e a amaldicoou! **\n", nl + 1, nc + 1);
                }
            }
        }
    }
}

int checarVitoria(char tabuleiro[TAM][TAM], char simbolo) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j <= TAM - 4; j++) {
            if (tabuleiro[i][j] == simbolo && tabuleiro[i][j+1] == simbolo && 
                tabuleiro[i][j+2] == simbolo && tabuleiro[i][j+3] == simbolo) return 1;
            if (tabuleiro[j][i] == simbolo && tabuleiro[j+1][i] == simbolo && 
                tabuleiro[j+2][i] == simbolo && tabuleiro[j+3][i] == simbolo) return 1;
        }
    }
    for (int i = 0; i <= TAM - 4; i++) {
        for (int j = 0; j <= TAM - 4; j++) {
            if (tabuleiro[i][j] == simbolo && tabuleiro[i+1][j+1] == simbolo && 
                tabuleiro[i+2][j+2] == simbolo && tabuleiro[i+3][j+3] == simbolo) return 1;
        }
    }
    for (int i = 3; i < TAM; i++) {
        for (int j = 0; j <= TAM - 4; j++) {
            if (tabuleiro[i][j] == simbolo && tabuleiro[i-1][j+1] == simbolo && 
                tabuleiro[i-2][j+2] == simbolo && tabuleiro[i-3][j+3] == simbolo) return 1;
        }
    }
    return 0;
}

void jogadaUzumaki(char tabuleiro[TAM][TAM], 
                   int *p1_amaldicoado, int *p1_mal_l, int *p1_mal_c,
                   int *p2_amaldicoado, int *p2_mal_l, int *p2_mal_c) {
    int l, c;
    printf("--- Turno do Uzumaki (@) ---\n");
    
    int espaco = 0;
    for(int i=0; i<TAM; i++) for(int j=0; j<TAM; j++) if(tabuleiro[i][j] == VAZIO) espaco = 1;
    if (!espaco) return;

    do {
        l = rand() % TAM;
        c = rand() % TAM;
    } while (tabuleiro[l][c] != VAZIO);

    tabuleiro[l][c] = UZUMAKI;
    printf("O Uzumaki expandiu sua espiral em [%d, %d]!\n", l + 1, c + 1);
    
    espalharMaldicaoUzumaki(tabuleiro, l, c, p1_amaldicoado, p1_mal_l, p1_mal_c, p2_amaldicoado, p2_mal_l, p2_mal_c);
}

void turnoHumano(char tabuleiro[TAM][TAM], int jogadorNum, char simbolo, int *perde_vez, int *amaldicoado, int *mal_l, int *mal_c) {
    int l, c;
    printf("--- Turno do Jogador %d (%c) ---\n", jogadorNum, simbolo);

    if (*amaldicoado) {
        printf("!! MALDICAO DA ESPIRAL !! Mova obrigatoriamente sua peca de [%d, %d].\n", *mal_l + 1, *mal_c + 1);
        int nova_l, nova_c;
        while (1) {
            printf("Digite a nova posicao na ordem [LINHA COLUNA] separando por espaco (Ex: 3 4): ");
            scanf("%d %d", &nova_l, &nova_c);
            nova_l--; nova_c--;

            if (nova_l >= 0 && nova_l < TAM && nova_c >= 0 && nova_c < TAM && tabuleiro[nova_l][nova_c] == VAZIO) {
                tabuleiro[*mal_l][*mal_c] = VAZIO; 
                tabuleiro[nova_l][nova_c] = simbolo; 
                
                if (checarEfeitoRebote(tabuleiro, nova_l, nova_c, simbolo)) {
                    printf(">> Efeito Rebote! Voce colou em um simbolo inimigo ao mover. Perdera o proximo turno!\n");
                    *perde_vez = 1;
                }
                if (checarMaldicao(tabuleiro, nova_l, nova_c)) {
                    printf("** A peca continuou encostada no Uzumaki e segue amaldicoada!\n");
                    *mal_l = nova_l; *mal_c = nova_c;
                } else {
                    *amaldicoado = 0; 
                }
                break;
            }
            printf("Posicao invalida! Tente novamente.\n");
        }
        return;
    }

    while (1) {
        printf("Sua jogada! Digite na ordem [LINHA COLUNA] separando por espaco (Ex: 2 5): ");
        scanf("%d %d", &l, &c);
        l--; c--; 

        if (l >= 0 && l < TAM && c >= 0 && c < TAM && tabuleiro[l][c] == VAZIO) {
            tabuleiro[l][c] = simbolo;

            if (checarEfeitoRebote(tabuleiro, l, c, simbolo)) {
                printf(">> EFEITO REBOTE! Voce colou em um simbolo inimigo. O Uzumaki jogara duas vezes!\n");
                *perde_vez = 1;
            }
            if (checarMaldicao(tabuleiro, l, c)) {
                printf("** MALDICAO DA ESPIRAL! Peca em [%d, %d] amaldicoada.\n", l + 1, c + 1);
                *amaldicoado = 1;
                *mal_l = l; *mal_c = c;
            }
            break;
        }
        printf("Posicao invalida ou ocupada! Tente novamente.\n");
    }
}

int main() {
    srand(time(NULL));

    char tabuleiro[TAM][TAM];
    int p1_perde_vez = 0, p2_perde_vez = 0;
    int p1_amaldicoado = 0, p2_amaldicoado = 0;
    int p1_mal_l = -1, p1_mal_c = -1; 
    int p2_mal_l = -1, p2_mal_c = -1; 

    inicializarTabuleiro(tabuleiro);
    
    int turno = 1; 
    int jogo_rodando = 1;

    printf("=========================================\n");
    printf(" ## UZUMAKI: Fuja da maldição! ## \n");
    printf("=========================================\n");

    while (jogo_rodando) {
        desenharTabuleiro(tabuleiro);

        if (turno == 1) {
            if (p1_perde_vez) {
                printf("\n>> Jogador 1 pulado pelo Efeito Rebote! O Uzumaki ganha um turno extra.\n");
                p1_perde_vez = 0;
                turno = 2; 
                continue;
            }
            turnoHumano(tabuleiro, 1, P1, &p1_perde_vez, &p1_amaldicoado, &p1_mal_l, &p1_mal_c);
            if (checarVitoria(tabuleiro, P1)) { 
                desenharTabuleiro(tabuleiro); 
                printf("!! Fim da obsessao! Jogador 1 (A) venceu! !!\n"); 
                jogo_rodando = 0; 
            }
            turno = 2;
        } 
        else if (turno == 2) {
            if (p2_perde_vez) {
                printf("\n>> Jogador 2 pulado pelo Efeito Rebote! O Uzumaki ganha um turno extra.\n");
                p2_perde_vez = 0;
                turno = 3; 
                continue;
            }
            turnoHumano(tabuleiro, 2, P2, &p2_perde_vez, &p2_amaldicoado, &p2_mal_l, &p2_mal_c);
            if (checarVitoria(tabuleiro, P2)) { 
                desenharTabuleiro(tabuleiro); 
                printf("!! Fim da obsessao! Jogador 2 (B) venceu! !!\n"); 
                jogo_rodando = 0; 
            }
            turno = 3;
        } 
        else if (turno == 3) {
            jogadaUzumaki(tabuleiro, &p1_amaldicoado, &p1_mal_l, &p1_mal_c, &p2_amaldicoado, &p2_mal_l, &p2_mal_c);
            if (checarVitoria(tabuleiro, UZUMAKI)) { 
                desenharTabuleiro(tabuleiro); 
                printf("** O UZUMAKI ALINHOU 4 ESPIRAIS! A maldicao consumiu a todos. Os humanos perderam! **\n"); 
                jogo_rodando = 0; 
            }
            turno = 1;
        }

        if (jogo_rodando && !tabuleiroCheio(tabuleiro)) {
            desenharTabuleiro(tabuleiro);
            printf("## O tabuleiro foi completamente distorcido. Empate caotico. ##\n");
            jogo_rodando = 0;
        }
    }
    return 0;
}
