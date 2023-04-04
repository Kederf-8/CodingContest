#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

class Array
{
public:
    int *A, *B, *C;
    int arraySize;

    Array(int *a, int size)
    {
        A = a;
        B = new int[size];
        arraySize = size;
    }

    int max()
    {
        int max = A[0];
        for (int i = 1; i < arraySize; i++)
        {
            if (max < A[i])
                max = A[i];
        }
        return max;
    }

    int min()
    {
        int min = A[0];
        for (int i = 1; i < arraySize; i++)
        {
            if (min > A[i])
                min = A[i];
        }
        return min;
    }

    void countingSort()
    {
        if (arraySize <= 1)
            return;

        int M = max();
        int m = min();
        int k = M - m + 1;
        int *C = new int[k];

        for (int i = 0; i < k; i++)
            C[i] = 0;

        for (int i = 0; i < arraySize; i++)
            C[A[i] - m]++;

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
            B[C[A[i] - m]] = A[i];
            C[A[i] - m]++;
        }

        for (int i = 0; i < arraySize; i++)
            out << B[i] << " ";

        out << endl;
    }
};

class Task
{
public:
    Task(int size)
    {
        int *a = new int[size];

        for (int i = 0; i < size; i++)
        {
            int v;
            in >> v;
            a[i] = v;
        }

        Array *array = new Array(a, size);

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