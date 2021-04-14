include_directories("../../libparsing/src/h")

add_executable(GrammarSpike "GrammarSpike.cpp" "GrammarSpike.h" "../../libparsing/test/c-parser-expr.c" "../../libparsing/src/c/gc.c" "../../libparsing/src/c/parsing.c" "../../libparsing/src/h/testing.h" "../../libparsing/src/h/parsing.h" "../../libparsing/src/h/gc.h" "../../libparsing/src/h/oo.h")