#pragma once
#include "iostream.hpp"
#include "string.hpp"

namespace Dream {
    class quoted {
        char *str_;
        const char delim_, escape_;

    public:
        constexpr quoted(const char *str, const char delim = '"', const char escape = '\\') noexcept : str_(const_cast<char *>(str)), delim_(delim), escape_(escape) {}
        constexpr quoted(const string &str, const char delim = '"', const char escape = '\\') noexcept : str_(const_cast<char *>(str.data())), delim_(delim), escape_(escape) {}
        constexpr quoted(string &str, const char delim = '"', const char escape = '\\') noexcept : str_(str.data()), delim_(delim), escape_(escape) {}

        constexpr friend const ostream &operator<<(const ostream &stream, const quoted &quote) noexcept {
            stream << quote.delim_;
            const char *str = quote.str_;

            while (str && *str) {
                if (*str == quote.delim_ || *str == quote.escape_) {
                    stream << quote.escape_;
                }
                stream << *str++;
            }
            stream << quote.delim_;
            return stream;
        }

        friend const istream &operator>>(const istream &stream, const quoted &quote) noexcept {
            char ch, *res = quote.str_;
            stream >> ch;

            if (ch == quote.delim_) {
                while (true) {
                    stream >> ch;

                    if (ch == quote.delim_) {
                        break;
                    }
                    if (ch == quote.escape_) {
                        stream >> ch;

                        if (ch == quote.delim_ || ch == quote.escape_) {
                            *res++ = quote.delim_;
                            continue;
                        }
                    }
                    *res++ = ch;
                }
            }
            *res = 0;
            return stream;
        }
    };
} // namespace Dream
