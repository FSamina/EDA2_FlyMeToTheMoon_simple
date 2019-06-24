#include <stdio.h>
#include <stdbool.h>


#define voosPorAir 150
struct voos
{
    char IdAirChegada[5];
    short hourPartida;
    short minutePartida;
    short tempTotal;
};

struct linkedFlights
{
    struct voos data;
    struct linkedFlights * son;

};
struct air
{
    char Id[5];
    struct linkedFlights linkedVoos;    
    char IdPrecessor[5];
    short tempoTotalDiskt;
};
