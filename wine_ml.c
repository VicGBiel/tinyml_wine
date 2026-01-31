#include <stdio.h>
#include "pico/stdlib.h"

#include "tflm_wrapper.h"
#include "wine_dataset.h"     
#include "wine_normalization.h" 

#define NUM_SAMPLES 36      
#define NUM_FEATURES 13   
#define NUM_CLASSES 3            

// Matriz de confusão 3x3: real x predito
static int conf_matrix[NUM_CLASSES][NUM_CLASSES];

/*
 * Função normalize_input
 * Aplica a normalização padrão (StandardScaler):
 *     x_norm = (x - mean) / std
 * Essa normalização precisa ser a mesma usada no treinamento em Python.
 */
void normalize_input(const float in[NUM_FEATURES], float out[NUM_FEATURES]) {
    for (int i = 0; i < NUM_FEATURES; i++)
        out[i] = (in[i] - wine_means[i]) / wine_stds[i]; // Usa vetores do vinho
}

/*
 * Função argmax
 * Retorna o índice da maior probabilidade entre scores[3]
 * É equivalente ao np.argmax() do Python.
 */
int argmax(const float v[3]) {
    int idx = 0;
    float max = v[0];
    for (int i = 1; i < 3; i++)
        if (v[i] > max) { max = v[i]; idx = i; }
    return idx;
}

// Função principal
int main() {

    // Inicializa printf via USB no Pico W
    stdio_init_all();
    sleep_ms(4000);

    printf("\n=== TinyML WINE - RP2040 ===\n");

    // Inicializa o TensorFlow Lite Micro (intérprete, arena, tensores etc.)
    if (tflm_init_model() != 0) {
        printf("Falha ao inicializar modelo.\n");
        return 1;
    }

    printf("Modelo inicializado com sucesso!\n");
    printf("Iniciando inferencia nas 150 amostras do dataset Iris...\n");

    // Zera matriz de confusão 3×3
    for (int i = 0; i < NUM_CLASSES; i++)
        for (int j = 0; j < NUM_CLASSES; j++)
            conf_matrix[i][j] = 0;

    int correct = 0;      // Acertos totais

    /*
     * Loop principal de inferência.
     * Percorre todas as 150 amostras do dataset Iris.
     */
    for (int i = 0; i < NUM_SAMPLES; i++) {
        float features_norm[NUM_FEATURES];    // Entrada normalizada
        float scores[NUM_CLASSES];           // Saída do modelo (probabilidades para 3 classes)
        
        // Normaliza a entrada usando média e desvio salvos
        normalize_input(wine_features[i], features_norm);

        // Executa inferência via wrapper TFLM
        tflm_infer(features_norm, scores);

        // Classe predita pelo modelo
        int pred = argmax(scores);

        // Classe verdadeira do dataset
        int real = wine_labels[i];

        // Conta acertos
        if (pred == real) correct++;

        // Atualiza matriz de confusão
        conf_matrix[real][pred]++;

        // Exibe apenas as 10 primeiras previsões, para inspeção
        if (i < 10) {
            printf("Amostra %3d  Real: %d  Pred: %d  [%.3f %.3f %.3f]\n",
                i, real, pred, scores[0], scores[1], scores[2]);
        }
    }

    // Exibe matriz de confusão formatada
    printf("\nMatriz de Confusao (real vs predito)\n");
    printf("          Pred0   Pred1   Pred2\n");
    for (int r = 0; r < NUM_CLASSES; r++) {
        printf("Real %d", r);
        for (int c = 0; c < NUM_CLASSES; c++) {
            printf("   %8d", conf_matrix[r][c]);
        }
        printf("\n");
    }

    // Calcula acurácia final
    float accuracy = (float)correct / NUM_SAMPLES;
    printf("\nAcuracia final: %.4f  ( %d / %d )\n",
            accuracy, correct, NUM_SAMPLES);

    printf("\nFim da inferencia. Loop infinito.\n");

    // Loop infinito - evita reset do programa
    while(1) tight_loop_contents();
}
