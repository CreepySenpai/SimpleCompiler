#pragma once

#include <Creepy/DynArray.hpp>
#include <Creepy/StringView.hpp>

namespace Creepy{

    struct Lexer{
        static constexpr char TERMINATOR = 0xff;

        StringView inputData;
        uint32_t currentReadPos;
    };

    Lexer Lexer_CreateLexer(StringView inputData);

    bool Lexer_IsEOF(const Lexer& lexer);
    bool Lexer_IsWhiteSpace(const Lexer& lexer);
    bool Lexer_IsNumber(const Lexer& lexer);
    bool Lexer_IsLetter(const Lexer& lexer);

    char Lexer_PeekCurrentChar(const Lexer& lexer);
    void Lexer_SkipWhiteSpace(Lexer& lexer);

    
    bool Lexer_IsMatch(Lexer& lexer, const char* syntax);

    StringView Lexer_GetAnyNextToken(Lexer& lexer);
}