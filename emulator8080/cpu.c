//
//  cpu.c
//  emulator8080
//
//  Created by Paweł Mazurkiewicz on 02/07/16.
//  Copyright © 2016 Paweł Mazurkiewicz. All rights reserved.
//

#include "cpu.h"

#define PRINTOPS 1
#define PRINTREGS 1

#if PRINTOPS
int instructions_count = 0;
#endif

int disassemble8080_op(unsigned char *codebuffer, int pc){
    unsigned char *code = &codebuffer[pc];
    int opbytes = 1;
    
    printf ("%04x ", pc);
    
    switch (*code) {
        case 0x00: printf("NOP"); break;
        case 0x01: printf("LXI  B,#$%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x02: printf("STAX B"); break;
        case 0x03: printf("INX  B"); break;
        case 0x04: printf("INR  B"); break;
        case 0x05: printf("DCR  B"); break;
        case 0x06: printf("MVI  B,#$%02x", code[1]); opbytes=2; break;
        case 0x07: printf("RLC"); break;
        case 0x08: printf("NOP"); break;
        case 0x09: printf("DAD  B"); break;
        case 0x0a: printf("LDAX B"); break;
        case 0x0b: printf("DCX  B"); break;
        case 0x0c: printf("INR  C"); break;
        case 0x0d: printf("DCR  C"); break;
        case 0x0e: printf("MVI  C,#$%02x", code[1]); opbytes=2; break;
        case 0x0f: printf("RRC"); break;
        case 0x10: printf("NOP"); break;
        case 0x11: printf("LXI  D,#$%02x%02x", code[2],code[1]); opbytes=3; break;
        case 0x12: printf("STAX D"); break;
        case 0x13: printf("INX  D"); break;
        case 0x14: printf("INR  D"); break;
        case 0x15: printf("DCR  D"); break;
        case 0x16: printf("MVI  D,#$%02x", code[1]); opbytes=2; break;
        case 0x17: printf("RAL"); break;
        case 0x18: printf("NOP"); break;
        case 0x19: printf("DAD  D"); break;
        case 0x1a: printf("LDAX D"); break;
        case 0x1b: printf("DCX  D"); break;
        case 0x1c: printf("INR  E"); break;
        case 0x1d: printf("DCR  E"); break;
        case 0x1e: printf("MVI  E,#$%02x", code[1]); opbytes=2; break;
        case 0x1f: printf("RAR"); break;
        case 0x20: printf("RIM"); break;
        case 0x21: printf("LXI  H,#$%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x22: printf("SHLD $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x23: printf("INX  H"); break;
        case 0x24: printf("INR  H"); break;
        case 0x25: printf("DCR  H"); break;
        case 0x26: printf("MVI  H,#$%02x", code[1]); opbytes=2; break;
        case 0x27: printf("DAA"); break;
        case 0x28: printf("NOP"); break;
        case 0x29: printf("DAD  H"); break;
        case 0x2a: printf("LHLD $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x2b: printf("DCX  H"); break;
        case 0x2c: printf("INR  L"); break;
        case 0x2d: printf("DCR  L"); break;
        case 0x2e: printf("MVI  L,#$%02x", code[1]); opbytes=2; break;
        case 0x2f: printf("CMA"); break;
        case 0x30: printf("SIM"); break;
        case 0x31: printf("LXI  SP,#$%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x32: printf("STA  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x33: printf("INX  SP"); break;
        case 0x34: printf("INR  M"); break;
        case 0x35: printf("DCR  M"); break;
        case 0x36: printf("MVI  M,#$%02x", code[1]); opbytes=2; break;
        case 0x37: printf("STC"); break;
        case 0x38: printf("NOP"); break;
        case 0x39: printf("DAD  SP"); break;
        case 0x3a: printf("LDA  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0x3b: printf("DCX  SP"); break;
        case 0x3c: printf("INR  A"); break;
        case 0x3d: printf("DCR  A"); break;
        case 0x3e: printf("MVI  A,#$%02x", code[1]); opbytes=2; break;
        case 0x3f: printf("CMC"); break;
        case 0x40: printf("MOV  B,B"); break;
        case 0x41: printf("MOV  B,C"); break;
        case 0x42: printf("MOV  B,D"); break;
        case 0x43: printf("MOV  B,E"); break;
        case 0x44: printf("MOV  B,H"); break;
        case 0x45: printf("MOV  B,L"); break;
        case 0x46: printf("MOV  B,M"); break;
        case 0x47: printf("MOV  B,A"); break;
        case 0x48: printf("MOV  C,B"); break;
        case 0x49: printf("MOV  C,C"); break;
        case 0x4a: printf("MOV  C,D"); break;
        case 0x4b: printf("MOV  C,E"); break;
        case 0x4c: printf("MOV  C,H"); break;
        case 0x4d: printf("MOV  C,L"); break;
        case 0x4e: printf("MOV  C,M"); break;
        case 0x4f: printf("MOV  C,A"); break;
        case 0x50: printf("MOV  D,B"); break;
        case 0x51: printf("MOV  D,C"); break;
        case 0x52: printf("MOV  D,D"); break;
        case 0x53: printf("MOV  D,E"); break;
        case 0x54: printf("MOV  D,H"); break;
        case 0x55: printf("MOV  D,L"); break;
        case 0x56: printf("MOV  D,M"); break;
        case 0x57: printf("MOV  D,A"); break;
        case 0x58: printf("MOV  E,B"); break;
        case 0x59: printf("MOV  E,C"); break;
        case 0x5a: printf("MOV  E,D"); break;
        case 0x5b: printf("MOV  E,E"); break;
        case 0x5c: printf("MOV  E,H"); break;
        case 0x5d: printf("MOV  E,L"); break;
        case 0x5e: printf("MOV  E,M"); break;
        case 0x5f: printf("MOV  E,A"); break;
        case 0x60: printf("MOV  H,B"); break;
        case 0x61: printf("MOV  H,C"); break;
        case 0x62: printf("MOV  H,D"); break;
        case 0x63: printf("MOV  H,E"); break;
        case 0x64: printf("MOV  H,H"); break;
        case 0x65: printf("MOV  H,L"); break;
        case 0x66: printf("MOV  H,M"); break;
        case 0x67: printf("MOV  H,A"); break;
        case 0x68: printf("MOV  L,B"); break;
        case 0x69: printf("MOV  L,C"); break;
        case 0x6a: printf("MOV  L,D"); break;
        case 0x6b: printf("MOV  L,E"); break;
        case 0x6c: printf("MOV  L,H"); break;
        case 0x6d: printf("MOV  L,L"); break;
        case 0x6e: printf("MOV  L,M"); break;
        case 0x6f: printf("MOV  L,A"); break;
        case 0x70: printf("MOV  M,B"); break;
        case 0x71: printf("MOV  M,C"); break;
        case 0x72: printf("MOV  M,D"); break;
        case 0x73: printf("MOV  M,E"); break;
        case 0x74: printf("MOV  M,H"); break;
        case 0x75: printf("MOV  M,L"); break;
        case 0x76: printf("HLT"); break;
        case 0x77: printf("MOV  M,A"); break;
        case 0x78: printf("MOV  A,B"); break;
        case 0x79: printf("MOV  A,C"); break;
        case 0x7a: printf("MOV  A,D"); break;
        case 0x7b: printf("MOV  A,E"); break;
        case 0x7c: printf("MOV  A,H"); break;
        case 0x7d: printf("MOV  A,L"); break;
        case 0x7e: printf("MOV  A,M"); break;
        case 0x7f: printf("MOV  A,A"); break;
        case 0x80: printf("ADD  B"); break;
        case 0x81: printf("ADD  C"); break;
        case 0x82: printf("ADD  D"); break;
        case 0x83: printf("ADD  E"); break;
        case 0x84: printf("ADD  H"); break;
        case 0x85: printf("ADD  L"); break;
        case 0x86: printf("ADD  M"); break;
        case 0x87: printf("ADD  A"); break;
        case 0x88: printf("ADC  B"); break;
        case 0x89: printf("ADC  C"); break;
        case 0x8a: printf("ADC  D"); break;
        case 0x8b: printf("ADC  E"); break;
        case 0x8c: printf("ADC  H"); break;
        case 0x8d: printf("ADC  L"); break;
        case 0x8e: printf("ADC  M"); break;
        case 0x8f: printf("ADC  A"); break;
        case 0x90: printf("SUB  B"); break;
        case 0x91: printf("SUB  C"); break;
        case 0x92: printf("SUB  D"); break;
        case 0x93: printf("SUB  E"); break;
        case 0x94: printf("SUB  H"); break;
        case 0x95: printf("SUB  L"); break;
        case 0x96: printf("SUB  M"); break;
        case 0x97: printf("SUB  A"); break;
        case 0x98: printf("SBB  B"); break;
        case 0x99: printf("SBB  C"); break;
        case 0x9a: printf("SBB  D"); break;
        case 0x9b: printf("SBB  E"); break;
        case 0x9c: printf("SBB  H"); break;
        case 0x9d: printf("SBB  L"); break;
        case 0x9e: printf("SBB  M"); break;
        case 0x9f: printf("SBB  A"); break;
        case 0xa0: printf("ANA  B"); break;
        case 0xa1: printf("ANA  C"); break;
        case 0xa2: printf("ANA  D"); break;
        case 0xa3: printf("ANA  E"); break;
        case 0xa4: printf("ANA  H"); break;
        case 0xa5: printf("ANA  L"); break;
        case 0xa6: printf("ANA  M"); break;
        case 0xa7: printf("ANA  A"); break;
        case 0xa8: printf("XRA  B"); break;
        case 0xa9: printf("XRA  C"); break;
        case 0xaa: printf("XRA  D"); break;
        case 0xab: printf("XRA  E"); break;
        case 0xac: printf("XRA  H"); break;
        case 0xad: printf("XRA  L"); break;
        case 0xae: printf("XRA  M"); break;
        case 0xaf: printf("XRA  A"); break;
        case 0xb0: printf("ORA  B"); break;
        case 0xb1: printf("ORA  C"); break;
        case 0xb2: printf("ORA  D"); break;
        case 0xb3: printf("ORA  E"); break;
        case 0xb4: printf("ORA  H"); break;
        case 0xb5: printf("ORA  L"); break;
        case 0xb6: printf("ORA  M"); break;
        case 0xb7: printf("ORA  A"); break;
        case 0xb8: printf("CMP  B"); break;
        case 0xb9: printf("CMP  C"); break;
        case 0xba: printf("CMP  D"); break;
        case 0xbb: printf("CMP  E"); break;
        case 0xbc: printf("CMP  H"); break;
        case 0xbd: printf("CMP  L"); break;
        case 0xbe: printf("CMP  M"); break;
        case 0xbf: printf("CMP  A"); break;
        case 0xc0: printf("RNZ"); break;
        case 0xc1: printf("POP  B"); break;
        case 0xc2: printf("JNZ  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xc3: printf("JMP  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xc4: printf("CNZ  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xc5: printf("PUSH B"); break;
        case 0xc6: printf("ADI  #$%02x", code[1]); opbytes=2; break;
        case 0xc7: printf("RST  0"); break;
        case 0xc8: printf("RZ"); break;
        case 0xc9: printf("RET"); break;
        case 0xca: printf("JZ $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xcb: printf("NOP"); break;
        case 0xcc: printf("CZ $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xcd: printf("CALL $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xce: printf("ACI  #$%02x", code[1]); opbytes=2; break;
        case 0xcf: printf("RST  1"); break;
        case 0xd0: printf("RNC"); break;
        case 0xd1: printf("POP  D"); break;
        case 0xd2: printf("JNC  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xd3: printf("OUT  #$%02x", code[1]); opbytes=2; break;
        case 0xd4: printf("CNC  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xd5: printf("PUSH D"); break;
        case 0xd6: printf("SUI  #$%02x", code[1]); opbytes=2; break;
        case 0xd7: printf("RST  2"); break;
        case 0xd8: printf("RC"); break;
        case 0xd9: printf("NOP"); break;
        case 0xda: printf("JC $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xdb: printf("IN #$%02x", code[1]); opbytes=2; break;
        case 0xdc: printf("CC $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xdd: printf("NOP"); break;
        case 0xde: printf("SBI  #$%02x", code[1]); opbytes=2; break;
        case 0xdf: printf("RST  3"); break;
        case 0xe0: printf("RPO"); break;
        case 0xe1: printf("POP  H"); break;
        case 0xe2: printf("JPO  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xe3: printf("XTHL"); break;
        case 0xe4: printf("CPO  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xe5: printf("PUSH H"); break;
        case 0xe6: printf("ANI  #$%02x", code[1]); opbytes=2; break;
        case 0xe7: printf("RST  4"); break;
        case 0xe8: printf("RPE"); break;
        case 0xe9: printf("PCHL"); break;
        case 0xea: printf("JPE  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xeb: printf("XCHG"); break;
        case 0xec: printf("CPE  $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xed: printf("NOP"); break;
        case 0xee: printf("XRI  #$%02x", code[1]); opbytes=2; break;
        case 0xef: printf("RST  5"); break;
        case 0xf0: printf("RP"); break;
        case 0xf1: printf("POP  PSW"); break;
        case 0xf2: printf("JP $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xf3: printf("DI"); break;
        case 0xf4: printf("CP $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xf5: printf("PUSH PSW"); break;
        case 0xf6: printf("ORI  #$%02x", code[1]); opbytes=2; break;
        case 0xf7: printf("RST  6"); break;
        case 0xf8: printf("RM"); break;
        case 0xf9: printf("SPHL"); break;
        case 0xfa: printf("JM $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xfb: printf("EI"); break;
        case 0xfc: printf("CM $%02x%02x", code[2], code[1]); opbytes=3; break;
        case 0xfd: printf("NOP"); break;
        case 0xfe: printf("CPI  #$%02x", code[1]); opbytes=2; break;
        case 0xff: printf("RST  7"); break;
        default: printf("Unrecognized instruction! %02x", code[0]); break;
    }
    
    printf ("\n");
    return opbytes;
}

int unimplemented_instruction(cpu_state* state){
    state->pc--;
    printf("Error: Unimplemented instruction\n");
    disassemble8080_op(state->memory, state->pc);
    printf("\n");
    return state->pc;
}

uint16_t get_hl_addr(cpu_state* state){
    uint16_t addr = (state->h << 8) | (state->l);
    return addr;
}

int parity(int x, int size){
    int i;
    int p = 0;
    x = (x & ((1<<size)-1));
    for (i=0; i < size; i++){
        if(x & 0x1) p++;
        x = x >> 1;
    }
    return (0 == (p & 0x1));
}

int emulate8080op(cpu_state* state){
    
    unsigned char *opcode = &state->memory[state->pc];
    
#if PRINTOPS
    disassemble8080_op(state->memory, state->pc);
    instructions_count += 1;
    //if (instructions_count == 37390) exit(0); //end of initial black screen
#endif
    
    state->pc+=1;
    
    switch (*opcode) {
        case 0x00:  //NOP
            break;
        case 0x01:  //LXI   B,D16
            state->c = opcode[1];
            state->b = opcode[2];
            state->pc += 2;
            break;
        case 0x02: //STAX B
        {
            uint32_t bc = (state->b << 8) | state->c;
            state->memory[bc] = state->a;
            break;
        }
        case 0x03: //INX B
        {
            state->c++;
            if (state->c == 0)
                state->b++;
            break;
        }
        case 0x04: //INR B
        {
            uint8_t res = state->b + 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->b = res;
            break;
        }
        case 0x05: //DCR B
        {
            uint8_t res = state->b - 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->b = res;
            break;
        }
        case 0x06:  //MVI B,D8
        {
            state->b = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x07: //RLC (Rotate left)
        {
            uint8_t x = state->a;
            state->a = ((x & 1) >> 7) | (x << 1);
            state->cc.cy = (0x80 == (x & 0x80));
            break;
        }
        case 0x08: //-
        {
            unimplemented_instruction(state);
            break;
        }
        case 0x09: //DAD B
        {
            uint16_t hl = (state->h << 8) | state->l;
            uint16_t bc = (state->b << 8) | state->c;
            uint32_t res = hl + bc;
            state->h = (res & 0xff00) >> 8;
            state->l = res & 0xff;
            state->cc.cy = ((res & 0xffff0000) !=0);
            break;
        }
        case 0x0a: //LDAX B
        {
            uint32_t bc = (state->b << 8) | state->c;
            state->a = state->memory[bc];
            break;
        }
        case 0x0b: //DCX B
        {
            state->c -= 1;
            if (state->c == 0xff)
                state->b =-1;
            break;
        }
        case 0x0c: //INR C
        {
            uint8_t res = state->c + 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);

            state->cc.z = (res == 0);
            state->c = res;
            break;
        }
        case 0x0d: //DCR C
        {
            uint8_t res = state->c - 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->c = res;
            break;
        }
        case 0x0e: //MVI C,D8
        {
            state->c = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x0f: //RRC (Rotate right)
        {
            uint8_t x = state->a;
            state->a = ((x & 1) << 7) | (x >> 1);
            state->cc.cy = (1 == (x & 1));
            break;
        }
        case 0x10: //-
        {
            unimplemented_instruction(state);
            break;
        }
        case 0x11: //LXI D,D16
        {
            state->e = opcode[1];
            state->d = opcode[2];
            state->pc += 2;
            break;
        }
        case 0x12: //STAX D
        {
            uint32_t de = (state->d << 8) | state->e;
            state->memory[de] = state->a;
            break;
        }
        case 0x13: //INX D
        {
            state->e++;
            if (state->e == 0)
                state->d++;
            break;
        }
        case 0x14: //INR D
        {
            uint8_t res = state-> d + 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->d = res;
            break;
        }
        case 0x15: //DCR D
        {
            uint8_t res = state-> d - 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.z = parity(res, 8);
            state->cc.z = (res == 0);
            state->d = res;
            break;
        }
        case 0x16: //MVI D, D8
        {
            state->d = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x17: //RAL
        {
            uint8_t x = state->a;
            state->a = state->cc.cy | (x << 1);
            state->cc.cy = (0x80 == (x & 0x80));
            break;
        }
        case 0x18: //-
        {
            unimplemented_instruction(state);
            break;
        }
        case 0x19: //DAD D
        {
            uint16_t hl = (state->h << 8) | state->l;
            uint16_t de = (state->d << 8) | state->e;
            uint32_t res = hl + de;
            state->h = (res & 0xff00) >> 8;
            state->l = res & 0xff;
            state->cc.cy = ((res & 0xffff0000) !=0);
            break;
        }
        case 0x1a: //LDAX D
        {
            uint32_t de = (state->d << 8) | state->e;
            state->a = state->memory[de];
            break;
        }
        case 0x1b: //DCX D
        {
            state->e -= 1;
            if (state->e == 0xff)
                state->d =-1;
            break;
        }
        case 0x1c: //INR E
        {
            uint8_t res = state-> e + 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->e = res;
            break;

        }
        case 0x1d: //DCR E
        {
            uint8_t res = state-> e - 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->e = res;
            break;
        }
        case 0x1e: //MVI E,D8
        {
            state->e = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x1f: //RAR
        {
            uint8_t x = state->a;
            state->a = (state->cc.cy << 7) | (x >> 1);
            state->cc.cy = (1 == (x & 1));
            break;
        }
        case 0x20: // -
        {
            unimplemented_instruction(state);
            break;
        }
        case 0x21: //LXI H,D16
        {
            state->l = opcode[1];
            state->h = opcode[2];
            state->pc += 2;
            break;
        }
        case 0x22: //SHLD addr
        {
            uint16_t addr = opcode[1] | (opcode[2] << 8);
            state->memory[addr] = state->l;
            state->memory[addr+1] = state->h;
            state->pc+=2;
            break;
        }
        case 0x23: //INX H
        {
            state->l++;
            if (state->l == 0)
                state->h++;
            break;
        }
        case 0x24: //INR H
        {
            uint8_t res = state-> h + 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->h = res;
            break;
        }
        case 0x25: //DCR H
        {
            uint8_t res = state-> h - 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->h = res;
            break;
        }
        case 0x26: //MVI H,D8
        {
            state->h = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x27: //DAA - special case, TBD
        {
            return unimplemented_instruction(state);
        }
        case 0x28: //-
        {
            return unimplemented_instruction(state);
        }
        case 0x29: //DAD H
        {
            uint16_t hl = (state->h << 8) | state->l;
            uint32_t res = hl + hl;
            state->h = (res & 0xff00) >> 8;
            state->l = res & 0xff;
            state->cc.cy = ((res & 0xffff0000) !=0);
            break;
        }
        case 0x2a: //LHLD addr
        {
            uint16_t addr = opcode[1] | (opcode[2] << 8);
            state->l = state->memory[addr];
            state->h = state->memory[addr+1];
            state->pc+=2;
            break;
        }
        case 0x2b: //DCX H
        {
            state->l -= 1;
            if (state->l == 0xff)
                state->h =-1;
            break;
        }
        case 0x2c: //INR L
        {
            uint8_t res = state-> l + 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->l = res;
            break;
        }
        case 0x2d: //DCR L
        {
            uint8_t res = state-> l - 1;
            if (res & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            if (res > 0xff)
                state->cc.cy = 1;
            else
                state->cc.cy = 0;
            state->cc.p = parity(res, 8);
            state->cc.z = (res == 0);
            state->l = res;
            break;
        }
        case 0x2e: //MVI L,D8
        {
            state->l = opcode[1];
            state->pc += 1;
            break;
        }
        case 0x2f: //CMA
        {
            state->a = ~state->a;
            break;
        }
        case 0x30: //-
        {
            return unimplemented_instruction(state);
        }
        case 0x31: //LXI SP,D16
        {
            state->sp = (opcode[2]<<8) | opcode[1];
            state->pc += 2;
            break;
        }
        case 0x32: //STA addr
        {
            uint16_t addr = (opcode[2]<<8) | opcode[1];
            state->memory[addr] = state->a;
            state->pc += 2;
            break;
        }
        case 0x33: //INX SP
        {
            state->sp++;
            break;
        }
        case 0x34: //INR M
        {
            uint16_t res = ((state->h << 8) | state->l) + 1;
            state->cc.z = (res == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res, 16);
            state->memory[state->h << 8 | state->l] = res;
            break;
        }
        case 0x35: //DCR M
        {
            uint16_t res = ((state->h << 8) | state->l) - 1;
            state->cc.z = (res == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res, 16);
            state->memory[state->h << 8 | state->l] = res;
            break;
        }
        case 0x36: //MVI M,D8
        {
            state->memory[state->h << 8 | state->l] = opcode[1];
            state->pc++;
            break;
        }
        case 0x37: //STC
        {
            state->cc.cy = 1;
            break;
        }
        case 0x38: //-
        {
            return unimplemented_instruction(state);
        }
        case 0x39: //DAD SP
        {
            uint16_t hl = (state->h << 8) | state->l;
            uint32_t res = hl + state->sp;
            state->h = (res & 0xff00) >> 8;
            state->l = res & 0xff;
            state->cc.cy = ((res & 0xffff0000) > 0);
            break;
        }
        case 0x3a: //LDA addr
        {
            uint16_t addr = (opcode[2] << 8) | (opcode[1]);
            state->a = state->memory[addr];
            state->pc+=2;
            break;
        }
        case 0x3b: //DCX SP
        {
            state->sp -= 1;
            break;
        }
        case 0x3c: //INR A
        {
            state->a += 1;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0x3d: //DCR A
        {
            state->a -= 1;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0x3e: //MVI A,D8
        {
            state->a = opcode[1];
            state->pc++;
            break;
        }
        case 0x3f: //CMC
        {
            state->cc.cy = ~state->cc.cy;
            break;
        }
        case 0x40: state->b = state->b; break; //MOV B,B
        case 0x41: state->b = state->c; break; //MOV B,C
        case 0x42: state->b = state->d; break; //MOV B,D
        case 0x43: state->b = state->e; break; //MOV B,E
        case 0x44: state->b = state->h; break; //MOV B,H
        case 0x45: state->b = state->l; break; //MOV B,L
        case 0x46: //MOV B,M
        {
            state->b = state->memory[get_hl_addr(state)];
            break;
        }
        case 0x47: state->b = state->a; break; //MOV B,A
            
        case 0x48: state->c = state->b; break; //MOV C,B
        case 0x49: state->c = state->c; break; //MOV C,C
        case 0x4a: state->c = state->d; break; //MOV C,D
        case 0x4b: state->c = state->e; break; //MOV C,E
        case 0x4c: state->c = state->h; break; //MOV C,H
        case 0x4d: state->c = state->l; break; //MOV C,L
        case 0x4e:
        {
            state->c = state->memory[get_hl_addr(state)];
            break;
        }
        case 0x4f: state->c = state->a; break; //MOV C,A
            
        case 0x50: state->d = state->b; break; //MOV D,B
        case 0x51: state->d = state->c; break; //MOV D,C
        case 0x52: state->d = state->d; break; //MOV D,D
        case 0x53: state->d = state->e; break; //MOV D,E
        case 0x54: state->d = state->h; break; //MOV D,H
        case 0x55: state->d = state->l; break; //MOV D,L
        case 0x56: //MOV D,M
        {
            state->d = state->memory[get_hl_addr(state)];
            break;
        }
        case 0x57: state->d = state->a; break; //MOV D,A
            
        case 0x58: state->e = state->b; break; //MOV E,B
        case 0x59: state->e = state->c; break; //MOV E,C
        case 0x5a: state->e = state->d; break; //MOV E,D
        case 0x5b: state->e = state->e; break; //MOV E,E
        case 0x5c: state->e = state->h; break; //MOV E,H
        case 0x5d: state->e = state->l; break; //MOV E,L
        case 0x5e: //MOV E,M
        {
            state->e = state->memory[get_hl_addr(state)];
            break;
        }
        case 0x5f: state->e = state->a; break; //MOV E,A
            
        case 0x60: state->h = state->b; break; //MOV H,B
        case 0x61: state->h = state->c; break; //MOV H,C
        case 0x62: state->h = state->d; break; //MOV H,D
        case 0x63: state->h = state->e; break; //MOV H,E
        case 0x64: state->h = state->h; break; //MOV H,H
        case 0x65: state->h = state->l; break; //MOV H,L
        case 0x66: //MOV H,M
        {
            state->h = state->memory[get_hl_addr(state)];
            break;
        }
        case 0x67: state->h = state->a; break; //MOV H,A
            
        case 0x68: state->l = state->b; break; //MOV L,B
        case 0x69: state->l = state->c; break; //MOV L,C
        case 0x6a: state->l = state->d; break; //MOV L,D
        case 0x6b: state->l = state->e; break; //MOV L,E
        case 0x6c: state->l = state->h; break; //MOV L,H
        case 0x6d: state->l = state->l; break; //MOV L,L
        case 0x6e: //MOV L,M
        {
            state->l = state->memory[get_hl_addr(state)];
            break;
        }
        case 0x6f: state->l = state->a; break; //MOV L,A
            
        case 0x70: //MOV M,B
        {
            state->memory[get_hl_addr(state)] = state->b;
            break;
        }
        case 0x71: //MOV M,C
        {
            state->memory[get_hl_addr(state)] = state->c;
            break;
        }
        case 0x72: //MOV M,D
        {
            state->memory[get_hl_addr(state)] = state->d;
            break;
        }
        case 0x73: //MOV M,E
        {
            state->memory[get_hl_addr(state)] = state->e;
            break;
        }
        case 0x74: //MOV M,H
        {
            state->memory[get_hl_addr(state)] = state->h;
            break;
        }
        case 0x75: //MOV M,L
        {
            state->memory[get_hl_addr(state)] = state->l;
            break;
        }
        case 0x76: //HLT
        {
            return unimplemented_instruction(state);
        }
        case 0x77: //MOV M,A
        {
            state->memory[get_hl_addr(state)] = state->a;
            break;
        }
        case 0x78: state->a = state->b; break; //MOV A,B
        case 0x79: state->a = state->c; break; //MOV A,C
        case 0x7a: state->a = state->d; break; //MOV A,D
        case 0x7b: state->a = state->e; break; //MOV A,E
        case 0x7c: state->a = state->h; break; //MOV A,H
        case 0x7d: state->a = state->l; break; //MOV A,L
        case 0x7e: state->a = state->memory[get_hl_addr(state)]; break; //MOV A,M
        case 0x7f: state->a = state->a; break; //MOV A,A
        case 0x80: //ADD B
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->b;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x81: //ADD C
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->c;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x82: //ADD D
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->d;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x83: //ADD E
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->e;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x84: //ADD H
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->h;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x85: //ADD L
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->l;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x86: //ADD M
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->memory[get_hl_addr(state)];
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x87: //ADD A
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->a;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x88: //ADC B
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->b + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x89: //ADC C
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->c + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x8a: //ADC D
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->d + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x8b: //ADC E
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->e + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x8c: //ADC H
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->h + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x8d: //ADC L
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->l + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x8e: //ADC M
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->memory[get_hl_addr(state)] + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x8f: //ADC A
        {
            uint16_t res = (uint16_t)state->a + (uint16_t)state->a + state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x90: //SUB B
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->b;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x91: //SUB C
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->c;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x92: //SUB D
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->d;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x93: //SUB E
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->e;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x94: //SUB H
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->h;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x95: //SUB L
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->l;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x96: //SUB M
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->memory[get_hl_addr(state)];
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x97: //SUB A
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->a;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x98: //SBB B
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->b - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x99: //SBB C
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->c - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x9a: //SBB D
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->d - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x9b: //SBB E
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->e - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x9c: //SBB H
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->h - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x9d: //SBB L
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->l - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x9e: //SBB M
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->memory[get_hl_addr(state)] - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0x9f: //SBB A
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->a - state->cc.z;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            state->a = (res & 0xff);
            break;
        }
        case 0xa0: //ANA B
        {
            state->a = state->a & state->b;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa1: //ANA C
        {
            state->a = state->a & state->c;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa2: //ANA D
        {
            state->a = state->a & state->d;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa3: //ANA E
        {
            state->a = state->a & state->e;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa4: //ANA H
        {
            state->a = state->a & state->h;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa5: //ANA L
        {
            state->a = state->a & state->b;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa6: //ANA M
        {
            state->a = state->a & state->memory[get_hl_addr(state)];
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa7: //ANA A
        {
            state->a = state->a & state->a;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa8: //XRA B
        {
            state->a = state->a ^ state->b;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xa9: //XRA C
        {
            state->a = state->a ^ state->c;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xaa: //XRA D
        {
            state->a = state->a ^ state->d;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xab: //XRA E
        {
            state->a = state->a ^ state->e;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xac: //XRA H
        {
            state->a = state->a ^ state->h;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xad: //XRA L
        {
            state->a = state->a ^ state->l;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xae: //XRA M
        {
            state->a = state->a ^ state->memory[get_hl_addr(state)];
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xaf: //XRA A
        {
            state->a = state->a ^ state->a;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb0: //ORA B
        {
            state->a = state->a | state->b;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb1: //ORA C
        {
            state->a = state->a | state->c;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb2: //ORA D
        {
            state->a = state->a | state->d;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb3: //ORA E
        {
            state->a = state->a | state->e;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb4: //ORA H
        {
            state->a = state->a | state->h;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb5: //ORA L
        {
            state->a = state->a | state->l;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb6: //ORA M
        {
            state->a = state->a | state->b;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb7: //ORA A
        {
            state->a = state->a | state->a;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            break;
        }
        case 0xb8: //CMP B
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->b;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xb9: //CMP C
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->c;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xba: //CMP D
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->d;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xbb: //CMP E
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->e;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xbc: //CMP H
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->h;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xbd: //CMP L
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->l;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xbe: //CMP M
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->memory[get_hl_addr(state)];
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xbf: //CMP A
        {
            uint16_t res = (uint16_t)state->a - (uint16_t)state->a;
            state->cc.z = ((res & 0xff) == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res & 0xff, 8);
            break;
        }
        case 0xc0: //RNZ
        {
            if (state->cc.z == 0){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->pc += 2;
            }
            break;
        }
        case 0xc1: //POP B
        {
            state->c = state->memory[state->sp];
            state->b = state->memory[state->sp + 1];
            state->sp += 2;
            break;
        }
        case 0xc2: //JNZ
        {
            if (state->cc.z == 0) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc += 2;
            break;
        }
        case 0xc3: //JMP
        {
            state->pc = (opcode[2] << 8) | opcode[1];
            break;
        }
        case 0xc4: //CNZ addr
        {
            if (state->cc.z == 0){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xc5: //PUSH B
        {
            state->memory[state->sp-2] = state->c;
            state->memory[state->sp-1] = state->b;
            state->sp -= 2;
            break;
        }
        case 0xc6: ///ADI D8
        {
            uint16_t res = (uint16_t) state->a + (uint16_t) opcode[1];
            state->cc.z = (res == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res, 8);
            state->cc.cy = (res > 0xff);
            state->a = (res & 0xff);
            state->pc++;
            break;
        }
        case 0xc7: //RST 0
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x0000;
            break;
        }
        case 0xc8: //RZ
        {
            if (state->cc.z == 0){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xc9: //RET
        {
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
            state->sp += 2;
            break;
        }
        case 0xca: //JZ addr
        {
            if (state->cc.z == 0) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc += 2;
            break;
        }
        case 0xcb: //-
        {
            return unimplemented_instruction(state);
        }
        case 0xcc: //CZ addr
        {
            if (state->cc.z == 0){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xcd: //CALL
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = (opcode[2] << 8) | opcode[1];
            break;
        }
        case 0xce: //ACI D8
        {
            uint16_t res = (uint16_t) state->a + (uint16_t) opcode[1] + (uint16_t)state->cc.cy;
            state->cc.z = (res == 0);
            state->cc.s = (0x80 == (res & 0x80));
            state->cc.p = parity(res, 8);
            state->cc.cy = (res > 0xff);
            state->a = (res & 0xff);
            state->pc++;
            break;
        }
        case 0xcf: //RST 1
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x10;
            break;
        }
        case 0xd0: //RNC
        {
            if (state->cc.cy == 0){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xd1: //POP D
        {
            state->e = state->memory[state->sp];
            state->d = state->memory[state->sp + 1];
            state->sp += 2;
            break;
        }
        case 0xd2: //JNC addr
        {
            if (state->cc.cy == 0) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc += 2;
            break;
        }
        case 0xd3: //OUT D8
        {
            //FIXME: actual implementation
            state->pc++; //skip over the byte for now
            break;
        }
        case 0xd4: //CNC addr
        {
            if (state->cc.cy == 0){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xd5: //PUSH D
        {
            state->memory[state->sp-2] = state->e;
            state->memory[state->sp-1] = state->d;
            state->sp -= 2;
            break;
        }
        case 0xd6: //SUI D8
        {
            uint8_t res = state->a - opcode[1];
            state->cc.z = (res & 0xff) == 0;
            state->cc.s = (0x80 == ((res & 0xff) & 0x80));
            state->cc.p = parity(res, 8);
            state->cc.cy = (state->a < opcode[1]);
            state->pc++;
            break;
        }
        case 0xd7: //RST 2
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x10;
            break;
        }
        case 0xd8: //RC
        {
            if (state->cc.cy == 1){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xd9: //-
        {
            return unimplemented_instruction(state);
        }
        case 0xda: //JC addr
        {
            if (state->cc.cy == 1) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc += 2;
            break;
        }
        case 0xdb: //IN
        {
            //FIXME: Actual implementation
            state->pc++; //skip over byte for now
            break;
        }
        case 0xdc: //CC addr
        {
            if (state->cc.cy == 1){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xdd: //-
        {
            return unimplemented_instruction(state);
        }
        case 0xde: //SBI D8
        {
            uint8_t res = state->a - opcode[1] - state->cc.cy;
            state->cc.z = (res & 0xff) == 0;
            state->cc.s = (0x80 == ((res & 0xff) & 0x80));
            state->cc.p = parity(res, 8);
            state->cc.cy = (state->a < opcode[1]);
            state->pc++;
            break;
        }
        case 0xdf: //RST 3
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x18;
            break;
        }
        case 0xe0: //RPO
        {
            if (state->cc.p == 0){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xe1: //POP H
        {
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp + 1];
            state->sp += 2;
            break;
        }
        case 0xe2: //JPO addr
        {
            if (state->cc.p == 0) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc += 2;
            break;
        }
        case 0xe3: //XTHL
        {
            uint8_t h = state->h;
            uint8_t l = state->l;
            state->l = state->memory[state->sp];
            state->h = state->memory[state->sp + 1];
            state->memory[state->sp] = l;
            state->memory[state->sp + 1] = h;
            break;
        }
        case 0xe4: //CPO addr
        {
            if (state->cc.p == 0){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xe5: //PUSH H
        {
            state->memory[state->sp-2] = state->l;
            state->memory[state->sp-1] = state->h;
            state->sp -= 2;
            break;
        }
        case 0xe6: //ANI D8
        {
            uint16_t res = (state->a & opcode[1]);
            state->a = res;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            state->pc++;
            break;
        }
        case 0xe7: //RST 4
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x20;
            break;
        }
        case 0xe8: //RPE
        {
            if (state->cc.p != 0){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xe9: //PCHL
        {
            state->pc = get_hl_addr(state);
            break;
        }
        case 0xea: //JPE addr
        {
            if (state->cc.p != 0) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc +=2;
            break;
        }
        case 0xeb: //XCHG
        {
            uint8_t temp = 0x0;
            temp = state->d;
            state->d = state->h;
            state->h = temp;
            temp = state->l;
            state->e = state->l;
            state->l = temp;
            break;
        }
        case 0xec: //CPE
        {
            if (state->cc.p != 0){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xed: //-
        {
            return unimplemented_instruction(state);
        }
        case 0xee: //XRI D8
        {
            uint16_t res = (state->a ^ opcode[1]);
            state->a = res;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            state->pc++;
            break;
        }
        case 0xef: //RST 5
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x28;
            break;
        }
        case 0xf0: //RP
        {
            if (state->cc.s == 0){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xf1: //POP PSW
        {
            state->a = state->memory[state->sp + 1];
            uint8_t psw  = state->memory[state->sp];
            state->cc.z = (0x01 == (psw & 0x01));
            state->cc.s = (0x02 == (psw & 0x02));
            state->cc.p = (0x04 == (psw & 0x04));
            state->cc.cy = (0x05 == (psw & 0x08));
            state->cc.ac = (0x10 == (psw & 0x10));
            state->sp += 2;
            break;
        }
        case 0xf2: //JP addr
        {
            if (state->cc.s == 0) state->pc = (opcode[2] << 8) | opcode[1];
            else state->pc += 2;
            break;
        }
        case 0xf3: //DI
        {
            state->int_enable = 0;
            break;
        }
        case 0xf4: //CP addr
        {
            if (!state->cc.s){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xf5: //PUSH PSW
        {
            state->memory[state->sp - 1] = state->a;
            uint8_t psw =   (state->cc.z |
                            state->cc.s << 1 |
                            state->cc.p << 2 |
                            state->cc.cy << 3 |
                            state->cc.ac << 4 );
            state->memory[state->sp - 2] = psw;
            state->sp -= 2;
            break;
        }
        case 0xf6: //ORI D8
        {
            uint16_t res = (state->a | opcode[1]);
            state->a = res;
            state->cc.cy = state->cc.ac = 0;
            state->cc.z = (state->a == 0);
            state->cc.s = (0x80 == (state->a & 0x80));
            state->cc.p = parity(state->a, 8);
            state->pc++;
            break;
        }
        case 0xf7: //RST 6
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x30;
            break;
        }
        case 0xf8: //RM
        {
            if (state->cc.s == 1){
                state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
                state->sp += 2;
            }
            break;
        }
        case 0xf9: //SPHL
        {
            state->sp = get_hl_addr(state);
            break;
        }
        case 0xfa: //JM addr
        {
            if (state->cc.s == 1){
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xfb: //EI
        {
            state->int_enable = 1;
            break;
        }
        case 0xfc: //CM addr
        {
            if (state->cc.s == 1){
                uint16_t ret = state->pc+2;
                state->memory[state->sp-1] = (ret >> 8) & 0xff;
                state->memory[state->sp-2] = ret & 0xff;
                state->sp = state->sp-2;
                state->pc = (opcode[2] << 8) | opcode[1];
            } else state->pc += 2;
            break;
        }
        case 0xfd: //-
        {
            return unimplemented_instruction(state);
        }
        case 0xfe: //CPI D8
        {
            uint8_t x = state->a - opcode[1];
            state->cc.z = (x == 0);
            if (x & 0x80)
                state->cc.s = 1;
            else
                state->cc.s = 0;
            state->cc.p = parity(x, 8);
            state->cc.cy = (state->a < opcode[1]);
            state->pc++;
            break;
        }
        case 0xff: //RST 7
        {
            uint16_t ret = state->pc+2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = ret & 0xff;
            state->sp = state->sp-2;
            state->pc = 0x38;
            break;
        }
    }
#if PRINTREGS
    printf("\tC=%d,P=%d,S=%d,Z=%d\n", state->cc.cy, state->cc.p,
           state->cc.s, state->cc.z);
    printf("\tA $%02x B $%02x C $%02x D $%02x E $%02x H $%02x L $%02x SP %04x\n",
           state->a, state->b, state->c, state->d,
           state->e, state->h, state->l, state->sp);
    printf("\tCurrent instructions count: %d\n", instructions_count);
#endif
    return 0;
}

cpu_state* init8080(uint16_t memsize){
    cpu_state* init_state = calloc(1, sizeof(cpu_state));
    init_state->memory = calloc(1, memsize); //Initialize memory
    init_state->cc.z = 0;
    init_state->cc.s = 0;
    init_state->cc.cy = 0;
    init_state->cc.p = 0;
    init_state->cc.ac = 0;
    return init_state;
}
