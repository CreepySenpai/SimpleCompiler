#pragma once

#include <Creepy/DynArray.hpp>

namespace Creepy{

    struct Lexer{
        static constexpr char TERMINATOR = 0xff;

        DynArray<char> inputData;
        uint32_t currentReadPos;
    };

    Lexer Lexer_CreateLexer(DynArray<char> inputData);
    Lexer Lexer_CreateLexer(const char* str, Arena& arena);

    bool Lexer_IsEOF(const Lexer& lexer);
    bool Lexer_IsWhiteSpace(const Lexer& lexer);
    bool Lexer_IsNumber(const Lexer& lexer);
    bool Lexer_IsLetter(const Lexer& lexer);

    char Lexer_PeekNextChar(const Lexer& lexer);
    char Lexer_GetNextChar(Lexer& lexer);
    void Lexer_SkipWhiteSpace(Lexer& lexer);


    bool Lexer_IsMatch(Lexer& lexer, const char* syntax);
}