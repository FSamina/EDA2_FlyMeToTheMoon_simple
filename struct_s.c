#include <stdio.h>

struct flights{
    char IdAirChegada[5];
    short hourChegada;
    short minuteChegada;
    short tempTotal;
};

struct linked_fligts{
    struct flights data;
    struct flights *son;
};


struct AirFlights{
    char Id[5];
    struct linked_flights;
    char IdPrecessor[5];
    short tempoTotalDiskt;
};


int main() {
    printf("%lu + %lu",sizeof(struct AirFlights)*400009, sizeof(struct linked_fligts)*750000);
    return 0;
}