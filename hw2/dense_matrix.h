#pragma once
#include <stdexcept>
#include "matrix.h"
#include <vector>
#include <memory>
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
        
        DenseMatrix multiplyNaive(const DenseMatrix &other) const {
        
            if (cols_ != other.rows()){
                throw std::invalid_argument("Invalid matrix: cols_A != rows_B ");

            }
           
            DenseMatrix C(rows_, other.cols());
            for (size_t i = 0; i < rows_; i++){

                for (size_t j = 0; j<other.cols(); j++) {
                
                        for (size_t k = 0; k<cols_;k++){
                        C.at(i,j) +=  data_[i*cols_+k] * other.at(k,j);
                }
            
                }          

            }
            return C;


        };
        DenseMatrix OptimizedMultiply(const DenseMatrix &other) const {
            if (cols_ != other.rows()) throw std::invalid_argument("Invalid matrix: cols_A != rows_B ");
            DenseMatrix C(rows_,other.cols());
            for (size_t i = 0; i < rows_; i++){
                for (size_t k = 0; k<cols_;k++){
                    for (size_t j = 0; j<other.cols(); j++) {
                        C.at(i,j) +=  data_[i*cols_+k] * other.at(k,j);
                }
            
                }          

            }
            return C;

        }
        std::unique_ptr<Matrix> mul(
            const Matrix&other
        ) const override {
            const auto *dense = dynamic_cast<const DenseMatrix*> (&other);
            if (dense == nullptr) throw std::invalid_argument("Unsupported matrix type");
            auto ptr = std::make_unique<DenseMatrix>(OptimizedMultiply(*dense));
            return ptr;

        }


    };
    
    


