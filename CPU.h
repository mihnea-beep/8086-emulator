#pragma once
#include <iostream>
#include <unicorn/unicorn.h>
using namespace std;

class CPU
{
private:
    const int ADDRESS = 0x1000000;
    int size;
    uc_engine *uc;
    uc_err err;

    // registers
    int r_ebx = 1; // EBX
    int r_ecx = 1; // ECX
    int r_edx = 1; // EDX 
    int r_eax = 0; // EAX

public:
    CPU();
    bool open();
    void map();
    bool write();
    void wx_regs();
    void rx_regs();
    void set_data();
    void emulate();
    void close();

    ~CPU();
};
