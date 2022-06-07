#include <enigma_encoding.h>

#include <stddef.h>
#include <string.h>
#include <stdlib.h>

char* default_rotor_reflector_cfg[] = {
            "3avbdfhjlcprtxvznyeiwgakmusqo13579,2(['/-&;*48+60.:\"]) ?><\\|}{=^_%$#@!`~",
            "2aeajdksiruxblhwtmcqgznpyfvoe093.]8[\"/1,7+':2)6&;(*5- 4?><\\|}{=^_%$#@!`~",
            "1aqekmflgdqvzntowyhxuspaibrcj4.:5,63)-&;' +*7/\"](081[29?><\\|}{=^_%$#@!`~",
            "byruhqsldpxngokmiebfzcwvjat*[\"7)],3(/;6 .:8415&2+-90'?<>\\|}{=_^%$#@`!~"
        };

char* enigma_encoding(char* input) {
    init_enigma();

    // init rotors
    set_plugboards("abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?\n\
                    abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?");
    set_rotor_and_reflector(default_rotor_reflector_cfg,
        "bdfhjlcprtxvznyeiwg->akmusqo13579,2(['/-&;*48+60.:\"]) ?><\\|}{=^_%$#@!`~\n\
        ->ajdksiruxblhwtmcqgznpyfvoe093.]8[\"/1,7+':2)6&;(*5- 4?><\\|}{=^_%$#@!`~\n\
        ekmflgdqvzntowyhxusp->aibrcj4.:5,63)-&;' +*7/\"](081[29?><\\|}{=^_%$#@!`~"
    );

    char* output = malloc(strlen(input) + 1);

    for (int i = 0; i < strlen(input); i++) {
        output[i] = encrypt_char(input[i]);
    }

    return output;
}

static char encrypt_char(char c) {
    int r;
    int i = 0;

    turn_rotors();
    rotor_step[i++] = plugboard_wiring[idx_of(c, input_alphabet)];
    for(r = 0; r < rotors_count; ++r) {
        rotor_step[i++] = r_to_l_path(rotor_step[i-1], r);
    }
    rotor_step[i++] = reflector[idx_of(rotor_step[i-1], input_alphabet)];

    for(r = rotors_count - 1; r > 0; --r) {
        rotor_step[i++] = l_to_r_path(rotor_step[i-1], r);
    }

    return plugboard_wiring[idx_of(rotor_step[i-1], input_alphabet)];
}