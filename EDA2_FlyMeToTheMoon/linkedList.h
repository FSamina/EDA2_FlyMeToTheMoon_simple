#include "hashtable.h"

void print_list(struct linkedFlights *head);

struct linkedFlights *searchList(struct linkedFlights *head, char IdAirChegada_search[5]);

struct linkedFlights *add(struct linkedFlights *linkedFlights,
                          char IdAirPartida[5],
                          char IdAirChegada[5],
                          short hourPartida,
                          short minutePartida,
                          short tempTotal);

struct linkedFlights *add_from_disk(struct linkedFlights *linkedFlights,
                          char IdAirPartida[5],
                          char IdAirChegada[5],
                          short hourPartida,
                          short minutePartida,
                          short tempTotal);



struct linkedFlights *remove_linkedFlights(struct linkedFlights *head,
                                           char IdAirPartida_remove[5],
                                           char IdAirChegada_remove[5],
                                           short hourPartida,
                                           short minutePartida) ;