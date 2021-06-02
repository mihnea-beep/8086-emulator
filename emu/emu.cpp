#include <iostream>
#include "Assembler.h"
#include "CPU.h"
using namespace std;

int main(){

	
    // Test assembler functionality
    Assembler assembler;
    assembler.open();
    assembler.load(); // "asm_code.asm" - default input file
    assembler.store("machine_code.txt"); 
    
    
    CPU cpu;
    cpu.set_data();
    cpu.open();
    cpu.map();
    cpu.write();

    cpu.wx_regs();
    cpu.rx_regs();
    
    cpu.emulate();
    cpu.close();

    
return 0;
}
