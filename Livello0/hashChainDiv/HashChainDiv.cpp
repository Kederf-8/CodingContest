#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

template <class T>
class Task
{
public:
    int *HashTable;
    int N, M;

    Task(int m, int n)
    {
        N = n;
        M = m;
        HashTable = new int[m];

        for (int i = 0; i < m; i++)
            HashTable[i] = 0;

        for (int i = 0; i < n; i++)
        {
            T v;
            in >> v;

            HashTable[int(v) % M]++;
        }

        for (int i = 0; i < m; i++)
            out << HashTable[i] << " ";
        out << endl;
    }
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        string type;
        int m, n;

        in >> type >> m >> n;

        if (type == "int")
            Task<int> *t = new Task<int>(m, n);
        if (type == "double")
            Task<double> *t = new Task<double>(m, n);
        if (type == "bool")
            Task<bool> *t = new Task<bool>(m, n);
        if (type == "char")
            Task<char> *t = new Task<char>(m, n);
    }
    return 0;
}