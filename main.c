#include <stdio.h>
#include <stdlib.h>

void freeMatriz(int*** matriz, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            free(matriz[i][j]);
        }
    }

    for(int i = 0; i < n; i++){
        free(matriz[i]);
    }
    free(matriz);
}

int main(){
    //Declaração de váriaveis
    int*** matA, matB, matResultante;
    int n = 4;
    int rgbSize = 3;

    //Alocacao da Matriz
    matA = (int***) malloc(n * sizeof(int**));
    for(int i = 0; i < n; i++){
        matA[i] = (int**) malloc(n * sizeof(int*));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matA[i][j] = (int*) malloc(rgbSize * sizeof(int));
        }
    } 


    //Preenchendo Matriz
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matA[i][j][k] = 1;
            }
        }
    }

    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < n; j++){
            printf(" ");
            for(int k = 0; k < rgbSize; k++){
                printf("%d ", matA[i][j][k]);
            }
        }
    }

    freeMatriz(matA, n);
}