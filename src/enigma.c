#include <enigma.h>

#include <string.h>

extern uint8_t rotors_count;
extern uint8_t refrectors_count;
extern uint8_t rotors_position[ROTORS_COUNT];
extern char char_window[ROTORS_COUNT];
extern char init_window[ROTORS_COUNT];
extern char* rotor_wiring[ROTORS_COUNT];
extern char rotor_switch_pos[ROTORS_COUNT];
extern char encryption_step[REFLECTORS_COUNT];
extern char* plugboard_wiring;

void init_enigma(void) {
    asm volatile("  mov %0, 3\n\
                    mov %1, %0\n\
                    shl $0x01, %1\n\
                    add %1, 3\n"
                : "=r"(rotors_count), "=r"(refrectors_count));

    strcpy(plugboard_wiring, plugboards);

    // asm volatile("  mov %%ecx, 0\n\
    //                 loop1:\n\
    //                     mov (%2, %%ecx, 70), (%0, %%ecx, 70)\n\
    //                     inc %%ecx\n\
    //                     cmp %%ecx, %1\n\
    //                     jne loop1\n\
    //             "
    //             : "+m"(rotor_wiring)
    //             : "m"(rotors_count), "m"(rotors));

    // asm volatile("  mov %%ecx, 0\n\
    //                 loop2:\n\
    //                     mov (%2, %%ecx, 1), (%0, %%ecx, 1)\n\
    //                     inc %%ecx\n\
    //                     cmp %%ecx, %1\n\
    //                     jne loop2\n\
    //             "
    //             : "+m"(rotor_switch_pos)
    //             : "m"(rotors_count), "m"(notches));

    // asm volatile("  mov %%ecx, 0\n\
    //                 loop3:\n\
    //                     mov %%ecx, (%0, %%ecx) \n\
    //                     inc %%ecx\n\
    //                     cmp %%ecx, %1\n\
    //                     jne loop3\n\
    //             "
    //             : "+m"(encryption_step)
    //             : "m"(rotors_count));

    // asm volatile("  mov %%ecx, 0\n\
    //                 mov %%ax, 97\n\
    //                 loop4:\n\
    //                     mov %%al, (%0, %%ecx)  \n\
    //                     mov %%al, (%1, %%ecx) \n\
    //                     inc %%ecx\n\
    //                     cmp %%ecx, %2\n\
    //                     jne loop4\n\
    //             "
    //             : "+m"(char_window), "+m"(init_window)
    //             : "m"(rotors_count));
}