//
//  main.c
//  emulator8080
//
//  Created by Paweł Mazurkiewicz on 02/07/16.
//  Copyright © 2016 Paweł Mazurkiewicz. All rights reserved.
//

#include <stdio.h>
#include "cpu.h"

void read_bin_into_mem(cpu_state *state, char *filename, uint32_t offset){
    FILE *file = fopen(filename, "rb");
    if (file == NULL){
        printf("Error: Could not open this file: %s\n", filename);
        exit(-1);
    }
    fseek(file, 0L, SEEK_END);
    long fsize = ftell(file);
    fseek(file, 0L, SEEK_SET);
    
    uint8_t *buffer = &state->memory[offset];
    fread(buffer, fsize, 1, file);
    fclose(file);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
