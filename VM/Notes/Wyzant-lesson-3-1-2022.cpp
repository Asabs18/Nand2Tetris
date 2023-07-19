// // character streams
// ifstream input("foo.hack");
// istringstream ss("push local 5");

// parser_t parser("foo.hack");
// parser_t parser1(input);
// parser_t parser2(ss);

// parser::parser(ifstream input) {
//   m_tokenizer = new tokenizer(input);
// }
// // iterator or advance()
// // instuction streams
// instruction_t parser::parse() {
//   // token streams
//   op_code_token = m_tokenizer.tokenize();
//   switch(op_code_token.type) {
//     case add:
//       // tokenize remainder of line - should be empty
//       return add_instruction_t{op_code_token};
//     case call:
//     case memory access:
//       ms_token = m_tokenize();
//       if(ms_token.type != MEMORY_SEGMENT) {
//       	// error
//       } else {
//         // look for what's next, in this case a number
//       }
//       return memory_access_instruction{ op_code_token, ms_token, number_token}
//     default:
//   }
// }

// parser_t parser("foo.hack");
// ofstream output("foo.asm");
// instruction_t instr;
// while((instr = parser.parse()) != EOF) {
// 	instr.code_gen(output);
// }
