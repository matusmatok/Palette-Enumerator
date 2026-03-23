#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>
#include "enumerator_util.h"
#include "enumerator_premapper.h"

using namespace std;

#define SHORT_SIZE 65536
#define MAX_SHORT 0xffff

struct halin_tripole {
    string expr;
    unsigned short bit_map[16] = {};
    unsigned short sub2_perms[16] = {};
    unsigned short sub3_perms2[16] = {};
    unsigned short sub3_perms3[16] = {};
};

unsigned short connection_mapping[SHORT_SIZE];
unsigned short full_bit_map[16] = {};
unsigned short extendable_pallete_bit_map[16] = {};
unsigned short extendable_pallete_bit_map_avd_2[16] = {};
unsigned short extendable_pallete_bit_map_savd_2[16] = {};

uint8_t all_perms[12][4] = {{2,0,1,3}, {2,0,3,1}, {2,1,0,3}, {2,1,3,0}, {2,3,0,1}, {2,3,1,0},
                            {3,0,1,2}, {3,0,2,1}, {3,1,0,2}, {3,1,2,0}, {3,2,0,1}, {3,2,1,0}};
unsigned short perm_mappings[12][SHORT_SIZE] = {};
uint8_t perm_bucket_mappings[12][16] = {};

/**TOTAL */
unsigned short (*total_sub3_perms2_mappings[4])[SHORT_SIZE] = {&(perm_mappings[0]), &(perm_mappings[1]), &(perm_mappings[4]), &(perm_mappings[5])};
unsigned short (*total_sub3_perms3_mappings[4])[SHORT_SIZE] = {&(perm_mappings[6]), &(perm_mappings[7]), &(perm_mappings[10]), &(perm_mappings[11])};

uint8_t (*total_sub3_perms2_bucket_mappings[4])[16] = {&(perm_bucket_mappings[0]), &(perm_bucket_mappings[1]), &(perm_bucket_mappings[4]), &(perm_bucket_mappings[5])};
uint8_t (*total_sub3_perms3_bucket_mappings[4])[16] = {&(perm_bucket_mappings[6]), &(perm_bucket_mappings[7]), &(perm_bucket_mappings[10]), &(perm_bucket_mappings[11])};

/**AVD 
 * avd_X_subY:
 * X -- permutations of tripole with root of degree X
 * Y -- which permutations, i.e., 2_perms, 3_perms2, 3_perms3
*/
unsigned short (*avd_2_sub2_perm_mappings[4])[SHORT_SIZE] = {&(perm_mappings[6]), &(perm_mappings[7]), &(perm_mappings[8]), &(perm_mappings[10])};
uint8_t (*avd_2_sub2_perm_bucket_mappings[4])[16] = {&(perm_bucket_mappings[6]), &(perm_bucket_mappings[7]), &(perm_bucket_mappings[8]), &(perm_bucket_mappings[10])};

unsigned short (*avd_2_sub3_perm2_mappings[6])[SHORT_SIZE] = {&(perm_mappings[0]),
                                                              &(perm_mappings[1]),
                                                              &(perm_mappings[2]),
                                                              &(perm_mappings[3]),
                                                              &(perm_mappings[4]),
                                                              &(perm_mappings[5])};
unsigned short (*avd_2_sub3_perm3_mappings[6])[SHORT_SIZE] = {&(perm_mappings[6]),
                                                              &(perm_mappings[7]),
                                                              &(perm_mappings[8]),
                                                              &(perm_mappings[9]),
                                                              &(perm_mappings[10]),
                                                              &(perm_mappings[11])};
uint8_t (*avd_2_sub3_perm2_bucket_mappings[6])[16] = {&(perm_bucket_mappings[0]),
                                                      &(perm_bucket_mappings[1]),
                                                      &(perm_bucket_mappings[2]),
                                                      &(perm_bucket_mappings[3]),
                                                      &(perm_bucket_mappings[4]), 
                                                      &(perm_bucket_mappings[5])};
uint8_t (*avd_2_sub3_perm3_bucket_mappings[6])[16] = {&(perm_bucket_mappings[6]), 
                                                      &(perm_bucket_mappings[7]), 
                                                      &(perm_bucket_mappings[8]),
                                                      &(perm_bucket_mappings[9]),
                                                      &(perm_bucket_mappings[10]),
                                                      &(perm_bucket_mappings[11])};
//----DEGREE 3 CASES
unsigned short (*avd_3_sub2_perm_mappings[6])[SHORT_SIZE] = {&(perm_mappings[6]),
                                                              &(perm_mappings[7]),
                                                              &(perm_mappings[8]),
                                                              &(perm_mappings[9]),
                                                              &(perm_mappings[10]),
                                                              &(perm_mappings[11])};
uint8_t (*avd_3_sub2_perm_bucket_mappings[6])[16] = {&(perm_bucket_mappings[6]), 
                                                      &(perm_bucket_mappings[7]), 
                                                      &(perm_bucket_mappings[8]),
                                                      &(perm_bucket_mappings[9]),
                                                      &(perm_bucket_mappings[10]),
                                                      &(perm_bucket_mappings[11])};

unsigned short (*avd_3_sub3_perm2_mappings[4])[SHORT_SIZE] = {&(perm_mappings[0]),
                                                              &(perm_mappings[1]),
                                                              &(perm_mappings[4]),
                                                              &(perm_mappings[5])};
unsigned short (*avd_3_sub3_perm3_mappings[4])[SHORT_SIZE] = {&(perm_mappings[6]),
                                                              &(perm_mappings[7]),
                                                              &(perm_mappings[10]),
                                                              &(perm_mappings[11])};
uint8_t (*avd_3_sub3_perm2_bucket_mappings[4])[16] = {&(perm_bucket_mappings[0]),
                                                      &(perm_bucket_mappings[1]),
                                                      &(perm_bucket_mappings[4]), 
                                                      &(perm_bucket_mappings[5])};
uint8_t (*avd_3_sub3_perm3_bucket_mappings[4])[16] = {&(perm_bucket_mappings[6]), 
                                                      &(perm_bucket_mappings[7]),
                                                      &(perm_bucket_mappings[10]),
                                                      &(perm_bucket_mappings[11])};

/**S-AVD */
//DEGREE 2-cases
unsigned short (*savd_2_sub2_perm_mappings[4])[SHORT_SIZE] = {&(perm_mappings[6]), &(perm_mappings[7]), &(perm_mappings[8]), &(perm_mappings[10])};
uint8_t (*savd_2_sub2_perm_bucket_mappings[4])[16] = {&(perm_bucket_mappings[6]), &(perm_bucket_mappings[7]), &(perm_bucket_mappings[8]), &(perm_bucket_mappings[10])};

unsigned short (*savd_2_sub3_perm2_mappings[2])[SHORT_SIZE] = {&(perm_mappings[1]),
                                                              &(perm_mappings[4])};
unsigned short (*savd_2_sub3_perm3_mappings[2])[SHORT_SIZE] = {&(perm_mappings[7]),
                                                              &(perm_mappings[10])};
uint8_t (*savd_2_sub3_perm2_bucket_mappings[2])[16] = {&(perm_bucket_mappings[1]),
                                                      &(perm_bucket_mappings[4])};
uint8_t (*savd_2_sub3_perm3_bucket_mappings[2])[16] = {&(perm_bucket_mappings[7]),
                                                      &(perm_bucket_mappings[10])};
//DEGREE 3-cases
unsigned short (*savd_3_sub2_perm_mappings[2])[SHORT_SIZE] = {&(perm_mappings[6]), &(perm_mappings[7])};
uint8_t (*savd_3_sub2_perm_bucket_mappings[2])[16] = {&(perm_bucket_mappings[6]), &(perm_bucket_mappings[7])};

unsigned short (*savd_3_sub3_perm2_mappings[4])[SHORT_SIZE] = {&(perm_mappings[0]),
                                                              &(perm_mappings[1]),
                                                              &(perm_mappings[4]),
                                                              &(perm_mappings[5])};
unsigned short (*savd_3_sub3_perm3_mappings[4])[SHORT_SIZE] = {&(perm_mappings[6]),
                                                              &(perm_mappings[7]),
                                                              &(perm_mappings[10]),
                                                              &(perm_mappings[11])};
uint8_t (*savd_3_sub3_perm2_bucket_mappings[4])[16] = {&(perm_bucket_mappings[0]),
                                                      &(perm_bucket_mappings[1]),
                                                      &(perm_bucket_mappings[4]), 
                                                      &(perm_bucket_mappings[5])};
uint8_t (*savd_3_sub3_perm3_bucket_mappings[4])[16] = {&(perm_bucket_mappings[6]), 
                                                      &(perm_bucket_mappings[7]),
                                                      &(perm_bucket_mappings[10]),
                                                      &(perm_bucket_mappings[11])};

void prepare_mappings() {
    produce_connection_mapping(connection_mapping);
    produce_full_bit_map(full_bit_map);
    produce_extendable_bit_map(extendable_pallete_bit_map);
    produce_extendable_bit_map_avd_2(extendable_pallete_bit_map_avd_2);
    produce_extendable_bit_map_savd_2(extendable_pallete_bit_map_savd_2);

    for(int i = 0; i < 12; i++) {
        produce_permutation_mapping(all_perms[i], perm_mappings[i]);
        produce_permutation_bucket_mapping(all_perms[i], perm_bucket_mappings[i]);
    }
}

/**
 * flags:
 * -b = prints bitmap, otherwise prints quads
 * -f = print tripoles with full pallets
 * -r = print reducible pairs; i. e. pairs with same pallet
 * -u = generate only tripoles with unique pallets, discard the rest
 * -n = only prints the number of tripoles on each tier
 * -N = prints only non-colourable halin graphs
 * -p = prints pallete parent count for each tripole, forces -u, as otherwise it does not make much sense 
 * -P (capital) = prints pallete parents for each tripole, forces -u
 * -s = generate sub-cubic graphs
 * -a = AVD colouring
 * -A = strong-AVD colouring
 */
uint16_t const flag_b = 0x8000;
uint16_t const flag_f = 0x8000 >> 1;
uint16_t const flag_r = 0x8000 >> 2;
uint16_t const flag_u = 0x8000 >> 3;
uint16_t const flag_n = 0x8000 >> 4;
uint16_t const flag_N = 0x8000 >> 5;
uint16_t const flag_p = 0x8000 >> 6;
uint16_t const flag_P = 0x8000 >> 7;
uint16_t const flag_s = 0x8000 >> 8;
uint16_t const flag_a = 0x8000 >> 9;
uint16_t const flag_A = 0x8000 >> 10;

void process_args(const int argc, char* argv[], string& output_file_path, int& depth, uint16_t& flags) {
    bool file_set = false;
    bool depth_set = false;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            int j = 1;
            while (argv[i][j] != '\0') {
                if (argv[i][j] == 'b') {
                    flags |= flag_b;
                } else if (argv[i][j] == 'f') {
                    flags |= flag_f;
                } else if (argv[i][j] == 'r') {
                    flags |= flag_r;
                } else if (argv[i][j] == 'u') {
                    flags |= flag_u;
                } else if (argv[i][j] == 'n') {
                    flags |= flag_n;
                } else if (argv[i][j] == 'N') {
                    flags |= flag_N;
                } else if (argv[i][j] == 'p') {
                    flags |= flag_p | flag_u;
                } else if (argv[i][j] == 'P') {
                    flags |= flag_P | flag_p | flag_u;
                } else if (argv[i][j] == 's') {
                    flags |= flag_s;
                } else if (argv[i][j] == 'a') {
                    flags |= flag_a;
                    if (flags & flag_A) {
                        printf("AVD colouring and Strong-AVD colouring cannot be enabled at the same time.");
                        exit(-1);
                    }
                } else if (argv[i][j] == 'A') {
                    flags |= flag_A;
                    if (flags & flag_a) {
                        printf("AVD colouring and Strong-AVD colouring cannot be enabled at the same time.");
                        exit(-1);
                    }
                } else {
                    printf("Unknown flag %c\n", argv[i][j]);
                    exit(-1);
                }
                j++;
            }
        } else if (!file_set) {
            output_file_path = argv[i];
            file_set = true;
        } else if (!depth_set) {
            char *endptr;
            depth = strtol(argv[i], &endptr, 10);
            if (*endptr != '\0') {
                printf("The second argument must be an integer.\n");
                exit(-1);
            }
        } else {
            printf("Unexpteced argument '%s'\n", argv[i]);
            exit(-1);
        }
    }
}

unsigned short combine_masks[2] = {0, MAX_SHORT};

void combine_bit_maps(unsigned short (&left)[16], unsigned short (&right)[16], unsigned short (&result)[16]) {
    for (int i = 0; i < 16; i++) {
        unsigned short mapping_mask = connection_mapping[left[i]];
        for (int j = 0; j < 16; j++) {
            result[i] |= combine_masks[(mapping_mask & (0x8000 >> j)) >> (15 - j)] & right[j];
        }
    }
}

void merge_bit_maps(unsigned short (&first)[16], unsigned short (&second)[16], unsigned short (&result)[16]) {
    for (int i = 0; i < 16; i++) {
        result[i] = first[i] | second[i];
    }
}

void permutate_bit_map(uint8_t (&bucket_mapping)[16], unsigned short (&permutation_mapping)[SHORT_SIZE],
                       unsigned short (&old)[16], unsigned short (&result)[16]) {
    for (int i = 0; i < 16; i++) {
        result[bucket_mapping[i]] |= permutation_mapping[old[i]];
    }
}

void add_permutations_total(halin_tripole& tripole, int tripole_deg, uint16_t flags) {
    if (flags & flag_a) { //avd
        if (tripole_deg == 3) {
            for (int i = 0; i < 6; i++) {
                permutate_bit_map(*avd_3_sub2_perm_bucket_mappings[i], *avd_3_sub2_perm_mappings[i], tripole.bit_map, tripole.sub2_perms);
            }

            for (int i = 0; i < 4; i++) {
                permutate_bit_map(*avd_3_sub3_perm2_bucket_mappings[i], *avd_3_sub3_perm2_mappings[i], tripole.bit_map, tripole.sub3_perms2);
                permutate_bit_map(*avd_3_sub3_perm3_bucket_mappings[i], *avd_3_sub3_perm3_mappings[i], tripole.bit_map, tripole.sub3_perms3);
            }
        } else if (tripole_deg == 2) {
            for (int i = 0; i < 4; i++) {
                permutate_bit_map(*avd_2_sub2_perm_bucket_mappings[i], *avd_2_sub2_perm_mappings[i], tripole.bit_map, tripole.sub2_perms);
            }

            for (int i = 0; i < 6; i++) {
                permutate_bit_map(*avd_2_sub3_perm2_bucket_mappings[i], *avd_2_sub3_perm2_mappings[i], tripole.bit_map, tripole.sub3_perms2);
                permutate_bit_map(*avd_2_sub3_perm3_bucket_mappings[i], *avd_2_sub3_perm3_mappings[i], tripole.bit_map, tripole.sub3_perms3);
            }
        } else {
            perror("tripole_deg");
        }
    } else if (flags & flag_A) { //savd
        if (tripole_deg == 3) {
            for (int i = 0; i < 2; i++) {
                permutate_bit_map(*savd_3_sub2_perm_bucket_mappings[i], *savd_3_sub2_perm_mappings[i], tripole.bit_map, tripole.sub2_perms);
            }

            for (int i = 0; i < 4; i++) {
                permutate_bit_map(*savd_3_sub3_perm2_bucket_mappings[i], *savd_3_sub3_perm2_mappings[i], tripole.bit_map, tripole.sub3_perms2);
                permutate_bit_map(*savd_3_sub3_perm3_bucket_mappings[i], *savd_3_sub3_perm3_mappings[i], tripole.bit_map, tripole.sub3_perms3);
            }
        } else if (tripole_deg == 2) {
            for (int i = 0; i < 4; i++) {
                permutate_bit_map(*savd_2_sub2_perm_bucket_mappings[i], *savd_2_sub2_perm_mappings[i], tripole.bit_map, tripole.sub2_perms);
            }

            for (int i = 0; i < 2; i++) {
                permutate_bit_map(*savd_2_sub3_perm2_bucket_mappings[i], *savd_2_sub3_perm2_mappings[i], tripole.bit_map, tripole.sub3_perms2);
                permutate_bit_map(*savd_2_sub3_perm3_bucket_mappings[i], *savd_2_sub3_perm3_mappings[i], tripole.bit_map, tripole.sub3_perms3);
            }
        } else {
            perror("tripole_deg");
        }
    } else { //total
        for (int i = 0; i < 4; i++) {
            permutate_bit_map(*total_sub3_perms2_bucket_mappings[i], *total_sub3_perms2_mappings[i], tripole.bit_map, tripole.sub3_perms2);
        }
        for (int i = 0; i < 4; i++) {
            permutate_bit_map(*total_sub3_perms3_bucket_mappings[i], *total_sub3_perms3_mappings[i], tripole.bit_map, tripole.sub3_perms3);
        }
        merge_bit_maps(tripole.sub3_perms2, tripole.sub3_perms3, tripole.sub2_perms);
    }
}

halin_tripole produce_deg3_total(halin_tripole& left, halin_tripole& right, uint16_t flags) {
    halin_tripole tripole = halin_tripole();
    tripole.expr = "(" + left.expr + ")" + right.expr;
    combine_bit_maps(left.sub3_perms2, right.sub3_perms3, tripole.bit_map);
    combine_bit_maps(left.sub3_perms3, right.sub3_perms2, tripole.bit_map);

    add_permutations_total(tripole, 3, flags);
    return tripole;
}

halin_tripole produce_deg2_total(halin_tripole& sub_tripole, uint16_t flags) {
    halin_tripole tripole = halin_tripole();
    tripole.expr = "<" + sub_tripole.expr + ">";
    
    for (int i = 0; i < 16; i++) {
        tripole.bit_map[i] = sub_tripole.sub2_perms[i];
    }
    
    add_permutations_total(tripole, 2, flags);
    return tripole;
}

halin_tripole create_t0_tripole(uint16_t flags) {
    halin_tripole tripole = halin_tripole();
    tripole.expr = "";
    uint8_t quad_set[2] = {0x97, 0xd6};
    create_bit_vector(tripole.bit_map, 2, quad_set);
    add_permutations_total(tripole, 3, flags);
    return tripole;
}

vector<vector<halin_tripole>> global_result({});
unordered_map<__int128_t, unordered_map<__int128_t, vector<string>>> global_map;

ostream& operator<<(ostream& o, const __int128& x) {
    if (x == numeric_limits<__int128_t>::min()) return o << "nonsense";
    if (x < 0) return o << "-" << -x;
    if (x < 10) return o << (char)(x + '0');
    return o << x / 10 << (char)(x % 10 + '0');
}

/**
 * returns true if bits is a new pallet, false otherwise
 */
bool map_check_and_add(unsigned short (&bits)[16], string& left, string& right) {
    __int128_t& key = ((__int128_t*) bits)[0];
    __int128_t& value = ((__int128_t*) bits)[1];
    unordered_map<__int128_t, unordered_map<__int128_t, vector<string>>>::iterator it = global_map.find(key);
    bool result = false;
    if (it == global_map.end()) { // no such key in map
        unordered_map<__int128_t, vector<string>>  value_map;
        value_map[value] = {left, right};
        global_map[key] = {value_map};
        result = true;
    } else {
        unordered_map<__int128_t, vector<string>>& value_map = global_map[key];
        if (value_map.find(value) == value_map.end()) { // no such value in the value set
            value_map[value] = {left, right};
            result = true;
        } else {
            value_map[value].push_back(left);
            value_map[value].push_back(right);
        }
    }

    return result;
}

int map_get_count(unsigned short (&bits)[16]) {
    __int128_t& key = ((__int128_t*) bits)[0];
    __int128_t& value = ((__int128_t*) bits)[1];
    if (global_map.find(key) != global_map.end()) {
        unordered_map<__int128_t, vector<string>>& value_map = global_map[key];
        if (value_map.find(value) != value_map.end()) {
            return value_map[value].size() / 2;
        }
    }
    return 0;
}

vector<string> map_get_vector(unsigned short (&bits)[16]) {
    __int128_t& key = ((__int128_t*) bits)[0];
    __int128_t& value = ((__int128_t*) bits)[1];
    if (global_map.find(key) != global_map.end()) {
        unordered_map<__int128_t, vector<string>>& value_map = global_map[key];
        if (value_map.find(value) != value_map.end()) {
            return value_map[value];
        }
    }
    return {};
}

void generate_sub(int tier, int const depth, uint16_t flags) {
    vector<halin_tripole> new_tier = {};
    global_result.push_back(new_tier);

    for (int i = 0; i < tier; i++) {
        vector<halin_tripole>& left_trees = global_result.at(i);
        vector<halin_tripole>& right_trees = global_result.at(tier - i - 1);
        for (halin_tripole& left_tripole : left_trees) {
            for (halin_tripole& right_tripole : right_trees) {
                halin_tripole result = produce_deg3_total(left_tripole, right_tripole, flags);
                if (flags & flag_u) {
                    bool check_result = map_check_and_add(result.bit_map, left_tripole.expr, right_tripole.expr);
                    if (check_result) {
                        global_result.at(tier).push_back(result);
                    }
                } else {
                    global_result.at(tier).push_back(result);
                }
            }
        }
    }

    if (flags & flag_s) {
        vector<halin_tripole>& n_minus_1_trees = global_result.at(tier - 1);
        for (halin_tripole& sub_tripole : n_minus_1_trees) {
            halin_tripole result = produce_deg2_total(sub_tripole, flags);
            if (flags & flag_u) {
                string str = "%";
                bool check_result = map_check_and_add(result.bit_map, sub_tripole.expr, str);
                if (check_result) {
                    global_result.at(tier).push_back(result);
                }
            } else {
                global_result.at(tier).push_back(result);
            }
        }
    }

    if (tier < depth) {
        generate_sub(++tier, depth, flags);
    }
}

void generate(int const depth, uint16_t flags) {
    halin_tripole tripole = create_t0_tripole(flags);
    global_result.push_back({tripole});

    if (flags & flag_u) {
        string str = "void";
        map_check_and_add(tripole.bit_map, str, str);
    }

    generate_sub(1, depth, flags);
}

void fprint_tripole(halin_tripole& tripole, FILE* fp, uint16_t print_flags) {
    if (print_flags & flag_P) {
        fprintf(fp, "=");
    }
    fprintf(fp, "%s", tripole.expr.c_str());
    if (print_flags & flag_P) {
        fprintf(fp, "=");
    }

    if (print_flags & flag_p) {
        fprintf(fp, " %u", map_get_count(tripole.bit_map));
    }
    
    fprintf(fp, "\n");
    if (print_flags & flag_P) {
        vector<string> parent_strings = map_get_vector(tripole.bit_map);
        for (int i = 0; i < parent_strings.size() / 2; i++) {
            string p1 = parent_strings[i * 2];
            if (p1 == "") p1 = "*";
            string p2 = parent_strings[i * 2 + 1];
            if (p2 == "") p2 = "*";
            fprintf(fp, "%s,  %s\n",p1.c_str(), p2.c_str());
        }
    }

    if (print_flags & flag_b) {
        fprint_bit_vector(fp, tripole.bit_map);
    } else {
        fprint_bit_vector_quads(fp, tripole.bit_map);
    }
}

bool print_filter(halin_tripole& tripole, uint16_t flags) {
    if (flags & flag_N) {
        if (flags & flag_a) {
            if (tripole.expr.at(0) = '(') {
                for (int i = 0; i < 16; i++) {
                    if (tripole.bit_map[i] & extendable_pallete_bit_map[i]) return false;
                }
            } else {
                for (int i = 0; i < 16; i++) {
                    if (tripole.bit_map[i] & extendable_pallete_bit_map_avd_2[i]) return false;
                }
            }
        } else if (flags & flag_A) {
            if (tripole.expr.at(0) = '(') {
                for (int i = 0; i < 16; i++) {
                    if (tripole.bit_map[i] & extendable_pallete_bit_map[i]) return false;
                }
            } else {
                for (int i = 0; i < 16; i++) {
                    if (tripole.bit_map[i] & extendable_pallete_bit_map_savd_2[i]) return false;
                }
            }
        } else {
            for (int i = 0; i < 16; i++) {
                if (tripole.bit_map[i] & extendable_pallete_bit_map[i]) return false;
            }
        }
    }
    if (flags & flag_f) {
        return compare_bit_vectors(tripole.bit_map, full_bit_map);
    }
    return true;
}

void print_output(FILE* fp, uint16_t flags) {
    if (flags & flag_r) {
        for (int print_depth = 0; print_depth < global_result.size(); print_depth++) {
            for (halin_tripole& current : global_result.at(print_depth)) {
                if (print_filter(current, flags)) {
                    for (int scan_depth = 0; scan_depth < print_depth; scan_depth++) {
                        for (halin_tripole& scanned : global_result.at(scan_depth)) {
                            if (compare_bit_vectors(current.bit_map, scanned.bit_map)) {
                                fprintf(fp, "Reduction: \n");
                                fprint_tripole(current, fp, flags);
                                fprint_tripole(scanned, fp, flags);
                            }
                        }
                    }
                }
            }
        }
    } else if (flags & flag_n) {
        for (int i = 1; i < global_result.size(); i++) {
            int count = 0;
            for (halin_tripole& tripole : global_result.at(i)) {
                count++;
            }
            fprintf(fp, "%u: %u\n", i, count);
        }
    } else {
        for (int i = 1; i < global_result.size(); i++) {
            vector<halin_tripole>& tier = global_result.at(i);
            for (halin_tripole& tripole : tier) {
                if (print_filter(tripole, flags)) fprint_tripole(tripole, fp, flags);
            }
        }
    }
}

void test_combine() {
    unsigned short test_map[16] = {0, 0x8000 >> 1, 0x8000 >> 2, 0x8000 >> 3,
                                    0x8000 >> 4, 0, 0x8000 >> 6, 0x8000 >> 7,
                                    0x8000 >> 8, 0x8000 >> 9, 0, 0x8000 >> 11,
                                    0x8000 >> 12, 0x8000 >> 13, 0x8000 >> 14, 0};
    unsigned short result[16] = {};
    combine_bit_maps(test_map, test_map, result);
    for (int i = 0; i < 16; i++) {
        print_short_binary(result[i]);
        if (i % 4 == 3) printf("\n");
    }
}

void test_permutate_bit_map() {
    unsigned short former[16] = {};
    uint8_t perms_to_set[8] = {0x3d, 0x67, 0x6e, 0x7e, 0x89, 0xb6, 0xc1, 0xee};
    create_bit_vector(former, 8, perms_to_set);
    print_bit_vector_quads(former);
    unsigned short permutated[16] = {};
    permutate_bit_map(*total_sub3_perms2_bucket_mappings[0], *total_sub3_perms2_mappings[0], former, permutated);
    print_bit_vector_quads(permutated);
}

void test_create_t0() {
    halin_tripole tripole = create_t0_tripole(0);
    print_bit_vector_quads(tripole.bit_map);
    print_bit_vector_quads(tripole.sub3_perms2);
    print_bit_vector_quads(tripole.sub3_perms3);
}

void test_combine_tripoles() {
    halin_tripole tripole = create_t0_tripole(0);
    halin_tripole t1_tripole = produce_deg3_total(tripole, tripole, 0);
    print_bit_vector_quads(t1_tripole.bit_map);
}

void test_check_and_add_map() {
    unsigned short test_arr1[16] = {0,1,0,0,
                                   0,0,0,0,
                                   7,0,0,0,
                                   0,0,0,0};
    unsigned short test_arr2[16] = {0,1,0,0,
                                   0,0,0,0,
                                   6,0,0,0,
                                   0,0,0,0};
    unsigned short test_arr3[16] = {0,0,0,0,
                                   0,0,0,12,
                                   0,0,0,0,
                                   0,0,0,7};
    string dummy_string1 = "s1";
    string dummy_string2 = "s2";
    assert(map_check_and_add(test_arr1, dummy_string1, dummy_string2) == true);
    assert(map_check_and_add(test_arr1, dummy_string1, dummy_string2) == false);
    assert(map_check_and_add(test_arr2, dummy_string1, dummy_string2) == true);
    assert(map_check_and_add(test_arr3, dummy_string1, dummy_string2) == true);
    assert(map_check_and_add(test_arr3, dummy_string1, dummy_string2) == false);
    assert(map_check_and_add(test_arr2, dummy_string1, dummy_string2) == false);
    assert(map_check_and_add(test_arr1, dummy_string1, dummy_string2) == true);
    assert(map_check_and_add(test_arr1, dummy_string1, dummy_string2) == false);
}

int main(int argc, char* argv[]) {
    prepare_mappings();
    uint16_t flags = 0;
    string output_file_path;
    int depth;

    process_args(argc, argv, output_file_path, depth, flags);

    FILE *fp;
    fp = fopen(output_file_path.c_str(), "w");
    
    if (fp == NULL) {
        printf("Failed to open file %s.\n", output_file_path.c_str());
        exit(-1);
    }

    generate(depth, flags);
    print_output(fp, flags);
    fclose(fp);

    printf("Outputs successfully written to '%s'\n", output_file_path.c_str());
    return 0;
}
