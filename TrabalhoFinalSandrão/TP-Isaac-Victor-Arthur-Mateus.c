#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Nome: Isaac Portela Da Silva
 *Matricula: 20192004900
 *Nome: Arthur Gustavo
 *Matricula: 20192004599
 *Nome: Victor Wilson
 *Matricula:20191018271 
 *Nome: Mateus Leal
 *Matricula: 20192020340
 *Descricao: O Programa abre um arquivo , resgata desse arquivo as linhas com informações começadas
com a palavra ATOM e armazena em uma lista encadeada .
 */
    /*
 4) Crie uma struct para armazenar os dados de cada átomo: 
                        a) Número que o identifica
                        b) O nome do átomo (N, CA, C, O, CB, SG, etc)
                        c) O nome do aminoácido (GLY, CYS, SER, etc)
                        d) As coordenadas atômicas X, Y, Z - colunas 7, 8 e 9
                        */
 typedef struct propriedades
 {
   int num;
   char nome[6];
   char aminoacido[6];
   float x ;
   float y;
   float z;
   struct propriedades *prox;
 }ATOM;
 typedef struct aux{
     char atomo[6];
     int quantos;
 }quantidade;
 typedef struct aminoacidos{
     char  aminoacido[6];
     int quantidade;
 }quant;

 int abrirArq(FILE ** pont , char * nome , char  *abertura);
int listaencadea(ATOM **lista , FILE **pont);
void Listar(ATOM **lista);
int Menu(ATOM **lista,char *arquivo,int qtd,int total_amino);
void Saida(ATOM **lista,char *arquivo);
void dados(ATOM **lista,int numero);
void dados_tipo(ATOM **lista,char *nome);
void tipoatomos(ATOM **lista, int qtd);
 void tipoaminoaciados(ATOM **lista , int qts);
 int  Total_Aminoacidos(char *arquivo , char *entrada,int qtd);
 /*
 1) Leia do prompt de comando os nomes dos arquivos de entrada e saída. 
Por exemplo: ./TP-Sandro entrada.pdb saida.txt
 */
int main(int argc , char *argv[]){
     FILE *pont_arq;
     int verifica;
     int teste;
     int total_aminoacidos;
    ATOM *lista;
    int cont;
    lista = NULL;
    if(argc!=3){
         printf("Erro! , poucos parametros passados na linha de comando\n");
         exit(0);
    }
    /* 2) Abra o arquivo de entrada e leia a quantidade (N) de linhas do arquivo 
    que iniciem pela palavra ATOM. O arquivo de entrada é um arquivo que 
    contém a estrutura tridimensional de uma proteína, como pode ser visto
     a seguir. As linhas iniciadas por ATOM contém informações sobre cada
      átomo que compõe e proteína.
    */
    verifica = abrirArq(&pont_arq,argv[1],"r");
    if(verifica==1){
            printf("Erro na alocação ! \n ");
            exit(1);
    }
    cont = listaencadea(&lista,&pont_arq);
    fclose(pont_arq);
        //3) Imprima na tela a quantidade total de átomos presentes no arquivo.
       printf("Quantidade total de átomos presentes no arquivo: %d\n",cont);
       total_aminoacidos = Total_Aminoacidos(argv[1],"r",cont);
       while(teste!=1){
           teste = Menu(&lista,argv[2],cont,total_aminoacidos);
       }
    return 0;
}

int abrirArq(FILE **pont , char * nome , char * abertura){
    *pont = fopen(nome,abertura);
    if(*pont!=NULL){
        return 0;
    }
    return 1;
}
int listaencadea(ATOM **lista , FILE **pont){
    char linha[2000];
    int cont=0;
    char int_1;
    int int_2;
    float int_3 , int_4;
    char int_5;
    ATOM *dados;
    ATOM *aux;
     
        while(fgets(linha,sizeof(linha),*pont)!=NULL){
                if( linha[0]=='A' &&  linha[1]=='T' && linha[2]=='O' && linha[3]=='M'){
                    cont++;
                    /*
                    5) Crie uma lista encadeada para os átomos que forem lidos do arquivo, 
                    a partir da struct criada anteriormente, fazendo a alocação dinâmica 
                    dos elementos da lista à medida que forem lidos.
                    */
                    dados = (ATOM *) malloc(sizeof(ATOM));
                    if(dados!=NULL){
                             sscanf(linha,"%*s %d %s %s %c %d %f %f %f %f %f %c",&dados->num,dados->nome,dados->aminoacido,&int_1,&int_2,&dados->x,&dados->y,&dados->z,&int_3,&int_4,&int_5);
                            dados->prox = NULL;
                            if(*lista==NULL){
                            *lista = dados;  
                      }
                      else{
                          aux = *lista;
                          while(aux->prox!=NULL)
                          aux = aux->prox;
                            aux->prox = dados;
                      }
                  }
             }   
     }
        return cont;
}
void Listar(ATOM **lista){
    ATOM *aux;
    aux = *lista;
    while(aux!=NULL){
        printf("%d %s %s %f %f %f\n",aux->num,aux->nome,aux->aminoacido,aux->x,aux->y,aux->z);
        aux = aux->prox;
    }
}
void Saida(ATOM **lista,char *arquivo){
    FILE *saida;
    ATOM *aux;
    aux = *lista;
    saida = fopen(arquivo,"w");
    
     while(aux!=NULL){
        fprintf(saida,"%d %s %s %f %f %f\n",aux->num,aux->nome,aux->aminoacido,aux->x,aux->y,aux->z);
        aux = aux->prox;
    }
    fclose(saida);

}
void tipoatomos(ATOM **lista,int qtd){  
   quantidade atomos[qtd];
   int j;
   int verifica;
   int i=0;
   int k;
   int x,y;
   int value_2;
   char value[6];
   int aux_i=0;
   ATOM *aux_tipo;
   aux_tipo = *lista;
   for(j=0;j<qtd;j++){
    atomos[j].quantos = 1;
   }
   while (aux_tipo!=NULL)
   {
       verifica=1;
        i = aux_i - 1;
       while(i>=0){
           if(strcmp(atomos[i].atomo,aux_tipo->nome)==0){
                atomos[i].quantos++;
                verifica = 0;
           }
           i--;
       }
       if(verifica==1){
               strcpy(atomos[aux_i].atomo,aux_tipo->nome);
               aux_i++;
       }
      aux_tipo = aux_tipo->prox;
   }
   // Ordenando por insertion sort
   for(x=1; x<aux_i;x++){
            strcpy(value,atomos[x].atomo);
            value_2 = atomos[x].quantos;
            for(y=x-1;y>=0 && strcmp(atomos[y].atomo , value)>0;y--){
                    strcpy( atomos[y+1].atomo ,atomos[y].atomo);
                    atomos[y+1].quantos = atomos[y].quantos;

            }
            strcpy(atomos[y+1].atomo , value);
            atomos[y+1].quantos =value_2;
        }
   
       for(k=0;k<aux_i;k++){
           printf("%s: %d\n",atomos[k].atomo,atomos[k].quantos);
       }
   
   
 }
//f) Listar os dados de um átomo específico, buscando pelo seu número informado pelo usuário.
void dados(ATOM **lista,int numero){
    ATOM *aux;
    aux = *lista;
    while (aux!=NULL)
    {
        if(numero==aux->num){
            printf("%d %s %s %f %f %f\n",aux->num,aux->nome,aux->aminoacido,aux->x,aux->y,aux->z);
        }
        aux = aux->prox;
    }
    
}   
//  g) Listar os dados de todos os átomos que tenham o mesmo tipo (N, CA, C, O, CB, SG, etc) informado pelo usuário.

void dados_tipo(ATOM **lista,char *nome){
    ATOM *aux;
    aux = *lista;
    while (aux!=NULL)
    { 
        if(strcmp(nome ,aux->nome)==0){
            printf("%d %s %s %f %f %f\n",aux->num,aux->nome,aux->aminoacido,aux->x,aux->y,aux->z);
        }
        aux = aux->prox;
    }
}
void tipoaminoaciados(ATOM **lista , int qtd){

    quant amino[qtd];
   int j;
   int verifica;
   int i=0;
   int k;
   int aux_i=0;
   int x,y;
   char value[6];
   int value_2;
   ATOM *aux_tipo;
   aux_tipo = *lista;
   for(j=0;j<qtd;j++){
    amino[j].quantidade = 1;
   }
   while (aux_tipo!=NULL)
   {
       verifica=1;
        i = aux_i - 1;
       while(i>=0){
           if(strcmp(amino[i].aminoacido,aux_tipo->aminoacido)==0){
                amino[i].quantidade++;
                verifica = 0;
           }
           i--;
       }
       if(verifica==1){
               strcpy(amino[aux_i].aminoacido,aux_tipo->aminoacido);
               aux_i++;
       }
      aux_tipo = aux_tipo->prox;
   }
        // Ordenando por insertion sort
        for(x=1; x<aux_i;x++){
            strcpy(value,amino[x].aminoacido);
            value_2 = amino[x].quantidade;
            for(y=x-1;y>=0 && strcmp(amino[y].aminoacido , value)>0;y--){
                    strcpy( amino[y+1].aminoacido , amino[y].aminoacido);
                    amino[y+1].quantidade = amino[y].quantidade;

            }
            strcpy(amino[y+1].aminoacido , value);
            amino[y+1].quantidade =value_2;
        }
         for(k=0;k<aux_i;k++){
           printf("%s: %d\n",amino[k].aminoacido,amino[k].quantidade);
       }
   
        
   
}
 int  Total_Aminoacidos(char *arquivo , char *entrada,int qtd){
     int lx_1;
     int i=0;
     int j;
     int contador = 1;
     char lx2[6],lx3[2];
     float lx4,lx5,lx6,lx7,lx8;
     char lx9[4];
     char linha[2000];
     quant total[qtd];
     FILE *pont;
     abrirArq(&pont,arquivo,entrada);
        while(fgets(linha,sizeof(linha),pont)!=NULL){
                if( linha[0]=='A' &&  linha[1]=='T' && linha[2]=='O' && linha[3]=='M'){
                           sscanf(linha,"%*s %d %s %s %c %d %f %f %f %f %f %c",&lx_1,lx2,total[i].aminoacido,lx3,&total[i].quantidade,&lx4,&lx5,&lx6,&lx7,&lx8,lx9);
                    i++;
                }
        }
        for(j=1;j<i;j++){
            if(strcmp(total[j-1].aminoacido,total[j].aminoacido)==0 && total[j-1].quantidade == total[j].quantidade){

            }
         else{
                contador++;
            }
        }
        fclose(pont);
    return contador;
 }
int Menu(ATOM **lista,char *arquivo,int qtd,int total_amino){
    int verifica;
    int num;
    char atomo[5];
    printf("\n\n");
    printf("O que você deseja fazer ? \n");
    printf("0) Para Sair\n");
    printf("1) Listar todos os átomos e suas características constantes na lista criada\n");
    printf("2) Gerar arquivo de saída \n");
    printf("3) Átomos de cada tipo presentes no arquivo:\n");
    printf("4) Exibir na tela a quantidade de aminoácidos de cada tipo (GLY, CYS, SER, etc), presentes no arquivo\n");
    printf("5 Exibir na tela a quantidade total de aminoácidos presentes no arquivo\n");
    printf("6) Listar os dados de um átomo específico a partir do seu numero\n");
    printf("7)Listar os dados de todos os átomos que tenham o mesmo tipo (N, CA, C, O, CB, SG, etc)\n");

    scanf("%d",&verifica);
    if(verifica==1){
        Listar(*&lista);
        return 0;
    }
    else if(verifica==2){
        Saida(*&lista,arquivo);
        return 0;
    }
    else if(verifica==3){
        printf("Átomos de cada tipo presentes no arquivo:\n");
       tipoatomos(*&lista,qtd);
       return 0;
    }
    else if(verifica==4){
        printf("Aminoácidos de cada tipo presentes no arquivo:\n");
        tipoaminoaciados(*&lista,qtd);
        return 0 ;
    }
    else if(verifica==5){

            printf("Quantidade total de aminoácidos presentes no arquivo: %d\n ",total_amino);
    }
    else if(verifica==6){
         printf("Digite o numero do atomo: \n");
        scanf("%d",&num);
        dados(*&lista,num);
        return 0;
    }
    else if(verifica==7){
         printf("Digite o nome do atomo: \n");
           scanf("%s",atomo);
        dados_tipo(*&lista,atomo);
        return 0;
    }
    else
    return 1;
    
}

