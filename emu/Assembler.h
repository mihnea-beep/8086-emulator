#pragma once
#include <iostream>
#include <sstream>
#include <keystone/keystone.h>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <string>
using namespace std;

class Assembler
{
private:
    size_t size;
    ks_engine *ks;
    ks_err err_ks;
    size_t stat_count;
    char* CODE; // "INC ecx; INC ecx; INC ecx; DEC edx; DEC edx; MOV eax, 300; ADD ecx, eax;";
    unsigned char *encode;

    stringstream machine_code_stream;
    string machine_code_string;
    //char* assembly_code;
public:

    Assembler(/* args */);
    void load();
    void load(string);
    const char* get_code();
    int open();
    void compile();
    string assemble();
    void store(string);
    void free();
    void close();
    unsigned char* get_encode();
    ~Assembler();
    string getCode();
    void test();

};

