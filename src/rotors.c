#include <rotors.h>
#include <string.h>

const char* rotors[ROTORS_COUNT] = {
     "abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?", // input alphabet
     "ekmflgdqvzntowyhxuspaibrcj4.:5,63)-&;' +*7/\"](081[29?><\\|}{=^_%$#@!`~", // rotor 1
     "ajdksiruxblhwtmcqgznpyfvoe093.]8[\"/1,7+':2)6&;(*5- 4?><\\|}{=^_%$#@!`~", // rotor 2
     "bdfhjlcprtxvznyeiwgakmusqo13579,2(['/-&;*48+60.:\"]) ?><\\|}{=^_%$#@!`~", // rotor 3
     "esovpzjayquirhxlnftgkdcmwb4] -(&90*)\"8[7/,;5'6.32:+1?><\\|}{=^_%$#@!`~", // rotor 4
     "vzbrgityupsdnhlxawmjqofeck-&1[68'*\"(]3;7,/0+:9) 542.?><\\|}{=^_%$#@!`~", // rotor 5
     "jpgvoumfyqbenhzrdkasxlictw9(6- \":5*)14;7&[3.0]/,82'+?><\\|}{=^_%$#@!`~", // rotor 6
     "nzjhgrcxmyswboufaivlpekqdt;&976[2/:*]+1 \"508-,(4.)3'?><\\|}{=^_%$#@!`~", // rotor 7
     "fkqhtlxocbjspdzramewniuygv5.)7',/ 219](3&[0:4+;8\"*6-?><\\|}{=^_%$#@!`~", // rotor 8
     "leyjvcnixwpbqmdrtakzgfuhos,4*9-2;8/+(1):3['0.&65\"7 ]?><\\|}{=^_%$#@!`~", // beta rotor
     "fsokanuerhmbtiycwlqpzxvgjd5] .0;\"4[7:1'8*2+,)(&/-693?><\\|}{=^_%$#@!`~"  // gamma rotor
};

const char* refrectors[REFLECTORS_COUNT] = {
     "abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?", // input alphabet
     "yruhqsldpxngokmiebfzcwvjat*[\"7)],3(/;6 .:8415&2+-90'?<>\\|}{=_^%$#@`!~", // reflector B, thick
     "fvpjiaoyedrzxwgctkuqsbnmhl5-(980 *43[&/+62'.\")]1;:7,?<>\\|}{=_^%$#@`!~", // reflector C, thick
     "enkqeuywjicopblmdxzvfthrgs4;.)0\"*+982 (1,:3/&-5'7[6]?<>\\|}{=_^%$#@`!~", // reflector B, dunn
     "rdobjntkvehmlfcwzrxgyipsuq[3 19;'.-47:,52+&0/6*8(]\")?<>\\|}{=_^%$#@`!~"  // reflector C, dunn
};

const char notches[ROTORS_COUNT] = { 'z', 'q', 'e', 'v', 'j', 'z', 'z', 'z', 'z', 'a', 'a' };
const char* plugboards = "abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?";
const char* input_alphabet = "abcdefghijklmnopqrstuvwxyz0123456789.,:; ()[]'\"-+/*&~`!@#$%^_={}|\\<>?";
