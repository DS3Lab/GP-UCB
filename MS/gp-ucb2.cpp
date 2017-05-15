#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <sstream>
#include <math.h> 
#include <Eigen/Eigen>

#define ALGO 9
#define DATASET 22

using namespace Eigen;
using namespace std;

double prior_accu[DATASET+5][ALGO+5];
double prior_mean[ALGO+5];
double prior_cov[ALGO+5][ALGO+5];
double observe_accu[DATASET*10][ALGO+5];
double beta[ALGO*1000];
double reward[ALGO*1000][ALGO];
double current_mean[ALGO+5];
double current_cov[ALGO+5][ALGO+5];
double y[10000]; 
double sigma_t_k[10000];
double sigma_t[10000][10000];
int a[10000]; // start from a[1]
double C_t[10000][10000]; // 10000 is time t;

// y has the same meaning with y in the draft
double algo_id[10000]; // algo_id[t] represents the algorithm_id chosen at time point t

double const sigma = 0. 5;

/*
void my_cin(string f)
{
	ifstream fin(f);
	for (int i=0; i < DATASET; i++)
		for (int j = 0; j < ALGO ; j++)
			fin >> prior_accu[i][j];
}*/

void init_prior_gaussian()
{
	memset(prior_mean, 0, sizeof(prior_mean));
	memset(prior_cov, 0, sizeof(prior_cov));

	cout << "prior mean for 9 algorithms is:" << endl;
	for (int i = 0; i < ALGO; i++)
	{
		prior_mean[i] = 0;
		cout << prior_mean[i] << " " << endl;
	}
	cout << endl << endl;
	cout << "prior covarance for 9 algorithms is:" << endl;
	for (int i = 0; i < ALGO; i++)
	{
		for (int j = 0; j < ALGO; j++)
		{
			prior_cov[i][j] = 0.01;
			cout << prior_cov[i][j] << " ";
		}
		cout << endl;
	}
}

void cin_test(string f)
{
	ifstream fin(f);
	string test_line, accu;
	int i = 0;
	while (getline(fin, test_line))
	{
		istringstream stream(test_line);   
		int j = 0; 
		while (stream >> accu)  
		{
			// observe_accu[i][j]: simulates the observed quality in the i-th time by the j-th algorithm
			// i starts from 1

			observe_accu[i][j] = double(stoi(accu));
			j++;
		}			 
		i++;
	}
}

void init()
{
	for (int i = 0; i < ALGO; i++)
		current_mean[i] = prior_mean[i];
	for (int i = 0; i < ALGO; i++)
		for (int j = 0; j < ALGO; j++)
			current_cov[i][j] = prior_cov[i][j];
}

// generate the Gaussian noise ~ N (mu, sigma * sigma)

double generate_gaussian_noise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0 * 3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
	{
		return z1 * sigma + mu;
	}

	double u1, u2;
	do
	{
		u1 = rand() * (1.0 / RAND_MAX);
		u2 = rand() * (1.0 / RAND_MAX);

	} while (u1 <= epsilon); // in case u1 is 0

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u2)) * sin(two_pi * u1);

	cout << "the gaussian noise generated randomly is: " << z0 * sigma + mu << endl;
	return z0 * sigma + mu;
}

int main(int argc, char const *argv[])
{

	init_prior_gaussian();
	cin_test(argv[1]);
	init();

	cout << "Data  has been loaded..." << endl;

	ofstream fout("predict2.txt");

	int t = 1;
	while (t <= ALGO * 40) // fisrt, only try to iterate through all the arms once
	{
		cout << "Iteration: " << t << endl;
		beta[t] = log(ALGO * t * t *1.0/ sigma);
		double max_reward = -1000000.0;
		int algo = -1; // the algo_id we find currently which has the max_reward
		for (int i = 0; i < ALGO; i++)
		{
			// choose a 'best' algorithm based on the previous accuracy and covariance information
			// beta[t] is responsible for the balance between exploration and exploitation
			double tmp_reward = current_mean[i] + sqrt(beta[t]) * current_cov[i][i];
			cout << "tmp_reward is: " << tmp_reward << endl;
			if (tmp_reward > max_reward)
			{
				max_reward = tmp_reward;
				algo = i;
			}
		}
		a[t] = algo;
		fout << algo + 1 << endl;
		double gaussian_noise = generate_gaussian_noise(0, sigma);
		y[t] = observe_accu[0][algo] + gaussian_noise;

		for (int j = 0; j < t; j++)
				for (int k = 0; k < t; k++)
					sigma_t[j][k] = current_cov[a[j+1]][a[k+1]];
		for (int j = 0; j < t; j++)
			for (int k= 0; k < t; k++)
			{
				if (j == k)
					C_t[j][k] = sigma_t[j][k] + sigma * sigma;
				else
					C_t[j][k] = sigma_t[j][k];
			}
			// compute (C_t)-1

		MatrixXd C_t_eigen(360, 360);
		for (int j = 0; j < 360; j++)
			for (int k = 0; k < 360; k++)
			{
				if (j < t && k < t)
					C_t_eigen(j,k) = C_t[j][k];
				else if (j == k)
					C_t_eigen(j,k) = 1;
				else
					C_t_eigen(j,k) = 0;
			}
		C_t_eigen = C_t_eigen.inverse();
		for (int j = 0; j < t; j++)
			for (int k = 0; k < t; k++)
				C_t[j][k] = C_t_eigen(j,k);
		
		for (int i = 0; i < ALGO; i++)
		{
			// update mean_[i]
			for (int j = 0; j < t; j++)
				sigma_t_k[j] = current_cov[a[j+1]][i];

			double tmp[10000];
			for (int j = 0; j < t; j++)
			{
				tmp[j] = 0;
				for (int k = 0; k < t; k++)
					tmp[j] += sigma_t_k[k] * C_t[k][j];
			}
			current_mean[i] = 0;
			for (int j = 0; j < t; j++)
				current_mean[i] += tmp[j]* y[j+1];


			// update cov
			double update = 0;
			for (int j = 0; j < t; j++)
				update += tmp[j] * current_cov[a[j+1]][i];

			current_cov[i][i] -= update;

		}

		t++;
	}
	fout.close();

	return 0;
}