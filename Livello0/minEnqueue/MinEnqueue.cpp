#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class MinHeap
{
public:
    T **queue;
    int heapsize, queueLength;

    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) | 1; }
    int parent(int i) { return i >> 1; }
    void printKey(int i) const { out << *queue[i] << " "; }

    MinHeap(int size)
    {
        queue = new T *[size + 1];
        heapsize = 0;
        queueLength = size + 1;
    }

    void print() const
    {
        for (int i = 1; i <= heapsize; i++)
            printKey(i);
        out << endl;
    }

    void swap(int i, int j)
    {
        T *tmp = queue[i];
        queue[i] = queue[j];
        queue[j] = tmp;
    }

    void moveUpKey(int i)
    {
        if (heapsize <= 1)
            return;
        while (i > 1)
        {
            int p = parent(i);
            if (p > 0 && *queue[i] < *queue[p])
            {
                swap(i, p);
                i = p;
            }
            else
                return;
        }
    }

    MinHeap<T> *enqueue(T k)
    {
        heapsize++;
        queue[heapsize] = new T(k);
        moveUpKey(heapsize);
        return this;
    }
};

template <class T>
class Task
{
public:
    Task(int size)
    {
        MinHeap<T> *heap = new MinHeap<T>(size);

        for (int i = 0; i < size; i++)
        {
            T v;
            in >> v;

            heap->enqueue(v);
        }
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