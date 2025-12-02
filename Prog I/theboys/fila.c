
#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

struct fila_t *fila_cria() 
{
    struct fila_t *f = (struct fila_t *) malloc(sizeof(struct fila_t));
    
    if (f == NULL)
        return NULL;

    f->prim = NULL;
    f->ult = NULL;
    f->num = 0;

    return f;
}

struct fila_t *fila_destroi (struct fila_t *f)
{
    if (f == NULL)
        return NULL;

    struct fila_nodo_t *atual = f->prim;
    struct fila_nodo_t *temp;

    while (atual != NULL)
    {
        temp = atual->prox;
        free(atual);
        atual = temp;
    }

    free(f);
    return NULL;
}


int fila_insere (struct fila_t *f, int item) 
{
    if (f == NULL) 
        return 0;

    struct fila_nodo_t *novo = (struct fila_nodo_t *) malloc(sizeof(struct fila_nodo_t));

    if (novo == NULL)
        return 0; 

    novo->item = item;
    novo->prox = NULL;

    if (f->prim == NULL) 
    {
        f->prim = novo;
        f->ult = novo;
    } 
    else 
    {
        f->ult->prox = novo;
        f->ult = novo;
    }

    f->num++;
    return 1; 
}

int fila_retira (struct fila_t *f, int *item)
{
    if (f == NULL || f->prim == NULL)
        return 0;

    struct fila_nodo_t *temp = f->prim;
    *item = temp->item;

    f->prim = temp->prox;

    if (f->prim == NULL)
        f->ult = NULL;

    free(temp);
    f->num--;
    
    return 1; 
}

int fila_tamanho (struct fila_t *f)
{
    if (f == NULL)
        return -1;

    return f->num;
}

void fila_imprime (struct fila_t *f)
{
    if (f == NULL || f->prim == NULL)
        return;

    struct fila_nodo_t *atual = f->prim;

    while (atual != NULL) 
    {
        printf("%d", atual->item);
        atual = atual->prox;

        if (atual != NULL)
            printf(" ");
    }
}