echo "#####################"
echo "Reading assembly code (asm_code.asm)"
echo "Generating instructions.h (assembly code data)"
printf "\n"
echo "asm_code.asm -> instructions.h"
printf "\n"
g++ gen_instructions_h.cpp
./a.out
echo "#####################"

echo "Generating machine code and storing it (machine_code.h) "
printf "\n"
g++ asm_to_machine.cpp Assembler.cpp -lkeystone
./a.out

echo "#####################"

echo "Running CPU emulator ..."
printf "\n"
g++ emuTest.cpp CPU.cpp -lunicorn -lpthread
./a.out
