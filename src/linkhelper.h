
typedef struct{
    int export; //se o gráfico vai ser exportado
    int lines; //quantidade de linhas
    int help; //1 se for para retornar a ajuda
    int bar; //1 se for barra
    int demo; //1 para executar a demo
    char* fileName; //nome do arquivo (caso seja exportado)
    char* graphTitle; //título do gráfico
    
} Config;

int argParser(int argc, char* argv[], Config* conf);
int errorHandler(int value);