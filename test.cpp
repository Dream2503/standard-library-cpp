#include <cassert>
#include <iterator>

#include "iomanip.hpp"
#include "string.hpp"

int main() {
    Dream::cout << "1)  string(); ";
    Dream::string s1;
    assert(s1.empty() && (s1.length() == 0) && (s1.size() == 0));
    Dream::cout << "s1.capacity(): " << s1.capacity() << '\n'; // unspecified

    Dream::cout << "3)  string(size_type count, CharT ch): ";
    Dream::string s2(4, '=');
    Dream::cout << Dream::quoted(s2) << '\n'; // "===="

    Dream::cout << "4)  string(InputIt first, InputIt last): ";
    char mutable_c_str[] = "another C-style string";
    Dream::string s4(Dream::begin(mutable_c_str) + 8, Dream::end(mutable_c_str) - 1);
    Dream::cout << Dream::quoted(s4) << '\n'; // "C-style string"

    Dream::cout << "6)  string(CharT const* s, size_type count): ";
    Dream::string s6("C-style string", 7);
    Dream::cout << Dream::quoted(s6) << '\n'; // "C-style", i.e. [0, 7)

    Dream::cout << "7)  string(CharT const* s): ";
    Dream::string s7("C-style\0string");
    Dream::cout << Dream::quoted(s7) << '\n'; // "C-style"

    Dream::cout << "11) string(string&): ";
    Dream::string const other11("Exemplar");
    Dream::string s11(other11);
    Dream::cout << Dream::quoted(s11) << '\n'; // "Exemplar"

    // Dream::cout << "12) string(string&&): ";
    // Dream::string s12(Dream::string("C++ by ") + Dream::string("example"));
    // Dream::cout << Dream::quoted(s12) << '\n'; // "C++ by example"

    Dream::cout << "15) string(const string& other, size_type pos): ";
    Dream::string const other15("Mutatis Mutandis");
    Dream::string s15(other15, 8);
    Dream::cout << Dream::quoted(s15) << '\n'; // "Mutandis", i.e. [8, 16)

    Dream::cout << "17) string(const string& other, size_type pos, size_type count): ";
    Dream::string const other17("Exemplary");
    Dream::string s17(other17, 0, other17.length() - 1);
    Dream::cout << Dream::quoted(s17) << '\n'; // "Exemplar"
}
