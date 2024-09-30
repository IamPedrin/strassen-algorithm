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


int*** multiplicaoMatrizesPixelsClassico(int*** matA, int*** matB, int n, int rgbSize){
    int*** matrizResultante = alocarMatrizPixels(n, rgbSize);
    
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

    return matrizResultante;
}


void preencherMatriz(FILE *file, int*** mat, int n, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                fscanf(file, "%d", &mat[i][j][k]);
            }
        }
    }
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


int*** dividirMatriz(int n, int*** mat, int iInicio, int jInicio, int rgbSize){
    int novoTamanho = n/2;
    int*** matrizDividida = alocarMatrizPixels(novoTamanho, rgbSize);

    for(int i = 0, i2 = iInicio; i < novoTamanho; i++, i2++){
        for(int j = 0, j2 = jInicio; j < novoTamanho; j++, j2++){
           for(int k = 0; k < rgbSize; k++){
                matrizDividida[i][j][k] = mat[i2][j2][k];
            }
        }
    }
    return matrizDividida;
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

int*** adicaoMatrizes(int n, int*** matA, int*** matB,int rgbSize){
    int*** matResultante = alocarMatrizPixels(n, rgbSize);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matResultante[i][j][k] = matA[i][j][k] + matB[i][j][k];
            }
        }
    }
    return matResultante;
}

int*** subtracaoMatrizes(int n, int*** matA, int*** matB, int rgbSize){
    int*** matResultante = alocarMatrizPixels(n, rgbSize);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matResultante[i][j][k] = matA[i][j][k] - matB[i][j][k];
            }
        }
    }
    return matResultante;
}

/*
    | PARTE 1   PARTE 2 |   | 
    |                   | X |
    | PARTE 3   PARTE 4 |   |

*/
void multiplicacaoMatrizesStrassen(int*** matA, int***matB, int*** resultado, int n, int rgbSize){
    int tamanhoMatrizDividido = n/2;
    if(n == 1){
        for(int k = 0; k < rgbSize; k++){
            resultado[0][0][k] = matA[0][0][k] * matB[0][0][k];
        }
        
    }else{
        // int*** matrizResultante = alocarMatrizPixels(n, rgbSize);

        //Dividindo Matriz A em 4
        int*** matAParte1 = dividirMatriz(n, matA, 0, 0, rgbSize);
        int*** matAParte2 = dividirMatriz(n, matA, 0, tamanhoMatrizDividido, rgbSize);
        int*** matAParte3 = dividirMatriz(n, matA, tamanhoMatrizDividido, 0, rgbSize);
        int*** matAParte4 = dividirMatriz(n, matA, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        //Dividindo Matriz B em 4
        int*** matBParte1 = dividirMatriz(n, matB, 0, 0, rgbSize);
        int*** matBParte2 = dividirMatriz(n, matB, 0, tamanhoMatrizDividido, rgbSize);
        int*** matBParte3 = dividirMatriz(n, matB, tamanhoMatrizDividido, 0, rgbSize);
        int*** matBParte4 = dividirMatriz(n, matB, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        //Variaveis para receber os resultados das formulas de strassen
        int*** p1 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** p2 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** p3 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** p4 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** p5 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** p6 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);
        int*** p7 = alocarMatrizPixels(tamanhoMatrizDividido, rgbSize);

        //7 produtos de strassen
 
        //P1 = A.(F-H)
        multiplicacaoMatrizesStrassen(matAParte1, subtracaoMatrizes(tamanhoMatrizDividido, matBParte2, matBParte4, rgbSize),
        p1, tamanhoMatrizDividido, rgbSize);
        
        //P2 = (A+B).H
        multiplicacaoMatrizesStrassen(adicaoMatrizes(tamanhoMatrizDividido, matAParte1, matAParte2, rgbSize),
        matBParte4, p2, tamanhoMatrizDividido, rgbSize);
        //P3 = (C+D).E
        multiplicacaoMatrizesStrassen(adicaoMatrizes(tamanhoMatrizDividido, matAParte3, matAParte4, rgbSize),
        matBParte1, p3, tamanhoMatrizDividido, rgbSize);
        //P4 = D.(G-E)
        multiplicacaoMatrizesStrassen(matAParte4, subtracaoMatrizes(tamanhoMatrizDividido, matBParte3, matBParte1, rgbSize),
        p4, tamanhoMatrizDividido, rgbSize);
        //P5 = (A+D).(E+H)
        multiplicacaoMatrizesStrassen(adicaoMatrizes(tamanhoMatrizDividido, matAParte1, matAParte4, rgbSize),
        adicaoMatrizes(tamanhoMatrizDividido, matBParte1, matBParte4, rgbSize), p5, tamanhoMatrizDividido, rgbSize);
        //P6 = (B-D).(G+H)
        multiplicacaoMatrizesStrassen(subtracaoMatrizes(tamanhoMatrizDividido, matAParte2, matAParte4, rgbSize),
        adicaoMatrizes(tamanhoMatrizDividido, matBParte3, matBParte4, rgbSize), p6, tamanhoMatrizDividido, rgbSize);
        //P7 = (A-C).(E-F)
        multiplicacaoMatrizesStrassen(subtracaoMatrizes(tamanhoMatrizDividido, matAParte1, matAParte3, rgbSize),
        adicaoMatrizes(tamanhoMatrizDividido, matBParte1, matBParte2, rgbSize), p7, tamanhoMatrizDividido, rgbSize);

        //Construindo a matriz resultante a partir dos produtos, construindo em 4 partes para junta depois em uma só matriz
        int*** matResultanteP1 = adicaoMatrizes(tamanhoMatrizDividido, subtracaoMatrizes(tamanhoMatrizDividido,
        adicaoMatrizes(tamanhoMatrizDividido, p5, p4, rgbSize), p2, rgbSize), p6, rgbSize);
        int*** matResultanteP2 = adicaoMatrizes(tamanhoMatrizDividido, p1, p2, rgbSize);
        int*** matResultanteP3 = adicaoMatrizes(tamanhoMatrizDividido, p3, p4, rgbSize);
        int*** matResultanteP4 = subtracaoMatrizes(tamanhoMatrizDividido, subtracaoMatrizes(tamanhoMatrizDividido,
        adicaoMatrizes(tamanhoMatrizDividido, p1, p5, rgbSize), p3, rgbSize), p7, rgbSize);
        //int*** matResultanteP4 = adicaoMatrizes(tamanhoMatrizDividido, subtracaoMatrizes(tamanhoMatrizDividido,
        //subtracaoMatrizes(tamanhoMatrizDividido, p3, p1, rgbSize), p5, rgbSize), p1, rgbSize);

        //Juncao das partes
        juntarMatriz(n, matResultanteP1, resultado, 0, 0, rgbSize);
        juntarMatriz(n, matResultanteP2, resultado, 0, tamanhoMatrizDividido, rgbSize);
        juntarMatriz(n, matResultanteP3, resultado, tamanhoMatrizDividido, 0, rgbSize);
        juntarMatriz(n, matResultanteP4, resultado, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        freeMatriz(matAParte1, tamanhoMatrizDividido);
        freeMatriz(matAParte2, tamanhoMatrizDividido);
        freeMatriz(matAParte3, tamanhoMatrizDividido);
        freeMatriz(matAParte4, tamanhoMatrizDividido);
        freeMatriz(matBParte1, tamanhoMatrizDividido);
        freeMatriz(matBParte2, tamanhoMatrizDividido);
        freeMatriz(matBParte3, tamanhoMatrizDividido);
        freeMatriz(matBParte4, tamanhoMatrizDividido);
        freeMatriz(p1, tamanhoMatrizDividido);
        freeMatriz(p2, tamanhoMatrizDividido);
        freeMatriz(p3, tamanhoMatrizDividido);
        freeMatriz(p4, tamanhoMatrizDividido);
        freeMatriz(p5, tamanhoMatrizDividido);
        freeMatriz(p6, tamanhoMatrizDividido);
        freeMatriz(p7, tamanhoMatrizDividido);
        freeMatriz(matResultanteP1, tamanhoMatrizDividido);
        freeMatriz(matResultanteP2, tamanhoMatrizDividido);
        freeMatriz(matResultanteP3, tamanhoMatrizDividido);
        freeMatriz(matResultanteP4, tamanhoMatrizDividido);
    }

    //return resultado;
}
