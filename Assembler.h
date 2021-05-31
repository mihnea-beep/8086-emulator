#pragma once
#include <iostream>
#include <sstream>
#include <keystone/keystone.h>
#include <sstream>
#include <iomanip>
#include <fstream>
using namespace std;

class Assembler
{
private:
    size_t size;
    ks_engine *ks;
    ks_err err_ks;
    size_t stat_count;
    unsigned char *encode;

    stringstream machine_code_stream;
    string machine_code_string;
    const char* assembly_code;
public:
    Assembler(/* args */);
    int open();
    void compile();
    string assemble();
    void store(string);
    void free();
    void close();
    ~Assembler();
};

