#include <iostream>
#include <iomanip> 
#include <vector>

class Matrix {

    /*Class Matrix for solve -> System Line Algebraical the Equations
 
    :a:      ->  2 dimension vector(Matrix)
    :b:      ->  1 dimension vector(the Equations)
 
    */

public:
    std::vector<std::vector<double>> a;
    std::vector<double> b;

    //constructor
    Matrix(std::vector<std::vector<double>> &a, std::vector<double> &b) {
        this->a = a;
        this->b = b;
    }

    //output matrix
    void getMatrix() {
        for (unsigned int i = 0; i < a.size(); ++i) {
            for (unsigned int j = 0; j < b.size(); ++j) {
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
        for (unsigned int i = k; i < a.size(); ++i) {
            if (a[i][k] != 0) {
                return i;
            }
        }
        return -1;
    }

    void groundingColumn(int k) {
        for (unsigned int i = k + 1; i < a.size(); ++i) {
            double coefficient = a[i][k] / a[k][k];
            for (unsigned j = 0; j < a[0].size(); ++j) {
                a[i][j] = a[i][j] - (coefficient * a[k][j]);
            }
            b[i] = b[i] - (coefficient * b[k]);
        }   
        //last transform
        b[b.size()-1] /= a[a.size()-1][a[0].size()-1];
    }

};


Matrix forwardRunGaus(Matrix &test) {
    for (unsigned int i = 0; i < test.a.size(); ++i) {
        test.a[test.getHeadElementColumn(i)].swap(test.a[i]); // swap rows to the surface
        test.groundingColumn(i);
    }

    //last transform
    test.a[test.a.size() - 1][test.a[0].size() - 1] = 1;

    return test;
}

std::vector<double> reverseGaus(Matrix test) {
    std::vector<double> x(test.a[0].size());
    for (int i = test.a[0].size() - 1; i >= 0; --i) {
        double sum = 0;
        for (unsigned int j = i + 1; j < test.a[0].size(); ++j) {
            sum += test.a[i][j] * x[j];
        }
        x[i] = test.b[i] - sum;
    }
    return x;
}

void outputVector(std::vector<double> x) {
    for (unsigned int i = 0; i < x.size(); ++i) {
        std::cout << "x" << i + 1 << " =" << std::setw(8) << std::setprecision(4) << x[i] << std::endl;
    }
}




int main() {
    std::vector <std::vector<double>> a = { {1, 2, 4, 4}, {4, 5, 4, 6}, {3, 7, 3, 9}, {14, 75, 23, 86} };
    std::vector<double>               b = { 5, 6, 4, 7 };

    Matrix test(a, b);

    forwardRunGaus(test).getMatrix();
    outputVector(reverseGaus(test));

}
