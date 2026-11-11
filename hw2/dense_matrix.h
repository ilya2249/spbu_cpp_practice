#pragma once
#include <stdexcept>
#include "matrix.h"
#include <vector>

class DenseMatrix: public Matrix {
    private:
        std::size_t rows_;
        std::size_t cols_;
        std::vector<double> data_;

    public:
        DenseMatrix(std::size_t rows, std::size_t cols):
            rows_(rows), cols_(cols), data_(rows * cols, 0.0) {}  
        std::size_t rows() const override { return rows_; }
        std::size_t cols() const override { return cols_; }

        double& at(std::size_t i,std::size_t j){
            if (i>=rows_ || j>=cols_) {
                throw std::out_of_range("Index out of range");
            }
            return data_[i*cols_+j];
        }
        
        const double& at(std::size_t i, std::size_t j) const{
            if (i>=rows_ || j>=cols_) {
                throw std::out_of_range("Index out of range");
            }
            return data_[i*cols_+j];
        }
    };
    
    


