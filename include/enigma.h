#ifndef __ENIGMA_H__
#define __ENIGMA_H__

#include <stdint.h>
#include <rotors.h>

uint8_t rotors_count;
uint8_t refrectors_count;
uint8_t rotors_position[ROTORS_COUNT];
char char_window[ROTORS_COUNT];
char init_window[ROTORS_COUNT];
char* rotor_wiring[ROTORS_COUNT];
char rotor_switch_pos[ROTORS_COUNT];
char encryption_step[REFLECTORS_COUNT];
char* plugboard_wiring;

void init_enigma(void);

#endif