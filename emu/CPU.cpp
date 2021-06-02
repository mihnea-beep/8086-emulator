#include "CPU.h"
#include <fstream>
#include "machine_code.h"
#include <vector>
#include "Assembler.h"
using namespace std;

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
    rx_EIP();

    // 

    ifstream src_file("emu_data/machine_code.txt");
    string line;
    getline(src_file, line);
    cout << "Code: " << line << endl;
    cout << "Code2: " << line.c_str() << endl;
    // printf("C1: %s\n", line);
    printf("C2: %s\n", line.c_str());

    const char* machine_code; //X86_CODE32; //line.c_str();
    // string a = "INC ecx;";
    // string b = " INC ecx;";
    // string c = a + b;
    const char* x = line.c_str();
    // cout << "x content: " << x;
    // printf("Continut x: %s\n", x);

    // ---- test binary write
    ifstream infile;
    infile.open("emu_data/junk.dat");
    // getline(infile, line);
    // for(int i = 0; i < size; i++){
    //     infile >> c[i];
    
    char in[size + 1];

for(int i = 0; i < size + 1; i++){
    infile >> in[i];

    cout << "\n\nREAD: " << (int)in[i] << "\n\n";
    cout << "SIZE: " << size;
}
    // for(int i = 0; i < 1; i++){
    //     infile >> in[i];
    //     char brk[1];
    //     infile >> brk[0];
    //     cout << in[i] << "-";
    // }


    // write machine code to be emulated to memory
    if (uc_mem_write(uc, ADDRESS, in, size))
    {
        printf("Failed to write emulation code to memory, quit!\n");
        return 0;
    }
    cout << "Machine code written to memory\n";
    rx_EIP();
    return 1;
}

void CPU::set_data()
{
    ifstream metadata_file("emu_data/metadata.txt");
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

void CPU::rx_EIP()
{
    uc_reg_read(uc, UC_X86_REG_EIP, &r_eip);
    printf(">>> EIP = %d\n", r_eip);
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
    cout << "ADR: " << ADDRESS << endl;
    cout << "EIP: " << r_eip << endl;
    rx_EIP();
    // err = uc_emu_start(uc, ADDRESS, ADDRESS + size, 0, 1);
    // if (err)
    // {
    //     printf("Failed on uc_emu_start() with error returned %u: %s\n",
    //            err, uc_strerror(err));
    // }
    // rx_EIP();
    // cout << "ADR: " << ADDRESS << endl;

    // err = uc_emu_start(uc, ADDRESS + 1, ADDRESS + size, 0, 1);
    // if (err)
    // {
    //     printf("Failed on uc_emu_start() with error returned %u: %s\n",
    //            err, uc_strerror(err));
    // }
    // rx_EIP();
    err = UC_ERR_OK;
    err = uc_emu_start(uc, ADDRESS, ADDRESS + size, 0, 1);
    rx_EIP();
    rx_regs();
    int oldIP = 0;
    while (r_eip != ADDRESS + size)
   {
        oldIP = r_eip;
        string x;
        // cout << "Press any key to advance ...";
        // cin >> x;
        cout << " ----- " << endl;
        err = uc_emu_start(uc, ADDRESS + (r_eip - ADDRESS), ADDRESS + size, 0, 1);
        rx_EIP();
        rx_regs();
    }
}

void CPU::close()
{
    printf("Emulation done. Below is the CPU context\n");
    rx_regs();
    uc_close(uc);
    reset_regs();
    printf("CPU: OFF\n");
}

void CPU::reset_regs()
{
    printf("Resetting registers\n");
    r_ebx = 1;
    r_ecx = 1;
    r_edx = 1;
    r_eax = 0;
    r_eip = 0;
}

int CPU::get_eax(){
    return r_eax;
}