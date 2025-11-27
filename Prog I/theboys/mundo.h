#ifndef PERSONA
#define PERSONA

#include "fila.h"
#include "fprio.h"
#include "conjunto.h"
#include "lista.h"

//defines referentes ao mundo
#define T_INICIO 0 //tempo inicial
#define T_FIM_DO_MUNDO 525600 //tempo final em minutos
#define N_TAMANHO_MUNDO 20000 // tamanho do mundo
#define N_HABILIDADES 10 // Numero de habilidades
#define N_HEROIS (N_HABILIDADES * 5) //numero de herois
#define N_BASES (N_HEROIS / 5) //numero de bass
#define N_MISSOES (T_FIM_DO_MUNDO / 100) //numero de missoes
#define N_COMPOSTOS_V (N_HABILIDADES * 3) //numero de compostos v 

 

struct heroi {
    int heroiID; //identifica o heroi
    struct cjto_t *habilidades; //conjunto de habilidades do heroi
    int paciencia; //indica o quao paciente o heroi eh
    int velocidade; //velocidade de deslocamento do heroi
    int experiencia; //numero de missoes que o heroi ja participou
    int baseAtual; //base que o heroi se encontra no momento
    int status; //0 - vivo e 1 - morto
} ;

struct coordenada {
    int x;
    int y; //coordenadas no mundo
} ;

//distancia ate uma das bases
struct distancia {
    int baseID; 
    int distance; 
} ;

struct base {
    int IDbase; //numero que identifica cada base
    int lotacao; //numero de heroi maximos que a base comporta
    struct cjto_t *presentes; //conjunto de ids dos herois presentes no momento na base
    struct fila_t *espera; //fila de herois que estão esperando para entrar na base
    struct coordenada *local; //usa a struct de coordenada para definir o local da base
    int missoesConcluidas; //quantidade de missoes concluidas
} ;

struct missao {
    int missaoID; //numero que identifica a misso
    struct cjto_t *habilidades; //conjutno de habilidades necessarias na missao
    struct coordeanda *local; //usa a struct de coordenada para definir o local da missao
} ;

struct mundo {
    int NHerois; //numeto total de herois no mundo
    struct heroi vetor_de_herois[N_HEROIS]; //vetor que esta representando os herois possiveis
    int NBases; //numero total de bases no mundo;
    struct base vetor_de_bases[N_BASES]; //vetor que esta representando as bases possiveis
    int NMissoes; //numero total de missoes no mundo.
    struct missao vetor_de_missoes[N_MISSOES]; //vetor que esta representando as missoes possiveis
    int NHabilidades; //numero de habilidades diferentes possiveis no mundo
    int NCompostosV;  //numeor de compostos v disponiveis no mundo
    struct coordeanda *TamanhoMundo; //coordenadas maximas do tamanho do mundo 
    int Tempo; //tempo atual do mundo
    struct fprio_t lef; // lista de eventos futuros
    int eventosTratados; //contador para o evento fim
    int mortosPorCompostoV; // contador para herois que morreram pelo composto V
    int heroisIniciais; //contador de herois para calcular a mortalidade posteriormente
    int attempt; //numero de tentativas de realizar a missao

 } ;

 struct evento {
    int tempo; // tempor de duração do evento
    int heroiID; //id do heroi
    int baseID; //id da base
    int missaoID; //id da missao
    int tipoEvento; //tipo do evento
 } ;

//funcao ira retornar um numero pseudoaleatorio em um dado intervalo
 int aleat(int min, int max);






#endif 