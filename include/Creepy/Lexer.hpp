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

    // Check match syntax, if true then advance read pos to end syntax
    bool Lexer_IsMatch(Lexer& lexer, const char* syntax);

    // Check match syntax and not follow by id letter, if true then advance read pos to end syntax
    bool Lexer_IsMatchExact(Lexer& lexer, const char* syntax);

    StringView Lexer_GetAnyNextToken(Lexer& lexer);

    
    int64_t Lexer_ParseToNumber(Lexer& lexer);
}