
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
        Vec() : arr{0} {}
        Vec(const Vec<T, N> &o) : arr{o.arr} {}
        Vec(std::initializer_list<T> l) : arr{l} {}
        ~Vec() = default;

        void operator=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] = o.arr[i];
            }
        }

        // No checks...
        T &operator[](size_t i) {
            return this->arr[i];
        }

        // Using carrot for dot product.
        T operator^(const Vec<T, N> &o) const {
            T dot_prod = 0;
            for (size_t i = 0; i < N; i++) {
                dot_prod += this->arr[i] * o.arr[i];
            }
            return dot_prod;
        }
        
        Vec<T, N> operator+(const Vec<T, N> &o) const {
            Vec<T, N> sum(*this);
            for (size_t i = 0; i < N; i++) {
                sum.arr[i] += o.arr[i];
            }
            return sum;
        }

        void operator+=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] += o.arr[i];
            }
        }

        Vec<T, N> operator-(const Vec<T, N> &o) const {
            Vec<T, N> diff(*this);
            for (size_t i = 0; i < N; i++) {
                diff.arr[i] - o.arr[i];
            }
            return diff; 
        }

        void operator-=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] -= o.arr[i];
            }
        }

        // Using * for scaling and flat mult.
        Vec<T, N> operator*(T s) const {
            Vec<T, N> prod(*this);
            for (size_t i = 0; i < N; i++) {
                prod.arr[i] *= s;
            }
            return prod;
        }

        Vec<T, N> operator*(const Vec<T, N> &o) const {
            Vec<T, N> prod(*this);
            for (size_t i = 0; i < N; i++) {
                prod.arr[i] *= o.arr[i];
            }
            return prod;
        }

        void operator*=(T s) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] *= s;
            }
        }

        void operator*=(const Vec<T, N> &o) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] *= o.arr[i];
            }
        }

        Vec<T, N> operator/(T s) const {
            Vec<T, N> quot(*this);
            for (size_t i = 0; i < N; i++) {
                quot.arr[i] /= s;
            }
            return quot;
        }

        void operator/=(T s) {
            for (size_t i = 0; i < N; i++) {
                this->arr[i] /= s;
            }
        }

        Vec<T, N> operator-() const {
            return *this * -1;
        }

        T mag2() const {
            return *this ^ *this;
        }

        double mag() const {
            return std::sqrt(this->mag2());
        }

        Vec<T, N> norm() const {
            return *this / this->mag();
        }

        void normalize() {
            *this /= this->mag();
        }

        Vec<T, N> proj(const Vec<T, N> &o) const {
            return ((*this ^ o) / (o ^ o)) * o;
        }
    };

    typedef Vec<double, 3> Vec3d;
    typedef Vec<float, 3> Vec3f;

    template <typename T, size_t IN, size_t OUT>
    class VecFunc {
    public:
        VecFunc() {};
        virtual ~VecFunc() = default;
        virtual Vec<T, OUT> apply(const Vec<T, IN> &v) = 0;      
    };
}
