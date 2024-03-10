#pragma once

#include "Token.h"
#include "Instruction.h"
#include "RegisterAliases.h"
#include "SymbolTable.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

class Lexer {
public:
    std::vector<Token> tokenize(const std::string& input, SymbolTable &symbolTable);

    static bool caseInsensitiveCompare(const std::string& str1, const std::string& str2) {
        return toLowerCase(str1) == toLowerCase(str2);
    }

    static std::string toLowerCase(const std::string& str) {
        std::string lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
        return lowerStr;
    }

private:

    const std::unordered_map<std::string, std::string>& registerAliasMap = RegisterAliases::registerAliasMap;
    const std::unordered_map<std::string, std::tuple<Type, std::string, std::string, std::string>>& instructionMap = InstructionInfo::instructionMap;
    bool isWhitespace(char c);
    bool isDelimiter(char c);
    bool isComment(char c);
    bool isHexadecimal(const std::string& str);
    bool isBinary(const std::string& str);
    std::string mapSpecialRegisters(const std::string& alias);
    TokenType getTokenType(const std::string& token);
};
