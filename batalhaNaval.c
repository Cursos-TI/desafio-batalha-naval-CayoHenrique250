#include <stdio.h>

// Definição de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // 1. Inicialização do Tabuleiro (Matriz 10x10)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa manualmente com loops (ou poderia usar = {0})
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){
            tabuleiro[i][j] = AGUA;
        }
    }

    // Vetor que representa o navio (molde)
    int navio[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // --- NAVIO 1: HORIZONTAL (Linha 1, Coluna 1) ---
    int l1 = 1, c1 = 1;
    if (c1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[l1][c1 + i] = navio[i];
        }
        printf("Navio 1 (Horizontal) posicionado.\n");
    }

    // --- NAVIO 2: VERTICAL (Linha 1, Coluna 8) ---
    int l2 = 1, c2 = 8;
    if (l2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[l2 + i][c2] = navio[i];
        }
        printf("Navio 2 (Vertical) posicionado.\n");
    }

    // --- NAVIO 3: DIAGONAL PRINCIPAL (Descendo: Linha aumenta, Coluna aumenta) ---
    // Posição inicial: Linha 6, Coluna 0
    int l3 = 6, c3 = 0;
    
    // Validação: precisa de espaço tanto para baixo quanto para a direita
    if (l3 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && c3 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Verifica sobreposição antes de colocar
        int livre = 1;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            if (tabuleiro[l3 + i][c3 + i] != AGUA) livre = 0;
        }

        if (livre) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                // A mágica da diagonal: [l3 + i] e [c3 + i]
                tabuleiro[l3 + i][c3 + i] = navio[i];
            }
            printf("Navio 3 (Diagonal Descendo) posicionado.\n");
        } else {
             printf("Erro: Sobreposicao no Navio 3.\n");
        }
    }

    // --- NAVIO 4: DIAGONAL SECUNDÁRIA (Subindo: Linha diminui, Coluna aumenta) ---
    // Posição inicial: Linha 8, Coluna 6
    int l4 = 8, c4 = 6;

    // Validação: precisa de espaço para cima (linha >= tamanho-1) e para a direita
    // Nota: Como o índice diminui, verificamos se não vai ficar negativo
    if (l4 - (TAMANHO_NAVIO - 1) >= 0 && c4 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        
        int livre = 1;
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
             // Verifica [l4 - i][c4 + i]
            if (tabuleiro[l4 - i][c4 + i] != AGUA) livre = 0;
        }

        if (livre) {
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                // Diagonal subindo: Linha diminui (-i), Coluna aumenta (+i)
                tabuleiro[l4 - i][c4 + i] = navio[i];
            }
            printf("Navio 4 (Diagonal Subindo) posicionado.\n");
        } else {
             printf("Erro: Sobreposicao no Navio 4.\n");
        }
    }

    // --- EXIBIÇÃO DO TABULEIRO ---
    printf("\n      0 1 2 3 4 5 6 7 8 9 (Colunas)\n");
    printf("     ---------------------\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("L%d | ", i); // Exibe o número da linha para facilitar
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}