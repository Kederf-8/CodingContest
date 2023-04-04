#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class MaxHeap
{
public:
    T **queue1, **queue2, **queue3;
    int heapsize, queueLength, heapifyCalls;
    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) | 1; }
    int parent(int i) { return i >> i; }
    void printKey(int i) const { out << "(" << *queue1[i] << " " << *queue2[i] << " " << *queue3[i] << ") "; }

    MaxHeap(T **q1, T **q2, T **q3, int size)
    {
        queue1 = q1;
        queue2 = q2;
        queue3 = q3;
        heapsize = size;
        queueLength = size + 1;
        heapifyCalls = 0;
    }

    void print()
    {
        out << heapifyCalls << " ";
        for (int i = 1; i <= heapsize; i++)
            printKey(i);
        out << endl;
    }

    void swap(int i, int j)
    {
        T *tmp = queue1[i];
        queue1[i] = queue1[j];
        queue1[j] = tmp;

        tmp = queue2[i];
        queue2[i] = queue2[j];
        queue2[j] = tmp;

        tmp = queue3[i];
        queue3[i] = queue3[j];
        queue3[j] = tmp;
    }

    void heapify(int i)
    {
        if (i == 0)
            return;
        while (i <= heapsize)
        {
            if (heapsize > 0)
                heapifyCalls++;

            int l = left(i);
            int r = right(i);
            int x = i;

            if (l <= heapsize && *queue1[x] <= *queue1[l])
            {
                if (*queue1[x] < *queue1[l] || (*queue1[x] == *queue1[l] && *queue2[x] < *queue2[l]) || (*queue1[x] == *queue1[l] && *queue2[x] == *queue2[l] && *queue3[x] < *queue3[l]))
                    x = l;
            }

            if (r <= heapsize && *queue1[x] <= *queue1[r])
            {
                if (*queue1[x] < *queue1[r] || (*queue1[x] == *queue1[r] && *queue2[x] < *queue2[r]) || (*queue1[x] == *queue1[r] && *queue2[x] == *queue2[r] && *queue3[x] < *queue3[r]))
                    x = r;
            }

            if (x == i)
                break;

            swap(i, x);
            i = x;
        }
    }

    void buildMaxHeap()
    {
        for (int i = heapsize / 2; i > 0; i--)
            heapify(i);
    }

    void extract()
    {
        if (heapsize == 0)
            return;
        heapsize--;
        swap(1, heapsize + 1);
        heapify(1);
    }

    void heapsort()
    {
        int nodes_number = heapsize;
        for (int i = 0; i < nodes_number; i++)
            extract();
        heapsize = nodes_number;
    }
};

template <class T>
class Task
{
public:
    Task(int size)
    {
        MaxHeap<T> *heap;
        T **q1 = new T *[size];
        T **q2 = new T *[size];
        T **q3 = new T *[size];

        for (int i = 1; i <= size; i++)
        {
            char c;
            T v1, v2, v3;

            in >> c; // '('
            in >> v1;
            // in >> c; // ','
            in >> v2;
            // in >> c; // ','
            in >> v3;
            in >> c; // ')'

            q1[i] = new T(v1);
            q2[i] = new T(v2);
            q3[i] = new T(v3);
        }

        heap = new MaxHeap<T>(q1, q2, q3, size);

        heap->buildMaxHeap();
        heap->heapsort();
        heap->print();
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string type;
        in >> type;

        int n;
        in >> n;

        if (type == "int")
            Task<int> *t = new Task<int>(n);
        if (type == "double")
            Task<double> *t = new Task<double>(n);
        if (type == "bool")
            Task<bool> *t = new Task<bool>(n);
        if (type == "char")
            Task<char> *t = new Task<char>(n);
    }
    return 0;
}