#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#define MAX 256

int **lematriz(int lin, int col);
void printmat(int lin, int col, int **mat);
char **lepalavras(int quant);
void teste(char **testing);
int tabuleiro(int lin, int col, int quant, int **matriz, char **palavras);
int contadorDeColunas(int i, int j, int col, int **matriz);
int contadorDeLinhas(int i, int j, int lin, int **matriz);
int preenchecol(int i, int j, int quant, int contcolunas, int **matrix, char **palavras);
void destruir(int c, char **word);
int preenchelin(int i, int j, int quant, int contLinhas, int **matrix, char **palavras); 


int main() {
    int lin,col, quant;
    int **matr;
    char **palavras;
    

    printf("Digite a quantidade de linhas e colunas: \n");
    scanf("%d %d", &lin, &col);

    matr = lematriz(lin, col);
    printmat(lin, col, matr);

    printf("Digite a quantidade de palavras: \n");
    scanf("%d", &quant);
    palavras = lepalavras(quant);
    

    tabuleiro(lin,col,quant,matr,palavras);

    return 0;
}


char **lepalavras(int quant){
    int i;
    char **words;

    words = malloc(quant*sizeof(char *));

    for(i=0;i<quant;i++) {
        words[i] = malloc(MAX*sizeof(char));
    }

    for(i=0;i<quant;i++){
        scanf("%s", words[i]);
        
    }
   

    return words;
}



int **lematriz(int lin, int col){
    int i, j;
    int **mat;

    mat = malloc(lin*sizeof(int *));

    for(i=0;i< lin; i++){
        mat[i] = malloc(col*sizeof(int));

    }

    for(i=0;i<lin;i++) {
        for(j=0;j<col;j++) {
            scanf("%d", &mat[i][j]);
        }
    }

    return mat;

}

void printmat(int lin, int col, int **mat) {
    int i, j;

    for(i=0;i<lin; i++) {
        for(j=0;j<col;j++) {
            printf(" %c ", mat[i][j]);
        }
        printf("\n");
    }
}

int tabuleiro(int lin, int col, int quant, int **matriz, char **palavras) {
    int i, j, contcolunas, contLinhas;
    /*pilha * posicoes = cria();*/

    for(i=0; i<lin; i++){
        for(j=0;j<col;j++) {
            contcolunas = 0;
            contLinhas = 0;
            /*
            flagColuna = 0;
            flagLinha = 0;
            */
            if(matriz[i][j] == 0) {
                contcolunas = contadorDeColunas(i,j,col, matriz);
                contLinhas = contadorDeLinhas(i,j,lin,matriz);
            }
            if(contcolunas > 1) {
                preenchecol(i,j,quant,contcolunas,matriz,palavras);
                
            }
            if(contLinhas > 1) {
                preenchelin(i,j,quant,contLinhas,matriz,palavras);
            }
            /*
            if(flagLinha || flagColuna) {
                Irei colocar na pilha a posição da atual posição modificada
                empilha(posicoes, i);
                empilha(posicoes,j);
            }
            */

        }
    }
    return 0;
}

int contadorDeColunas(int i, int j, int col, int **matriz){
    int k, contcolunas=0;
    for(k=j;k<col;k++){
        if(matriz[i][k]!=-1) contcolunas++;
        if(matriz[i][k]==-1) return contcolunas;
    }
    return contcolunas;
}


int contadorDeLinhas(int i, int j, int lin, int **matriz){
    int k, contLinhas=0;
    for(k=i;k<lin;k++){
        if(matriz[k][j]!=-1) contLinhas++;
        if(matriz[k][j]==-1) return contLinhas;
    }
    return contLinhas;
}

int preenchecol(int i, int j, int quant, int contcolunas, int **matrix, char **palavras) {
    int h, l, m, length;

    l = 0;
    for(h=0;h<quant;h++) {
        length = strlen(palavras[h]);
        l++;
        
        if(contcolunas == length) {
            /*
            o=j;
            for(n=0;n<length;n++) {
                if(matrix[i][o] != 0 && matrix[i][o] != palavras[h][n]);
                o++;
            }
            */
            for(m=0;m<length;m++){
                matrix[i][j] = palavras[h][m];
                j++;
                if(m == length-1){
                    printmat(3,3,matrix);
                    return 1;
                    /*Retorno 1 caso consiga preencher a palavra*/
                }
            }
        }
    }
    printmat(3,3, matrix);
    return 0;
    /*Retorno 0 caso não consiga preencher a palavra*/
}

int preenchelin(int i, int j, int quant, int contLinhas, int **matrix, char **palavras) {
    int h, l, m, length;


    l = 0;
    for(h=0;h<quant;h++) {
        length = strlen(palavras[h]);
        l++;
        
        if(contLinhas == length) {
            for(m=0;m<length;m++){
                matrix[i][j] = palavras[h][m];
                i++;
                if(m == length-1){
                    printmat(3,3,matrix);
                    return 1;
                    /*Retorno 1 caso consiga preencher a palavra*/
                }
            }
        }
    }
    printmat(3,3, matrix);
    return 0;
    /*Retorno 0 caso não consiga preencher a palavra*/
}


void destruir(int c, char **word){
    int i;
    for(i=0;i<c;i++){
        free(word[i]);
    }
    free(word);

}
