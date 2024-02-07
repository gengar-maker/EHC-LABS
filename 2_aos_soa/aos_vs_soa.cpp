#include <time.h>
#include <iostream>

#include <random>
#include <chrono>

using namespace std;

struct Object
{
    char opts_a[129];
    int opts_b[3];
    float opts_c[3];
};

struct Object_soa
{
    char *opts_a;                       // 11 * num of objects
    int *opts_b0, *opts_b1, *opts_b2;   // 3 * num of objects
    float *opts_c0, *opts_c1, *opts_c2; // 3 * num of objects
};

void init_objects(int arrSize, Object *array)
{
    mt19937 gen;
    int i;
    for (i = 0; i < arrSize; i++)
    {
        strcpy(array[i].opts_a, "some name");
        array[i].opts_b[0] = gen();
        array[i].opts_b[1] = gen();
        array[i].opts_b[2] = gen();
        array[i].opts_c[0] = static_cast<float>(gen());
        array[i].opts_c[1] = static_cast<float>(gen());
        array[i].opts_c[2] = static_cast<float>(gen());
    }
}

void init_objects_soa(int arrSize, Object_soa &obj)
{
    mt19937 gen;
    int i;
    for (i = 0; i < arrSize; i++)
    {
        strcpy(obj.opts_a + i * 129, "some name");
        obj.opts_b0[i] = gen();
        obj.opts_b1[i] = gen();
        obj.opts_b2[i] = gen();
        obj.opts_c0[i] = static_cast<float>(gen());
        obj.opts_c1[i] = static_cast<float>(gen());
        obj.opts_c2[i] = static_cast<float>(gen());
    }
}

void compare_objects(int arrSize, Object *array)
{
    float max_dist = -1.f;

    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < arrSize; j++)
        {
            float d_0 = array[i].opts_c[0] - array[j].opts_c[0];
            float d_1 = array[i].opts_c[1] - array[j].opts_c[1];
            float d_2 = array[i].opts_c[2] - array[j].opts_c[2];

            max_dist = max(max_dist, sqrt(d_0 * d_0 + d_1 * d_1 + d_2 * d_2));
        }
    }

    cout << "Max dist = " << max_dist << endl;
}

void compare_objects_soa(int arrSize, Object_soa &obj)
{
    float max_dist = -1.f;

    for (int i = 0; i < arrSize; i++)
    {
        for (int j = 0; j < arrSize; j++)
        {
            float d_0 = obj.opts_c0[i] - obj.opts_c0[j];
            float d_1 = obj.opts_c1[i] - obj.opts_c1[j];
            float d_2 = obj.opts_c2[i] - obj.opts_c2[j];
            max_dist = max(max_dist, sqrt(d_0 * d_0 + d_1 * d_1 + d_2 * d_2));
        }
    }

    cout << "Max dist = " << max_dist << endl;
}

void comp_task(int argc, char *argv[])
{
    int num = 0;

    if (argc != 2)
    {
        cerr << "Usage: 2_aos_soa.exe arraySize [default is 1024].\n";
        num = 1024;
    }
    else
    {
        num = atoi(argv[1]);
        if (num < 0)
        {
            cerr << "Array dimensions must be positive; setting it to 1024. \n"
                 << endl;
            num = 1024;
        }
    }

    Object *objs = new Object[num];

    Object_soa obj_soa;
    obj_soa.opts_a = new char[num * 129];
    obj_soa.opts_b0 = new int[num];
    obj_soa.opts_b1 = new int[num];
    obj_soa.opts_b2 = new int[num];
    obj_soa.opts_c0 = new float[num];
    obj_soa.opts_c1 = new float[num];
    obj_soa.opts_c2 = new float[num];

    init_objects(num, objs);
    init_objects_soa(num, obj_soa);

    cout << "Size: " << num << endl;
    auto start = chrono::high_resolution_clock::now();
    compare_objects(num, objs);
    auto stop = chrono::high_resolution_clock::now();

    cout << "Elapsed time aos = " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds" << endl;

    start = chrono::high_resolution_clock::now();
    compare_objects_soa(num, obj_soa);
    stop = chrono::high_resolution_clock::now();

    cout << "Elapsed time soa = " << (chrono::duration_cast<chrono::milliseconds>(stop - start).count()) << " mseconds" << endl;

    delete[] objs;

    delete[] obj_soa.opts_a;
    delete[] obj_soa.opts_b0;
    delete[] obj_soa.opts_b1;
    delete[] obj_soa.opts_b2;
    delete[] obj_soa.opts_c0;
    delete[] obj_soa.opts_c1;
    delete[] obj_soa.opts_c2;
}

int main(int argc, char *argv[])
{
    comp_task(argc, argv);
    return 0;
}
