#include <iostream>
#include <cmath>
#include <ctime>
#include <string>

#include <chrono>

class Solver {
private:
// double(*m_func)(double) ;

double m_func(double x) {
    double y;
    y = 4. / sqrt(4. - pow((x), 2));
    return y;
}

double mid_rectangles(double a, double h, size_t q) {
    double result{};

    for(size_t i = 0; i < q; ++i) {
        result += m_func(a + h * i + h / 2) * h;
    }
    return result;
}

public:
Solver(double(*func)(double))
// : m_func(func)
{}

double integrate(double a, double b, size_t q) {
    double h = (b - a) / q;
    return mid_rectangles(a, h, q);
}
};

double func(double x) {
    double y;
    y = 4. / sqrt(4. - pow((x), 2));
    return y;
}

double refer = 2.094395;

int main(int argc, char** argv)
{
    size_t rects = 0;
    if (argc != 2) {
        std::cerr << "Usage: integral.exe iterations [default is 1'000'000].\n";
        rects = 1'000'000;
    } else {
        rects = std::stoll(argv[1]);
    }

    std::cout << "Integral solver\n";
    double a = 0;
    double b = 1;

    double  res;
    Solver  sol{func};
    std::chrono::time_point t_start = std::chrono::high_resolution_clock::now();
    double result = sol.integrate(a, b, rects);
    std::chrono::time_point t_end = std::chrono::high_resolution_clock::now();
    
    const std::chrono::duration<double> elapsed_time = t_end - t_start;

    std::cout << "Elapsed time: " << elapsed_time.count() << std::endl;
    
    std::cout << "Reference answer: " << refer << std::endl;
    std::cout << "Answer: " << result << std::endl;
    std::cout << "Delta: " << std::abs(refer - result) << std::endl;

    return 0;
}