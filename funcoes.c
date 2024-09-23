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
            printf(" ");
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