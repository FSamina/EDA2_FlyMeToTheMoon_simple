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
    struct voos * son;

};
struct air
{
    char Id[5];
    struct linkedFlights linkedVoos;    
    char IdPrecessor[5];
    short tempoTotalDiskt;
};





/*
int main(void)
{
    printf("Size of air = %lu Bytes  \nSize of voos = %lu  Bytes \n", sizeof(struct air),sizeof(struct voos));
    return -1;
}
 */

/*
struct air
{
    char Id[5];
    short hour;
    short minute;
    char IdPrecessor[5];
    short tempoTotalDiskt;

    bool flag;
};

struct voos
{
    char Id[7];
    char IdAirChegada[5];
    short hourPartida;
    short minutePartida;
    short hourChegada;
    short minuteChegada;
    short tempTotal;
};
*/