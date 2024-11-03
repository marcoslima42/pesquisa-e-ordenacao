#include<stdio.h>
#include<stdlib.h>

int pesquisaBinaria(int *lista, int tam, int item, int* qtdPont){
    int baixo=0, alto=tam-1, chute=0;

    while (baixo<=alto){
        int meio=(baixo+alto)/2;
        chute=lista[meio];
        if(chute==item){
            (*qtdPont)++;
            return meio;
        }else if(chute>item){
            alto=meio-1;
            (*qtdPont)++;
        }else{
            baixo=meio+1;
            (*qtdPont)++;
        }
    }
}

int main(){
    int lista[10]={2,4,5,9,7,20,32,40,55,60}, qtd=0, indice=0, item=32;
    int* qtdPont=&qtd;
    
    indice=pesquisaBinaria(lista, 10, item, qtdPont);
    printf("O indice do item e: %d", indice);   
    printf("\n\nQuantidade de operacoes: %d", qtd);

    
    return 0;
}