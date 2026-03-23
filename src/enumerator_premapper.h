#ifndef ENUMERATOR_PREMAPPER_H
#define ENUMERATOR_PREMAPPER_H
#define SHORT_SIZE 65536

#include "enumerator_util.h"

void produce_connection_mapping(unsigned short (&mappings)[SHORT_SIZE]);

void produce_permutation_mapping(uint8_t *perm, unsigned short (&mapping)[SHORT_SIZE]);

void produce_permutation_bucket_mapping(uint8_t *perm, uint8_t *mapping);

void produce_full_bit_map(unsigned short (&bit_map)[16]);

void produce_extendable_bit_map(unsigned short (&bit_map)[16]);

void produce_extendable_bit_map_avd_2(unsigned short (&bit_map)[16]);

void produce_extendable_bit_map_savd_2(unsigned short (&bit_map)[16]);

#endif
