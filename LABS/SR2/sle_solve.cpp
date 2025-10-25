#include <vector>
#include <iostream>
#include <random>
#include <string>

#include <chrono>

typedef double type;

class Gauss
{
    type** coefs;
    type* free_term;
    std::vector<type> variables;
    int n, m;

public:
    Gauss(int _n, int _m, type **_coefs, type *_free_terms)
        : n(_n),
          m(_m),
          coefs(_coefs),
          variables(_n),
          free_term(_free_terms)
    {}
    double solve()
    {
        std::chrono::time_point start = std::chrono::high_resolution_clock::now();
        forward();
        backward();
        get_answer();
        std::chrono::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_time = end - start;
        return elapsed_time.count();
    }

    void forward()
    {
        for (int i = 0; i < m; ++i)
        {
            type lead_elem = coefs[i][i];
            for (int j = 0; j < n; ++j)
            {
                coefs[i][j] = coefs[i][j] / lead_elem;
            }
            free_term[i] = free_term[i] / lead_elem;
            for (int j = i + 1; j < m; ++j)
            {
                type coef = coefs[j][i] / coefs[i][i];
                for (int k = 0; k < n; ++k)
                {
                    coefs[j][k] = coefs[j][k] - coefs[i][k] * coef;
                }
                free_term[j] = free_term[j] - free_term[i] * coef;
            }
        }
    }
    void backward()
    {
        for (int i = m - 1; i >= 0; --i)
        {
            type lead_elem = coefs[i][i];
            for (int j = n - 1; j >= 0; --j)
            {
                coefs[i][j] = coefs[i][j] / lead_elem;
            }
            free_term[i] = free_term[i] / lead_elem;
            for (int j = i - 1; j >= 0; --j)
            {
                type coef = coefs[j][i] / coefs[i][i];
                for (int k = n - 1; k >= 0; --k)
                {
                    coefs[j][k] = coefs[j][k] - coefs[i][k] * coef;
                }
                free_term[j] = free_term[j] - free_term[i] * coef;
            }
        }
    }

    void get_answer()
    {
        for (int i = 0; i < n; ++i)
        {
            variables[i] = free_term[i];
        }
    }

    type &operator[](int ind)
    {
        return variables[ind];
    }
};

bool correctness_test_run()
{
    type line_1[] = {1, 2, 3};
    type line_2[] = {3, 5, 7};
    type line_3[] = {1, 3, 4};

    type free_terms[] = {3, 0, 1};

    type answer[] = {-4, -13, 11};

    type *coefs[] = {line_1, line_2, line_3};

    Gauss method{3, 3, coefs, free_terms};
    double test_time = method.solve();

    for (int i = 0; i < 3; ++i)
    {
        if (std::abs(answer[i] - method[i]) > 1e-9)
        {
            std::cout << "Small test failed. Calculations are incorrect.\n";
            return false;
        }
    }
    std::cout << "Small test passed.\n";
    return true;
}

bool performance_run(int task_size)
{
    type **coefs = new type *[task_size];
    type *free_term = new type[task_size];

    std::mt19937 generator{};

    for (int i = 0; i < task_size; ++i)
    {
        coefs[i] = new type[task_size];
        for (int j = 0; j < task_size; ++j)
        {
            coefs[i][j] = generator();
            if (i == j)
            {
                while (coefs[i][j] == 0)
                {
                    coefs[i][j] = generator();
                }
            }
        }
        free_term[i] = generator();
    }

    Gauss method(task_size, task_size, coefs, free_term);
    double seq_time = method.solve();
    std::cout << "Elapsed sequential Gaussian time: " << seq_time << " seconds\n";

    delete[] (free_term);
    for (int i = 0; i < task_size; ++i)
    {
        delete[] (coefs[i]);
    }
    delete[] (coefs);
    return true;
}

int main(int argc, char **argv)
{
    int task_size = 2000;

    if (argc > 1)
    {
        task_size = std::stoi(argv[1]);
        std::cout << "Task size set to: " << task_size << std::endl;
    }
    else
    {
        std::cout << "Using default task size: " << task_size << std::endl;
    }
    correctness_test_run();
    performance_run(task_size);
}
