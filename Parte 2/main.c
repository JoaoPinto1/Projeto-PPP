/*
 * Nesta segunda parte, não esquecer de copiar os ficheiros de texto da parte 1 para a pasta cmake-build-debug.
 * É possível executar pelo terminal como pelo run. A minha abordagem na contrução da estrutura de dados foi relativamente
 * simples, foi apenas necessário colocar em cada nó da árvore uma lista ligada e uma palavra. Para deixar o utilizador
 * escolher o que queria procurar, utilizei um interface em que o ajuda a isso mesmo. Na parte do contexto, decidi
 * percorrer todoo o texto à procura dos pontos finais até chegar à posição da palavra que decidiu encontrar e depois
 * encontrar apenas um (se estiver na ultima frase) ou dois pontos final. Na parte da procura de palavra que iniciam com
 * uma determinada letra ou gama de letras, foi relativamente simples, utilizei uma função recursiva já que tinha de
 * procurar em todos os nós da arvore, tanto do lado esquerdo como do direito.
 */

#include "struc_dados.h"
bool verificar_ficheiro(char *nome_fich);
void ler_ficheiro(char *nome_fich, struct arvore_binaria *arvore);
int interface(struct arvore_binaria arvore, char *nome_fich);

int main(int argc, char *argv[]) {
    char nome_fich[50];
    if(argc<2){
        printf("Nome de ficheiro não recebido\n");
        while(verificar_ficheiro(nome_fich)==false){
            printf("Nome do ficheiro: ");
            scanf("%s",nome_fich);
        }
    }
    if(argc>2){
        printf("ERRO - Apenas recebe nome do ficheiro");
        return 1;
    }
    if(argc==2){
        if(verificar_ficheiro(argv[1])==false){
            printf("Ficheiro nao encontrado\n");
            return 1;
        }
        else
            strcpy(nome_fich,argv[1]);
    }
    struct arvore_binaria arvore;
    inicializar_arvore(&arvore);
    ler_ficheiro(nome_fich,&arvore);
    interface(arvore,nome_fich);
}