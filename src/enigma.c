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
        init_window[i] = char_window[i] = 'A';
    }

    reflector = (char*)refrectors[1];
    reflector_type = 1;   
}

void set_rotor_and_reflector(char** rotors_cfg, char* reflectors_cfg) {
    int n, rotor, rotor_pos;
    char ch_temp;

    rotors_count = rotors_cfg[0][0] - '0';
    rotors_count = rotors_count > 4 ? 4 : rotors_count;
    
    asm volatile("  mov $3, %0\n\
                    shl $1, %0\n\
                    add $3, %0"
                : "=r"(steps));

    for(int i = 1; i <= rotors_count; i++) {
        ch_temp = rotors_cfg[i][0];

        if(ch_temp >= '0' && ch_temp <= '9') rotor = ch_temp - '0';
        else {
            ch_temp -= '0';
            rotor = ch_temp == 'b' ? 9 : ch_temp == 'g' ? 10 : 0;
        }
        rotor_pos = rotors_cfg[i][1] - '0';
        init_window[rotor_pos] = char_window[rotor_pos] = rotors_cfg[i][2];
        setup_rotor(rotor_pos, rotor);
    }

    if(reflectors_cfg[0] == 'b') n = 1;
    else if(reflectors_cfg[0] == 'c') n = 2;
    else if(reflectors_cfg[0] == 'B') n = 3;
    else if(reflectors_cfg[0] == 'C') n = 4;
    else n = 0;

    reflector = (char*)refrectors[n];
    reflector_type = n;
}

void set_plugboards(char* cfg) {
    char p1, p2, ch_temp;

    for (int i = 0; i < strlen(cfg); i++) {
        p1 = cfg[i];
        p2 = cfg[i + 1];
        int x = idx_of(p1, input_alphabet);
        ch_temp = plugboard_wiring[x];
        if(ch_temp != p1) {
            plugboard_wiring[idx_of(ch_temp, input_alphabet)] = ch_temp;
            plugboard_wiring[x] = p1;
        }
        plugboard_wiring[x] = p2;
        x = idx_of(p2, input_alphabet);
        if(plugboard_wiring[x] != p2) {
            plugboard_wiring[idx_of(ch_temp, input_alphabet)] = plugboard_wiring[x];
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

void turn_rotors() {
    char* r1 = rotor_wiring[1];
    char* r2 = rotor_wiring[2];
    char* r3 = rotors_count > 3 ? rotor_wiring[3] : NULL;
    uint8_t rotate[ROTORS_COUNT];
    rotate[1] = 1;

    for(int i = 2; i <= rotors_count; i++)
        rotate[i] = 0; 
    if(rotor_switch_pos[1] == r1[rotors_position[1]] || rotor_switch_pos[2] == r2[rotors_position[2]])
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
