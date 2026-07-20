#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ERROR_MISSING_ARG 1
#define ERROR_GRAPH_NAME 2
#define ERROR_MISSING_LINE 3
#define ERROR_UNKNOWN_ARG 4

typedef struct{
    int export; //se o gráfico vai ser exportado
    int lines; //quantidade de linhas
    int help; //1 se for para retornar a ajuda
    int bar; //1 se for barra
    int demo; //1 para executar a demo
    char* fileName; //nome do arquivo (caso seja exportado)
    char* graphTitle; //título do gráfico
    
} Config;

int argParser(int argc, char* argv[], Config* conf){
    
    if (argc == 1) {
        return ERROR_MISSING_ARG;
    }

    if (argc == 2) {
        if (!strcmp(argv[1], "-help")) {
            conf->help = 1;
            return 0; // Sucesso, pediu ajuda
        } else {
            return ERROR_MISSING_ARG;
        }
    }

    for(int i = 1; i< argc; i++ ){
        
        if(!strcmp(argv[i],"-e")){
            if(argc > i+1 && argv[i+1][0] != '-'){
                conf->fileName = malloc(strlen(argv[i+1])+1);
                strcpy(conf->fileName, argv[i+1]);
                i++;
                conf->export = 1;
            }
            else return ERROR_GRAPH_NAME;
        }
        else if(!strcmp(argv[i],"-t")){
            if(argc > i+1 && argv[i+1][0] != '-'){
                conf->graphTitle = malloc(strlen(argv[i+1])+1);
                strcpy(conf->graphTitle, argv[i+1]);
                i++;
            }
            else return ERROR_GRAPH_NAME;
        }
        else if(!strcmp(argv[i],"-n")){
            if(argc > i+1){
                conf->lines = atoi(argv[i+1]);
                i++;
            }
            else return ERROR_MISSING_LINE;
        }
        else if(!strcmp(argv[i],"-b")){
            conf->bar = 1;
        }
        else if(!strcmp(argv[i], "-d")){
            conf->demo = 1;
        }
        else {
            return ERROR_UNKNOWN_ARG; 
        }
    }
    return 0;
}

int argParseTest(int argc, char* argv[]){
    Config* conf = malloc(sizeof(Config));
    conf->bar = 0;
    conf->demo = 0;
    conf->help = 0;
    conf->lines = 0;
    conf->fileName = NULL;
    conf->graphTitle = NULL;

    int code = argParser(argc,argv,conf);

    if(conf->graphTitle != NULL){
        printf("Titulo do grafico: %s\n", conf->graphTitle);
    }
    if(conf->fileName != NULL){
        printf("Nome do arquivo: %s\n",conf->fileName);
    }
    printf("Modo Selecionado:");
    if(conf->bar == 0){
        printf("linhas\n");
    }
    else if(conf->bar == 1){
        printf("barras\n");
    }
    printf("Demo: %d\n", conf->demo);
    printf("Quantidade de linhas: %d\n", conf->lines);
    printf("Ajuda: %d\n", conf->help);
    printf("Erro: %d\n", code);
}