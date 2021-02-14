#include <iostream>
#include <iomanip> 
#include <vector>

class Matrix {

    /*Class Matrix for solve -> System Line Algebraical the Equations
 
    :a:      ->  2 dimension vector(Matrix)
    :b:      ->  1 dimension vector(the Equations)
 
    */

private:
    std::vector<std::vector<double>> a;
    std::vector<double> b;

public:
    //constructor
    Matrix(const std::vector<std::vector<double>> &a, const std::vector<double> &b) : a(a), b(b) {}
        
    //output matrix
    void getMatrix() {
        for (size_t i = 0; i < a.size(); ++i) {
            for (size_t j = 0; j < a[0].size(); ++j) {
                std::cout << std::setw(8) << std::setprecision(4) << a[i][j] << " ";
            }
            std::cout << "|" << std::setprecision(4) << std::setw(8) << b[i];
            std::cout << std::endl;
        }
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
    std::vector<std::vector<double>>& getA() {
        return a;
    }

    //getting vector b
    std::vector<double>& getB() {
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

std::vector<double> reverseGaus(Matrix test) {
    std::vector<double> x(test.getA()[0].size());
    for (int i = test.getA()[0].size() - 1; i >= 0; --i) {
        double sum = 0;
        for (size_t j = i + 1; j < test.getA()[0].size(); ++j) {
            sum += test.getA()[i][j] * x[j];
        }
        x[i] = test.getB()[i] - sum;
    }
    return x;
}

void outputVector(std::vector<double> x) {
    for (size_t i = 0; i < x.size(); ++i) {
        std::cout << "x" << i + 1 << " =" << std::setw(8) << std::setprecision(4) << x[i] << std::endl;
    }
}




int main() {
    std::vector <std::vector<double>> a = { {1, 2, 4}, {4, 5, 4}, {3, 7, 3} };
    std::vector<double>               b = { 5, 6, 4 };

    Matrix test(a, b);

    forwardRunGaus(test).getMatrix();
    outputVector(reverseGaus(test));

}
