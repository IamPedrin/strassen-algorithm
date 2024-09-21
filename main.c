#include <stdio.h>
#include <stdlib.h>

#include "funcoes.c"

int main(){
    //Declaração de váriaveis
    int*** matA;
    int*** matB;
    int*** matResultante;

    int n = 2;
    int rgbSize = 3;

    //Alocacao da Matriz A, B e Resultante
    matA = alocarMatrizPixels(n, rgbSize);


    //Preenchendo Matriz
    preencherMatriz(matA, n, rgbSize);
    printMatriz(matA, n, rgbSize);

    freeMatriz(matA, n);
}