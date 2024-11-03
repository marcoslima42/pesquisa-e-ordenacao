#include "arvoreAVL.h"

ArvoreAVL* criaArvoreAVL()
{
    ArvoreAVL *t = (ArvoreAVL*)malloc(sizeof(ArvoreAVL));
    t->altura = 0;
    t->raiz = NULL;
    return t;
}
NoAVL* criaNoAVL(int chave)
{
    NoAVL *novo = (NoAVL*)malloc(sizeof(NoAVL));
    novo->chave = chave;
    novo->fb = 0;
    novo->esq = novo->dir = NULL;
    return novo;
}
NoAVL* rotacaoEsq(NoAVL *desbal)
{


}
NoAVL* rotacaoDir(NoAVL *desbal)
{





    
}
NoAVL* rotacaoEsqDir(NoAVL *desbal){}
NoAVL* rotacaoDirEsq(NoAVL *desbal){}