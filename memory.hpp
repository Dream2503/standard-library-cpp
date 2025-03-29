#pragma once
#include <cstdlib>

namespace Dream {
    template<typename T>
    class allocator {
    public:
        constexpr allocator() noexcept = default;
        constexpr T *allocate(const size_t size) const noexcept { return static_cast<T *>(malloc(size * sizeof(T))); }

        constexpr bool reallocate(T *&ptr, const size_t size) const noexcept {
            if (T *res = static_cast<T*>(realloc(ptr, size * sizeof(T)))) {
                ptr = res;
                return true;
            }
            return false;
        }
        constexpr void deallocate(T *ptr) const noexcept { free(ptr); }
        constexpr void construct(T *ptr, const T value) const noexcept { *ptr = value; }
        constexpr void destroy(T *ptr) const noexcept { ptr->~T(); }
    };
} // namespace Dream
