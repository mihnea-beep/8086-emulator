#include "Assembler.h"
#include "instructions.h"

Assembler::Assembler(/* args */)
{
}

Assembler::~Assembler()
{
}

void Assembler::free()
{
    // NOTE: free encode after usage to avoid leaking memory
    ks_free(encode);
}

void Assembler::close()
{
    // close Keystone instance when done
    ks_close(ks);
}

int Assembler::open()
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

void Assembler::compile()
{
    assembly_code = CODE;
    if (ks_asm(ks, assembly_code, 0, &encode, &size, &stat_count) != KS_ERR_OK)
    {
        printf("ERROR: ks_asm() failed & stat_count = %lu, error = %u\n",
               stat_count, ks_errno(ks));
    }
    else
    {
        size_t i;

        printf("%s = ", assembly_code);
        for (i = 0; i < size; i++)
        {
            printf("%02x ", encode[i]);

            machine_code_stream << "\\" << 'x' << hex << setw(2) << setfill('0') << (int)(encode[i]);
            machine_code_string = machine_code_string + "\\x" + to_string(encode[i]);
        }
        printf("\n");
        printf("Compiled: %lu bytes, statements: %lu\n", size, stat_count);
        printf(". . . \n");
    }
}

string Assembler::assemble()
{
    open();
    compile();
    cout << "Machine code (keystone format): " << machine_code_stream.str() << "\n";
    // TODO: add clean format
    return machine_code_stream.str();
}

void Assembler::store(string dst_file_name) // store machine code and size
{ 
    // TODO: error handling/return bool
    ofstream dst_file(dst_file_name);
    dst_file << "const char* X86_CODE32 = \"" << assemble() << "\";";
    dst_file.close();
    ofstream meta_file("metadata.txt");
    meta_file << size;
}
