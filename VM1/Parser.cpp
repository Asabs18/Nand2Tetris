#include "Parser.h"

Parser::Parser(std::string filename)
{
}

Parser::Parser() {
}

bool Parser::parse()
{
	return false;
}

RETURN::RETURN() {
}

RETURN* RETURN::createReturn(std::string line)
{
	return new RETURN();
}

bool RETURN::parse()
{
	return false;
}

int main() {
	RETURN* ret = RETURN::createReturn("Hello");
	ret->parse();
}