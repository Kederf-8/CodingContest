#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

class Array
{
public:
    double *A1, *A2, *B1, *B2;
    int *C;
    int arraySize;

    Array(double *a1, double *a2, int size)
    {
        A1 = a1;
        A2 = a2;
        arraySize = size;
        B1 = new double[size];
        B2 = new double[size];
    }

    double min()
    {
        double min = A1[0];
        for (int i = 1; i < arraySize; i++)
        {
            if (min > A1[i])
                min = A1[i];
        }
        return min;
    }

    double max()
    {
        double max = A1[0];
        for (int i = 1; i < arraySize; i++)
        {
            if (max < A1[i])
                max = A1[i];
        }
        return max;
    }

    void countingSort()
    {
        if (arraySize <= 1)
            return;

        int M = max() * 10, m = min() * 10;
        int k = M - m + 1;

        C = new int[k];

        for (int i = 0; i < k; i++)
            C[i] = 0;

        for (int i = 0; i < arraySize; i++)
            C[(int(A1[i] * 10)) - m]++;

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
            B1[C[(int(A1[i] * 10)) - m]] = A1[i];
            B2[C[(int(A1[i] * 10)) - m]] = A2[i];
            C[(int(A1[i] * 10)) - m]++;
        }

        for (int i = 0; i < arraySize; i++)
            out << "(" << B1[i] << " " << B2[i] << ") ";
        out << endl;

        delete[] A1;
        delete[] A2;
        delete[] B1;
        delete[] B2;
        delete[] C;
    }
};

class Task
{
public:
    Task(int size)
    {
        double *a1 = new double[size];
        double *a2 = new double[size];

        for (int i = 0; i < size; i++)
        {
            char c;
            double v1, v2;

            in >> c;
            in >> v1;
            in >> v2;
            in >> c;

            a1[i] = v1;
            a2[i] = v2;
        }

        Array *array = new Array(a1, a2, size);

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