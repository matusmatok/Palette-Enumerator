#include "enumerator_util.h"

using namespace std;

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c\n"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0') 

#define SHORT_TO_BINARY_PATTERN "%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c\n"
#define SHORT_TO_BINARY(word)   \
  ((word) & 0x8000 ? '1' : '0'), \
  ((word) & 0x4000 ? '1' : '0'), \
  ((word) & 0x2000 ? '1' : '0'), \
  ((word) & 0x1000 ? '1' : '0'), \
  ((word) & 0x0800 ? '1' : '0'), \
  ((word) & 0x0400 ? '1' : '0'), \
  ((word) & 0x0200 ? '1' : '0'), \
  ((word) & 0x0100 ? '1' : '0'), \
  ((word) & 0x0080 ? '1' : '0'), \
  ((word) & 0x0040 ? '1' : '0'), \
  ((word) & 0x0020 ? '1' : '0'), \
  ((word) & 0x0010 ? '1' : '0'), \
  ((word) & 0x0008 ? '1' : '0'), \
  ((word) & 0x0004 ? '1' : '0'), \
  ((word) & 0x0002 ? '1' : '0'), \
  ((word) & 0x0001 ? '1' : '0') 

#define BYTE_TO_QUAD_PATTERN "%u%u%u%u "
#define BYTE_TO_QUAD(byte)   \
  (((byte) & 0xc2) >> 6),   \
  (((byte) & 0x30) >> 4),   \
  (((byte) & 0x0c) >> 2),   \
  ((byte) & 0x03)


void print_byte_binary(uint8_t word) {
	printf(BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(word));
}

void print_short_binary(unsigned short word) {
    printf(SHORT_TO_BINARY_PATTERN, SHORT_TO_BINARY(word));
}

void fprint_short_binary(FILE* fp, unsigned short word) {
    fprintf(fp, SHORT_TO_BINARY_PATTERN, SHORT_TO_BINARY(word));
}

void print_bit_vector(unsigned short (&bits)[16]) {
    for (int i = 0; i < 16; i++) {
        print_short_binary(bits[i]);
        if (i % 4 == 3) printf("-------------------\n");
    }
}

void fprint_bit_vector(FILE* fp, unsigned short (&bits)[16]) {
    for (int i = 0; i < 16; i++) {
        fprint_short_binary(fp, bits[i]);
        if (i % 4 == 3) fprintf(fp, "\n");
    }
}

void print_bit_vector_quads(unsigned short (&bits)[16]){
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (bits[i] & (0x8000 >> j)) {
                print_quad((uint8_t) (i << 4) | j);
            }
        }
    }
    printf("\n");
}

void fprint_bit_vector_quads(FILE* fp, unsigned short (&bits)[16]) {
    for (int i = 0; i < 16; i++) {
        for (int j = 0; j < 16; j++) {
            if (bits[i] & (0x8000 >> j)) {
                fprint_quad(fp, (uint8_t) (i << 4) | j);
            }
        }
    }
    fprintf(fp, "\n");
}

void create_bit_vector(unsigned short (&bits)[16], int argc, uint8_t (&args)[]) {
    for (int i = 0; i < argc; i++) {
        bits[(args[i] & 0xf0) >> 4] |= (0x8000 >> (args[i] & 0xf)); 
    }
}

void print_quad(uint8_t word) {
    printf(BYTE_TO_QUAD_PATTERN, BYTE_TO_QUAD(word));
}

void fprint_quad(FILE* fp, uint8_t word) {
    fprintf(fp, BYTE_TO_QUAD_PATTERN, BYTE_TO_QUAD(word));
}

void print_quads(vector<uint8_t> sequence) {
    for (auto quad : sequence) {
        print_quad(quad);
    }
    printf("\n");
}

void fprint_quads(FILE* fp, vector<uint8_t> sequence) {
    for (auto quad : sequence) {
        fprint_quad(fp, quad);
        fprintf(fp, " ");
    }
    fprintf(fp, "\n");
}

void print_buckets_quad(vector<vector<uint8_t>> buckets) {
    for (auto bucket = buckets.begin(); bucket != buckets.end(); bucket++){
        printf("{");
        for (auto quad = bucket->begin(); quad != bucket->end(); quad++) {
            print_quad(*quad);
            printf(", ");
        }
        printf("}\n");
    }
}

uint8_t FIRST_BITS_MASK = 170;
uint8_t zeros = 0;
uint8_t ones = 85;
uint8_t twos = 170;
uint8_t threes = 255;

uint8_t MASKS[4] = {0,85,170,255};

uint8_t mask_for_in(uint8_t mask_for, uint8_t in) {
    uint8_t result = ~(in ^ mask_for);
    uint8_t shifted = (((FIRST_BITS_MASK & result) >> 1) & result);
    return (shifted | (shifted << 1));
}

uint8_t permutate(uint8_t word, uint8_t* mapping) {
    uint8_t result = 0;
    for (uint8_t i = 0; i < 4; i++) {
        uint8_t mask = mask_for_in(MASKS[i], word);
        uint8_t masked = mask & MASKS[mapping[i]];
        result |= masked;
    }        
    return result;
}

bool compare_bit_vectors(unsigned short (&first)[16], unsigned short (&second)[16]) {
    return equal(begin(first), end(first), begin(second));
}
