#include "header.h"
int ler_fich(char nome_fich[]) {
    FILE *fich_in = NULL;
    FILE *fich_out = NULL;
    char nome_fich_out[MAXNOME] = "ind_";
    strcat(nome_fich_out, nome_fich);
    fich_in = fopen(nome_fich, "r");
    if (fich_in == NULL) {
        fprintf(stderr, "ERRO - Não foi possivel abrir o ficheiro");
        return 1;
    }
    fich_out = fopen(nome_fich_out, "w");
    if (fich_out == NULL) {
        fprintf(stderr, "ERRO - Erro ao abrir ficheiro de saída");
        return 1;
    }
    char carater[MB_CUR_MAX + 1], caraux[] = "";
    int c, c_ant;
    long int posicao;
    while (fgets_c_u8(carater, 1, fich_in) != NULL) {
        strtobase_u8(caraux, carater);
        bool simbolo = false;
        c = (int) caraux[0];  //neste momento sabemos que caraux tem 1 byte de tamanho pois foi usado strtobase_u8
        if (c_ant == 0 && isalpha(c) != 0)
            posicao = ftell(fich_in);
        if (isalpha(c) == 0 && c != '-' && isalpha(c_ant) != 0) {
            fprintf(fich_out, ";%ld\n", posicao);
            simbolo = true;
        }
        if (isalpha(c) == 0 && isalpha(c_ant) == 0)
            simbolo = true;
        if (isalpha(c) != 0 && isalpha(c_ant) == 0)
            posicao = ftell(fich_in);
        if (simbolo == false)
            fprintf(fich_out, "%s", carater);
        c_ant = (int) c;
    }
    fclose(fich_out);
    fclose(fich_in);
    return 0;
}