The user can write assembly code in the *asm_code.asm* file and run it using the **run.sh** script.

### run.sh:
- *gen_mcode.sh* 
  - stores the assembly code in the appropiate variable in "instructions.h" (gen_mcode.cpp)
  - the assembly code is converted into machine code (assembler.cpp)
- *gen.sh*
  - the machine code is stored in the appropriate header and variable (gen_code.cpp)
- *run_emulator.sh*
  -  the registers are initialized and the machine code is run
  -  the state of the register is displayed after the execution has ended