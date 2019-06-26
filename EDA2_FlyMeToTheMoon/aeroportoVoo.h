#include <stdio.h>
#include <stdbool.h>


#define voosPorAir 150
struct voos
{
    char IdAirPartida[5];
    char IdAirChegada[5];
    short hourPartida;
    short minutePartida;
    short tempTotal;//Duração do voo
};

struct linkedFlights
{
    struct voos data;
    struct linkedFlights * son;

};
struct air
{
    char Id[5];
    struct linkedFlights *linkedVoos;
    struct voos * vooP;//P
    short hourProntoParaPartir;//Tempo
    short minProntoParaPartir;//Tempo
    short tempoTotalDiskt; //NOSSO D
};
