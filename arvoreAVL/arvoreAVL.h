#ifndef ARVORE_AVL
#define ARVORE_AVL
#include <stdlib.h>
#include <stdio.h>

struct noAVL
{
    int chave;
    struct noAVL *esq,*dir;
    int fb;   
};
typedef struct noAVL NoAVL;
struct arvoreAVL
{
   NoAVL *raiz;
   int altura; //altura max
};
typedef struct arvoreAVL ArvoreAVL;

ArvoreAVL* criaArvoreAVL();
NoAVL* criaNoAVL(int chave);
NoAVL* rotacaoEsq(NoAVL *desbal);
NoAVL* rotacaoDir(NoAVL *desbal);
NoAVL* rotacaoEsqDir(NoAVL *desbal);
NoAVL* rotacaoDirEsq(NoAVL *desbal);
#endif