#pragma once

namespace Dream {
    template<typename T, typename Child>
    class iterator {
    protected:
        T *ptr_ = nullptr;

    public:
        constexpr iterator() noexcept = default;
        constexpr iterator(const T *value) noexcept : ptr_(const_cast<T *>(value)) {}
        constexpr iterator(const iterator &itr) noexcept : ptr_(itr.ptr_) {}

        constexpr Child operator+(const size_t offset) const noexcept { return ptr_ + offset; }
        constexpr Child operator-(const size_t offset) const noexcept { return ptr_ - offset; }
        constexpr size_t operator-(const iterator &other) const noexcept { return ptr_ - other.ptr_; }
        constexpr bool operator==(const iterator &itr) const noexcept { return ptr_ == itr.ptr_; }
        constexpr bool operator!=(const iterator &itr) const noexcept { return ptr_ != itr.ptr_; }
        constexpr T &operator*() const noexcept { return *ptr_; }
        constexpr operator const void *() const noexcept { return static_cast<const void *>(ptr_); }
        constexpr operator const T *() const noexcept { return static_cast<const T *>(ptr_); }

        constexpr Child &operator=(const T value) noexcept {
            *ptr_ = value;
            return *static_cast<Child *>(this);
        }

        constexpr Child &operator=(const iterator &other) noexcept {
            if (this != &other) {
                ptr_ = other.ptr_;
                return *static_cast<Child *>(this);
            }
            return *static_cast<Child *>(this);
        }

        constexpr Child &operator++() noexcept {
            ++ptr_;
            return *static_cast<Child *>(this);
        }

        constexpr Child operator++(int) noexcept {
            Child temp = *static_cast<Child *>(this);
            ++ptr_;
            return temp;
        }

        constexpr Child &operator--() noexcept {
            --ptr_;
            return *static_cast<Child *>(this);
        }

        constexpr Child operator--(int) noexcept {
            Child temp = *static_cast<Child *>(this);
            --ptr_;
            return temp;
        }

        constexpr Child &operator+=(const size_t offset) noexcept {
            ptr_ += offset;
            return *static_cast<Child *>(this);
        }

        constexpr Child &operator-=(const size_t offset) noexcept {
            ptr_ -= offset;
            return *static_cast<Child *>(this);
        }
    };


    template<typename T, typename Child>
    class reverse_iterator : public iterator<T, reverse_iterator<T, Child>> {
    protected:
        using iterator<T, reverse_iterator>::ptr_;

    public:
        using iterator<T, reverse_iterator>::iterator;

        constexpr Child &operator++() noexcept {
            --ptr_;
            return *this;
        }

        constexpr Child operator++(int) noexcept {
            Child temp = *this;
            --ptr_;
            return temp;
        }

        constexpr Child &operator--() noexcept {
            ++ptr_;
            return *this;
        }

        Child operator--(int) noexcept {
            Child temp = *this;
            ++ptr_;
            return temp;
        }

        constexpr Child &operator+=(const size_t offset) noexcept {
            ptr_ -= offset;
            return *this;
        }

        constexpr Child &operator-=(const size_t offset) noexcept {
            ptr_ += offset;
            return *this;
        }
    };

    template<typename T>
    constexpr auto begin(T &child) -> decltype(child.begin()) {
        return child.begin();
    }

    template<typename T>
    constexpr auto begin(const T &child) -> decltype(begin(child)) {
        return child.begin();
    }

    template<typename T, size_t N>
    constexpr T *begin(T (&array)[N]) {
        return array;
    }

    template<typename T>
    constexpr auto cbegin(const T &child) -> decltype(child.cbegin()) {
        return child.cbegin();
    }


    template<typename T>
    constexpr auto rbegin(T &child) -> decltype(child.rbegin()) {
        return child.rbegin();
    }

    template<typename T>
    constexpr auto rbegin(const T &child) -> decltype(rbegin(child)) {
        return child.rbegin();
    }

    template<typename T, size_t N>
    constexpr T *rbegin(T (&array)[N]) {
        return array + N - 1;
    }

    template<typename T>
    constexpr auto crbegin(const T &child) -> decltype(child.crbegin()) {
        return child.crbegin();
    }


    template<typename T>
    constexpr auto end(T &child) -> decltype(child.end()) {
        return child.end();
    }

    template<typename T>
    constexpr auto end(const T &child) -> decltype(end(child)) {
        return child.end();
    }

    template<typename T, size_t N>
    constexpr T *end(T (&array)[N]) {
        return array + N;
    }

    template<typename T>
    constexpr auto cend(const T &child) -> decltype(child.cend()) {
        return child.cend();
    }


    template<typename T>
    constexpr auto rend(T &child) -> decltype(child.rend()) {
        return child.rend();
    }

    template<typename T>
    constexpr auto rend(const T &child) -> decltype(rend(child)) {
        return child.rend();
    }

    template<typename T, size_t N>
    constexpr T *rend(T (&array)[N]) {
        return array - 1;
    }

    template<typename T>
    constexpr auto crend(const T &child) -> decltype(child.crend()) {
        return child.crend();
    }
} // namespace Dream
