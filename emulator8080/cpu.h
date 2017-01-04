//
//  cpu.h
//  emulator8080
//
//  Created by Paweł Mazurkiewicz on 02/07/16.
//  Copyright © 2016 Paweł Mazurkiewicz. All rights reserved.
//

#ifndef cpu_h
#define cpu_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct conditioncodes {
    uint8_t z:1;
    uint8_t s:1;
    uint8_t p:1;
    uint8_t cy:1;
    uint8_t ac:5;
    uint8_t pad:3;
} conditioncodes;

typedef struct cpu_state {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    uint16_t  sp;
    uint16_t  pc;
    uint8_t  *memory;
    struct  conditioncodes  cc;
    uint8_t int_enable;
} cpu_state;

int disassemble8080_op(unsigned char *codebuffer, int pc);
int emulate8080op(cpu_state* state);
cpu_state* init8080(uint16_t memsize);
int parity(int x, int size);

#endif /* cpu_h */
