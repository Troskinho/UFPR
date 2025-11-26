#ifndef PERSONA
#define PERSONA

#include "fila.h"
#include "fprio.h"
#include "conjunto.h"
#include "lista.h"


struct heroi {
    int heroiID; //identifica o heroi
    struct cjto_t *habilidades; //conjunto de habilidades do heroi
    int paciencia; //indica o quao paciente o heroi eh
    int velocidade; //velocidade de deslocamento do heroi
    int experiencia; //numero de missoes que o heroi ja participou
    int baseID; //base que o heroi se encontra no momento
    int status; //0 - vivo e 1 - morto
}

struct base {
    int IDbase; //numero que identifica cada base
    int lotacao; //numero de heroi maximos que a base comporta
    struct cjto_t *presentes; //conjunto de ids dos herois presentes no momento na base
    struct fila_t *espera; //fila de herois que estão esperando para entrar na base
    int baseX, baseY; //coordenadas que definem o local da base 
}

struct missao {
    int missaoID; //numero que identifica a misso
    struct cjto_t *habilidades; //conjutno de habilidades necessarias na missao
    int missaoX, missaoY; //coordenads que definem o local da missao
    int attempt; //numero de tentativas de realizar a missao
}

struct mundo {
    int NHerois; //numeto total de herois no mundo
    struct heroi vetor_de_herois[Numero_de_Herois]; //vetor que esta representando os herois possiveis
    int NBases; //numero total de bases no mundo;
    struct base vetor_de_bases[Numero_de_Bases]; //vetor que esta representando as bases possiveis
    int NMissoes; //numero total de missoes no mundo.
    struct missao vetor_de_missoes[Numero_de_Missoes]; //vetor que esta representando as missoes possiveis
    int NHabilidades; //numero de habilidades diferentes possiveis no mundo
    int NCompostosV;  //numeor de compostos v disponiveis no mundo
    int TamanhoMundo; //coordenadas maximas do tamanho do mundo
    int Tempo; //tempo atual do mundo
    struct fprio_t lista_eventos; // lista de eventos futuros
    int eventosTratados; //contador para o evento fim
    int mortosPorCompostoV; // contador para herois que morreram pelo composto V
    int heroisIniciais; //contador de herois para calcular a mortalidade posteriormente
 }

#endif 