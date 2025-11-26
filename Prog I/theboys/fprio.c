// Foi usada a implementação, com pequenas alterações, dada na entrega do trabalho prático 4 da disciplina

#include <stdlib.h>
#include <stdio.h>
#include "fprio.h"
#include "mundo.h"


// descreve um nodo da fila de prioridades
// NAO altere estas estruturas
struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria() {

  struct fprio_t *fila = (struct fprio_t *)malloc(sizeof(struct fprio_t));

  if (fila == NULL)
    return NULL;

  fila->prim = NULL;
  fila->num = 0;

  return fila;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi(struct fprio_t *f) {

  if (f == NULL)
    return NULL;

  struct fpnodo_t *atual = f->prim;
  struct fpnodo_t *aux;

  while (atual != NULL) {
    aux = atual;
    atual = atual->prox;

    if (aux->item != NULL)
        free(aux->item);

    free(aux);
  }

  free(f);
  return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio) {

  //verificação: fila ou item nulos
  if (f == NULL || item == NULL)
    return -1;

  //verificação: item já na fila
  struct fpnodo_t *atual = f->prim;
  while (atual != NULL) {

    if (atual->item == item)
      return -1;
    
    atual = atual->prox;
  }

  //criação do novo item na fila
  struct fpnodo_t *novo_nodo = (struct fpnodo_t *)malloc(sizeof(struct fpnodo_t));
  if (novo_nodo == NULL)
    return -1;

  novo_nodo->item = item;
  novo_nodo->tipo = tipo;
  novo_nodo->prio = prio;
  novo_nodo->prox = NULL;

  //verificação: se fila vazia ou item novo com maioi prioridade
  if (f->prim == NULL || prio < f->prim->prio) {
    novo_nodo->prox = f->prim; 
    f->prim = novo_nodo;        
  }
  else {
    struct fpnodo_t *anterior = NULL;
    atual = f->prim;

    while (atual != NULL && atual->prio <= prio){
      anterior = atual;
      atual = atual->prox;
    }

    novo_nodo->prox = atual;
    if (anterior == NULL)
      f->prim = novo_nodo;
    
    else
      anterior->prox = novo_nodo;
  }

  f->num++;
  return f->num; //irá retornar o novo número de itens n fila

}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio){

  if (f == NULL || f->prim == NULL || tipo == NULL || prio == NULL)
    return NULL;

  struct fpnodo_t *nodo_removido = f->prim;

  //armazena valores e tipos do item removido
  *tipo = nodo_removido->tipo;
  *prio = nodo_removido->prio;

  f->prim = nodo_removido->prox;
  f->num--;

  void *item_removido = nodo_removido->item;

  free(nodo_removido);

  return item_removido;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f){
  if (f == NULL){
    return -1; 
  }

  else {
    return f->num;
  }
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f){
  if (f == NULL || f->prim == NULL)
    return;

  struct fpnodo_t *atual = f->prim;
  int primeiro = 1;

  while (atual != NULL){

    if (!primeiro)
      printf(" ");
    
    printf("(%d %d)", atual->tipo, atual->prio);
    primeiro = 0;

    atual = atual->prox;

  }
}