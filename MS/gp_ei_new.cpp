#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <string.h>
#include <sstream>
#include <math.h> 
#include <Eigen/Eigen>
#include <boost/math/distributions/normal.hpp>

#define ALGO 8
#define PRIOR_DATASET 10 // this is the number of testing dataset
#define TEST_DATASET 9
#define ITERATION 8
#define SCALE_FACTOR 0.5 // scale factor of kernel matrix
#define EPSILON 0.0001

using namespace Eigen;
using namespace std;
using namespace boost;

double prior_accu[PRIOR_DATASET+5][ALGO+5];
double prior_mean[ALGO+5];
double prior_cov[ALGO+5][ALGO+5];
double observe_accu[PRIOR_DATASET*10][ALGO+5];
double beta[ALGO*1000];
double reward[ALGO*1000][ALGO];
double current_mean[ALGO+5];
double current_var[ALGO+5];
double current_max[TEST_DATASET+5];
double kernel[ALGO+5][ALGO+5];
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
double const gaussian_noise = 0.01;
boost::math::normal_distribution<> my_normal(0,1);

void my_cin(string f)
{
	ifstream fin(f);
	for (int i=0; i < PRIOR_DATASET; i++)
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
		for (int j = 0; j < PRIOR_DATASET; j++)
			prior_mean[i] += prior_accu[j][i];
		prior_mean[i] = prior_mean[i] * 1.0 / PRIOR_DATASET;
		cout << prior_mean[i] << " " << endl;
	}
	cout << endl << endl;
	cout << "-----------------------------------------------" << endl;
	cout << "kernel matrix for 9 algorithms is:" << endl;
	for (int i = 0; i < ALGO; i++)
	{
		for (int j = 0; j < ALGO; j++)
		{
			double dis = 0;
			for (int k = 0; k < PRIOR_DATASET; k++)
				dis += (prior_accu[k][i]-prior_accu[k][j])*(prior_accu[k][i] - prior_accu[k][j]);
			kernel[i][j] = SCALE_FACTOR * exp((-1)*dis*1.0/0.5);
			//kernel[i][j] = 1;
			cout << kernel[i][j] << " ";
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
	cout << "variance is: " << endl;
	for (int i = 0; i < ALGO; i++)
	{
		current_var[i] = kernel[i][i] * 1.0;
		cout << current_var[i] << " " << endl;
	}
	for (int i = 0; i < ALGO; i++)
		chosen[i] = 0;

	for (int i = 0; i < TEST_DATASET; i++)
		current_max[i] = 0;

	max_iteration = ITERATION;
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

	cout << endl;

	ofstream fout("ei_with_prior_without_googlenet_just_test.txt");

	int t = 1;
	for (int observe = 0; observe < TEST_DATASET; observe++)
	{
			t = 1;
			init();
			//for (int i = 0; i < ALGO; i++)
			//	current_mean[i] = 0.8;

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
					cout << "For dataset " << observe << ", current max is: " << current_max[observe] << endl;
					for (int i = 0; i < ALGO; i++)
					{
						// choose a 'best' algorithm based on the previous accuracy and covariance information
						// beta[t] is responsible for the balance between exploration and exploitation
						double delta = current_mean[i] - current_max[observe];
						double delta_plus = delta - EPSILON;
						cout << "delta is: " << delta << ",and sigma is: " << sqrt(current_var[i]) << endl;
						
						double tmp_reward = delta_plus + sqrt(current_var[i]) * pdf(my_normal, delta * 1.0/sqrt(current_var[i]))
						-fabs(delta) * cdf(my_normal, (-1)*fabs(delta)/sqrt(current_var[i]));
						cout << "tmp_reward is: " << tmp_reward << endl;
						if (tmp_reward > max_reward)
						{
							max_reward = tmp_reward;
							algo = i;
						}
					}
					chosen[algo] = chosen[algo]+1;
					if (observe_accu[observe][algo] > current_max[observe])
						current_max[observe] = observe_accu[observe][algo];
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
							//double tmp_reward = current_mean[i] + sqrt(beta[t]) * sqrt(current_var[i]);
							double delta = current_mean[i] - current_max[observe];
							double delta_plus = delta - EPSILON;
							cout << "delta is: " << delta << ",and sigma is: " << sqrt(current_var[i]) << endl;
						
							double tmp_reward = delta_plus + sqrt(current_var[i]) * pdf(my_normal, delta * 1.0/sqrt(current_var[i]))
						-fabs(delta) * cdf(my_normal, (-1)*fabs(delta)/sqrt(current_var[i]));
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

			
				
				y[t] = observe_accu[observe][algo] + gaussian_noise;
				cout << "observe_accu is: " << observe_accu[observe][algo] << " " << "noise is: " << gaussian_noise << endl;
		
				for (int j = 0; j < t; j++)
						for (int k = 0; k < t; k++)
							sigma_t[j][k] = kernel[a[j+1]][a[k+1]];
				for (int j = 0; j < t; j++)
				{
					for (int k= 0; k < t; k++)
					{
						if (j == k)
							C_t[j][k] = sigma_t[j][k] + gaussian_noise * gaussian_noise;
						else
							C_t[j][k] = sigma_t[j][k];
					}
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
					}
				}
				
				for (int i = 0; i < ALGO; i++)
				{
					// update mean_[i]
					for (int j = 0; j < t; j++)
						sigma_t_k[j] = kernel[a[j+1]][i];
		
					double tmp[10000];
					for (int j = 0; j < t; j++)
					{
						tmp[j] = 0;
						for (int k = 0; k < t; k++)
							tmp[j] += sigma_t_k[k] * C_t[k][j];
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
						update += tmp[j] * kernel[a[j+1]][i];
		
					current_var[i] = kernel[i][i] - update;
				}
				cout << endl;
				cout << "updated variance is: ";
				for (int i = 0; i < ALGO; i++)
					cout << current_var[i]<< " ";
				cout << endl << endl; 
				t++;
			}
	}
	fout.close();

	return 0;
}