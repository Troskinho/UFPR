// programa principal do projeto "The Boys - 2025/2"
// Autor: Gabriel de Oliveira Ostroski, GRR 20240487

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <math.h> 
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "lista.h"
#include "mundo.h"

// programa principal
int main () {

  srand(time(NULL));
  struct mundo *w = criarMundo();
  iniciarMundo(w);

  for (int i = 0; i < w->nHerois; i++){
    int base = aleat(0, w->nBases - 1);
    int tempo = aleat(0, 4320);
    agendarEvento(w, tempo, CHEGA, i, base);
  }

  for (int i = 0; i < w->nMissoes; i++){
    int tempo = aleat(0, T_FIM_DO_MUNDO);
    agendarEvento(w, tempo, MISSAO, i, -1);
  }

  agendarEvento(w, T_FIM_DO_MUNDO, FIM, 0, 0);

  int tipoEvento; 
  int tempoEvento;
  struct evento *ev;

  while ((ev = (struct evento*) fprio_retira(w->lef, &tipoEvento, &tempoEvento)) != NULL) {

    w->tempoAtual = tempoEvento;
    w->eventosTratados++;

    switch (tipoEvento){
      case CHEGA: eventoChega(w, ev->tempo, ev->dado1, ev->dado2); break;
      case ESPERA: eventoEspera(w, ev->tempo, ev->dado1, ev->dado2); break;
      case DESISTE: eventoDesiste(w, ev->tempo, ev->dado1, ev->dado2); break;
      case AVISA: eventoAvisa(w, ev->tempo, ev->dado1); break;
      case ENTRA: eventoEntra(w, ev->tempo, ev->dado1, ev->dado2); break;
      case SAI: eventoSai(w, ev->tempo, ev->dado1, ev->dado2); break;
      case VIAJA: eventoViaja(w, ev->tempo, ev->dado1, ev->dado2); break;
      case MORRE: eventoMorre(w, ev->tempo, ev->dado1, ev->dado2); break;
      case MISSAO: eventoMissao(w, ev->tempo, ev->dado1); break;
      case FIM:  eventoFim(w, ev->tempo); break;
    }
    free(ev);

    if (tipoEvento == FIM) break;
  }

  destruirMundo(w);
  return 0;
}
