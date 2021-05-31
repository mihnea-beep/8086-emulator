#include <unicorn/unicorn.h>
#include <iostream>
#include <bitset>
#include <cstring>
#include <keystone/keystone.h>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <fstream>
#include "asmcode.h"
#include "assembler.h"
#include <fstream>
using namespace std;


// code to be emulated
#define X86_CODE323 "\x41\x4a\xBB\x00\x00\x00\x00\x89\xDA\xB8\x32\x00\x00\x00"
// INC ecx; DEC edx; MOV ebx, 0; MOV edx, ebx; MOV eax, 50
// memory address where emulation starts
#define ADDRESS 0x1000000
int size;
bool open()
{

  return true;
}

bool map()
{
  return true;
}

bool writeMachineCode()
{

  return true;
}

void writeRegs()
{
}

void readRegs()
{
}

void emulate()
{
}

void close()
{
}

void read_metadata(){
  ifstream metadata_file("metadata.txt"); // TODO: add more data
  string size_data;
  getline(metadata_file, size_data); // size is read from the first line
  size = stoi(size_data);
}

int main(int argc, char **argv, char **envp)
{
  
  printf("Emulate i386 code\n");
  read_metadata();
  cout << size << "SIZEEEE" << endl;
  cout << "macro: " << string(X86_CODE32) << endl;
  uc_engine *uc;
  uc_err err;

  int r_ebx = 1;
  int r_ecx = 1; // ECX register
  int r_edx = 1; // EDX register
  int r_eax = 0;

  int val = 50;
  open();
  // Initialize emulator in X86-32bit mode
  err = uc_open(UC_ARCH_X86, UC_MODE_32, &uc);

  if (err != UC_ERR_OK)
  {
    printf("Failed on uc_open() with error returned: %u\n", err);
    return 0;
  }

  map();

  // map 2MB memory for this emulation
  uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);

  writeMachineCode();
  // write machine code to be emulated to memory
  if (uc_mem_write(uc, ADDRESS, X86_CODE32, size))
  {
    printf("Failed to write emulation code to memory, quit!\n");
    return 0;
  }

  writeRegs();
  // initialize machine registers
  uc_reg_write(uc, UC_X86_REG_ECX, &r_ecx);
  uc_reg_write(uc, UC_X86_REG_EDX, &r_edx);
  uc_reg_write(uc, UC_X86_REG_EBX, &r_ebx);
  uc_reg_write(uc, UC_X86_REG_EAX, &r_eax);

  std::cout << "Initial values: " << endl;
  readRegs(); // initial values stored in regs
              // print out registers (initial state)
  uc_reg_read(uc, UC_X86_REG_ECX, &r_ecx);
  uc_reg_read(uc, UC_X86_REG_EDX, &r_edx);
  uc_reg_read(uc, UC_X86_REG_EBX, &r_ebx);
  uc_reg_read(uc, UC_X86_REG_EAX, &r_eax);

  printf(">>> ECX = %d\n", r_ecx);
  printf(">>> EDX = %d\n", r_edx);
  printf(">>> EBX = %d\n", r_ebx);
  printf(">>> EAX = %d\n", r_eax);
  emulate();
  // emulate code in infinite time & unlimited instructions
  err = uc_emu_start(uc, ADDRESS, ADDRESS + size, 0, 0);
  if (err)
  {
    printf("Failed on uc_emu_start() with error returned %u: %s\n",
           err, uc_strerror(err));
  }
  // now print out some registers
  printf("Emulation done. Below is the CPU context\n");
  readRegs();
  uc_reg_read(uc, UC_X86_REG_ECX, &r_ecx);
  uc_reg_read(uc, UC_X86_REG_EDX, &r_edx);
  uc_reg_read(uc, UC_X86_REG_EBX, &r_ebx);
  uc_reg_read(uc, UC_X86_REG_EAX, &r_eax);

  printf(">>> ECX = %d\n", r_ecx);
  printf(">>> EDX = %d\n", r_edx);
  printf(">>> EBX = %d\n", r_ebx);
  printf(">>> EAX = %d\n", r_eax);
  uc_close(uc);
  return 0;
}