# Trabalho-Final-do-Sandro
Descrição do trabalho Seu arquivo deverá ser nomeado TP-Nome1-Nome2-Nome3-Nome4.c, onde Nome1, Nome2, etc, são os primeiros nomes de cada um do grupo. Cada item abaixo deverá estar como comentário logo antes de sua implementação no arquivo a ser submetido, indicando onde foram atendidas estas solicitações. Escreva um programa em C que faça:

1) Leia do prompt de comando os nomes dos arquivos de entrada e saída.  Por exemplo: ./TP-Sandro entrada.pdb saida.txt  

2) Abra o arquivo de entrada e leia a quantidade (N) de linhas do arquivo que iniciem pela palavra ATOM. O arquivo de entrada é um arquivo que contém a estrutura tridimensional de uma proteína, como pode ser visto a seguir. As linhas iniciadas por ATOM contém informações sobre cada átomo que compõe e proteína. 

3) Imprima na tela a quantidade total de átomos presentes no arquivo.

4) Crie uma struct para armazenar os dados de cada átomo:  a) Número que o identifica 
b) O nome do átomo (N, CA, C, O, CB, SG, etc)
c) O nome do aminoácido (GLY, CYS, SER, etc) 
d) As coordenadas atômicas X, Y, Z - colunas 7, 8 e 9 

5) Crie uma lista encadeada para os átomos que forem lidos do arquivo, a partir da struct criada anteriormente, fazendo a alocação dinâmica dos elementos da lista à medida que forem lidos. 

6) Exiba um menu ao usuário para escolher:
a) Listar todos os átomos e suas características constantes na lista criada 
b) Gerar arquivo de saída - Escreva no arquivo de saída o número do átomo (coluna 2), o nome do átomo (coluna 3), o nome do aminoácido (coluna 4) e suas coordenadas atômicas (colunas 7, 8 e 9).
c) Exibir na tela a quantidade de átomos de cada tipo (N, CA, C, O, CB, SG, etc), presentes no arquivo 
d) Exibir na tela a quantidade de aminoácidos de cada tipo (GLY, CYS, SER, etc), presentes no arquivo
e) Exibir na tela a quantidade total de aminoácidos presentes no arquivo (Observe que apesar de terem o mesmo nome, aminoácidos consecutivos devem ser contados de forma distinta. Cada aminoácido também tem um número que o identifica - coluna  OBS.: Os átomos e aminoácidos deverão ser impressos em ordem alfabética, portando, indique no código onde está sendo feita a ordenação e qual método está sendo usado.
f) Listar os dados de um átomo específico, buscando pelo seu número informado pelo usuário. 
g) Listar os dados de todos os átomos que tenham o mesmo tipo (N, CA, C, O, CB, SG, etc) informado pelo usuário.
