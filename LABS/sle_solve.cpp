#include <vector>
#include <iostream>
#include <omp.h>
#include <random>
#include <string>

typedef double type;

struct linear_system
{
    int vars, lines;
    std::vector<std::vector<type>> coefs;
    std::vector<type> free_term;
    std::vector<type> variables;
};

class Gauss
{
    std::vector<std::vector<type>> coefs;
    std::vector<std::vector<type>> coefs_tmp;
    std::vector<type> variables;
    std::vector<type> free_term;
    std::vector<type> free_term_tmp;
    int n, m;

    linear_system system;
    linear_system tmp_system;

public:
    Gauss(int _n, int _m, type **_coefs, type *_free_terms)
        : n(_n),
          m(_m),
          coefs(_m, std::vector<type>(_n)),
          coefs_tmp(_m, std::vector<type>(_n)),
          variables(_n),
          free_term(_m),
          free_term_tmp(_m)
    //   system({.vars = _n, .lines = _m, .coefs = std::vector(_m, std::vector<type>(_n)), .free_term = std::vector(_m), .variables = std::vector(_n)})
    {
        for (int i = 0; i < _m; ++i)
        {
            for (int j = 0; j < _n; ++j)
            {
                coefs[i][j] = coefs_tmp[i][j] = _coefs[i][j];
            }
            free_term[i] = free_term_tmp[i] = _free_terms[i];
        }
    }
    double solve()
    {
        double start{}, end{};
        start = omp_get_wtime();
        forward();
        backward();
        get_answer();
        end = omp_get_wtime();
        std::cout << "Elapsed sequential Gaussian time: " << end - start << " seconds\n";
        return end - start;
    }

    double solve_par()
    {
        double start{}, end{};
        start = omp_get_wtime();
        forward_par();
        backward_par();
        get_answer_par();
        end = omp_get_wtime();
        std::cout << "Elapsed parallel Gaussian time: " << end - start << " seconds\n";
        return end - start;
    }

    void forward()
    {
        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                coefs_tmp[i][j] = coefs_tmp[i][j] / coefs[i][i];
            }

            free_term_tmp[i] = free_term_tmp[i] / coefs[i][i];

            for (int j = i + 1; j < n; ++j)
            {
                type coef = coefs_tmp[j][i] / coefs_tmp[i][i];
                for (int k = 0; k < n; ++k)
                {
                    coefs_tmp[j][k] = coefs_tmp[j][k] - coefs_tmp[i][k] * coef;
                }
                free_term_tmp[j] = free_term_tmp[j] - free_term_tmp[i] * coef;
            }

            for (int k = 0; k < m; ++k)
            {
                for (int j = 0; j < n; ++j)
                {
                    coefs[k][j] = coefs_tmp[k][j];
                }
                free_term[k] = free_term_tmp[k];
            }
        }
    }
    void forward_par()
    {
        for (int i = 0; i < m; ++i)
        {
#pragma omp parallel for
            for (int j = 0; j < n; ++j)
            {
                coefs_tmp[i][j] = coefs_tmp[i][j] / coefs[i][i];
            }

            free_term_tmp[i] = free_term_tmp[i] / coefs[i][i];

#pragma omp parallel for
            for (int j = i + 1; j < n; ++j)
            {
                type coef = coefs_tmp[j][i] / coefs_tmp[i][i];
                for (int k = 0; k < n; ++k)
                {
                    coefs_tmp[j][k] = coefs_tmp[j][k] - coefs_tmp[i][k] * coef;
                }
                free_term_tmp[j] = free_term_tmp[j] - free_term_tmp[i] * coef;
            }

#pragma omp parallel for
            for (int k = 0; k < m; ++k)
            {
                for (int j = 0; j < n; ++j)
                {
                    coefs[k][j] = coefs_tmp[k][j];
                }
                free_term[k] = free_term_tmp[k];
            }
        }
    }
    void backward_par()
    {
        for (int i = m - 1; i >= 0; --i)
        {
#pragma omp parallel for
            for (int j = n - 1; j >= 0; --j)
            {
                coefs_tmp[i][j] = coefs_tmp[i][j] / coefs[i][i];
            }
            free_term_tmp[i] = free_term_tmp[i] / coefs[i][i];

#pragma omp parallel for
            for (int j = i - 1; j >= 0; --j)
            {
                type coef = coefs_tmp[j][i] / coefs_tmp[i][i];
                for (int k = n - 1; k >= 0; --k)
                {
                    coefs_tmp[j][k] = coefs_tmp[j][k] - coefs_tmp[i][k] * coef;
                }
                free_term_tmp[j] = free_term_tmp[j] - free_term_tmp[i] * coef;
            }
        }
    }
    void backward()
    {
        for (int i = m - 1; i >= 0; --i)
        {
            for (int j = n - 1; j >= 0; --j)
            {
                coefs_tmp[i][j] = coefs_tmp[i][j] / coefs[i][i];
            }
            free_term_tmp[i] = free_term_tmp[i] / coefs[i][i];

            for (int j = i - 1; j >= 0; --j)
            {
                type coef = coefs_tmp[j][i] / coefs_tmp[i][i];
                for (int k = n - 1; k >= 0; --k)
                {
                    coefs_tmp[j][k] = coefs_tmp[j][k] - coefs_tmp[i][k] * coef;
                }
                free_term_tmp[j] = free_term_tmp[j] - free_term_tmp[i] * coef;
            }
        }
    }

    void get_answer()
    {
        for (int i = 0; i < n; ++i)
        {
            variables[i] = free_term_tmp[i];
        }
    }

    void get_answer_par()
    {
#pragma omp parallel for
        for (int i = 0; i < n; ++i)
        {
            variables[i] = free_term_tmp[i];
        }
    }

    type &operator[](int ind)
    {
        return variables[ind];
    }
};

bool correctness_test_run()
{
    type line_1[] = {7, 1, 0};
    type line_2[] = {2, -10, 4};
    type line_3[] = {-10, -1, -8};

    type free_terms[] = {-47, -74, 148};

    type answer[] = {-7, 2, -10};

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

    omp_set_num_threads(4);

    Gauss method(task_size, task_size, coefs, free_term);
    double seq_time = method.solve();

    Gauss method_par(task_size, task_size, coefs, free_term);
    double par_time = method_par.solve_par();

    for (int i = 0; i < task_size; ++i)
    {
        if (std::abs(method[i] - method_par[i]) > 1e-9)
        {
            std::cout << "Error while calculating\n";
            delete[] (free_term);
            for (int i = 0; i < task_size; ++i)
            {
                delete[] (coefs[i]);
            }
            delete[] (coefs);
            return false;
        }
    }
    std::cout << "All correct\n";

    std::cout << "Speedup: " << seq_time / par_time << std::endl;
#pragma omp parallel
    {
        if (omp_get_thread_num() == 0)
            std::cout << "Num threads: " << omp_get_num_threads() << std::endl;
    }

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
    int task_size = 100;

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
