#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "funcoes.c"

int main(int argc, char *argv[]){
    //Declaração de váriaveis
    clock_t start_t, end_t;
    double total_t;
    int*** matA;
    int*** matB;
    int*** matResultante;
    int*** matrizDividida;

    int n;
    int tamanhoDividido;
    int rgbSize = 3;
    int corMax;
    char formato[2];
    
    start_t = clock();
    FILE *file;

    file = fopen(argv[1], "r");

    if(file == NULL){
        printf("Erro ao abrir o arquivo");
        return 1;
    }

    //Leitura dos dados do arquivo
    fscanf(file, "%s", formato);
    fscanf(file, "%d %d", &n, &n);
    fscanf(file, "%d", &corMax);
    
    //Preenchendo Matriz A
    matA = preencherMatriz(file, n, rgbSize);
    //Preenchendo Matriz B
    matB = preencherMatriz(file, n, rgbSize);
    
    //Strassen
    matResultante = multiplicacaoMatrizesStrassen(matA, matB, n, rgbSize);


    //Printando no formato correto
    printf("%s\n", formato);
    printf("%d %d\n", n, n);
    printf("%d", corMax);
    printMatriz(matResultante, n, rgbSize);

    //Liberando Memoria
    freeMatriz(matA, n);
    freeMatriz(matB, n);
    freeMatriz(matResultante, n);

    end_t = clock();

    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("\nTempo total: %f\n", total_t);

    fclose(file);
    return 0;
}