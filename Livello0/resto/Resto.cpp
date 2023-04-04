#include <fstream>
#define INF 9999999

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

int resto(int r, int n, int *m)
{
    int *table = new int[r + 1];

    table[0] = 0;
    
    for (int i = 1; i <= r; i++)
    {
        table[i] = INF;
        for (int j = 0; j < n; j++)
        {
            if (m[j] <= i)
                table[i] = min(table[i], 1 + table[i - m[j]]);
        }
    }

    int result = table[r];

    return result;
};

int main()
{
    for (int i = 0; i < 100; i++)
    {
        int r, n;

        in >> r >> n;

        int m[n];

        for (int j = 0; j < n; j++)
            in >> m[j];

        out << resto(r, n, m) << endl;
    }
    return 0;
}