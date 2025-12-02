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


int aleat(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void insertionSort(struct distancia *d, int n) {
    for (int i = 1; i < n; i++) {
        struct distancia aux = d[i];
        int j = i - 1;
        while (j >= 0 && d[j].distance > aux.distance) {
            d[j + 1] = d[j];
            j--;
        }
        d[j + 1] = aux;
    }
}

void agendarEvento(struct mundo *w, int tempo, int tipo, int d1, int d2) {
    struct evento *ev = malloc(sizeof(struct evento));
    if (ev) {
        ev->tempo = tempo;
        ev->tipo = tipo;
        ev->dado1 = d1;
        ev->dado2 = d2;
        
        fprio_insere(w->lef, ev, tipo, tempo);
    }
}

struct heroi *criarHerois(int id) {
    
    struct heroi *h = malloc(sizeof(struct heroi));
    
    h->id = id;
    h->experiencia = 0;
    h->paciencia = aleat(0, 100);
    h->velocidade = aleat(50, 5000); 
    h->baseAtual = -1;
    h->status = 1; 
    h->habilidades = cjto_cria(N_HABILIDADES);
    
    int tam = aleat(1, 3);
    while (cjto_card(h->habilidades) < tam)
        cjto_insere(h->habilidades, aleat(0, N_HABILIDADES - 1));
        
    return h;
}

struct base *criarBase(int id) {

    struct base *b = malloc(sizeof(struct base));

    b->local = malloc(sizeof(struct coordenada));
    b->IDbase = id;
    b->local->x = aleat(0, N_TAMANHO_MUNDO);
    b->local->y = aleat(0, N_TAMANHO_MUNDO);
    b->lotacao = aleat(3, 10);
    b->presentes = cjto_cria(N_HEROIS);
    b->espera = fila_cria(); 
    b->missoesConcluidas = 0;

    return b;
}


struct missao *criarMissao(int id) {

    struct missao *m = malloc(sizeof(struct missao));

    m->local = malloc(sizeof(struct coordenada));
    m->id = id;
    m->tentativas = 0;
    m->local->x = aleat(0, N_TAMANHO_MUNDO);
    m->local->y = aleat(0, N_TAMANHO_MUNDO);
    m->habilidades = cjto_cria(N_HABILIDADES);
    
    int tam = aleat(6, 10);
    while (cjto_card(m->habilidades) < tam)
        cjto_insere(m->habilidades, aleat(0, N_HABILIDADES - 1));
    return m;
}

struct mundo *criarMundo() {

    struct mundo *w = malloc(sizeof(struct mundo));
    if (!w) return NULL;

    w->tamanhoMundo = malloc(sizeof(struct coordenada));
    w->tamanhoMundo->x = N_TAMANHO_MUNDO;
    w->tamanhoMundo->y = N_TAMANHO_MUNDO;
    
    w->nHerois = N_HEROIS;
    w->nBases = N_BASES;
    w->nMissoes = N_MISSOES;
    w->nHabilidades = N_HABILIDADES;
    w->nCompostosV = N_COMPOSTOS_V;
    
    w->tempoAtual = T_INICIO;
    w->eventosTratados = 0;
    w->missoesCump = 0;
    w->mortosPorCompostoV = 0;
    w->totalTentativas = 0;
    
    w->lef = fprio_cria();
    
    return w;
}

void iniciarMundo(struct mundo *w) {
    w->herois = malloc(w->nHerois * sizeof(struct heroi*));
    for (int i = 0; i < w->nHerois; i++) w->herois[i] = criarHerois(i);

    w->bases = malloc(w->nBases * sizeof(struct base*));
    for (int i = 0; i < w->nBases; i++) w->bases[i] = criarBase(i);

    w->missoes = malloc(w->nMissoes * sizeof(struct missao*));
    for (int i = 0; i < w->nMissoes; i++) w->missoes[i] = criarMissao(i);
}


void destruirMundo(struct mundo *w) {
    // destroi herois
    for (int i = 0; i < w->nHerois; i++) {
        cjto_destroi(w->herois[i]->habilidades);
        free(w->herois[i]);
    }
    free(w->herois);

    // destroi as bases
    for (int i = 0; i < w->nBases; i++) {
        cjto_destroi(w->bases[i]->presentes);
        fila_destroi(w->bases[i]->espera);
        free(w->bases[i]->local);
        free(w->bases[i]);
    }
    free(w->bases);

    // destroi as missoes
    for (int i = 0; i < w->nMissoes; i++) {
        cjto_destroi(w->missoes[i]->habilidades);
        free(w->missoes[i]->local);
        free(w->missoes[i]);
    }
    free(w->missoes);

    // destroi a atual lista de eventos futuros e por fim, o mundo
    fprio_destroi(w->lef);
    free(w->tamanhoMundo);
    free(w);
}

void eventoChega(struct mundo *w, int tempo, int heroiID, int baseID) {
    struct base *b = w->bases[baseID];
    struct heroi *h = w->herois[heroiID];
    
    if (h->status == 0) return;

    h->baseAtual = baseID;
    int espera = 0; //é uma variavel booleana pra poder definir qual evento se seguirá
    
    if (cjto_card(b->presentes) < b->lotacao && fila_tamanho(b->espera) == 0) {
        espera = 1;
    } else {
        if (h->paciencia > (10 * fila_tamanho(b->espera)))
            espera = 1;
        else
            espera = 0;
    }

    if (espera) {
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n", 
               tempo, heroiID, baseID, cjto_card(b->presentes), b->lotacao);
        agendarEvento(w, tempo, ESPERA, heroiID, baseID);
    } else {
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", 
               tempo, heroiID, baseID, cjto_card(b->presentes), b->lotacao);
        agendarEvento(w, tempo, DESISTE, heroiID, baseID);
    }
}

void eventoEspera(struct mundo *w, int tempo, int heroiID, int baseID) {
    struct base *b = w->bases[baseID];
    struct heroi *h = w->herois[heroiID];
    if (h->status == 0) return;

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", 
           tempo, heroiID, baseID, fila_tamanho(b->espera));

    fila_insere(b->espera, heroiID);
    agendarEvento(w, tempo, AVISA, baseID, -1);
}

void eventoDesiste(struct mundo *w, int tempo, int heroiID, int baseID) {
    struct heroi *h = w->herois[heroiID];
    if (h->status == 0) return;

    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroiID, baseID);

    int destino = aleat(0, w->nBases - 1);
    agendarEvento(w, tempo, VIAJA, heroiID, destino);
}

void eventoAvisa(struct mundo *w, int tempo, int baseID) {
    struct base *b = w->bases[baseID];
    
    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
           tempo, baseID, cjto_card(b->presentes), b->lotacao);
    fila_imprime(b->espera); 
    printf(" ]\n");

    while (cjto_card(b->presentes) < b->lotacao && fila_tamanho(b->espera) > 0) {
        int heroiID;
        fila_retira(b->espera, &heroiID);
        cjto_insere(b->presentes, heroiID);
        
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", tempo, baseID, heroiID);
        agendarEvento(w, tempo, ENTRA, heroiID, baseID);
    }
}

void eventoEntra(struct mundo *w, int tempo, int heroiID, int baseID) {
    struct heroi *h = w->herois[heroiID];
    struct base *b = w->bases[baseID];
    if (h->status == 0) return;

    int tempoPermanencia = 15 + h->paciencia + aleat(1, 20); //tempo de permanencia do heroi na base
    int tempoSair = tempo + tempoPermanencia; //tempo da saida da base 

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", 
           tempo, heroiID, baseID, cjto_card(b->presentes), b->lotacao, tempoSair);
           
    agendarEvento(w, tempoSair, SAI, heroiID, baseID);
}

void eventoSai(struct mundo *w, int tempo, int heroiID, int baseID) {
    struct base *b = w->bases[baseID];
    struct heroi *h = w->herois[heroiID];
    if (h->status == 0) return;

    cjto_retira(b->presentes, heroiID);
    
    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", 
           tempo, heroiID, baseID, cjto_card(b->presentes), b->lotacao);

    int dest = aleat(0, w->nBases - 1);
    agendarEvento(w, tempo, VIAJA, heroiID, dest);
    agendarEvento(w, tempo, AVISA, baseID, -1); 
}

void eventoViaja(struct mundo *w, int tempo, int heroiID, int IDdestino) {
    struct heroi *h = w->herois[heroiID];
    struct base *atual = (h->baseAtual != -1) ? w->bases[h->baseAtual] : w->bases[IDdestino];
    struct base *destino = w->bases[IDdestino];
    
    if (h->status == 0) return;

    int dist = (int)sqrt(pow(atual->local->x - destino->local->x, 2) + 
                         pow(atual->local->y - destino->local->y, 2));
    
    int duracao = dist / h->velocidade;
    int chegada = tempo + duracao;

    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n",
           tempo, heroiID, h->baseAtual, IDdestino, dist, h->velocidade, chegada);

    agendarEvento(w, chegada, CHEGA, heroiID, IDdestino);
}

void eventoMorre(struct mundo *w, int tempo, int heroiID, int missaoID) {
    struct heroi *h = w->herois[heroiID];
    struct base *b = w->bases[h->baseAtual];
    
    h->status = 0;
    cjto_retira(b->presentes, heroiID);
    
    printf("%6d: MORRE HEROI %2d MISSAO %d\n", tempo, heroiID, missaoID);
    
    agendarEvento(w, tempo, AVISA, b->IDbase, -1);
}

void eventoMissao(struct mundo *w, int tempo, int missaoID) {
    struct missao *m = w->missoes[missaoID];
    m->tentativas++;
    w->totalTentativas++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", tempo, missaoID, m->tentativas);
    cjto_imprime(m->habilidades);
    printf(" ]\n");

    struct distancia distancia[w->nBases];
    for (int i = 0; i < w->nBases; i++) {
        distancia[i].baseID = i;
        distancia[i].distance = (int)sqrt(pow(m->local->x - w->bases[i]->local->x, 2) + 
                                  pow(m->local->y - w->bases[i]->local->y, 2));
    }
    insertionSort(distancia, w->nBases);

    int bmp_id = -1;
    for (int i = 0; i < w->nBases; i++) {
        struct base *b = w->bases[distancia[i].baseID];
        
        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", tempo, missaoID, b->IDbase, distancia[i].distance);
        cjto_imprime(b->presentes);
        printf(" ]\n");

        struct cjto_t *uniao = cjto_cria(N_HABILIDADES);
        
        for(int k=0; k < w->nHerois; k++){
            if (w->herois[k]->baseAtual == b->IDbase && w->herois[k]->status == 1 && cjto_pertence(b->presentes, k)) {
                 printf("%6d: MISSAO %d HAB HEROI %2d: [ ", tempo, missaoID, k);
                 cjto_imprime(w->herois[k]->habilidades);
                 printf(" ]\n");

                 struct cjto_t *temp = cjto_uniao(uniao, w->herois[k]->habilidades);
                 cjto_destroi(uniao);
                 uniao = temp;
            }
        }
        
        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", tempo, missaoID, b->IDbase);
        cjto_imprime(uniao);
        printf(" ]\n");

        if (cjto_contem(uniao, m->habilidades)) {
            bmp_id = b->IDbase;
            cjto_destroi(uniao);
            break;
        }
        cjto_destroi(uniao);
    }

    if (bmp_id != -1) {
        // missao bem sucedida 
        struct base *b = w->bases[bmp_id];
        printf("%6d: MISSAO %d CUMPRIDA BASE %d\n", tempo, missaoID, bmp_id);
        w->missoesCump++;
        b->missoesConcluidas++;
        
        // aumenta a experiencia do heroi 
        for(int k=0; k < w->nHerois; k++){
            if (w->herois[k]->baseAtual == bmp_id && w->herois[k]->status == 1) {
                w->herois[k]->experiencia++;
            }
        }
    } else {
        //usa o composto v
        if (w->nCompostosV > 0 && (tempo % 2500 == 0)) {
             int target_base = distancia[0].baseID; 
             
             // busca por um heroi com maior experiencia
             int max_exp = -1;
             int heroi_v = -1;
             for(int k=0; k < w->nHerois; k++){
                if (w->herois[k]->baseAtual == target_base && w->herois[k]->status == 1) {
                    if (w->herois[k]->experiencia > max_exp) {
                        max_exp = w->herois[k]->experiencia;
                        heroi_v = k;
                    }
                }
             }

             if (heroi_v != -1) {
                 w->nCompostosV--;
                 w->mortosPorCompostoV++;
                 w->missoesCump++;
                 printf("%6d: MISSAO %d CUMPRIDA BASE %d (COMPOSTO V)\n", tempo, missaoID, target_base);
                 
                 agendarEvento(w, tempo, MORRE, heroi_v, missaoID);
                 
                 for(int k=0; k < w->nHerois; k++){
                    if (w->herois[k]->baseAtual == target_base && w->herois[k]->status == 1 && k != heroi_v) {
                        w->herois[k]->experiencia++;
                    }
                }
                return;
             }
        }
        printf("%6d: MISSAO %d IMPOSSIVEL\n", tempo, missaoID);
        agendarEvento(w, tempo + 24*60, MISSAO, missaoID, -1);
    }
}

void eventoFim(struct mundo *w, int tempo) {
    printf("%6d: FIM\n", tempo);
    
    for (int i = 0; i < w->nHerois; i++) {
        struct heroi *h = w->herois[i];
        printf("HEROI %2d %s PAC %3d VEL %4d EXP %4d HABS [ ", 
               i, (h->status ? "VIVO" : "MORTO"), h->paciencia, h->velocidade, h->experiencia);
        cjto_imprime(h->habilidades);
        printf(" ]\n");
    }

    for (int i = 0; i < w->nBases; i++) {
        struct base *b = w->bases[i];
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", 
               i, b->lotacao, -1, b->missoesConcluidas);
    }

    int total_mortos = 0;
    for(int i=0; i<w->nHerois; i++) if(w->herois[i]->status == 0) total_mortos++;
    float taxa_mortalidade = ((float)total_mortos / w->nHerois) * 100.0;

    printf("EVENTOS TRATADOS: %d\n", w->eventosTratados);
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", w->missoesCump, w->nMissoes, ((float)w->missoesCump/w->nMissoes)*100);
    printf("TENTATIVAS/MISSAO: MEDIA %.1f\n", (float)w->totalTentativas / w->nMissoes);
    printf("TAXA MORTALIDADE: %.1f%%\n", taxa_mortalidade);
}