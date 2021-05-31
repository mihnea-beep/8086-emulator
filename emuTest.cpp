#include <iostream>
#include "Assembler.h"
#include "CPU.h"
using namespace std;

int main(int argc, char const *argv[])
{

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
