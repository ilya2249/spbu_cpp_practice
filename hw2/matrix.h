#pragma once
#include <cstddef>
#include <memory>

class Matrix{
    public: 
        virtual std::size_t rows() const = 0;
        virtual std::size_t cols() const = 0;

        virtual std::unique_ptr<Matrix> mul(const Matrix& other) const = 0;
        virtual ~Matrix() = default;

    };