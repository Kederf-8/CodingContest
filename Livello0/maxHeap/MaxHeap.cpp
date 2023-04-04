#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class MaxHeap
{
public:
    T **queue;
    int heapsize, queueLength, heapifyCalls;

    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) | 1; }
    int parent(int i) { return i >> 1; }
    void printHeapifyCalls() { out << heapifyCalls << " "; }
    void printKey(int i) const { out << *(queue)[i] << " "; }

    void swap(int i, int j)
    {
        T *tmp = queue[i];
        queue[i] = queue[j];
        queue[j] = tmp;
    }

    void print() const
    {
        for (int i = 1; i <= heapsize; i++)
            printKey(i);
        out << endl;
    }

    void heapify(int index)
    {
        int i = index;
        while (i <= heapsize)
        {
            if (heapsize > 0)
                heapifyCalls++;
            int x = i;
            int l = left(i);
            int r = right(i);
            if (l <= heapsize && *queue[x] < *queue[l])
                x = l;
            if (r <= heapsize && *queue[x] < *queue[r])
                x = r;
            if (x == i)
                break;
            swap(i, x);
            i = x;
        }
    }

    MaxHeap(int size)
    {
        queue = new T *[size + 1];
        queueLength = size + 1;
        heapsize = 0;
        heapifyCalls = 0;
    }

    void moveUpKey(int i)
    {
        while (i > 1 && *queue[i] > *queue[parent(i)])
        {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    MaxHeap<T> *enqueue(T k)
    {
        if (heapsize == queueLength - 1)
            return this;
        heapsize += 1;
        queue[heapsize] = new T(k);
        int i = heapsize;
        moveUpKey(i);
        return this;
    }

    T *extractMax()
    {
        if (heapsize == 0)
            return NULL;
        swap(1, heapsize);
        heapsize--;
        heapify(1);
        return queue[heapsize + 1];
    }
};

template <class T>
class Task
{
public:
    MaxHeap<T> *heap;

    Task(int size)
    {
        heap = new MaxHeap<T>(size);

        for (int i = 0; i < size; i++)
        {
            char e, x;
            T v;

            in >> e;
            in >> x;

            if (x == ':')
            {
                in >> v;
                heap->enqueue(v);
            }
            else
            {
                string a;
                in >> a;
                heap->extractMax();
            }
        }

        heap->printHeapifyCalls();
        heap->print();
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string type;
        int n;

        in >> type;
        in >> n;

        if (type == "int")
            Task<int> *t = new Task<int>(n);

        else if (type == "double")
            Task<double> *t = new Task<double>(n);

        else if (type == "bool")
            Task<bool> *t = new Task<bool>(n);

        else if (type == "char")
            Task<char> *t = new Task<char>(n);
    }
    return 0;
}
