#include <cassert>
#include <cstdint>
#include <fstream>
#include <iostream>
#include "../include/token.hpp"
#include "../include/parser.hpp"

// HACK: Not sure what do here given (a) x-macroed tokens, and, (b) design of symbol table
#define TOKEN(prefix, token)        \
    { #token, tokens_t::prefix##_##token }
//
const stork::lookup<std::string_view, tokens_t> reserved_instruction_terminal_map {
    // Arithmetic / Logic Commands: al_*
    TOKEN(al, add),
    TOKEN(al, sub),
    TOKEN(al, neg),
    TOKEN(al, eq),
    TOKEN(al, get),
    TOKEN(al, lt),
    TOKEN(al, and),
    TOKEN(al, or),
    TOKEN(al, not),
    // Memory access commands: ma_*
    TOKEN(ma, pop),
    TOKEN(ma, push),
    // Branching commands: bc_*
    TOKEN(bc, label),
    TOKEN(bc, goto),
    TOKEN(bc, if_goto),    // if-goto
    // Function commands: fc_*
    TOKEN(fc, function),
    TOKEN(fc, call),
    TOKEN(fc, return)
};

// enum wordType { eof, space, alpha, num, punct };
// terminals_t parser_t::tokenizer_t::tokenize(){
//     int length = 0; //TBD
//     char* buffer = new char [length];
//     while(true){
//       char character = stream.read(buffer, 1);
//       switch(getCharType(character)){
//         case eof:
//           return {eof(), lineNum, charIndex}
//         case space:
//           continue;
//         case alphanum:
//           stream.putback(character);
//           return fetchToken(fetchFullString()); //make member function so you dont have to pass in stream
//         case num:
//           stream.putback(character);
//           return fetchToken(fetchFullNumber()); 
//         case punct:
//           switch(character) {
//             case '/':
//               if(stream.peek() == '/'){
//                 stream.putback(character);
//                 skipComment();
//               }
//             default:
//               return "error" //change to throw and exception or raise error
//           }
//         default:
//           stream.putback(character);
//           return "error" //change to throw and exception or raise error
//       }
//     }
//     return terminals_t::fc_return;


// enum wordType { eof, space, alpha, num, punct };
// terminals_t parser_t::tokenizer_t::tokenize(){
//     int length = 0; //TBD
//     char* buffer = new char [length];
//     while(true){
//       char character = stream.read(buffer, 1);
//       switch(getCharType(character)){
//         case eof:
//           return {eof(), lineNum, charIndex}
//         case space:
//           continue;
//         case alphanum:
//           stream.putback(character);
//           return fetchToken(fetchFullString()); //make member function so you dont have to pass in stream
//         case num:
//           stream.putback(character);
//           return fetchToken(fetchFullNumber()); 
//         case punct:
//           switch(character) {
//             case '/':
//               if(stream.peek() == '/'){
//                 stream.putback(character);
//                 skipComment();
//               }
//             default:
//               return "error" //change to thorw and exception or raise error
//           }
//         default:
//           stream.putback(character);
//           return "error" //change to thorw and exception or raise error
//       }
//     }
//     return terminals_t::fc_return;
//}
