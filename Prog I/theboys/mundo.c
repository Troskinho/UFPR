#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "lista.h"
#include "mundo.h"


int aleat(int min, int max) {
    return rand() % (max - min + 1) + min;
}

struct mundo *criar_mundo(){
    struct mundo mundo;

    mundo.NHerois = N_HEROIS;
    mundo.NBases = N_BASES;
    mundo.NCompostosV = N_COMPOSTOS_V;
    mundo.NHabilidades = N_HABILIDADES;
    mundo.NMissoes = N_MISSOES;
    mundo.TamanhoMundo = N_TAMANHO_MUNDO;
    mundo.Tempo = 0;
    mundo.attempt = 0;

    for (int i = 0; i < N_HEROIS; i++) {
        mundo.vetor_de_herois[i].heroiID = i;
        mundo.vetor_de_herois[i].habilidades = cjto_aleat(aleat(1, 3), N_HABILIDADES);
        mundo.vetor_de_herois[i].paciencia = aleat(0, 100);
        mundo.vetor_de_herois[i].velocidade = aleat(50, 5000);
        mundo.vetor_de_herois[i].experiencia = 0;
        mundo.vetor_de_herois[i].baseAtual = -1;
        mundo.vetor_de_herois[i].status = 0;
    }

    for (int i = 0; i < N_BASES; i++) {
        mundo.vetor_de_bases[i].IDbase = i;
        mundo.vetor_de_bases[i].lotacao = aleat(3, 10);
        mundo.vetor_de_bases[i].presentes = cjto_cria(50);
        mundo.vetor_de_bases[i].espera = fila_cria();
        mundo.vetor_de_bases[i].local = aleat(0, N_TAMANHO_MUNDO - 1);
        mundo.vetor_de_bases[i].missoesConcluidas = 0;
    }

    for (int i = 0; i < N_MISSOES; i++) {
        mundo.vetor_de_missoes[i].missaoID = i;
    }

} 

void CHEGA(int tempo, int heroiID, int IDbase )  {

    heroi->baseAtual = base;

}