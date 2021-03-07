#include <iostream>
#include <iomanip> 
#include <vector>

using column_t = std::vector<double>;
using matrix_t = std::vector<std::vector<double>>;

class Matrix {

    /*Class Matrix for solve -> System Line Algebraical the Equations
 
    :a:      ->  2 dimension vector(Matrix)
    :b:      ->  1 dimension vector(the Equations)
 
    */

private:
    matrix_t a;
    column_t b;

public:
    //constructor
    Matrix(const matrix_t &a, const column_t &b) : a(a), b(b) {}

    //output matrix
    void getMatrix() {
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                std::cout << std::setw(8) << std::setprecision(4) << a[i][j] << " ";
            }
            std::cout << "|" << std::setprecision(4) << std::setw(8) << b[i];
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /*
 
    a[0].size ==== count column(only go on diagonal - important!!! )
    :k:  ->  k-column, and from k to vector.size  
     
     */   
    int getHeadElementColumn(int k) {
        for (size_t i = k; i < a.size(); ++i) {
            if (a[i][k] != 0) {
                return i;
            }
        }
        return -1;
    }

    void groundingColumn(int k) {

        // :coef:  ->  coefficient first addendum (in k-row)
        double coef = a[k][k];

        for (size_t m = k; m < a.size(); ++m) {
            a[k][m] /= coef;
        }
        b[k] /= coef;

        for (size_t i = k + 1; i < a.size(); ++i) {
            double coefficient = a[i][k] / a[k][k];
            for (size_t j = k; j < a[0].size(); ++j) {
                a[i][j] = a[i][j] - (coefficient * a[k][j]);
            }
            b[i] = b[i] - (coefficient * b[k]);
        }   
    }

    //getting vector a
    matrix_t& getA() {
        return a;
    }

    //getting vector b
    column_t& getB() {
        return b;
    }

};


Matrix forwardRunGaus(Matrix &test) {
    for (size_t i = 0; i < test.getA().size(); ++i) {
        test.getA()[test.getHeadElementColumn(i)].swap(test.getA()[i]); // swap rows to the surface
        test.groundingColumn(i);
    }
    test.getB().back() /= test.getA().back().back();
    test.getA().back().back() = 1;

    return test;
}

column_t reverseGaus(Matrix test) {
    column_t x(test.getA()[0].size());
    for (int i = test.getA()[0].size() - 1; i >= 0; --i) {
        double sum = 0;
        for (size_t j = i + 1; j < test.getA()[0].size(); ++j) {
            sum += test.getA()[i][j] * x[j];
        }
        x[i] = test.getB()[i] - sum;
    }
    return x;
}

void outputVector(column_t x) {
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << "x" << i + 1 << " =" << std::setw(8) << std::setprecision(4) << x[i] << std::endl;
    }
    std::cout << std::endl;
}

void checkingAnswer(matrix_t a, column_t x) {
    for (size_t i = 0; i < a.size(); ++i) {
        double sumRow = 0; 
        
        for (size_t j = 0; j < a[0].size(); ++j) {
            sumRow += a[i][j] * x[j];
        }
        std::cout << "b" << i + 1 << " =" << std::setw(8) << std::setprecision(4) << sumRow << std::endl;
    }
    std::cout << std::endl;
}





int main() {
    std::vector <column_t> a = { {-0.512, -0.788, -0.495, -0.363, -0.793, 1.032},
                                            { 0.570,  0.379,  1.054,  0.697,  0.269, 0.034},
                                            {-0.187, -1.369,  0.119,  0.208, -1.105, 0.467},
                                            { 0.863,  0.710, -0.877,  1.164, -0.867,-0.168},
                                            { 1.101,  0.914, -0.976,  1.227, -0.580, 0.284},
                                            {-0.443,  0.297,  1.234,  0.484,  0.849, 0.619}
                                        };
                                            
    column_t               b = { 0.424, -0.005,  0.939, -0.589, -0.588, -0.433};

    Matrix test(a, b);
    
    test.getMatrix();
    forwardRunGaus(test).getMatrix();
    
    column_t x = reverseGaus(test);
    outputVector(x);
    
    checkingAnswer(a, x);

}
