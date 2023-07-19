#pragma once
#include <string>
#include <variant>
#include "lookup.hpp"
// #include "parser.hpp"
// [chapter 7 lecture.pdf - Google Drive](https://drive.google.com/file/d/19fe1PeGnggDHymu4LlVY08KmDdhMVRpm/view)
// Memory Segments:
//     - Slide 63
// Arithmetic / Logical commands
// Memory access commands
// Branching commands
// Function commands
//     - Slide 82
// Other Terminal Symbols:
//  - number (number_t)
//  - symbol (symbol_t)
//  - null (pseudo-token)
//      - used as a sentinel (list/array terminator)

#define MS_TOKENS_TABLE(TOKEN)              \
    TOKEN(ms, local, local)                 \
    TOKEN(ms, argument, argument)           \
    TOKEN(ms, this, this)                   \
    TOKEN(ms, that, that)                   \
    TOKEN(ms, constant, constant)           \
    TOKEN(ms, static, static)               \
    TOKEN(ms, pointer, pointer)             \
    TOKEN(ms, temp, temp)

#define AL_TOKENS_TABLE(TOKEN)              \
    TOKEN(al, add, add)                     \
    TOKEN(al, sub, sub)                     \
    TOKEN(al, neg, neg)                     \
    TOKEN(al, eq, eq)                       \
    TOKEN(al, get, get)                     \
    TOKEN(al, lt, lt)                       \
    TOKEN(al, and, and)                     \
    TOKEN(al, or, or )                      \
    TOKEN(al, not, not)

#define MA_TOKENS_TABLE(TOKEN)              \
    TOKEN(ma, pop, pop)                     \
    TOKEN(ma, push, push)

#define BC_TOKENS_TABLE(TOKEN)              \
    TOKEN(bc, label, label)                 \
    TOKEN(bc, goto, goto)                   \
    TOKEN(bc, if_goto, if-goto)

#define FC_TOKENS_TABLE(TOKEN)              \
    TOKEN(fc, function, function)           \
    TOKEN(fc, call, call)                   \
    TOKEN(fc, return, return)

#define TS_TOKENS_TABLE(TOKEN)              \
    TOKEN(ts, number, "D")                  \
    TOKEN(ts, symbol, "regex")              \
    TOKEN(ts, null, NULL )

#define TOKENS_TABLE(TOKEN)                 \
    MS_TOKENS_TABLE(TOKEN)                  \
    AL_TOKENS_TABLE(TOKEN)                  \
    MA_TOKENS_TABLE(TOKEN)                  \
    BC_TOKENS_TABLE(TOKEN)                  \
    FC_TOKENS_TABLE(TOKEN)                  \
    TS_TOKENS_TABLE(TOKEN)

#define DEFINE_ENUM(category, token, pattern)       \
    category##_##token,

enum class tokens_t {
    TOKENS_TABLE(DEFINE_ENUM)
};
static_assert(sizeof(unsigned char) == 1);
#define EXPAND_AS_STRUCT(a,b,c) unsigned char a##_##b;
typedef struct{
    TOKENS_TABLE(EXPAND_AS_STRUCT)
} _tokens_t_size_struct_t;
#define NUM_TOKENS_T    sizeof(_tokens_t_size_struct_t)

extern const stork::lookup<std::string_view, tokens_t> reserved_instruction_terminal_map;
// extern const memory_segment_t::stork::lookup<std::string_view, tokens_t> reserved_memory_segment_terminal_map;
// namespace VM {
struct memory_t {
     uint16_t   value;
};
// namespace VM {
// token types
struct number_t : memory_t {
};
// Book: 6.2.1 Syntax Conventions and File Formats
//  "Constants and Symbols Constants must be non-negative and are written in decimal notation. A user-
//  defined symbol can be any sequence of letters, digits, underscore (_), dot (.), dollar sign ($), and colon (:)
//  that does not begin with a digit."
struct symbol_t : std::string {
};

// Book: 8.2.1 Program Flow Commands
//  "Only labeled locations can be jumped to from other parts of the program. The scope of the label is the
//  function in which it is defined. The label is an arbitrary string composed of any sequence of letters, digits,
//  underscore (_), dot (.), and colon (:) that does not begin with a digit."
struct label_t : symbol_t {
};

// Book: 8.2.2 Function Calling Commands
//  "A function has a symbolic name that is used globally to call it. The function name is an arbitrary string
//  composed of any sequence of letters, digits, underscore (_), dot (.), and colon (:) that does not begin with
//  a digit. (We expect that a method bar in class Foo in some high-level language will be translated by the
//  compiler to a VM function named Foo.bar). The scope of the function name is global: All functions in all
//  files are seen by each other and may call each other using the function name."
struct function_name_t : symbol_t {
};

struct eof_t {
};

class token_t {
    private:
        using token_value = std::variant<tokens_t, number_t, label_t, function_name_t, eof_t>;
        token_value _value;

    public:
        token_t(token_value value)
            : _value(value) {};
    
        bool is_token() const { return std::holds_alternative<tokens_t>(_value); };
        bool is_number() const { return std::holds_alternative<number_t>(_value); };
        bool is_label() const { return std::holds_alternative<label_t>(_value); };
    
        operator tokens_t() const { return std::get<tokens_t>(_value); };
        operator number_t() const { return std::get<number_t>(_value); };
        operator std::string() const { return std::get<label_t>(_value); };
    
        const tokens_t* get_token() const { return is_token() ? std::get_if<tokens_t>(&_value) : nullptr; };
        const number_t* get_number() const { return is_number() ? std::get_if<number_t>(&_value) : nullptr; };
        const std::string* get_label() const { return is_label() ? std::get_if<label_t>(&_value) : nullptr; };
};