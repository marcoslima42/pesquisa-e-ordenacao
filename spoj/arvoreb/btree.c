#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//estrutura lista dupla
struct nod
{
    void* info;
    struct nod *prox;
    struct nod *ant;
};
typedef struct nod Nod;
struct listad
{
    Nod *ini, *fim;
};
typedef struct listad Listad;
Listad* cria_listad();
Nod* cria_nod(void* info);
void insere_inicio_listad(void* info, Listad *L);
void insere_fim_listad(void* info, Listad *L);
Nod* remove_inicio_listad(Listad *L);
Nod* remove_fim_listad(Listad *L);
Listad* libera_listad(Listad *L);
Listad* divide_listad(Listad *L, int n);

//estrutura arvore B
struct pagina
{
 int folha;
 int qtdeChaves;
 struct pagina *pai;
 Listad *listaChaves;
 struct pagina *direita;
};

typedef struct pagina Pagina;
struct chave
{
	int valorChave;
	struct pagina *filho;
};

typedef struct chave Chave;

struct arvoreb
{
 struct pagina *raiz;
 int ordem;
 int altura;
};

typedef struct arvoreb Arvoreb;

Arvoreb *cria_arvoreb(int ordem);
Pagina *cria_pagina();
Chave *cria_chave(int valor);
void em_ordem(Pagina* raiz);
void insere_arvoreb(Arvoreb *T, int valor);
Pagina *encontra_folha(Pagina *raiz, int valor);
Pagina *divide(Pagina *pagina_dividir);
void insere_chave_pagina(Pagina *folha, Chave *ch);

Chave* retira_ultima_chave(Pagina* folha);
Pagina* cria_nova_raiz(Pagina* folha, Pagina* nova_pagina, Chave *ch);

void mostar_lista_detalhe(Listad *L);
Pagina *getFilho(Nod *aux);


//funcoes lista dupla
Listad *cria_listad()
{
    Listad *L = (Listad *)malloc(sizeof(Listad));
    L->ini = L->fim = NULL;
    return L;
}

Nod *cria_nod(void *info)
{
    Nod *novo = (Nod *)malloc(sizeof(Nod));
    novo->info = info;
    novo->ant = novo->prox = NULL;
    return novo;
}

void insere_inicio_listad(void *info, Listad *L)
{
    Nod *novo = cria_nod(info);

    if (L->ini == NULL)
    {
        L->ini = L->fim = novo;
    }
    else
    {
        novo->prox = L->ini;
        L->ini->ant = novo;
        L->ini = novo;
    }
}

void insere_fim_listad(void *info, Listad *L)
{
    Nod *novo = cria_nod(info);

    if (L->ini == NULL)
    {
        L->ini = L->fim = novo;
    }
    else
    {
        novo->ant = L->fim;
        L->fim->prox = novo;
        L->fim = novo;
    }
}

Listad *libera_listad(Listad *L)
{
    Nod *aux;

    while (L->ini != NULL)
    {
        aux = L->ini;
        L->ini = L->ini->prox;
        free(aux);
    }
    free(L);
    return NULL;
}

Nod *remove_inicio_listad(Listad *L)
{
    Nod *aux = NULL;
    if (L != NULL && L->fim != NULL) // caso haja elemento
    {
        aux = L->ini;
        if (L->ini == L->fim)
        {
            L->ini = L->fim = NULL;
        }
        else
        {
            L->ini = L->ini->prox;
            L->ini->ant = NULL;
        }
    }
    return aux;
}

Nod *remove_fim_listad(Listad *L)
{
    Nod *aux;
    if (L->fim != NULL)
    {
        aux = L->fim;
        if (L->ini != L->fim)
        {
            L->fim = L->fim->ant;
            L->fim->prox = NULL;
        }
        
        else
        {
            L->ini = L->fim = NULL;
        }
        aux->prox = aux->ant = NULL;
    }
    return aux;
}

Listad *divide_listad(Listad *L, int qtde_elementos_primeira_lista)
{
    Listad *L2 = cria_listad();
    Nod *aux = L->ini;
    int i = 0;
    while (i < qtde_elementos_primeira_lista)
    {
        i++;
        aux = aux->prox;
    }
    L2->ini = aux;
    L2->fim = L->fim;
    L->fim = aux->ant;
    L2->ini->ant = NULL;
    L->fim->prox = NULL;
    return L2;
}

//funcoes arvore B
Arvoreb *cria_arvoreb(int ordem)
{
    Arvoreb *T = malloc(sizeof(Arvoreb));
    T->raiz = NULL;
    T->ordem = ordem;
    T->altura = 0;
    return T;
}

Pagina *cria_pagina()
{
    Pagina *p = malloc(sizeof(Pagina));
    p->folha = 1; // eh folha
    p->qtdeChaves = 0;
    p->pai = NULL;
    p->listaChaves = cria_listad();
    p->direita = NULL;

    return p;
}

Chave *cria_chave(int valor)
{
    Chave *ch = malloc(sizeof(Chave));
    ch->valorChave = valor;
    ch->filho = NULL;
    return ch;
}

int getChave(Nod *aux)
{
    return ((Chave *)aux->info)->valorChave;
}

Pagina *getFilho(Nod *aux)
{
    return ((Chave *)aux->info)->filho;
}

void insere_ordenado(Listad *L, Chave *ch)
{

    Nod *aux = L->ini;
    Nod *novo_no;
    if (L->ini == NULL)
    {
        insere_inicio_listad(ch, L);
    }
    else
    {
        if (ch->valorChave < getChave(L->ini))
            insere_inicio_listad(ch, L);
        else if (ch->valorChave > getChave(L->fim))
            insere_fim_listad(ch, L);
        else
        {
            while (ch->valorChave > getChave(aux))
                aux = aux->prox;
            novo_no = cria_nod(ch);
            novo_no->ant = aux->ant;
            novo_no->prox = aux;
            aux->ant = novo_no;
            novo_no->ant->prox = novo_no;
        }
    }
}

void insere_arvoreb(Arvoreb *T, int valor)
{
    Pagina *pag_aux = T->raiz;
    int tem_valor_para_inserir = 1;
    Chave *ch = cria_chave(valor);

    Pagina *folha = encontra_folha(pag_aux, valor);
    Pagina *nova_pagina;

    if (folha == NULL)
    {
        T->raiz = cria_pagina();
        insere_chave_pagina(T->raiz, ch);
    }
    else
    {
        while (tem_valor_para_inserir)
        {
            insere_chave_pagina(folha, ch); /// no futuro vai ser uma chave
            if (folha->qtdeChaves < T->ordem)
            {
                tem_valor_para_inserir = 0;
            }
            else // estorou a pagina
            {
                nova_pagina = divide(folha);
                ch = retira_ultima_chave(folha);
                if (T->raiz == folha)
                {
                    T->raiz = cria_nova_raiz(folha, nova_pagina, ch);
                    tem_valor_para_inserir = 0;
                }
                else
                    folha = folha->pai;
            }
        }
    }
}

Pagina *encontra_folha(Pagina *raiz, int valor)
{
    Pagina *aux_pagina = raiz;

    if (raiz == NULL)
        return NULL;
    else
    {
        while (aux_pagina->folha != 1)
        {
            Nod *aux_lista = aux_pagina->listaChaves->ini;
            while (aux_lista != NULL && valor > getChave(aux_lista))
            {
                aux_lista = aux_lista->prox;
            }
            if (aux_lista == NULL)
                aux_pagina = aux_pagina->direita;
            else
                aux_pagina = getFilho(aux_lista);
        }
        return aux_pagina;
    }
}

void insere_chave_pagina(Pagina *folha, Chave *ch)
{
    insere_ordenado(folha->listaChaves, ch);
    folha->qtdeChaves++;
}

Pagina *divide(Pagina *pagina_dividir)
{

    Pagina *nova_pagina = cria_pagina();
    // a função ceil arrenda para cima (biblioteca math.h)
    int qtde_pagina_dividir = ceil(pagina_dividir->qtdeChaves / 2.0);

    Listad *nova_lista = divide_listad(pagina_dividir->listaChaves, 
    qtde_pagina_dividir);
    nova_pagina->listaChaves = nova_lista;
    nova_pagina->qtdeChaves =
        pagina_dividir->qtdeChaves - qtde_pagina_dividir;
    nova_pagina->pai = pagina_dividir->pai;
    nova_pagina->folha = pagina_dividir->folha;
    nova_pagina->direita = pagina_dividir->direita;
    
    pagina_dividir->qtdeChaves = qtde_pagina_dividir;

    Chave *ultima_chave = pagina_dividir->listaChaves->fim->info;

    if (pagina_dividir->pai != NULL)
    {

        // O filho da chave seguinte a ponta para o nova página
        Nod *aux = pagina_dividir->pai->listaChaves->ini;
        while (aux != NULL && //nesse caso o ponteiro do filho é o da direita
                getFilho(aux) != pagina_dividir)
            aux = aux->prox;
        if(aux != NULL)
            ((Chave *)aux->info)->filho = nova_pagina;
        else
            pagina_dividir->pai->direita = nova_pagina;
    }

    if (pagina_dividir->folha == 0)
    {
        Nod *aux = nova_pagina->listaChaves->ini;
        while (aux != NULL)
        {
            getFilho(aux)->pai = nova_pagina;
            aux = aux->prox;
        }
        nova_pagina->direita->pai = nova_pagina;
        pagina_dividir->direita =  ultima_chave->filho ;
    }
    //O filho da chave que subiu aponta para a página que já existia
        ultima_chave->filho = pagina_dividir;
        return nova_pagina;
}


void em_ordem(Pagina* raiz)
{
    Nod *aux;
    if (raiz != NULL)
    {
        aux = raiz->listaChaves->ini;
        while(aux != NULL)
        {
            em_ordem(((Chave*)aux->info)->filho);
            printf("%d ", ((Chave*)aux->info)->valorChave);
            aux=aux->prox;
        }
        em_ordem(raiz->direita);
    }
}

Chave* retira_ultima_chave(Pagina* folha)
{
    Nod* ultimo_no = remove_fim_listad(folha->listaChaves);
    Chave* ch = ultimo_no->info;
    free(ultimo_no);
    folha->qtdeChaves--;
    return ch;
}


Pagina* cria_nova_raiz(Pagina* folha, Pagina* nova_pagina, Chave *ch)
{
    Pagina* nova_raiz = cria_pagina();
    nova_raiz->folha = 0;
    insere_chave_pagina(nova_raiz,ch);
    ch->filho = folha;
    nova_raiz->direita = nova_pagina;
    nova_pagina->pai = nova_raiz;
    ch->filho->pai = nova_raiz;
    
    return nova_raiz;
    
}

void mostar_lista_detalhe(Listad *L)
{
    Nod* aux = L->ini;
    while ( aux != NULL)
    {
        printf("%d [%d] %d ",
        aux->ant == NULL? 0:getChave(aux->ant),
        getChave(aux),
        aux->prox == NULL? 0:getChave(aux->prox)
        );
        aux = aux->prox;
    }
}

Nod* busca(Pagina* paginaArvore, int valor, int i){
    //Pagina* paginaArvore=T->raiz;
    //Nod* no=T->raiz->listaChaves->ini;
    Nod* no=paginaArvore->listaChaves->ini;

    //encontrar indice certo
    while(no!=NULL && getChave(no)<valor){
        no=no->prox;
        i++;
    }

    if(no!=NULL && getChave(no)==valor)
        return no;

    if (paginaArvore->folha)
        return NULL;

    //buscando o indice do filho
    Nod* no2=no;
    for(int x=0; i<i; x++){
        no2=no2->prox;
    }

    //ENTRANDO NA SUBARVORE DO FILHO

    //se o filho for a direita
    if(no2->prox==NULL){ 
        paginaArvore=paginaArvore->direita;
        return busca(paginaArvore, valor, i);
    }else{ //filho no meio da lista
        paginaArvore=getFilho(no2->info);
        return busca(paginaArvore, valor, i);
    }
}

int main(){
    Arvoreb* tree;
    int ordem=0, input=0;

    //criar arvore
    scanf("%d", &ordem);
    tree=cria_arvoreb(ordem);

    //entrada dos dados na arvore
    scanf("%d", &input);

    while(input!=-1){
        insere_arvoreb(tree,input);
        scanf("%d", &input);
    }

    //em_ordem(tree->raiz);
    int valor=0, i=0;
    scanf("%d", &valor);
    Nod* noPrint=busca(tree->raiz, valor, i);
    printf("\n\nEsse e o no %d", getChave(noPrint));
    return 0;
}

Pagina* folhaAdjacente(Pagina* raiz, int k){
    Pagina *pagK=NULL, *pagPaiK=NULL;
    pagK=encontra_folha(raiz, k);
    pagPaiK=pagK->pai;
    
    Nod* noPai=pagPaiK->listaChaves->ini;
    
    
    
    //encontrar no com o filhonque leva a pagK
    while(getFilho(noPai)!=pagK && (noPai)!=NULL)
        noPai=noPai->prox;

    if(noPai==NULL)
        noPai=pagPaiK->direita;

    //verificar subarvores
    int irmao_dir =0, irmao_esq=0; 
    //tratar se for nulo
    int irmao_dir = (getFilho(noPai->prox))->qtdeChaves;
    int irmao_esq = (getFilho(noPai->ant))->qtdeChaves;

    if(irmao_dir>irmao_esq){
        //caso o da direita tenha mais elementos

    }
    else if(irmao_esq>irmao_dir){
        //caso o da esq tenha mais elementos 
    }
    else if(irmao_dir==0){
        //caso nao tenha a subarvore a direita
    }
    else{
        //caso nao tenha a subarvore a esquerda
    }

    //return pagina;
}

