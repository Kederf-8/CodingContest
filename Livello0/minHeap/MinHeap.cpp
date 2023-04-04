#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class MinHeap
{
public:
    T **queue;
    int queueLength, heapsize, heapifyCalls;

    int left(int i) { return i << 1; }
    int right(int i) { return (i << 1) | 1; }
    int parent(int i) { return i >> 1; }
    void printHeapifyCalls() const { out << heapifyCalls << " "; }
    void printKey(int i) const { out << *(queue)[i] << " "; }

    void print() const
    {
        printHeapifyCalls();
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

    MinHeap(int size)
    {
        queue = new T *[size + 1];
        queueLength = size + 1;
        heapsize = 0;
        heapifyCalls = 0;
    }

    void moveUpKey(int i)
    {
        while (i > 1 && *queue[i] < *queue[parent(i)])
        {
            swap(i, parent(i));
            i = parent(i);
        }
    }

    void enqueue(T k)
    {
        if (heapsize == queueLength - 1)
            return;
        heapsize++;
        queue[heapsize] = new T(k);
        int i = heapsize;
        moveUpKey(i);
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

    T *extract()
    {
        if (heapsize == 0)
            return NULL;
        heapsize--;
        swap(1, heapsize + 1);
        heapify(1);
        return queue[heapsize + 1];
    }
};

template <class T>
class task
{
public:
    MinHeap<T> *heap;

    task(int size)
    {
        heap = new MinHeap<T>(size);

        for (int i = 0; i < size; i++)
        {
            char e, x;
            in >> e;
            in >> x;
            if (x == ':')
            {
                T value;
                in >> value;
                heap->enqueue(value);
            }
            else
            {
                string s;
                in >> s;
                heap->extract();
            }
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

        int size;
        in >> size;

        if (type == "int")
            task<int> *t = new task<int>(size);
        else if (type == "double")
            task<double> *t = new task<double>(size);
        if (type == "bool")
            task<bool> *t = new task<bool>(size);
        if (type == "char")
            task<char> *t = new task<char>(size);
    }
    return 0;
}