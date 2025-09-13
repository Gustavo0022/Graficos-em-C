#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

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

void plotaBarra(float valor){

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
        
        plotaBarra(numeroDeRepresentacao);
        printf(" %.2f\n          |",dados[i].valor );
        plotaBarra(numeroDeRepresentacao);
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

void salvarArquivo(char* titulo,dado* dados,int quantDados){
        FILE *arquivo;
        char nome[20];
        printf("Digite o nome do arquivo para exportar: ");
        scanf("%s", &nome);
        strcat(nome,".txt");
        arquivo = fopen(nome, "a");

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


  

    if(argc < 3){

        if(argc < 2 /* || strcmp(argv[1],"-l") || strcmp(argv[1],"-b")*/){
            printf("Consulte 'testeGraficos help'\nSaindo...\n");
		    return 1;
        }

        else if(!strcmp(argv[1],"help")){
        help();
        return 0;
        }

		
	}
	
    if(!strcmp(argv[1],"-e")){
        
        int numeroDados = atoi(argv[3]);
        dado listaDados[numeroDados];
        inserirDados(listaDados,numeroDados);
        plotGraficoLinha(argv[2],listaDados,numeroDados);
        salvarArquivo(argv[2],listaDados,numeroDados);
        return 0;
    }
    
    int numeroDados = atoi(argv[3]);

    dado listaDados[numeroDados];

    inserirDados(listaDados,numeroDados);

    if(!strcmp(argv[1],"-l")){
        plotGraficoLinha(argv[2], listaDados, numeroDados);
    }
    if(!strcmp(argv[1],"-b")){
        plotaGraficoBarra(argv[2], listaDados, numeroDados);
    }
    

    /* for(int i = 0; i<13;i++){
        for(int j = 0; j<35;j++ ){
            printf("[%d]",j);
        }
        printf("\n");
    } */
}
