#include <iostream>
#include <cmath>
#include <string>

#include <chrono>

class Solver {
private:

double(*m_func)(float);

void kahan_sum(double func_ret, double& sum, double& corr) {
    const double y = func_ret - corr;
    const double t = sum + y;
    corr = (t - sum) - y;
    sum = t;
}

double mid_rectangles(float a, float h, size_t q) {
    double result{};
    double c{};

    for(size_t i = 0; i < q; ++i) {
        kahan_sum(m_func(a + h * i + h / 2) * h, result, c);
    }
    return result;
}

public:
Solver(double(*func)(float))
: m_func(func) {}

float integrate(float a, float b, size_t q) {
    const float h = (b - a) / q;
    return mid_rectangles(a, h, q);
}
};

double func(float x) {
    return 4. / sqrt(4. - pow(x, 2));
}

const double refer = 2.09439510239319;

int main(int argc, char** argv)
{
    std::cout << "Integral solver\n\n";
    size_t rects = 0;
    if (argc != 2) {
        std::cerr << "Usage: integral.exe iterations [default is 1000000000].\n";
        rects = 1000000000;
    } else {
        rects = std::stoll(argv[1]);
    }

    const float a = 0;
    const float b = 1;

    Solver  sol{func};
    
    const std::chrono::time_point t_start = std::chrono::high_resolution_clock::now();
    double result = sol.integrate(a, b, rects);
    const std::chrono::time_point t_end = std::chrono::high_resolution_clock::now();
    
    const std::chrono::duration<double> elapsed_time = t_end - t_start;

    std::cout << "Elapsed time: " << elapsed_time.count() << std::endl;
    std::cout << "Reference answer: " << refer << std::endl;
    std::cout << "Answer: " << result << std::endl;
    std::cout << "Delta: " << std::abs(refer - result) << std::endl;

    return 0;
}