#include <fstream>
#include <iostream>
using namespace std;

ifstream fin ("mon.txt");
ofstream fout ("att.txt");

double level[100], att[100];
int n;

void Cal ()
{
    double xsum = 0, ysum = 0;
    double xave, yave;
    double xysum = 0, xxsum = 0;
    for (int i=0; i<n; ++i)
    {
	xsum += level[i];
	ysum += att[i];
	xysum += level[i] * att[i];
	xxsum += level[i] * level[i];
    }
    xave = xsum / n;
    yave = ysum / n;
    double b = (n * xysum - xsum * ysum) / (n * xxsum - xsum * xsum);
    double a = yave - b * xave;
    fout << a << ' ' << b << endl;
}

int main ()
{
    int l, t;
    while (fin >> l >> t)
    {
	while (true)
	{
	    if (l == 0 && t == 0)
	    {
		Cal ();
		n = 0;
		break;
	    }
	    level[n] = l, att[n] = t;
	    n ++;
	    fin >> l >> t;
	}
    }
    return 0;
}
