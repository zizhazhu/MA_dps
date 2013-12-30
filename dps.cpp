/*
 *  Ver: 0.2
 *  3 cards
 */

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("input.txt");

const int MAX = 1000;

int card[MAX][10];
char name[MAX][100];
int monatt;
int beishu = 100;

int Cost (int num[3])
{
    int cost = 0;
    for (int i=0; i<3; ++i)
    {
	int t;
	t = num[i];
	cost += card[t][5];
    }
    return cost;
}

int Dps (int num[3])
{
    int dps = 0, myattack = 0, myhp = 0, exatt = 0, cost = 0;
    for (int i=0; i<3; ++i)
    {
	int t;
	t = num[i];
	myattack += card[t][0] * card[t][4];
	myhp += card[t][1];
	if (card[t][2] == 0) // att
	{
	    exatt += card[t][0] * card[t][4] * card[t][3] / 100;
	}
	else if (card[t][2] == 1) // hp
	{
	    myhp += card[t][1] * card[t][3] / 100;
	}
    }
    //cout << myattack << ' ' << myhp << ' ' << exatt << endl;
    dps = (myattack * (int)(myhp / monatt) + exatt) * beishu / 100;
    return dps;
}

int main ()
{
    int n;
    fin >> monatt;
    fin >> n;
    for (int i=0; i<n; ++i)
    {
	fin >> card[i][0] >> card[i][1] >> card[i][2] >> card[i][3] >> card[i][4] >> card[i][5] >> name[i];
	//cout << card[i][0] << ' ' << card[i][1] << ' ' << card[i][2] << ' ' << card[i][3] << ' ' << card[i][4] << ' ' << name[i] << endl;
	//sscanf (t, "%d %d %d %d %d", &card[i][0], &card[i][1], &card[i][2], &card[i][3], &card[i][4]);
	// att hp type num times
    }
    int m;
    while (fin >> m)
    {
	if (m == 0) // search mode
	{
	    int temp[3];
	    fin >> temp[0] >> temp[1] >> temp[2];
	    int dps = Dps (temp);
	    int cost = Cost (temp);
	    cout << name[temp[0]] << '\n' << name[temp[1]] << '\n' << name[temp[2]] << '\n';
	    cout << dps << endl;
	    cout << dps / cost << endl;
	    cout << endl;
	}
	if (m == 1) // max
	{
	    int maxdps = 0, cost, maxi, maxj, maxk;
	    for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
		    for (int k=j+1; k<n; ++k)
		    {
			int temp[3];
			temp[0] = i;
			temp[1] = j;
			temp[2] = k;
			int dps = Dps (temp);
			if (maxdps < dps)
			{
			    maxdps = dps;
			    cost = Cost(temp);
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
		    }
	    cout << name[maxi] << '\n' << name[maxj] << '\n' << name[maxk] << '\n' << maxdps << '\n' << cost << '\n' << '\n';
	}
	if (m == 2) // cost
	{
	    int maxdps = 0, maxcost, maxi, maxj, maxk, up;
	    fin >> up;
	    for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
		    for (int k=j+1; k<n; ++k)
		    {
			int temp[3];
			temp[0] = i;
			temp[1] = j;
			temp[2] = k;
			int dps = Dps (temp);
			int cost = Cost (temp);
			if (maxdps < dps && cost <= up)
			{
			    maxdps = dps;
			    maxcost = cost;
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
		    }
	    cout << name[maxi] << '\n' << name[maxj] << '\n' << name[maxk] << '\n' << maxdps << '\n' << maxcost << '\n' << '\n';
	}
	if (m == 3) // hp
	{
	    int maxdps = 0, mincost = 1000, maxi, maxj, maxk, low;
	    fin >> low;
	    for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
		    for (int k=j+1; k<n; ++k)
		    {
			int temp[3];
			temp[0] = i;
			temp[1] = j;
			temp[2] = k;
			int dps = Dps (temp);
			int cost = Cost (temp);
			if (low <= dps && cost < mincost)
			{
			    maxdps = dps;
			    mincost = cost;
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
			else if (cost == mincost && dps > maxdps)
			{
			    maxdps = dps;
			    mincost = cost;
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
		    }
	    cout << name[maxi] << '\n' << name[maxj] << '\n' << name[maxk] << '\n' << maxdps << '\n' << mincost << '\n' << '\n';
	}
    }
    while (cin >> m)
    {
	if (m == 0) // search mode
	{
	    int temp[3];
	    cin >> temp[0] >> temp[1] >> temp[2];
	    int dps = Dps (temp);
	    int cost = Cost (temp);
	    cout << name[temp[0]] << '\n' << name[temp[1]] << '\n' << name[temp[2]] << '\n';
	    cout << dps << endl;
	    cout << dps / cost << endl;
	    cout << endl;
	}
	if (m == 1) // max
	{
	    int maxdps = 0, cost, maxi, maxj, maxk;
	    for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
		    for (int k=j+1; k<n; ++k)
		    {
			int temp[3];
			temp[0] = i;
			temp[1] = j;
			temp[2] = k;
			int dps = Dps (temp);
			if (maxdps < dps)
			{
			    maxdps = dps;
			    cost = Cost(temp);
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
		    }
	    cout << name[maxi] << '\n' << name[maxj] << '\n' << name[maxk] << '\n' << maxdps << '\n' << cost << '\n' << '\n';
	}
	if (m == 2) // cost
	{
	    int maxdps = 0, maxcost, maxi, maxj, maxk, up;
	    cin >> up;
	    for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
		    for (int k=j+1; k<n; ++k)
		    {
			int temp[3];
			temp[0] = i;
			temp[1] = j;
			temp[2] = k;
			int dps = Dps (temp);
			int cost = Cost (temp);
			if (maxdps < dps && cost <= up)
			{
			    maxdps = dps;
			    maxcost = cost;
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
		    }
	    cout << name[maxi] << '\n' << name[maxj] << '\n' << name[maxk] << '\n' << maxdps << '\n' << maxcost << '\n' << '\n';
	}
	if (m == 3) // hp
	{
	    int maxdps = 0, mincost = 1000, maxi, maxj, maxk, low;
	    cin >> low;
	    for (int i=0; i<n; ++i)
		for (int j=i+1; j<n; ++j)
		    for (int k=j+1; k<n; ++k)
		    {
			int temp[3];
			temp[0] = i;
			temp[1] = j;
			temp[2] = k;
			int dps = Dps (temp);
			int cost = Cost (temp);
			if (low <= dps && cost < mincost)
			{
			    maxdps = dps;
			    mincost = cost;
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
			else if (cost == mincost && dps > maxdps)
			{
			    maxdps = dps;
			    mincost = cost;
			    maxi = i;
			    maxj = j;
			    maxk = k;
			}
		    }
	    cout << name[maxi] << '\n' << name[maxj] << '\n' << name[maxk] << '\n' << maxdps << '\n' << mincost << '\n' << '\n';
	}
    }
    return 0;
}
