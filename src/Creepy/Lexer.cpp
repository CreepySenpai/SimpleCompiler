#include <Creepy/Lexer.hpp>
#include <Creepy/Logger.hpp>
#include <Creepy/Assert.hpp>
#include <cstring>
#include <charconv>

namespace {
    static bool isNumber(char c){
        return c >= '0' && c <= '9';
    }

    static bool isWhiteSpace(char c){
        return (c == ' ') || (c == '\t') || (c == '\n');
    }

    static bool isLetter(char c){
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    static bool isPunctuation(char c){
        static constexpr char punctualTable[] = "=;[]<>(){}+-/*!";
        for(char p : punctualTable){
            if(p == c){
                return true;
            }
        }

        return false;
    }

    // Check char in alphabet
    static bool isAlphabet(char c){
        return isLetter(c) || isNumber(c);
    }

    // Only accept str + _ to be start of identifier
    static bool isIDStart(char c){
        return isLetter(c) || c == '_';
    }

    // Accept Alphabet + _
    static bool isIDLetter(char c){
        // return isLetter(c) || c == '_';
        return isAlphabet(c) || c == '_';
    }
}

namespace Creepy{
    Lexer Lexer_CreateLexer(StringView inputData) {
        return {
            .inputData = inputData,
            .currentReadPos = 0
        };
    }

    bool Lexer_IsEOF(const Lexer& lexer) {
        return lexer.currentReadPos >= lexer.inputData.count;
    }

    bool Lexer_IsWhiteSpace(const Lexer& lexer) {
        return Lexer_PeekCurrentChar(lexer) <= ' ';
    }

    char Lexer_PeekCurrentChar(const Lexer& lexer) {
        if(Lexer_IsEOF(lexer)){
            return Lexer::TERMINATOR;
        }

        return lexer.inputData.ptr[lexer.currentReadPos];
    }


    void Lexer_SkipWhiteSpace(Lexer& lexer) {
        while(isWhiteSpace(Lexer_PeekCurrentChar(lexer))){
            ++lexer.currentReadPos;
        }
    }

    bool Lexer_IsMatch(Lexer& lexer, const char* syntax) {
        Lexer_SkipWhiteSpace(lexer);

        const size_t syntaxLen = std::strlen(syntax);

        if(lexer.currentReadPos + syntaxLen > lexer.inputData.count){
            LOG("Input too long");

            return false;
        }

        for(uint32_t i{}; i < syntaxLen; ++i){
            if(lexer.inputData.ptr[lexer.inputData.count + i] != syntax[i]){
                return false;
            }
        }

        return true;
    }


    StringView Lexer_GetNextNumber(Lexer& lexer){
        const uint32_t start = lexer.currentReadPos;
        
        while(isNumber(Lexer_PeekCurrentChar(lexer))){
            ++lexer.currentReadPos;
        }

        StringView strView{
            .ptr = &lexer.inputData.ptr[start],
            .count = lexer.currentReadPos - start
        };

        return strView;
    }

    int64_t Lexer_ParseToNumber(Lexer& lexer){
        StringView strView = Lexer_GetNextNumber(lexer);
        int64_t num{};

        auto err = std::from_chars(strView.ptr, strView.ptr + strView.count, num);

        ASSERT_MSG((err.ec != std::errc::invalid_argument), "Lexer: Invalid input");

        return num;
    }

    StringView Lexer_GetNextID(Lexer& lexer){
        const uint32_t start = lexer.currentReadPos;

        while(isIDLetter(Lexer_PeekCurrentChar(lexer))){
            ++lexer.currentReadPos;
        }

        return StringView{
            .ptr = &lexer.inputData.ptr[start],
            .count = lexer.currentReadPos - start
        };
    }

    StringView Lexer_GetNextPunctual(Lexer& lexer){
        const uint32_t startPos = lexer.currentReadPos;
        ++lexer.currentReadPos;

        return {
            .ptr = &lexer.inputData.ptr[startPos],
            .count = 1
        };
    }


    StringView Lexer_GetAnyNextToken(Lexer& lexer) {
        if(Lexer_IsEOF(lexer)){
            return {};
        }

        if(isIDStart(Lexer_PeekCurrentChar(lexer))){
            return Lexer_GetNextID(lexer);
        }

        if(isNumber(Lexer_PeekCurrentChar(lexer))){
            return Lexer_GetNextNumber(lexer);
        }

        if(isPunctuation(Lexer_PeekCurrentChar(lexer))){
            return Lexer_GetNextPunctual(lexer);
        }

        return {
            .ptr = &lexer.inputData.ptr[lexer.currentReadPos],
            .count = 1
        };
    }
}