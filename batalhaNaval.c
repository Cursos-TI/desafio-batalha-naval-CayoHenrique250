#include <stdio.h>

// Definição de constantes para facilitar a manutenção do código
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3

int main() {
    // 1. Declaração e Inicialização do Tabuleiro (Matriz 10x10)
    // Inicializamos tudo com 0 (AGUA)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // 2. Declaração dos Navios (Vetores)
    // Usamos um vetor para representar a estrutura do navio contendo o valor 3
    int navio[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // --- Posicionamento do Navio 1: HORIZONTAL ---
    // Coordenadas iniciais (hardcoded conforme solicitado)
    // Vamos posicionar na linha 2, começando na coluna 2
    int linha_navio1 = 2;
    int col_navio1 = 2;

    // Lógica de validação simples: verifica se cabe dentro do tabuleiro
    if (col_navio1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        // Loop para copiar o vetor 'navio' para a matriz 'tabuleiro'
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Na horizontal: Linha fixa, Coluna varia (coluna + i)
            tabuleiro[linha_navio1][col_navio1 + i] = navio[i];
        }
        printf("Navio Horizontal posicionado com sucesso!\n");
    } else {
        printf("Erro: O navio horizontal nao cabe nesta posicao.\n");
    }

    // --- Posicionamento do Navio 2: VERTICAL ---
    // Coordenadas iniciais
    // Vamos posicionar na linha 5, coluna 8
    int linha_navio2 = 5;
    int col_navio2 = 8;

    // Lógica de validação simples e verificação de sobreposição
    // Verifica se cabe na vertical E se a posição inicial está livre (simplificado)
    if (linha_navio2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        
        // Loop para copiar o vetor 'navio' para a matriz 'tabuleiro'
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            // Na vertical: Coluna fixa, Linha varia (linha + i)
            // Verificação extra: garante que não estamos escrevendo em cima de outro navio
            if (tabuleiro[linha_navio2 + i][col_navio2] == AGUA) {
                 tabuleiro[linha_navio2 + i][col_navio2] = navio[i];
            } else {
                printf("Erro: Sobreposicao detectada na posicao (%d, %d)\n", linha_navio2 + i, col_navio2);
            }
        }
        printf("Navio Vertical posicionado com sucesso!\n");
        
    } else {
        printf("Erro: O navio vertical nao cabe nesta posicao.\n");
    }

    // --- Exibição do Tabuleiro ---
    printf("\n--- TABULEIRO BATALHA NAVAL ---\n\n");
    
    // Loop externo percorre as linhas
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        // Loop interno percorre as colunas
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            
            // Imprime o valor da célula seguido de um espaço para legibilidade
            // Usamos %d para inteiros.
            printf("%d ", tabuleiro[i][j]);
        }
        // Ao final de cada linha, pulamos para a próxima
        printf("\n");
    }

    return 0;
}