#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class MinHeap
{
public:
    T **queue;
    int heapsize, queueLength, heapifyCalls;

    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) | 1; }
    int parent(int i) { return i >> 1; }
    void printKey(int i) const { out << *queue[i] << " "; }

    MinHeap(T **q, int size)
    {
        queue = q;
        heapsize = size;
        queueLength = size + 1;
        heapifyCalls = 0;
    }

    void print() const
    {
        out << heapifyCalls << " ";
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

    void heapify(int index)
    {
        int i = index;
        while (i <= heapsize)
        {
            if (heapsize > 0)
                heapifyCalls++;
            int l = left(i);
            int r = right(i);
            int x = i;
            if (l <= heapsize && *queue[x] > *queue[l])
                x = l;
            if (r <= heapsize && *queue[x] > *queue[r])
                x = r;
            if (x == i)
                break;
            swap(i, x);
            i = x;
        }
    }

    void buildMinHeap()
    {
        for (int i = heapsize / 2; i > 0; i--)
            heapify(i);
    }

    T *extract()
    {
        if (heapsize == 0)
            return NULL;
        heapsize--;
        swap(1, heapsize + 1);
        heapify(1);
        return queue[heapsize + 1];
    }

    void heapsort()
    {
        int node_number = heapsize;
        for (int i = 0; i < node_number; i++)
            extract();
        heapsize = node_number;
    }
};

template <class T>
class Task
{
public:
    Task(int size)
    {
        MinHeap<T> *heap;
        T **queue = new T *[size];

        for (int i = 1; i <= size; i++)
        {
            T v;
            in >> v;

            queue[i] = new T(v);
        }

        heap = new MinHeap<T>(queue, size);

        heap->buildMinHeap();
        heap->heapsort();
        heap->print();

        free(queue);
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