#include <stdio.h>
#include <stdbool.h>

#define voosPorAir 150 // no maximo há 150 voos por aeroporto
struct voos
{
    char IdAirPartida[5];//Id do aeroporto de partida
    char IdAirChegada[5];//id do aeropoto de chegada
    unsigned short hourPartida;//hora de partida do voo
    unsigned short minutePartida;//minutos de partida do voo
    unsigned short tempTotal;//Duração do voo
};

struct linkedFlights//Linked list dos voos 
{
    struct voos data;//Voo
    struct linkedFlights * son;//voo Filho

};
struct air
{
    char id[5]; 
    struct linkedFlights *linkedVoos;//conjunto dos voos todos de um aeroporto
    struct voos vooP;//Voo predecessor deste aeroporto ( algoritmo de Dijkstra)
    short hourProntoParaPartir;//hora a que estamos prontos para entrar num novo voo
    short minProntoParaPartir;//minuto a que estamos prontos para entrar num novo voo
    unsigned int tempoTotalDijkstra; //Nosso "d" ( algoritmo de Dijkstra)
    int indexNaHeap; // para sabermos o index deste aeroporto na heap
    bool inHeap; // para garantirmos que um aeroporto so entra uma fez na heap
};
