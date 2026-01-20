#pragma once

#include <format>
#include <Creepy/StringView.hpp>

template <>
struct std::formatter<Creepy::StringView>{
    constexpr inline auto parse(std::format_parse_context& ctx) {
        return ctx.begin();
    }

    inline auto format(const Creepy::StringView& strView, std::format_context& ctx) const {
        if(strView.count > 0){
            const auto resBro = std::format_to_n(ctx.out(), static_cast<size_t>(strView.count), "{}", strView.ptr);
            return resBro.out;
        }
        return std::format_to(ctx.out(), "null");
    }

};