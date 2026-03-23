#ifndef ENUMERATOR_UTIL_H
#define ENUMERATOR_UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

void print_byte_binary(uint8_t word);

void print_short_binary(unsigned short word);

void fprint_short_binary(FILE* fp, unsigned short word);

void print_bit_vector(unsigned short (&bits)[16]);

void fprint_bit_vector(FILE* fp, unsigned short (&bits)[16]);

void print_bit_vector_quads(unsigned short (&bits)[16]);

void fprint_bit_vector_quads(FILE* fp, unsigned short (&bits)[16]);

void create_bit_vector(unsigned short (&bits)[16], int argc, uint8_t (&args)[]);

void print_quad(uint8_t word);

void fprint_quad(FILE* fp, uint8_t word);

void print_quads (vector<uint8_t> sequence);

void fprint_quads(FILE* fp, vector<uint8_t> sequence);

void print_buckets_quad(vector<vector<uint8_t>> buckets);

uint8_t permutate(uint8_t word, uint8_t* mapping);

bool compare_bit_vectors(unsigned short (&first)[16], unsigned short (&second)[16]);

#endif
