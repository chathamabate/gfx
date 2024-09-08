
#pragma once

#include <cstdlib>
#include <cstdint>
#include <iostream>

namespace gfx {
    template <typename T, size_t N>
    class Vec {
    private:
        T arr[N];

    public:
        inline Vec() : arr{0} {}
        inline Vec(const Vec<T, N> &o) : arr{o.arr} {}
        inline Vec(std::initializer_list<T> l) : arr{l} {}

        inline void operator=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] = o.arr[i];
            }
        }

        // No checks...
        inline T &operator[](size_t i) {
            return this->arr[i];
        }

        // Using carrot for dot product.
        inline T operator^(const Vec<T, N> &o) const {
            T dot_prod = 0;
            for (size_t i = 0; i < N; i++) {
                dot_prod += this->arr[i] * o.arr[i];
            }
            return dot_prod;
        }
        
        inline Vec<T, N> operator+(const Vec<T, N> &o) const {
            Vec<T, N> sum(*this);
            for (size_t i = 0; i < N; i++) {
                sum.arr[i] += o.arr[i];
            }
            return sum;
        }

        inline void operator+=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] += o.arr[i];
            }
        }

        inline Vec<T, N> operator-(const Vec<T, N> &o) const {
            Vec<T, N> diff(*this);
            for (size_t i = 0; i < N; i++) {
                diff.arr[i] - o.arr[i];
            }
            return diff; 
        }

        inline void operator-=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] -= o.arr[i];
            }
        }

        // Using * for scaling and flat mult.
        inline Vec<T, N> operator*(T s) const {
            Vec<T, N> prod(*this);
            for (size_t i = 0; i < N; i++) {
                prod.arr[i] *= s;
            }
            return prod;
        }

        inline Vec<T, N> operator*(const Vec<T, N> &o) const {
            Vec<T, N> prod(*this);
            for (size_t i = 0; i < N; i++) {
                prod.arr[i] *= o.arr[i];
            }
            return prod;
        }

        inline void operator*=(T s) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] *= s;
            }
        }

        inline void operator*=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] *= o.arr[i];
            }
        }

        inline Vec<T, N> operator-() const {
            return *this * -1;
        }
    };
}
