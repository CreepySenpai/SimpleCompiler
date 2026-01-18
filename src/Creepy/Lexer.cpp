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
        return Lexer_PeekCurrentChar(lexer) <= ' ';
    }

    char Lexer_PeekCurrentChar(const Lexer& lexer) {
        if(Lexer_IsEOF(lexer)){
            return Lexer::TERMINATOR;
        }

        return lexer.inputData.element[lexer.currentReadPos];
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
            if(lexer.inputData.element[lexer.inputData.count + i] != syntax[i]){
                return false;
            }
        }

        // lexer.currentReadPos += syntaxLen;

        return true;
    }


    StringView Lexer_GetNextNumber(Lexer& lexer){
        const uint32_t start = lexer.currentReadPos;
        
        while(isNumber(Lexer_PeekCurrentChar(lexer))){
            ++lexer.currentReadPos;
        }

        StringView strView{
            .ptr = &lexer.inputData.element[start],
            .count = lexer.currentReadPos - start
        };

        return strView;
    }

    int64_t Lexer_ParseToNumber(Lexer& lexer){
        StringView strView = Lexer_GetNextNumber(lexer);
        int64_t num{};

        auto err = std::from_chars(strView.ptr, strView.ptr + strView.count, num);

        ASSERT_MSG((err.ec == std::errc::invalid_argument), "Lexer: Invalid input");

        return num;
    }

    StringView Lexer_GetNextID(Lexer& lexer){
        const uint32_t start = lexer.currentReadPos;

        while(isIDLetter(Lexer_PeekCurrentChar(lexer))){
            ++lexer.currentReadPos;
        }

        return StringView{
            .ptr = &lexer.inputData.element[start],
            .count = lexer.currentReadPos - start
        };
    }

    StringView Lexer_GetNextPunctual(Lexer& lexer){
        return {
            .ptr = &lexer.inputData.element[lexer.currentReadPos],
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
            .ptr = &lexer.inputData.element[lexer.currentReadPos],
            .count = 1
        };
    }
}