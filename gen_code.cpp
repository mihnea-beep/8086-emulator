#include <iostream>
#include <fstream>
#include "assembler.h"
using namespace std;

int main(){

	
	// read from the machine code source file
	ifstream src_file("asmcode.txt");
	string line;
	getline(src_file, line);
 
	
	// create a macro/const char* containing the machine code
	ofstream assembled_code_file;
	assembled_code_file.open("asmcode.h");
	assembled_code_file << "const char* X86_CODE32 = " << "\"" << line << "\"" << ";";
	src_file.close();

	assembled_code_file.close();

return 0;
}
