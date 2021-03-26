#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional>

double fx(double x){
    return sin(x + 2) - 1.5;
}

double fy(double y){
    return 0.5 - cos(y - 2);
}

struct ComputationResult {
  double x;  // x-coordinate intersection
  double y;  // y-coordinate intersection
  size_t iterations_number = 0;  //count iterations that you need for accuracy.
  
};

ComputationResult FindIntersection(std::function<void(double)> first, std::function<void(double)> second, double eps) {
    
    double x1 = 1, x2;  //x1-start approximation, x2 - help variable.
    double y0;          //y0-point intersection in y-axis
    double delta;       //delta-current error approximation
    ComputationResult result;
    
    do{
    result.iterations_number++;

    y0 = fx(x1);
    x2 = fy(y0);
    y0 = fx(x2);
    x1 = fy(y0);
    delta = fabs(x1-x2);
    
   }while(delta > eps);

   result.x = x1;
   result.y = y0;

   return result;
}


int main() {
    double eps = 1e-6;  //bottom border approximation
    ComputationResult result = FindIntersection(fx, fy, eps);   //finding intersection two function with :eps: approximation.
    std::cout << result.x << " " << result.y << std::endl;

    return 0;
}
