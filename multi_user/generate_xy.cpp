#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	double dataset[10][10];
	double curren_accu[10][10];
	ifstream fin1("sum_time.txt");
	ifstream fin2("current_best_accuracy.txt");
	ofstream fout("xy.txt");

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 9; j++)
			fin1 >> dataset[i][j];

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 9; j++)
			fin2 >> curren_accu[i][j];

	map<double,double> xy;

	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 9; j++)
		{
			double t = dataset[i][j];
			double sum_ = curren_accu[i][j];
		
			for (int k = 0; k < 8; k++)
			{
				double max_ = 0;
				// for every dataset k, find the current best accuracy which the sum of time <= t
				if (k != i)
				{
					for (int u = 0; u < 9; u++)
					{
						if (dataset[k][u] <= t)
						{
							if (curren_accu[k][u] > max_)
							{
								max_ = curren_accu[k][u];
							}
						}
					}
				}
				sum_ += max_;
			}
			xy.insert(std::pair<double,double>(t,sum_));
			//xy.insert((t,sum_));
			fout << t << " " << sum_ << endl;
		}



	return 0;
}