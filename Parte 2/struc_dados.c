#include "struc_dados.h"

void inicializar_arvore(struct arvore_binaria *pa) {
    pa->raiz = NULL;
}

static struct no_arvore *addtree(struct no_arvore *, struct no_arvore *);

bool colocar(struct arvore_binaria *pa, char palavra[TAMPAL], long int posicao) {
    struct no_arvore *p = NULL;
    if (verificar(pa, palavra, p) == NULL) { //se nao existir nenhum nó com essa palavra
        p = (struct no_arvore *) malloc(sizeof(struct no_arvore));
        if (p == NULL)
            return false;
        strcpy(p->palavra, palavra);
        inicializar_lista(&p->lista); //criar uma lista
        colocar_lista(&p->lista, posicao); //colocar no primeiro nó da lista a primeira ocorrencia da palavra
        p->lista.ocorrencias = 1;
        p->left = p->right = NULL;
        pa->raiz = addtree(pa->raiz, p);
    } else { //se já existir um nó de uma arvore para essa palavra
        p = verificar(pa, palavra, p);
        colocar_lista(&p->lista, posicao); //colocar na lista as posiçoes de todas as ocorencias
        p->lista.ocorrencias++;
    }
    return true;
}

struct no_arvore *addtree(struct no_arvore *pr, struct no_arvore *p) {
    int cond;
    char nome1[MAXNOME + 1], nome2[MAXNOME + 1];
    if (pr == NULL)
        pr = p;
    else {
        strtobase_u8(nome1, p->palavra);
        strtobase_u8(nome2, pr->palavra);
        if ((cond = strcmp(nome1, nome2)) > 0) {
            pr->right = addtree(pr->right, p);
        } else if (cond < 0)
            pr->left = addtree(pr->left, p);
    }
    return pr;
}

struct no_arvore *find(struct no_arvore *pr, char *pn);

struct no_arvore *verificar(struct arvore_binaria *pa, char nome[], struct no_arvore *p) {
    p = find(pa->raiz, nome); //procurar a palavra pela arvore, se não existir devolve NULL
    return p;
}

struct no_arvore *find(struct no_arvore *pr, char *pn) {
    int cond;
    if (pr == NULL)
        return NULL;
    char nome1[MAXNOME + 1], nome2[MAXNOME + 1];
    strtobase_u8(nome1, pr->palavra);
    strtobase_u8(nome2, pn);
    if ((cond = strcmp(nome1, nome2)) == 0)
        return pr;
    else if (cond > 0)
        return find(pr->left, pn);
    return find(pr->right, pn);
}

bool consultar_contexto(struct arvore_binaria *pa, char *nome, char *nome_fich) {
    FILE *fich;
    fich = fopen(nome_fich, "r"); //abrir o ficheiro onde está o texto
    struct no_arvore *p;
    p = find(pa->raiz, nome); //procurar a palavra na arvore
    if (p == NULL)
        return false;
    long int posicao;
    while (retirar(&p->lista, &posicao)) { //vai percorrer a lista até ficar vazia
        fseek(fich, 0, SEEK_SET);
        char c[MB_CUR_MAX + 1];
        long int pontos[1000]; //armazenar a posiçao de todos os pontos finais até à nossa palavra
        int contador = 0; //numero de pontos finais até à palavra
        while (ftell(fich) != posicao) {
            fgets_c_u8(c, 1, fich);
            if (strcmp(c, ".") == 0 || strcmp(c, "!") == 0 || strcmp(c, "?") == 0) {
                pontos[contador] = ftell(fich);
                contador++;
            }
        }
        if (contador == 0 || contador == 1) { //se a palavra estiver na primeira ou na segunda frase do texto
            fseek(fich, 0, SEEK_SET);
            while (ftell(fich) != posicao) {
                fgets_c_u8(c, 1, fich);
                printf("%s", c);
            }
        } else {
            fseek(fich, pontos[contador - 2], SEEK_SET); //para mostrar a frase anterior é necessário haver um ponto
            // final a separar
            while (ftell(fich) != posicao) {
                fgets_c_u8(c, 1, fich);
                printf("%s", c);
            }
        }
        contador = 0;
        while (contador != 2) {
            if (fgets_c_u8(c, 1, fich) == NULL) //se chegar ao final do ficheiro
                break;
            printf("%s", c);
            if (strcmp(c, ".") == 0 || strcmp(c, "!") == 0 || strcmp(c, "?") == 0)
                contador++;
        }
        printf("\n-------------------------\n");
    }
    return true;
}

struct no_arvore *find_carateres(struct no_arvore *pr, char *pn);

void obter_palavras(struct arvore_binaria *pa, char *carateres) {
    if (strlen_u8(carateres) > 2)
        puts("Gama de carateres inválida");
    char nome[MAXNOME + 1];
    strtobase_u8(nome, carateres);
    if (strlen_u8(nome) == 1 || nome[1] > nome[0])
        find_carateres(pa->raiz, nome);
    else
        puts("Gama de carateres inválida");
}

struct no_arvore *find_carateres(struct no_arvore *pr, char *pn) {
    if (pr == NULL)
        return NULL;
    char nome1[MAXNOME + 1];
    strtobase_u8(nome1, pr->palavra);
    if (strlen_u8(pn) == 1) { //se for apenas dado uma letra
        if (pn[0] == nome1[0]) {
            puts(pr->palavra);
            printf("-----------------------------\n");
        }
    } else { //se for dado uma gama de letras
        char letra = pn[0];
        while (1) {
            if (letra == nome1[0]) {
                puts(pr->palavra);
                printf("---------------------------------\n");
            }
            if (letra == pn[1])
                break;
            letra++;
        }
    }
    find_carateres(pr->left, pn);
    find_carateres(pr->right, pn);
    return pr;
}

void inicializar_lista(struct lista *pf) {
    pf->tam = TAMFILA;
    // a fila está inicialmente vazia
    pf->entrada_lista = TAMFILA - 1;
    for (int i = 0; i < TAMFILA; i++)
        pf->no[i].ocupado = false;
}

bool colocar_lista(struct lista *pf, long int posicao) {
    int i, anterior, prox;
    //Procurar uma posição disponível
    for (i = pf->tam - 1; i >= 0 && pf->no[i].ocupado; i--);
    if (i < 0) {
        //fila cheia - não é possível inserir mais nada
        return false;
    }
    //colocar posicao na fila
    pf->no[i].posicao = posicao;

    //Procurar em que nó deve a posicao ficar
    if (!(pf->no[pf->entrada_lista].ocupado)) {
        // fila vazia, inserir primeira posicao
        pf->entrada_lista = i;
        pf->no[i].pos_seguinte = -1;
    } else {
        // fila contém posicoes
        if (pf->no[pf->entrada_lista].posicao < posicao) {
            // inserir à entrada da lista
            pf->no[i].pos_seguinte = pf->entrada_lista;
            pf->entrada_lista = i;
        } else {
            // procurar posição de inserção
            anterior = pf->entrada_lista;
            prox = pf->no[pf->entrada_lista].pos_seguinte;
            while (prox >= 0 && pf->no[prox].posicao >= posicao) {
                anterior = prox;
                prox = pf->no[prox].pos_seguinte;
            }
            if (prox < 0) {
                // inserir no final da lista
                pf->no[anterior].pos_seguinte = i;
                pf->no[i].pos_seguinte = -1;
            } else {
                // inserir a meio da lista
                pf->no[anterior].pos_seguinte = i;
                pf->no[i].pos_seguinte = prox;
            }
        }
    }
    pf->no[i].ocupado = true;
    return true;
}

bool retirar(struct lista *pf, long int *posicao) {
    int i, j;
    if (!pf->no[pf->entrada_lista].ocupado) {
        // lista vazia
        return false;
    }
    //  Procurar a última mensagem da lista
    j = -1;
    for (i = pf->entrada_lista; pf->no[i].pos_seguinte != -1; i = pf->no[i].pos_seguinte)
        j = i; // guardar a localização da mensagem anterior à que vai sair
    if (j != -1)
        // havia mais do que uma mensagem na lista
        pf->no[j].pos_seguinte = -1;
    pf->no[i].ocupado = false;
    *posicao = pf->no[i].posicao;
    return true;
}