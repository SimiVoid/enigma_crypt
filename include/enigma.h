#ifndef __ENIGMA_H__
#define __ENIGMA_H__

#include <stdint.h>
#include <rotors.h>

#define STEP_COUNT 11

extern uint8_t rotors_count;
extern uint8_t steps;
extern int rotors_position[ROTORS_COUNT];
extern char char_window[ROTORS_COUNT];
extern char init_window[ROTORS_COUNT];
extern char* rotor_wiring[ROTORS_COUNT];
extern char rotor_switch_pos[ROTORS_COUNT];
extern int rotor_number[ROTORS_COUNT];
extern char encryption_step[REFLECTORS_COUNT];
extern char* reflector;
extern char plugboard_wiring[N_CHARS + 1];
extern int reflector_type;
extern uint8_t rotor_step[STEP_COUNT];

void init_enigma(void);

void set_rotor_and_reflector(char** rotors_cfg, char* reflectors_cfg);
void set_plugboards(char* cfg);
void setup_rotor(int pos, int r);
void set_rotor_position();

void turn_rotors();
int turn_single_rotor(int rotor_num, int step);

#endif