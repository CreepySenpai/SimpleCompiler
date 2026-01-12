#include <Creepy/Lexer.hpp>
#include <Creepy/Logger.hpp>
#include <Creepy/Assert.hpp>
#include <cstring>
#include <charconv>

namespace Creepy{
    Lexer Lexer_CreateLexer(DynArray<char> inputData) {
        return {
            .inputData = inputData,
            .currentReadPos = 0
        };
    }

    Lexer Lexer_CreateLexer(const char* str, Arena& arena) {
        const size_t strSize = std::strlen(str);
        Lexer lexer{
            .inputData = DynArray_Create<char>(arena, strSize),
            .currentReadPos = 0
        };

        std::memcpy(lexer.inputData.element, str, strSize);
        lexer.inputData.count = strSize;

        return lexer;
    }

    bool Lexer_IsEOF(const Lexer& lexer) {
        return lexer.currentReadPos >= lexer.inputData.count;
    }

    bool Lexer_IsWhiteSpace(const Lexer& lexer) {
        return Lexer_PeekNextChar(lexer) <= ' ';
    }

    static bool isNumber(char c){
        return c >= '0' && c <= '9';
    }

    static bool isLetter(char c){
        return (c == '_') || isNumber(c) || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    }

    bool Lexer_IsNumber(const Lexer& lexer) {
        const char nextChar = Lexer_PeekNextChar(lexer);
        return isNumber(nextChar);
    }

    bool Lexer_IsLetter(const Lexer& lexer) {
        const char nextChar = Lexer_PeekNextChar(lexer);
        return isLetter(nextChar);
    }

    char Lexer_PeekNextChar(const Lexer& lexer) {
        if(Lexer_IsEOF(lexer)){
            return Lexer::TERMINATOR;
        }

        return lexer.inputData.element[lexer.currentReadPos];
    }

    char Lexer_GetNextChar(Lexer& lexer) {
        const char nextChar = Lexer_PeekNextChar(lexer);
        ++lexer.currentReadPos;
        return nextChar;
    }

    void Lexer_SkipWhiteSpace(Lexer& lexer) {
        while(Lexer_IsWhiteSpace(lexer)){
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
            if(lexer.inputData.element[lexer.inputData.count + i] != syntax[i]){
                return false;
            }
        }

        // lexer.currentReadPos += syntaxLen;

        return true;
    }

    struct Viewer{
        const char* startData{nullptr};
        uint32_t count{};
    };

    Viewer Lexer_GetNextStringAsNumber(Lexer& lexer){
        const uint32_t start = lexer.currentReadPos;
        
        while(isNumber(Lexer_GetNextChar(lexer))){

        }

        Viewer viewer{
            .startData = &lexer.inputData.element[start],
            .count = lexer.currentReadPos - start
        };

        return viewer;
    }

    int64_t Lexer_GetNextNumber(Lexer& lexer){
        Viewer viewer = Lexer_GetNextStringAsNumber(lexer);
        int64_t num{};

        auto err = std::from_chars(viewer.startData, viewer.startData + viewer.count, num);

        // ASSERT(true);

        // if(err.ec == std::errc::invalid_argument){
        //     LOG("Input is not a number");
        // }
        // else if()

        return num;
    }
}