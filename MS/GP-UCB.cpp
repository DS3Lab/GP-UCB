#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <sstream>
#include <math.h> 
#include <Eigen/Eigen>

#define ALGO 9
#define DATASET 10
#define TEST 1
#define ITERATION 9
#define FACTOR 0.05

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
int chosen[ALGO];
int max_iteration;

// y has the same meaning with y in the draft
double algo_id[10000]; // algo_id[t] represents the algorithm_id chosen at time point t

double const sigma = 0.5;

void my_cin(string f)
{
	ifstream fin(f);
	for (int i=0; i < DATASET; i++)
		for (int j = 0; j < ALGO ; j++)
			fin >> prior_accu[i][j];
}

void calculate_prior_gaussian()
{
	memset(prior_mean, 0, sizeof(prior_mean));
	memset(prior_cov, 0, sizeof(prior_cov));

	cout << "prior mean for the algorithms is:" << endl;
	for (int i = 0; i < ALGO; i++)
	{
		prior_mean[i] = 0;
		for (int j = 0; j < DATASET; j++)
			prior_mean[i] += prior_accu[j][i];
		prior_mean[i] = prior_mean[i] * 1.0 / DATASET * 0.3;
		cout << prior_mean[i] << " " << endl;
	}
	cout << endl << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "prior covarance for 9 algorithms is:" << endl;
	for (int i = 0; i < ALGO; i++)
	{
		for (int j = 0; j < ALGO; j++)
		{
			double tmp1[DATASET+5];
			double tmp2[DATASET+5];
			double sum_ = 0;
			for (int k = 0; k < DATASET; k++)
			{
				tmp1[k] = prior_accu[k][i] - prior_mean[i];
				tmp2[k] = prior_accu[k][j] - prior_mean[j];
				sum_ += tmp1[k] * tmp2[k];
			}
			
			//sum_ = 0.1;
			prior_cov[i][j] = sum_ * 1.0 / DATASET ;
			//double tmp_ = fabs(prior_mean[i]-prior_mean[j]) * 1.0 / 0.5;
			//tmp_ = FACTOR *(1 + sqrt(5 * tmp_) + 5.0/3 * tmp_ * exp((-1)*sqrt(5 * tmp_)));
			//prior_cov[i][j] = tmp_;
			cout << prior_cov[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-----------------------------------------------" << endl;
}

void cin_test(string f)
{
	ifstream fin(f);
	string test_line;
	double accu;
	int i = 0;
	while (getline(fin, test_line))
	{
		istringstream stream(test_line);   
		int j = 0; 
		while (stream >> accu)  
		{
			// observe_accu[i][j]: simulates the observed quality in the i-th time by the j-th algorithm
			// i starts from 1

			observe_accu[i][j] = double(accu);
			if (i == 0)
				cout << "observed accuracy for algorithm " << j + 1 << " is: " << observe_accu[i][j] << endl;
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
	for (int i = 0; i < ALGO; i++)
		chosen[i] = 0;
	max_iteration = 8;
}

// generate the Gaussian noise ~ N (mu, sigma * sigma)

double generate_gaussian_noise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0 * 3.14159265358979323846;

	static double z0, z1;


	static bool generate;
	generate = !generate;

	/*if (!generate)
	{
		return z1 * sigma + mu;
	}*/

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
	my_cin(argv[1]);
	calculate_prior_gaussian();
	cin_test(argv[2]);
	init();

	for (int i = 0; i < ALGO; i++)
		prior_mean[i] = 0.5;

	cout << endl;

	cout << "Data  has been loaded..." << endl;

	ofstream fout("predict_without_prior2_withoutgooglenet.txt");

	int t = 1;
	for (int observe = 0; observe < TEST; observe++)
	{
			t = 1;
			init();
			if (observe > 0)
				fout << endl;
			while (t <= max_iteration) // 
			{
				cout << "Iteration: " << t << endl;
				beta[t] = log(ALGO * t * t * 1.0 /sigma);
				cout << beta[t] << endl;
				double max_reward = -1000000.0;
				int algo = -1; // the algo_id we find currently which has the max_reward
				while (1)
				{
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
					chosen[algo] = chosen[algo]+1;
					cout << algo+1 <<" has been chosen " << chosen[algo] << "times"<< endl;
					a[t] = algo;
					if (chosen[algo] > 1 && chosen[algo] < 5)
					{
						max_iteration = max_iteration+1;
						break;
					}
					else if (chosen[algo] >= 5)
					{
						cout << "enter re-choosing..." << endl;
						max_reward = -100000000.0;
						algo = -1;
						for (int i = 0; i < ALGO; i++)
						{
							double tmp_reward = current_mean[i] + sqrt(beta[t]) * current_cov[i][i];
							
							if (tmp_reward > max_reward && chosen[i] == 0)
							{
								max_reward = tmp_reward;
								algo = i;
							}
						}
						if (algo == -1)
							break;
						a[t] = algo;
						chosen[algo] = chosen[algo]+1;
						cout << "choose " << algo+1 << " which has not been chosen before..." << endl;
						fout << algo + 1 << " ";
					}	
					else
						fout << algo + 1 << " ";
					break;
				}	

			
				double gaussian_noise = 0.001;
				y[t] = observe_accu[observe][algo] + gaussian_noise;
				cout << "observe_accu is: " << observe_accu[0][algo] << " " << "noise is: " << gaussian_noise << endl;
		
				for (int j = 0; j < t; j++)
						for (int k = 0; k < t; k++)
							sigma_t[j][k] = current_cov[a[j+1]][a[k+1]];
				for (int j = 0; j < t; j++)
				{
					for (int k= 0; k < t; k++)
					{
						if (j == k)
							C_t[j][k] = sigma_t[j][k] + gaussian_noise * gaussian_noise;
						else
							C_t[j][k] = sigma_t[j][k];
						cout << C_t[j][k] << " ";
					}
					cout << endl;
				}
		
					// compute (C_t)-reverse
		
				MatrixXd C_t_eigen(40, 40);
				for (int j = 0; j < 40; j++)
					for (int k = 0; k < 40; k++)
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
				{
					for (int k = 0; k < t; k++)
					{
						C_t[j][k] = C_t_eigen(j,k);
						cout << C_t[j][k] << " ";
					}
					cout << endl;
				}
				
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
						cout << "tmpj: " << tmp[j]<< " "<< endl;
					}
					current_mean[i] = 0;
					cout << "updated mean is: ";
					for (int j = 0; j < t; j++)
					{
						current_mean[i] += tmp[j]* y[j+1];
						
					}
					cout << current_mean[i] << " ";
		
		
					// update cov
					double update = 0;
					for (int j = 0; j < t; j++)
						update += tmp[j] * current_cov[a[j+1]][i];
		
					current_cov[i][i] -= update;
				}
				cout << endl;
				cout << "updated covariance is: ";
				for (int i = 0; i < ALGO; i++)
					cout << current_cov[i][i] << " ";
				cout << endl << endl; 
				t++;
			}
	}
	fout.close();

	return 0;
}