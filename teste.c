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
int preenchecol(int i, int j, int quant, int contcolunas, int **matrix, char **palavras, pilha *dePalavras);
void destruir(int c, char **word);
int preenchelin(int i, int j, int quant, int contLinhas, int **matrix, char **palavras, pilha *dePalavras); 
void zeraLinha(int n, int m, int tam, int **matriz);
void zeraColuna(int n, int m, int tam, int **matriz);


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

    destruir(quant,palavras);

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
    int i, j,m,n, q,r, length, length2, contcolunas, contLinhas, flagColuna, flagLinha;
    pilha *posicoes = cria();
    pilha *dasPalavras = cria();

    char **copiaDePalavras;

    copiaDePalavras = malloc(quant*sizeof(char *));

    for(i=0;i<quant;i++) {
        copiaDePalavras[i] = malloc(MAX*sizeof(char));
    }

    for(i=0;i<quant;i++) {
        length = strlen(palavras[i]);
        for(j=0;j<length+1;j++){
            copiaDePalavras[i][j] = palavras[i][j];
        }
    }

    for(i=0; i<lin; i++){
        for(j=0;j<col;j++) {

            printf("\n");
            printf("%d %d \n", i, j);
            printf("\n");
            
            contcolunas = 0;
            contLinhas = 0;

            flagColuna = 0;
            flagLinha = 0;

            if(matriz[i][j] != -1) {
                contcolunas = contadorDeColunas(i,j,col, matriz);
                contLinhas = contadorDeLinhas(i,j,lin,matriz);
                printf("\n");
                printf("Contcolunas = %d, contLinhas = %d \n",contcolunas , contLinhas);
                printf("\n");
            }

            if(contcolunas > 1) {
                flagColuna = preenchecol(i,j,quant,contcolunas,matriz,copiaDePalavras,dasPalavras);
                printf("\n");
                printf("flagColuna = %d \n", flagColuna);
                printf("\n");
                
            }
            if(contLinhas > 1) {
                flagLinha = preenchelin(i,j,quant,contLinhas,matriz,copiaDePalavras, dasPalavras);
                printf("\n");
                printf("flagLinha = %d \n", flagLinha);
                printf("\n");
            }

            if(flagLinha || flagColuna) {
                /*Irei colocar na pilha a posição da atual posição modificada*/
                printf("\n");
                printf("empilhei = %d %d\n", i,j);
                printf("\n");
                empilha(posicoes, i);
                empilha(posicoes,j);
            } else if(contcolunas>1 || contLinhas>1) {
                /*Backtracking*/
                printf("\n");
                printf("Posição que pediu backtracking = %d %d \n", i, j);
                printf("\n");
                printf("Contcolunas: %d Contlinhas: %d \n", contcolunas, contLinhas);
                printf("\n");
                m =desempilha(posicoes);
                /*Coluna */
                n = desempilha(posicoes);
                /*Linha */

                printf("\n");
                printf("desempilhei = %d %d\n", n,m);
                printf("\n");

                matriz[n][m] = 0;

                if(matriz[n][m] != -1) {
                    contcolunas = contadorDeColunas(n,m,col, matriz);
                    contLinhas = contadorDeLinhas(n,m,lin,matriz);
                }
                if(contcolunas > 1) {
                    zeraLinha(n,m,contcolunas,matriz);

                    
                }  
                if(contLinhas > 1) {
                    zeraColuna(n,m,contLinhas,matriz);
                    
                }
                if(contcolunas > 1)  flagColuna = preenchecol(n,m,quant,contcolunas,matriz,copiaDePalavras,dasPalavras);
                if(contLinhas > 1) flagLinha = preenchelin(n,m,quant,contLinhas,matriz,copiaDePalavras, dasPalavras);

                if(flagLinha) {
                    q = desempilha(dasPalavras);
                    length2 = strlen(palavras[q]);
                    for(r=0;r<length2+1;r++) {
                        copiaDePalavras[q][r] = palavras[q][r];
                    }
                }

                if(flagColuna) {
                    q = desempilha(dasPalavras);
                    length2 = strlen(palavras[q]);
                    for(r=0;r<length2+1;r++) {
                        copiaDePalavras[q][r] = palavras[q][r];
                    }
                }
                i = n;
                j = m; 
                if(m==0 && n==0) {
                    i = 10000;
                    j = 10000;    
                } 
                    
            }
        }
    }
    destroi(posicoes);
    destroi(dasPalavras);
    destruir(quant, copiaDePalavras);
    return 0;
}

void zeraLinha(int n, int m, int tam, int **matriz){
    int i;
    for(i=0;i<tam;i++) {
        matriz[n][m] = 0;
        m++;
    }
}

void zeraColuna(int n, int m, int tam, int **matriz){
    int i;
    for(i=0;i<tam;i++) {
        matriz[n][m] = 0;
        n++;
    }
}


int contadorDeColunas(int i, int j, int col, int **matriz){
    int k, contcolunas=1, flag = 0;

    if(matriz[i][j]==0) flag=1;

    for(k=j+1;k<col;k++){
        if(matriz[i][k]!= -1) {
            contcolunas++;
            if(matriz[i][k] == 0) flag=1;
        }
        if(matriz[i][k]==-1 && flag) return contcolunas;
        else if(matriz[i][k]==-1 && !flag) {
            contcolunas = 1;
            return contcolunas;
        }
    }
    if(flag) return contcolunas;
    contcolunas = 1;
    return contcolunas;
}


int contadorDeLinhas(int i, int j, int lin, int **matriz){
    int k, contLinhas=1, flag=0;

    if(matriz[i][j]==0) flag=1;

    for(k=i+1;k<lin;k++){
        if(matriz[k][j]!=-1) {
            contLinhas++;
            if(matriz[k][j] == 0) flag=1;
        }
        if(matriz[k][j]==-1 && flag) return contLinhas;
        else if(matriz[k][j]==-1 && !flag){
            contLinhas = 1;
            return contLinhas;
        }
    }

    if(flag) return contLinhas;
    contLinhas = 1;
    return contLinhas;
}

int preenchecol(int i, int j, int quant, int contcolunas, int **matrix, char **palavras, pilha *dePalavras) {
    int h, l, m, length, x, fits;

    l = 0;
    for(h=0;h<quant;h++) {
        fits = 1;
        x=j;
        length = strlen(palavras[h]);
        l++;
        
        if(contcolunas == length) {
            for(m=0;m<length && fits;m++){
                if(matrix[i][x] != 0 && matrix[i][x] != palavras[h][m]) {
                    fits = 0;
                }
                x++;
            } 
            x=j;
            for(m=0;m<length && fits;m++){
                matrix[i][x] = palavras[h][m];
                x++;
                if(m == length-1){
                    empilha(dePalavras,h);
                    /*Eu acredito que nesse momento eu preciso apagar a palavra da lista de palavras, então;*/
                    palavras[h][0] = '\0';
                    printmat(5,4,matrix);
                    printf("\n");
                    return 1;
                    /*Retorno 1 caso consiga preencher a palavra*/
                }
            }
        }
    }
    return 0;
    /*Retorno 0 caso não consiga preencher a palavra*/
}

int preenchelin(int i, int j, int quant, int contLinhas, int **matrix, char **palavras, pilha *dePalavras) {
    int h, l, m, length, x, fits;
    

    l = 0;
    for(h=0;h<quant;h++) {
        fits = 1;
        x=i;
        length = strlen(palavras[h]);
        l++;
        
        if(contLinhas == length) {
            for(m=0;m<length && fits;m++) {
                if(matrix[x][j] != 0 && matrix[x][j] != palavras[h][m]) {
                    fits = 0;
                }
                x++;
            }
            x=i;
            for(m=0;m<length && fits;m++){
                matrix[x][j] = palavras[h][m];
                x++;
                if(m == length-1){
                    empilha(dePalavras,h);
                    palavras[h][0] = '\0';
                    printmat(5,4,matrix);
                    printf("\n");
                    return 1;
                    /*Retorno 1 caso consiga preencher a palavra*/
                }
            }
        }
    }

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