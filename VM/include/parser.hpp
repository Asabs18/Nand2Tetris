#pragma once
#include "lookup.hpp"
#include "token.hpp"
#include <string>
#include <istream>

struct instruction_t {
    std::string instruction;
    virtual ~instruction_t() = default;
};

class parser_t {
#if defined( _UT_) 
    public:
#else
    private:
#endif // (_UT_)
        using parser_value = std::variant<instruction_t, eof_t>;
        parser_value _value;
        size_t _line_number;
        size_t _char_index;

    public: //HACK: DELETE THIS LINE, TOKENIZER ONLY PUBLIC FOR TESTING PURPOSES
        class tokenizer_t {
            public:
                tokenizer_t(std::istream& stream) : _stream(stream) {};
                token_t* tokenize();

            private:
                std::istream& _stream;
                std::string readNextWord(std::stringstream& file);
        };

        tokenizer_t* _tokenizer;

    public:
        parser_t(std::string file_name) {};
        parser_t(std::ifstream file_stream);
        // parser_t(std::stringstream& string_stream){ //TODO: Fix constructors for correct types
        //     std::istream& temp(string_stream);
        //     _tokenizer = new tokenizer_t(std::istream&{string_stream});
        // }

// [function with an istream& parameter C++ - Stack Overflow](https://stackoverflow.com/questions/21492119/function-with-an-istream-parameter-c)

// [c++ - Is it possible to pass a stringstream as a function parameter? - Stack Overflow](https://stackoverflow.com/questions/10833188/is-it-possible-to-pass-a-stringstream-as-a-function-parameter)
// [c++ - How to assign istringstream and ifstream to an istream variable? - Stack Overflow](https://stackoverflow.com/questions/38798133/how-to-assign-istringstream-and-ifstream-to-an-istream-variable)


        //The Big 5:
        parser_t() = delete;
        parser_t(const parser_t&) = delete;
        parser_t& operator=(const parser_t&) = delete;
        parser_t(parser_t&&) = delete;
        parser_t& operator=(parser_t&&) = delete;
        virtual ~parser_t() = default;
        
        instruction_t* parse(std::vector<token_t*> token);
};

struct memory_segment_t
{
    // const stork::lookup<std::string_view,  terminals_t> reserved_memory_segment_terminal_map {
    std::string memory_segment;
};

struct memory_segment_index_t : number_t {
    // int index;
};
 
// AL instructions
struct al_instruction_t : instruction_t {
};

// MA instructions
struct ma_instruction_t : public instruction_t {
    memory_segment_t memory_segment;
    memory_segment_index_t index;
};

// BC instructions 
struct br_instruction_t : instruction_t {
    label_t label;
};

// FC instructions
struct fn_instruction_t : instruction_t {
    function_name_t name;
    number_t number;    // locals or arguments;
};