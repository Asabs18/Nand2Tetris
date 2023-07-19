#include <cassert>
#include "include/parser.hpp"

// `main()` driver program:
//  _VM_:   call VM's main()
//  _UT_:   call VM's µnit main()
//  _MU_:   call µnit/example.cpp: main()
//
//
// Main entry points:
//  VM to ASM translator UTs
int main_vm_ut(int argc, char* argv[]);
//  VM to ASM translator
int main_vm(int argc, char* argv[]);
//  µnit example 
int main_munit_example(int argc, char* argv[]); 

int main(int argc, char* argv[]) {
#if defined( _UT_) 
    return main_vm_ut(argc, argv); 
#elif defined(_VM_)
    return main_vm(argc, argv);
#elif defined(_MU_)
    return main_munit_example(argc, argv);
#else
    #pragma message("***\n*** Undefined main()\n***\n")
    assert(false);
#endif // _UT_
}