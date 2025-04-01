#pragma once
#include <cstring>
#include "iostream.hpp"
#include "iterator.hpp"
#include "memory.hpp"
#define BUFFER_SIZE 1024


namespace Dream {
    class string {
        char *buffer_;
        size_t capacity_, size_;
        allocator<char> alloc_;

    public:
        const size_t npos = static_cast<size_t>(-1);

        class iterator final : public Dream::iterator<char> {
        public:
            using Dream::iterator<char>::iterator;
        };

        class reverse_iterator final : public Dream::reverse_iterator<char> {
        public:
            using Dream::reverse_iterator<char>::reverse_iterator;
        };

        class const_iterator final : public Dream::iterator<const char> {
        public:
            using iterator::iterator;
        };

        class const_reverse_iterator final : public Dream::reverse_iterator<const char> {
        public:
            using reverse_iterator::reverse_iterator;
        };

        constexpr string() noexcept : string(allocator<char>()) {}
        explicit constexpr string(const allocator<char> &alloc) noexcept : buffer_(nullptr), capacity_(0), size_(0), alloc_(alloc) {}
        constexpr string(const char *str, const size_t count, const allocator<char> &alloc = allocator<char>()) noexcept : string(str, str + count, alloc) {}
        constexpr string(const char *str, const allocator<char> &alloc = allocator<char>()) noexcept : string(str, strlen(str), alloc) {}
        constexpr string(const string &other, const allocator<char> &alloc) noexcept : string(other, 0, 0, alloc) {}
        constexpr string(const string &other, const size_t pos, const allocator<char> &alloc) noexcept : string(other, pos, 0, alloc) {}
        constexpr string(string &&other, const allocator<char> &alloc) noexcept : string(static_cast<string &&>(other), 0, 0, alloc) {}
        constexpr string(string &&other, const size_t pos, const allocator<char> &alloc) noexcept : string(static_cast<string &&>(other), pos, 0, alloc) {}
        constexpr string(const string &other, const size_t pos = 0, const size_t count = 0, const allocator<char> &alloc = allocator<char>()) noexcept :
            string(other.begin() + pos, other.begin() + (count ? pos + count : other.size_), alloc) {}

        constexpr string(const size_t count, const char ch, const allocator<char> &alloc = allocator<char>()) noexcept :
            buffer_(nullptr), capacity_(count + 1), size_(count), alloc_(alloc) {
            if (size_) {
                if ((buffer_ = alloc_.allocate(capacity_ * sizeof(char)))) {
                    for (size_t i = 0; i < count; ++i) {
                        buffer_[i] = ch;
                    }
                    buffer_[size_] = 0;
                } else {
                    *this = string();
                }
            } else {
                *this = string();
            }
        }

        constexpr string(const iterator &first, const iterator &last, const allocator<char> &alloc = allocator<char>()) noexcept :
            buffer_(nullptr), capacity_(last - first + 1), size_(last - first), alloc_(alloc) {
            if (size_) {
                if ((buffer_ = alloc_.allocate(capacity_ * sizeof(char)))) {
                    memcpy(buffer_, first, size_);
                    buffer_[size_] = 0;
                } else {
                    *this = string();
                }
            } else {
                *this = string();
            }
        }

        constexpr string(string &&other, const size_t pos = 0, const size_t count = 0, const allocator<char> &alloc = allocator<char>()) noexcept :
            buffer_(nullptr), capacity_(count + 1), size_(count), alloc_(alloc) {
            if (size_) {
                if ((buffer_ = alloc_.allocate(capacity_ * sizeof(char)))) {
                    for (size_t i = pos; i <= pos + size_; ++i) {
                        buffer_[i - pos] = other.buffer_[i];
                    }
                    buffer_[size_] = 0;
                    other = string();
                } else {
                    *this = string();
                }
            } else {
                *this = string();
            }
        }

        constexpr string &operator=(const char *str) noexcept { return *this = string(str); }
        constexpr string &operator=(const char ch) noexcept { return *this = string(&ch, 1); }

        constexpr string &operator=(const string &other) noexcept {
            if (this != &other) {
                alloc_.deallocate(buffer_);
                *this = string(other.begin(), other.end());
            }
            return *this;
        }

        constexpr string &operator=(string &&other) noexcept {
            if (this != &other) {
                capacity_ = other.capacity_;
                size_ = other.size_;
                alloc_ = other.alloc_;
                alloc_.deallocate(buffer_);
                buffer_ = other.buffer_;
                other.buffer_ = nullptr;
                other.capacity_ = other.size_ = 0;
            }
            return *this;
        }

        constexpr string &assign(const string &other) noexcept { return *this = other; }
        constexpr string &assign(const string &&other) noexcept { return *this = const_cast<string &&>(other); }
        constexpr string &assign(const size_t count, const char ch) { return *this = string(count, ch); }
        constexpr string &assign(const char *str, const size_t count) { return *this = string(str, count); }
        constexpr string &assign(const char *str) { return *this = str; }
        constexpr string &assign(const string &other, const size_t sub_pos, const size_t sub_len = 0) {
            return *this = string(other, sub_pos, sub_len ? sub_len : other.size_ - sub_pos);
        }
        string &assign(const iterator &first, const iterator &last) { return *this = first; }

        constexpr const allocator<char> &get_allocator() const noexcept { return alloc_; }

        constexpr const char &at(const size_t pos) const noexcept {
            if (pos >= size_) {
                return *end();
            }
            return buffer_[pos];
        }

        constexpr char &at(const size_t pos) noexcept {
            if (pos >= size_) {
                return *end();
            }
            return buffer_[pos];
        }

        constexpr const char &operator[](const size_t pos) const noexcept { return this->at(pos); }
        constexpr char &operator[](const size_t pos) noexcept { return this->at(pos); }

        constexpr const char &front() const noexcept { return buffer_[0]; }
        constexpr char &front() noexcept { return buffer_[0]; }
        constexpr const char &back() const noexcept { return buffer_[size_ - 1]; }
        constexpr char &back() noexcept { return buffer_[size_ - 1]; }

        constexpr char *data() noexcept { return buffer_; }
        constexpr const char *data() const noexcept { return buffer_; }
        constexpr const char *c_str() const noexcept { return buffer_; }

        constexpr iterator begin() const noexcept { return buffer_; }
        constexpr const_iterator cbegin() const noexcept { return buffer_; }
        constexpr iterator end() const noexcept { return buffer_ + size_; }
        constexpr const_iterator cend() const noexcept { return buffer_ + size_; }

        constexpr reverse_iterator rbegin() const noexcept { return buffer_ + size_ - 1; }
        constexpr const_reverse_iterator crbegin() const noexcept { return buffer_ + size_ - 1; }
        constexpr reverse_iterator rend() const noexcept { return buffer_ - 1; }
        constexpr const_reverse_iterator crend() const noexcept { return buffer_ - 1; }

        constexpr size_t find(const string &other, const size_t pos = 0) const noexcept { return find(other.buffer_, pos, other.size_); }
        constexpr size_t find(const char *str, const size_t pos) const noexcept { return find(str, pos, strlen(str)); }
        constexpr size_t find(const char ch, const size_t pos = 0) const noexcept { return find(&ch, pos, 1); }

        constexpr size_t find(const char *str, const size_t pos, const size_t count) const noexcept {
            if (count == 0) {
                return pos;
            }
            if (pos >= size_ || count > size_ - pos) {
                return npos;
            }

            for (size_t i = pos; i <= size_ - count; ++i) {
                size_t j = 0;

                while (j < count && buffer_[i + j] == str[j]) {
                    ++j;
                }
                if (j == count) {
                    return i;
                }
            }
            return npos;
        }

        constexpr size_t rfind(const string &other, const size_t pos = 0) const noexcept { return rfind(other.buffer_, pos, other.size_); }
        constexpr size_t rfind(const char *str, const size_t pos) const noexcept { return rfind(str, pos, strlen(str)); }
        constexpr size_t rfind(const char ch, const size_t pos = 0) const noexcept { return rfind(&ch, pos, 1); }

        constexpr size_t rfind(const char *str, const size_t pos, const size_t count) const noexcept {
            if (count == 0) {
                return pos;
            }
            if (pos >= size_ || count > size_ - pos) {
                return npos;
            }

            for (size_t i = size_ - 1; i >= pos + count; --i) {
                size_t j = count;

                while (j != npos && buffer_[i + j - count] == str[j]) {
                    --j;
                }
                if (j == npos) {
                    return i;
                }
            }
            return npos;
        }


        constexpr friend const ostream &operator<<(const ostream &stream, const string &str) noexcept {
            if (str.buffer_) {
                stream << str.buffer_;
            }
            return stream;
        }

        friend const istream &operator>>(const istream &stream, string &str) noexcept {
            char buffer[BUFFER_SIZE];

            if (fgets(buffer, sizeof(buffer), stdin)) {
                const size_t len = strlen(buffer);

                if (buffer[len - 1] == '\n') {
                    buffer[len - 1] = 0;
                }
                str = string(buffer, buffer + len);
            }
            return stream;
        }

        constexpr operator bool() const noexcept { return buffer_ != nullptr; }

        string &append(const size_t num, const char ch) noexcept { return append(string(num, ch)); }
        string &append(const char *str, const size_t len) noexcept { return append(str, str + len); }
        string &append(const char *str) noexcept { return append(str, str + strlen(str)); }
        string &append(const string &other) noexcept { return append(other.begin(), other.end()); }
        string &append(const string &other, const size_t sub_pos, const size_t sub_len = 0) noexcept {
            return this->append(other.begin() + sub_pos, other.begin() + sub_pos + (sub_len ? sub_len : other.size_ - sub_pos));
        }

        string &append(const iterator &first, const iterator &last) noexcept {
            const size_t len = last - first;

            if (len && alloc_.reallocate(buffer_, (size_ + len + 1) * sizeof(char))) {
                size_t i = size_;
                iterator itr = first;

                while (itr != last) {
                    buffer_[i] = *itr;
                    ++itr;
                    ++i;
                }
                size_ += len;
                capacity_ = size_ + 1;
                buffer_[size_] = 0;
            }
            return *this;
        }

        void clear();

        int compare(const string &other);

        int compare(size_t pos, size_t len, const string &other);

        int compare(size_t pos, size_t len, const string &str, size_t subpos, size_t sublen);

        int compare(const char *s);

        int compare(size_t pos, size_t len, const char *s);

        int compare(size_t pos, size_t len, const char *s, size_t n);

        size_t copy(const char *other, size_t len, size_t pos);

        bool empty() const { return size_ == 0; }

        bool ends_with(const string &suffix);

        bool ends_with(const char *suffix);

        bool ends_with(char ch);

        iterator &erase(const_iterator &pos);

        iterator &erase(const_iterator &first, const_iterator &last);

        string &erase(size_t pos, size_t count);

        size_t find_first_not_of(const string &other, size_t pos);

        size_t find_first_not_of(const char *other, size_t pos);

        size_t find_first_not_of(const char *other, size_t pos, size_t count);

        size_t find_first_not_of(char ch, size_t pos);

        size_t find_first_of(const string &other, size_t pos);

        size_t find_first_of(const char *other, size_t pos);

        size_t find_first_of(const char *other, size_t pos, size_t count);

        size_t find_first_of(char ch, size_t pos);

        size_t find_last_not_of(const string &other, size_t pos);

        size_t find_last_not_of(const char *other, size_t pos);

        size_t find_last_not_of(const char *other, size_t pos, size_t count);

        size_t find_last_not_of(char ch, size_t pos);

        size_t find_last_of(const string &other, size_t pos);

        size_t find_last_of(const char *other, size_t pos);

        size_t find_last_of(const char *other, size_t pos, size_t count);

        size_t find_last_of(char ch, size_t pos);

        string &insert(size_t pos, const string &other);

        string &insert(size_t pos, const string &str, size_t sub_pos, size_t sub_len);

        string &insert(size_t pos, const char *other);

        string &insert(size_t pos, const char *other, size_t num);

        string &insert(size_t pos, size_t num, char ch);

        iterator insert(const_iterator first, char ch);

        iterator insert(const_iterator first, size_t num, char ch);

        iterator insert(const_iterator p, iterator first, iterator last);

        size_t length() const { return size_; }
        size_t size() const { return size_; }
        size_t capacity() const { return capacity_; }

        void pop_back();

        void push_back(const char ch);

        string &replace(const_iterator start, const_iterator end, const char *other);

        string &replace(const_iterator start, const_iterator end, const string &other);

        constexpr void reserve(const size_t new_capacity) noexcept {
            if (new_capacity > capacity_) {
                if (char *new_buffer = alloc_.allocate(new_capacity * sizeof(char))) {
                    memcpy(new_buffer, buffer_, size_ + 1);
                    alloc_.deallocate(buffer_);
                    buffer_ = new_buffer;
                    capacity_ = new_capacity;
                }
            }
        }

        constexpr string operator+(const string &other) const noexcept {
            string temp = *this;
            temp.append(other);
            return temp;
        }

        constexpr string operator+(const char *str) const noexcept {
            string temp = *this;
            temp.append(str);
            return temp;
        }

        constexpr ~string() noexcept {
            if (buffer_) {
                alloc_.deallocate(buffer_);
            }
            buffer_ = nullptr;
        }
    };
} // namespace Dream
