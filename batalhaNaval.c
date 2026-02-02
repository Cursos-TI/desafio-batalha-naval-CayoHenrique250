#include <stdio.h>
#include <stdlib.h> // Necessário para a função abs()

// Definição de constantes
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_MATRIZ_HABILIDADE 5 // Tamanho das matrizes de efeito (5x5)

// Códigos visuais do tabuleiro
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5 // Novo valor para área afetada

int main() {
    // ----------------------------------------------------------------
    // PARTE 1: INICIALIZAÇÃO E POSICIONAMENTO DOS NAVIOS (CÓDIGO EXISTENTE)
    // ----------------------------------------------------------------

    // 1. Inicialização do Tabuleiro (Matriz 10x10)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    
    // Inicializa com ÁGUA
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        for(int j = 0; j < TAMANHO_TABULEIRO; j++){
            tabuleiro[i][j] = AGUA;
        }
    }

    // Vetor que representa o navio
    int navio[TAMANHO_NAVIO] = {NAVIO, NAVIO, NAVIO};

    // --- NAVIO 1: HORIZONTAL (Linha 1, Coluna 1) ---
    int l1 = 1, c1 = 1;
    if (c1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[l1][c1 + i] = navio[i];
        }
    }

    // --- NAVIO 2: VERTICAL (Linha 1, Coluna 8) ---
    int l2 = 1, c2 = 8;
    if (l2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[l2 + i][c2] = navio[i];
        }
    }

    // --- NAVIO 3: DIAGONAL PRINCIPAL ---
    int l3 = 6, c3 = 0;
    if (l3 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && c3 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int livre = 1;
        for (int i = 0; i < TAMANHO_NAVIO; i++) if (tabuleiro[l3 + i][c3 + i] != AGUA) livre = 0;
        if (livre) for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[l3 + i][c3 + i] = navio[i];
    }

    // --- NAVIO 4: DIAGONAL SECUNDÁRIA ---
    int l4 = 8, c4 = 6;
    if (l4 - (TAMANHO_NAVIO - 1) >= 0 && c4 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int livre = 1;
        for (int i = 0; i < TAMANHO_NAVIO; i++) if (tabuleiro[l4 - i][c4 + i] != AGUA) livre = 0;
        if (livre) for (int i = 0; i < TAMANHO_NAVIO; i++) tabuleiro[l4 - i][c4 + i] = navio[i];
    }

    // ----------------------------------------------------------------
    // PARTE 2: DEFINIÇÃO DAS MATRIZES DE HABILIDADE (NOVA LÓGICA)
    // ----------------------------------------------------------------
    
    // Declaração das matrizes de habilidade 5x5
    int matrizCone[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    int matrizCruz[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    int matrizOctaedro[TAMANHO_MATRIZ_HABILIDADE][TAMANHO_MATRIZ_HABILIDADE];
    
    // O centro da matriz 5x5 é a posição [2][2]
    int centro = TAMANHO_MATRIZ_HABILIDADE / 2; 

    // Geração dinâmica das matrizes usando loops e condicionais
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            
            // 1. CONE: Triângulo apontando para cima (ou base para baixo)
            // Lógica: A cada linha que desce (i aumenta), a largura permitida aumenta
            // Exemplo visual no código: "abs(j - centro) <= i" cria um triângulo
            if (abs(j - centro) <= i) {
                matrizCone[i][j] = 1;
            } else {
                matrizCone[i][j] = 0;
            }

            // 2. CRUZ: Linha central completa OU Coluna central completa
            if (i == centro || j == centro) {
                matrizCruz[i][j] = 1;
            } else {
                matrizCruz[i][j] = 0;
            }

            // 3. OCTAEDRO (Losango): Soma das distâncias (Manhattan) <= raio
            // Lógica: |linha - centro| + |coluna - centro| <= raio
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matrizOctaedro[i][j] = 1;
            } else {
                matrizOctaedro[i][j] = 0;
            }
        }
    }

    // ----------------------------------------------------------------
    // PARTE 3: APLICAÇÃO DAS HABILIDADES NO TABULEIRO
    // ----------------------------------------------------------------
    
    // Definição dos pontos de origem (Centro da explosão) no tabuleiro
    // Nota: Escolhi posições que não apaguem todos os navios para visualização
    int origemConeL = 2, origemConeC = 2;
    int origemCruzL = 5, origemCruzC = 5;
    int origemOctaL = 8, origemOctaC = 2;

    int offset = TAMANHO_MATRIZ_HABILIDADE / 2; // Offset para centralizar (vale 2)

    // APLICAR CONE
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            // Calcula a posição real no tabuleiro (Linha/Coluna Tabuleiro)
            // Lógica: Posição de Origem + Posição na Matriz Habilidade - Centralização
            int tabL = origemConeL + i - offset; // Nota: Para o cone ficar perfeito com topo na origem, o cálculo do offset vertical pode variar, mas manteremos centralizado.
            int tabC = origemConeC + j - offset;

            // Verifica se está dentro dos limites do tabuleiro E se a habilidade atinge aqui (valor 1)
            if (tabL >= 0 && tabL < TAMANHO_TABULEIRO && tabC >= 0 && tabC < TAMANHO_TABULEIRO) {
                if (matrizCone[i][j] == 1) {
                    tabuleiro[tabL][tabC] = HABILIDADE;
                }
            }
        }
    }

    // APLICAR CRUZ
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            int tabL = origemCruzL + i - offset;
            int tabC = origemCruzC + j - offset;

            if (tabL >= 0 && tabL < TAMANHO_TABULEIRO && tabC >= 0 && tabC < TAMANHO_TABULEIRO) {
                if (matrizCruz[i][j] == 1) {
                    tabuleiro[tabL][tabC] = HABILIDADE;
                }
            }
        }
    }

    // APLICAR OCTAEDRO
    for (int i = 0; i < TAMANHO_MATRIZ_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_MATRIZ_HABILIDADE; j++) {
            int tabL = origemOctaL + i - offset;
            int tabC = origemOctaC + j - offset;

            if (tabL >= 0 && tabL < TAMANHO_TABULEIRO && tabC >= 0 && tabC < TAMANHO_TABULEIRO) {
                if (matrizOctaedro[i][j] == 1) {
                    tabuleiro[tabL][tabC] = HABILIDADE;
                }
            }
        }
    }

    // ----------------------------------------------------------------
    // PARTE 4: EXIBIÇÃO DO TABULEIRO FINAL
    // ----------------------------------------------------------------

    printf("\nLEGENDA: 0=Agua, 3=Navio, 5=Habilidade Afetada\n\n");
    printf("      0 1 2 3 4 5 6 7 8 9 (Colunas)\n");
    printf("     ---------------------\n");
    
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("L%d | ", i); 
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Exibe o valor da célula
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}