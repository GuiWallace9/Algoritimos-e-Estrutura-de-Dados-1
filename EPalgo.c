#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pilha.h"
#define MAX 256

int **lematriz(int lin, int col, FILE *arq);
void printmat(int lin, int col, int **mat);
char **lepalavras(int quant, FILE *arq);
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
    FILE *arq;
    char filename[256];
    int lin = 1,col = 1, quant, flag;
    int **matr;
    char **palavras;
    printf("Digite o nome do arquivo de entrada: \n");
    printf("\n");
    scanf("%s", filename);
    printf("\n");

    arq = fopen(filename, "r");
    
    
    while(lin != 0 && col != 0) {
        printf("Digite a quantidade de linhas e colunas: \n");
        fscanf(arq, "%d %d", &lin, &col);
        printf("%d %d \n", lin, col);
        printf("\n");
        /*scanf("%d %d", &lin, &col);*/

        if(lin != 0 && col != 0) {
            matr = lematriz(lin, col, arq);
            printmat(lin, col, matr);

            printf("Digite a quantidade de palavras: \n");
            fscanf(arq, "%d", &quant);
            /*scanf("%d", &quant);*/
            palavras = lepalavras(quant, arq);
            

            flag = tabuleiro(lin,col,quant,matr,palavras);
            if(flag) printf("Deu certo \n");
            else printf("Não deu certo \n");

            destruir(quant,palavras);
        }
    }

    return 0;
}

char **lepalavras(int quant, FILE *arq){
    int i;
    char **words;

    words = malloc(quant*sizeof(char *));

    for(i=0;i<quant;i++) {
        words[i] = malloc(MAX*sizeof(char));
    }

    for(i=0;i<quant;i++){
        fscanf(arq, "%s", words[i]);
        /*scanf("%s", words[i]);*/
        
    }

    return words;
}


int **lematriz(int lin, int col, FILE *arq){
    int i, j;
    int **mat;

    mat = malloc(lin*sizeof(int *));

    for(i=0;i< lin; i++){
        mat[i] = malloc(col*sizeof(int));

    }

    for(i=0;i<lin;i++) {
        for(j=0;j<col;j++) {
            fscanf(arq, "%d", &mat[i][j]);
            /*scanf("%d", &mat[i][j]);*/
        }
    }

    return mat;

}

void printmat(int lin, int col, int **mat) {
    int i, j;

    for(i=0;i<lin; i++) {
        for(j=0;j<col;j++) {
            if(mat[i][j]==0) printf(" - ");
            else if(mat[i][j]==-1) printf(" * " );
            else printf(" %c ", mat[i][j]);
        }
        printf("\n");
    }
}

int tabuleiro(int lin, int col, int quant, int **matriz, char **palavras) {
    int z, i, j,m,n, q,r, length, length2, flag, contcolunas, desemp, contLinhas, flagColuna, flagLinha, backtracking;
    pilha *posicoes = cria();
    pilha *dasPalavras = cria();
    pilha *regulador = cria();

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
                if(flagColuna) {
                    printmat(lin,col,matriz);
                    printf("\n");

                }
             
                printf("\n");
                printf("flagColuna = %d \n", flagColuna);
                printf("\n");
            }
            if(contLinhas > 1) {
                flagLinha = preenchelin(i,j,quant,contLinhas,matriz,copiaDePalavras, dasPalavras);
                if(flagLinha) {
                    printmat(lin,col,matriz);
                    printf("\n");

                }
                printf("\n");
                printf("flagLinha = %d \n", flagLinha);
                printf("\n");
            }
            printf("\n");

            for(z=0;z<quant;z++){
                printf("Copia: %s \n", copiaDePalavras[z]);
                printf("Oficial: %s \n", palavras[z]);
            }

            printf("\n");
            if((flagLinha==1 && flagColuna==0) || (flagLinha==0 &&flagColuna==1)) {
                desemp = desempilha(regulador);
                q = desempilha(dasPalavras);
                length2 = strlen(palavras[q]);
                printf("O QUE DESEMPILHOU? %d \n", q);
                for(r=0;r<length2+1;r++) {
                    printf("\nAQUI1\n");
                    copiaDePalavras[q][r] = palavras[q][r];
                }
            }

            if(contLinhas > 1 && !flagLinha) flagColuna =0;
            if(contcolunas > 1 && !flagColuna) flagLinha =0;
            if(flagLinha  || flagColuna) {
                /*Irei colocar na pilha a posição da atual posição modificada*/
            
                printf("\n");
                printf("empilhei = %d %d\n", i,j);
                printf("\n");
            
                if(flagLinha && flagColuna) empilha(regulador,2);
                else empilha(regulador,1);

                empilha(posicoes, i);
                empilha(posicoes,j);

            } else if(contcolunas>1 || contLinhas>1) {
                /*Backtracking*/
                backtracking = 1;
                while(backtracking) {
                    printf("\n");
                    printf("Posição que pediu backtracking = %d %d \n", i, j);
                    printf("\n");
                    printf("Contcolunas: %d Contlinhas: %d \n", contcolunas, contLinhas);
                    printf("\n");
                    desemp=0;
        
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
                    if(flagColuna) {
                        printf("Print de BACKTRACKING \n");
                        printmat(lin,col,matriz);
                        printf("\n");

                    }                
                    if(contLinhas > 1) flagLinha = preenchelin(n,m,quant,contLinhas,matriz,copiaDePalavras, dasPalavras);
                    if(flagLinha) {
                        printf("Print de BACKTRACKING \n");
                        printmat(lin,col,matriz);
                        printf("\n");

                    }
                    desemp = desempilha(regulador);
                    if(desemp == 1){
                        q = desempilha(dasPalavras);
                        length2 = strlen(palavras[q]);
                        printf("O QUE DESEMPILHOU? %d \n", q);
                        for(r=0;r<length2+1;r++) {
                            printf("\nAQUI1\n");
                            copiaDePalavras[q][r] = palavras[q][r];
                        }     
                    } else if(desemp == 2){
                        while(desemp>0){
                            q = desempilha(dasPalavras);
                            length2 = strlen(palavras[q]);
                            for(r=0;r<length2+1;r++) {
                                printf("\nAQUI2\n");
                                copiaDePalavras[q][r] = palavras[q][r];
                            }
                            desemp--;
                        }
                    }
                    printf("DENTRO DO BACKTRACK; \n");
                    for(z=0;z<quant;z++){
        
                        printf("Copia: %s \n", copiaDePalavras[z]);
                        printf("Oficial: %s \n", palavras[z]);
                    }


                    
/*
                    if(flagLinha) {
                        q = desempilha(dasPalavras);
                        length2 = strlen(palavras[q]);
                        for(r=0;r<length2+1;r++) {
                            printf("\nAQUI1\n");
                            copiaDePalavras[q][r] = palavras[q][r];
                        }

                    }*/

/*
                    if(flagColuna) {
                        q = desempilha(dasPalavras);
                        length2 = strlen(palavras[q]);
                        for(r=0;r<length2+1;r++) {
                            printf("\nAQUI2\n");
                            copiaDePalavras[q][r] = palavras[q][r];
                        }
                    }*/
                    i = n;
                    j = m; 
                    if(m==0 && n==0) {
                        i = 10000;
                        j = 10000;    
                    } 
                    if(pilhaVazia(posicoes)) backtracking=0;
                }

            }
        }
    }
    for(i=0;i<quant;i++){
        length = strlen(copiaDePalavras[i]);
        if(length == 0) {
            flag = 0;
        }
    }
    if(!flag) return 0;
    

    destroi(posicoes);
    destroi(dasPalavras);
    destroi(regulador);
    destruir(quant, copiaDePalavras);
    return 1;
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
                    /*Eu acredito que nesse momento euCopia: ad 
Oficial: ad  preciso apagar a palavra da lista de palavras, então;*/
                    palavras[h][0] = '\0';
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