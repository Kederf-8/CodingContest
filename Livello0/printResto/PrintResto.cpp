#include <fstream>
#include <algorithm>

#define INF 99999999

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

void resto(int r, int n, int *m)
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

    out << result << " ";

    sort(m, m + n, greater<int>());

    if(m[0] * result == r)
    {
        for(int i = 0; i < result; i++)
            out << m[0] << " ";
    }
    else{
        //no sacciu
    }

    out << endl;

    delete[] table;
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

        resto(r, n, m);
    }

    return 0;
}