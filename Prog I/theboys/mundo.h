#ifndef MUNDO
#define MUNDO

#include <stdbool.h>
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

//defines para os tipos de Eventos
#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MORRE 8
#define MISSAO 9
#define FIM 0

 

struct heroi {
    int id; //identifica o heroi
    struct cjto_t *habilidades; //conjunto de habilidades do heroi
    int paciencia; //indica o quao paciente o heroi eh
    int velocidade; //velocidade de deslocamento     do heroi
    int experiencia; //numero de missoes que o heroi ja participou
    int baseAtual; //base que o heroi se encontra no momento
    int status; //1 vivo e 0 morto 
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
    int id; //numero que identifica a misso
    struct cjto_t *habilidades; //conjutno de habilidades necessarias na missao
    struct coordenada *local; //usa a struct de coordenada para definir o local da missao
    int tentativas; //controla as tentativas de realizar a missao
} ;

struct evento {
    int tempo; 
    int tipo; 
    int dado1; // dado generico 1
    int dado2; // dado generico 2
} ;

struct mundo {
    int nHerois;  //numeto total de herois no mundo
    struct heroi **herois; //vetor que esta representando os herois possiveis
    int nBases;  //numero total de bases no mundo;
    struct base **bases; //vetor que esta representando as bases possiveis
    int nMissoes; //numero total de missoes no mundo.
    struct missao **missoes; //vetor que esta representando as missoes possiveis
    int nHabilidades; //numero de habilidades diferentes possiveis no mundo
    int nCompostosV;  //numeor de compostos v disponiveis no mundo
    struct coordenada *tamanhoMundo; // coordenadas maximas do tamanho do mundo 
    int tempoAtual; //tempo atual do mundo
    struct fprio_t *lef; // Lista de Eventos Futuros
    
    int eventosTratados; //contador para o evento fim
    int missoesCump; //missoes concluidas com sucesso
    int mortosPorCompostoV; // contador para herois que morreram pelo composto V
    int totalTentativas; //contador de missoes realizadas
};

//funcao ira retornar um numero pseudoaleatorio em um dado intervalo
 int aleat(int min, int max);

 // struct responsavel por criar o mundo
 struct mundo *criarMundo();

 //struct que inicia o mundo, os herois, bases e missoes tudo junto
 void iniciarMundo(struct mundo *w);

//struct que destroi o mundo
 void destruirMundo(struct mundo *w);

 //algoritmo de ordenação auxiliar
 //ordena bases por distância (saber qual está mais prox para os eventos)
 void insertionSort(struct distancia *d, int n);

 //funcao auxiliar para agendar eventos da lista
 void agendarEvento(struct mundo *w, int tempo, int tipo, int d1, int d2);

 //funcao destinada a tratar do evento chega
void eventoChega(struct mundo *w, int tempo, int heroiID, int baseID);

 //funcao destinada a tratar do evento espera
void eventoEspera(struct mundo *w, int tempo, int heroiID, int baseID);

 //funcao destinada a tratar do evento desiste
void eventoDesiste(struct mundo *w, int tempo, int heroiID, int baseID);

 //funcao destinada a tratar do evento avisa
void eventoAvisa(struct mundo *w, int tempo, int baseID);

 //funcao destinada a tratar do evento entra
void eventoEntra(struct mundo *w, int tempo, int heroiID, int baseID);

 //funcao destinada a tratar do evento sair
void eventoSai(struct mundo *w, int tempo, int heroiID, int baseID);

 //funcao destinada a tratar do evento viaja
void eventoViaja(struct mundo *w, int tempo, int heroiID, int IDdestino);

 //funcao destinada a tratar do evento morre
void eventoMorre(struct mundo *w, int tempo, int heroiID, int missaoID);

 //funcao destinada a tratar do evento missao
void eventoMissao(struct mundo *w, int tempo, int missaoID);

 //funcao destinada a tratar do fim da simulação
void eventoFim(struct mundo *w, int tempo);

#endif 