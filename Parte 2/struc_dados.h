#define MAXNOME 100
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "lib-utf8.h"
#define TAMFILA 50
#define TAMPAL 100

struct no_lista{
    long int posicao;
    bool ocupado;
    int pos_seguinte;
};

struct lista {
    struct no_lista no[TAMFILA];
    int ocorrencias;
    int entrada_lista;
    int tam;
};

struct no_arvore {
    char palavra[TAMPAL];
    struct lista lista;
    struct no_arvore *left;
    struct no_arvore *right;
};

struct arvore_binaria {
    struct no_arvore * raiz;
};

bool colocar(struct arvore_binaria * pa, char palavra[TAMPAL], long int posicao);

struct no_arvore *verificar(struct arvore_binaria * pa, char nome[], struct no_arvore *p);

void inicializar_arvore(struct arvore_binaria * pa);

void inicializar_lista(struct lista *pf);

bool colocar_lista(struct lista *pf, long int posicao);

bool retirar(struct lista *pf, long int *posicao);

bool consultar_contexto(struct arvore_binaria * pa, char *nome, char *nome_fich);

void obter_palavras(struct arvore_binaria *pa, char *carateres);