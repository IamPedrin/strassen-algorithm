//CTCO04 - Projeto e Análise de Algoritmos
//Algoritmo de Strassen - Multiplicação de matrizes aplicado a pixels de uma imagem
//Pedro Luiz de Freitas Silva - 2022014276

#include <stdio.h>
#include <stdlib.h>

struct pixel{
    int rgb[3];
};

typedef struct pixel pixel;

//Função para alocar a matriz na memória
//n - tamanho da matriz quadratica
pixel** alocarMatrizPixels(int n){
    pixel** matriz = (pixel**) malloc(n * sizeof(pixel*));
    for(int i = 0; i < n; i++){
        matriz[i] = (pixel*) malloc(n * sizeof(pixel));
    }
    return matriz;
}

//funcao utilizada realizar de maneira classica a multiplicacao de matrizes
void multiplicaoMatrizesPixelsClassico(pixel** matA, pixel** matB, pixel** matrizResultante, int n, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matrizResultante[i][j].rgb[k] = 0;
                for(int l = 0; l < n; l++){
                    matrizResultante[i][j].rgb[k] += matA[i][l].rgb[k] * matB[l][j].rgb [k];  
                }
            }
        }
    }
}

//funcao utilizada para ler dados para uma matriz
void preencherMatriz(pixel** mat, int n, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                scanf("%d", &mat[i][j].rgb[k]);
            }
        }
    }
}

//funcao utilizada para printar uma matriz
void printMatriz(pixel** mat, int n, int rgbSize){
    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                printf("%d ", mat[i][j].rgb[k]);
            }
        }
        
    }
}

//Função para liberar a matriz da memória
void freeMatriz(pixel** matriz, int n){
    for(int i = 0; i < n; i++){
        free(matriz[i]);
    }
    free(matriz);
}

//Funcao utilizada para dividir um quadradante de uma matriz
void dividirMatriz(int n, pixel** mat, pixel** matrizDividida, int iInicio, int jInicio, int rgbSize){
    int novoTamanho = n/2;

    for(int i = 0, i2 = iInicio; i < novoTamanho; i++, i2++){
        for(int j = 0, j2 = jInicio; j < novoTamanho; j++, j2++){
           for(int k = 0; k < rgbSize; k++){
                matrizDividida[i][j].rgb[k] = mat[i2][j2].rgb[k];
            }
        }
    }
}

//Junta as 4 partes da matriz em uma matriz completa
void juntarMatriz(int n, pixel** matDividida, pixel** matrizCompleta, int iInicio, int jInicio, int rgbSize){
    int novoTamanho = n/2;

    for(int i = 0, i2 = iInicio; i < novoTamanho; i++, i2++){
        for(int j = 0, j2 = jInicio; j < novoTamanho; j++, j2++){
            for(int k = 0; k < rgbSize; k++){
                matrizCompleta[i2][j2].rgb[k] = matDividida[i][j].rgb[k];
            }
        }
    }
}

//Funcao para adição de uma matriz por outra
void adicaoMatrizes(int n, pixel** matA, pixel** matB, pixel** matResultante, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matResultante[i][j].rgb[k] = matA[i][j].rgb[k] + matB[i][j].rgb[k];
            }
        }
    }
}

//Funcao para Subtração de uma matriz por outra
void subtracaoMatrizes(int n, pixel** matA, pixel** matB, pixel** matResultante, int rgbSize){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < rgbSize; k++){
                matResultante[i][j].rgb[k] = matA[i][j].rgb[k] - matB[i][j].rgb[k];
            }
        }
    }
}

/*
    | PARTE 1   PARTE 2 | 
    |                   |
    | PARTE 3   PARTE 4 |

*/
//Funcao utilizada para aplicar a multiplicacao de Strassen de forma recursiva
pixel** multiplicacaoMatrizesStrassen(pixel** matA, pixel**matB, int n, int rgbSize){
    pixel** resultado = alocarMatrizPixels(n);
    int tamanhoMatrizDividido = n/2;
    if(n < 32){
        multiplicaoMatrizesPixelsClassico(matA, matB, resultado, n, rgbSize);
    }else{
        //Dividindo Matriz A em 4
        pixel** matAParte1 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matA, matAParte1, 0, 0, rgbSize);
        pixel** matAParte2 = alocarMatrizPixels(tamanhoMatrizDividido); 
        dividirMatriz(n, matA, matAParte2, 0, tamanhoMatrizDividido, rgbSize);
        pixel** matAParte3 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matA, matAParte3, tamanhoMatrizDividido, 0, rgbSize);
        pixel** matAParte4 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matA, matAParte4, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        //Dividindo Matriz B em 4
        pixel** matBParte1 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matB, matBParte1, 0, 0, rgbSize);
        pixel** matBParte2 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matB, matBParte2, 0, tamanhoMatrizDividido, rgbSize);
        pixel** matBParte3 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matB, matBParte3, tamanhoMatrizDividido, 0, rgbSize);
        pixel** matBParte4 = alocarMatrizPixels(tamanhoMatrizDividido);
        dividirMatriz(n, matB, matBParte4, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);
        
        //Matrizes temporarias para serem utilizadas para chamar as adicoes e subtracoes nos produtos de strassen
        pixel** temp1 = alocarMatrizPixels(tamanhoMatrizDividido);
        pixel** temp2 = alocarMatrizPixels(tamanhoMatrizDividido);

        //Variaveis para receber os resultados das formulas de strassen
        pixel** p1;
        pixel** p2;
        pixel** p3;
        pixel** p4;
        pixel** p5;
        pixel** p6;
        pixel** p7;

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

        //Matrizes das 4 partes que serao juntadas posteriormentes aos produtos de Strassen
        pixel** matResultanteP1 = alocarMatrizPixels(tamanhoMatrizDividido);
        pixel** matResultanteP2 = alocarMatrizPixels(tamanhoMatrizDividido);
        pixel** matResultanteP3 = alocarMatrizPixels(tamanhoMatrizDividido);
        pixel** matResultanteP4 = alocarMatrizPixels(tamanhoMatrizDividido);

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


        //Juncao das 4 partes
        juntarMatriz(n, matResultanteP1, resultado, 0, 0, rgbSize);
        juntarMatriz(n, matResultanteP2, resultado, 0, tamanhoMatrizDividido, rgbSize);
        juntarMatriz(n, matResultanteP3, resultado, tamanhoMatrizDividido, 0, rgbSize);
        juntarMatriz(n, matResultanteP4, resultado, tamanhoMatrizDividido, tamanhoMatrizDividido, rgbSize);

        //Liberando da memoria as matrizes restantes
        freeMatriz(matResultanteP1, tamanhoMatrizDividido);
        freeMatriz(matResultanteP2, tamanhoMatrizDividido);
        freeMatriz(matResultanteP3, tamanhoMatrizDividido);
        freeMatriz(matResultanteP4, tamanhoMatrizDividido);

    }
    return resultado;
}

int main(){
    //Declaração de váriaveis
    pixel** matA;
    pixel** matB;
    pixel** matResultante;
    int n;
    int rgbSize = 3;
    int corMax;
    char formato[2];

    //Leitura dos dados do arquivo
    scanf("%s", formato);
    scanf("%d %d", &n, &n);
    scanf("%d", &corMax);

    //Alocacao da Matriz A, B e Resultante
    matA = alocarMatrizPixels(n);
    matB = alocarMatrizPixels(n);
    
    //Preenchendo Matriz A
    preencherMatriz(matA, n, rgbSize);
    //Preenchendo Matriz B
    preencherMatriz(matB, n, rgbSize);

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

    return 0;
}