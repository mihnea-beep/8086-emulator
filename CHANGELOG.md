# Changelog

###  0.1.0

- The user can write asm code in "asm_code.asm" and run it with run.sh
- run.sh runs gen_mcode.sh, gen.sh and run_emulator.sh
- #### run.sh:
    - *gen_mcode.sh* 
        - stores the assembly code in the appropiate variable in "instructions.h" (gen_mcode.cpp)
        - the assembly code is converted into machine code (assembler.cpp)
    - *gen.sh*
        - the machine code is stored in the appropriate header and variable (gen_code.cpp)
    - *run_emulator.sh*
        -  the registers are initialized and the machine code is run
        -  the state of the register is displayed after the execution has ended

### 0.1.1

- Refactoring:
    - CPU class
    - Assembler class

### 0.1.2

- Instructions (assembly code) are loaded directly from the user input file  
- Assembled data for the CPU logic program is now stored in "machine_code.h"

### 0.1.3

- Added step by step execution (register state tracking)
- Minor fixes

### 0.1.4

- GUI Menu (buttons):
    - Assemble
    - Edit (separate thread)
    - Execute (separate thread)
    - Exit
