#include <enigma.h>

#include <stdlib.h>
#include <string.h>

uint8_t rotors_count;
uint8_t steps;
int rotors_position[ROTORS_COUNT];
char char_window[ROTORS_COUNT];
char init_window[ROTORS_COUNT];
char* rotor_wiring[ROTORS_COUNT];
char rotor_switch_pos[ROTORS_COUNT];
int rotor_number[ROTORS_COUNT];
char encryption_step[REFLECTORS_COUNT];
char* reflector;
char plugboard_wiring[N_CHARS + 1];
int reflector_type;
uint8_t rotor_step[STEP_COUNT];

extern int idx_of(char c, const char* collection);

void init_enigma(void) {
    asm volatile("  mov $3, %0\n\
                    mov %0, %1\n\
                    shl $1, %1\n\
                    add $3, %1\n"
                : "=r"(rotors_count), "=r"(steps));

    strcpy(plugboard_wiring, plugboards);

    for(int i = 0; i < rotors_count; i++) {
        rotor_wiring[i] = rotors[i];
        rotor_number[i] = i;
        rotor_switch_pos[i] = notches[i];
        init_window[i] = 'A';
        char_window[i] = 'A';
    }

    reflector = (char*)refrectors[1];
    reflector_type = 1;   
}

void set_rotor_and_reflector(char** rotors_cfg, char* reflectors_cfg) {
    int i, n, rotor, rotor_pos;
    char ch_temp, ring_pos;

    rotors_count = rotors_cfg[0][0] - '0';
    if(rotors_count > 4)
        rotors_count = 4;
    
    steps = (rotors_count << 1) + 3;

    for(i = 1; i <= rotors_count; i++) {
        ch_temp = rotors_cfg[i][0];

        if(ch_temp >= '0' && ch_temp <= '9') {
            rotor = ch_temp - '0';
        }
        else {
            ch_temp = tolower(ch_temp);
            rotor = ch_temp == 'b' ? 9 : ch_temp == 'g' ? 10 : 0;
        }
        rotor_pos = rotors_cfg[i][1] - '0';
        ring_pos = rotors_cfg[i][2];
        init_window[rotor_pos] = char_window[rotor_pos] = ring_pos;
        setup_rotor(rotor_pos, rotor);
    }

    ch_temp = reflectors_cfg[0];

    if(ch_temp == 't')
        n = 0;
    else if(ch_temp == 'b')
        n = 1;
    else if(ch_temp == 'c')
        n = 2;
    else if(ch_temp == 'B')
        n = 3;
    else if(ch_temp == 'C')
        n = 4;
    else n = 0;

    reflector = (char*)refrectors[n];
    reflector_type = n;
}

void set_plugboards(char* cfg) {
    int i, x;
    char p1, p2, ch_temp;
    size_t n = strlen(cfg);

    for (i = 0; i < n; i++) {
        p1 = cfg[i];
        p2 = cfg[i + 1];
        x = idx_of(p1, input_alphabet);
        ch_temp = plugboard_wiring[x];
        if(ch_temp != p1) {
            plugboard_wiring[idx_of(ch_temp, input_alphabet)] = ch_temp;
            plugboard_wiring[x] = p1;
        }
        plugboard_wiring[x] = p2;
        x = idx_of(p2, input_alphabet);
        ch_temp = plugboard_wiring[x];
        if(ch_temp != p2) {
            plugboard_wiring[idx_of(ch_temp, input_alphabet)] = ch_temp;
            plugboard_wiring[x] = p1;
        }
        plugboard_wiring[x] = p1;
    }
}

void setup_rotor(int pos, int r) {
    rotor_wiring[pos] = (char*)rotors[r];
    rotor_switch_pos[pos] = notches[r];
    rotor_number[pos] = r;
}

char r_to_l_path(char c, int rotor_num) {
    char* rotor = rotor_wiring[rotor_num];
    int offset = idx_of(rotor[rotors_position[rotor_num]], input_alphabet);
    return input_alphabet[(idx_of(rotor[(idx_of(c, input_alphabet) + offset) % N_CHARS], input_alphabet) - offset) % N_CHARS];
}

char l_to_r_path(char c, int rotor_num) {
    char* rotor = rotor_wiring[rotor_num];
    int offset = idx_of(rotor[rotors_position[rotor_num]], input_alphabet);
    int new_char = input_alphabet[(idx_of(c, input_alphabet) + offset) % N_CHARS];
    int m = 0;

    while(m < N_CHARS && rotor[m] != new_char) m++;
    
    return input_alphabet[(m - offset) % N_CHARS];
}

void turn_rotors() {
    char* r1 = rotor_wiring[1];
    char* r2 = rotor_wiring[2];
    char* r3 = rotors_count > 3 ? rotor_wiring[3] : NULL;
    uint8_t rotate[ROTORS_COUNT];
    rotate[1] = 1;

    for(int i = 2; i <= rotors_count; i++)
        rotate[i] = 0;
    
    if(rotor_switch_pos[1] == r1[rotors_position[1]]
        || rotor_switch_pos[2] == r2[rotors_position[2]])
        rotate[1] = 1;
    if(rotor_switch_pos[2] == r2[rotors_position[2]])
        rotate[3] = 1;
    if(rotors_count > 3 && rotor_switch_pos[3] == r3[rotors_position[3]])
        rotate[4] = 1;

    for(int i = 1; i <= rotors_count; i++) 
        turn_single_rotor(i, rotate[i]);
}

int turn_single_rotor(int rotor_num, int step) {
    if(step <= 0) return -1;

    rotors_position[rotor_num] = (rotors_position[rotor_num] + step) % N_CHARS;
    char_window[rotor_num] = rotor_wiring[rotor_num][rotors_position[rotor_num]];

    return step;
}