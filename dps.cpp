/*
 *  Ver: 0.2
 *  3 cards
 */

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("input.txt");
ifstream att("att.txt");

const int MAX = 1000;

int card[MAX][10];
char name[MAX][100];
int monatt;
int n;
int beishu = 100;
double atta[6], attb[6];

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

void Search (int num[3])
{
    int dps = Dps (num);
    cout << name[num[0]] << '\n' << name[num[1]] << '\n' << name[num[2]] << '\n';
    cout << dps << endl;
    cout << endl;
}

void Max_dps ()
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

void Fin_cost (int up)
{
    int maxdps = 0, maxcost, maxi, maxj, maxk;
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

void Hp (int low)
{
    int maxdps = 0, mincost = 1000, maxi, maxj, maxk;
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

void Change_atk (int mode, int ty, int tl)
{
    if (mode == 0)
    {
	monatt = ty;
	cout << monatt;
    }
    else if (mode == 1)
    {
	monatt = atta[ty] + attb[ty] * tl;
	cout << monatt;
    }
    cout << endl << endl;
}

int main ()
{
    for (int i=0; i<6; ++i)
	att >> atta[i] >> attb[i];

    fin >> n;

    for (int i=0; i<n; ++i)
    {
	fin >> card[i][0] >> card[i][1] >> card[i][2] >> card[i][3] >> card[i][4] >> card[i][5] >> name[i];
	// att hp type num times
    }
    fin >> monatt;

    int m;
    while (fin >> m)
    {
	if (m == 0) // search mode
	{
	    int temp[3];
	    fin >> temp[0] >> temp[1] >> temp[2];
	    Search (temp);
	}
	if (m == 1) // max
	{
	    Max_dps ();
	}
	if (m == 2) // cost
	{
	    int up;
	    fin >> up;
	    Fin_cost (up);
	}
	if (m == 3) // hp
	{
	    int low;
	    fin >> low;
	    Hp (low);
	}
	if (m == 4)
	{
	    int monty, monle;
	    fin >> monty >> monle;
	    Change_atk (1, monty, monle);
	}
    }
    while (cin >> m)
    {
	if (m == 0) // search mode
	{
	    int temp[3];
	    cin >> temp[0] >> temp[1] >> temp[2];
	    Search (temp);
	}
	if (m == 1) // max
	{
	    Max_dps ();
	}
	if (m == 2) // cost
	{
	    int up;
	    cin >> up;
	    Fin_cost (up);
	}
	if (m == 3) // hp
	{
	    int low;
	    cin >> low;
	    Hp (low);
	}
	if (m == 4)
	{
	    int monty, monle;
	    cin >> monty >> monle;
	    Change_atk (1, monty, monle);
	}
    }
    return 0;
}
