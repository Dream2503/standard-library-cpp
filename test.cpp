#include <cassert>
#include <iterator>

#include "iomanip.hpp"

#include "string.hpp"

int main() {
    Dream::string s;
    // assign(size_type count, CharT ch)
    s.assign(4, '=');
    Dream::cout << s << '\n'; // "===="

    Dream::string const c("Exemplary");
    // assign(const basic_string& str)
    s.assign(c);
    Dream::cout << c << " == " << s << '\n'; // "Exemplary == Exemplary"

    // assign(const basic_string& str, size_type pos, size_type count)
    s.assign(c, 0, c.length() - 1);
    Dream::cout << s << '\n'; // "Exemplar";

    // assign(basic_string&& str)
    s.assign(Dream::string("C++ by ") + "example");
    Dream::cout << s << '\n'; // "C++ by example"

    // assign(const CharT* s, size_type count)
    s.assign("C-style string", 7);
    Dream::cout << s << '\n'; // "C-style"

    // assign(const CharT* s)
    s.assign("C-style\0string");
    Dream::cout << s << '\n'; // "C-style"

    char mutable_c_str[] = "C-style string";
    // assign(InputIt first, InputIt last)
    s.assign(Dream::begin(mutable_c_str), Dream::end(mutable_c_str) - 1);
    Dream::cout << s << '\n'; // "C-style string"

    // // assign(Dream::initializer_list<CharT> ilist)
    // s.assign({'C', '-', 's', 't', 'y', 'l', 'e'});
    // Dream::cout << s << '\n'; // "C-style"
}
