#include <sstream>
#include <iostream>
#include <fstream>
#include "instructions.h"
#include <keystone/keystone.h>
#include <algorithm>
#include <iomanip>
#include <cstddef>
#include "assembler.h"

using namespace std;
/** KEYSTONE - ASSEMBLER **/

string asm_code;// = "INC ecx; INC ecx; INC ecx; DEC edx;";//"INC ecx; DEC edx; MOV ebx, 2; MOV edx, ebx; MOV eax, 500"; //"INC ecx; DEC edx";

// const char *CODE = asm_code.c_str(); 
// strcpy(CODE);
//#define CODE
size_t size;

string a = "asd";

ks_engine *ks;
ks_err err_ks;
size_t stat_count;
unsigned char *encode;

string compiled_string;
string compiled_string_filtered;
stringstream stream;
const char *c_assembled_code;
// const char *X86_CODE32;


int get_code_size()
{
  return size;
}

int open_ks()
{

  err_ks = ks_open(KS_ARCH_X86, KS_MODE_32, &ks);
  if (err_ks != KS_ERR_OK)
  {
    printf("ERROR: failed on ks_open(), quit\n");
    return -1;
  }
  else
    return 1;
}

void compile_ks()
{
  if (ks_asm(ks, CODE, 0, &encode, &size, &stat_count) != KS_ERR_OK)
  {
    printf("ERROR: ks_asm() failed & stat_count = %lu, error = %u\n",
           stat_count, ks_errno(ks));
  }
  else
  {
    size_t i;

    printf("%s = ", CODE);
    for (i = 0; i < size; i++)
    {
      printf("%02x ", encode[i]);

      stream << "\\" << 'x' << hex << setw(2) << setfill('0') << (int)(encode[i]);
      compiled_string = compiled_string + "\\x" + to_string(encode[i]);
    }
    printf("\n");
    printf("Compiled: %lu bytes, statements: %lu\n", size, stat_count);
    // cout << stream.str() << endl;
  }
}

void free_ks()
{
  // NOTE: free encode after usage to avoid leaking memory
  ks_free(encode);
}

void close_ks()
{
  // close Keystone instance when done
  ks_close(ks);
}

string assemble_ks()
{
  open_ks();
  compile_ks();

  // cout << "Compiled string raw decimal: " + compiled_string << endl;
  cout << "Compiled string stream hex: " + stream.str() << endl;
  string new_stream = stream.str();
  for (int i = 0; i < new_stream.length(); i++)
  {
    if (new_stream[i] == '\\')
      new_stream[i] = ' ';
  }
  new_stream.erase(remove(new_stream.begin(), new_stream.end(), 'x'), new_stream.end());
  cout << "Compiled stream clean hex: " << new_stream << endl;

  new_stream = stream.str();
  const char *x;
  x = new_stream.c_str();
  cout << "Compiled code size: " << size << "(bytes)" << endl;
  cout << "x: " << x;
  cout << endl
       << endl;
  cout << "Compilation done --- " << endl
       << endl;

  free_ks();
  close_ks();
  return stream.str();
}

/** KEYSTONE - ASSEMBLER **/

int main()
{
    // read .asm code and turn it into machine code
	
	ifstream asm_file("asm_code.asm");
	getline(asm_file, asm_code);

     // turn assembly into machine code
	 cout << "ASSEMBLER" << endl
         << "--- --- --- " << endl
         << endl;

    stringstream ss_assembled_code;
    ss_assembled_code << assemble_ks();
    string s_assembled_code = ss_assembled_code.str();
    c_assembled_code = s_assembled_code.c_str();
    // c_assembled_code = assemble_ks().c_str();
    cout << "--- --- --- " << endl
         << endl;
    fstream assembled_data_file;
    assembled_data_file.open("asmcode.txt");
    // assembled_data_file << "X86_CODE32 = ";
    assembled_data_file << c_assembled_code; //ss_assembled_code.str();
    assembled_data_file.close();

    cout << "c_assembled_code: " << string(c_assembled_code) << endl;

    ofstream metadata_file;
    metadata_file.open("metadata.txt");
    metadata_file << size;
    metadata_file.close();    
    
    return 0;
}