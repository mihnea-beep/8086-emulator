echo "#####################"
echo " -- Assembler -- "
echo "Reading assembly code (asm_code.asm)"
echo "Generating instructions.h (assembly code data)"
printf "\n"
g++ assemble.cpp Assembler.cpp -lkeystone
./a.out
echo "#####################"
printf "\n"