#include "CPU.h"
#include <fstream>
#include "machine_code.h"

CPU::CPU(/* args */)
{
}

CPU::~CPU()
{
}

bool CPU::open()
{
    err = uc_open(UC_ARCH_X86, UC_MODE_32, &uc);

    if (err != UC_ERR_OK)
    {
        cout << "Failed on uc_open() --- error: " << err << "\n";
        return false;
    }
    cout << "CPU: ON\n";
    return true;
}

void CPU::map()
{
    // map 2MB memory for this emulation
    uc_mem_map(uc, ADDRESS, 2 * 1024 * 1024, UC_PROT_ALL);
}

bool CPU::write()
{
    // write machine code to be emulated to memory
    if (uc_mem_write(uc, ADDRESS, X86_CODE32, size))
    {
        printf("Failed to write emulation code to memory, quit!\n");
        return 0;
    }
    cout << "Machine code written to memory\n";
    return 1;
}

void CPU::set_data()
{
    ifstream metadata_file("metadata.txt");
    string size_data;
    getline(metadata_file, size_data);
    size = stoi(size_data);
}

void CPU::wx_regs()
{
    uc_reg_write(uc, UC_X86_REG_ECX, &r_ecx);
    uc_reg_write(uc, UC_X86_REG_EDX, &r_edx);
    uc_reg_write(uc, UC_X86_REG_EBX, &r_ebx);
    uc_reg_write(uc, UC_X86_REG_EAX, &r_eax);

    cout << "Registers initialized.\n";
}

void CPU::rx_regs()
{
    
    uc_reg_read(uc, UC_X86_REG_ECX, &r_ecx);
    uc_reg_read(uc, UC_X86_REG_EDX, &r_edx);
    uc_reg_read(uc, UC_X86_REG_EBX, &r_ebx);
    uc_reg_read(uc, UC_X86_REG_EAX, &r_eax);

    cout << "Values read from register:\n";

    printf(">>> ECX = %d\n", r_ecx);
    printf(">>> EDX = %d\n", r_edx);
    printf(">>> EBX = %d\n", r_ebx);
    printf(">>> EAX = %d\n", r_eax);
}

void CPU::emulate()
{
    err = uc_emu_start(uc, ADDRESS, ADDRESS + size, 0, 0);
    if (err)
    {
        printf("Failed on uc_emu_start() with error returned %u: %s\n",
               err, uc_strerror(err));
    }
}

void CPU::close()
{
  printf("Emulation done. Below is the CPU context\n");
  rx_regs();
  uc_close(uc);
  printf("CPU: OFF\n");
}