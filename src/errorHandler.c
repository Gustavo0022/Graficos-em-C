#include <stdio.h>

int errorHandler(int value){
    switch(value){
        case 0:
            return 0;
        case 1:
            printf("Erro: Argumentos ausentes na execução.  Utilize '-help' para ver argumentos\n");
            return 1;
        case 2:
            printf("Erro: Nome do gráfico ou do arquivo ausente.\n");
            return 1;
        case 3:
            printf("Erro: Quantidade de linhas ausente.\n");
            return 1;
        case 4:
            printf("Erro: 1 ou mais argumentos desconhecidos.  Utilize '-help' para ver argumentos\n");
            return 1;
        default: return 0;
    }
}