#pragma once

namespace Dream {
    template<typename T>
    class iterator {
    protected:
        T *ptr_ = nullptr;

    public:
        constexpr iterator() noexcept = default;
        constexpr iterator(const T *value) noexcept : ptr_(const_cast<T *>(value)) {}
        constexpr iterator(const iterator &itr) noexcept : ptr_(itr.ptr_) {}
        constexpr auto operator+(const size_t offset) const noexcept { return ptr_ + offset; }
        constexpr auto operator-(const size_t offset) const noexcept { return ptr_ - offset; }
        constexpr size_t operator-(const iterator &other) const noexcept { return ptr_ - other.ptr_; }
        constexpr bool operator==(const iterator &itr) const noexcept { return ptr_ == itr.ptr_; }
        constexpr bool operator!=(const iterator &itr) const noexcept { return ptr_ != itr.ptr_; }
        constexpr T &operator*() const noexcept { return *ptr_; }
        constexpr operator const void *() const noexcept { return static_cast<const void *>(ptr_); }
        constexpr operator const T *() const noexcept { return static_cast<const T *>(ptr_); }

        constexpr iterator &operator=(const T value) noexcept {
            *ptr_ = value;
            return *this;
        }

        constexpr iterator &operator=(const iterator &other) noexcept {
            if (this != &other) {
                ptr_ = other.ptr_;
                return *this;
            }
            return *this;
        }

        constexpr iterator &operator++() noexcept {
            ++ptr_;
            return *this;
        }

        constexpr iterator operator++(int) noexcept {
            iterator temp = *this;
            ++ptr_;
            return temp;
        }

        constexpr iterator &operator--() noexcept {
            --ptr_;
            return *this;
        }

        constexpr iterator operator--(int) noexcept {
            iterator temp = *this;
            --ptr_;
            return temp;
        }

        constexpr iterator &operator+=(const size_t offset) noexcept {
            ptr_ += offset;
            return *this;
        }

        constexpr iterator &operator-=(const size_t offset) noexcept {
            ptr_ -= offset;
            return *this;
        }
    };


    template<typename T>
    class reverse_iterator : public iterator<T> {
    protected:
        using iterator<T>::ptr_;

    public:
        using iterator<T>::iterator;

        constexpr reverse_iterator &operator++() noexcept {
            --ptr_;
            return *this;
        }

        constexpr reverse_iterator operator++(int) noexcept {
            reverse_iterator temp = *this;
            --ptr_;
            return temp;
        }

        constexpr reverse_iterator &operator--() noexcept {
            ++ptr_;
            return *this;
        }

        reverse_iterator operator--(int) noexcept {
            reverse_iterator temp = *this;
            ++ptr_;
            return temp;
        }

        constexpr reverse_iterator &operator+=(const size_t offset) noexcept {
            ptr_ -= offset;
            return *this;
        }

        constexpr reverse_iterator &operator-=(const size_t offset) noexcept {
            ptr_ += offset;
            return *this;
        }
    };

    template<typename T>
    constexpr auto begin(T &itr) -> decltype(itr.begin()) {
        return itr.begin();
    }

    template<typename T>
    constexpr auto begin(const T &itr) -> decltype(begin(itr)) {
        return itr.begin();
    }

    template<typename T, size_t N>
    constexpr T *begin(T (&array)[N]) {
        return array;
    }

    template<typename T>
    constexpr auto cbegin(const T &itr) -> decltype(itr.cbegin()) {
        return itr.cbegin();
    }


    template<typename T>
    constexpr auto rbegin(T &itr) -> decltype(itr.rbegin()) {
        return itr.rbegin();
    }

    template<typename T>
    constexpr auto rbegin(const T &itr) -> decltype(rbegin(itr)) {
        return itr.rbegin();
    }

    template<typename T, size_t N>
    constexpr T *rbegin(T (&array)[N]) {
        return array + N - 1;
    }

    template<typename T>
    constexpr auto crbegin(const T &itr) -> decltype(itr.crbegin()) {
        return itr.crbegin();
    }


    template<typename T>
    constexpr auto end(T &itr) -> decltype(itr.end()) {
        return itr.end();
    }

    template<typename T>
    constexpr auto end(const T &itr) -> decltype(end(itr)) {
        return itr.end();
    }

    template<typename T, size_t N>
    constexpr T *end(T (&array)[N]) {
        return array + N;
    }

    template<typename T>
    constexpr auto cend(const T &itr) -> decltype(itr.cend()) {
        return itr.cend();
    }


    template<typename T>
    constexpr auto rend(T &itr) -> decltype(itr.rend()) {
        return itr.rend();
    }

    template<typename T>
    constexpr auto rend(const T &itr) -> decltype(rend(itr)) {
        return itr.rend();
    }

    template<typename T, size_t N>
    constexpr T *rend(T (&array)[N]) {
        return array - 1;
    }

    template<typename T>
    constexpr auto crend(const T &itr) -> decltype(itr.crend()) {
        return itr.crend();
    }
} // namespace Dream
