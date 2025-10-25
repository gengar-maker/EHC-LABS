#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>

#include <chrono>

class Solver {
protected:
    double func(float x) {
        return 4. / sqrt(4. - x * x);
    }

    double method(float a, float h, size_t i)
    {
        return func(a + h * i + h / 2) * h;
    }

public:
    Solver()
    {}
    virtual ~Solver() {}

    double integrate(float a, float b, size_t q) {
        double sum{};
        const float h = (b - a) / q;

        for (size_t i = 0; i < q; ++i) {
            sum += method(a, h, i);
        }
        return sum;
    }
};


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
    auto sol = Solver();

    const double refer = 2.09439510239319;
    
    const std::chrono::time_point t_start = std::chrono::high_resolution_clock::now();
    double result = sol.integrate(a, b, rects);
    const std::chrono::time_point t_end = std::chrono::high_resolution_clock::now();
    
    const std::chrono::duration<double> elapsed_time = t_end - t_start;

    std::cout << std::setprecision(16);
    std::cout << std::endl;
    std::cout << "Interval a = " << a << " b = " << b << std::endl;
    std::cout << "Elapsed time: " << elapsed_time.count() << std::endl;
    std::cout << "Reference answer: " << refer << std::endl;
    std::cout << "Answer: " << result << std::endl;
    std::cout << "Delta: " << std::abs(refer - result) << std::endl;

    return 0;
}