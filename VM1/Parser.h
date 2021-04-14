#pragma once
#include <string>

enum MemSegment {};
enum operations {};
typedef unsigned int MemIndex;

class Parser {
public:
	Parser(std::string filename);
	~Parser();
	virtual bool parse() = 0;
	Parser* advance();
protected:
	std::string getLine() { return m_line; };
	Parser();
private:
	std::string m_line;
};

class ARITHMETIC : Parser {
public:
	static ARITHMETIC* createArithmetic(std::string line);
	bool parse() override;
	operations getOperation();
private:
	operations m_operation;
};

class PUSH : Parser {
public:
	static PUSH* createPush(std::string line);
	bool parse() override;
	MemSegment getMemSegment();
	MemIndex getMemIndex();
private:
	MemSegment m_memSegment;
	MemIndex m_memIndex;
};

class POP : Parser {
public:
	static POP* createPop(std::string line);
	bool parse() override;
	MemSegment getMemSegment();
	MemIndex getMemIndex();
private:
	MemSegment m_memSegment;
	MemIndex m_memIndex;
};

class LABEL : Parser {
public:
	static LABEL* createLabel(std::string line);
	bool parse() override;
	std::string getSymbName();
private:
	std::string m_symbName;
};

class GOTO : Parser {
public:
	static GOTO* createGoto(std::string line);
	bool parse() override;
	std::string getSymbName();
private:
	std::string m_symbName;
};

class IF : Parser {
public:
	static IF* createIf(std::string line);
	bool parse() override;
	std::string getSymbName();
private:
	std::string m_SymbName;
};

class FUNCTION : Parser {
public:
	static FUNCTION* createFunction(std::string line);
	bool parse() override;
	std::string getFuncName();
	size_t getLocalsNum();
private:
	std::string m_funcName;
	size_t m_localsNum;
};

class CALL : Parser {
public:
	static CALL* createCall(std::string line);
	bool parse() override;
	std::string getFuncName();
	size_t getLocalsNum();
private:
	std::string m_funcName;
	size_t m_localsNum;
};

class RETURN : Parser {
public:
	static RETURN* createReturn(std::string line);
	bool parse() override;
private:
	RETURN();
};