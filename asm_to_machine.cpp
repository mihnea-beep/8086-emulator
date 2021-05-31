#include <iostream>
#include "Assembler.h"
using namespace std;

int main(int argc, char const *argv[])
{
    Assembler assembler;

    assembler.store("machine_code.h");
    return 0;
}
