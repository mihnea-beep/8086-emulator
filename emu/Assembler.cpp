#include "Assembler.h"

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

// void Assembler::load()
// {
//     cout << "load";
// }
void Assembler::test()
{
    cout << "asd";
}
void Assembler::load(string src)
{
    cout << "\nLOAD\n";
    // read from the machine code source file
    cout << "Reading assembly code from asm_code.asm ...\n";
    // string src = "asm_code.asm";
    ifstream src_file(src);
    string line;
    getline(src_file, line);
    cout << "Code: " << line << endl;

    CODE = (char *)line.c_str();
    // cout << (char *)line.c_str() << endl;
    cout << "Storing assembly code \n";
    // cout << ".., " << (const char *)CODE << "..." << endl;
    src_file.close();

    // cout << ".., " << (const char *)CODE << "..." << endl;
    machine_code_string = (const char *)CODE;
    // cout << "^^^" << machine_code_string << "^^^" << endl;
    machine_code_string = line;
}

const char *Assembler::get_code()
{
    return machine_code_string.c_str();
}

string Assembler::getCode()
{
    cout << "asm ... " << machine_code_string.c_str() << " asm ..." << endl;
    return machine_code_string;
}

void Assembler::close()
{
    // close Keystone instance when done
    ks_close(ks);
}

int Assembler::open()
{
    cout << "\nOPEN\n";
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

    const char *assembly_code = machine_code_string.c_str();
    // cout << ".., " << (const char *)CODE << "..." << endl;
    // cout << ",,," << machine_code_string << ",,," << endl;
    if (ks_asm(ks, assembly_code, 0, &encode, &size, &stat_count) != KS_ERR_OK)
    {
        printf("ERROR: ks_asm() failed & stat_count = %lu, error = %u\n",
               stat_count, ks_errno(ks));
    }
    else
    {
        size_t i;

        printf("%s = ", assembly_code);
        ofstream outfile;
        outfile.open("emu_data/junk.dat");

        for (i = 0; i < size; i++)
        {
            outfile << encode[i];

            printf("%02x ", encode[i]);
            machine_code_stream << "\\" << 'x' << hex << setw(2) << setfill('0') << (int)(encode[i]);
            machine_code_string = machine_code_string + "\\x" + to_string(encode[i]);
        }
        cout << "\n ENCODE: \n"
             << encode;
        outfile.close();
        printf("\n");
        printf("Compiled: %lu bytes, statements: %lu\n", size, stat_count);
        printf(". . . \n");
    }
    machine_code_string = machine_code_stream.str();
    for (int i = 0; i < size; i++)
    {
        machine_code_string[i] = machine_code_stream.str()[i];
    }
}

unsigned char *Assembler::get_encode()
{
    return encode;
}

string Assembler::assemble()
{
    // open();
    // load();
    cout << "\nCOMPILE\n";
    compile();
    cout << "Machine code (keystone format): " << machine_code_stream.str() << "\n";
    // cout << "13123213" << (const char *)CODE << "12312312";
    // TODO: add clean format
    return machine_code_stream.str();
}

void Assembler::store(string dst_file_name) // store machine code and size
{
    // TODO: error handling/return bool
    ofstream dst_file(dst_file_name);
    dst_file << assemble() << endl;
    cout << "\nSTORE\n";
    dst_file.close();
    ofstream meta_file("emu_data/metadata.txt");
    meta_file << size;
    meta_file.close();

    // generate CPU header
    // ofstream header("machine_code.h");
    // header << "const char *X86_CODE32 = "
    //        << "\"" << machine_code_stream.str() << "\""
    //        << ";";
}
