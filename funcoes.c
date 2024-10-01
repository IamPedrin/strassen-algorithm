#include <stdio.h>

//Função para alocar a matriz na memória
//n - tamanho da matriz quadratica
//rgbSize - tamnho do vetor q vai ser o RGB
int*** alocarMatrizPixels(int n, int rgbSize){
    int*** mat = (int***) malloc(n * sizeof(int**));
    for(int i = 0; i < n; i++){
        mat[i] = (int**) malloc(n * sizeof(int*));
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            mat[i][j] = (int*) malloc(rgbSize * sizeof(int));
            for(int k = 0; k < rgbSize; k++){
                mat[i][j][k] = 0;
            }
        }
    } 
    return mat;
}

void multiplicaoMatrizesPixelsClassico(int*** matA, int*** matB, int*** matrizResultante, int n, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matrizResultante[i][j][k] = 0;
                for(int l = 0; l < n; l++){
                    matrizResultante[i][j][k] += matA[i][l][k] * matB[l][j][k];  
                }
            }
        }
    }
}


int*** preencherMatriz(FILE *file, int n, int rgbSize){
    int*** mat = alocarMatrizPixels(n, rgbSize);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                fscanf(file, "%d", &mat[i][j][k]);
            }
        }
    }
    return mat;
}

void printMatriz(int*** mat, int n, int rgbSize){
    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                printf("%d ", mat[i][j][k]);
            }
        }
    }
}

//Função para liberar a matriz da memória
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

void dividirMatriz(int n, int*** mat, int*** matrizDividida, int iInicio, int jInicio, int rgbSize){
    int novoTamanho = n/2;

    for(int i = 0, i2 = iInicio; i < novoTamanho; i++, i2++){
        for(int j = 0, j2 = jInicio; j < novoTamanho; j++, j2++){
           for(int k = 0; k < rgbSize; k++){
                matrizDividida[i][j][k] = mat[i2][j2][k];
            }
        }
    }
}

void juntarMatriz(int n, int*** matDividida, int*** matrizCompleta, int iInicio, int jInicio, int rgbSize){
    int novoTamanho = n/2;

    for(int i = 0, i2 = iInicio; i < novoTamanho; i++, i2++){
        for(int j = 0, j2 = jInicio; j < novoTamanho; j++, j2++){
            for(int k = 0; k < rgbSize; k++){
                matrizCompleta[i2][j2][k] = matDividida[i][j][k];
            }
        }
    }
}

void adicaoMatrizes(int n, int*** matA, int*** matB, int*** matResultante, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matResultante[i][j][k] = matA[i][j][k] + matB[i][j][k];
            }
        }
    }
}

void subtracaoMatrizes(int n, int*** matA, int*** matB, int*** matResultante, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matResultante[i][j][k] = matA[i][j][k] - matB[i][j][k];
            }
        }
    }
}

int*** multiplicacaoMatrizesStrassen(int*** matA, int***matB, int n, int rgbSize){
    int*** resultado = alocarMatrizPixels(n, rgbSize);
    int tamanhoMatrizDividido = n/2;
    if(n < 32){
        multiplicaoMatrizesPixelsClassico(matA, matB, resultado, n, rgbSize);
    }else{
        //Dividindo Matriz A em 4
        int*** matAParte1 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matA, matAParte1, 0, 0, rgbSize);
        int*** matAParte2 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize); 
        dividirMatriz(n, matA, matAParte2, 0, tamanhoMatrizDividido, rgbSize);
        int*** matAParte3 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matA, matAParte3, tamanhoMatrizDividido, 0, rgbSize);
        int*** matAParte4 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matA, matAParte4, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        //Dividindo Matriz B em 4
        int*** matBParte1 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matB, matBParte1, 0, 0, rgbSize);
        int*** matBParte2 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matB, matBParte2, 0, tamanhoMatrizDividido, rgbSize);
        int*** matBParte3 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matB, matBParte3, tamanhoMatrizDividido, 0, rgbSize);
        int*** matBParte4 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        dividirMatriz(n, matB, matBParte4, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        int*** temp1 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** temp2 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);

        //Variaveis para receber os resultados das formulas de strassen
        int*** p1;
        int*** p2;
        int*** p3;
        int*** p4;
        int*** p5;
        int*** p6;
        int*** p7;

        //7 produtos de strassen
        //P1 = A.(F-H)
        
        subtracaoMatrizes(tamanhoMatrizDividido, matBParte2, matBParte4, temp1, rgbSize);
        p1 = multiplicacaoMatrizesStrassen(matAParte1, temp1, tamanhoMatrizDividido, rgbSize);
        //P2 = (A+B).H
        adicaoMatrizes(tamanhoMatrizDividido, matAParte1, matAParte2, temp1, rgbSize);
        p2 = multiplicacaoMatrizesStrassen(temp1, matBParte4, tamanhoMatrizDividido, rgbSize);
        //P3 = (C+D).E
        adicaoMatrizes(tamanhoMatrizDividido, matAParte3, matAParte4, temp1, rgbSize);
        p3 = multiplicacaoMatrizesStrassen(temp1, matBParte1, tamanhoMatrizDividido, rgbSize);
        //P4 = D.(G-E)
        subtracaoMatrizes(tamanhoMatrizDividido, matBParte3, matBParte1, temp1, rgbSize);
        p4 = multiplicacaoMatrizesStrassen(matAParte4, temp1, tamanhoMatrizDividido, rgbSize);
        //P5 = (A+D).(E+H)
        adicaoMatrizes(tamanhoMatrizDividido, matAParte1, matAParte4, temp1, rgbSize);
        adicaoMatrizes(tamanhoMatrizDividido, matBParte1, matBParte4, temp2, rgbSize);
        p5 = multiplicacaoMatrizesStrassen(temp1, temp2, tamanhoMatrizDividido, rgbSize);
        //P6 = (B-D).(G+H)
        subtracaoMatrizes(tamanhoMatrizDividido, matAParte2, matAParte4, temp2, rgbSize);
        adicaoMatrizes(tamanhoMatrizDividido, matBParte3, matBParte4, temp2, rgbSize);
        p6 = multiplicacaoMatrizesStrassen(temp1, temp2, tamanhoMatrizDividido, rgbSize);
        //P7 = (A-C).(E-F)
        subtracaoMatrizes(tamanhoMatrizDividido, matAParte1, matAParte3, temp1, rgbSize);
        adicaoMatrizes(tamanhoMatrizDividido, matBParte1, matBParte2, temp2, rgbSize);
        p7 = multiplicacaoMatrizesStrassen(temp1, temp2, tamanhoMatrizDividido, rgbSize);

        freeMatriz(matAParte1, tamanhoMatrizDividido);
        freeMatriz(matAParte2, tamanhoMatrizDividido);
        freeMatriz(matAParte3, tamanhoMatrizDividido);
        freeMatriz(matAParte4, tamanhoMatrizDividido);
        freeMatriz(matBParte1, tamanhoMatrizDividido);
        freeMatriz(matBParte2, tamanhoMatrizDividido);
        freeMatriz(matBParte3, tamanhoMatrizDividido);
        freeMatriz(matBParte4, tamanhoMatrizDividido);

        int*** matResultanteP1 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** matResultanteP2 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** matResultanteP3 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** matResultanteP4 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);

        adicaoMatrizes(tamanhoMatrizDividido, p5, p4, temp1, rgbSize);
        subtracaoMatrizes(tamanhoMatrizDividido, temp1, p2, temp2, rgbSize);
        adicaoMatrizes(tamanhoMatrizDividido, temp2, p6, matResultanteP1, rgbSize);

        adicaoMatrizes(tamanhoMatrizDividido, p1, p2, matResultanteP2, rgbSize);
        adicaoMatrizes(tamanhoMatrizDividido, p3, p4, matResultanteP3, rgbSize);

        adicaoMatrizes(tamanhoMatrizDividido, p5, p1, temp1, rgbSize);
        subtracaoMatrizes(tamanhoMatrizDividido, temp1, p3, temp2, rgbSize);
        subtracaoMatrizes(tamanhoMatrizDividido, temp2, p7, matResultanteP4, rgbSize);

        freeMatriz(temp1, tamanhoMatrizDividido);
        freeMatriz(temp2, tamanhoMatrizDividido);

        freeMatriz(p1, tamanhoMatrizDividido);
        freeMatriz(p2, tamanhoMatrizDividido);
        freeMatriz(p3, tamanhoMatrizDividido);
        freeMatriz(p4, tamanhoMatrizDividido);
        freeMatriz(p5, tamanhoMatrizDividido);
        freeMatriz(p6, tamanhoMatrizDividido);
        freeMatriz(p7, tamanhoMatrizDividido);

        //Juncao das partes
        juntarMatriz(n, matResultanteP1, resultado, 0, 0, rgbSize);
        juntarMatriz(n, matResultanteP2, resultado, 0, tamanhoMatrizDividido, rgbSize);
        juntarMatriz(n, matResultanteP3, resultado, tamanhoMatrizDividido, 0, rgbSize);
        juntarMatriz(n, matResultanteP4, resultado, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);


        freeMatriz(matResultanteP1, tamanhoMatrizDividido);
        freeMatriz(matResultanteP2, tamanhoMatrizDividido);
        freeMatriz(matResultanteP3, tamanhoMatrizDividido);
        freeMatriz(matResultanteP4, tamanhoMatrizDividido);

    }
    return resultado;
}
