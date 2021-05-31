echo "Generating instructions header (instructions.h) . . . "
g++ -o generate_machine_code gen_mcode.cpp -lkeystone
./generate_machine_code
cat instructions.h
echo ". . . "
echo "Generating assembled code header (assembler.h)"
g++ -o assemble_code assembler.cpp -lkeystone
./assemble_code
echo  ". . . "
