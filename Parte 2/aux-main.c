#include "struc_dados.h"

bool verificar_ficheiro(char *nome_fich){ //verificar se o ficheiro existe
    if(fopen(nome_fich,"r")==NULL)
        return false;
    else
        return true;

}
void ler_ficheiro(char *nome_fich, struct arvore_binaria *arvore){
    char nomeaux[]="ind_";
    strcat(nomeaux,nome_fich);
    FILE *fich, *fichaux;
    fich=fopen(nomeaux,"r");
    fichaux=fopen("ficheiro_aux.txt","w");
    int c;
    while((c=fgetc(fich))!=EOF){
        if(c==';')
            fputc(' ',fichaux); //para me ajudar, criei um ficheiro auxiliar onde em vez de ; existe um espaço
        else
            fputc(c,fichaux);
    }
    fclose(fich);
    fclose(fichaux);
    fichaux= fopen("ficheiro_aux.txt","r");
    char palavra[TAMPAL];
    long int posicao;
    while(fscanf(fichaux,"%s %ld",palavra,&posicao)!=EOF) {
        //antes de começar o trabalho usei esta função da mesma maneira e não dava aviso e agora começou a dar
        if(strlen_u8(palavra)!=1)
            colocar(arvore, palavra, posicao);
    }
    fclose(fichaux);
}
int interface(struct arvore_binaria arvore, char *nome_fich){
    int escolha;
    while (1) {
        printf("\n"
               "  0 - Sair\n"
               "  1 - Obter Contexto\n"
               "  2 - Obter Palavras\n"
               "Escolha: ");
        escolha = ' ';
        while (isspace(escolha))
            escolha = getchar();
        while (getchar() != '\n'); //limpar o resto da linha
        if (escolha == '0') return 0;
        if (escolha == '1') {
            char palavra[]="";
            printf("\nPalavra: ");
            scanf("%s",palavra);
            if(!consultar_contexto(&arvore,palavra,nome_fich))
                printf("Palavra não encontrada\n");
        }
        else if (escolha == '2'){
            char carateres[]="";
            printf("\nCarateres: ");
            scanf("%s",carateres);
            obter_palavras(&arvore,carateres);
        }
        else printf("Escolha inválida\n");
    }
}
