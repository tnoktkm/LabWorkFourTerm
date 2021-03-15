#include <iostream>
#include <iomanip> 
#include <vector>

using column_t = std::vector<double>;
using matrix_t = std::vector<std::vector<double>>;

class Matrix {

    /*Class Matrix for solve -> System Line algebraical the Equations
 
    :a:      ->  2 dimension vector(Matrix)
    :b:      ->  1 dimension vector(the Equations)
 
    */

private:
    matrix_t coefs;
    column_t freeCoefs;
    /*
    a[0].size ==== count column(only go on diagonal - important!!! )
    :k:  ->  k-column, and from k to vector.size  
     */  

    int getHeadElementColumn(size_t k) {
        for (size_t i = k; i < coefs.size(); ++i) {
            if (coefs[i][k] != 0) {
                return i;
            }
        }
        return -1;
    }

    void groundingColumn(size_t k) {

        // :coef:  ->  coefficient first addendum (in k-row)
        double coef = coefs[k][k];

        for (size_t m = k; m < coefs.size(); ++m) {
            coefs[k][m] /= coef;
        }
        freeCoefs[k] /= coef;

        for (size_t i = k + 1; i < coefs.size(); ++i) {
            double coefficient = coefs[i][k] / coefs[k][k];
            for (size_t j = k; j < coefs[0].size(); ++j) {
                coefs[i][j] = coefs[i][j] - (coefficient * coefs[k][j]);
            }
            freeCoefs[i] = freeCoefs[i] - (coefficient * freeCoefs[k]);
        }   
    }

public:
    //constructor
    Matrix(const matrix_t &coefs, const column_t &freeCoefs) : coefs(coefs), freeCoefs(freeCoefs) {}
     
    //getting vector a
    matrix_t getA() {
        return coefs;
    }

    //getting vector b
    column_t getB() {
        return freeCoefs;
    }

    void forwardRunGaus() {
        for (size_t i = 0; i < coefs.size(); ++i) {

            size_t element = getHeadElementColumn(i); 
            coefs[element].swap(coefs[i]); // swap rows to the surface
            groundingColumn(i);
        }
        freeCoefs.back() /= coefs.back().back();
        coefs.back().back() = 1;
    }

    std::vector<double> reverseGaus() {
        column_t x(coefs[0].size());
        for (int i = coefs[0].size() - 1; i >= 0; --i) {
            double sum = 0;
            for (size_t j = i + 1; j < coefs[0].size(); ++j) {
                sum += coefs[i][j] * x[j];
            }
            x[i] = freeCoefs[i] - sum;
        }
        return x;
    }

};




void printVector(column_t x) {
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << "x" << i + 1 << " =" << std::setw(8) << std::setprecision(4) << x[i] << std::endl;
    }
    std::cout << std::endl;
}

void printRightAnswer(matrix_t a, column_t x) {
    for (size_t i = 0; i < a.size(); ++i) {
        double sumRow = 0; 
        
        for (size_t j = 0; j < a[0].size(); ++j) {
            sumRow += a[i][j] * x[j];
        }
        std::cout << "b" << i + 1 << " =" << std::setw(8) << std::setprecision(4) << sumRow << std::endl;
    }
    std::cout << std::endl;
}

 //output matrix
void printMatrix(Matrix a) {
    for (size_t i = 0; i < a.getA().size(); ++i) {
        for (size_t j = 0; j < a.getA()[0].size(); ++j) {
            std::cout << std::setw(8) << std::setprecision(4) << a.getA()[i][j] << " ";
        }
        std::cout << "|" << std::setprecision(4) << std::setw(8) << a.getB()[i];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}




int main() {
    std::vector <column_t> a = {{-0.512, -0.788, -0.495, -0.363, -0.793, 1.032},
                                { 0.570,  0.379,  1.054,  0.697,  0.269, 0.034},
                                {-0.187, -1.369,  0.119,  0.208, -1.105, 0.467},
                                { 0.863,  0.710, -0.877,  1.164, -0.867,-0.168},
                                { 1.101,  0.914, -0.976,  1.227, -0.580, 0.284},
                                {-0.443,  0.297,  1.234,  0.484,  0.849, 0.619}
                                        };
                                            
    column_t b = { 0.424, -0.005,  0.939, -0.589, -0.588, -0.433};

    Matrix test(a, b);
    
    printMatrix(test);
    test.forwardRunGaus();
    printMatrix(test);
    
    column_t x = test.reverseGaus();
    printVector(x);
    
    printRightAnswer(a, x);

}
