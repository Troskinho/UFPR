#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

/* ------------------- Nao altere estas structs ------------------------- */
struct nodo {
    int chave;
    struct nodo *prox;
};

struct lista {
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;

};
/* ---------------------------------------------------------------------- */

struct lista *lista_cria (void){
    struct lista *nova_lista = malloc(sizeof(*nova_lista));
    if (nova_lista == NULL) {
        return NULL;
    }
    nova_lista->ini = malloc(sizeof(struct nodo));
    if (nova_lista->ini == NULL) {
        free(nova_lista);
        return NULL;
    }
    nova_lista->ini->prox = NULL;
    nova_lista->tamanho = 0;
    nova_lista->ptr = NULL;
    return nova_lista;
}

void lista_destroi (struct lista **lista){
    if (lista == NULL || *lista == NULL)
        return;
    struct nodo *atual = (*lista)->ini;
    struct nodo *aux;

    while (atual != NULL)
    {
        aux = atual;
        atual = atual->prox;
        free(aux);
    }
    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave){
    if (lista == NULL)
        return 0;
    
    struct nodo *novo_nodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo_nodo == NULL) 
        return 0;
    
    novo_nodo->chave = chave;
    novo_nodo->prox = lista->ini->prox;
    lista->ini->prox = novo_nodo;
    lista->tamanho++;
    return 1;
}

int lista_insere_fim (struct lista *lista, int chave){
    if (lista == NULL)
        return 0;
    struct nodo *novo_nodo = (struct nodo *)malloc(sizeof(struct nodo));
    if (novo_nodo == NULL)
        return 0;
    
    novo_nodo->chave = chave;
    novo_nodo->prox = NULL;

    struct nodo *atual = lista->ini;
    while (atual->prox != NULL)
        atual = atual->prox;
    atual->prox = novo_nodo;
    lista->tamanho++;
    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave){
    if (lista == NULL)
        return 0;
    
    struct nodo *novo_nodo = malloc(sizeof(*novo_nodo));
    if (novo_nodo == NULL)
        return 0;
    
    novo_nodo->chave = chave;

    struct nodo *anterior = lista->ini;
    struct nodo *atual = anterior->prox;

    while (atual != NULL && atual->chave < chave){
        anterior = atual;
        atual = atual->prox;
    }
    novo_nodo->prox = atual;
    anterior->prox = novo_nodo;
    lista->tamanho++;
    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave){
    if (lista == NULL || lista->ini->prox == NULL)
        return 0;
    
    struct nodo *aux = lista->ini->prox;
    *chave = aux->chave;
    lista->ini->prox = aux->prox;
    free(aux);
    lista->tamanho--;
    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave){
    if (lista == NULL || lista->ini->prox == NULL)
        return 0;

    struct nodo *atual = lista->ini;
    struct nodo *anterior = NULL;

    while (atual->prox != NULL){
        anterior = atual;
        atual = atual->prox;
    }

    *chave = atual->chave;

    if (anterior == lista->ini)
        lista->ini->prox = NULL;
    else 
        anterior->prox = NULL;

    free(atual);
    lista->tamanho--;
    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave){
    if (lista == NULL || lista->ini == NULL)
        return 0;
    
    struct nodo *atual = lista->ini->prox;
    struct nodo *anterior = lista->ini;;

    while (atual != NULL && atual->chave != chave){
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL || atual->chave != chave)
        return 0;
    
    anterior->prox = atual->prox;
    free(atual);
    lista->tamanho--;
    return 1;
}

int lista_vazia (struct lista *lista){
    return lista == NULL || lista->tamanho == 0;
}

int lista_tamanho (struct lista *lista){
    if (lista == NULL)
        return 0;
    else
        return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
    if (lista == NULL)
        return 0;
    
    struct nodo *atual = lista->ini->prox;
    while (atual != NULL){
        if (atual->chave == chave)
            return 1;
        atual = atual->prox;
    }
    return 0;
}

void lista_inicia_iterador (struct lista *lista){
    if (lista != NULL){
        lista->ptr = lista->ini->prox;
    }
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    if (lista == NULL || lista->ptr == NULL)
        return 0;
    
    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}