/* prng.c -- Pseudorandom Number Generator
 * by yasunoxx <yasunoxx gmail com>
*/

/*
  Original source (C)2017 by EDN Japan
  http://ednjapan.com/edn/articles/1704/06/news026.html

; *********************************************************************************
;  LISTING 1 - 12C508 ASSEMBLY CODE FOR PSEUDORANDOM-NOISE GENERATOR
; "Single IC Forms pseudorandom-noise source," EDN, March 21, 2002, pg 98
; *********************************************************************************
; 
;    Pseudorandom Noise Generator
;    12/12/01 Stephen J. Ploss
;

    LIST p=12C508A

#include "P12C508A.INC"

    __CONFIG _CP_OFF & _WDT_OFF & _IntRC_OSC & _MCLRE_OFF

    cblock 0x07

    Lobyte
    Midbyte
    Hibyte

    endc

start
    movlw 0xC0

    option
    movlw 0xFE
    tris GPIO

    ; Start the PN Generator
main
    movlw 0xFF
    movwf Lobyte
    movwf Midbyte
    movwf Hibyte

loop
    rlf Lobyte, F
    rlf Midbyte, F
    rlf Hibyte, F
    movlw 0x1A
    btfsc STATUS, C
    xorwf Lobyte, F

    movf Hibyte, W
    movwf GPIO
    goto loop

    END
*/

#include <stdio.h>
#include "prng.h"

#define Hibyte 1
#define Midbyte 2
#define Lobyte 3

union uni_ShiftReg {
    u_int i;
    struct str_b {
        u_short pad:7;
        u_char carry:1;
        u_int reg:24;
    } b;
    struct str_b2 {
        u_int pad:15;
        u_char retbit:1;
        u_int pad2:15;
        u_char carry:1;
    } b2;
    u_char c[ 4 ];
} ShiftReg;

void main()
{
	u_char prn_a;
	init_prng();
	
	while( 1 )
	{
		prn_a = prng();
		printf( "%d", prn_a );
	}
}


u_char prng( void )
{
    u_char carry;

    carry = ShiftReg.b.carry;
    ShiftReg.i <<= 1;
    ShiftReg.b2.carry = carry;

    if( carry == 1 )
    {
        ShiftReg.c[ Lobyte ] ^= 0x1A;
    }

    return ShiftReg.b2.retbit;
}

void init_prng( void )
{
	ShiftReg.i = 0x00FFFFFF;
}
