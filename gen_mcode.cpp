#include <iostream>
#include <fstream>
#include "assembler.h"
using namespace std;

int main(){

	
	// read from the machine code source file
    cout << "Reading assembly code from asm_code.asm ...\n";
	ifstream src_file("asm_code.asm");
	string line;
	getline(src_file, line);
    cout << "Code: " << line << endl;
	
    cout << "Writing assembly code to header: instructions.h\n\n";
	// create a macro/const char* containing the assembly code
	ofstream assembly_code_file;
	assembly_code_file.open("instructions.h");
	assembly_code_file << "const char* CODE = " << "\"" << line << "\"" << ";";
	src_file.close();

	assembly_code_file.close();

    
return 0;
}
