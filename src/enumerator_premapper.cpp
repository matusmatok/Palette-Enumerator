#include "enumerator_util.h"

#define SHORT_SIZE 65536

using namespace std;

unsigned short connections[16][2] ={
    {0,0}, //00
    {6, 7}, //01 -> 12,13
    {9, 11}, //02 -> 21,23
    {13, 14},//03 -> 31,32
    {2, 3},//10 -> 02,03
    {1,1},//11 
    {8, 11},//12 -> 20,23
    {12, 14},//13 -> 30,32
    {1, 3},//20 -> 01,03 
    {4, 7},//21 -> 10,13
    {2,2},//22
    {12, 13},//23 -> 30,31
    {1, 2},//30 -> 01,02
    {4, 6},//31 -> 10,12
    {8, 9},//32 -> 20,21
    {3,3}//33
};

void produce_connection_mapping(unsigned short (&mappings)[SHORT_SIZE]) {

    for (int i = 0; i < SHORT_SIZE; i++) {
        unsigned short result = 0;
        for (int j = 0; j < 16; j++) {
            if ((0x8000 >> j) & i) {
                result |= (0x8000 >> connections[j][0]);
                result |= (0x8000 >> connections[j][1]);
            }
        }
        mappings[i] = result;
    }
}

void produce_permutation_mapping(uint8_t *perm, unsigned short (&mapping)[SHORT_SIZE]) {
    for(int i = 0; i < SHORT_SIZE; i++) {
        unsigned short result = 0;
        for (uint8_t j = 0; j < 16; j++) {
            if ((0x8000 >> j) & i) {
                result |= (0x8000 >> (permutate(j, perm) & 0xf));   
            }       
        }
        mapping[i] = result;
    }
}

void produce_permutation_bucket_mapping(uint8_t *perm, uint8_t *mapping) {    
    for (uint8_t i = 0; i < 16; i++) {
        mapping[i] = 0xf & permutate(i, perm);
    }
}

void produce_full_bit_map(unsigned short (&bit_map)[16]) {
    for (int i = 0; i < 256; i++) {
        if ((i & 0xc0) != ((i & 0x30) << 2) && (i & 0xc) != ((i & 0x3) << 2)) {
            bit_map[(i & 0xf0) >> 4] |= 0x8000 >> (i & 0xf);
        }
    }
}

//abcd: a != d && a != 0 && d != 0 && (abcd neobsahuje zaroven 2 a 3)
void produce_extendable_bit_map(unsigned short (&bit_map)[16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            int a = (i & 0xc) >> 2;
            int d = (j & 0x3);
            if (a != d && a != 0 && d != 0) {
                int b = i & 0x3;
                int c = (j & 0xc) >> 2;
                bool contains_2 = (a == 2 || b == 2 || c == 2 || d == 2);
                bool contains_3 = (a == 3 || b == 3 || c == 3 || d == 3);
                if (!(contains_2 & contains_3)) {
                    bit_map[i] |= 0x8000 >> j;
                }
            }
        }    
    } 
}

void produce_extendable_bit_map_avd_2(unsigned short (&bit_map)[16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            int a = (i & 0xc) >> 2;
            int d = (j & 0x3);
            if (a != d && a != 0 && d != 0) {
                int b = i & 0x3;
                int c = (j & 0xc) >> 2;
                bool contains_1 = (a == 1 || b == 1 || c == 1 || d == 1);
                bool contains_2 = (a == 2 || b == 2 || c == 2 || d == 2);
                bool contains_3 = (a == 3 || b == 3 || c == 3 || d == 3);
                if (!(contains_1 & contains_2 & contains_3)) {
                    bit_map[i] |= 0x8000 >> j;
                }
            }
        }    
    } 
}

void produce_extendable_bit_map_savd_2(unsigned short (&bit_map)[16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            int a = (i & 0xc) >> 2;
            int d = (j & 0x3);
            int b = i & 0x3;
            int c = (j & 0xc) >> 2;
            if (a != 3 && b != 3 && c != 3 && d != 3 && a != d && a!= 0 && d != 0) {
                bit_map[i] |= 0x8000 >> j;
            }
        }    
    } 
}
