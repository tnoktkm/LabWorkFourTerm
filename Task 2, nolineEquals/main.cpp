#include <iostream>
#include <cmath>
#include <iomanip>

double fx(double x){
    return sin(x + 2) - 1.5;
}

double fy(double y){
    return 0.5 - cos(y - 2);
}



int main() {
double e = 1e-6;
int n = 0;
double x1 = 1, x2, y0;
double delta;

    do{
    n++;

    y0 = fx(x1);
    x2 = fy(y0);
    y0 = fx(x2);
    x1 = fy(y0);
    delta = fabs(x1-x2);
    
    std::cout << std::setprecision(4) << std::setw(12) << delta << "   x1 = " << x1 << "   x2 = " << x2 << std::endl;
    }while(delta > e);

    std::cout << std::endl;
    std::cout << std::setprecision(4) << std::setw(12) << "We find a solve for "<< n <<" iterations, in x0 = " << x1 << "   y0 =" << y0 << std::endl;
    return 0;
}