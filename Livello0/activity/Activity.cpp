#include <fstream>

using namespace std;

ifstream in = ifstream("input.txt");
ofstream out = ofstream("output.txt");

class Task
{
public:
    Task(int n)
    {
        struct time_range
        {
            int I;
            int F;
        };

        time_range r[n];

        for (int i = 0; i < n; i++)
        {
            char c;
            int ti, tf;

            in >> c >> ti >> tf >> c;
            r[i].I = ti;
            r[i].F = tf;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (r[i].I < r[j].I || (r[i].I == r[j].I && r[i].F > r[j].F && j != 0))
                {
                    int tmp = r[i].I;
                    r[i].I = r[j].I;
                    r[j].I = tmp;

                    tmp = r[i].F;
                    r[i].F = r[j].F;
                    r[j].F = tmp;
                }
            }
        }

        int i, j, tot = 0;

        i = 0;
        tot += (r[i].F - r[i].I);

        for (j = 1; j < n; j++)
        {
            if (r[j].I >= r[i].F)
            {
                tot += (r[j].F - r[j].I);
                i = j;
            }
        }

        out << tot << endl;
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