/* prng.h -- Pseudorandom Noise Generator
 * by yasunoxx <yasunoxx gmail com>
 */

#ifndef u_char
#define u_char unsigned char
#endif

#ifndef u_short
#define u_short unsigned short
#endif

#ifndef u_int
// #define u_int unsigned long
#define u_int unsigned int
#endif

u_char prng( void );
u_char md_prng( u_char prn_a, u_char prn_b, u_char prn_c );
void init_prng( void );
