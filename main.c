#include <stdio.h>
#include <stdlib.h>

#include "funcoes.c"

int main(int argc, char *argv[]){
    //Declaração de váriaveis
    int*** matA;
    int*** matB;
    int*** matResultante;
    int*** matrizDividida;

    int n;
    int tamanhoDividido;
    int rgbSize = 3;
    int corMax;
    char formato[2];
    

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
    tamanhoDividido = n/2;

    //Alocacao da Matriz A, B e Resultante
    matA = alocarMatrizPixels(n, rgbSize);
    matB = alocarMatrizPixels(n, rgbSize);
    matResultante = alocarMatrizPixels(n, rgbSize);
    
    //Preenchendo Matriz A
    preencherMatriz(file, matA, n, rgbSize);
    //Preenchendo Matriz B
    preencherMatriz(file, matB, n, rgbSize);
    
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

    fclose(file);
    return 0;
}