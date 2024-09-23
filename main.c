#include <stdio.h>
#include <stdlib.h>

#include "funcoes.c"

int main(){
    //Declaração de váriaveis
    int*** matA;
    int*** matB;
    int*** matResultante;

    int n;
    int rgbSize = 3;
    int corMax;
    char formato[2];

    FILE *file;
    file = fopen("Casos/1.in", "r");

    if(file == NULL){
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    fscanf(file, "%s", formato);
    fscanf(file, "%d %d", &n, &n);
    fscanf(file, "%d", &corMax);

    printf("%s\n", formato);
    printf("%d %d\n", n, n);
    printf("%d", corMax);

    //Alocacao da Matriz A, B e Resultante
    matA = alocarMatrizPixels(n, rgbSize);
    matB = alocarMatrizPixels(n, rgbSize);

    //Preenchendo Matriz A
    preencherMatriz(file, matA, n, rgbSize);
    printMatriz(matA, n, rgbSize);

    //Preenchendo Matriz B
    preencherMatriz(file, matB, n, rgbSize);
    printMatriz(matB, n, rgbSize);

    matResultante = multiplicaoMatrizesPixelsClassico(matA, matB, n, rgbSize);
    printf("\n");
    printMatriz(matResultante, n, rgbSize);

    //Liberando Memoria
    freeMatriz(matA, n);
    freeMatriz(matB, n);
    freeMatriz(matResultante, n);

    fclose(file);
    return 0;
}