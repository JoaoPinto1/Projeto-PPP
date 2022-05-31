/*
 * Este trabalho está divido em dois projetos, pelo que os ficheiros de texto original e o resultante que introduzir na
 * pasta da primeira parte do trabalho deve copiar para a pasta da segunda parte do trabalho. A primeira parte, recebe
 * um ficheiro com um texto e processa-o de modo a separar todas as palavras e guardar a posição em bytes de cada uma.
 * Usei a função isalpha() pois achei que seria a maneira mais fácil de resolver. A segunda parte, dá ao utilizar a
 * escolher se quer procurar em contexto uma palavra ou se pretende saber todas as palavra que começã com uma determinda
 * letra ou gama de letras. Explicado no ficheiro main da segunda parte.
 * */

#include "header.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERRO - Falta nome de ficheiro");
        return 1;
    }
    if (argc > 2) {
        printf("ERRO - Apenas recebe nome do ficheiro");
        return 1;
    }
    ler_fich(argv[1]);
}
