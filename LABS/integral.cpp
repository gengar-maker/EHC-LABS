// lab1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <ctime>

#include <chrono>
using namespace std;
using namespace std::chrono;


#define NUM 5


double refer = 2.094395;

double integral(int q, double h) {
    double sum = 0;

    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    for (int i = 0; i < q; i++) {
        sum = sum + (4 / sqrt(4 - pow((h * i + h / 2), 2))) * h;
    }
    high_resolution_clock::time_point t2 = high_resolution_clock::now();

    duration<double> duration = (t2 - t1);
    cout << "Duration is: " << duration.count() << " seconds" << endl;
    return sum;
}

int main()
{
    double a = 0;
    double b = 1;
    double res;
    int   q[NUM] = { 10000, 100000, 1000000, 10000000, 100000000 };
    double h[NUM];
    for (int i = 0; i < NUM; i++) {
        h[i] = (b - a) / (double)(q[i]);
        printf("q = %i \n", q[i]);
        printf("h = %f \n", h[i]);
        res = integral(q[i], h[i]);
        printf("res = %f \n", res);
        printf("err = %e \n\n\n", abs(res - refer));
    }
}


