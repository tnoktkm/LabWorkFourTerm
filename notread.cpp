#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>

std::vector<int> absMaxElement(std::vector<std::vector<double>> matrix) {
    size_t maximum = 0;
    size_t x, y;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = i; j < matrix.size(); ++j) {
            if (i != j && abs(matrix[i][j]) > maximum) {
                x = i;
                y = j;
            }
        }
    }
    std::vector<int> ans;
    ans.push_back(x);
    ans.push_back(y);
    return ans;
}

double findFi (int i, int j, std::vector<std::vector<double>> matrix) {
    double p = (2*matrix[i][j]) / (matrix[i][i] - matrix[j][j]);
    double fi = (1.0/2.0) * atan(p);
    return fi;
}

void printMatrix(std::vector<std::vector<double>> a) {
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < a.size(); ++j) {
            std::cout << std::setw(8) << std::setprecision(4) << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::vector<std::vector<double>> multiplie(std::vector<std::vector<double>> a, std::vector<std::vector<double>> b) {
    std::vector<std::vector<double>> ans;
    ans.resize(a.size(), a.size());
        for(size_t i = 0; i < a.size(); ++i) {
            for(size_t j = 0; j < a.size(); ++j) {
                for (size_t k = 0; k < a.size(); ++k) {
                    ans[i][j] += a[i][k]*b[k][j];
                }
            }
        }
    return ans;
}

std::vector<std::vector<double>> returnv(double fi, int i, int j, int n) {
    std::vector<std::vector<double>> a;
    a.resize(n, n);
    
    for (size_t i = 0; i < n; ++i) {
        for size_t j = 0; j < n; ++j) {
            a[i][j] = 1;    
        }
    }
    a[i][i] = cos(fi);
    a[i][j] = -sin(fi);
    a[j][i] = sin(fi);
    a[j][j] = cos(fi);
}



int main() {
    std::vector<std::vector<double>> a = {{-0.512, -0.788, -0.363,  0.424, -2.579,  1.907, -0.863},
                                          {-0.788, -0.495,  2.483, -2.706, -3.007,  0.119, -2.566},
                                          {-0.363,  2.483, -2.244,  0.379,  0.034, -3.068, -0.877},
                                          { 0.424, -2.706,  0.379, -2.222, -0.005,  2.171,  1.164},
                                          {-2.579, -3.007,  0.034, -0.005,  3.088,  0.467,  2.409},
                                          { 1.907,  0.119, -3.068,  2.171,  0.467, -2.337,  3.108},
                                          {-0.863, -2.566, -0.877,  1.164,  2.409,  3.108,  2.687}};
    
                                                            
    
}
