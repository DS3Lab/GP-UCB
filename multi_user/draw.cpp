#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

#define USER 4
#define ALGO 9

int main()
{
	ifstream fin("multi_user_2_4.txt",'r');
	ifstream fin1("test44.txt",'r');
	ifstream fin2("test_time2.txt",'r');
	ofstream fout("xy_.txt",'w');

	double test_time[10][10];
	double accu[10][10];
	double x_time[100];
	double y_sum_accu[100];

	for (int i = 0; i < USER; i++)
	{
		for (int j = 0; j < ALGO; j++)
		{
			fin1 >> accu[i][j];
			cout << accu[i][j]<< " ";
			fin2 >> test_time[i][j];
			cout << test_time[i][j];
		}
		cout << endl;
	}
	/*accu[0] = (0.04, 0.05,0.03	,0.04,	0.04	,0.04	,0.04,	0.03	,0.04);
	accu[1] = {0.08	,0.13	,0.13	,0.12,	0.12	,0.12,	0.12	,0.12	,0.03};
	accu[2] = {0.25,	0.3,	0.3,	    0.21,	0.26	,0.28,	0.2,	    0.23	,0.28};
	accu[3] = {0.27,	0.34,	0.29	,0.36,	0.33,	0.27,	0.35	,0.32,	0.35};

	test_time[0] = {42.75,	96.0,	2250.0	,10.0,	112.5	,132.25,	1700.0,	2050.0	,300.0};
	test_time[1] = {150.0	,400.0	,2250.0	,1.0	,25.0	,1150.0,	1700.0,	2050.0	,300.0};
	test_time[2] = {150.0,	320.0,	2250.0,	83.0	,43.75,	1150.0,	1700.0,	2050.0,	300.0};
	test_time[3] = {150.0,	160.0,	2250.0	,18.5,	75.0	,1150.0	,1700.0,	2050.0,	279.0};*/

	double sum_time = 0;
	double sum_accu = 0;
	double max_accu[USER]; // keep updating the maximal accuracy for each user

	for (int i = 0; i < USER; i++)
		max_accu[i] = 0;

	for (int i = 0; i < USER * ALGO; i++)
	{
		int u, a;
		fin  >> u >> a;
		sum_time += test_time[u][a];
		x_time[i] = sum_time;

		if (accu[u][a] > max_accu[u])
		{
			sum_accu = sum_accu - max_accu[u] + accu[u][a];
			max_accu[u] = accu[u][a];
		}

		y_sum_accu[i] = sum_accu;

	}

	for (int i = 0; i < USER * ALGO; i++)
	{
		fout << x_time[i] << " ";
	}
	fout << endl;
	for (int i = 0; i < USER * ALGO; i++)
	{
		fout << y_sum_accu[i] << " ";
	}

	return 0;
}