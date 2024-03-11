#include "Parser.h"

#include <string>
#include <vector>
#include <iostream>

Instruction Parser::parse(const std::vector<Token>& tokens, SymbolTable& symbolTable) {

    std::string instructionName = tokens[0].getValue();

    auto it = InstructionInfo::instructionMap.find(instructionName);

    if (it != InstructionInfo::instructionMap.end()) {
        Type type = std::get<0>(it->second);
        std::string opcode = std::get<1>(it->second);
        std::string funct3 = std::get<2>(it->second);
        std::string funct7 = std::get<3>(it->second);
        std::vector<std::string> operands;

        for (size_t i = 1; i < tokens.size(); ++i) {
            if (tokens[i].getType() == TokenType::LABEL) {

                int labelNextInstructionLineNumber = symbolTable.getLabelInstructionLineNumber(tokens[i].getValue());
                if (labelNextInstructionLineNumber == -1)
                    throw std::runtime_error("Label " + tokens[i].getValue() +  " used but not defined ");


                int immediate = 4 * labelNextInstructionLineNumber;
                if (type == Type::R_TYPE or type == Type::SB_TYPE or type == Type::UJ_TYPE)
                    immediate -= 4 * tokens[i].getLineNumber();
                else
                    immediate -= 4;

                operands.push_back(std::to_string(immediate));
            } else
                operands.push_back(tokens[i].getValue());
        }

        return Instruction(type, opcode, funct3, funct7, operands);
    }

    return Instruction(Type::INVALID_TYPE, "", "", "", {});

}