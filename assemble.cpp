#include <iostream>
#include "Assembler.h"
using namespace std;

int main(){

	
    // Test assembler functionality
    Assembler assembler;
    assembler.open();
    assembler.load();
    assembler.store("machine_code.txt"); 


    
return 0;
}
