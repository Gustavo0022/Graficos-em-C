#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "linkhelper.h"


//dado com titulo
typedef struct Dado{
    char nome[10];
    float valor;
} dado;

//exibe texto de ajuda
void help(){
    printf("Sintaxe:\n");
    printf("testeGraficos [argumento] [tituloDoGrafico] [numeroDeLinhas] \n");
    printf("Argumentos suportados: -e (exportar como um arquivo)(apenas de linha), -b (grafico de barra), -l (grafico de linha) [-i (inserir dados na execucao) -d (demo)]\n");
    printf("Máximo de linhas suportadas: 5\n");
}

void inserirDados(dado lista[], int tamanho){
    for(int i=0; i<tamanho; i++){
        printf("Insira o nome da linha (max 10 caracteres):");
        scanf("%s", &lista[i].nome);
        printf("Insira o valor da linha:");
        scanf("%f", &lista[i].valor);
    }

    dado aux;
    for(int i=0; i<tamanho-1; i++){
        for(int j = i+1; j<tamanho; j++){
            if(lista[i].valor<lista[j].valor){
                aux = lista[i];
                lista[i] = lista[j];
                lista[j] = aux;
            }
        }
    }
}

void plotaLinha(float valor){
    for(int j = 0; j<(valor);j++){
            printf("#");
        }
}


void plotGraficoLinha(char* titulo, dado *dados, int quantDados){
    //char grafico[13][35];
    //imprime o titulo do grafico
    for(int i =0; i<36-(strlen(titulo)); i++){
        printf(" ");
    }
    printf("%s\n", titulo);

    //plota o gráfico
    for(int i =0; i<quantDados;i++){

        printf("%10s|",dados[i].nome);

        float numeroDeRepresentacao = (dados[i].valor * 50)/dados[0].valor;
        
        plotaLinha(numeroDeRepresentacao);
        printf(" %.2f\n          |",dados[i].valor );
        plotaLinha(numeroDeRepresentacao);
        printf("\n          |\n");
    }
    printf("          ----------------------------------------------------------\n");

}

void plotaGraficoBarra(char* titulo, dado* dados, int quantDados ){
    for(int i =0; i<20-(strlen(titulo)); i++){
        printf(" ");
    }
    printf("%s\n", titulo);

    float dadosNormalizados[8];

    for(uint16_t i = 0; i<quantDados; i++){
        dadosNormalizados[i] = (dados[i].valor*20)/dados[0].valor; 
    }

    for(int i =20; i>=0;i--){

        printf("| ");

        for(uint16_t j = 0; j<quantDados; j++){
            
            if(dadosNormalizados[j] >= i){
                printf(" ##### ");
            }
        }
        printf("\n");
    }

    for(uint16_t i = 0; i<(quantDados*8)+2;i++){
        printf("-");
    } 
    printf("\n  ");

    for(uint16_t i = 0; i<quantDados; i++){
        printf(" %.2f ", dados[i].valor);
    }

   
    printf("\n  ");
    for(uint16_t i = 0; i< quantDados; i++){

        if(strlen(dados[i].nome) > 5){
            printf("%c%c%c%c%c", dados[i].nome[0],
                dados->nome[1],dados[i].nome[2],
                dados->nome[3],dados[i].nome[4]);
        }
        else{
            printf(" %s ", dados[i].nome);
        }
    }
    printf("\n ");

    for(uint16_t i = 0; i< quantDados; i++){
        if(strlen(dados[i].nome) > 5){
            int j = 5;
            while(j< strlen(dados[i].nome)){
                printf("%c", dados[i].nome[j]);
                j++;
            }
        }
        else{
            printf("\t");
        }
    }


}

void salvarArquivo(char* nomeArquivo,char* titulo,dado* dados,int quantDados){
        FILE *arquivo;
        strcat(nomeArquivo,".txt");
        arquivo = fopen(nomeArquivo, "a");

        if (arquivo == NULL){
            printf("Ocorreu um erro ao abrir o arquivo :(\n");
            printf("Saindo...\n");
            return;
        }

        for(int i =0; i<42-(strlen(titulo)/2); i++){
            fprintf(arquivo," ");
        }
        
        fprintf(arquivo,"%s\n", titulo);
        

        for(int i =0; i<quantDados;i++){
            fprintf(arquivo,"%10s|",dados[i].nome);

            float numeroDeRepresentacao = (dados[i].valor * 100)/dados[0].valor;

            for(int j = 0; j<(numeroDeRepresentacao);j++){
                fprintf(arquivo,"#");
            }
            fprintf(arquivo," %.2f\n          |",dados[i].valor );
            for(int j = 0; j<(numeroDeRepresentacao);j++){
                fprintf(arquivo,"#");
            }

            fprintf(arquivo,"\n          |\n");
        }

        fprintf(arquivo,"          ----------------------------------------------------\n");
        fclose(arquivo);

}

int main(int argc, char ** argv){
    
    /* alocação dinâmica do gráfico (bicho grande)
    char **grafico;

    grafico = calloc(40+(atoi(argv[1])*2), sizeof(char*));

    for(int i =0; i<40; i++){
        grafico[i] = calloc(20,sizeof(char));
    }
    */
    Config* conf = malloc(sizeof(Config));
    conf->export = 0;
    conf->bar = 0;
    conf->demo = 0;
    conf->help = 0;
    conf->lines = 0;
    conf->fileName = NULL;
    conf->graphTitle = NULL;
    if(errorHandler(argParser(argc,argv,conf))) return 1;

    dado* dados = malloc(sizeof(dado)*conf->lines);

    inserirDados(dados,conf->lines);

    if(conf->export == 1){
        salvarArquivo(conf->fileName,conf->graphTitle,dados,conf->lines);
    }

    if(!conf->graphTitle){
        printf("ERRO FATAL: Sem título do gráfico");
        return 1;
    }
    
    if(conf->bar){
        plotaGraficoBarra(conf->graphTitle,dados,conf->lines);
        return 0;
    }
    plotGraficoLinha(conf->graphTitle,dados,conf->lines);

}
