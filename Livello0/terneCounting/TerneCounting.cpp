#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

class Array
{
public:
    double *A1, *A2, *A3, *B1, *B2, *B3;
    int *C;
    int arraySize;

    Array(double *a1, double *a2, double *a3, int size)
    {
        A1 = a1;
        A2 = a2;
        A3 = a3;
        arraySize = size;
        B1 = new double[size];
        B2 = new double[size];
        B3 = new double[size];
    }

    double min()
    {
        double min = A1[0];
        for (int i = 1; i < arraySize; i++)
        {
            if (A1[i] < min)
                min = A1[i];
        }
        return min;
    }

    double max()
    {
        double max = A1[0];
        for (int i = 1; i < arraySize; i++)
        {
            if (A1[i] > max)
                max = A1[i];
        }
        return max;
    }

    void countingSort()
    {
        if (arraySize <= 1)
            return;

        int k, m, M;
        m = min() * 10;
        M = max() * 10;
        k = M - m + 1;

        C = new int[k];
        for (int i = 0; i < k; i++)
            C[i] = 0;

        for (int i = 0; i < arraySize; i++)
            C[int((A1[i] * 10) - m)]++;

        int tmp = C[0];
        C[0] = 0;
        for (int i = 1; i < k; i++)
        {
            int t = C[i];
            C[i] = C[i - 1] + tmp;
            tmp = t;
        }

        for (int i = 0; i < k; i++)
            out << C[i] << " ";

        for (int i = 0; i < arraySize; i++)
        {
            B1[C[int((A1[i] * 10) - m)]] = A1[i];
            B2[C[int((A1[i] * 10) - m)]] = A2[i];
            B3[C[int((A1[i] * 10) - m)]] = A3[i];
            C[int((A1[i] * 10) - m)]++;
        }

        for (int i = 0; i < arraySize; i++)
            out << "(" << B1[i] << " " << B2[i] << " " << B3[i] << ") ";
        out << endl;
    }
};

class Task
{
public:
    Task(int size)
    {
        double *a1 = new double[size];
        double *a2 = new double[size];
        double *a3 = new double[size];

        for (int i = 0; i < size; i++)
        {
            double v1, v2, v3;
            char c;

            in >> c; //'('
            in >> v1;
            // in >> c; //','
            in >> v2;
            // in >> c; //','
            in >> v3;
            in >> c; //')'

            a1[i] = v1;
            a2[i] = v2;
            a3[i] = v3;
        }

        Array *array = new Array(a1, a2, a3, size);

        array->countingSort();
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int n;
        in >> n;
        Task *t = new Task(n);
    }
    return 0;
}