// References
//  [Creating a Small-footprint Programming Language in C++ | Toptal](https://www.toptal.com/c-plus-plus/creating-programming-language-in-c-)
// 
#include <cassert>
#include <cstdlib>
#include <iostream>

#include "../include/parser.hpp"
#include "../include/token.hpp"

int main_vm(int argc, char* argv[]) {
    // [Range-based for loop (since C++11) - cppreference.com](https://en.cppreference.com/w/cpp/language/range-for)
    for (const auto& reserved_instruction_terminal : reserved_instruction_terminal_map) {
        std::cout << reserved_instruction_terminal.first << std::endl;
    }
    std::cout << "---" << std::endl;
    // for (const auto& reserved_memory_segment_terminal : memory_segment_t::reserved_memory_segment_terminal_map) {
    //     std::cout << reserved_memory_segment_terminal.first << std::endl;
    // }
    return EXIT_SUCCESS;
}