#include "../include/parser.hpp"
#include <string>
#include <iostream> 
#include <fstream>   
#include <vector>
#include <sstream>
#include <algorithm>
#include <cassert>

//TODO: Handle Comments

#define TOKEN(prefix, token)        \
    { #token, tokens_t::prefix##_##token }

// instruction_t* parser_t::parse(std::vector<token_t*> token){
//     switch(token){
//         case 
//     }

//     return nullptr;
// }


//======================= Tokenizer =========================

//TODO: Change helper functions to use token map instead of .compare calls
bool isValidTokenMA(std::string word){
    bool isValidToken = false;
    if(word.compare("push") == 0 || word.compare("pop") == 0){
        isValidToken = true;
    }
    return isValidToken;
}


bool isValidTokenAL(std::string word){
    bool isValidToken = false;
    if( word.compare("add") == 0 || word.compare("sub") ==  0 || word.compare("neg") == 0 ||
        word.compare("eq")  == 0 || word.compare("gt")  ==  0 || word.compare("lt")  == 0 ||
        word.compare("and") == 0 || word.compare("or")  ==  0 || word.compare("not") == 0){
        isValidToken = true;
    }
    return isValidToken;
}


bool isValidTokenBR(std::string word){
    bool isValidToken = false;
    if(word.compare("label") == 0 || word.compare("goto") == 0 || word.compare("if-goto") == 0){
        isValidToken = true;
    }
    return isValidToken;
}


bool isValidTokenFN(std::string word){
    bool isValidToken = false;
    if(word.compare("function") == 0 || word.compare("call") == 0 || word.compare("return") == 0){
        isValidToken = true;
    }
    return isValidToken;
}


bool isValidToken(std::string word){
    bool isValidToken = false;
    if(isValidTokenMA(word) || isValidTokenAL(word) || isValidTokenBR(word) || isValidTokenFN(word)){ // Check each helper function for valid next word
        isValidToken = true;
    }
    return isValidToken;
}


bool isNumber(const std::string& str){
    for (char const &c : str) {
        if (std::isdigit(c) == 0) return false; //Return false if any part of the string isn't a digit
    }
    return true;
}


bool isFnName(std::string word, std::string lastWord){
    bool isFnName = false;
    if(lastWord.compare("function") == 0){
        isFnName = true;
    }
    return isFnName;
}


bool isSpace(unsigned char c){ //Checks for whitespace (Can use isspace from standard but may need isSpace for word.erase(see ln 125)) 
	return (c == ' ' || c == '\n' || c == '\r' ||
		c == '\t' || c == '\v' || c == '\f');
}


std::string parser_t::tokenizer_t::readNextWord(std::stringstream& file){
    // std::vector<char> wordVector;
    // char c;
    
    // while (file.get(c)){ //Read from the stringstream one letter at a time
    //     if(isSpace(c) == false){ //Add each letter to the word if it is not a whitespace character
    //         wordVector[wordVector.size()] = c;
    //         wordVector.resize(wordVector.size() + 1);
    //     }
    //     else{ //Stop adding to wordVector if a whitespace character is found
    //         std::string wordString(wordVector.begin(), wordVector.end());
    //         return wordString; 
    //     }
    // }
    return "NOT WORKING";
}


std::string readLastWord(std::stringstream& file){ //TODO: Fix readLastWord
    std::string lastWord;
    // if (nameVector.size() > 0){
    //     lastWord = nameVector[nameVector.size() - 1];
    // }
    return lastWord; 
}


token_t* parser_t::tokenizer_t::tokenize(){
    std::stringstream file("push pop sub add function fn sub 10 15");
    std::string word = readNextWord(file);
    word.erase(std::remove_if(word.begin(), word.end(), isSpace), word.end()); //Remove any whitespace characters from word
    token_t* returnToken = nullptr;

    auto it = reserved_instruction_terminal_map.find(word); 
    if (it != reserved_instruction_terminal_map.end()){ //Check if token map returns a valid token
        if(isValidToken(word)){
            returnToken = new token_t(it->second);
        }
        else if(isNumber(word) == false){
            if(isFnName(word, readLastWord(file))){ //HACK: readLastWord currently not working
                returnToken = new token_t(function_name_t{word});
            }
            else{
                returnToken = new token_t(label_t{word});
            }
        }
        else{
            returnToken = new token_t(number_t{static_cast<uint16_t>(std::atoi(word.c_str()))});
        }
        
        std::cout << "Token Added: " + word + "\n";
    }
    else{
        throw "Invalid Token";
    }
    return returnToken;
}


// const stork::lookup<std::string_view,  tokens_t> memory_segment_t::reserved_memory_segment_terminal_map {
// // Memory Segments: ms_*
//     TOKEN(ms, local),
//     TOKEN(ms, argument),
//     TOKEN(ms, this),
//     TOKEN(ms, that),
//     TOKEN(ms, constant),
//     TOKEN(ms, static),
//     TOKEN(ms, pointer),
//     TOKEN(ms, temp),
// };