- Changed name of `µnit\munit.c` to `.cpp` so `repl.it` would build
- Edited `µnit\munit.cpp` to eliminate `C++` errors
    - see 'djg'
- Changed name of `µnit\example.c` to `.cpp` so `repl.it` would build
    - see 'djg'
- numerous structural and naming changes to enable VS Code support
	- µnit ➡️ munit
	- **HACK**: `main()` *files* renamed to avoid object file name clashes - weak solution


# Tokenizer:

## Article Example:
 ```c++
class token {
private:
	using token_value = std::variant<reserved_token, identifier, double, std::string, eof>;
	token_value _value;
	size_t _line_number;
	size_t _char_index;
public:
	token(token_value value, size_t line_number, size_t char_index);

	bool is_reserved_token() const;
	bool is_identifier() const;
	bool is_number() const;
	bool is_string() const;
	bool is_eof() const;

	reserved_token get_reserved_token() const;
	std::string_view get_identifier() const;
	double get_number() const;
	std::string_view get_string() const;
	
	size_t get_line_number() const;
	size_t get_char_index() const;
};
```

## New Token Class:
```c++
#include <stdint.h>

typedef uint16_t number_t;
typedef std::string symbol_t;
typedef struct eof{ } eof_t;

class token {
private:
	using token_value = std::variant<number_t, symbol_t, eof_t>;
	token_value _value;
	size_t _line_number;
	size_t _char_index;
public:
	token(token_value value, size_t line_number, size_t char_index);

	bool is_number() const;
	bool is_symbol() const;
	bool is_eof() const;

  operator number_t() const;
  operator symbol_t() const;

	number_t get_number() const;
	symbol_t get_symbol() const;
  
	size_t get_line_number() const;
	size_t get_char_index() const;
};
```

##  Article Tokenize Function:
```c++
token tokenize(push_back_stream& stream) {
  while (true) {
    size_t line_number = stream.line_number();
    size_t char_index = stream.char_index();
    int c = stream();
    switch (get_character_type(c)) {
      case character_type::eof:
        return {eof(), line_number, char_index};
      case character_type::space:
        continue;
      case character_type::alphanum:
        stream.push_back(c);
        return fetch_word(stream);
      case character_type::punct:
        switch (c) {
          case '"':
            return fetch_string(stream);
          case '/':
          {
            char c1 = stream();
            switch(c1) {
            case '/':
                skip_line_comment(stream);
                continue;
              case '*':
                skip_block_comment(stream);
                continue;
              default:
                stream.push_back(c1);
            }
          }
          default:
            stream.push_back(c);
            return fetch_operator(stream);
        }char
        break;
    }
  }
}
```

## New Tokenize Function:
```c++
token tokenize(push_back_stream& stream){
	while(true){
		size_t line_number = stream.line_number();
	    size_t char_index = stream.char_index();
		int currentChar = stream();
		/*
		switch(get_char_type(currentChar)){
			case character_type::eof:
				return {oef(), line_number, char_index};	
			case character_type::space:
				continue;
			case c == "/" and NEXTCHAR == "/": not sure NEXTCHAR is needed
				skipComment();
			case c == "p":
				switch(NEXTCHAR):
					case NEXTCHAR == "o":
						Its pop
					case NEXTCHAR == "u":
						Its push	
		}
		*/
	}
}
```